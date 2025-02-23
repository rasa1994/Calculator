#pragma once
#include <functional>

class DigitButton : public wxButton
{
public:
	DigitButton(wxFrame* frame, unsigned int sizeX, unsigned int sizeY, unsigned int posX, unsigned int posY, const std::string& text, unsigned int id);
	DigitButton(wxFrame* frame, const wxSize& size, const wxPoint& pos, const std::string& text, unsigned int id);
	~DigitButton() override;
	void RegisterClick(const std::function<void(wxCommandEvent& event)>& buttonClick);

	DigitButton(const DigitButton&) = delete;
	DigitButton& operator=(const DigitButton&) = delete;
	DigitButton(DigitButton&&) = delete;
	DigitButton& operator=(DigitButton&&) = delete;
private:
	unsigned int m_id;
	std::string m_text;
	std::function<void(wxCommandEvent& event)> m_onClick;
	void TestFunctionOnClick(wxCommandEvent& event);
};
