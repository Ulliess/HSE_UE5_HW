#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Quest.h"
#include "QuestStatusWidget.generated.h"

UCLASS(Abstract, Blueprintable)
class PRACTICE_API UQuestStatusWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Quest")
    void SetObservedQuest(AQuest* InQuest);
protected:
    virtual void NativeConstruct() override;
    virtual void NativeDestruct() override;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quest|Appearance")
    FLinearColor NormalColor = FLinearColor::White;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Quest|Appearance")
    FLinearColor CompletedColor = FLinearColor::Green;
    UPROPERTY(BlueprintReadOnly, Category="Quest")
    TObjectPtr<AQuest> ObservedQuest;
private:
    void RefreshQuestColor();
    UFUNCTION()
    void HandleQuestStatusChanged(EQuestStatus OldStatus, EQuestStatus NewStatus);
};
