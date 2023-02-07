// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "CoreGlobals.h"
#include "CoreMinimal.h"

#include "RealBandConfig.generated.h"

/**
 * 
 */
UCLASS(Config = Editor)
class URealBandConfig : public UObject
{
	GENERATED_BODY()
public:

	URealBandConfig();
	void SetConfig();
};
