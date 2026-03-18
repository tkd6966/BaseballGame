#include "BGPlayerController.h"
#include "BaseBallGame/UI/BGChatInput.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BaseballGame/BaseballGame.h"

void ABGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController() == false)
	{
		return;
	}

	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);

	if (IsValid(ChatInputWidgetClass) == true)
	{
		ChatInputWidgetInstance = CreateWidget<UBGChatInput>(this, ChatInputWidgetClass);
		if (IsValid(ChatInputWidgetInstance) == true)
		{
			ChatInputWidgetInstance->AddToViewport();
		}
	}
}

void ABGPlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	ChatMessageString = InChatMessageString;

	PrintChatMessageString(ChatMessageString);
}

void ABGPlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	BaseballGameFunctionLibrary::MyPrintString(this, InChatMessageString, 10.f);
}
