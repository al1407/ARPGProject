// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "RPGAbilityComponent.h"
#include "RPGAttributeSet.h"
#include "RPGEnemy.generated.h"

UCLASS()
class ARPGPROJECT_API ARPGEnemy : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARPGEnemy();

	UPROPERTY()
	URPGAbilityComponent* AbilitySystem;

	UPROPERTY()
	URPGAttributeSet* AttributeSet;

	UPROPERTY(EditDefaultsOnly, Category = "RPG|Enemy")
	TSubclassOf<class UGameplayEffect> DefaultAttributesEffect;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void ShowDamage(float Damage);

};
