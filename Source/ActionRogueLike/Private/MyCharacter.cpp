// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

#include "BaseProjectile.h"
#include "CharacterAttributeComponent.h"
#include "InteractComponent.h"
#include "MagicProjectile.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
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

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
}

void AMyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttributeComponent->OnHealthChange.AddDynamic(this, &AMyCharacter::OnPlayerHealthChange);
	AttributeComponent->OnDie.AddDynamic(this, &AMyCharacter::OnPlayerDie);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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

void AMyCharacter::PrimaryAttack()
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	AMagicProjectile* MagicProjectile = Cast<AMagicProjectile>(SpawnProjectile(MagicProjectileClass, HandLocation));
	if(ensure(MagicProjectile))
	{
		MagicProjectile->OnDamagedTarget.AddDynamic(this, &AMyCharacter::OnDoDamage);
		UGameplayStatics::SpawnEmitterAtLocation(this, MagicProjectileCastingVFX, HandLocation);
		UGameplayStatics::PlayWorldCameraShake(this, CameraShakeClass, HandLocation, 1, 10000);
	}
}

void AMyCharacter::UltimateAttack()
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	SpawnProjectile(UltimateProjectileClass, HandLocation);
}

void AMyCharacter::TeleportSkill()
{
	FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	SpawnProjectile(TeleportProjectileClass, HandLocation);
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

void AMyCharacter::OnDoDamage(UCharacterAttributeComponent* Target, int Damage)
{
	OnCharacterDoDamage.Broadcast(Target, Damage);
}

void AMyCharacter::OnPlayerHealthChange(AActor* InstigateActor, int DeltaVal, int CurrHealth)
{
	if(DeltaVal < 0)
	{
		UGameplayStatics::PlayWorldCameraShake(this, CameraShakeClass, GetActorLocation(), 1, 10000);
	}
	else
	{
		
	}
}
void AMyCharacter::OnPlayerDie(AActor* Killer)
{
	OnPlayerCharacterDie.Broadcast(this, Killer);
	if(CharacterWidget)
	{
		CharacterWidget->RemoveFromParent();
	}
	DisableInput(Cast<APlayerController>(GetController()));
	SetLifeSpan(8);
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
	PlayerInputComponent->BindAction("Skill", IE_Pressed, this, &AMyCharacter::TeleportSkill);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, InteractComponent, &UInteractComponent::Interact);
}

