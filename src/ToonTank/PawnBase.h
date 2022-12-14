// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Particles/ParticleSystem.h"
#include "ToonTanks/Actors/ProjectileBase.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraShake.h"
#include "PawnBase.generated.h"

class UHealthComponent;

UCLASS() class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

	public:
		// Sets default values for this pawn's properties
		APawnBase();

		void PawnDestroyed();
		virtual void HandleDestruction();

	private:
		//Components
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))	
		UCapsuleComponent* CapsuleComp;
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))		
		UStaticMeshComponent* BaseMesh;
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* TurretMesh;
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USceneComponent* ProjectileSpawnPoint;
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UHealthComponent* HealthComponent;

		//Variables
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Type", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AProjectileBase> ProjectileClass;
		UPROPERTY(EditAnywhere, Category = "Effects")
		UParticleSystem* DeathParticle;
		UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase *DeathSound;
		UPROPERTY(EditAnywhere, Category = "Effects")
		TSubclassOf<UCameraShake> DeathShake;

	protected:
		void RotateTurret(FVector LookAtTarget);

		void Fire();
};
