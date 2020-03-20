#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AsteroidGameAsteroid.generated.h"

UCLASS()
class ASTEROIDGAME_API AAsteroidGameAsteroid : public AActor
{
	GENERATED_BODY()
	
	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	class USphereComponent* CollisionComp;

	/** Asteroid mesh component. Configurable in blueprint. */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* AsteroidMeshComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

	/** Score given for hitting this asteroid.*/
	UPROPERTY(EditAnywhere, Category = "Gameplay")
	float ScoreReward;

public:	
	// Sets default values for this actor's properties
	AAsteroidGameAsteroid();

	/**
	 * Called when asteroid hits an Actor
	 *
	 * Useful to detect the collision events with other asteroids and spaceship.
	 *
	 * @param HitComp Pointer to the primitivecomponent of the asteroid
	 * @param OtherActor Pointer to the Actor hitting the asteroid
	 * @param OtherComp Pointer to the primitivecomponent of the Other Actor
	 * @param NormalImpulse 
	 * @param Hit Structure containing information about one hit of a trace, such as point of impact and surface normal at that point.
	 */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/**
	* Take Damage override.
	*
	* Increases the player score.
	*
	* @see https://www.unrealengine.com/blog/damage-in-ue4
	* @param DamageAmount How much damage to apply
	* @param DamageEvent Data package that fully describes the damage received.
	* @param EventInstigator The Controller responsible for the damage.
	* @param DamageCauser The Actor that directly caused the damage (e.g. the projectile that exploded, the rock that landed on you)
	* @return The amount of damage actually applied.
	*/
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	/**
	* Function called when the Asteroid takes damage from the collision with other asteroids or bullet.
	* Since we want only the large asteroids to break into small ones, we override this function in the
	* blueprint class of big asteroid.
	*
	* @see AAsteroidGameAsteroid::TakeDamage
	* @see Blueprint'/Game/TopDownCPP/Blueprints/Asteroids/BP_Asteroid2.BP_Asteroid2'
	*/	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Gameplay")
	void SpawnSmallerAsteroids();

protected:
	/**
	* Called when the game starts or when spawned.
	* Used for registering OnHit events and generate random asteroid velocity.
	*/
	virtual void BeginPlay() override;
};
