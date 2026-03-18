#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BGChatInput.generated.h"

class UEditableTextBox;

UCLASS()
class BASEBALLGAME_API UBGChatInput : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> EditableTextBox_ChatInput;
};
