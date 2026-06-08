#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BigNumberFunctionLibrary.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "BigNumberCounterWidget.generated.h"

UCLASS()
class SCIENTIFIC_NOTATION_API UBigNumberCounterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CounterText;

	UPROPERTY(meta = (BindWidget))
	UButton* ResetButton;

	UPROPERTY(meta = (BindWidgetOptional))
	UButton* AddButton;

	UPROPERTY(meta = (BindWidgetOptional))
	UButton* SubtractButton;

	UPROPERTY(meta = (BindWidgetOptional))
	UButton* MultiplyButton;

	UPROPERTY(meta = (BindWidgetOptional))
	UButton* DivideButton;

	UPROPERTY(meta = (BindWidgetOptional))
	UButton* PowerButton;

	UPROPERTY(meta = (BindWidgetOptional))
	UButton* SqrtButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BigNumber")
	FBigNumber CurrentValue = FBigNumber(0.0f, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BigNumber")
	int32 Decimal = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BigNumber")
	float UpdateInterval = 0.01f;

	FTimerHandle UpdateTimerHandle;

	UFUNCTION()
	void OnClickReset();

	UFUNCTION()
	void OnClickAdd();

	UFUNCTION()
	void OnClickSubtract();

	UFUNCTION()
	void OnClickMultiply();

	UFUNCTION()
	void OnClickDivide();

	UFUNCTION()
	void OnClickPower();

	UFUNCTION()
	void OnClickSqrt();

	void AutoIncrease();
	
	UFUNCTION(BlueprintCallable)
	void RefreshText();
};