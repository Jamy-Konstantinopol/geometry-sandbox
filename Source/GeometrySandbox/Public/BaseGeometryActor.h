#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.generated.h"

class UStaticMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnColorChanged, const FLinearColor&, Color, const FString&, Name);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerFinished, AActor*);

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	Static,
	Sin
};

USTRUCT(BlueprintType)
struct FGeometryData
{
	GENERATED_USTRUCT_BODY()

public:
	FString MovementTypeToString(const EMovementType& Type) const;
	FString ToString() const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	EMovementType MovementType = EMovementType::Static;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	double Amplitude = 0.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	double Frequency = 0.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Design)
	FLinearColor LinearColor = FLinearColor::Black;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Design)
	float ColorTimerRate = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Design)
	int32 MaxCountColorTimerRateCount = 0;
};

UCLASS()
class GEOMETRYSANDBOX_API ABaseGeometryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseGeometryActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	void HandleMovement();
	void PrintTypes();
	void SetMaterialColor(const FLinearColor& LinearColor);
	void OnColorTimerFired();

public:
	void SetGeometryData(const FGeometryData& NewGeometryData) { GeometryData = NewGeometryData; }
	FGeometryData GetGeomertyData() const { return GeometryData; }

private:
	FVector InitialLocation;
	FTimerHandle TimerHandle;
	int32 CountColorTimer = 0;

protected:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GeometryData)
	FGeometryData GeometryData;

	UPROPERTY(EditAnywhere, Category = Weapon)
	int32 WeaponsCount = 0;

	UPROPERTY(EditAnywhere, Category = Health)
	float Health = 0.f;

	UPROPERTY(EditAnywhere, Category = Health)
	bool IsDead = false;

public:
	UPROPERTY(BlueprintAssignable)
	FOnColorChanged OnColorChanged;

	FOnTimerFinished OnTimerFinished;
};
