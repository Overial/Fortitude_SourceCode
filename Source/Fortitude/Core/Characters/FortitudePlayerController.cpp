// Fill out your copyright notice in the Description page of Project Settings.

#include "FortitudePlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FortitudePlayerCharacter.h"

void AFortitudePlayerController::BeginPlay()
{
	Super::BeginPlay();

	OnBeginPlay();

	// Get ref to pawn
	this->FortitudePlayerCharacter = Cast<AFortitudePlayerCharacter>(GetCharacter());
	Possess(this->FortitudePlayerCharacter);

	// Get ref to character movement component
	this->CharacterMovementComponent = this->FortitudePlayerCharacter->GetCharacterMovement();

	this->SprintSpeed = 900.0f;
	this->WalkSpeed = 600.0f;
}

void AFortitudePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

	check(this->InputComponent);

	this->InputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AFortitudePlayerController::OnFire);

	this->InputComponent->BindAction(TEXT("TogglePauseMenu"), IE_Pressed, this, &AFortitudePlayerController::OnTogglePauseMenu).bExecuteWhenPaused = true;

	this->InputComponent->BindAction(TEXT("SlowTime"), IE_Pressed, this, &AFortitudePlayerController::OnStartSlowTime);
	this->InputComponent->BindAction(TEXT("SlowTime"), IE_Released, this, &AFortitudePlayerController::OnStopSlowTime);

	this->InputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &AFortitudePlayerController::OnStartSprint);
	this->InputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &AFortitudePlayerController::OnStopSprint);

	this->InputComponent->BindAxis(TEXT("MoveForward"), this, &AFortitudePlayerController::MoveForward);
	this->InputComponent->BindAxis(TEXT("MoveRight"), this, &AFortitudePlayerController::MoveRight);

	this->InputComponent->BindAxis(TEXT("Turn"), this, &AFortitudePlayerController::Turn);
	this->InputComponent->BindAxis(TEXT("LookUp"), this, &AFortitudePlayerController::LookUp);
}

void AFortitudePlayerController::MoveForward(float Val)
{
	if ((this->FortitudePlayerCharacter != nullptr) && (Val != 0.0f))
	{
		const FRotator Rotation = this->FortitudePlayerCharacter->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		
		this->FortitudePlayerCharacter->AddMovementInput(Direction, Val);
	}
}

void AFortitudePlayerController::MoveRight(float Val)
{
	if ((this->FortitudePlayerCharacter != nullptr) && (Val != 0.0f))
	{
		const FRotator Rotation = this->FortitudePlayerCharacter->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		
		this->FortitudePlayerCharacter->AddMovementInput(Direction, Val);
	}
}

void AFortitudePlayerController::Turn(float Val)
{
	if ((this->FortitudePlayerCharacter != nullptr) && (Val != 0.0f))
	{
		this->FortitudePlayerCharacter->AddControllerYawInput(Val);
	}
}

void AFortitudePlayerController::LookUp(float Val)
{
	if ((this->FortitudePlayerCharacter != nullptr) && (Val != 0.0f))
	{
		this->FortitudePlayerCharacter->AddControllerPitchInput(Val);
	}
}

void AFortitudePlayerController::OnStartSprint()
{
	this->CharacterMovementComponent->MaxWalkSpeed = this->SprintSpeed;
}

void AFortitudePlayerController::OnStopSprint()
{
	this->CharacterMovementComponent->MaxWalkSpeed = this->WalkSpeed;
}
