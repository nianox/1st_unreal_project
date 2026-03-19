#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WResultWidget.generated.h"

UCLASS()
class WORK_API UWResultWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, Category = "GameResult", meta = (DisplayName = "ShowResult"))
	void ShowResult(const FString& InResultText);

protected:
	
private:

};