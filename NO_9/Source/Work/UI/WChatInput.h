#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WChatInput.generated.h"


UCLASS()
class WORK_API UWChatInput : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

protected:

	UFUNCTION()
	void OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);
	//이게 뭐더라

public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UEditableTextBox> EditableTextBox_ChatInput;


	
};
