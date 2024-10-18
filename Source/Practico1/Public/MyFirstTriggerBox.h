// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "Components/PointLightComponent.h"
#include "MyFirstTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class PRACTICO1_API AMyFirstTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	AMyFirstTriggerBox();

	//Create a function to call when the overlap occurs
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	//Create a function for when ending the overlap
	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

	//Add light component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light")
	UPointLightComponent* PointLight;
	

};
