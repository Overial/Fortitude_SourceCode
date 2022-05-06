// Fill out your copyright notice in the Description page of Project Settings.

#include "Fortitude/Blueprints/HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	this->PrimaryComponentTick.bCanEverTick = false;

	this->DefaultHealth = 100.0f;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	this->Health = 100.0f;
	this->bIsOwnerDead = false;

	AActor* Owner = GetOwner();
	if (Owner != nullptr)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeDamage);
	}
}

void UHealthComponent::OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	this->Health -= Damage;

	if (this->Health <= 0.0f)
	{
		this->bIsOwnerDead = true;
		OnDie.Broadcast();
	}
}
