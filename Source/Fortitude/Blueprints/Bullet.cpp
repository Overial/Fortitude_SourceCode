// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"

ABullet::ABullet()
{
	this->PrimaryActorTick.bCanEverTick = false;

	// Initialize SphereCollisionComponent
	this->SphereCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	this->RootComponent = this->SphereCollisionComponent;
	this->SphereCollisionComponent->OnComponentHit.AddDynamic(this, &ABullet::OnBulletHit);

	// Initialize BulletMeshComponent
	this->BulletMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMesh"));
	this->BulletMeshComponent->SetupAttachment(this->SphereCollisionComponent);
	this->BulletMeshComponent->SetRelativeScale3D(FVector(0.5, 0.5f, 0.5f));

	// Initialize ProjectileMovementComponent
	this->ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	this->ProjectileMovementComponent->bShouldBounce = true;
	this->ProjectileMovementComponent->InitialSpeed = 5000.0f;
	this->ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	this->BulletImpactParticleSystemScale = FVector(0.5f, 0.5f, 0.5f);
	this->BaseDamage = 25.0f;
	this->HitCount = 0;
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();
}

void ABullet::OnBulletHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	++this->HitCount;

	OnBulletTargetHit(OtherActor);

	if (this->HitCount > 3)
	{
		UWorld* World = GetWorld();
		if (World != nullptr)
		{
			if (this->BulletImpactParticleSystem != nullptr)
			{
				UGameplayStatics::SpawnEmitterAtLocation
				(
					World,
					this->BulletImpactParticleSystem,
					GetActorLocation(),
					GetActorRotation(),
					this->BulletImpactParticleSystemScale
				);
			}
		}

		Destroy();
	}
}
