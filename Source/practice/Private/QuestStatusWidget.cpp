#include "QuestStatusWidget.h"

void UQuestStatusWidget::SetObservedQuest(AQuest* InQuest)
{
    if (IsValid(ObservedQuest))
        ObservedQuest->OnQuestStatusChanged.RemoveDynamic(this, &UQuestStatusWidget::HandleQuestStatusChanged);
    ObservedQuest = InQuest;
    if (IsValid(ObservedQuest))
        ObservedQuest->OnQuestStatusChanged.AddUniqueDynamic(this, &UQuestStatusWidget::HandleQuestStatusChanged);
    RefreshQuestColor();
}

void UQuestStatusWidget::NativeConstruct()
{
    Super::NativeConstruct();
    if (IsValid(ObservedQuest))
        ObservedQuest->OnQuestStatusChanged.AddUniqueDynamic(this, &UQuestStatusWidget::HandleQuestStatusChanged);
    RefreshQuestColor();
}

void UQuestStatusWidget::NativeDestruct()
{
    if (IsValid(ObservedQuest))
        ObservedQuest->OnQuestStatusChanged.RemoveDynamic(this, &UQuestStatusWidget::HandleQuestStatusChanged);
    Super::NativeDestruct();
}

void UQuestStatusWidget::HandleQuestStatusChanged(EQuestStatus OldStatus, EQuestStatus NewStatus)
{
    RefreshQuestColor();
}

void UQuestStatusWidget::RefreshQuestColor()
{
    const bool bCompleted = IsValid(ObservedQuest) && ObservedQuest->GetQuestStatus() == EQuestStatus::Completed;
    SetColorAndOpacity(bCompleted ? CompletedColor : NormalColor);
}
