# Scientific Notation Implementation

Unreal Engine에서 사용할 수 있는 **Big Number(대형 수) 계산 및 표기 시스템** 예제 프로젝트입니다.  
`Mantissa + Exponent` 구조를 기반으로 큰 수를 정규화하고, 사칙연산 및 지수 연산을 수행하며, UMG 위젯으로 값을 시각적으로 조작할 수 있습니다.

## Overview

이 프로젝트는 다음 기능을 포함합니다:

- `FBigNumber` 기반 큰 수 표현
- 정규화된 scientific notation 처리
- 덧셈, 뺄셈, 곱셈, 나눗셈 지원
- 제곱 및 제곱근 연산 지원
- `K`, `M`, `B`, `T` 등 suffix 기반 문자열 출력
- UMG 기반 카운터 위젯 예제
- 일정 주기로 자동 증가하는 카운터 동작

## Project Structure

```text
Source/
└── Scientific_Notation/
    ├── BigNumberCounterWidget.cpp
    ├── BigNumberCounterWidget.h
    ├── BigNumberFunctionLibrary.cpp
    ├── BigNumberFunctionLibrary.h
    ├── FBigNumber.h
    ├── Scientific_Notation.Build.cs
    ├── Scientific_Notation.cpp
    └── Scientific_Notation.h
```

## Core Types

### `FBigNumber`

큰 수를 다음 두 값으로 저장합니다:

- `Mantissa`
- `Exponent`

예:

```cpp
FBigNumber Value{ 1.23f, 6 };
```

위 값은 아래를 의미합니다:

```text
1.23 × 10^6
```

## Main Features

### 1. Big Number Arithmetic

`UBigNumberFunctionLibrary`를 통해 다음 연산을 제공합니다:

- `NormalizeBigNumber`
- `CompareBigNumbers`
- `AddBigNumbers`
- `SubtractBigNumbers`
- `MultiplyBigNumbers`
- `DivideBigNumbers`
- `PowerBigNumber`
- `SqrtBigNumber`
- `BigNumberToString`

모든 주요 함수는 `BlueprintPure`로 선언되어 있어 Blueprint에서도 쉽게 사용할 수 있습니다.

### 2. Readable Number Formatting

큰 수는 suffix 형식으로 출력할 수 있습니다.

예:

- `1.23K`
- `5.67M`
- `9.99B`

suffix 범위를 벗어나면 scientific notation 형식으로 출력됩니다.

예:

```text
3.14e42
```

### 3. UMG Counter Widget

`UBigNumberCounterWidget`는 버튼 입력과 타이머를 이용해 값을 조작하는 예제 UI입니다.

지원 동작:

- Reset
- Add
- Subtract
- Multiply
- Divide
- Power
- Sqrt
- Auto Increase

## Example Usage

### Add

```cpp
FBigNumber Result = UBigNumberFunctionLibrary::AddBigNumbers(A, B);
```

### Multiply

```cpp
FBigNumber Result = UBigNumberFunctionLibrary::MultiplyBigNumbers(A, B);
```

### Power

```cpp
FBigNumber Result = UBigNumberFunctionLibrary::PowerBigNumber(A, 2.0);
```

### Convert to String

```cpp
FString Text = UBigNumberFunctionLibrary::BigNumberToString(Value, 2);
```

## Widget Behavior

`UBigNumberCounterWidget`는 초기화 시 버튼 이벤트를 바인딩하고, 타이머를 설정해 일정 간격마다 값을 증가시킵니다.

기본 동작:

- 초기값: `0`
- 자동 증가 간격: `0.01f`
- 표시 소수점 자리수: `2`

## Unreal Engine Dependencies

`Scientific_Notation.Build.cs`에 포함된 모듈:

- `Core`
- `CoreUObject`
- `Engine`
- `InputCore`
- `EnhancedInput`
- `UMG`

## How to Use

### 1. Open the Project

Unreal Engine에서 프로젝트를 열고 빌드합니다.

### 2. Create a Widget Blueprint

`UBigNumberCounterWidget`를 기반으로 Widget Blueprint를 생성합니다.

### 3. Bind Widgets

다음 위젯들을 연결합니다:

- `CounterText`
- `ResetButton`
- `AddButton`
- `SubtractButton`
- `MultiplyButton`
- `DivideButton`
- `PowerButton`
- `SqrtButton`

일부 버튼은 optional로 선언되어 있어 선택적으로 구성할 수 있습니다.

### 4. Display the Widget

게임 화면에 위젯을 추가하면 버튼 입력과 자동 증가에 따라 값이 갱신됩니다.

## Current Limitations

현재 구현에는 다음 제한이 있습니다:

- 음수 결과를 완전하게 지원하지 않음
- `SubtractBigNumbers()`에서 `A < B`인 경우 `0` 반환
- mantissa가 `float` 기반이라 정밀도 한계가 있음
- suffix 목록이 제한적임
- 부동소수점 연산에 따른 오차 가능성 존재

## Use Cases

이 프로젝트는 다음과 같은 경우에 활용할 수 있습니다:

- 클릭커 / 방치형 게임의 숫자 시스템
- Unreal Engine에서 scientific notation 처리
- Blueprint Function Library 예제 학습
- UMG + C++ UI 연동 예제 구현
