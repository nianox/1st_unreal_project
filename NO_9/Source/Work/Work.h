#pragma once

#include "CoreMinimal.h"


class WorkFunctionLib
{
public:
	static void MyPrintString(const AActor* InWorldContextActor, const FString& InString, float InTimeToDisplay = 1.f, FColor InColor = FColor::Cyan)
	{
		if (IsValid(GEngine) && IsValid(InWorldContextActor))
		{
			const APlayerController* PC = Cast<APlayerController>(InWorldContextActor);
			bool bIsLocalPlayer = (PC && PC->IsLocalController());
			// 해당 액터가 플레이어 컨트롤러인지 확인
			// 그 컨트롤러가 이 컴퓨터에서 화면을 보고 있는 로컬 컨트롤러인지 확인
			
			if (bIsLocalPlayer)
			{// 오직 로컬 플레이어의 컨트롤러를 통해서 들어온 메시지만 화면에 그립니다. 
				GEngine->AddOnScreenDebugMessage(-1, InTimeToDisplay, InColor, InString);
			}
			else
			{
				// 그 외의 경우(서버 로직, 타인 로직 등)는 로그에만 남깁니다.
				UE_LOG(LogTemp, Log, TEXT("%s"), *InString);
			}
		}
	}

	static FString GetNetModeString(const AActor* InWorldContextActor)
	{
		FString NetModeString = TEXT("None");
		// 기본값 설정 만약 아무것도 하지 않게 될 경우 "None" 반환
		if (IsValid(InWorldContextActor) == true)
		{ //액터 유효성 검사
			ENetMode NetMode = InWorldContextActor->GetNetMode(); //위에서 했던 것 처럼 액터로부터 네트워크 모드를 가져온다
			if (NetMode == NM_Client)
			{ // 클라이언트 였을 경우 앞 클라이언트 반환
				NetModeString = TEXT("Client");
			}
			else
			{
				if (NetMode == NM_Standalone)
				{ // 넷모드가 스탠드 얼론일 경우,
					NetModeString = TEXT("StandAlone");
				}
				else
				{ // 넷모드가 서버일경우
					NetModeString = TEXT("Server");
				}
			}
		}

		return NetModeString;
	}// 반환

	static FString GetRoleString(const AActor* InActor)
	{
		FString RoleString = TEXT("None");

		if (IsValid(InActor) == true) // 액터 유효성 검사,
		{
			FString LocalRoleString = UEnum::GetValueAsString(TEXT("Engine.ENetRole"), InActor->GetLocalRole());
			//로컬 역할 가져오기, 및 문자열로 변환, 
			//UEnum::GetValueAsString: ENetRole이라는 열거형(Enum) 값을 "ROLE_Authority" 같은 사람이 읽기 쉬운 글자로 바꿔준다.
			FString RemoteRoleString = UEnum::GetValueAsString(TEXT("Engine.ENetRole"), InActor->GetRemoteRole());
			// 원격 역할(Remote Role) 가져오기 및 문자열 변환
			// InActor->GetRemoteRole(): '네트워크 반대편(서버 혹은 다른 클라이언트)'에서 이 액터가 어떤 역할인지 가져온다.
			RoleString = FString::Printf(TEXT("%s / %s"), *LocalRoleString, *RemoteRoleString);
			//문자열 합치기, 이 액터의 로컬 역할과, 이 액터가 다른 액터에선 어떻게 보일지 표시,
		}

		return RoleString;
	}

};

