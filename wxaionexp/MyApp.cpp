// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include "MyApp.h"
#include "MyFrame.h"
//#include "noname.h"

wxIMPLEMENT_APP(MyApp);



bool MyApp::OnInit()
{
	MyFrame *frame = new MyFrame(string(APP_TITLE) + " " + string(APP_VERSION), wxPoint(-1, -1), wxSize(FRAME_WIDTH, FRAME_HEIGHT) );
	
	//MyFrame3 *frame = new MyFrame3( "Hello World", wxPoint(50, 50), wxSize(250, 100) );
	frame->Show( true );


	return true;
}
