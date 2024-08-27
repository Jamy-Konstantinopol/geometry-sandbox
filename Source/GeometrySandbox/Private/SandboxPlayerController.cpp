#include "SandboxPlayerController.h"

#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SandboxPawn.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(SandboxPlayerController, All, All)

void ASandboxPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ASandboxPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(InputComponent)
	{
		InputComponent->BindAction("ChangePawn", IE_Pressed, this, &ThisClass::ChangePawn);
	}
	else
	{
		UE_LOG(SandboxPlayerController, Error, TEXT("There is NO InputComponent!"));
	}
}

void ASandboxPlayerController::ChangePawn()
{
	TArray<AActor*> Pawns;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASandboxPawn::StaticClass(), Pawns);

	if (Pawns.Num() <= 1)
	{
		UE_LOG(SandboxPlayerController, Display, TEXT("Pawn was NOT changed!"));
		return;
	}

	ASandboxPawn* CurrentPawn = Cast<ASandboxPawn>(Pawns[PawnIndex]);
	PawnIndex = (PawnIndex + 1) % Pawns.Num();

	if (!CurrentPawn)
	{
		UE_LOG(SandboxPlayerController, Display, TEXT("Pawn was NOT changed!"));
		return;
	}

	Possess(CurrentPawn);
	
	UE_LOG(SandboxPlayerController, Display, TEXT("Pawn was changed!"));
}
