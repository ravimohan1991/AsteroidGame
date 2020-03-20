#pragma once

#include "GameFramework/Actor.h"
#include "AsteroidGameBullet.generated.h"

UCLASS()
class AAsteroidGameBullet : public AActor
{
	GENERATED_BODY()
	
	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	class USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

public:
	AAsteroidGameBullet(const FObjectInitializer& ObjectInitializer);

	/**
	 * Called when bullet hits an Actor
	 *
	 * Useful to detect the collision events with asteroids and spaceship.
	 *
	 * @param HitComp Pointer to the primitivecomponent of the asteroid
	 * @param OtherActor Pointer to the Actor hitting the asteroid
	 * @param OtherComp Pointer to the primitivecomponent of the Other Actor
	 * @param NormalImpulse
	 * @param Hit Structure containing information about one hit of a trace, such as point of impact and surface normal at that point.
	 */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }

	/** Returns ProjectileMovement subobject **/
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

protected:
	/** Override BeginPlay() for registering hit events. */
	virtual void BeginPlay() override;
};