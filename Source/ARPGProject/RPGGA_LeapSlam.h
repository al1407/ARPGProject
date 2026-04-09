// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGGameplayAbility.h"
#include "RPGGA_LeapSlam.generated.h"

/**
 * 
 */
UCLASS()
class ARPGPROJECT_API URPGGA_LeapSlam : public URPGGameplayAbility
{
	GENERATED_BODY()
	
    FGameplayAbilitySpecHandle CachedHandle;
    const FGameplayAbilityActorInfo* CachedActorInfo;
    FGameplayAbilityActivationInfo CachedActivationInfo;

	URPGGA_LeapSlam();

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Leap")
    float ForwardStrength = 800.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Leap")
    float UpwardStrength = 400.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Leap")
    float BaseDuration = 0.5f;

    // AoE tuning
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Leap")
    float Radius = 300.f;
protected:

    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

    void PerformLeap(ACharacter* Character);
    void ApplyAOEDamage(ACharacter* Character);

    UFUNCTION()
    void OnLeapFinished(ACharacter* Character);

    virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
};
