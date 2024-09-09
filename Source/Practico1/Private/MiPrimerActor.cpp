// Fill out your copyright notice in the Description page of Project Settings.


#include "MiPrimerActor.h"

// Sets default values
AMiPrimerActor::AMiPrimerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//creamos una mesh para el actor
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp2"));
	//asignamos el mesh a la raiz del actor
	RootComponent = MeshComp;
	//asignamos el mesh comp2 a la raiz del actor
	MeshComp2->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//Posicion del mesh comp
	MeshComp->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	//Rotacion del mesh comp 2
	MeshComp2->SetRelativeLocation(FVector(200.0f, 10.0f, 0.0f));

	//creamos una esfera para el mesh
	auto MeshSphere = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	auto MeshCube = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

	//Textura
	auto Material = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Game/Geometry/Meshes/Cube/MaterialLadrillo.MaterialLadrillo'"));

	//si la esfera se encuentra
	if (MeshSphere.Succeeded() && MeshCube.Succeeded())
	{
		//asignamos la esfera al mesh
		MeshComp->SetStaticMesh(MeshSphere.Object);
		MeshComp2->SetStaticMesh(MeshCube.Object);
		//asignamos la textura al mesh
		MeshComp->SetMaterial(0, Material.Object);
	}

}

// Called when the game starts or when spawned
void AMiPrimerActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMiPrimerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

