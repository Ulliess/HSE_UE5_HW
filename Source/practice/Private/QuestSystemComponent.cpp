#include "QuestSystemComponent.h"
#include "EngineUtils.h"
#include "Quest.h"
#include "QuestCondition.h"

UQuestSystemComponent::UQuestSystemComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UQuestSystemComponent::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogQuest, Log, TEXT("Quest system started. Quests to spawn: %d"), Quests.Num());
    for (const TSubclassOf<AQuest>& QuestClass : Quests)
    {
        AQuest* Quest = GetWorld()->SpawnActor<AQuest>(QuestClass);
        if (Quest)
        {
            UE_LOG(LogQuest, Log, TEXT("Quest spawned: %s"), *GetNameSafe(Quest));
        }
        else
        {
            UE_LOG(LogQuest, Warning, TEXT("Failed to spawn quest: %s"), *GetNameSafe(QuestClass.Get()));
        }
    }
}

void UQuestSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UQuestSystemComponent::GetActiveAndStartedQuests(TArray<AQuest*>& OutQuests)
{
    for (AQuest* Quest : ActiveQuests)
    {
        if (Quest->GetQuestStatus() == EQuestStatus::Started)
        {
            OutQuests.Add(Quest);
        }
    }
}

void UQuestSystemComponent::RegisterQuest(AQuest* NewQuest)
{
    ActiveQuests.AddUnique(NewQuest);
    UE_LOG(LogQuest, Log, TEXT("Quest registered: %s"), *GetNameSafe(NewQuest));
}
