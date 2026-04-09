// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "RPGAbilityComponent.h"
#include "RPGAttributeSet.h"
#include "ARPGProjectCharacter.generated.h"

UCLASS(Blueprintable)
class AARPGProjectCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AARPGProjectCharacter();

	// Called when the game starts or when spawned.
	virtual void BeginPlay() override;

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

public:
	UPROPERTY()
	URPGAbilityComponent* AbilitySystem;

	UPROPERTY()
	URPGAttributeSet* AttributeSet;

	UPROPERTY(EditDefaultsOnly, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultAttributesEffect;

	UPROPERTY(BlueprintReadWrite, Category = "Abilities")
	TSubclassOf<UGameplayAbility> LeapSlamAbility;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
};

