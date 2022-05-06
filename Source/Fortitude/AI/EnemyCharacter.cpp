// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Fortitude/Blueprints/HealthComponent.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
	this->PrimaryActorTick.bCanEverTick = false;
	this->bUseControllerRotationYaw = false;
	this->Tags.Add(TEXT("Enemy"));
	this->AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	// Initialize WeaponMesh
	this->WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	this->WeaponMesh->SetupAttachment(GetMesh(), TEXT("hand_r"));
	this->WeaponMesh->SetRelativeLocation(FVector(-8.87f, 7.53f, -2.86f));
	this->WeaponMesh->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

	// Initialize HealthComponent
	this->HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}
