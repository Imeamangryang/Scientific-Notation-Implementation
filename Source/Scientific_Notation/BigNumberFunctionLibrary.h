#pragma once

#include "CoreMinimal.h"
#include "FBigNumber.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BigNumberFunctionLibrary.generated.h"

UCLASS()
class SCIENTIFIC_NOTATION_API UBigNumberFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
	static FBigNumber NormalizeBigNumber(const FBigNumber& Number);
	
	UFUNCTION(BlueprintPure)
	static int32 CompareBigNumbers(const FBigNumber& A, const FBigNumber& B);
	
	UFUNCTION(BlueprintPure)
	static FBigNumber AddBigNumbers(const FBigNumber& A, const FBigNumber& B);
	
	UFUNCTION(BlueprintPure)
	static FBigNumber SubtractBigNumbers(const FBigNumber& A, const FBigNumber& B);
	
	UFUNCTION(BlueprintPure)
	static FBigNumber MultiplyBigNumbers(const FBigNumber& A, const FBigNumber& B);
	
	UFUNCTION(BlueprintPure)
	static FBigNumber DivideBigNumbers(const FBigNumber& A, const FBigNumber& B);
	
	UFUNCTION(BlueprintPure)
	static FBigNumber PowerBigNumber(const FBigNumber& Base, double power);
	
	UFUNCTION(BlueprintPure)
	static FBigNumber SqrtBigNumber(const FBigNumber& Number);
	
	UFUNCTION(BlueprintPure)
	static FString BigNumberToString(const FBigNumber& Number, int32 Decimal = 3);

	static const TArray<FString> Suffixes;
};
