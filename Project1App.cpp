//---------------------------------------------------------------------------
//
// Name:        Project1App.cpp
// Author:      Weronika, Dominika, Alicja
// Created:     2016-12-23 22:00:56
// Description: 
//
//---------------------------------------------------------------------------

#include "Project1App.h"
#include "Project1Frm.h"

IMPLEMENT_APP(Project1FrmApp)

bool Project1FrmApp::OnInit()
{
    //wxMessageOutputDebug().Printf("i dam.");
    Project1Frm* frame = new Project1Frm(NULL);
    SetTopWindow(frame);
    frame->Show();
    
    return true;
}
 
int Project1FrmApp::OnExit()
{
	return 0;
}
