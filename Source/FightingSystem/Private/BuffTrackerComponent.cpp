


#include "BuffTrackerComponent.h"
#include <HealthManagerSubsystem.h>


// Sets default values for this component's properties
UBuffTrackerComponent::UBuffTrackerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UBuffTrackerComponent::HandleGlobalDeath(FVector DeathLocation)
{
    // 3. Sprawdzenie czy event siê wywo³a³ (Log i wiadomoœæ na ekranie)
    UE_LOG(LogTemp, Error, TEXT("EVENT WYWO£ANY! Aktor umarl na pozycji: %s"), *DeathLocation.ToString());

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MANAGER: Ktoœ zgin¹³! Spawnowanie obiektu..."));
    }

    // 1. Sprawdzamy, czy mamy ustawion¹ klasê buffa
    if (!_buffClass)
    {
		UE_LOG(LogTemp, Warning, TEXT("BuffTracker: BuffClass nie jest ustawiona! Nie mo¿na zspawnowaæ przedmiotu."));

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Buff Tracker Component: Ustaw BuffClass w komponencie w BP gracza"));
        }
        return;
    }

    // 2. Pobieramy World Timer Manager
    FTimerHandle TimerHandle;
    FTimerDelegate TimerDel;

    // 3. Bindujemy funkcjê z parametrem (lokalizacj¹)
    TimerDel.BindUObject(this, &UBuffTrackerComponent::SpawnDelayedPickup, DeathLocation);

    // 4. Ustawiamy timer na 2 sekundy, bez powtarzania (false)
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDel, 2.0f, false);

    UE_LOG(LogTemp, Warning, TEXT("Przeciwnik zgin¹³. Pickup pojawi siê za 2 sekundy..."));
}


// Called when the game starts
void UBuffTrackerComponent::BeginPlay()
{
    Super::BeginPlay();

    UHealthManagerSubsystem* HealthSubsystem = GetWorld()->GetSubsystem<UHealthManagerSubsystem>();

    if (HealthSubsystem)
    {
        HealthSubsystem->OnActorDied.AddDynamic(this, &UBuffTrackerComponent::HandleGlobalDeath);

        UE_LOG(LogTemp, Warning, TEXT("BuffTracker: Pomyœlnie zasubskrybowano do HealthSubsystem!"));
    }
}


// Called every frame
void UBuffTrackerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBuffTrackerComponent::SpawnDelayedPickup(FVector SpawnLocation)
{
    if (GetWorld() && _buffClass)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        GetWorld()->SpawnActor<ABuffPickup>(_buffClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);

        UE_LOG(LogTemp, Log, TEXT("Pickup zrodzony po opóŸnieniu!"));

        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("BUFF MANAGER: Nowy buff na mapie!"));
        }
    }
}

void UBuffTrackerComponent::ApplyBuff(TSubclassOf<UBuffEffect> BuffClass)
{
    if (!BuffClass) return;

    UBuffEffect* NewBuff = NewObject<UBuffEffect>(this, BuffClass);

    if (NewBuff)
    {
        //NewBuff->Apply(GetOwner());
		NewBuff->Apply_Implementation(GetOwner());

        FActiveBuffData NewData;
        NewData.BuffEffect = NewBuff;
        NewData.Duration = NewBuff->Duration;

        ActiveBuffs.Add(NewData);
    }
}

void UBuffTrackerComponent::AddScoreDetailed(TSubclassOf<UScore> ScoreClass, int32 Points)
{
    if (ScoreClass)
    {
        TotalScore += Points;
        CollectedScores.FindOrAdd(ScoreClass) += 1;
    }
}
