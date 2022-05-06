// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FortitudeGameInstance.generated.h"

enum class ERoundWinner
	: uint8;

UCLASS()
class FORTITUDE_API UFortitudeGameInstance
	: public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	int PlayerScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	int EnemyScore;

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Gameplay")
	void OnUpdateScore(ERoundWinner Winner);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Gameplay")
	void OnNewRound();
};
