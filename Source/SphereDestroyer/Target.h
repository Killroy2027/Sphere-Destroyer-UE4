// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target.generated.h"

class UStaticMeshComponent;
class UParticleSystemComponent;
UCLASS()
class SPHEREDESTROYER_API ATarget : public AActor
{
	GENERATED_BODY()


public:
	// Sets default values for this actor's properties
	ATarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destroyed() override;
	
	// On spawn mesh will have this size
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float DefaultSize = 1.0f;

	UPROPERTY(BlueprintReadOnly)
		float CurrentSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float MinSize = 0.2f;

	// Determines if target is needed to progress to the next round
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bNeededForWin = false;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void DecreaseSizeBy(float InSize);

	UFUNCTION(BlueprintCallable)
		void SetNeededForWin(bool IsNeededForWin) { bNeededForWin = IsNeededForWin; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* Mesh;
};
