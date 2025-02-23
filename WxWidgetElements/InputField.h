#pragma once

class InputField : public wxTextCtrl
{
public:
	InputField(wxFrame* frame, unsigned int sizeX, unsigned int sizeY, unsigned int posX, unsigned int posY);
	InputField(wxFrame* frame, const wxSize& size, const wxPoint& pos);
	~InputField() override = default;
	const std::string& GetText() const noexcept { return m_text; }
	void SetText(std::string_view text) noexcept;
	void ClearLast() noexcept;
	void ClearText() noexcept;
	void AddText(std::string_view text) noexcept;

	InputField(const InputField&) = delete;
	InputField& operator=(const InputField&) = delete;
	InputField(InputField&&) = delete;
	InputField& operator=(InputField&&) = delete;
private:
	std::string m_text;
	static unsigned int m_InputsId;
	unsigned int m_id;
};