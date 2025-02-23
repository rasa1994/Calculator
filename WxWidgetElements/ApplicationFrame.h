#pragma once
import Constants;
#include "DigitButton.h"
#include "InputField.h"
class ApplicationFrame : public wxFrame
{
public:
	ApplicationFrame();
private:
	void WriteCorrectVersion(long double result);
	std::vector<std::shared_ptr<DigitButton>> m_buttons;
	std::shared_ptr<InputField> m_inputResult;
	std::string m_expression;
	void OnHello(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnClickHandler(wxCommandEvent& event);
	void CreateButtons(); // Move to special class
	void DeleteButtons(); // Move to special class
	void CreateInputs();
	void HandleOperation(MyConstants::Buttons buttonClicked);
};