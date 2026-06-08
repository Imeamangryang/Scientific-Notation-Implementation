#pragma once

#include "CoreMinimal.h"
#include "FBigNumber.generated.h"

USTRUCT(BlueprintType)
struct FBigNumber
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Mantissa = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Exponent = 0;
};
