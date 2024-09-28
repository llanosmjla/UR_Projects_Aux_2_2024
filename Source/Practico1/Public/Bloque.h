// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Bloque.generated.h"

UCLASS()
class PRACTICO1_API ABloque : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABloque();

	// Una propiedad para el tipo de bloque	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Configuracion Bloque")
	int32 TipoBloque;

	//CREAR USTATICMESH PARA OBTENER LA FORMA DE LA MALLA PARA EL BLOQUE
	//UStaticMesh* MeshCubo;
	UStaticMesh* MeshEsfera;
	UStaticMesh* MeshCilindro;
	UStaticMesh* MeshCono;
	UStaticMesh* MeshObject;

	UStaticMesh* ObtenerForma(FString Ref);

	FVector FinalPosition;
	
	bool isMoving;
	bool wasPressed;
	float distance;
	int pressCount; //contador de veces que se presiona la tecla
	int flat; //variable para saber si se mueve hacia adelante o hacia atras
	float speed; //velocidad de movimiento


	//CREAR UPROPERTY PARA EL COMPONENTE DE LA MALLA ESTATICA
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componentes")
	UStaticMeshComponent* MeshComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void CambiarForma();
	void CambiarFormaPorTeclado(); //
	void MoverObjetoPorTeclado(float);
	void Acelerar(float); // si desean cambair el tipo de retorno de la funcion, pueden hacerlo
	void Desacelerar(float); // si desean cambair el tipo de retorno de la funcion, pueden hacerlo
	void CambiarDistancia(float); // si desean cambair el tipo de retorno de la funcion, pueden hacerlo
	
	
	//tipo de retorno * nonbre la funcion (parametros)
};
