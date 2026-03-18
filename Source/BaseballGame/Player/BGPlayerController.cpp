#include "BGPlayerController.h"
#include "BaseBallGame/UI/BGChatInput.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BaseballGame/BaseballGame.h"
#include "EngineUtils.h"

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

	if (IsLocalController() == true)
	{
		ServerRPCPrintChatMessageString(InChatMessageString);
	}
}

void ABGPlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	BaseballGameFunctionLibrary::MyPrintString(this, InChatMessageString, 10.f);
}

void ABGPlayerController::ClientRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	PrintChatMessageString(InChatMessageString);
}

void ABGPlayerController::ServerRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	for (TActorIterator<ABGPlayerController> It(GetWorld()); It; ++It)
	{
		ABGPlayerController* BGPlayerController = *It;
		if (IsValid(BGPlayerController) == true)
		{
			BGPlayerController->ClientRPCPrintChatMessageString(InChatMessageString);
		}
	}
}
