// Fill out your copyright notice in the Description page of Project Settings.

#include "FortitudePlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Damage.h"
#include "Fortitude/Blueprints/HealthComponent.h"

AFortitudePlayerCharacter::AFortitudePlayerCharacter()
{
	this->PrimaryActorTick.bCanEverTick = false;
	this->bUseControllerRotationYaw = true;
	this->Tags.Add("Player");

	// Initialize TopDownSpringArm
	this->TopDownSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("TopDownSpringArm"));
	this->TopDownSpringArm->SetupAttachment(this->RootComponent);
	this->TopDownSpringArm->SetRelativeRotation(FRotator(-80.0f, 0.0f, 0.0f));
	this->TopDownSpringArm->TargetArmLength = 1200.0f;
	this->TopDownSpringArm->bDoCollisionTest = false;
	this->TopDownSpringArm->bUsePawnControlRotation = true;
	this->TopDownSpringArm->bInheritPitch = false;

	// Initialize TopDownCamera
	this->TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	this->TopDownCamera->SetupAttachment(this->TopDownSpringArm);
	this->TopDownCamera->PostProcessSettings.VignetteIntensity = 0.9f;

	// Initialize WeaponMesh
	this->WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	this->WeaponMesh->SetupAttachment(GetMesh(), TEXT("hand_r"));
	this->WeaponMesh->SetRelativeLocation(FVector(-8.87f, 7.53f, -2.86f));
	this->WeaponMesh->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));

	// Initialize HealthComponent
	this->HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	// Initialize AIPerceptionStimuliSource
	this->AIPerceptionStimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIPerceptionStimuliSource"));
	this->AIPerceptionStimuliSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
	this->AIPerceptionStimuliSource->RegisterForSense(TSubclassOf<UAISense_Damage>());
	this->AIPerceptionStimuliSource->RegisterWithPerceptionSystem();
}

void AFortitudePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}
