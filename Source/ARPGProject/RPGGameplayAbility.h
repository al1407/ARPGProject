// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "RPGGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class ARPGPROJECT_API URPGGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

	
public:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
    float Damage = 50.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
    TSubclassOf<UGameplayEffect> CostEffect;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
    TSubclassOf<UGameplayEffect> CooldownEffect;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
    TSubclassOf<UGameplayEffect> DamageEffect;

    virtual UGameplayEffect* GetCooldownGameplayEffect() const override;

 

};
