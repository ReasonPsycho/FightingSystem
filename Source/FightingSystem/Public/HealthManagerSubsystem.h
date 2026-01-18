// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "HealthManagerSubsystem.generated.h"

class UHealthComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGlobalDeathSignature, FVector, DeathLocation);

UCLASS()
class FIGHTINGSYSTEM_API UHealthManagerSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:
    // --- The Global API ---

    // Called by HealthComponent on BeginPlay
    void RegisterComponent(UHealthComponent* Comp);

    // Called by HealthComponent on EndPlay (cleanup)
    void UnregisterComponent(UHealthComponent* Comp);

    // Called by HealthComponent when it actually dies
    void ReportDeath(UHealthComponent* Comp);

    // The Event everyone subscribes to (ItemDrop, Score, UI)
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnGlobalDeathSignature OnActorDied;

protected:
    // The collection of active components
    UPROPERTY(Transient)
    TArray<TObjectPtr<UHealthComponent>> ActiveHealthComponents;
};
