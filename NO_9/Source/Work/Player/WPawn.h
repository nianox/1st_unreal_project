#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "WPawn.generated.h"

UCLASS()
class WORK_API AWPawn : public APawn
{
	GENERATED_BODY()


protected:
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

};
