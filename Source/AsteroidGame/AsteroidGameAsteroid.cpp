#include "AsteroidGameAsteroid.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "AsteroidGamePlayerController.h"

AAsteroidGameAsteroid::AAsteroidGameAsteroid()
{
	UStaticMeshComponent* AsteroidMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AsteroidMeshComp"));
	RootComponent = AsteroidMeshComp;// Setting this way seems to work with projectile movement component
		
	// Use a ProjectileMovementComponent to govern this asteroid's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileAsteroidComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 2000.f;
	ProjectileMovement->MaxSpeed = 2000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	//CollisionComp->OnComponentHit.AddDynamic(this, &AAsteroidGameAsteroid::OnHit);
	//RootComponent = CollisionComp;
}

// Called when the game starts or when spawned
void AAsteroidGameAsteroid::BeginPlay()
{
	Super::BeginPlay();
	CollisionComp->OnComponentHit.AddDynamic(this, &AAsteroidGameAsteroid::OnHit);
}

void AAsteroidGameAsteroid::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Hitting spaceship or other asteroids
	FVector HitFromDirection = Hit.Location - GetActorLocation();
	if (!HitFromDirection.IsNearlyZero())
	{
		HitFromDirection.Normalize();
	}
	else
	{
		HitFromDirection = GetActorRotation().Vector();
	}

	UGameplayStatics::ApplyPointDamage(OtherActor, 100, HitFromDirection, Hit, GetInstigatorController(), this, UDamageType::StaticClass());
	UE_LOG(LogTemp, Warning, TEXT("Applying point damage to %s"), *OtherActor->GetName());
}

float AAsteroidGameAsteroid::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	//UE_LOG(LogTemp, Warning, TEXT("EventInstigator: %s,  DamageCauser: %s"), *EventInstigator->GetName(), *DamageCauser->GetName());
	
	AAsteroidGamePlayerController* MyController = Cast<AAsteroidGamePlayerController>(EventInstigator);
	if (MyController)
	{
		MyController->IncrementScore(ScoreReward);
	}
	Destroy();// not health based so we destory here.
	return Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}