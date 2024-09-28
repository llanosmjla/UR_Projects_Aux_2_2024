// Fill out your copyright notice in the Description page of Project Settings.


#include "MiPrimerActor.h"

// Sets default values
AMiPrimerActor::AMiPrimerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//creamos un escene component para el actor raiz y otro hijo
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	SceneComp2 = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp2"));

	//creamos una mesh para el actor
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp2"));


	//creamos una esfera para el mesh
	auto MeshObject = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	auto MeshObject2 = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone'"));

	//Textura
	auto Material = ConstructorHelpers::FObjectFinder<UMaterial>(TEXT("Material'/Game/Geometry/Meshes/Cube/MaterialLadrillo.MaterialLadrillo'"));

	//si la esfera se encuentra
	if (MeshObject.Succeeded() && MeshObject2.Succeeded() && Material.Succeeded())
	{
		//asignamos la esfera al mesh
		MeshComp->SetStaticMesh(MeshObject.Object);
		MeshComp2->SetStaticMesh(MeshObject2.Object);
		//asignamos la textura al mesh
		MeshComp->SetMaterial(0, Material.Object);
		MeshComp2->SetMaterial(0, Material.Object);
	}

	//establecemos las relaciones de los componentes y de los mesh
	RootComponent = SceneComp; //el SceneComp es la raiz osea el contenedor principal
	//Asigamos a ScenceComp su mesh
	MeshComp->AttachToComponent(SceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	//Asigamos a ScenceComp2 su mesh
	MeshComp2->AttachToComponent(SceneComp2, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	//Asignamos SceneComp2 como hijo de SceneComp
	SceneComp2->AttachToComponent(SceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	//establecemos la posicion de SceneComp2
	//SceneComp2->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));// establece la posicion de SceneComp2 con respecto a SceneComp que esta basicamente por encima de SceneComp

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
	CambiarPosicionDelHijoRespectoAlPadre();
}

/*void AMiPrimerActor::MoverObjecto() {

	if (GetWorld()->GetFirstPlayerController()->EKeys::One)) {
		FVector PosicionPadre = SceneComp->GetComponentLocation(); // obtener su posicion
		PosicionPadre.Z += 100.0f; //arriba
	}
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::Two)) {
		FVector PosicionPadre = SceneComp->GetComponentLocation(); // obtener su posicion
		PosicionPadre.X += 100.0f; //arriba
	}
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::Two)) {
		FVector PosicionPadre = SceneComp->GetComponentLocation(); // obtener su posicion
		PosicionPadre.Y += 100.0f; //arriba
	}
}*/

void AMiPrimerActor::CambiarPosicionDelHijoRespectoAlPadre() {
	//Obtenemos la posicion del padre
	FVector PosicionPadre = SceneComp->GetComponentLocation();
	PosicionPadre.Z += 100.0f;
	//Obtenemos la posicion del hijo
	FVector PosicionHijo = SceneComp2->GetComponentLocation();
	//Calculamos la distancia entre el padre y el hijo
	//float Distancia = FVector::Dist(PosicionPadre, PosicionHijo);
	//Imprimimos la distancia
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Distancia: %f"), Distancia));

	//Movemos el hijo al rededor del padre cada en un radio de 100 unidades
	FRotator Rotacion = SceneComp2->GetComponentRotation();
	Rotacion.Yaw += 1.0f; // hara que el hijo gire en el eje Y

	//Calculamos la nueva posicion del hijo basado en la rotacion
	//Convertir la rotacion a un vector de direccion
	FVector Direccion = FRotationMatrix(Rotacion).GetScaledAxis(EAxis::X);

	//Radio de la orbita del hijo alrededor del padre
	float Radio = 100.0f;

	//Calculamos la nueva posicion del hijo
	FVector NuevaPosicionHijo = PosicionPadre + Direccion * Radio;

	SceneComp2->SetWorldRotation(Rotacion);
	SceneComp2->SetWorldLocation(NuevaPosicionHijo);



}

