#include <windows.h>

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//create the main window
	CreateWindowEx(	
		0, // for now supply this 0
		WC_DIALOG, // window class name, predefined constant WC_DIALOG is used to create dialog boxes
		"My Window", // title text of the window
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, // style -WS_VISIBLE means make this window visible
		400, // X coordinates on screen
		100, // Y coordinates on screen
		200, // Width of the window in pixels
		200, // Height of the window in pixels
		NULL, // parent window handle - for now supply NULL
		NULL, //	- do -
		NULL, //	- do -
		NULL  //	- do -
	);
	
	//display a message box
	MessageBox(
		NULL, // parent window handle, supply NULL for fow
		"Am message", // message that is displayed
		"Am title",	// title of the message box
		0// style - supply 0 for now, means no style
	);
	return 0;
}
