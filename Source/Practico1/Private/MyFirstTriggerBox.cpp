// Fill out your copyright notice in the Description page of Project Settings.


#include "MyFirstTriggerBox.h"


AMyFirstTriggerBox::AMyFirstTriggerBox()
{
	//Initialize Point Light
	PointLight = nullptr;

	//Register Events
	OnActorBeginOverlap.AddDynamic(this, &AMyFirstTriggerBox::OnOverlapBegin);
	OnActorEndOverlap.AddDynamic(this, &AMyFirstTriggerBox::OnOverlapEnd);
}

void AMyFirstTriggerBox::BeginPlay()
{
	Super::BeginPlay();
}

void AMyFirstTriggerBox::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{
		//Create a pointLight at the location of the other actor or near the trigger box
		FVector LightLocation = GetActorLocation() + FVector(0.f, 0.f, 100.f);

		if (PointLight)
		{
			PointLight = NewObject<UPointLightComponent>(this);
			PointLight->SetVisibility(true);
			PointLight->SetIntensity(5000.f);
			PointLight->SetLightColor(FLinearColor::Red);
			PointLight->SetWorldLocation(LightLocation);

			PointLight->RegisterComponent();
			PointLight->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		}
		
		// Display a debug message for a specified amount of time
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
	}
}

void AMyFirstTriggerBox::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != this))
	{
		//Destroy the light component
		if (PointLight)
		{
			PointLight->DestroyComponent();
			PointLight = nullptr;
		}

		// Display a debug message for a specified amount of time
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Overlap Ended"));
	}
}