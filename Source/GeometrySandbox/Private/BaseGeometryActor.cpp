#include "BaseGeometryActor.h"

#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(BaseGeomentyActor, All, All)

ABaseGeometryActor::ABaseGeometryActor()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(BaseMesh);
}

void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetActorLocation();
	//PrintTypes();
	
	SetMaterialColor(GeometryData.LinearColor);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ThisClass::OnColorTimerFired, GeometryData.ColorTimerRate, true);
}

void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleMovement();
}

void ABaseGeometryActor::HandleMovement()
{
	switch (GeometryData.MovementType)
	{
	case EMovementType::Static:
		break;
	case EMovementType::Sin:
	{
		// z = z0 + amplitude * sin(freq * t)
		FVector ActorLocation = GetActorLocation();
		ActorLocation.Z = InitialLocation.Z + GeometryData.Amplitude * FMath::Sin(GeometryData.Frequency * GetWorld()->GetTimeSeconds());
		SetActorLocation(ActorLocation);
	}
	break;
	default:
		break;
	}
}

void ABaseGeometryActor::PrintTypes()
{
	FString WeaponsCountString = "Weapons count: " + FString::FromInt(WeaponsCount);
	FString HealthString = "Health: " + FString::SanitizeFloat(Health);
	FString IsDeadString = "Is dead: " + FString(IsDead ? "true" : "false");

	FString InfoString = FString::Printf(TEXT("\n === All info === \n%s\n%s\n%s"), *WeaponsCountString, *HealthString, *IsDeadString);

	UE_LOG(BaseGeomentyActor, Display, TEXT("%s"), *InfoString);

	FString CharacterName = "Mr.Boombastic!";

	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, CharacterName);
	}
}

void ABaseGeometryActor::SetMaterialColor(const FLinearColor& LinearColor)
{
	if (!BaseMesh)
	{
		UE_LOG(BaseGeomentyActor, Warning, TEXT("BaseMesh is nullptr"));
	}
	else if (UMaterialInstanceDynamic* BaseDynamicColor = BaseMesh->CreateAndSetMaterialInstanceDynamic(0))
	{
		BaseDynamicColor->SetVectorParameterValue("Color", LinearColor);
	}
}

void ABaseGeometryActor::OnColorTimerFired()
{
	if (++CountColorTimer <= GeometryData.MaxCountColorTimerRateCount)
	{
		UE_LOG(BaseGeomentyActor, Display, TEXT("%f"), GeometryData.ColorTimerRate);

		const FLinearColor LinearColor = FLinearColor::MakeRandomColor();
		SetMaterialColor(LinearColor);

		OnColorChanged.Broadcast(LinearColor, GetName());
	}
	else
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		OnTimerFinished.Broadcast(this);
	}
}

FString FGeometryData::MovementTypeToString(const EMovementType& Type) const
{
	switch (Type)
	{
	case EMovementType::Static:
		return "Static";
	case EMovementType::Sin:
		return "Sin";
	default:
		UE_LOG(BaseGeomentyActor, Error, TEXT("Add case for this MovementType"));
		return "undefined";
	}
}

FString FGeometryData::ToString() const
{
	return FString::Printf(TEXT("\n\t%s\n\t%f\n\t%f\n\t%s\n\t%f\n\t%d"), *MovementTypeToString(MovementType), Amplitude, Frequency, *LinearColor.ToString(), ColorTimerRate, MaxCountColorTimerRateCount);
}
