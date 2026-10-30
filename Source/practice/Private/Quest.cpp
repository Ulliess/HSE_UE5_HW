#include "Quest.h"
#include "QuestSettings.h"
#include "QuestCondition.h"
#include "QuestSystemComponent.h"
#include "GameFramework/GameModeBase.h"
#include "HAL/IConsoleManager.h"

int32 bDebugInstantFinish = 0;
FAutoConsoleVariableRef CVarDebugInstantFinish(TEXT("quest.InstantFinish"), bDebugInstantFinish, TEXT("Debug Instantly Finish Quests"), ECVF_Cheat);

AQuest::AQuest()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AQuest::SetQuestStatus(EQuestStatus NewStatus)
{
    if (QuestStatus == NewStatus) return;
    const EQuestStatus OldStatus = QuestStatus;
    QuestStatus = NewStatus;
    OnQuestStatusChanged.Broadcast(OldStatus, NewStatus);
}

void AQuest::BeginPlay()
{
    Super::BeginPlay();
    if (AGameModeBase* GameMode = GetWorld()->GetAuthGameMode())
    {
        if (UQuestSystemComponent* Component = GameMode->GetComponentByClass<UQuestSystemComponent>())
            Component->RegisterQuest(this);
    }
    if (!ensureMsgf(QuestSettings, TEXT("Missing quest settings: %s"), *GetName())) return;
    for (const UQuestCondition* Template : QuestSettings->StartConditionsInst)
    {
        if (!ensureMsgf(Template, TEXT("Invalid start condition: %s"), *GetName())) return;
    }
    bInitializingConditions = true;
    for (const UQuestCondition* Template : QuestSettings->StartConditionsInst)
    {
        UQuestCondition* Condition = DuplicateObject<UQuestCondition>(Template, this);
        StartConditions.Add(Condition);
        Condition->OnQuestConditionCompleted.AddUObject(this, &AQuest::UpdateStartStatus);
    }
    for (UQuestCondition* Condition : StartConditions) Condition->StartCondition();
    bInitializingConditions = false;
    UpdateStartStatus();
}

void AQuest::UpdateStartStatus()
{
    if (bInitializingConditions || QuestStatus != EQuestStatus::WaitingForStart || !QuestSettings) return;
    for (UQuestCondition* Condition : StartConditions)
    {
        if (!IsValid(Condition) || !Condition->IsCompleted()) return;
    }
    for (const UQuestCondition* Template : QuestSettings->EndConditionsInst)
    {
        if (!ensureMsgf(Template, TEXT("Invalid end condition: %s"), *GetName())) return;
    }
    for (UQuestCondition* Condition : StartConditions)
    {
        Condition->OnQuestConditionCompleted.RemoveAll(this);
        Condition->StopCondition();
    }
    bInitializingConditions = true;
    SetQuestStatus(EQuestStatus::Started);
    if (bDebugInstantFinish)
    {
        bInitializingConditions = false;
        SetQuestStatus(EQuestStatus::Completed);
        return;
    }
    for (const UQuestCondition* Template : QuestSettings->EndConditionsInst)
    {
        UQuestCondition* Condition = DuplicateObject<UQuestCondition>(Template, this);
        EndConditions.Add(Condition);
        Condition->OnQuestConditionCompleted.AddUObject(this, &AQuest::UpdateEndStatus);
    }
    for (UQuestCondition* Condition : EndConditions) Condition->StartCondition();
    bInitializingConditions = false;
    UpdateEndStatus();
}

void AQuest::UpdateEndStatus()
{
    if (bInitializingConditions || QuestStatus != EQuestStatus::Started) return;
    for (UQuestCondition* Condition : EndConditions)
    {
        if (!IsValid(Condition) || !Condition->IsCompleted()) return;
    }
    for (UQuestCondition* Condition : EndConditions)
    {
        Condition->OnQuestConditionCompleted.RemoveAll(this);
        Condition->StopCondition();
    }
    SetQuestStatus(EQuestStatus::Completed);
}
