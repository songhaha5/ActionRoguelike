// Copyright Epic Games, Inc. All Rights Reserved.


#include "ActionRoguelikeGameModeBase.h"

void AActionRoguelikeGameModeBase::StartPlay()
{
	Super::StartPlay();

	check(GEngine != nullptr);

	//��ʾ��Ϣ5s
	//-1��ֵ ��ֹ����Ϣ�����»�ˢ��
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, thisghhgiugh"));
}