import FunctionEvaluation;
import InputChecker;
import Constants;
import <wx/wxprec.h>;

#ifndef WX_PRECOMP
import <wx/wx.h>;
#endif // !WX_PRECOMP


import <vector>;
import <memory>;
#include "DigitButton.h"

DigitButton::DigitButton(wxFrame* frame, unsigned int sizeX, unsigned int sizeY, unsigned int posX, unsigned int posY, const std::string& text, unsigned int id) :
	wxButton(frame, id, text, wxPoint(posX, posY), wxSize(sizeX, sizeY)), m_id(id), m_text(text)
{

}

DigitButton::DigitButton(wxFrame* frame, const wxSize& size, const wxPoint& pos, const std::string& text, unsigned int id) :
	wxButton(frame, id, text, pos, size), m_id(id), m_text(text)
{

}

DigitButton::~DigitButton()
{
	Unbind(wxEVT_BUTTON, m_onClick, m_id);
}

void DigitButton::RegisterClick(const std::function<void(wxCommandEvent& event)>& buttonClick)
{
	m_onClick = buttonClick;
	Bind(wxEVT_BUTTON, m_onClick, m_id);
}
