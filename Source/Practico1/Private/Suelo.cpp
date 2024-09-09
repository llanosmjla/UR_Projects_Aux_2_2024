// Fill out your copyright notice in the Description page of Project Settings.


#include "Suelo.h"

// Sets default values
ASuelo::ASuelo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//creamos una mesh para el actor
	SueloMesh = CreateDefaultSubobject<UStaticMeshComponent>("SueloMesh");
	//asignamos el mesh a la raiz del actor
	SueloMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	//creamos una esfera para el mesh
	auto MeshCube = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	//Textura
	auto Material = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Game/Geometry/Meshes/Cube/Tierra/TierraMaterial.TierraMaterial'"));
	//si la esfera se encuentra
	if (MeshCube.Succeeded())
	{
		//asignamos la esfera al mesh
		SueloMesh->SetStaticMesh(MeshCube.Object); 
		//asignamos la textura al mesh
		SueloMesh->SetMaterial(0, Material.Object);
	}

}

// Called when the game starts or when spawned
void ASuelo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASuelo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

