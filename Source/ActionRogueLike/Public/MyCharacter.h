// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProjectile.h"
#include "CharacterAttributeComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "MyCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCharacterDoDamageSignature, UCharacterAttributeComponent*, Target, int, Damage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerCharacterDie, AMyCharacter*, PlayerCharacter, AActor*, Killer);
UCLASS()
class ACTIONROGUELIKE_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void MoveForward(float axis);
	virtual void MoveRight(float axis);
	void PrimaryAttack();
	void UltimateAttack();
	void TeleportSkill();
	AActor* SpawnProjectile(TSubclassOf<ABaseProjectile> ProjectileClass, FVector SpawnLocation);
	UFUNCTION()
	void OnDoDamage(UCharacterAttributeComponent* Target, int Damage);
	UFUNCTION()
	void OnPlayerHealthChange(AActor* InstigateActor, int DeltaVal, int CurrHealth);
	UFUNCTION()
	void OnPlayerDie(AActor* Killer);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	UPROPERTY(BlueprintAssignable)
    FOnCharacterDoDamageSignature OnCharacterDoDamage;
	UPROPERTY(BlueprintAssignable)
	FOnPlayerCharacterDie OnPlayerCharacterDie;
protected:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere)
	class UInteractComponent* InteractComponent;
	UPROPERTY(VisibleAnywhere)
	class UCharacterAttributeComponent* AttributeComponent;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABaseProjectile> MagicProjectileClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABaseProjectile> UltimateProjectileClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ABaseProjectile> TeleportProjectileClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UCameraShakeBase> CameraShakeClass;
	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* MagicProjectileCastingVFX;
	UPROPERTY(BlueprintReadWrite)
	UUserWidget* CharacterWidget;
};