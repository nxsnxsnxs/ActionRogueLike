// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "BaseProjectile.h"
#include "CharacterAttributeComponent.h"
#include "InteractComponent.h"
#include "MagicProjectile.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilitySystemComponent.h"
#include "GAS/MyCharacterAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComponent->SetupAttachment(SpringArmComponent);
	InteractComponent = CreateDefaultSubobject<UInteractComponent>("InteractComp");
	AttributeComponent = CreateDefaultSubobject<UCharacterAttributeComponent>("AttributeComp");

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

void AMyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComponent->OnHealthChange.AddDynamic(this, &AMyCharacter::OnHealthChange);
	AttributeComponent->OnDie.AddDynamic(this, &AMyCharacter::OnDie);

	MyCharacterAttributeSet = Cast<UMyCharacterAttributeSet>(AbilitySystemComponent->GetAttributeSet(UMyCharacterAttributeSet::StaticClass()));
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	for(auto& [Name, AbilityClass] : CharacterAbilities)
	{
		CharacterAbilityHandles.Add(Name, AbilitySystemComponent->GiveAbility(AbilityClass));
	}
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MyCharacterAttributeSet->GetEnduranceAttribute()).AddUObject(this, &AMyCharacter::OnEnduranceChange);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MyCharacterAttributeSet->GetMovementSpeedAttribute()).AddUObject(this, &AMyCharacter::OnMovementSpeedChange);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MyCharacterAttributeSet->GetRageValueAttribute()).AddUObject(this, &AMyCharacter::OnRageValueChange);
	AbilitySystemComponent->OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &AMyCharacter::OnGetGameplayEffect);
}

void AMyCharacter::MoveForward(float axis)
{
	FRotator CameraRot = GetControlRotation();
	CameraRot.Pitch = 0;
	CameraRot.Roll = 0;
	AddMovementInput(CameraRot.Vector(), axis);
}

void AMyCharacter::MoveRight(float axis)
{
	FRotator CameraRot = GetControlRotation();
	CameraRot.Pitch = 0;
	CameraRot.Roll = 0;
	AddMovementInput(UKismetMathLibrary::GetRightVector(CameraRot), axis);
}

void AMyCharacter::StartSprint()
{
	if(ensure(CharacterAbilityHandles.Find("Sprint")))
	{
		AbilitySystemComponent->TryActivateAbility(CharacterAbilityHandles["Sprint"]);
	}
}

void AMyCharacter::StopSprint()
{
	if(ensure(CharacterAbilityHandles.Find("Sprint")))
	{
		AbilitySystemComponent->CancelAbilityHandle(CharacterAbilityHandles["Sprint"]);
	}
}

void AMyCharacter::PrimaryAttack()
{
	if(ensure(CharacterAbilityHandles.Find("PrimaryAttack")))
	{
		AbilitySystemComponent->TryActivateAbility(CharacterAbilityHandles["PrimaryAttack"]);
	}
}

void AMyCharacter::UltimateAttack()
{
	if(ensure(CharacterAbilityHandles.Find("UltimateAttack")))
	{
		AbilitySystemComponent->TryActivateAbility(CharacterAbilityHandles["UltimateAttack"]);
	}
}

void AMyCharacter::CharacterSkill()
{
	if(ensure(CharacterAbilityHandles.Find("Teleport")))
	{
		AbilitySystemComponent->TryActivateAbility(CharacterAbilityHandles["Teleport"]);
	}
}

void AMyCharacter::CharacterJump()
{
	if(ensure(CharacterAbilityHandles.Find("Jump")))
	{
		AbilitySystemComponent->TryActivateAbility(CharacterAbilityHandles["Jump"]);
	}
}

AActor* AMyCharacter::SpawnProjectile(TSubclassOf<ABaseProjectile> ProjectileClass, FVector SpawnLocation)
{
	//Calc Real Shoot Dir
	FVector Start = CameraComponent->GetComponentLocation();
	FVector End = Start + GetControlRotation().Vector() * 10000.0f;
	FHitResult HitResult;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
	ObjectQueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(5);
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	if(GetWorld()->SweepSingleByObjectType(HitResult, Start, End, FQuat::Identity, ObjectQueryParams,CollisionShape, CollisionQueryParams))
	{
		End = HitResult.ImpactPoint;
		//DrawDebugSphere(GetWorld(), End, 5, 32, FColor::Red, false, 3, 0, 2);
	}
	FRotator ShootDir = UKismetMathLibrary::MakeRotFromX(End - SpawnLocation);
	//Spawn Projectile
	FTransform SpawnTM(ShootDir, SpawnLocation);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParameters.Instigator = this;
	return GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParameters);
}

void AMyCharacter::OnHealthChange(AActor* InstigateActor, int DeltaVal, int CurrHealth)
{
	//Get Damage
	if(DeltaVal < 0)
	{
		//Camera Shake
		UGameplayStatics::PlayWorldCameraShake(this, GetHitCameraShakeClass, GetActorLocation(), 1, 10000);
		//Add Rage
		FGameplayEffectSpecHandle GESpecHandle = AbilitySystemComponent->MakeOutgoingSpec(GetDamageAddRageEffectClass, 1, AbilitySystemComponent->MakeEffectContext());
		FGameplayEffectSpec* GESpec = GESpecHandle.Data.Get();
		GESpec->SetSetByCallerMagnitude(RageAttributeTag, -DeltaVal);
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*GESpec);
	}
	//Get Heal
	else
	{
		
	}
}
void AMyCharacter::OnDie(AActor* Killer)
{
	OnCharacterDie.Broadcast(this, Killer);
	if(CharacterWidget)
	{
		CharacterWidget->RemoveFromParent();
	}
	DisableInput(Cast<APlayerController>(GetController()));
	SetLifeSpan(8);
}

void AMyCharacter::OnEnduranceChange(const FOnAttributeChangeData& Data)
{
	OnCharacterEnduranceChange.Broadcast(Data.OldValue, Data.NewValue);
	float Delta = Data.NewValue - Data.OldValue;
	static FActiveGameplayEffectHandle TiredEffectHandle;
	//Endurance Exhausted
	if(!AbilitySystemComponent->GetActiveGameplayEffect(TiredEffectHandle) && Delta < 0 && Data.NewValue <= 1)
	{
		//Cancel Abilities
		TArray<FGameplayTag> TiredEffectCancelAbilityWithTags;
		TiredEffectCancelAbilityWithTags.Add(FGameplayTag::RequestGameplayTag("Endurance.NeedEndurance"));
		FGameplayTagContainer TiredEffectCancelAbilityWithTagContainer = FGameplayTagContainer::CreateFromArray(TiredEffectCancelAbilityWithTags);
		AbilitySystemComponent->CancelAbilities(&TiredEffectCancelAbilityWithTagContainer);
		//Apply Tired Effect
		TiredEffectHandle = AbilitySystemComponent->BP_ApplyGameplayEffectToSelf(TiredEffectClass, 1, AbilitySystemComponent->MakeEffectContext());
	}
	//Remove Tired Effect
	else if(AbilitySystemComponent->GetActiveGameplayEffect(TiredEffectHandle) && Delta > 0 && Data.NewValue >= 0.5f * MyCharacterAttributeSet->GetMaxEndurance())
	{
		AbilitySystemComponent->RemoveActiveGameplayEffect(TiredEffectHandle);
	}
}

void AMyCharacter::OnMovementSpeedChange(const FOnAttributeChangeData& Data)
{
	GetCharacterMovement()->MaxWalkSpeed = Data.NewValue;
}

void AMyCharacter::OnRageValueChange(const FOnAttributeChangeData& Data)
{
	OnCharacterRageValueChange.Broadcast(Data.OldValue, Data.NewValue);
}

void AMyCharacter::OnGetGameplayEffect(UAbilitySystemComponent* SourceComp, const FGameplayEffectSpec& GESpec,
                                       FActiveGameplayEffectHandle ActiveGEHandle)
{
	FGameplayTagContainer GETags;
	GESpec.GetAllAssetTags(GETags);
	GESpec.GetAllGrantedTags(GETags);
	if(GETags.HasTag(BuffTag))
	{
		OnCharacterGetBuff.Broadcast(SourceComp, GESpec, ActiveGEHandle);
	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("TurnRight", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AMyCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("UltimateAttack", IE_Pressed, this, &AMyCharacter::UltimateAttack);
	PlayerInputComponent->BindAction("Skill", IE_Pressed, this, &AMyCharacter::CharacterSkill);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::CharacterJump);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, InteractComponent, &UInteractComponent::Interact);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMyCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMyCharacter::StopSprint);
}

void AMyCharacter::DebugAddHealth(int Delta)
{
	UKismetSystemLibrary::PrintString(this, "Debug Add Health " + Delta);
	AttributeComponent->ApplyHealthChange(Delta, this);
}

