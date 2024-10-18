// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxLightExample.h"
#include "GameFramework/Actor.h"
#include "Bloque.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UBoxLightExample::UBoxLightExample()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	colisionesWithLight = TArray<int>();

	// ...
}


// Called when the game starts
void UBoxLightExample::BeginPlay()
{
	Super::BeginPlay();

	boxLightTrigger = GetOwner(); // Get the owner of this component

	//
	DrawDebugBox(GetWorld(), boxLightTrigger->GetActorLocation(), boxLightTrigger->GetActorScale()*100, FColor::Purple, true, duration, 0, lineThickness);

	//Bind the functions to the triggers events (overlap begin and end)
	boxLightTrigger->OnActorBeginOverlap.AddDynamic(this, &UBoxLightExample::OnOverlapBegin);
	boxLightTrigger->OnActorEndOverlap.AddDynamic(this, &UBoxLightExample::OnOverlapEnd);

	light = boxLightTrigger->FindComponentByClass<UPointLightComponent>();
	if (!light)
	{
		UE_LOG(LogTemp, Error, TEXT("No light component found"));
	}
	light->SetVisibility(false);
	
	
}


// Called every frame
void UBoxLightExample::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ShowColisionesWithLight();

	// ...
}

//Function overlap begin
void UBoxLightExample::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (OtherActor && (OtherActor != boxLightTrigger))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
		}
		contadorColisiones++;
		colisionesWithLight.Add(contadorColisiones);

		light->SetVisibility(true);

		GenerateBlocks();
		
	}
	
	//UE_LOG(LogTemp, Warning, TEXT("Overlap Begin"));
}

//Function overlap end
void UBoxLightExample::OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Overlap End"));
	}

	light->SetVisibility(false);

	UE_LOG(LogTemp, Warning, TEXT("Overlap End"));
}


void UBoxLightExample::GenerateBlocks()
{
	//Get the world
	UWorld* world = GetWorld();

	//Check if the world is valid
	if (world)
	{
		if (blocks.Num() > 0)
		{
			//Destroy the blocks

			for (ABloque* block : blocks)
			{
				block->Destroy();
			}

			//Clear the array
			blocks.Empty();
		}
		//Create a random number of blocks
		int32 numberOfBlocks = FMath::RandRange(1, 5);

		//Create the blocks
		for (int32 i = 0; i < numberOfBlocks; i++)
		{
			//Create a random location
			//FVector location = boxLightTrigger->GetActorLocation() + FVector(FMath::RandRange(-1000, 1000), FMath::RandRange(-1000, 1000), 100);
			FVector location = boxLightTrigger->GetActorLocation() + FVector(i * 200.0f, 0.0f, 0.0f);

			//Create a random rotation
			FRotator rotation = FRotator::ZeroRotator;

			//Spawn the block
			ABloque* block = world->SpawnActor<ABloque>(ABloque::StaticClass(), location, rotation);

			//Add the block to the array
			blocks.Add(block);
		}
	}
}

void UBoxLightExample::ShowColisionesWithLight()
{
	if (GetWorld()->GetFirstPlayerController()->WasInputKeyJustPressed(EKeys::Q)){
		if (GEngine)
		{
			for (int i = 0; i < colisionesWithLight.Num(); i++)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Colisiones con la luz: %d"), colisionesWithLight[i]));
			}
		}

	}
}
