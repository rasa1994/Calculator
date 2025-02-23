export module Constants;
import <array>;
import <vector>;
import <unordered_map>;
import <string>;
export
{
	namespace MyConstants
	{
#pragma region Screen
		constexpr uint16_t ScreenSizeX{ 800 };
		constexpr uint16_t ScreenSizeY{ 600 };
#pragma endregion

#pragma region Button
		constexpr uint16_t NumberOfButtonsHorizontal{ 3 };
		constexpr uint16_t NumberOfButtonsVertical{ 9 };
		constexpr uint16_t TotalNumberOfButtons{ NumberOfButtonsHorizontal * NumberOfButtonsVertical };
		constexpr uint16_t StartingButtonId{ 100 };
		constexpr uint16_t ButtonOffsetTop{ 200 };
		constexpr uint16_t ButtonOffsetLeft{ 120 };
		constexpr uint16_t ButtonOffsetRight{ 120 };
		constexpr uint16_t ButtonOffsetBottom{ 100 };
		constexpr uint16_t ButtonSpacingX{ 10 };
		constexpr uint16_t ButtonSpacingY{ 10 };
		constexpr uint16_t MinimumButtonSize{ 20 };

		enum Buttons : uint16_t
		{
			BUTTON_0 = StartingButtonId,
			BUTTON_1,
			BUTTON_2,
			BUTTON_3,
			BUTTON_4,
			BUTTON_5,
			BUTTON_6,
			BUTTON_7,
			BUTTON_8,
			BUTTON_9,
			BUTTON_PLUS,
			BUTTON_MINUS,
			BUTTON_MULTIPLY,
			BUTTON_DIVIDE,
			BUTTON_EQUAL,
			BUTTON_CLEAR,
			BUTTON_DELETE,
			BUTTON_SQRT,
			BUTTON_LEFT_PARENTHESIS,
			BUTTON_RIGHT_PARENTHESIS,
			BUTTON_DOT,
			BUTTON_SQUARE,
			BUTTON_FACTORIAL,
			BUTTON_BINOM_FORMULA,
			BUTTON_COMA,
			BUTTON_LAST, // Do not use this one
			BUTTON_COUNT = BUTTON_LAST - BUTTON_0
		};

		struct ButtonInfo
		{
		public:
			Buttons m_button;
			std::string m_text;
			ButtonInfo(Buttons button, const std::string& text) : m_button(button), m_text(text)
			{

			}
		};

		constexpr std::array ButtonArrangement =
		{
			BUTTON_DIVIDE,	          BUTTON_SQRT,               BUTTON_EQUAL,
			BUTTON_PLUS,	          BUTTON_MINUS,              BUTTON_MULTIPLY,
			BUTTON_LEFT_PARENTHESIS,  BUTTON_RIGHT_PARENTHESIS,  BUTTON_FACTORIAL,
			BUTTON_7,                 BUTTON_8,                  BUTTON_9,
			BUTTON_4,                 BUTTON_5,                  BUTTON_6,
			BUTTON_1,                 BUTTON_2,                  BUTTON_3,
			BUTTON_CLEAR,             BUTTON_0,                  BUTTON_DELETE,
			BUTTON_DOT,               BUTTON_SQUARE,             BUTTON_BINOM_FORMULA,
			BUTTON_COMA
		};

		const std::unordered_map<Buttons, std::string> ButtonTexts
		{
			{BUTTON_0,                          "0"},
			{BUTTON_1,                          "1"},
			{BUTTON_2,                          "2"},
			{BUTTON_3,                          "3"},
			{BUTTON_4,                          "4"},
			{BUTTON_5,                          "5"},
			{BUTTON_6,                          "6"},
			{BUTTON_7,                          "7"},
			{BUTTON_8,                          "8"},
			{BUTTON_9,                          "9"},
			{BUTTON_DIVIDE,                     "/"},
			{BUTTON_SQRT,                    "SQRT"},
			{BUTTON_EQUAL,                      "="},
			{BUTTON_PLUS,                       "+"},
			{BUTTON_MINUS,                      "-"},
			{BUTTON_MULTIPLY,                   "*"},
			{BUTTON_CLEAR,                      "C"},
			{BUTTON_DELETE,                   "DEL"},
			{BUTTON_LEFT_PARENTHESIS,           "("},
			{BUTTON_RIGHT_PARENTHESIS,          ")"},
			{BUTTON_FACTORIAL,          "FACTORIAL"},
			{BUTTON_DOT,                        "."},
			{BUTTON_SQUARE,                   "SQR"},
			{BUTTON_BINOM_FORMULA,       "(N)\n(M)"},
			{BUTTON_COMA,                       ","}
		};


#pragma endregion

#pragma region Input
		constexpr uint16_t StartingInputId{ 500 };
		constexpr uint16_t InputSizeX{ 400 };
		constexpr uint16_t InputSizeY{ 50 };
		constexpr uint16_t InputTopOffset{ 50 };
#pragma endregion

#pragma region ERRORS
		const std::string WRONG_OPERATION = "WRONG OPERATION PROVIDED. PROVIDE STRING WITH LENGTH 1!";
		const std::string INVALID_PARENTHESIS = "PLEASE CHECK YOUR PARENTHESIS";
		const std::string INVALID_EVALUATION = "EXPRESSION COULD NOT BE EVALUATED";
#pragma endregion
	}
}
