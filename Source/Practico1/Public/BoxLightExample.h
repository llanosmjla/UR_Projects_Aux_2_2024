// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/PointLightComponent.h"
#include <Bloque.h>
#include "BoxLightExample.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PRACTICO1_API UBoxLightExample : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBoxLightExample();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	AActor* boxLightTrigger = nullptr;

	//Function overlap begin
	UFUNCTION()
	void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
	//Function overlap end
	UFUNCTION()
	void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

	int lineThickness = 5;
	int duration = -1;

	UPointLightComponent* light = nullptr;

	//Array para guardar objetos de la clase bloque 
	TArray<ABloque*> blocks;

	//Array para guardar las veces que he colisionado con la luz 
	int contadorColisiones = 0;
	TArray<int> colisionesWithLight;

	//Funcion para generar bloques	
	void GenerateBlocks();

	//mostrar colisiones con luz 
	void ShowColisionesWithLight();

};
