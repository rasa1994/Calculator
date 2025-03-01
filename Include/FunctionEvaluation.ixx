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
import <unordered_set>;

namespace
{
	std::unordered_map<unsigned short, std::deque<uint8_t>> CalculatedResults;
	unsigned short MaxEvaluated;
	std::once_flag InitializedFactoriel, InitializedPrime;
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

	bool IsDivisible(const NumberAsArray& number, unsigned int divider);
	NumberAsArray DivideTwoNumbers(const NumberAsArray& number, unsigned int divider);

	using DequeLeftRightPart = std::pair <NumberAsArray, NumberAsArray>;
	DequeLeftRightPart ShrinkTwoNumbers(const NumberAsArray& number1, const NumberAsArray& number2);
	std::deque<unsigned long long> GeneratePrimeDividers(unsigned long long limit);
	std::deque<unsigned long long> GenerateUniquePrimeNumbers(unsigned long long limit);

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



bool IsDivisible(const NumberAsArray& number, unsigned int divider)
{
	NumberAsArray result{};
	auto remainder = 0;
	for (const auto& digit : number)
	{
		const auto value = remainder * 10 + digit;
		result.push_back(value / divider);
		remainder = value % divider;
	}

	return remainder == 0;
}



NumberAsArray DivideTwoNumbers(const NumberAsArray& number, unsigned int divider)
{
	NumberAsArray result{};
	auto remainder = 0;
	for (const auto& digit : number)
	{
		const auto value = remainder * 10 + digit;
		result.push_back(value / divider);
		remainder = value % divider;
	}
	RemoveLeadingZeros(result);
	return result;
}



DequeLeftRightPart ShrinkTwoNumbers(const NumberAsArray& number1, const NumberAsArray& number2)
{
	DequeLeftRightPart result = std::make_pair(number1, number2);

	auto& [number1Original, number2Original] = result;

	const auto biggest = std::pow<unsigned long long>(10, (std::max(number1Original.size(), number2Original.size())));
	
	// TODO: cache this part, this method will be called several times
	auto primeDivisiors = GenerateUniquePrimeNumbers(biggest);

	while (!primeDivisiors.empty())
	{
		const auto divider = primeDivisiors.front();
		if (IsDivisible(number1Original, divider) && IsDivisible(number2Original, divider))
		{
			number1Original = DivideTwoNumbers(number1Original, divider);
			number2Original = DivideTwoNumbers(number2Original, divider);
		}
		else 
			primeDivisiors.pop_front();
	}

	return result;
}



std::deque<unsigned long long> GeneratePrimeDividers(unsigned long long limit)
{
	std::deque<unsigned long long> primeDividers;
	auto divider = 2ull;

	while (limit > 1)
	{
		if (limit % divider == 0)
		{
			primeDividers.push_back(divider);
			limit /= divider;
		}
		else
		{
			++divider;
		}
	}
	
	return primeDividers;
}

int BinarySearch(const auto& container, const auto& value)
{
	auto left = 0;
	auto right = container.size() - 1;
	while (left <= right)
	{
		auto middle = left + (right - left) / 2;
		auto nextToMiddle = middle + 1;
		if (nextToMiddle >= container.size())
			return -1;

		if (value > container[middle] && value <= container[nextToMiddle])
			return nextToMiddle;

		if (value > container[middle])
			left = middle + 1;
		else
			right = middle - 1;
	}
	return -1;
}

std::deque<unsigned long long> GenerateUniquePrimeNumbers(unsigned long long limit)
{
	static std::deque<unsigned long long> result;
	std::call_once(InitializedPrime, []() 
		{
			result.push_back(2);
		});

	std::unordered_set <unsigned long long> oddNumbers;

	bool biggerThanLast = limit < result.back();

	for (auto divider{ result.back() }; divider <= limit; ++divider)
	{
		if (!oddNumbers.contains(divider))
		{
			result.push_back(divider);
			for (auto multiple = divider; multiple <= limit / divider; multiple++)
			{
				oddNumbers.insert(multiple * divider);
			}
		}
	}

	if (biggerThanLast)
	{
		return std::deque(result.begin(), result.begin() + BinarySearch(result, limit));
	}
	else
		return result;
}



NumberAsArray GetBinom(std::string_view binomElements) noexcept
{
	const auto [n, r] = GetNumbersForBinomFormula(binomElements);
	if (n < r)
		return{};

	auto nFactorial = CalculateBigNumberFactorial(n);
	auto rFactorial = CalculateBigNumberFactorial(r);
	auto nMinusRFactorial = CalculateBigNumberFactorial(n - r);
	std::tie(nFactorial, rFactorial) = ShrinkTwoNumbers(nFactorial, rFactorial);
	std::tie(nFactorial, nMinusRFactorial) = ShrinkTwoNumbers(nFactorial, nMinusRFactorial);

	auto bigMultiply = MultiplyTwoNumbers(rFactorial, nMinusRFactorial);
	std::tie(nFactorial, bigMultiply) = ShrinkTwoNumbers(nFactorial, bigMultiply);


	return nFactorial;
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