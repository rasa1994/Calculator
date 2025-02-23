export module InputChecker;
import <algorithm>;
import <charconv>;
import <string>;
import <stack>;
import <limits.h>;
import <float.h>;
import <vector>;
import <string_view>;
import <cmath>;
import <ranges>;
import <type_traits>;
import <typeinfo>;

export
{
	template <typename Type>
	concept TypeStringOrChar = std::is_same_v<Type, char> || std::is_convertible_v<Type, std::string>;

	template <TypeStringOrChar CharType>
	bool IsNumber(const CharType& operation) noexcept;

	template <TypeStringOrChar CharType>
	bool IsSimpleOperation(const CharType& operation) noexcept;

	std::vector<std::string> ConvertExpressionToIndividualOperation(const std::string& expression) noexcept;

	template <TypeStringOrChar CharType>
	bool CheckAddingParenthesis(std::string_view expression, const CharType& parenthesis) noexcept;

	template <TypeStringOrChar CharType>
	bool IsParenthesis(const CharType& operation) noexcept;

	bool AreParenthesisOk(std::string_view expression) noexcept;

	template <TypeStringOrChar CharType>
	bool IsLeftParenthesis(const CharType& expression) noexcept;

	template <TypeStringOrChar CharType>
	bool IsRightParenthesis(const CharType& expression) noexcept;

	bool CanDotBetAdded(std::string_view expression) noexcept;

	template <typename DecimalNumber>
	bool NumberHasOnlyZerosAfterDot(const DecimalNumber& number);

	template <typename From, typename To>
	To Convert(const From& number);

	using LeftRightPart = std::pair<unsigned short, unsigned short>;
	LeftRightPart GetNumbersForBinomFormula(std::string_view binomElements) noexcept;

	template <TypeStringOrChar CharType>
	bool IsHighLevelOperation(const CharType& operation) noexcept;

	template <TypeStringOrChar CharType>
	bool IsLowLevelOperation(const CharType& operation) noexcept;
}

template <TypeStringOrChar CharType>
bool IsLowLevelOperation(const CharType& operation) noexcept
{
	if constexpr (std::is_same_v<CharType, char>)
	{
		return operation == '+' || operation == '-';
	}
	else if constexpr (std::is_convertible_v<CharType, std::string>)
	{
		const auto converted = std::string(operation);
		return !converted.empty() && converted.size() == 1 && IsLowLevelOperation(converted.back());
	}
	else
	{
		static_assert(false, "IsLowLevelOperation() function is not implemented for this type");
		return false;
	}
}

template <TypeStringOrChar CharType>
bool IsHighLevelOperation(const CharType& operation) noexcept
{
	if constexpr (std::is_same_v<CharType, char>)
	{
		return operation == '*' || operation == '/';
	}
	else if constexpr (std::is_convertible_v<CharType, std::string>)
	{
		const auto converted = std::string(operation);
		return !converted.empty() && converted.size() == 1 && IsHighLevelOperation(converted.back());
	}
	else
	{
		static_assert(false, "IsHighLevelOperation() function is not implemented for this type");
		return false;
	}
}


template <typename From, typename To>
To Convert(const From& number)
{
	if constexpr (std::is_convertible_v<From, To>)
	{
		return static_cast<To>(number);
	}
	else
	{
		static_assert(false, "Convert() function is not implemented for this type");
		return To{};
	}
}



template <typename DecimalNumber>
bool NumberHasOnlyZerosAfterDot(const DecimalNumber& number)
{
	if (std::is_integral_v<DecimalNumber>)
	{
		return true;
	}
	
	if constexpr (std::is_convertible_v<DecimalNumber, long long>)
	{
		long long floorVersion = std::floor<long long>(number);
		return std::abs(number - floorVersion) <= std::numeric_limits<DecimalNumber>::epsilon();
	}

	return false;
}

template <TypeStringOrChar CharType>
bool IsRightParenthesis(const CharType& expression) noexcept
{
	if constexpr (std::is_same_v<CharType, char>)
	{
		return expression == ')';
	}
	else if constexpr (std::is_convertible_v<CharType, std::string>)
	{
		const auto converted = std::string(expression);
		return !converted.empty() && converted.size() == 1 && IsRightParenthesis(converted.back());
	}
	else
	{
		static_assert(false, "IsRightParenthesis() function is not implemented for this type");
		return false;
	}
}

template <TypeStringOrChar CharType>
bool IsLeftParenthesis(const CharType& expression) noexcept
{
	if constexpr (std::is_same_v<CharType, char>)
	{
		return expression == '(';
	}
	else if constexpr (std::is_convertible_v<CharType, std::string>)
	{
		const auto converted = std::string(expression);
		return !converted.empty() && converted.size() == 1 && IsLeftParenthesis(converted.back());
	}
	else
	{
		static_assert(false, "IsLeftParenthesis() function is not implemented for this type");
		return false;
	}
}

template <TypeStringOrChar CharType>
bool CheckAddingParenthesis(std::string_view expression, const CharType& parenthesis) noexcept
{
	if constexpr (std::is_same_v<CharType, char>)
	{
		if (!IsParenthesis(parenthesis))
		{
			return false;
		}
		if (parenthesis == '(')
		{
			if (expression.empty() || expression.back() == '(' || IsSimpleOperation(expression.back()))
				return true;
		}
		else if (parenthesis == ')')
		{
			if (expression.empty())
				return false;
			if (IsNumber(expression.back()) || IsRightParenthesis(expression.back()))
				return true;
		}
		return false;
	}
	else if constexpr (std::is_convertible_v<CharType, std::string>)
	{
		const auto converted = std::string(parenthesis);
		if (converted.empty() || converted.size() > 1)
			return false;
		return CheckAddingParenthesis(expression, converted.back());
	}
	else
	{
		static_assert(false, "CheckAddingParenthesis() function is not implemented for this type");
		return false;
	}
}

template <TypeStringOrChar CharType>
bool IsSimpleOperation(const CharType& operation) noexcept
{
	if constexpr (std::is_same_v<CharType, char>)
	{
		return operation == '-' || operation == '+' || operation == '*' || operation == '/';
	}
	else if constexpr (std::is_convertible_v<CharType, std::string>)
	{
		const auto converted = std::string(operation);
		return !converted.empty() && converted.size() == 1 && IsSimpleOperation(converted.back());
	}
	else
	{
		static_assert(false, "IsSimpleOperation() function is not implemented for this type");
		return false;
	}
}

template <TypeStringOrChar CharType>
bool IsNumber(const CharType& operation) noexcept
{
	if constexpr (std::is_same_v<CharType, char>)
	{
		return operation >= 48 && operation <= 57;
	}
	else if constexpr (std::is_convertible_v<CharType, std::string>)
	{
		const auto converted = std::string(operation);
		return !converted.empty() && std::ranges::all_of(converted, [](char a) { return IsNumber(a); });
	}
	else
	{
		static_assert(false, "IsNumber() function is not implemented for this type");
		return false;
	}
}

std::vector<std::string> ConvertExpressionToIndividualOperation(const std::string& expression) noexcept
{
	std::vector<std::string> piecesOfExpression;
	piecesOfExpression.reserve(expression.size());
	std::string helper{};
	for (const auto& character : expression)
	{
		if (!IsNumber(character) && character != '.')
		{
			if (!helper.empty())
			{
				piecesOfExpression.emplace_back(std::move(helper));
				helper.clear();
			}
			piecesOfExpression.emplace_back(1, character);
		}
		else
		{
			helper.push_back(character);
		}
	}
	if (!helper.empty())
		piecesOfExpression.emplace_back(std::move(helper));

	return piecesOfExpression;
}

template <TypeStringOrChar CharType>
bool IsParenthesis(const CharType& operation) noexcept
{
	if constexpr (std::is_same_v<CharType, char>)
	{
		return operation == '(' || operation == ')';
	}
	else if constexpr (std::is_convertible_v<CharType, std::string>)
	{
		const auto converted = std::string(operation);
		return !converted.empty() && converted.size() == 1 && IsParenthesis(converted.back());
	}
	else
	{
		static_assert(false, "IsParenthesis() function is not implemented for this type");
		return false;
	}
}



bool AreParenthesisOk(std::string_view expression) noexcept
{
	if (expression.empty())
		return true;

	std::stack<char> expressionPieces;
	for (const auto& character : expression)
	{
		if (character == '(')
			expressionPieces.push(character);
		else if (character == ')')
		{
			if (expressionPieces.empty())
				return false;

			expressionPieces.pop();
		}
	}
	return expressionPieces.empty();
}


bool CanDotBetAdded(std::string_view expression) noexcept
{
	for (const auto& character : expression | std::ranges::views::reverse)
	{
		if (character == '.')
			return false;
		if (IsParenthesis(character))
			return false;
		if (IsSimpleOperation(character))
			break;
	}

	return !expression.empty() && IsNumber(expression.back());
}


long long TransferNumberToInt(long double number)
{
	return static_cast<long long>(std::floor(number));
}



LeftRightPart GetNumbersForBinomFormula(std::string_view binomElements) noexcept
{
	unsigned short beforeComa = 0, afterComa = 0;
	const auto comaPosition = binomElements.find(',');

	if (comaPosition != std::string::npos)
	{
		std::from_chars(binomElements.data(), binomElements.data() + comaPosition, beforeComa);
		std::from_chars(binomElements.data() + comaPosition + 1, binomElements.data() + binomElements.size(), afterComa);
	}

	return std::make_pair(beforeComa, afterComa);
}
