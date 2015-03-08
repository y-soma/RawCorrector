#include "MainDialog.h"

/*****************************************************************************\
	[Function]
		_tWinMain
	[Purpose]
		Application Entry Point
	[Parameter1] hInstance
		Instance Handle
	[Parameter2] hPrevInstance
		Instance Handle2(NULL)
	[Parameter3] lpCmdLine
		Commandline Parameter
	[Parameter4] nCmdShow
		Window Parameter
	[Returns]
		FALSE
\*****************************************************************************/
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	CMainDialog dlg;
	return dlg.DoModal(hInstance);
}
