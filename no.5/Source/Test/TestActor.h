// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestActor.generated.h"

UCLASS()
class TEST_API ATestActor : public AActor
{
	GENERATED_BODY()


	
public:	
	// Sets default values for this actor's properties
	ATestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void ChangeRotation(float DeltaTime); // 방향바꾸기용
	void ChangeLocation(float DeltaTime); // 이동용
	void CuttonCall(); // 끝나지롱
	void TickTrigger(float DeltaTime); // 당겨용
private:
	FVector FirstLocation;
	FVector DiffLocation;
	int OTTnums = 0;
	int cpp = 0;
	int turncnt = 0;
	int movecnt = 0;
};
