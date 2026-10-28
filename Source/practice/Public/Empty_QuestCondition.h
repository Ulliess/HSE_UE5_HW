// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestCondition.h"
#include "UObject/Object.h"
#include "Empty_QuestCondition.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICE_API UEmpty_QuestCondition : public UQuestCondition
{
	GENERATED_BODY()
public:
	virtual void StartCondition() override;
	virtual void StopCondition() override;
};
