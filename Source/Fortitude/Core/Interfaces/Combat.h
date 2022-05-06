// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Combat.generated.h"

UINTERFACE(BlueprintType)
class FORTITUDE_API UCombat
	: public UInterface
{
	GENERATED_BODY()
};

class FORTITUDE_API ICombat
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void OnAttackRanged();
};
