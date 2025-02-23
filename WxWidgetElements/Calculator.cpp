import FunctionEvaluation;
import InputChecker;
import <wx/wxprec.h>;
#ifndef WX_PRECOMP
import <wx/wx.h>;
#endif
#include "Application.h"
int main(int argc, char* argv[])
{
	wxApp::SetInstance(new Application());
	const auto instance = wxApp::GetInstance();
	wxEntryStart(argc, argv);
	instance->CallOnInit();
	instance->OnRun();
	instance->OnExit();
	wxEntryCleanup();
	return 0;
}