// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MiPrimerActor.generated.h"

UCLASS()
class PRACTICO1_API AMiPrimerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMiPrimerActor();

	//Creamos un escene component para el actor con el cual se podra mover
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComp;

	//Otro escene component que actua como hijo del anterior osea del SceneComp
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComp2;


	//creamos una mesh statica para el actor
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp2;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void CambiarPosicionDelHijoRespectoAlPadre();

};
