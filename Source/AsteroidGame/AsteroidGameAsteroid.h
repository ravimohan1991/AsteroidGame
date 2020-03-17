#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "DestructibleComponent.h"
#include "AsteroidGameAsteroid.generated.h"

//class UDestructibleComponent;

UCLASS()
class ASTEROIDGAME_API AAsteroidGameAsteroid : public AActor
{
	GENERATED_BODY()
	
	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	class USphereComponent* CollisionComp;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//class UDestructibleComponent* AsteroidDestComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

	/** Score given for hitting this projectile.*/
	UPROPERTY(EditAnywhere, Category = "Gameplay")
	float ScoreReward;

public:	
	// Sets default values for this actor's properties
	AAsteroidGameAsteroid();

	/** called when asteroid hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/**
	* Take Damage override.
	*/
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
