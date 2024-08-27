#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SandboxPlayerController.generated.h"

UCLASS()
class GEOMETRYSANDBOX_API ASandboxPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UFUNCTION()
	void ChangePawn();

private:
	int32 PawnIndex = 0;
};
