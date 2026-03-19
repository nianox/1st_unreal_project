#include "Player/WPlayerController.h"

#include "UI/WChatInput.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Work.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Game/WGameModeBase.h"

void AWPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController() == false)
	{
		return;
	}

	FInputModeUIOnly InputModeUIOnly; 
	SetInputMode(InputModeUIOnly);
	// 굉장히 번거로워 보이는 코드다

	if (IsValid(ChatInputWidgetClass) == true)
	{
		ChatInputWidgetInstance = CreateWidget<UWChatInput>(this, ChatInputWidgetClass); // 왜 인스턴스로 위젯을 만드는지 다시 배우기
		if (IsValid(ChatInputWidgetInstance) == true)
		{
			ChatInputWidgetInstance->AddToViewport();
		}
	}
}

void AWPlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	ChatMessageString = InChatMessageString;
	//UI에서 입력한 데이터를 SetChatMessage를 UI에서 실행해주고 그걸 넘겨준다 
	//PrintChatMessageString(ChatMessageString);  // ChatMessageString 은 InChatMessageString 값으로 바뀌고 그 값을 Print로 넘겨준다
	
	if (IsLocalController() == true)
	{
		ServerRPCPrintChatMessageString(InChatMessageString);
	}
}

void AWPlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	// UKismetSystemLibrary::PrintString(this, ChatMessageString, true, true, FLinearColor::Red, 5.0f);
	// 다만 여기서 이러면 왜 굳이 InChatMessageString를 매개변수로 String 타입으로 받을까? 강의가 이상한가?

	//UKismetSystemLibrary::PrintString(this, InChatMessageString, true, true, FLinearColor::Red, 5.0f);
	// 일단 바꿔보기로했다. 이건 디버깅 로그를 안쓸때 쓴다
	
	if (IsLocalController() == false)
	{
		return;
	}
	FString NetModeString = WorkFunctionLib::GetNetModeString(this);
	// work.h 에서 정의한 클래스 내부 함수 호출 해당 액터의 넷모드가 무엇인지 반환
	FString CombinedMessageString = FString::Printf(TEXT("%s: %s"), *NetModeString, *InChatMessageString);
	// 받은 메세지에의 앞에 넷모드를 붙여서 메세지를 정의 *를 붙이는건 문자열의 길이에 따른 용량을 고려해서 주소값만을 전해주는 기본적인 점도 있지만
	// %s 가 c언어 방식의 문자열 시작 주소가 들어오는걸 대기하기 때문인 점도 있다. 게다가 해당 코드는 원래 FString& 참조를 통해서 주소를 쓰지 않고도 효율적이게 되고 있다.
	WorkFunctionLib::MyPrintString(this, CombinedMessageString, 10.f);
	// 그 메세지를 출력
	// 신기하게 이 쪽에서는 InChatMessageString 를 정상적으로 쓴다.
}

void AWPlayerController::ClientRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	PrintChatMessageString(InChatMessageString);
}

void AWPlayerController::ServerRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	//for (TActorIterator<AWPlayerController> It(GetWorld()); It; ++It)
	//{
	//	AWPlayerController* WPlayerController = *It;
	//	if (IsValid(WPlayerController) == true)
	//	{
	//		WPlayerController->ClientRPCPrintChatMessageString(InChatMessageString);
	//	}
	//}
	AGameModeBase* GM = UGameplayStatics::GetGameMode(this); // 게임모드를 가져온다,
	if (IsValid(GM) == true) // 유효성 검사
	{
		AWGameModeBase* WGM = Cast<AWGameModeBase>(GM); // 기존 게임모드에 숫자야구 게임모드 캐스팅
		if (IsValid(WGM) == true) // 유효성 검사
		{
			WGM->PrintChatMessageString(this, InChatMessageString); // 게임모드에서 채팅 관리
		}
	}// 실제로는 서버에서 게임모드를 관리할테니 이렇게 되는게 맞나?? -> 아 이거 RPC 서버전용 객체구나;;
}



