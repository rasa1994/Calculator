export module FunctionEvaluation;
import InputChecker;
import <math.h>;
import <unordered_map>;
import <algorithm>;
import <utility>;
import <deque>;
import <vector>;
import <mutex>;
import <iterator>;
import <exception>;
import <stack>;
import <string_view>;
import <string>;

namespace
{
	std::unordered_map<unsigned short, std::deque<uint8_t>> CalculatedResults;
	unsigned short MaxEvaluated;
	std::once_flag InitializedFactoriel;
}

export
{
	using NumberAsArray = std::deque<uint8_t>;
	long double CalculateSQRT(long double value) noexcept;
	unsigned long long CalculateFACTORIAL(short value) noexcept;
	long double CalculateDegree(long double value);
	NumberAsArray CalculateBigNumberFactorial(unsigned short number);

	template <typename Number>
	NumberAsArray MultiplyTwoNumbers(const Number& number, const Number& multiplier);

	bool DivideTwoNumbers(NumberAsArray& number, unsigned int divider);
	void DivideTwoNumbers(unsigned int number, unsigned int divider);
	void ShrinkTwoNumbers(NumberAsArray& number1, NumberAsArray& number2);
	std::deque<unsigned long long> GeneratePrimeDividers(unsigned long limit);

	NumberAsArray GetBinom(std::string_view binomElements) noexcept;
	void RemoveLeadingZeros(NumberAsArray& number);
	NumberAsArray ConvertNumberToArray(unsigned short number);

	template <typename NumberTypeL, typename NumberTypeR>
	long double DoOperation(const NumberTypeL& number1, const NumberTypeR& number2, const std::string& operation);

	long double GetResult(std::string_view expression);
	std::deque<std::string> CreatePolishNotationExpression(const std::vector<std::string> expression);
	long double EvaluateResult(const std::deque<std::string>& expression);
}

template <typename NumberTypeL, typename NumberTypeR>
long double DoOperation(const NumberTypeL& number1, const NumberTypeR& number2, const std::string& operation)
{
	const auto leftAsLongDouble = static_cast<long double>(number1);
	if (operation == "+")
		return leftAsLongDouble + number2;
	if (operation == "-")
		return leftAsLongDouble - number2;
	if (operation == "*")
		return leftAsLongDouble * number2;
	if (operation == "/")
		return leftAsLongDouble / number2;
	throw std::runtime_error("Invalid operation!");
}

NumberAsArray GetBinom(std::string_view binomElements) noexcept
{
	return {};
}

NumberAsArray ConvertNumberToArray(unsigned short number)
{
	NumberAsArray result{};
	while (number)
	{
		result.push_front(number % 10);
		number /= 10;
	}
	return result;
}


void RemoveLeadingZeros(NumberAsArray& number)
{
	while (number.front() == 0)
		number.pop_front();
}

NumberAsArray CalculateBigNumberFactorial(unsigned short number)
{
	if (CalculatedResults.contains(number))
	{
		return CalculatedResults[number];
	}


	std::call_once(InitializedFactoriel, []()
	{
		MaxEvaluated = 1;
		CalculatedResults[0] = { 1 };
		CalculatedResults[1] = { 1 };
	});

	NumberAsArray result = CalculatedResults[std::min(MaxEvaluated, number)];

	for (unsigned int value = MaxEvaluated + 1; value <= number; ++value)
	{
		result = MultiplyTwoNumbers(result, ConvertNumberToArray(value));
		CalculatedResults[value] = result;
	}

	return result;
}


template <typename Number>
NumberAsArray MultiplyTwoNumbers(const Number& number, const Number& multiplier)
{
	if constexpr (std::is_same_v<Number, NumberAsArray>)
	{
		if (number.empty() || multiplier.empty())
			return{};

		short numberPtr = static_cast<short>(number.size() - 1);
		short multiplierPtr = static_cast<short>(multiplier.size() - 1);
		NumberAsArray result(number.size() + multiplier.size(), 0);
		short resultPtr = result.size() - 1;
		while (multiplierPtr >= 0)
		{
			auto multiplierNumber = multiplier.at(multiplierPtr--);
			short resultShift = resultPtr--;
			numberPtr = number.size() - 1;
			size_t depth = 0;
			while (numberPtr >= 0)
			{
				auto innerShift = resultShift - depth++;
				auto numberValue = number.at(numberPtr--);
				auto resultValue = result[innerShift] + numberValue * multiplierNumber;

				result[innerShift] = resultValue % 10;
				auto remainder = resultValue / 10;
				while (remainder)
				{
					result[--innerShift] += remainder;
					remainder = result[innerShift] / 10;
					result[innerShift] %= 10;
				}
			}
		}
		RemoveLeadingZeros(result);
		return result;
	}
	else if constexpr (std::is_integral_v<Number>)
	{
		NumberAsArray dividedNumber{}, dividedMultiplier{};
		Number numberCopy{ number };
		Number multiplierCopy{ multiplier };

		while (numberCopy != 0 || multiplierCopy != 0)
		{
			if (numberCopy != 0)
			{
				dividedNumber.push_front(numberCopy % 10);
				numberCopy /= 10;
			}

			if (multiplierCopy != 0)
			{
				dividedMultiplier.push_front(multiplierCopy % 10);
				multiplierCopy /= 10;
			}
		}

		return MultiplyTwoNumbers(dividedNumber, dividedMultiplier);
	}
	else
	{
		static_assert(false, "Format not recognisable!");
		return {};
	}
}


std::deque<std::string> CreatePolishNotationExpression(const std::vector<std::string> expression)
{
	std::deque<std::string> convertedExpression;
	std::deque<std::string> operations;
	bool startingMinus = false;
	for (const auto& partial : expression)
	{
		if (IsNumber(partial))
		{
			if (startingMinus)
			{
				startingMinus = false;
				std::string negativPartial = "-";
				negativPartial.append(partial);
				convertedExpression.push_back(negativPartial);
			}
			else
			{
				convertedExpression.push_back(partial);
				if (!operations.empty() &&
					IsHighLevelOperation(operations.back()) &&
					!IsLeftParenthesis(operations.back()))
				{
					convertedExpression.push_back(operations.back());
					operations.pop_back();
				}
			}
		}
		else if (IsLowLevelOperation(partial))
		{
			if (convertedExpression.empty())
			{
				startingMinus = true;
				continue;
			}
			operations.push_back(partial);
		}
		else if (IsHighLevelOperation(partial))
		{
			operations.push_back(partial);
		}
		else if (IsLeftParenthesis(partial))
		{
			operations.push_back(partial);
		}
		else if (IsRightParenthesis(partial) && !operations.empty())
		{
			while (!IsLeftParenthesis(operations.back()))
			{
				convertedExpression.push_back(operations.back());
				operations.pop_back();
			}
			operations.pop_back();
			while (!operations.empty() && IsHighLevelOperation(operations.back()))
			{
				convertedExpression.push_back(operations.back());
				operations.pop_back();
			}
		}
	}
	while (!operations.empty())
	{
		convertedExpression.push_back(operations.back());
		operations.pop_back();
	}

	return convertedExpression;
}


long double GetResult(std::string_view expression)
{
	if (AreParenthesisOk(expression))
	{
		const auto convertedResult = ConvertExpressionToIndividualOperation(expression.data());
		try
		{
			const auto expressionToPolish = CreatePolishNotationExpression(convertedResult);
			return EvaluateResult(expressionToPolish);
		}
		catch (const std::exception& exception)
		{
			throw std::runtime_error(exception.what());
		}
	}
	throw std::runtime_error("Not valid expression");
}


long double EvaluateResult(const std::deque<std::string>& expression)
{
	std::vector <long double> numbers;
	numbers.reserve(expression.size());
	for (const auto& digit : expression)
	{
		long double tempResult = 0.0;
		if (IsNumber(digit))
			numbers.emplace_back(std::stold(digit));
		else
		{
			const auto number2 = numbers.back();
			numbers.pop_back();
			const auto number1 = numbers.back();
			numbers.pop_back();
			numbers.push_back(DoOperation(number1, number2, digit));
		}
	}
	return numbers.back();
}