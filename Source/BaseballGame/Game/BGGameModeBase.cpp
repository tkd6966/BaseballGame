#include "BGGameModeBase.h"
#include "BGGameStateBase.h"

void ABGGameModeBase::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);

	ABGGameStateBase* BGGameStateBase = GetGameState<ABGGameStateBase>();
	if (IsValid(BGGameStateBase) == true)
	{
		BGGameStateBase->MulticastRPCBroadcastLoginMessage(TEXT("XXXXXXX"));
	}
}
