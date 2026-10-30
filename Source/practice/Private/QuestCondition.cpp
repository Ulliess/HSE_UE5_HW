#include "QuestCondition.h"

DEFINE_LOG_CATEGORY(LogQuest)

void UQuestCondition::Complete()
{
    bCompleted = true;
    UE_LOG(LogQuest, Log, TEXT("Condition completed: %s, quest: %s"), *GetName(), *GetNameSafe(GetOuter()));
    OnQuestConditionCompleted.Broadcast();
}
