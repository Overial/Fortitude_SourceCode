//// Fill out your copyright notice in the Description page of Project Settings.
//
//#include "FindRandomLocation.h"
//#include "BehaviorTree/BlackboardComponent.h"
//#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
//#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
//#include "Fortitude/AI/EnemyAIController.h"
//
//UFindRandomLocation::UFindRandomLocation()
//{
//	this->NodeName = "BTTask_FindRandomLocation";
//	this->SearchRadius = 0.0f;
//}
//
//EBTNodeResult::Type UFindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
//{
//	auto const EnemyAIControllerRef = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
//	auto const PawnRef = EnemyAIControllerRef->GetPawn();
//
//	UWorld* const World = GetWorld();
//	if (World != nullptr)
//	{
//		FVector const Origin = PawnRef->GetActorLocation();
//		UNavigationSystemV1* const NavigationSystem = UNavigationSystemV1::GetCurrent(World);
//		FNavLocation NavigationLocation;
//
//		if (NavigationSystem->GetRandomPointInNavigableRadius(Origin, this->SearchRadius, NavigationLocation, nullptr))
//		{
//			EnemyAIControllerRef->GetBlackboard()->SetValueAsVector(GetSelectedBlackboardKey(), NavigationLocation.Location);
//		}
//	}
//
//	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
//
//	return EBTNodeResult::Succeeded;
//}
