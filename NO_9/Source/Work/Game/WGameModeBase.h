#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WGameModeBase.generated.h"

class AWPlayerController;

UCLASS()
class WORK_API AWGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	void PrintChatMessageString(AWPlayerController* InChattingPlayerController, const FString& InChatMessageString);

	virtual void OnPostLogin(AController* NewPlayer) override;

	FString GenerateNumber();

	bool IsGuessNumberString(const FString& InNumberString);

	FString JudgeResult(const FString& InSecretNumberString, const FString InGuessNumberString);

	void BroadcastNormalChat(const FString& InChatMessageString);

	void FinishGame(AWPlayerController* Winner, bool bIsVictory);

	void CheckGameOver();

	void ResetGame();

protected:
	FString SecretNumberString;

	TArray<TObjectPtr<AWPlayerController>> AllPlayerControllers;
	
	UPROPERTY(BlueprintReadOnly)
	FString ResultMessage;
};
