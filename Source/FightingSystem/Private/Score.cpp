#include "Score.h"
#include <BP_BuffTrackerComponent.h>

UScore::UScore()
{
	Name = FText::FromString("Score");
	Description = FText::FromString("Adds the item to equipment; + 1 ");
}

void UScore::Apply_Implementation(AActor* Target)
{
    if (Target)
    {
        UBuffTrackerComponent* Tracker = Target->FindComponentByClass<UBuffTrackerComponent>();
        if (Tracker)
        {
            Tracker->AddScore(point);
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, TEXT("Zebrano punkty!!"));
            }

            UE_LOG(LogTemp, Warning, TEXT("Zebrano punkty! Nowy wynik: %d"), Tracker->TotalScore);
        }
        else
        {
            if (GEngine)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Brakuje Buff Tracker Component!!"));
            }
        }
    }
}
