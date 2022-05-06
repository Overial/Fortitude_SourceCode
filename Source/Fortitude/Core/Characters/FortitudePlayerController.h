// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Fortitude/Core/Interfaces/Combat.h"
#include "FortitudePlayerController.generated.h"

class AFortitudePlayerCharacter;
class UCharacterMovementComponent;

UCLASS()
class FORTITUDE_API AFortitudePlayerController
	: public APlayerController
	, public ICombat
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Gameplay", AdvancedDisplay)
	AFortitudePlayerCharacter* FortitudePlayerCharacter;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Gameplay", AdvancedDisplay)
	UCharacterMovementComponent* CharacterMovementComponent;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float SprintSpeed;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float WalkSpeed;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	float TimeDilation;

protected:
	void BeginPlay() override;

	void SetupInputComponent() override;

public:
	void MoveForward(float Val);

	void MoveRight(float Val);

	void Turn(float Val);

	void LookUp(float Val);

	void OnStartSprint();

	void OnStopSprint();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Gameplay")
	void OnStartSlowTime();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Gameplay")
	void OnStopSlowTime();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Gameplay")
	void OnTogglePauseMenu();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Gameplay")
	void OnFire();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Gameplay")
	void OnBeginPlay();
};
