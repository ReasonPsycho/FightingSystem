#include "WaterVisibilityController.h"
#include "Kismet/GameplayStatics.h"

UWaterVisibilityController::UWaterVisibilityController()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UWaterVisibilityController::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(),
		WaterTag,
		WaterActors
	);
}


void UWaterVisibilityController::TickComponent(
	float DeltaTime,
	ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction
)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PlayerPawn) return;

	for (AActor* Water : WaterActors)
	{
		if (!Water) continue;

		const float Distance = FVector::Dist(
			PlayerPawn->GetActorLocation(),
			Water->GetActorLocation()
		);

		const bool bPlayerNear = Distance <= ActivationDistance;

		Water->SetActorHiddenInGame(!bPlayerNear);
		Water->SetActorEnableCollision(bPlayerNear);
	}
}
