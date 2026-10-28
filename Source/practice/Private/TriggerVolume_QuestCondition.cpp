// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerVolume_QuestCondition.h"

#include "Quest.h"

void UTriggerVolume_QuestCondition::StartCondition()
{
	AQuest* Quest =Cast<AQuest>(GetOuter());
	Quest->OnActorBeginOverlap.AddDynamic(this, &UTriggerVolume_QuestCondition::StartOverlap);
}

void UTriggerVolume_QuestCondition::StopCondition()
{

}

void UTriggerVolume_QuestCondition::StartOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogQuest, Log, TEXT("Quest Condition Overlaped with actor %s with has tag %s"), *OtherActor->GetName(),
		OtherActor->ActorHasTag(OtherTag)? TEXT("has tag") : TEXT("no tag"));
	AQuest* Quest =Cast<AQuest>(GetOuter());
	FVector Center;
    FVector Extents;
    Quest->GetActorBounds(true, Center, Extents, false);
	UE_VLOG_BOX(Quest, LogQuest, Error, FBox(Center - Extents, Center + Extents), FColor::Orange, TEXT(""));
    if (OtherActor->ActorHasTag(OtherTag))
    {
    	Complete();
    }
	
	
}
