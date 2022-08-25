// Fill out your copyright notice in the Description page of Project Settings.


#include "SphereDestroyerGameInstance.h"
#include "Target.h"
#include "SphereDestroyerCharacter.h"

#include "Kismet/GameplayStatics.h" 

void USphereDestroyerGameInstance::SpawnTargets(const ASphereDestroyerCharacter* Player)
{
	UWorld* World = GetWorld();
	if (!ensure(World)) return;
	
	float Distance = BeginSpawnRadius + ((BeginSpawnRadius * SpawnRadiusIncreaseByPercentage) / 100) * CurrentRound;
	int Amount = TargetAmount + ((TargetAmount * TargetsAmountIncreaseByPercentage) / 100) * CurrentRound;
	float SizeDecreaseBy = TargetsSizeDecreaseByValue * CurrentRound;

	FActorSpawnParameters Param = FActorSpawnParameters();
	
	TargetsToWinAlive = TargetsToWin;

	TArray<FVector> SpawnPoints;

	for (int i{ 0 }; i < Amount; i++)
	{
		float SpawnDistance;
		bool NeededForWin;
		if (i < TargetsToWin)
		{
			SpawnDistance = WiningRadius;
			NeededForWin = true;
		}
		else
		{
			SpawnDistance = Distance;
			NeededForWin = false;
		}

		FVector NewLocation = CreateSpawnLocation(SpawnDistance, Player);
		if (i != 0)
		{
			while (!AreSpacedCorrectly(SpawnPoints, NewLocation))
			{
				NewLocation = CreateSpawnLocation(SpawnDistance, Player);
			}
			
		}
		SpawnPoints.Add(NewLocation);
		ATarget* Target = World->SpawnActor<ATarget>(TargetClass, NewLocation, FRotator(0, 0, 0), Param);
		Target->SetNeededForWin(NeededForWin);
		Target->DecreaseSizeBy(SizeDecreaseBy);
	}
}

FVector USphereDestroyerGameInstance::CreateSpawnLocation(float Distance, const ASphereDestroyerCharacter* Player)
{
	FTransform PlayerTransform = Player->GetTransform();
	FVector NewLocation = FVector(PlayerTransform.GetLocation().X + FMath::RandRange(0.0f, Distance), PlayerTransform.GetLocation().Y, PlayerTransform.GetLocation().Z + FMath::RandRange(TargetSpawnMinHight, TargetSpawnMaxHight));
	FRotator Rot = FRotator(0, FMath::RandRange(0.0f, 360.0f), 0);
	return Rot.RotateVector(NewLocation);
}

bool USphereDestroyerGameInstance::AreSpacedCorrectly(const TArray<FVector>& SpawnPoints, const FVector& CreatedPoint)
{
	for (const FVector& Point : SpawnPoints)
	{
		if ((Point - CreatedPoint).Size() < DistanceBetweenTargets) return false;
	}
	return true;
}

void USphereDestroyerGameInstance::OnTargetsForWinDestroy()
{
	UWorld* World = GetWorld();
	if (!ensure(World)) return;

	TArray<AActor*> FoundTargets;
	UGameplayStatics::GetAllActorsOfClass(World, TargetClass, FoundTargets);

	if (FoundTargets.Num() > 0)
	{
		for (AActor* Actor : FoundTargets)
		{
			ATarget* Target = Cast<ATarget>(Actor);
			if (Target != nullptr) Target->Destroy();
		}
	}
}

void USphereDestroyerGameInstance::StartNewRound(const ASphereDestroyerCharacter* Player)
{
	if (CurrentRound < AmountOfRounds)
	{
		SpawnTargets(Player);
		++CurrentRound;
	}
	else bIsGameFinished = true;
}

void USphereDestroyerGameInstance::StartGame(const ASphereDestroyerCharacter* Player)
{
	this->SpawnTargets(Player);
	++CurrentRound;
}