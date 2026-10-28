// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Quest.generated.h"

class UQuestSettings;
class UQuestCondition;

UENUM()
enum class EQuestStatus : uint8
{
	WaitingForStart,
	Started,
	Completed
};

UCLASS()
class PRACTICE_API AQuest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void UpdateStartStatus();
	void UpdateEndStatus();
	EQuestStatus GetQuestStatus() const {return QuestStatus;}
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UQuestSettings> QuestSettings;

	UPROPERTY()
	TArray<UQuestCondition*> StartConditions;
	UPROPERTY()
	TArray<TObjectPtr<UQuestCondition>> EndConditions;
	UPROPERTY(BlueprintReadOnly)
	EQuestStatus QuestStatus = EQuestStatus::WaitingForStart;
};
