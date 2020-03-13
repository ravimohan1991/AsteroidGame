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

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	// For moving forward.
	UFUNCTION()
	void MoveForward(float Value);

	// For rotating
	UFUNCTION()
	void RotateRight(float Value);

	UFUNCTION()
	void OnFire();

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Projectile class. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	TSubclassOf<class AAsteroidGameBullet> ProjectileClass;

	/** Sound to be played everytime we fire. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;

	/**
	* Take Damage override.
	*/
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void Die();

private:
	/** Offset of the gun. */
	FVector GunOffset;
};

