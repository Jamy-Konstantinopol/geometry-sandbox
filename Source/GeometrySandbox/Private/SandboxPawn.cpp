#include "SandboxPawn.h"

#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"

DEFINE_LOG_CATEGORY_STATIC(SandboxPawn, All, All)

ASandboxPawn::ASandboxPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetupAttachment(SceneComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SceneComponent);
}

void ASandboxPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ASandboxPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis("MoveForward", this, &ThisClass::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &ThisClass::MoveRight);
	}
	else
	{
		UE_LOG(SandboxPawn, Error, TEXT("There is NO PlayerInputComponent!"));
	}
}

void ASandboxPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsControlled())
	{
		VelocityVector = FVector::ZeroVector;
	}

	if (!VelocityVector.IsZero())
	{
		const FVector NewLocation = GetActorLocation() + Velocity * DeltaTime * VelocityVector;
		SetActorLocation(NewLocation);
	}
}

void ASandboxPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	UE_LOG(SandboxPawn, Display, TEXT("PossessedBy() was called!"));
}

void ASandboxPawn::UnPossessed()
{
	Super::UnPossessed();

	UE_LOG(SandboxPawn, Display, TEXT("UnPossessed() was called!"));
}

void ASandboxPawn::MoveForward(float Amount)
{
	UE_LOG(SandboxPawn, Display, TEXT("Move forward amount: %f"), Amount);

	VelocityVector.X = Amount;
}

void ASandboxPawn::MoveRight(float Amount)
{
	UE_LOG(SandboxPawn, Display, TEXT("Move right amount: %f"), Amount);

	VelocityVector.Y = Amount;
}
