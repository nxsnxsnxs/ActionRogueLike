// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveBarrel.h"

#include "CharacterAttributeComponent.h"
#include "MagicProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AExplosiveBarrel::AExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	RootComponent = StaticMeshComponent;
	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();

	StaticMeshComponent->OnComponentHit.AddDynamic(this, &AExplosiveBarrel::OnHit);
}

void AExplosiveBarrel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if(OtherActor->IsA(AMagicProjectile::StaticClass()))
	{
		Explode();
	}
}

void AExplosiveBarrel::Explode()
{
	RadialForceComponent->FireImpulse();
	UGameplayStatics::SpawnEmitterAtLocation(this, ExplodeParticle, GetActorLocation());
	UGameplayStatics::SpawnSoundAtLocation(this, ExplodeSound, GetActorLocation());
	//DoDamage
	TArray<TEnumAsByte<EObjectTypeQuery>> QueryTypes;
	QueryTypes.Add(EObjectTypeQuery::ObjectTypeQuery3);
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(this);
	TArray<AActor*> ResultActors;
	if(UKismetSystemLibrary::SphereOverlapActors(this, GetActorLocation(), ExplodeRadius, QueryTypes, nullptr, IgnoredActors, ResultActors))
	{
		for(AActor* TargetActor : ResultActors)
		{
			UCharacterAttributeComponent* TargetAttributeComponent = TargetActor->FindComponentByClass<UCharacterAttributeComponent>();
			if(TargetAttributeComponent)
			{
				TargetAttributeComponent->ApplyHealthChange(-ExplodeDamage, this);
			}
		}
	}
	Destroy();
}

// Called every frame
void AExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

