#include "BGPlayerController.h"
#include "BGPlayerState.h"
#include "BaseBallGame/UI/BGChatInput.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BaseballGame/BaseballGame.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "BaseballGame/Game/BGGameModeBase.h"
#include "Net/UnrealNetwork.h"

ABGPlayerController::ABGPlayerController()
{
	bReplicates = true;
}

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
	
	if (IsValid(NotificationTextWidgetClass) == true)
	{
		NotificationTextWidgetInstance = CreateWidget<UUserWidget>(this, NotificationTextWidgetClass);
		if (IsValid(NotificationTextWidgetInstance) == true)
		{
			NotificationTextWidgetInstance->AddToViewport();
		}
	}
}

void ABGPlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	ChatMessageString = InChatMessageString;

	if (IsLocalController() == true)
	{
		ABGPlayerState* BGPS = GetPlayerState<ABGPlayerState>();
		if (IsValid(BGPS) == true)
		{
			FString CombinedMessageString = BGPS->GetPlayerInfoString() + TEXT(": ") + InChatMessageString;

			ServerRPCPrintChatMessageString(CombinedMessageString);
		}
	}
}

void ABGPlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	BaseballGameFunctionLibrary::MyPrintString(this, InChatMessageString, 10.f);
}

void ABGPlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, NotificationText);
}

void ABGPlayerController::ClientRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	PrintChatMessageString(InChatMessageString);
}

void ABGPlayerController::ServerRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
	if (IsValid(GM) == true)
	{
		ABGGameModeBase* BGGM = Cast<ABGGameModeBase>(GM);
		if (IsValid(BGGM) == true)
		{
			BGGM->PrintChatMessageString(this, InChatMessageString);
		}
	}
}
