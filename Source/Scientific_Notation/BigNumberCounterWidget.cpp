#include "BigNumberCounterWidget.h"
#include "TimerManager.h"

bool UBigNumberCounterWidget::Initialize()
{
	const bool bResult = Super::Initialize();

	if (ResetButton)
	{
		ResetButton->OnClicked.AddDynamic(this, &UBigNumberCounterWidget::OnClickReset);
	}

	if (AddButton)
	{
		AddButton->OnClicked.AddDynamic(this, &UBigNumberCounterWidget::OnClickAdd);
	}

	if (SubtractButton)
	{
		SubtractButton->OnClicked.AddDynamic(this, &UBigNumberCounterWidget::OnClickSubtract);
	}

	if (MultiplyButton)
	{
		MultiplyButton->OnClicked.AddDynamic(this, &UBigNumberCounterWidget::OnClickMultiply);
	}

	if (DivideButton)
	{
		DivideButton->OnClicked.AddDynamic(this, &UBigNumberCounterWidget::OnClickDivide);
	}

	if (PowerButton)
	{
		PowerButton->OnClicked.AddDynamic(this, &UBigNumberCounterWidget::OnClickPower);
	}

	if (SqrtButton)
	{
		SqrtButton->OnClicked.AddDynamic(this, &UBigNumberCounterWidget::OnClickSqrt);
	}

	CurrentValue = FBigNumber(0.0f, 0);

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
			UpdateTimerHandle,
			this,
			&UBigNumberCounterWidget::AutoIncrease,
			UpdateInterval,
			true
		);
	}

	RefreshText();

	return bResult;
}

void UBigNumberCounterWidget::AutoIncrease()
{
	CurrentValue = UBigNumberFunctionLibrary::AddBigNumbers(
		CurrentValue,
		FBigNumber(1.0f, 0)
	);

	RefreshText();
}

void UBigNumberCounterWidget::OnClickReset()
{
	CurrentValue = FBigNumber(0.0f, 0);
	RefreshText();
}

void UBigNumberCounterWidget::OnClickAdd()
{
	CurrentValue = UBigNumberFunctionLibrary::AddBigNumbers(
		CurrentValue,
		FBigNumber(1.0f, 0)
	);

	RefreshText();
}

void UBigNumberCounterWidget::OnClickSubtract()
{
	CurrentValue = UBigNumberFunctionLibrary::SubtractBigNumbers(
		CurrentValue,
		FBigNumber(1.0f, 0)
	);

	RefreshText();
}

void UBigNumberCounterWidget::OnClickMultiply()
{
	CurrentValue = UBigNumberFunctionLibrary::MultiplyBigNumbers(
		CurrentValue,
		FBigNumber(2.0f, 0)
	);

	RefreshText();
}

void UBigNumberCounterWidget::OnClickDivide()
{
	CurrentValue = UBigNumberFunctionLibrary::DivideBigNumbers(
		CurrentValue,
		FBigNumber(2.0f, 0)
	);

	RefreshText();
}

void UBigNumberCounterWidget::OnClickPower()
{
	CurrentValue = UBigNumberFunctionLibrary::PowerBigNumber(CurrentValue, 2.0);
	RefreshText();
}

void UBigNumberCounterWidget::OnClickSqrt()
{
	CurrentValue = UBigNumberFunctionLibrary::SqrtBigNumber(CurrentValue);
	RefreshText();
}

void UBigNumberCounterWidget::RefreshText()
{
	if (!CounterText)
	{
		return;
	}

	FString ResultString = UBigNumberFunctionLibrary::BigNumberToString(CurrentValue, Decimal);
	CounterText->SetText(FText::FromString(ResultString));
}