


#include "BuffSpeed.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


UBuffSpeed::UBuffSpeed()
{
    Name = FText::FromString("Speed Buff");
    Description = FText::FromString("Increases movement speed by a multiplier.");
}

void UBuffSpeed::Apply_Implementation(AActor* Target)
{
    if (!Target) return;

    ACharacter* Character = Cast<ACharacter>(Target);
    if (Character && Character->GetCharacterMovement())
    {
        float DefaultSpeed = Character->GetCharacterMovement()->MaxWalkSpeed;
        Character->GetCharacterMovement()->MaxWalkSpeed = DefaultSpeed * SpeedMultiplier;

        // Debug message
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Speed buff applied!"));
        }
    }
}
