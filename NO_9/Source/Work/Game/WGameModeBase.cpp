#include "Game/WGameModeBase.h"

#include "WGameStateBase.h"
#include "EngineUtils.h"
#include "Player/WPlayerController.h"
#include "Player/WPlayerState.h"



void AWGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SecretNumberString = GenerateNumber();
}

void AWGameModeBase::PrintChatMessageString(AWPlayerController* InChattingPlayerController, const FString& InChatMessageString)
{
	if (!IsValid(InChattingPlayerController))
	{
		return;
	}
	AWPlayerState* WPS = InChattingPlayerController->GetPlayerState<AWPlayerState>();
	if (!WPS)
	{
		return;
	}

	FString ChatMessageString = InChatMessageString; // 입력받은 메세지 복사,
	
	FString GuessNumberString = InChatMessageString.Right(3); // RightChop: 앞에서부터 Index만큼을 잘라내고 남은 마지막 3글자 가져오기.
	// 기존 RightChop의 문자열 길이가 3보다 낮을 경우의 위험성을 고려해서 조정
	
	if (IsGuessNumberString(GuessNumberString) == true) // 가져온 문자열 앞 3개는 과연 숫자야구용 문자열이 맞나?
	{ // 맞다!
		// 기회가 남아있는지 확인
		if (WPS->IsOutofAttempts()) // 기회가 없는 경우 
		{
			InChattingPlayerController->ClientRPCPrintChatMessageString(TEXT("시스템: 기회를 모두 소진하여 더 이상 게임에 참여할 수 없습니다. (일반 채팅은 가능합니다)"));

			// 기회는 없지만 입력한 내용은 일반 채팅으로 브로드캐스트 (선택 사항)
			BroadcastNormalChat(InChatMessageString);
		}
		else
		{ // 기회가 남아있다!
			WPS->AddAttempt();

			FString JudgeResultString = JudgeResult(SecretNumberString, GuessNumberString);

			FString AttemptInfo = FString::Printf(TEXT("[%d / %d]"), WPS->GetCurrentAttempts(), WPS->GetMAXAttempts());

			FString CombinedMessageString = FString::Printf(TEXT("%s %s -> %s"), *AttemptInfo, *InChatMessageString, *JudgeResultString);

			for (TActorIterator<AWPlayerController> It(GetWorld()); It; ++It) // 모든 플레이어에게 방송(Broadcast)
			{ //월드에 존재하는 모든 AWPlayerController를 순회.
				AWPlayerController* WPlayerController = *It;
				if (IsValid(WPlayerController) == true)
				{
					WPlayerController->ClientRPCPrintChatMessageString(CombinedMessageString);
					// ClientRPC 호출: 서버에서 개별 클라이언트의 화면에 출력 명령
				}
			}
			// 2. 승리 판정 (3스트라이크 확인)
			if (JudgeResultString == TEXT("3S0B"))
			{
				FinishGame(InChattingPlayerController, true); // 승리 종료
			}
			// 3. 무승부 판정 (본인의 마지막 기회였고 틀렸을 때)
			else if (WPS->IsOutofAttempts())
			{
				CheckGameOver(); // 다른 사람들도 다 썼는지 확인
			}
		}
		
	}
	else
	{//아니다!
		for (TActorIterator<AWPlayerController> It(GetWorld()); It; ++It)
		{
			AWPlayerController* WPlayerController = *It;
			if (IsValid(WPlayerController) == true)
			{
				WPlayerController->ClientRPCPrintChatMessageString(InChatMessageString);
			} // 평범하게 일반 채팅 처리
		}
	}
}

void AWGameModeBase::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	AWGameStateBase* WGameStateBase = GetGameState<AWGameStateBase>();
	if (IsValid(WGameStateBase) == true)
	{
		WGameStateBase->MulticastRPCBroadcastLoginMessage(TEXT("XXXXXXX"));
	}
}

FString AWGameModeBase::GenerateNumber()
{
	TArray<int32> number;
	for (int32 i = 1; i < 10; i++)
	{
		number.Add(i);
	}
	FMath::RandInit(FDateTime::Now().GetTicks());
	number = number.FilterByPredicate([](int32 Num) {return Num > 0; });
	
	FString Result;
	for (int32 i = 0; i < 3; ++i)
	{
		int32 Index = FMath::RandRange(0, number.Num() - 1);
		Result.Append(FString::FromInt(number[Index]));
		number.RemoveAt(Index);
	}
	return Result;
}

bool AWGameModeBase::IsGuessNumberString(const FString& InNumberString)
{
	bool bCanPlay = false;
	// 기본결과를 false로 설정, 
	//do while(false) 를 사용해서 한번만 전체문을 돌리는데 중간의 break 로 즉시 탈출 유도

	do {
		if (InNumberString.Len() != 3)
		{
			break;
		}
		bool bIsUnique = true;
		TSet<TCHAR> UniqueDigits;
		for (TCHAR C : InNumberString)
		{
			if (FChar::IsDigit(C) == false || C == '0')
			{
				bIsUnique = false;
				break;
			}
			UniqueDigits.Add(C);
		}
		if (bIsUnique == false)
		{
			break;
		} 
		// 위 코드중 TSet<TCHAR> UniqueDigits;는 왜 필요했을까 처음에는 Set형 구조체를 이용해서 내부중복을 없애는 것으로 
		// 최종적으로 UniqueDigits.Num() == 3.Num() == 3 을 체크해서 false 반환을 노린줄 알았는데 여기까지 작성하고 나니 이해가 안간다 
		//그런 논리는 없고 UniqueDigits 만 붕뜨는 기분인데


		bCanPlay = true;
	} while (false);

	return bCanPlay;
}

FString AWGameModeBase::JudgeResult(const FString& InSecretNumberString, const FString InGuessNumberString)
{
	int32 StrikeCount = 0, BallCount = 0;

	for (int32 i = 0; i < 3; ++i)
	{
		if (InSecretNumberString[i] == InGuessNumberString[i])
		{
			StrikeCount++;
		}
		else
		{
			FString PlayerGuessChar = FString::Printf(TEXT("%c"), InGuessNumberString[i]);
			if (InSecretNumberString.Contains(PlayerGuessChar))
			{
				BallCount++;
			}
		}
	}
	if (StrikeCount == 0 && BallCount == 0)
	{
		return TEXT("OUT");
	}


	return FString::Printf(TEXT("%dS%dB"), StrikeCount, BallCount);
}

void AWGameModeBase::FinishGame(AWPlayerController* Winner, bool bIsVictory)
{
	FString EndMessage;
	if (bIsVictory && Winner)
	{
		EndMessage = FString::Printf(TEXT("게임 종료 승리자 : %s, 정답 : %s "), *Winner->GetPlayerState<APlayerState>()->GetPlayerName(), *SecretNumberString);
	}
	else
	{
		EndMessage = FString::Printf(TEXT("게임 종료! 패배! (정답: %s) "), *SecretNumberString);
	}
	BroadcastNormalChat(EndMessage);

	AWGameStateBase* WGameStateBase = GetGameState<AWGameStateBase>();
	if (IsValid(WGameStateBase))
	{
		// Multicast RPC를 호출
		// 함수가 실행되면 모든 클라이언트에서 위젯이 생성되고 ShowResult호출
		WGameStateBase->MulticastRPCShowResultWidget(EndMessage);
	}
	
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AWGameModeBase::ResetGame, 5.0f, false);
}

void AWGameModeBase::CheckGameOver()
{
	bool bAnyPlayerHasChance = false;

	for (TActorIterator<AWPlayerController> It(GetWorld()); It; ++It)
	{	// 월드의 모든 플레이어 컨트롤러를 순회하며 남은 기회가 있는지 확인
		if (AWPlayerState* PS = (*It)->GetPlayerState<AWPlayerState>())
		{
			if (!PS->IsOutofAttempts()) // 한 명이라도 기회가 남았다면 게임은 계속됨
			{
				bAnyPlayerHasChance = true;
				break;
			}
		}
	}
	if (!bAnyPlayerHasChance)
	{// 모든 플레이어가 기회를 소진했다면 무승부로 종료
		FinishGame(nullptr, false);
	}
}

void AWGameModeBase::BroadcastNormalChat(const FString& InChatMessageString)
{
	for (TActorIterator<AWPlayerController> It(GetWorld()); It; ++It) // 모든 플레이어에게 방송(Broadcast)
	{ //월드에 존재하는 모든 AWPlayerController를 순회.
		AWPlayerController* WPlayerController = *It;
		if (IsValid(WPlayerController) == true)
		{
			WPlayerController->ClientRPCPrintChatMessageString(InChatMessageString);
			// ClientRPC 호출: 서버에서 개별 클라이언트의 화면에 출력 명령
		}
	}
}


void AWGameModeBase::ResetGame()
{
	SecretNumberString = GenerateNumber();
	//게임 리셋
	
	UE_LOG(LogTemp, Log, TEXT("새로운 게임 시작! 정답: %s"), *SecretNumberString);
	// 요구사항: 서버 로그에 정답 출력 (디버깅용)
	
	for (TActorIterator<AWPlayerController> It(GetWorld()); It; ++It)
	{
		if (AWPlayerState* PS = (*It)->GetPlayerState<AWPlayerState>())
		{ // 각 컨트롤러에게서 AWPlayerState를 가져온다.
			PS->ResetAttempts(); // 시도 횟수를 0으로 리셋
		}
	}
	
	FString ResetMessage = FString::Printf(TEXT("시스템: 게임이 리셋되었습니다! 새로운 숫자를 맞춰보세요."));
	
	BroadcastNormalChat(ResetMessage);
}