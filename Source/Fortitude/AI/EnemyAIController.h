// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "Fortitude/Core/Interfaces/Combat.h"
#include "EnemyAIController.generated.h"

class UBlackboardComponent;
class UBehaviorTree;
class UBehaviorTreeComponent;
class UAISenseConfig_Sight;
class UAISenseConfig_Damage;
class UAIPerceptionComponent;

UCLASS()
class FORTITUDE_API AEnemyAIController
	: public AAIController
	, public ICombat
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(EditDefaultsOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UAISenseConfig_Sight* SightConfig;

	UPROPERTY(EditDefaultsOnly, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UAISenseConfig_Damage* DamageConfig;

	UPROPERTY(AdvancedDisplay)
	FTimerHandle PatienceTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float PatienceTime;

public:
	AEnemyAIController(FObjectInitializer const& ObjectInitializer = FObjectInitializer::Get());

	UBlackboardComponent* GetBlackboard() const;

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	void OnTargetDetected(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	void OnLoseTarget();
};
