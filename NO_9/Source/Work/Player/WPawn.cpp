#include "Player/WPawn.h"

#include "Work.h"

void AWPawn::BeginPlay()
{
	Super::BeginPlay();

	FString NetRoleString = WorkFunctionLib::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("CXPawn::BeginPlay() %s [%s]"), *WorkFunctionLib::GetNetModeString(this), *NetRoleString);
	WorkFunctionLib::MyPrintString(this, CombinedString, 10.f);
	
}

void AWPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	FString NetRoleString = WorkFunctionLib::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("CXPawn::PossessedBy() %s [%s]"), *WorkFunctionLib::GetNetModeString(this), *NetRoleString);
	WorkFunctionLib::MyPrintString(this, CombinedString, 10.f);
}

