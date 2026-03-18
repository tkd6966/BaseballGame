#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BGPlayerController.generated.h"

class UBGChatInput;

UCLASS()
class BASEBALLGAME_API ABGPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	void SetChatMessageString(const FString& InChatMessageString);

	void PrintChatMessageString(const FString& InChatMessageString);

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBGChatInput> ChatInputWidgetClass;

	UPROPERTY()
	TObjectPtr<UBGChatInput> ChatInputWidgetInstance;

	FString ChatMessageString;
};
