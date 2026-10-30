#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Quest.generated.h"

class UQuestSettings;
class UQuestCondition;

UENUM(BlueprintType)
enum class EQuestStatus : uint8
{
    WaitingForStart,
    Started,
    Completed
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnQuestStatusChanged, EQuestStatus, OldStatus, EQuestStatus, NewStatus);

UCLASS()
class PRACTICE_API AQuest : public AActor
{
    GENERATED_BODY()
public:
    AQuest();
    void UpdateStartStatus();
    void UpdateEndStatus();
    UFUNCTION(BlueprintPure, Category="Quest")
    EQuestStatus GetQuestStatus() const { return QuestStatus; }
    UPROPERTY(BlueprintAssignable, Category="Quest")
    FOnQuestStatusChanged OnQuestStatusChanged;
protected:
    virtual void BeginPlay() override;
    void SetQuestStatus(EQuestStatus NewStatus);
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    TObjectPtr<UQuestSettings> QuestSettings;
    UPROPERTY()
    TArray<UQuestCondition*> StartConditions;
    UPROPERTY()
    TArray<TObjectPtr<UQuestCondition>> EndConditions;
    UPROPERTY(BlueprintReadOnly)
    EQuestStatus QuestStatus = EQuestStatus::WaitingForStart;
private:
    bool bInitializingConditions = false;
};
