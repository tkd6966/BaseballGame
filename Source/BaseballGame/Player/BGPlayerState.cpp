#include "BGPlayerState.h"
#include "Net/UnrealNetwork.h"

ABGPlayerState::ABGPlayerState() : PlayerNameString(TEXT("None"))
{
	bReplicates = true;
}

void ABGPlayerState::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, PlayerNameString);
}
