#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SandboxPawn.generated.h"

class UCameraComponent;

UCLASS()
class GEOMETRYSANDBOX_API ASandboxPawn : public APawn
{
	GENERATED_BODY()

public:
	ASandboxPawn();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;

private:
	void MoveForward(float Amount);
	void MoveRight(float Amount);

private:
	FVector VelocityVector = FVector::ZeroVector;

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere)
	float Velocity = 300.f;
};
