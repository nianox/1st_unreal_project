#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "WGameStateBase.generated.h"

class UWResultWidget;

UCLASS()
class WORK_API AWGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
	
public:
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCBroadcastLoginMessage(const FString& InNameString = FString(TEXT("XXXX")));

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCShowResultWidget(const FString& ResultText);

protected:

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UWResultWidget> ResultWidgetClass;
};
