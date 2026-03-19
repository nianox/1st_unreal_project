#include "Game/WGameStateBase.h"

#include"Kismet/GameplayStatics.h"
#include"Player/WPlayerController.h"
#include "UI/WResultWidget.h"

void AWGameStateBase::MulticastRPCBroadcastLoginMessage_Implementation(const FString& InNameString)
{
	if (HasAuthority() == false) //서버가 아닌 클라이언트인지 확인 true 면 서버
	{
		APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0); // 로컬플레이어 컨트롤러 가져오기. 클라이언트 환경의 0번은 항상 플레이어 자신
		if (IsValid(PC) == true)
		{
			AWPlayerController* WPC = Cast<AWPlayerController>(PC);
			if (IsValid(WPC) == true)
			{
				FString NotificationString = InNameString + TEXT("has joined the game.");
				WPC->PrintChatMessageString(NotificationString);
			}
		}
	}
}

void AWGameStateBase::MulticastRPCShowResultWidget_Implementation(const FString& ResultText)
{
	if (IsValid(ResultWidgetClass))
	{
		UWResultWidget* ResultWidget = CreateWidget<UWResultWidget>(GetWorld(), ResultWidgetClass);
		if (IsValid(ResultWidget))
		{
			ResultWidget->ShowResult(ResultText);

			ResultWidget->AddToViewport();
		}
	}
}