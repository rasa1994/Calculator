import <wx/wxprec.h>;

#ifndef WX_PRECOMP
import <wx/wx.h>;
#endif // !W

#include "Application.h"
#include "ApplicationFrame.h"

bool Application::OnInit()
{
	ApplicationFrame* frame = new ApplicationFrame();
	frame->Show(true);
	return true;
}