// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "FortitudePlayerState.generated.h"

UCLASS()
class FORTITUDE_API AFortitudePlayerState
	: public APlayerState
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Gameplay")
	void OnHandlePlayerAction(const FText& ActionText);
};
