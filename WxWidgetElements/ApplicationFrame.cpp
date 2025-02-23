import FunctionEvaluation;
import InputChecker;
import Constants;
import <wx/wxprec.h>;

#ifndef WX_PRECOMP
import <wx/wx.h>;
#endif // !WX_PRECOMP


import <vector>;
import <memory>;
#include "ApplicationFrame.h"


ApplicationFrame::ApplicationFrame() : wxFrame(nullptr, wxID_ANY, "HELLO WORLD", wxPoint(0, 0), wxSize(MyConstants::ScreenSizeX, MyConstants::ScreenSizeY))
{
	wxMenu* menuFile = new wxMenu;
//	menuFile->Append(ID_Hello, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);

	wxMenu* menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);
	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&File");
	menuBar->Append(menuHelp, "&Help");

	SetMenuBar(menuBar);
	CreateStatusBar();
	SetStatusText("Welcome to wxWidgets");

	//Bind(wxEVT_MENU, &ApplicationFrame::OnHello, this, ID_Hello);
	Bind(wxEVT_MENU, &ApplicationFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &ApplicationFrame::OnExit, this, wxID_EXIT);

	CreateButtons();
	CreateInputs();
}



void ApplicationFrame::WriteCorrectVersion(long double result)
{
	if (NumberHasOnlyZerosAfterDot(result))
	{
		m_inputResult->SetText(std::to_string(static_cast<long long>(result)));
		m_expression = std::to_string(static_cast<long long>(result));
	}
	else
	{
		m_inputResult->SetText(std::to_string(result));
		m_expression = std::to_string(result);
	}
}



void ApplicationFrame::OnHello(wxCommandEvent& event)
{
	wxLogMessage("Hello wxWidget");
}

void ApplicationFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("This is a wxWidget Hello world example", "About hello world", wxOK | wxICON_INFORMATION);
}

void ApplicationFrame::OnExit(wxCommandEvent& event)
{
	DeleteButtons();
	Close(true);
}

void ApplicationFrame::OnClickHandler(wxCommandEvent& event)
{
	
}

void ApplicationFrame::CreateButtons()
{
	// Calculate button size using predefined values 
	unsigned int sizeX = (MyConstants::ScreenSizeX - 
		(MyConstants::ButtonSpacingX * MyConstants::NumberOfButtonsHorizontal) -
		MyConstants::ButtonOffsetLeft - MyConstants::ButtonOffsetRight) / MyConstants::NumberOfButtonsHorizontal;

	if (sizeX < MyConstants::MinimumButtonSize)
	{
		// Add some assert here
		return;
	}

	unsigned int sizeY = (MyConstants::ScreenSizeY -
		(MyConstants::ButtonSpacingY * MyConstants::NumberOfButtonsVertical) -
		MyConstants::ButtonOffsetTop - MyConstants::ButtonOffsetBottom) / MyConstants::NumberOfButtonsVertical;

	if (sizeY < MyConstants::MinimumButtonSize)
	{
		// Add some assert here
		return;
	}

	//if (MyConstants::TotalNumberOfButtons <= MyConstants::Buttons::BUTTON_COUNT || MyConstants::TotalNumberOfButtons <= MyConstants::ButtonTexts.size())
	//{
	//	std::cout << "PROBLEM WITH NUMBER OF BUTTONS" << std::endl;
	//	// ADD other assert here
	//	return;
	//}


	for (unsigned int buttonX = 0; buttonX < MyConstants::NumberOfButtonsHorizontal; buttonX++)
	{
		for (unsigned int buttonY = 0; buttonY < MyConstants::NumberOfButtonsVertical; buttonY++)
		{
			unsigned int posX = buttonX * sizeX + MyConstants::ButtonOffsetLeft + buttonX * MyConstants::ButtonSpacingX;
			unsigned int posY = buttonY * sizeY + MyConstants::ButtonOffsetTop + buttonY * MyConstants::ButtonSpacingY;

			const unsigned int buttonPositionInArray = buttonX + buttonY * MyConstants::NumberOfButtonsHorizontal;

			if (buttonPositionInArray >= MyConstants::ButtonArrangement.size())
				break;

			const auto& buttonInfo = MyConstants::ButtonArrangement[buttonPositionInArray];

			std::shared_ptr<DigitButton> button = std::make_shared<DigitButton>(this, sizeX, sizeY, posX, posY, MyConstants::ButtonTexts.at(buttonInfo), buttonInfo);
			button->RegisterClick([this](wxCommandEvent& event) 
				{ 
					HandleOperation(static_cast<MyConstants::Buttons>(event.GetId()));
				});

			m_buttons.push_back(button);
		}
	}
}

void ApplicationFrame::DeleteButtons()
{
	m_buttons.clear();
}

void ApplicationFrame::CreateInputs()
{
	unsigned int positionX = (MyConstants::ScreenSizeX - MyConstants::InputSizeX) / 2;
	unsigned int positionY = MyConstants::InputTopOffset;
	m_inputResult = std::make_shared<InputField>(this, wxSize(MyConstants::InputSizeX, MyConstants::InputSizeY), wxPoint(positionX, positionY));
}

void ApplicationFrame::HandleOperation(MyConstants::Buttons buttonClicked)
{
	switch (buttonClicked)
	{
	case MyConstants::BUTTON_0:
	case MyConstants::BUTTON_1:
	case MyConstants::BUTTON_2:
	case MyConstants::BUTTON_3:
	case MyConstants::BUTTON_4:
	case MyConstants::BUTTON_5:
	case MyConstants::BUTTON_6:
	case MyConstants::BUTTON_7:
	case MyConstants::BUTTON_8:
	case MyConstants::BUTTON_9:
	{
		std::string_view operation = MyConstants::ButtonTexts.at(buttonClicked);
		m_inputResult->AddText(operation);
		m_expression.append(operation);
	}break;

	case MyConstants::BUTTON_PLUS:
	case MyConstants::BUTTON_MINUS:
	case MyConstants::BUTTON_MULTIPLY:
	case MyConstants::BUTTON_DIVIDE:
	{
		std::string_view operation = MyConstants::ButtonTexts.at(buttonClicked);
		m_inputResult->AddText(operation);
		m_expression.append(operation);
	}break;
	case MyConstants::BUTTON_EQUAL:
	{
		try
		{
			const auto result = GetResult(m_expression);
			WriteCorrectVersion(result);
		}
		catch (const std::exception& e)
		{
			//HelperClass::ShowError(e.what());
		}		
	}break;
	case MyConstants::BUTTON_CLEAR:
	{
		if (m_expression.empty())
			return;
		m_inputResult->ClearLast();
		m_expression.pop_back();
	}break;
	case MyConstants::BUTTON_DELETE:
	{
		if (m_expression.empty())
			return;
		m_inputResult->ClearText();
		m_expression.clear();
	}break;
	case MyConstants::BUTTON_SQRT:
	{
		try
		{
			auto result = GetResult(m_expression);
			result = std::sqrt(result);
			WriteCorrectVersion(result);
		}
		catch (const std::exception& e)
		{
			//HelperClass::ShowError(e.what());
		}
	}break;
	case MyConstants::BUTTON_LEFT_PARENTHESIS:
	case MyConstants::BUTTON_RIGHT_PARENTHESIS:
	{
		std::string operation = MyConstants::ButtonTexts.at(buttonClicked);
		if (CheckAddingParenthesis(m_expression, operation))
		{
			m_inputResult->AddText(operation);
			m_expression.append(operation);
		}
	}break;
	case MyConstants::BUTTON_SQUARE:
	{
		try
		{
			auto result = GetResult(m_expression);
			result = std::sqrt(result);
			WriteCorrectVersion(result);
		}
		catch (const std::exception& e)
		{
			//HelperClass::ShowError(e.what());
		}
		
	}break;
	case MyConstants::BUTTON_DOT:
	{
		if (CanDotBetAdded(m_expression))
		{
			std::string_view operation = MyConstants::ButtonTexts.at(buttonClicked);
			m_inputResult->AddText(operation);
			m_expression.append(operation);
		}
	}
	case MyConstants::BUTTON_COMA:
	{
		std::string_view operation = MyConstants::ButtonTexts.at(buttonClicked);
		m_inputResult->AddText(operation);
		m_expression.append(operation);
	}break;
	case MyConstants::BUTTON_BINOM_FORMULA:
	{
		auto result = GetBinom(m_expression);
		m_inputResult->ClearText();
		m_expression.clear();
		for (auto v : result)
		{
			m_inputResult->AddText(std::to_string(v));
			m_expression.append(std::to_string(v));
		}
	}break;
	case MyConstants::BUTTON_FACTORIAL:
	{
		try
		{
			auto result = GetResult(m_expression);
			auto resultLong = CalculateBigNumberFactorial(std::floor(result));
			m_inputResult->ClearText();
			m_expression.clear();
			for (const auto character : resultLong)
			{
				m_inputResult->AddText(std::to_string(character));
				m_expression.append(std::to_string(character));
			}
		}
		catch (const std::exception& e)
		{
			//HelperClass::ShowError(e.what());
		}
	}break;
	default:
		break;
	}
}