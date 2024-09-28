// Fill out your copyright notice in the Description page of Project Settings.


#include "Bloque.h"

// Sets default values
ABloque::ABloque()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//inicializamos variables de movimiento 
	isMoving = false;
	wasPressed = false;

	distance = 400.f;
	FinalPosition = FVector(0, 0, 0);
	//this->c.X += this->Distance; //{100, 0, 0}
	//Mostrar coordenadas en pantalla de la posicion inicial
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Black, FString::Printf(TEXT("Posicion inicial Game : X=%f, Y=%f, Z=%f"), c.X, c.Y, c.Z));
	pressCount = 0;
	flat = 1;
	//Inicializar el componente de la malla estatica, crear el componente de la malla estatica
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));

	//Establacer MeshComponent como la raiz del actor
	RootComponent = MeshComponent;

	//Buscar con FObjectFinder el cubo, esfera, cilindro y cono
	//auto MeshCuboObject = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	auto MeshEsferaObject = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	auto MeshCilindroObject = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'"));
	auto MeshConoObject = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone'"));


	//Si se encuentra la malla asignar cada malla a su respectiva variable de malla
	/*if (MeshCuboObject.Succeeded())
	{
		MeshCubo = MeshCuboObject.Object;
		//MeshCubo = ObtenerForma("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'");
	}*/
	if (MeshEsferaObject.Succeeded())
	{
		MeshEsfera = MeshEsferaObject.Object;//obtiene la esfera
	}
	if (MeshCilindroObject.Succeeded())
	{
		MeshCilindro = MeshCilindroObject.Object;
	}
	if (MeshConoObject.Succeeded())
	{
		MeshCono = MeshConoObject.Object;
	}

}

// Called when the game starts or when spawned
void ABloque::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ABloque::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CambiarForma();
	CambiarFormaPorTeclado();
	MoverObjetoPorTeclado(DeltaTime);
	/*if (GEngine) {
		FString DeltaTimeString = FString::Printf(TEXT("DeltaTime: %f"), DeltaTime);
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, DeltaTimeString);
	}*/


}

void ABloque::CambiarForma()
{
	//Dependiendo del tipo de bloque asignar la malla correspondiente
	switch (TipoBloque)
	{
	case 1:
		if (ObtenerForma("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'") != nullptr) {
			MeshComponent->SetStaticMesh(ObtenerForma("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Error al cargar la malla"));
		}
		break;
	case 2:
		if (ObtenerForma("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'") != nullptr) {
			MeshComponent->SetStaticMesh(ObtenerForma("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Error al cargar la malla"));
		}
		break;
	case 3:
		if (ObtenerForma("StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'") != nullptr) {
			MeshComponent->SetStaticMesh(ObtenerForma("StaticMesh'/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder'"));
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Error al cargar la malla"));
		}
		break;
	case 4:
		if (ObtenerForma("StaticMesh'/Game/StarterContent/Shapes/Shape_Cone.Shape_Cone'") != nullptr) {
			MeshComponent->SetStaticMesh(ObtenerForma("StaticMesh'/Game/StarterContent/Shapes/Shape_Cone.Shape_Con'"));
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Error al cargar la malla"));
		}
		break;
	default:
		//Mostrar un mensaje de error
		
		break;
	}
}

void ABloque::CambiarFormaPorTeclado() {
	//Verificamos si el jugador presiona una tecla para cambiar el tipo de bloque 
	//IsInputKeyDown verifica si la tecla esta siendo presionada
	//WasInputKeyJustPressed verifica si la tecla fue presionada
	//EKeys indica las teclas que se pueden utilizar
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::One)) {
		TipoBloque = 1;
	}
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::Two)) {
		TipoBloque = 2;
	}
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::Three)) {
		TipoBloque = 3;
	}
	if (GetWorld()->GetFirstPlayerController()->IsInputKeyDown(EKeys::Four)) {
		TipoBloque = 4;
	}
}

UStaticMesh* ABloque::ObtenerForma(FString RefObject) {
	return StaticCast<UStaticMesh*>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, *RefObject));
	/*if (MeshObject1 != nullptr) {
		return MeshObject1;
	}
	return nullptr;*/
}

void ABloque::MoverObjetoPorTeclado(float DeltaTime) {
	FVector CurrentPosition = GetActorLocation();
	
	
	//imprimir valor 
	/*if (counter == 0) {
	
		if(GEngine) GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Black, FString::Printf(TEXT("Posicion C : X=%f, Y=%f, Z=%f"), c.X, c.Y, c.Z));
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Black, FString::Printf(TEXT("Posicion Start : X=%f, Y=%f, Z=%f"), PosicionInicial.X, PosicionInicial.Y, PosicionInicial.Z));
		counter = 1;
	}*/
	//Verificar si la tecla fue presionada
	this->wasPressed = GetWorld()->GetFirstPlayerController()->WasInputKeyJustPressed(EKeys::NumPadOne);
	if (wasPressed) {
		if (pressCount == 0) {
			FinalPosition.X = CurrentPosition.X + distance;
		}
		pressCount++;
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Magenta, FString::Printf(TEXT("Veces presionadas : %d"), pressCount));
		//FinalPosition.X = CurrentPosition.X + distance;
		//contador++;
		//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Blue, FString::Printf(TEXT("Posicion actual C : X=%f"), c.X));
		//PosicionInicial += GetActorForwardVector()*55*DeltaTime;
		//SetActorLocation(PosicionInicial);
		
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Black, FString::Printf(TEXT("Posicion Start : X=%f, Y=%f, Z=%f"), CurrentPosition.X, CurrentPosition.Y, CurrentPosition.Z));
		isMoving = true;
	}

	if (isMoving) {
		
		CurrentPosition += GetActorForwardVector() * (55*flat) * DeltaTime;
		
		if (CurrentPosition.X >= FinalPosition.X) {
			if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Red, FString::Printf(TEXT("Posicion Final : X=%f, Y=%f, Z=%f"), CurrentPosition.X, CurrentPosition.Y, CurrentPosition.Z));
			flat = -1;
		}
		
		if (CurrentPosition.X <= FinalPosition.X - distance) {
			if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Green, FString::Printf(TEXT("Posicion Inicial : X=%f, Y=%f, Z=%f"), CurrentPosition.X, CurrentPosition.Y, CurrentPosition.Z));
			flat = 1;
		}
		SetActorLocation(CurrentPosition);
	}
	/*else {
		PosicionInicial -= GetActorForwardVector() * 55 * DeltaTime;
		SetActorLocation(PosicionInicial);
		if (PosicionInicial.X <= c.X - Distance) {
			isMove = true;
		}
	}*/
	
}


