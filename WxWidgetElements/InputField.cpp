import Constants;
import <wx/wxprec.h>;

#ifndef WX_PRECOMP
import <wx/wx.h>;
#endif // !WX_PRECOMP

#include "InputField.h"

unsigned int InputField::m_InputsId = MyConstants::StartingInputId;

InputField::InputField(wxFrame* frame, unsigned int sizeX, unsigned int sizeY, unsigned int posX, unsigned int posY)
	: wxTextCtrl(frame, ++m_InputsId, "", wxPoint(posX, posY), wxSize(sizeX, sizeY)), m_text(""), m_id(m_InputsId)
{
}



InputField::InputField(wxFrame* frame, const wxSize& size, const wxPoint& pos)
	: wxTextCtrl(frame, ++m_InputsId, "", pos, size), m_text(""), m_id(m_InputsId)
{
}



void InputField::SetText(std::string_view text) noexcept
{
	m_text = text;
	__super::Clear();
	AppendText(m_text);
}



void InputField::ClearLast() noexcept
{
	m_text.pop_back();
	__super::Clear();
	AppendText(m_text);
}



void InputField::ClearText() noexcept
{
	m_text.clear();
	__super::Clear();
}



void InputField::AddText(std::string_view text) noexcept
{
	m_text.append(text);
	__super::Clear();
	AppendText(m_text);
}