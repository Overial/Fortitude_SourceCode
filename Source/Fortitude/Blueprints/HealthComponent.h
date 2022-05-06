// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDieSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FORTITUDE_API UHealthComponent
	: public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float DefaultHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health", Transient)
	float Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health", Transient)
	bool bIsOwnerDead;

	UPROPERTY(BlueprintAssignable, Category = "Custom")
	FDieSignature OnDie;

public:
	UHealthComponent();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
