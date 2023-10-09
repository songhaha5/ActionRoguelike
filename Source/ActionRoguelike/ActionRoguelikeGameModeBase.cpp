// Copyright Epic Games, Inc. All Rights Reserved.


#include "ActionRoguelikeGameModeBase.h"

void AActionRoguelikeGameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	//显示消息5s
	//-1键值 防止该消息被更新或刷新
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, thisghhgiugh"));
}