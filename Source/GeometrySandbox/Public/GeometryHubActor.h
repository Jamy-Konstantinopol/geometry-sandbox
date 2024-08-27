#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.h"
#include "GeometryHubActor.generated.h"

USTRUCT()
struct FGeometryPayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = SpawnSettings)
	TSubclassOf<ABaseGeometryActor> GeometryClass;

	UPROPERTY(EditAnywhere, Category = SpawnSettings)
	FGeometryData GeometryData;

	UPROPERTY(EditAnywhere, Category = SpawnSettings)
	FTransform InitialTransform;
};

UCLASS()
class GEOMETRYSANDBOX_API AGeometryHubActor : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	void SpawnGeometryArray(TArray<FGeometryPayload> GeometryPayloadsToSpawn);
	void OnTimerFinished(AActor* Actor);

	UFUNCTION()
	void OnColorChanged(const FLinearColor& LinearColor, const FString& Name);

protected:
	UPROPERTY(EditAnywhere, Category = SpawnSettings)
	TArray<FGeometryPayload> GeometryPayloads;

	UPROPERTY(EditAnywhere, Category = SpawnSettings)
	int32 GeometryClassCount;
};
