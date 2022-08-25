// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SphereDestroyerGameInstance.generated.h"

class ATarget;

UCLASS()
class SPHEREDESTROYER_API USphereDestroyerGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void StartGame(const ASphereDestroyerCharacter* Player);

	UFUNCTION(BlueprintCallable)
		void SpawnTargets(const ASphereDestroyerCharacter* Player);
	
	UFUNCTION(BlueprintCallable)
		FVector CreateSpawnLocation(float Distance, const ASphereDestroyerCharacter* Player);

	// Checks if targets are spaced according to DistanceBetweenTargets. Returns true if so.
	UFUNCTION(BlueprintCallable)
		bool AreSpacedCorrectly(const TArray<FVector>& SpawnPoints, const FVector& CreatedPoint);

	UFUNCTION(BlueprintCallable)
		void TargetNeededForWinDestroyed() { --TargetsToWinAlive; }

	UFUNCTION(BlueprintCallable)
		void PlayerKilledTarget() { ++Kills; }

	UFUNCTION(BlueprintCallable)
		void OnTargetsForWinDestroy();

	UFUNCTION(BlueprintCallable)
		void StartNewRound(const ASphereDestroyerCharacter* Player);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float BeginSpawnRadius = 2000.0f;

	// Radius where spawns targets that are needed for round completion
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float WiningRadius = 1500.0f;

	// Total amount of targets
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int TargetAmount = 15;

	UPROPERTY(BlueprintReadOnly)
		int TargetsToWinAlive;

	// Amount of targets that are needed for round completion
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int TargetsToWin = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float TargetSpawnMinHight = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float TargetSpawnMaxHight = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float DistanceBetweenTargets = 80.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float TargetsSizeDecreaseByValue = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int TargetsAmountIncreaseByPercentage = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int SpawnRadiusIncreaseByPercentage = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int AmountOfRounds = 1;

	UPROPERTY(BlueprintReadOnly)
		int CurrentRound = 0;

	UPROPERTY(BlueprintReadOnly)
		int Kills = 0;

	UPROPERTY(BlueprintReadOnly)
		bool bIsGameFinished = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<ATarget> TargetClass;
};
