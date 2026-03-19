#include "UI/WChatInput.h"

#include "Components/EditableTextBox.h"
#include "Player/WPlayerController.h"

void UWChatInput::NativeConstruct()
{
	Super::NativeConstruct();

	if (EditableTextBox_ChatInput->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted) == false)
	{// 함수가 등록되어 있는지 확인,
		EditableTextBox_ChatInput->OnTextCommitted.AddDynamic(this, &ThisClass::OnChatInputTextCommitted);
	}// false 라면 OnTextCommitted 이후 OnChatInputTextCommitted 를 연결
	//10~13코드 해석 다시 필요


}

void UWChatInput::NativeDestruct()
{
	Super::NativeDestruct();

	if (EditableTextBox_ChatInput->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted) == true)
	{
		EditableTextBox_ChatInput->OnTextCommitted.RemoveDynamic(this, &ThisClass::OnChatInputTextCommitted);
	} // RemoveDynamic 등록된 연결해지,
	// 10~13코드는 false 였던 것이 여기서는 true인 이유와 다이나믹 해석 필요
}

void UWChatInput::OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter) // 엔터 입력시, 및 자세한 설명은? 
	{ // ETextCommit은 언리얼 엔진의 UI 시스템(Slate/UMG)에서 사용자가 텍스트 입력을 어떤 방식으로 마쳤는가를 알려주는 열거형(Enumeration) 데이터 타입
		APlayerController* OwningPlayerController = GetOwningPlayer();
		if (IsValid(OwningPlayerController) == true) // GetOwningPlayer() 로 가져온 플레이어 컨트롤러는 유효한가?
		{
			AWPlayerController* OwningWPlayerController = Cast<AWPlayerController>(OwningPlayerController); // AWPlayerController를 가져온 플레이어 컨트롤러에 캐스팅;
			if (IsValid(OwningWPlayerController) == true) // 그 캐스팅한 OwningWPlayerController는 유효한가?
			{
				OwningWPlayerController->SetChatMessageString(Text.ToString()); //UI에서 입력한 텍스트를 String 문자열로 바꿔서 전해주기
				EditableTextBox_ChatInput->SetText(FText()); // 전해주고 나면 EditableTextBox_ChatInput를 공백으로 만들어주기,
			}
		}
	}
}

