// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"
#include "Engine/Engine.h"


// Sets default values
ATestActor::ATestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		FString Msg = FString::Printf(TEXT("TEST HI! Rotation %s and Location %s | Count: %d"), *GetActorRotation().ToString(), *GetActorLocation().ToString(), turncnt);
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, Msg);
	}
	FirstLocation = GetActorLocation();
	
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	TickTrigger(DeltaTime);
}

void ATestActor::TickTrigger(float DeltaTime)
{
	if (cpp <= 10) {
		if (cpp == 10)
		{
			if (GEngine)
			{
				FString msg = FString::Printf(TEXT("Whole Location difference: %s, Count: %d"), *(GetActorLocation() - FirstLocation).ToString(), movecnt);
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, msg);
			}
			cpp++;
		}
		OTTnums = FMath::RandRange(1, 2);
		{
			if (OTTnums == 1)
			{
				ChangeRotation(DeltaTime);
			}
			else
			{
				ChangeLocation(DeltaTime);
			}
			cpp++;
		}
	}
}


void ATestActor::ChangeRotation(float DeltaTime)
{
	turncnt++;
	FRotator CurrentRotation = GetActorRotation();

	FRotator RandomRotation = FRotator
	(
		FMath::FRandRange(0.0f, 360.0f), FMath::FRandRange(0.0f, 360.0f), FMath::FRandRange(0.0f, 360.0f)
	);
	SetActorRotation(CurrentRotation+RandomRotation);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, *GetActorRotation().ToString());
	}
}

void ATestActor::ChangeLocation(float DeltaTime)
{
	movecnt++;
	FVector CurrentLocation = GetActorLocation();

	FVector RandomLocation = FVector
	(
		FMath::FRandRange(1.0f, 20.0f), FMath::FRandRange(1.0f, 20.0f), FMath::FRandRange(1.0f, 5.0f)
	);
	SetActorLocation(CurrentLocation + RandomLocation);
	if (GEngine)
	{
		FString msg = FString::Printf(TEXT("Whole MOVE Location and MOVE count is : %s and %d"), *(GetActorLocation() - FirstLocation).ToString(),movecnt);
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, GetActorLocation().ToString());
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, msg);
	}
}