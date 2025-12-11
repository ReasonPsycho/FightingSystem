// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuffEffect.generated.h"

UCLASS()
class FIGHTINGSYSTEM_API UBuffEffect : public UObject
{
    GENERATED_BODY()

public:
    //UBuffEffect(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
     FText Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Buff")
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
    UStaticMesh* PickupMesh;

    UFUNCTION(BlueprintNativeEvent, Category = "Buff")
    void Apply(AActor* Target);

    virtual void Apply_Implementation(AActor* Target);
};
