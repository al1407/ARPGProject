// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameplayAbility.h"

UGameplayEffect* URPGGameplayAbility::GetCooldownGameplayEffect() const
{
    return CooldownEffect ? CooldownEffect->GetDefaultObject<UGameplayEffect>() : nullptr;
}

