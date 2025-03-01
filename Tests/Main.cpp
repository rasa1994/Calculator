import InputChecker;
import FunctionEvaluation;
import Constants;
import <gtest/gtest.h>;
import <algorithm>;
import <utility>;
import <numeric>;
import <deque>;
import <string>;

const auto Comp = [](const auto& v1, const auto v2)
	{
		return std::ranges::equal(v1, v2, [](const auto& wLH, const auto& wRH) {return wLH == wRH; });
	};



TEST(InputCheckerTest, IsSimpleOperation)
{
	EXPECT_TRUE(IsSimpleOperation("+"));
	EXPECT_TRUE(IsSimpleOperation("-"));
	EXPECT_TRUE(IsSimpleOperation("*"));
	EXPECT_TRUE(IsSimpleOperation('*'));
	EXPECT_TRUE(IsSimpleOperation("/"));
	EXPECT_FALSE(IsSimpleOperation("a"));
	EXPECT_FALSE(IsSimpleOperation("1"));
	EXPECT_FALSE(IsSimpleOperation(" "));
	EXPECT_FALSE(IsSimpleOperation(""));
}


TEST(InputCheckerTest, IsNumber)
{
	EXPECT_TRUE(IsNumber("1"));
	EXPECT_TRUE(IsNumber("2"));
	EXPECT_TRUE(IsNumber("3"));
	EXPECT_TRUE(IsNumber("4"));
	EXPECT_TRUE(IsNumber("5"));
	EXPECT_TRUE(IsNumber("6"));
	EXPECT_TRUE(IsNumber("7"));
	EXPECT_TRUE(IsNumber("8"));
	EXPECT_TRUE(IsNumber("9"));
	EXPECT_TRUE(IsNumber("0"));
	EXPECT_FALSE(IsNumber("+"));
	EXPECT_FALSE(IsNumber("-"));
	EXPECT_FALSE(IsNumber("*"));
	EXPECT_FALSE(IsNumber("/"));
	EXPECT_FALSE(IsNumber("a"));
	EXPECT_FALSE(IsNumber(" "));
	EXPECT_FALSE(IsNumber(""));
	EXPECT_TRUE(IsNumber('7'));
	EXPECT_TRUE(IsNumber('8'));
	EXPECT_TRUE(IsNumber('9'));
	EXPECT_TRUE(IsNumber('0'));
}

TEST(InputCheckerTest, ConvertExpressionToIndividualOperation)
{
	const auto result = ConvertExpressionToIndividualOperation("1+2");
	const auto expected = std::vector<std::string>{ "1", "+", "2" };
	const auto comp = [](const auto& vec1, const auto& vec2) { return std::ranges::equal(vec1, vec2, [](const auto& wLH, const auto& wRH) {return wLH == wRH; }); };
	EXPECT_TRUE(comp(result, expected));
	EXPECT_TRUE(comp(ConvertExpressionToIndividualOperation("1-2"), std::vector<std::string>{"1", "-", "2"}));
	EXPECT_TRUE(comp(ConvertExpressionToIndividualOperation("1*2"), std::vector<std::string>{"1", "*", "2"}));
	EXPECT_TRUE(comp(ConvertExpressionToIndividualOperation("1/2"), std::vector<std::string>{"1", "/", "2"}));
	EXPECT_TRUE(comp(ConvertExpressionToIndividualOperation("1+2+3"), std::vector<std::string>{"1", "+", "2", "+", "3"}));
	EXPECT_TRUE(comp(ConvertExpressionToIndividualOperation("1+2-3"), std::vector<std::string>{"1", "+", "2", "-", "3"}));
	EXPECT_TRUE(comp(ConvertExpressionToIndividualOperation("1+2*3"), std::vector<std::string>{"1", "+", "2", "*", "3"}));
	EXPECT_TRUE(comp(ConvertExpressionToIndividualOperation("1+2/3"), std::vector<std::string>{"1", "+", "2", "/", "3"}));
	EXPECT_TRUE(comp(ConvertExpressionToIndividualOperation("1-2+3"), std::vector<std::string>{"1", "-", "2", "+", "3"}));
	EXPECT_TRUE(comp(ConvertExpressionToIndividualOperation("1-2-3"), std::vector<std::string>{"1", "-", "2", "-", "3"}));
	EXPECT_TRUE(comp(ConvertExpressionToIndividualOperation("1-2*3"), std::vector<std::string>{"1", "-", "2", "*", "3"}));
}

TEST(InputCheckerTest, CheckAddingParenthesis)
{
	EXPECT_TRUE(CheckAddingParenthesis("", '('));
	EXPECT_FALSE(CheckAddingParenthesis("", ')'));
	EXPECT_FALSE(CheckAddingParenthesis("1", '('));
	EXPECT_TRUE(CheckAddingParenthesis("1", ')'));
	EXPECT_TRUE(CheckAddingParenthesis("1+", '('));
	EXPECT_FALSE(CheckAddingParenthesis("1+", ')'));
	EXPECT_FALSE(CheckAddingParenthesis("1+2", '('));
	EXPECT_TRUE(CheckAddingParenthesis("1+2", ')'));
	EXPECT_TRUE(CheckAddingParenthesis("1+2+", '('));
	EXPECT_FALSE(CheckAddingParenthesis("1+2+", ')'));
	EXPECT_FALSE(CheckAddingParenthesis("1+2+3", '('));
	EXPECT_TRUE(CheckAddingParenthesis("1+2+3", ')'));
	EXPECT_TRUE(CheckAddingParenthesis("1+2+3+", '('));
	EXPECT_FALSE(CheckAddingParenthesis("1+2+3+", ')'));
	EXPECT_FALSE(CheckAddingParenthesis("1+2+3+4", '('));
	EXPECT_TRUE(CheckAddingParenthesis("1+2+3+4", ')'));
	EXPECT_TRUE(CheckAddingParenthesis("1+2+3+4+", '('));
	EXPECT_FALSE(CheckAddingParenthesis("1+2+3+4+", ')'));
	EXPECT_FALSE(CheckAddingParenthesis("1+2+3+4+5", '('));
	EXPECT_TRUE(CheckAddingParenthesis("1+2+3+4+5", ')'));
	EXPECT_TRUE(CheckAddingParenthesis("1+2+3+4+5+", '('));
	EXPECT_FALSE(CheckAddingParenthesis("1+2+3+4+5+", ')'));
	EXPECT_FALSE(CheckAddingParenthesis("1+2+3+4+5+6", '('));
	EXPECT_TRUE(CheckAddingParenthesis("1+2+3+4+5+6", ')'));
	EXPECT_TRUE(CheckAddingParenthesis("1+2+3+4+5+6+", '('));
	EXPECT_FALSE(CheckAddingParenthesis("1+2+3+4+5+6+", ')'));
}

TEST(InputCheckerTest, IsParenthesis)
{
	EXPECT_TRUE(IsParenthesis('('));
	EXPECT_TRUE(IsParenthesis(')'));
	EXPECT_FALSE(IsParenthesis('+'));
	EXPECT_FALSE(IsParenthesis('-'));
	EXPECT_FALSE(IsParenthesis('*'));
	EXPECT_FALSE(IsParenthesis('/'));
	EXPECT_FALSE(IsParenthesis('1'));
	EXPECT_FALSE(IsParenthesis('2'));
	EXPECT_FALSE(IsParenthesis('3'));
	EXPECT_FALSE(IsParenthesis('4'));
	EXPECT_FALSE(IsParenthesis('5'));
	EXPECT_FALSE(IsParenthesis('6'));
	EXPECT_FALSE(IsParenthesis('7'));
	EXPECT_FALSE(IsParenthesis('8'));
	EXPECT_FALSE(IsParenthesis('9'));
	EXPECT_FALSE(IsParenthesis('0'));
	EXPECT_FALSE(IsParenthesis('a'));
	EXPECT_FALSE(IsParenthesis(' '));
	EXPECT_FALSE(IsParenthesis(""));
	EXPECT_TRUE(IsParenthesis(std::string(")")));
	EXPECT_TRUE(IsParenthesis(std::string("(")));
	EXPECT_FALSE(IsParenthesis(std::string("+")));
	EXPECT_FALSE(IsParenthesis(std::string("-")));
	EXPECT_FALSE(IsParenthesis(std::string("*")));
	EXPECT_FALSE(IsParenthesis(std::string("/")));
	EXPECT_FALSE(IsParenthesis(std::string("1")));
	EXPECT_FALSE(IsParenthesis(std::string("2")));
	EXPECT_FALSE(IsParenthesis(std::string("3")));
	EXPECT_FALSE(IsParenthesis(std::string("4")));
	EXPECT_FALSE(IsParenthesis(std::string("5")));
	EXPECT_FALSE(IsParenthesis(std::string("6")));
	EXPECT_FALSE(IsParenthesis(std::string("7")));
	EXPECT_FALSE(IsParenthesis(std::string("8")));
	EXPECT_FALSE(IsParenthesis(std::string("9")));
	EXPECT_FALSE(IsParenthesis(std::string("0")));
	EXPECT_FALSE(IsParenthesis(std::string("a")));
	EXPECT_FALSE(IsParenthesis(std::string(" ")));
	EXPECT_FALSE(IsParenthesis(std::string("")));
}

TEST(InputCheckerTest, AreParenthesisOk)
{
	EXPECT_TRUE(AreParenthesisOk(""));
	EXPECT_TRUE(AreParenthesisOk("()"));
	EXPECT_TRUE(AreParenthesisOk("(())"));
	EXPECT_TRUE(AreParenthesisOk("(()())"));
	EXPECT_TRUE(AreParenthesisOk("((()))"));
	EXPECT_TRUE(AreParenthesisOk("(((())))"));
	EXPECT_TRUE(AreParenthesisOk("((((()))))"));
	EXPECT_TRUE(AreParenthesisOk("(((((())))))"));
	EXPECT_TRUE(AreParenthesisOk("((((((()))))))"));
	EXPECT_TRUE(AreParenthesisOk("(((((((())))))))"));
	EXPECT_TRUE(AreParenthesisOk("((((((((()))))))))"));
	EXPECT_TRUE(AreParenthesisOk("(((((((((())))))))))"));

	EXPECT_FALSE(AreParenthesisOk(")("));
	EXPECT_FALSE(AreParenthesisOk("())"));
	EXPECT_FALSE(AreParenthesisOk("()("));
	EXPECT_FALSE(AreParenthesisOk("())("));
	EXPECT_TRUE(AreParenthesisOk("()()"));
	EXPECT_FALSE(AreParenthesisOk("()())"));
	EXPECT_FALSE(AreParenthesisOk("()()("));
	EXPECT_TRUE(AreParenthesisOk("()()()"));
	EXPECT_FALSE(AreParenthesisOk("()()())"));
	EXPECT_FALSE(AreParenthesisOk("()()()("));
	EXPECT_TRUE(AreParenthesisOk("()()()()"));
	EXPECT_FALSE(AreParenthesisOk("()()()())"));
	EXPECT_FALSE(AreParenthesisOk("()()()()("));
	EXPECT_TRUE(AreParenthesisOk("()()()()()"));
	EXPECT_FALSE(AreParenthesisOk("()()()()())"));
	EXPECT_FALSE(AreParenthesisOk("()()()()()("));
}

TEST(InputCheckerTest, IsLeftParenthesis)
{
	EXPECT_TRUE(IsLeftParenthesis('('));
	EXPECT_FALSE(IsLeftParenthesis(')'));
	EXPECT_TRUE(IsLeftParenthesis(std::string("(")));
	EXPECT_FALSE(IsLeftParenthesis(std::string(")")));
}

TEST(InputCheckerTest, IsRightParenthesis)
{
	EXPECT_FALSE(IsRightParenthesis('('));
	EXPECT_TRUE(IsRightParenthesis(')'));
	EXPECT_FALSE(IsRightParenthesis(std::string("(")));
	EXPECT_TRUE(IsRightParenthesis(std::string(")")));
}

TEST(InputCheckerTest, CanDotBetAdded)
{
	EXPECT_FALSE(CanDotBetAdded(""));
	EXPECT_TRUE(CanDotBetAdded("1"));
	EXPECT_FALSE(CanDotBetAdded("1+"));
	EXPECT_TRUE(CanDotBetAdded("1+2"));
	EXPECT_FALSE(CanDotBetAdded("1+2+"));
	EXPECT_TRUE(CanDotBetAdded("1+2+3"));
	EXPECT_FALSE(CanDotBetAdded("1+2+3+"));
	EXPECT_TRUE(CanDotBetAdded("1+2+3+4"));
	EXPECT_FALSE(CanDotBetAdded("1+2+3+4+"));
	EXPECT_TRUE(CanDotBetAdded("1+2+3+4+5"));
	EXPECT_FALSE(CanDotBetAdded("1+2+3+4+5+"));
	EXPECT_TRUE(CanDotBetAdded("1+2+3+4+5+6"));
	EXPECT_FALSE(CanDotBetAdded("1+2+3+4+5+6+"));
	EXPECT_TRUE(CanDotBetAdded("1+2+3+4+5+6+7"));
	EXPECT_FALSE(CanDotBetAdded("1+2+3+4+5+6+7+"));
	EXPECT_TRUE(CanDotBetAdded("1+2+3+4+5+6+7+8"));
	EXPECT_FALSE(CanDotBetAdded("1+2+3+4+5+6+7+8+"));
	EXPECT_TRUE(CanDotBetAdded("1+2+3+4+5+6+7+8+9"));
	EXPECT_FALSE(CanDotBetAdded("1+2+3+4+5+6+7+8+9+"));
	EXPECT_TRUE(CanDotBetAdded("1+2+3+4+5+6+7+8+9+0"));
	EXPECT_FALSE(CanDotBetAdded("1+2+3+4+5+6+7+8+9+0+"));
	EXPECT_TRUE(CanDotBetAdded("1+2+3+4+5+6+7+8+9+0+1"));
	EXPECT_FALSE(CanDotBetAdded("1+2+3+4+5+6+7+8+9+0+1+"));
}


TEST(InputCheckerTest, NumberHasOnlyZerosAfterDot)
{
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(1.0));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(1.000));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(1.0000));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(1.00000));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(1.000000));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(1.0000000));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(1.00000000));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(1.000000000));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(1.0000000000));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(1.00000000000));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(1.000000000000));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(1.0000000000000));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(1.00000000000000));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(1.000000000000000));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(1.0000000000000000));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(1.00000000000000000));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(1.000000000000000000));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(1.0000000000000000000));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(1.00000000000000000000));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(1.000000000000000000000));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(1.0000000000000000000000));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(1.00000000000000000000000));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(1.000000000000000000000000));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(1.0000000000000000000000000));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(1.00000000000000000000000000));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(1.000000000000000000000000000));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(1.0f));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(2));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(-4));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(-4.000f));
	EXPECT_TRUE(NumberHasOnlyZerosAfterDot(-4.0000000001f)); // epsilon too small it wont catch last 1
}

TEST(InputCheckerTest, ConvertTo)
{
	EXPECT_TRUE((Convert<double, int>(1.66) == 1));
	EXPECT_TRUE((Convert<int, double>(1) == 1.0));
	EXPECT_TRUE((Convert<int, unsigned int>(-1) == std::numeric_limits<unsigned int>::max()));

}

TEST(InputCheckerTest, GetNumbersForBinomFormula)
{
	EXPECT_TRUE((GetNumbersForBinomFormula("1,2") == std::pair<unsigned short, unsigned short>{1, 2}));
	EXPECT_TRUE((GetNumbersForBinomFormula("11,22") == std::pair<unsigned short, unsigned short>{11, 22}));
	EXPECT_TRUE((GetNumbersForBinomFormula("111,222") == std::pair<unsigned short, unsigned short>{111, 222}));

	EXPECT_TRUE((GetNumbersForBinomFormula("115,42") == std::pair<unsigned short, unsigned short>{115, 42}));
	EXPECT_TRUE((GetNumbersForBinomFormula("91,91") == std::pair<unsigned short, unsigned short>{91, 91}));

	EXPECT_TRUE((GetNumbersForBinomFormula("91,91,91") == std::pair<unsigned short, unsigned short>{91, 91}));
	EXPECT_TRUE((GetNumbersForBinomFormula("91,91,91111") == std::pair<unsigned short, unsigned short>{91, 91}));
	EXPECT_TRUE((GetNumbersForBinomFormula("91,91,91123123") == std::pair<unsigned short, unsigned short>{91, 91}));
	EXPECT_TRUE((GetNumbersForBinomFormula("91,91,9144411,124494") == std::pair<unsigned short, unsigned short>{91, 91}));
}

TEST(InputCheckerTest, MultiplyTwoNumbers)
{


	EXPECT_TRUE(Comp(MultiplyTwoNumbers(1, 1), NumberAsArray{ 1 }));
	EXPECT_TRUE(Comp(MultiplyTwoNumbers(1, 2), NumberAsArray{ 2 }));
	EXPECT_TRUE(Comp(MultiplyTwoNumbers(4, 4), NumberAsArray{ 1, 6 }));
	EXPECT_TRUE(Comp(MultiplyTwoNumbers(7, 7), NumberAsArray{ 4, 9 }));
	EXPECT_TRUE(Comp(MultiplyTwoNumbers(9, 9), NumberAsArray{ 8, 1 }));
	EXPECT_TRUE(Comp(MultiplyTwoNumbers(99, 99), NumberAsArray{ 9, 8, 0, 1 }));
    EXPECT_TRUE(Comp(MultiplyTwoNumbers(999, 999), NumberAsArray{ 9, 9, 8, 0, 0, 1 }));
	EXPECT_TRUE(Comp(MultiplyTwoNumbers(9999, 9999), NumberAsArray{ 9, 9, 9, 8, 0, 0, 0, 1 }));
	EXPECT_TRUE(Comp(MultiplyTwoNumbers(99999, 99999), NumberAsArray{ 9, 9, 9, 9, 8, 0, 0, 0, 0, 1 }));
	EXPECT_TRUE(Comp(MultiplyTwoNumbers(999999, 999999), NumberAsArray{ 9, 9, 9, 9, 9, 8, 0, 0, 0, 0, 0, 1 }));
	EXPECT_TRUE(Comp(MultiplyTwoNumbers(9999999, 9999999), NumberAsArray{ 9, 9, 9, 9, 9, 9, 8, 0, 0, 0, 0, 0, 0, 1 }));
	EXPECT_TRUE(Comp(MultiplyTwoNumbers(12, 99998), NumberAsArray{ 1, 1, 9, 9, 9, 7, 6}));
}


TEST(InputCheckerTest, FactorialOfBigNumbers)
{
	EXPECT_TRUE(Comp(CalculateBigNumberFactorial(1), NumberAsArray{ 1 }));
	EXPECT_TRUE(Comp(CalculateBigNumberFactorial(5), NumberAsArray{ 1, 2, 0 }));
	EXPECT_TRUE(Comp(CalculateBigNumberFactorial(6), NumberAsArray{ 7, 2, 0 }));
	EXPECT_TRUE(Comp(CalculateBigNumberFactorial(7), NumberAsArray{ 5, 0, 4, 0 }));
	EXPECT_TRUE(Comp(CalculateBigNumberFactorial(8), NumberAsArray{ 4, 0, 3, 2, 0 }));
	EXPECT_TRUE(Comp(CalculateBigNumberFactorial(9), NumberAsArray{ 3, 6, 2, 8, 8, 0 }));
	EXPECT_TRUE(Comp(CalculateBigNumberFactorial(10), NumberAsArray{ 3, 6, 2, 8, 8, 0, 0 }));
	EXPECT_TRUE(Comp(CalculateBigNumberFactorial(11), NumberAsArray{ 3, 9, 9, 1, 6, 8, 0, 0 }));
	EXPECT_TRUE(Comp(CalculateBigNumberFactorial(26), NumberAsArray{ 4,0,3,2,9,1,4,6,1,1,2,6,6,0,5,6,3,5,5,8,4,0,0,0,0,0,0 }));

}

TEST(InputCheckerTest, IsHighLevelOperation)
{
	EXPECT_TRUE(IsHighLevelOperation('*'));
	EXPECT_TRUE(IsHighLevelOperation('/'));
	EXPECT_FALSE(IsHighLevelOperation('+'));
	EXPECT_FALSE(IsHighLevelOperation('-'));
	EXPECT_FALSE(IsHighLevelOperation('1'));
	EXPECT_FALSE(IsHighLevelOperation('2'));
	EXPECT_FALSE(IsHighLevelOperation('3'));
	EXPECT_FALSE(IsHighLevelOperation('4'));
	EXPECT_FALSE(IsHighLevelOperation('5'));
	EXPECT_FALSE(IsHighLevelOperation('6'));
	EXPECT_FALSE(IsHighLevelOperation('7'));
	EXPECT_FALSE(IsHighLevelOperation('8'));
	EXPECT_FALSE(IsHighLevelOperation('9'));
	EXPECT_FALSE(IsHighLevelOperation('0'));
	EXPECT_FALSE(IsHighLevelOperation('a'));
	EXPECT_FALSE(IsHighLevelOperation(' '));
	EXPECT_FALSE(IsHighLevelOperation(""));
	EXPECT_TRUE(IsHighLevelOperation(std::string("*")));
	EXPECT_TRUE(IsHighLevelOperation(std::string("/")));
	EXPECT_FALSE(IsHighLevelOperation(std::string("+")));
	EXPECT_FALSE(IsHighLevelOperation(std::string("-")));
	EXPECT_FALSE(IsHighLevelOperation(std::string("1")));
	EXPECT_FALSE(IsHighLevelOperation(std::string("2")));
	EXPECT_FALSE(IsHighLevelOperation(std::string("3")));
	EXPECT_FALSE(IsHighLevelOperation(std::string("4")));
	EXPECT_FALSE(IsHighLevelOperation(std::string("5")));
	EXPECT_FALSE(IsHighLevelOperation(std::string("6")));
	EXPECT_FALSE(IsHighLevelOperation(std::string("7")));
	EXPECT_FALSE(IsHighLevelOperation(std::string("8")));
	EXPECT_FALSE(IsHighLevelOperation(std::string("9")));
	EXPECT_FALSE(IsHighLevelOperation(std::string("0")));
	EXPECT_FALSE(IsHighLevelOperation(std::string("a")));
	EXPECT_FALSE(IsHighLevelOperation(std::string(" ")));
	EXPECT_FALSE(IsHighLevelOperation(std::string("")));
}

TEST(InputCheckerTest, IsLowLevelOperation)
{
	EXPECT_TRUE(IsLowLevelOperation('+'));
	EXPECT_TRUE(IsLowLevelOperation('-'));
	EXPECT_FALSE(IsLowLevelOperation('*'));
	EXPECT_FALSE(IsLowLevelOperation('/'));
	EXPECT_FALSE(IsLowLevelOperation('1'));
	EXPECT_FALSE(IsLowLevelOperation('2'));
	EXPECT_FALSE(IsLowLevelOperation('3'));
	EXPECT_FALSE(IsLowLevelOperation('4'));
	EXPECT_FALSE(IsLowLevelOperation('5'));
	EXPECT_FALSE(IsLowLevelOperation('6'));
	EXPECT_FALSE(IsLowLevelOperation('7'));
	EXPECT_FALSE(IsLowLevelOperation('8'));
	EXPECT_FALSE(IsLowLevelOperation('9'));
	EXPECT_FALSE(IsLowLevelOperation('0'));
	EXPECT_FALSE(IsLowLevelOperation('a'));
	EXPECT_FALSE(IsLowLevelOperation(' '));
	EXPECT_FALSE(IsLowLevelOperation(""));
	EXPECT_TRUE(IsLowLevelOperation(std::string("+")));
	EXPECT_TRUE(IsLowLevelOperation(std::string("-")));
	EXPECT_FALSE(IsLowLevelOperation(std::string("*")));
	EXPECT_FALSE(IsLowLevelOperation(std::string("/")));
	EXPECT_FALSE(IsLowLevelOperation(std::string("1")));
	EXPECT_FALSE(IsLowLevelOperation(std::string("2")));
	EXPECT_FALSE(IsLowLevelOperation(std::string("3")));
	EXPECT_FALSE(IsLowLevelOperation(std::string("4")));
	EXPECT_FALSE(IsLowLevelOperation(std::string("5")));
	EXPECT_FALSE(IsLowLevelOperation(std::string("6")));
	EXPECT_FALSE(IsLowLevelOperation(std::string("7")));
	EXPECT_FALSE(IsLowLevelOperation(std::string("8")));
	EXPECT_FALSE(IsLowLevelOperation(std::string("9")));
	EXPECT_FALSE(IsLowLevelOperation(std::string("0")));
	EXPECT_FALSE(IsLowLevelOperation(std::string("a")));
	EXPECT_FALSE(IsLowLevelOperation(std::string(" ")));
	EXPECT_FALSE(IsLowLevelOperation(std::string("")));
}

TEST(InputCheckerTest, DoOperationTest)
{
	EXPECT_EQ(DoOperation(1, 1, "+"), 2);
	EXPECT_EQ(DoOperation(1, 1, "-"), 0);
	EXPECT_EQ(DoOperation(1, 1, "*"), 1);
	EXPECT_EQ(DoOperation(1, 1, "/"), 1);
	EXPECT_EQ(DoOperation(1, 2, "+"), 3);
	EXPECT_EQ(DoOperation(1, 2, "-"), -1);
	EXPECT_EQ(DoOperation(1, 2, "*"), 2);
	EXPECT_EQ(DoOperation(1, 2, "/"), 0.5);
	EXPECT_EQ(DoOperation(2, 1, "+"), 3);
	EXPECT_EQ(DoOperation(2, 1, "-"), 1);
	EXPECT_EQ(DoOperation(2, 1, "*"), 2);
	EXPECT_EQ(DoOperation(2, 1, "/"), 2);
	EXPECT_EQ(DoOperation(2, 2, "+"), 4);
	EXPECT_EQ(DoOperation(2, 2, "-"), 0);
	EXPECT_EQ(DoOperation(2, 2, "*"), 4);
	EXPECT_EQ(DoOperation(2, 2, "/"), 1);
	EXPECT_EQ(DoOperation(2, 3, "+"), 5);
	EXPECT_EQ(DoOperation(2, 3, "-"), -1);
	EXPECT_EQ(DoOperation(2, 3, "*"), 6);
	EXPECT_EQ(DoOperation(2, 3, "/"), 2.0 / 3.0);
	EXPECT_EQ(DoOperation(3, 2, "+"), 5);
	EXPECT_EQ(DoOperation(3, 2, "-"), 1);
	EXPECT_EQ(DoOperation(3, 2, "*"), 6);
	EXPECT_EQ(DoOperation(3, 2, "/"), 1.5);
	EXPECT_EQ(DoOperation(3, 3, "+"), 6);
	EXPECT_EQ(DoOperation(3, 3, "-"), 0);
	EXPECT_EQ(DoOperation(3, 3, "*"), 9);
	EXPECT_EQ(DoOperation(3, 3, "/"), 1);
	EXPECT_EQ(DoOperation(3, 4, "+"), 7);
	EXPECT_EQ(DoOperation(3, 4, "-"), -1);
}

TEST(InputCheckerTest, CreatePolishNotationExpression)
{
	EXPECT_TRUE(Comp(CreatePolishNotationExpression(std::vector<std::string>{"1", "+", "2"}), std::deque<std::string>{"1", "2", "+"}));
	EXPECT_TRUE(Comp(CreatePolishNotationExpression(std::vector<std::string>{"1", "-", "2"}), std::deque<std::string>{"1", "2", "-"}));
	EXPECT_TRUE(Comp(CreatePolishNotationExpression(std::vector<std::string>{"1", "*", "2"}), std::deque<std::string>{"1", "2", "*"}));
	EXPECT_TRUE(Comp(CreatePolishNotationExpression(std::vector<std::string>{"1", "/", "2"}), std::deque<std::string>{"1", "2", "/"}));
	EXPECT_TRUE(Comp(CreatePolishNotationExpression(std::vector<std::string>{"1", "+", "2", "+", "3"}), std::deque<std::string>{"1", "2", "3", "+", "+"}));
	EXPECT_TRUE(Comp(CreatePolishNotationExpression(std::vector<std::string>{"1", "+", "2", "-", "3"}), std::deque<std::string>{"1", "2", "3", "-", "+"}));
	EXPECT_TRUE(Comp(CreatePolishNotationExpression(std::vector<std::string>{"1", "+", "2", "*", "3"}), std::deque<std::string>{"1", "2", "3", "*", "+"}));
	EXPECT_TRUE(Comp(CreatePolishNotationExpression(std::vector<std::string>{"1", "+", "2", "/", "3"}), std::deque<std::string>{"1", "2", "3", "/", "+"}));
	EXPECT_TRUE(Comp(CreatePolishNotationExpression(std::vector<std::string>{"1", "-", "2", "+", "3"}), std::deque<std::string>{"1", "2", "3", "+", "-"}));
	EXPECT_TRUE(Comp(CreatePolishNotationExpression(std::vector<std::string>{"1", "-", "2", "-", "3"}), std::deque<std::string>{"1", "2", "3", "-", "-"}));
	EXPECT_TRUE(Comp(CreatePolishNotationExpression(std::vector<std::string>{"1", "-", "2", "*", "3"}), std::deque<std::string>{"1", "2", "3", "*", "-"}));
	EXPECT_TRUE(Comp(CreatePolishNotationExpression	(std::vector<std::string>{"(", "4", "-", "1", ")", "*", "9"}), std::deque<std::string>{"4", "1", "-", "9", "*"}));
	EXPECT_TRUE(Comp(CreatePolishNotationExpression(std::vector<std::string>{"(", "4", "-", "1", ")", "*", "(", "9", "+", "6", ")"}),
		std::deque<std::string>{"4", "1", "-", "9","6", "+", "*"}));
}

TEST(FunctionEvaluationTests, PrimeDividers)
{
	EXPECT_TRUE(Comp(GeneratePrimeDividers(10), std::deque{ 2ull,5ull }));
	EXPECT_TRUE(Comp(GeneratePrimeDividers(20), std::deque{ 2ull, 2ull, 5ull }));
	EXPECT_TRUE(Comp(GeneratePrimeDividers(173), std::deque{ 173ull }));
}

TEST(FunctionEvaluationTests, DivideTwoNumbers)
{
	EXPECT_TRUE(Comp(DivideTwoNumbers({ 2,2,2 }, 2u), std::deque{ 1u,1u,1u }));
	EXPECT_TRUE(Comp(DivideTwoNumbers({ 1,0,0 }, 2u), std::deque{ 5u,0u }));
	EXPECT_TRUE(Comp(DivideTwoNumbers({ 1,0,0 }, 10u), std::deque{ 1u, 0u }));
	EXPECT_TRUE(Comp(DivideTwoNumbers({ 6,2,5 }, 25u), std::deque{ 2u, 5u }));
	EXPECT_TRUE(Comp(DivideTwoNumbers({ 1,0,0,0 }, 25u), std::deque{ 4u, 0u }));

	EXPECT_TRUE(Comp(DivideTwoNumbers({ 2,5,2,5 }, 25u), std::deque{ 1u, 0u, 1u }));
	EXPECT_TRUE(Comp(DivideTwoNumbers({ 1,0,0,0,0,0,0 }, 1000u), std::deque{ 1u, 0u, 0u, 0u }));
}

TEST(FunctionEvaluationTests, IsDivisible)
{
	EXPECT_TRUE(IsDivisible({ 1,0,0 }, 2u));
	EXPECT_TRUE(IsDivisible({ 1,0,0 }, 10u));
	EXPECT_TRUE(IsDivisible({ 6,2,5 }, 25u));
	EXPECT_TRUE(IsDivisible({ 1,0,0,0 }, 25u));
	EXPECT_TRUE(IsDivisible({ 2,5,2,5 }, 25u));
	EXPECT_TRUE(IsDivisible({ 1,0,0,0,0,0,0 }, 1000u));
	EXPECT_FALSE(IsDivisible({ 1,0,0 }, 3u));
	EXPECT_TRUE(IsDivisible({ 1,0,0 }, 5u));
	EXPECT_FALSE(IsDivisible({ 6,2,5 }, 3u));
	EXPECT_FALSE(IsDivisible({ 1,0,0,0 }, 7u));
	EXPECT_FALSE(IsDivisible({ 2,5,2,5 }, 3u));
	EXPECT_FALSE(IsDivisible({ 1,0,0,0,0,0,0 }, 7u));
}


TEST(FunctionEvaluationTests, ShrinkTwoNumbers)
{
	const auto res1 = ShrinkTwoNumbers({ 1,0,0 }, { 2,5 });
	const auto res2 = ShrinkTwoNumbers({ 1, 0, 0, 0 }, { 1, 0, 0, 0 });
	const auto res3 = ShrinkTwoNumbers({ 1, 0, 0, 0 }, { 1, 0, 0, 0, 0 });
	EXPECT_TRUE(Comp(res1.first, std::deque{ 4 }));
	EXPECT_TRUE(Comp(res1.second, std::deque{ 1 }));
	EXPECT_TRUE(Comp(res2.first, std::deque{ 1 }));
	EXPECT_TRUE(Comp(res2.second, std::deque{ 1 }));
	EXPECT_TRUE(Comp(res3.first, std::deque{ 1 }));
	EXPECT_TRUE(Comp(res3.second, std::deque{ 1, 0 }));
}

TEST(FunctionEvaluationTests, GetBinom)
{
	EXPECT_TRUE(Comp(GetBinom("2,1"), std::deque{ 2 }));
	EXPECT_TRUE(Comp(GetBinom("10,5"), std::deque{ 2,5,2 }));
	EXPECT_TRUE(Comp(GetBinom("39,7"), std::deque{ 1,5,3,8,0,9,3,7}));
	//EXPECT_TRUE(Comp(GetBinom("115,42"), std::deque{ 115, 42 }));
	//EXPECT_TRUE(Comp(GetBinom("91,91"), std::deque{ 91, 91 }));
	//EXPECT_TRUE(Comp(GetBinom("91,91,91"), std::deque{ 91, 91 }));
	//EXPECT_TRUE(Comp(GetBinom("91,91,91111"), std::deque{ 91, 91 }));
	//EXPECT_TRUE(Comp(GetBinom("91,91,91123123"), std::deque{ 91, 91 }));
	//EXPECT_TRUE(Comp(GetBinom("91,91,9144411,124494"), std::deque{ 91, 91 }));
}

int RunAllTests()
{
	testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}
