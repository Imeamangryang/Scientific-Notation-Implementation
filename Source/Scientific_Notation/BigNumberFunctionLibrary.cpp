#include "BigNumberFunctionLibrary.h"
#include "FBigNumber.h"

const TArray<FString> UBigNumberFunctionLibrary::Suffixes = {
	TEXT(""),
	TEXT("K"),
	TEXT("M"),
	TEXT("B"),
	TEXT("T"),
	TEXT("Qa"),
	TEXT("Qi"),
	TEXT("Sx"),
	TEXT("Sp"),
	TEXT("Oc"),
	TEXT("No"),
	TEXT("Dc")
};

FBigNumber UBigNumberFunctionLibrary::NormalizeBigNumber(const FBigNumber& Number)
{
	float Mantissa = Number.Mantissa;
	int32 Exponent = Number.Exponent;

	constexpr int32 MaxExponent = 99999;

	if (FMath::IsNearlyZero(Mantissa))
	{
		return { 0.0f, 0 };
	}

	while (FMath::Abs(Mantissa) >= 10.0f)
	{
		Mantissa /= 10.0f;
		++Exponent;
	}

	while (FMath::Abs(Mantissa) < 1.0f)
	{
		Mantissa *= 10.0f;
		--Exponent;

		if (FMath::IsNearlyZero(Mantissa))
		{
			return { 0.0f, 0 };
		}
	}

	if (Exponent >= MaxExponent)
	{
		const float Sign = Mantissa < 0.0f ? -1.0f : 1.0f;
		return { 9.999999f * Sign, MaxExponent };
	}

	return { Mantissa, Exponent };
}

int32 UBigNumberFunctionLibrary::CompareBigNumbers(const FBigNumber& A, const FBigNumber& B)
{
	if (A.Exponent > B.Exponent)
	{
		return 1;
	}
	else if (A.Exponent < B.Exponent)
	{
		return -1;
	}
	else
	{
		if (A.Mantissa > B.Mantissa)
		{
			return 1;
		}
		else if (A.Mantissa < B.Mantissa)
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}
}

FBigNumber UBigNumberFunctionLibrary::AddBigNumbers(const FBigNumber& A, const FBigNumber& B)
{
	int32 ExponentResult;
	double MantissaA = A.Mantissa;
	double MantissaB = B.Mantissa;

	int32 ExponentDifference = A.Exponent - B.Exponent;

	if (FMath::Abs(ExponentDifference) > 15)
	{
		if (ExponentDifference > 0)
		{
			return A;
		}
		return B;
	}

	if (A.Exponent >= B.Exponent)
	{
		MantissaB /= FMath::Pow(10.0, ExponentDifference);
		ExponentResult = A.Exponent;
	}
	else
	{
		MantissaA /= FMath::Pow(10.0, -ExponentDifference);
		ExponentResult = B.Exponent;
	}

	double MantissaResult = MantissaA + MantissaB;

	FBigNumber CombinedResult;
	CombinedResult.Mantissa = MantissaResult;
	CombinedResult.Exponent = ExponentResult;

	return NormalizeBigNumber(CombinedResult);
}

FBigNumber UBigNumberFunctionLibrary::SubtractBigNumbers(const FBigNumber& A, const FBigNumber& B)
{
	int32 ExponentResult;
	double MantissaA;
	double MantissaB;

	// 음수에 대한 지원 X
	if (CompareBigNumbers(A, B) == -1)
	{
		return FBigNumber(0, 0);
	}
	
	int32 ExponentDifference = A.Exponent - B.Exponent;
	
	if (CompareBigNumbers(A, B) == 1)
	{
		ExponentResult = A.Exponent;
		MantissaA = A.Mantissa;
		MantissaB = B.Mantissa / FMath::Pow(10.0, ExponentDifference);
	}
	else
	{
		ExponentResult = B.Exponent;
		MantissaA = A.Mantissa / FMath::Pow(10.0, FMath::Abs(ExponentDifference));
		MantissaB = B.Mantissa;
	}
	
	double MantissaResult = MantissaA - MantissaB;
	
	FBigNumber CombinedResult;
	CombinedResult.Mantissa = MantissaResult;
	CombinedResult.Exponent = ExponentResult;
	
	return NormalizeBigNumber(CombinedResult);
}

FBigNumber UBigNumberFunctionLibrary::MultiplyBigNumbers(const FBigNumber& A, const FBigNumber& B)
{
	double MantissaResult = A.Mantissa * B.Mantissa;
	int32 ExponentResult = A.Exponent + B.Exponent;

	FBigNumber CombinedResult;
	CombinedResult.Mantissa = MantissaResult;
	CombinedResult.Exponent = ExponentResult;

	return NormalizeBigNumber(CombinedResult);
}

FBigNumber UBigNumberFunctionLibrary::DivideBigNumbers(const FBigNumber& A, const FBigNumber& B)
{
	if (FMath::IsNearlyZero(B.Mantissa))
	{
		return { 0.0, 0 };
	}

	double MantissaResult = A.Mantissa / B.Mantissa;
	int32 ExponentResult = A.Exponent - B.Exponent;

	FBigNumber CombinedResult;
	CombinedResult.Mantissa = MantissaResult;
	CombinedResult.Exponent = ExponentResult;

	return NormalizeBigNumber(CombinedResult);
}

FBigNumber UBigNumberFunctionLibrary::PowerBigNumber(const FBigNumber& Base, double Power)
{
	if (Base.Mantissa <= 0.0)
	{
		if (FMath::IsNearlyZero(Base.Mantissa) && Power > 0.0)
		{
			return { 0.0, 0 }; 
		}
		return { 0.0, 0 };
	}

	double RawExponent = static_cast<double>(Base.Exponent) * Power;

	double IntegralPart = 0.0;
	double FractionalPart = FMath::Modf(RawExponent, &IntegralPart);
	
	int32 ExponentResult = FMath::TruncToInt(IntegralPart);
	double MantissaResult = FMath::Pow(Base.Mantissa, Power) * FMath::Pow(10.0, FractionalPart);

	FBigNumber CombinedResult;
	CombinedResult.Mantissa = MantissaResult;
	CombinedResult.Exponent = ExponentResult;

	return NormalizeBigNumber(CombinedResult);
}

FBigNumber UBigNumberFunctionLibrary::SqrtBigNumber(const FBigNumber& Number)
{
	FBigNumber PowResult = PowerBigNumber(Number, 0.5);

	return NormalizeBigNumber(PowResult);
}

FString UBigNumberFunctionLibrary::BigNumberToString(const FBigNumber& Number, int32 Decimal)
{
	// Classical 표기법
	float MantissaResult; 
	
	if (Number.Mantissa == 0.0)
	{
		return TEXT("0");
	}
	
	int32 ExponentGroup = FMath::Floor(Number.Exponent / 3.0f);
	int32 GroupExponent = ExponentGroup * 3;
	
	if (Suffixes.IsValidIndex(ExponentGroup))
	{
		MantissaResult = Number.Mantissa * FMath::Pow(10.0f, Number.Exponent - GroupExponent);
		FString ResultString = FString::Printf(TEXT("%.*f%s"), Decimal, MantissaResult, *Suffixes[ExponentGroup]);
		return ResultString;
	}
	
	if (Number.Exponent < 0)
	{
		MantissaResult = Number.Mantissa * FMath::Pow(10.0f, Number.Exponent);
		FString ResultString = FString::Printf(TEXT("%.*f"), Decimal, MantissaResult);
		return ResultString;
	}
	
	// Scientific Notation으로 표현
	return FString::Printf(TEXT("%.*fe%d"), Decimal, Number.Mantissa, Number.Exponent);
}

