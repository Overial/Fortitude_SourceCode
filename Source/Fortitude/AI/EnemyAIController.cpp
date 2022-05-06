// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AIPerceptionComponent.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Engine/EngineTypes.h"
#include "TimerManager.h"

AEnemyAIController::AEnemyAIController(FObjectInitializer const& ObjectInitializer)
{
	this->PrimaryActorTick.bCanEverTick = true;
	
	// Initialize behavior tree
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> Obj(TEXT("BehaviorTree'/Game/GameFiles/AI/BT_Enemy.BT_Enemy'"));
	if (Obj.Succeeded())
	{
		this->BehaviorTree = Obj.Object;
	}
	
	// Initialize behavior tree component
	this->BehaviorTreeComponent = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorTreeComponent"));

	// Initialize blackboard
	this->Blackboard = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("Blackboard"));
	
	// Setup AIPerception binding
	SetPerceptionComponent(*(CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"))));
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnTargetDetected);

	// Initialise sight config
	this->SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
	this->SightConfig->PeripheralVisionAngleDegrees = 45.0f;
	this->SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	this->SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	this->SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	GetPerceptionComponent()->ConfigureSense(*(this->SightConfig));
	GetPerceptionComponent()->SetDominantSense(*(this->SightConfig)->GetSenseImplementation());

	// Initialize damage config
	this->DamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("DamageConfig"));
	GetPerceptionComponent()->ConfigureSense(*(this->DamageConfig));

	this->PatienceTime = 3.0f;
}

UBlackboardComponent* AEnemyAIController::GetBlackboard() const
{
	return this->Blackboard;
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	if (this->BehaviorTree != nullptr)
	{
		RunBehaviorTree(this->BehaviorTree);
		this->BehaviorTreeComponent->StartTree(*(this->BehaviorTree));
	}
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (this->Blackboard)
	{
		this->Blackboard->InitializeBlackboard(*(this->BehaviorTree)->BlackboardAsset);
	}
}

void AEnemyAIController::OnTargetDetected(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor->ActorHasTag("Player"))
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			if (Stimulus.WasSuccessfullySensed())
			{
				GetBlackboard()->SetValueAsObject(TEXT("TargetActor"), Actor);
				SetFocus(Actor);
				World->GetTimerManager().ClearTimer(this->PatienceTimerHandle);
			}
			else
			{
				World->GetTimerManager().SetTimer(this->PatienceTimerHandle, this, &AEnemyAIController::OnLoseTarget, this->PatienceTime, false);
			}
		}
	}
}

void AEnemyAIController::OnLoseTarget()
{
	GetBlackboard()->SetValueAsObject(TEXT("TargetActor"), nullptr);
	ClearFocus(EAIFocusPriority::Gameplay);
}
