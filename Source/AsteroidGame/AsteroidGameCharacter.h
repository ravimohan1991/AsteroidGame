#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AsteroidGameCharacter.generated.h"

UCLASS(Blueprintable)
class AAsteroidGameCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAsteroidGameCharacter();

	/**
	* Function for moving forward the spaceship
	*/
	UFUNCTION()
	void MoveForward(float Value);

	/**
	* Function for rotating the spaceship
	*/
	UFUNCTION()
	void RotateRight(float Value);

	/**
	* Fire logic
	*/
	UFUNCTION()
	void OnFire();

public:
	/**
	* Function to bind various ufunctions to the appropriate keys.
	*/
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Projectile class. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	TSubclassOf<class AAsteroidGameBullet> ProjectileClass;

	/** Sound to be played everytime we fire. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;

	/**
	* Take Damage override.
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
	* For killing the spaceship character. Calls 
	* AAsteroidGamePlayerController::NotifyDead
	*/
	void Die();

private:
	/** Offset of the gun. */
	FVector GunOffset;
};

