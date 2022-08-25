// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"
#include "SphereDestroyerGameInstance.h"

#include <Components/StaticMeshComponent.h>


// Sets default values
ATarget::ATarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	Mesh->AttachTo(this->RootComponent);
}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
	CurrentSize = DefaultSize;
	Mesh->SetRelativeScale3D(FVector(DefaultSize, DefaultSize, DefaultSize));
}

void ATarget::Destroyed()
{
	if (bNeededForWin)
	{
		UWorld* World = GetWorld();
		if (!ensure(World)) return;

		USphereDestroyerGameInstance* GameInstance = Cast<USphereDestroyerGameInstance>(World->GetGameInstance());
		if (!ensure(GameInstance)) return;
		GameInstance->TargetNeededForWinDestroyed();
	}

	Super::Destroyed();
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATarget::DecreaseSizeBy(float InSize)
{
	CurrentSize -= InSize;
	if (CurrentSize < MinSize) CurrentSize = MinSize;
	Mesh->SetRelativeScale3D(FVector(CurrentSize, CurrentSize, CurrentSize));
}

