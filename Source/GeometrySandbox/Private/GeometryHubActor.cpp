#include "GeometryHubActor.h"
#include "BaseGeometryActor.h"
#include "Engine/World.h"

DEFINE_LOG_CATEGORY_STATIC(GeometryHubActor, All, All)

void AGeometryHubActor::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnGeometryArray(GeometryPayloads);
}

void AGeometryHubActor::SpawnGeometryArray(TArray<FGeometryPayload> GeometryPayloadsToSpawn)
{
	if (!GetWorld())
	{
		UE_LOG(GeometryHubActor, Error, TEXT("GetWorld() is nullptr"));
		return;
	}
	
	for (const FGeometryPayload& GeometryPayload : GeometryPayloadsToSpawn)
	{
		if (ABaseGeometryActor* Actor = GetWorld()->SpawnActorDeferred<ABaseGeometryActor>(GeometryPayload.GeometryClass, GeometryPayload.InitialTransform))
		{
			Actor->SetGeometryData(GeometryPayload.GeometryData);

			Actor->OnColorChanged.AddDynamic(this, &ThisClass::OnColorChanged);
			Actor->OnTimerFinished.AddUObject(this, &ThisClass::OnTimerFinished);

			Actor->FinishSpawning(GeometryPayload.InitialTransform);
		}
	}
}

void AGeometryHubActor::OnColorChanged(const FLinearColor& LinearColor, const FString& Name)
{
	UE_LOG(GeometryHubActor, Display, TEXT("OnColorChanged"));
}

void AGeometryHubActor::OnTimerFinished(AActor* Actor)
{
	UE_LOG(GeometryHubActor, Display, TEXT("OnTimerFinished"));

	if (ABaseGeometryActor* GeomentyActor = Cast<ABaseGeometryActor>(Actor))
	{
		UE_LOG(GeometryHubActor, Display, TEXT("Actor is BaseGeometryActor: %s"), *GeomentyActor->GetGeomertyData().ToString());
	}
	else
	{
		UE_LOG(GeometryHubActor, Warning, TEXT("Actor is NOT BaseGeometryActor"));
	}
}
