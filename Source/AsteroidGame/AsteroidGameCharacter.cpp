#include "AsteroidGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "AsteroidGameBullet.h"
#include "AsteroidGameGameMode.h"
#include "AsteroidGamePlayerController.h"

AAsteroidGameCharacter::AAsteroidGameCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	GunOffset = FVector(80.0f, 0.0f, 0.0f);
}

void AAsteroidGameCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AAsteroidGameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up "movement" bindings.
	PlayerInputComponent->BindAxis("MoveForward", this, &AAsteroidGameCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAsteroidGameCharacter::RotateRight);

	// fire
	PlayerInputComponent->BindKey("SpaceBar", EInputEvent::IE_Pressed, this, &AAsteroidGameCharacter::OnFire);
}

void AAsteroidGameCharacter::OnFire()
{
	if (ProjectileClass)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			const FRotator SpawnRotation = GetActorRotation();

			const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(GunOffset);

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			ActorSpawnParams.Instigator = this;

			// spawn the bullet projectile
			World->SpawnActor<AAsteroidGameBullet>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}

	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
}

void AAsteroidGameCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AAsteroidGameCharacter::RotateRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		AddActorWorldRotation(FRotator(0, Value, 0));
	}
}

float AAsteroidGameCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float TDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	Die();// since this is not health based character
	return TDamage;
}

void AAsteroidGameCharacter::Die()
{
	AAsteroidGamePlayerController* MyController = nullptr;
	
	if (Controller && Controller->GetPawn() == this)
	{
		MyController = Cast<AAsteroidGamePlayerController>(Controller);
	}
	
	// Unpossess
	DetachFromControllerPendingDestroy();
	
	if (MyController)
	{
		MyController->NotifyDead();
	}

	Destroy();// Dying effects can be added here.
}
