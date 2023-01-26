// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseProjectile.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemInterface.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayEffectTypes.h"
#include "GAS/MyCharacterAttributeSet.h"
#include "MyCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCharacterDoDamageSignature, UCharacterAttributeComponent*, Target, int, Damage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCharacterDieSignature, AMyCharacter*, PlayerCharacter, AActor*, Killer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCharacterEnduranceChangeSignature, int, OldVal, int, NewVal);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCharacterRageValueChangeSignature, int, OldVal, int, NewVal);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCharacterGetBuffSignature, UAbilitySystemComponent*, SourceComp, const FGameplayEffectSpec&, GESpec, FActiveGameplayEffectHandle, ActiveGEHandle);
UCLASS()
class ACTIONROGUELIKE_API AMyCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	//Move, attack and skill(Bind to input)
	virtual void MoveForward(float axis);
	virtual void MoveRight(float axis);
	void StartSprint();
	void StopSprint();
	void PrimaryAttack();
	void UltimateAttack();
	void CharacterSkill();
	void CharacterJump();
	//Character Attribute Component Callback
	UFUNCTION()
	void OnHealthChange(AActor* InstigateActor, int DeltaVal, int CurrHealth);
	UFUNCTION()
	void OnDie(AActor* Killer);
	//Attribute Set Callback
	void OnEnduranceChange(const FOnAttributeChangeData& Data);
	void OnMovementSpeedChange(const FOnAttributeChangeData& Data);
	void OnRageValueChange(const FOnAttributeChangeData& Data);
	//Ability System Component callback
	void OnGetGameplayEffect(UAbilitySystemComponent* SourceComp, const FGameplayEffectSpec& GESpec, FActiveGameplayEffectHandle ActiveGEHandle);
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	UFUNCTION(BlueprintCallable)
	AActor* SpawnProjectile(TSubclassOf<ABaseProjectile> ProjectileClass, FVector SpawnLocation);
	UFUNCTION(BlueprintCallable)
	FGameplayAbilitySpecHandle GetAbilityHandle(FString AbilityName) const
	{
		if(CharacterAbilityHandles.Contains(AbilityName))
		{
			return CharacterAbilityHandles[AbilityName];
		}
		return FGameplayAbilitySpecHandle();
	}
public:
	UFUNCTION(Exec)
	void DebugAddHealth(int Delta);
public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
    FOnCharacterDoDamageSignature OnCharacterDoDamage;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCharacterDieSignature OnCharacterDie;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCharacterEnduranceChangeSignature OnCharacterEnduranceChange;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCharacterRageValueChangeSignature OnCharacterRageValueChange;
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCharacterGetBuffSignature OnCharacterGetBuff;
protected:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere)
	class UInteractComponent* InteractComponent;
	UPROPERTY(VisibleAnywhere)
	class UAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	const class UMyCharacterAttributeSet* MyCharacterAttributeSet;
	UPROPERTY(VisibleAnywhere)
	class UCharacterAttributeComponent* AttributeComponent;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UCameraShakeBase> GetHitCameraShakeClass;
	UPROPERTY(BlueprintReadWrite)
	UUserWidget* CharacterWidget;
	UPROPERTY(EditDefaultsOnly)
	TMap<FString, TSubclassOf<UGameplayAbility>> CharacterAbilities;
	TMap<FString, FGameplayAbilitySpecHandle> CharacterAbilityHandles;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> TiredEffectClass;
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> GetDamageAddRageEffectClass;
	//TODO:set global name for bufftag, not for specific charcter
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag BuffTag;
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag RageAttributeTag;
};