#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "WPlayerState.generated.h"


UCLASS()
class WORK_API AWPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AWPlayerState();

	void AddAttempt() { CurrentAttempts++; }

	int32 GetCurrentAttempts() const { return CurrentAttempts; }

	int32 GetMAXAttempts() const { return MAXAttempts; }

	bool IsOutofAttempts() const {return CurrentAttempts >= MAXAttempts;}

	void ResetAttempts() { CurrentAttempts = 0; }


protected:
	UPROPERTY(EditDefaultsOnly, Category = "GameRules")
	int32 MAXAttempts = 3;

	UPROPERTY(VisibleAnywhere, Category = "Stats")
	int32 CurrentAttempts = 0;
};
