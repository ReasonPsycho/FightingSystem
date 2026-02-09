#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BuffEffect.h"

#include "Score.generated.h"

UCLASS(Blueprintable)
class FIGHTINGSYSTEM_API UScore : public UBuffEffect
{

	GENERATED_BODY()

public:

	UScore();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Score")
	int point;

	virtual void Apply_Implementation(AActor* Target) override;
};
