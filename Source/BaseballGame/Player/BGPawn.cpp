// Fill out your copyright notice in the Description page of Project Settings.


#include "BGPawn.h"
#include "BaseballGame/BaseballGame.h"

void ABGPawn::BeginPlay()
{
	Super::BeginPlay();
	
	FString NetRoleString = BaseballGameFunctionLibrary::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("CXPawn::BeginPlay() %s [%s]"), *BaseballGameFunctionLibrary::GetNetModeString(this), *NetRoleString);
	BaseballGameFunctionLibrary::MyPrintString(this, CombinedString, 10.f);
}

void ABGPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	FString NetRoleString = BaseballGameFunctionLibrary::GetRoleString(this);
	FString CombinedString = FString::Printf(TEXT("CXPawn::PossessedBy() %s [%s]"), *BaseballGameFunctionLibrary::GetNetModeString(this), *NetRoleString);
	BaseballGameFunctionLibrary::MyPrintString(this, CombinedString, 10.f);
}


