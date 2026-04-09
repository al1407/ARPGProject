// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "RPGAttributeSet.generated.h"

/**
 * 
 */

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


UCLASS()
class ARPGPROJECT_API URPGAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:

    UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health)
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, Health)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana)
    FGameplayAttributeData Mana;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, Mana)

        UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackSpeed)
    FGameplayAttributeData AttackSpeed;
    ATTRIBUTE_ACCESSORS(URPGAttributeSet, AttackSpeed)

protected:

    UFUNCTION()
    void OnRep_Health(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_Mana(const FGameplayAttributeData& OldValue);

    UFUNCTION()
    void OnRep_AttackSpeed(const FGameplayAttributeData& OldValue);

    virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
   
};
