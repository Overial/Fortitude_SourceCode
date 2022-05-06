// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UParticleSystem;
class USoundBase;
class UProjectileMovementComponent;

UCLASS()
class FORTITUDE_API ABullet
	: public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Bullet")
	USphereComponent* SphereCollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Bullet")
	UStaticMeshComponent* BulletMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Bullet")
	UProjectileMovementComponent* ProjectileMovementComponent;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	UParticleSystem* BulletImpactParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	FVector BulletImpactParticleSystemScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet")
	float BaseDamage;

	UPROPERTY(AdvancedDisplay)
	int HitCount;

public:
	ABullet();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void OnBulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Bullet")
	void OnBulletTargetHit(AActor* OtherActor);
};
