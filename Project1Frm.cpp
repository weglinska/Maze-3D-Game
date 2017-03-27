///-----------------------------------------------------------------
///
/// @file      Project1Frm.cpp
/// @author    Weronika, Dominika, Alicja
/// Created:   2016-12-23 22:00:56
/// @section   DESCRIPTION
///            Project1Frm class implementation
///
///------------------------------------------------------------------

#include "Project1Frm.h"
#include <iostream>

//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// Project1Frm
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(Project1Frm,wxFrame)
	////Manual Code Start
	EVT_KEY_DOWN(Project1Frm::OnKeyDown)
	EVT_KEY_UP(Project1Frm::OnKeyUp)
	////Manual Code End
	
	EVT_CLOSE(Project1Frm::OnClose)
	EVT_CHECKBOX(ID_MINIMAP,Project1Frm::MiniMapClick)
	
	EVT_COMMAND_SCROLL(ID_FOVSLIDER,Project1Frm::FOVSliderScroll)
	EVT_BUTTON(ID_EXITBUTTON,Project1Frm::ExitButtonClick)
	EVT_BUTTON(ID_LOADBUTTON,Project1Frm::LoadButtonClick)
	EVT_BUTTON(ID_STARTBUTTON,Project1Frm::StartButtonClick)
    EVT_TIMER(TIMER_ID,Project1Frm::OnTimerTimeout)
END_EVENT_TABLE()
////Event Table End

Project1Frm::Project1Frm(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

Project1Frm::~Project1Frm()
{
}

void Project1Frm::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	WxBoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizer(WxBoxSizer1);
	this->SetAutoLayout(true);

	DrawPanel = new wxPanel(this, ID_DRAWPANEL, wxPoint(5, 5), wxSize(650, 500));
	WxBoxSizer1->Add(DrawPanel, 1, wxALIGN_CENTER | wxEXPAND | wxALL, 5);

	WxBoxSizer2 = new wxBoxSizer(wxVERTICAL);
	WxBoxSizer1->Add(WxBoxSizer2, 0, wxALIGN_CENTER | wxALL, 5);

	StartButton = new wxButton(this, ID_STARTBUTTON, _("Start"), wxPoint(5, 5), wxSize(150, 25), 0, wxDefaultValidator, _("StartButton"));
	WxBoxSizer2->Add(StartButton, 0, wxALIGN_CENTER | wxALL, 5);

	LoadButton = new wxButton(this, ID_LOADBUTTON, _("Wybierz planszê"), wxPoint(5, 40), wxSize(150, 25), 0, wxDefaultValidator, _("LoadButton"));
	WxBoxSizer2->Add(LoadButton, 0, wxALIGN_CENTER | wxALL, 5);

	ExitButton = new wxButton(this, ID_EXITBUTTON, _("Zakoñcz"), wxPoint(5, 75), wxSize(150, 25), 0, wxDefaultValidator, _("ExitButton"));
	WxBoxSizer2->Add(ExitButton, 0, wxALIGN_CENTER | wxALL, 5);

	Timer = new wxStaticText(this, ID_TIMER, _("Czas gry:"), wxPoint(54, 131), wxDefaultSize, 0, _("Timer"));
	WxBoxSizer2->Add(Timer, 0, wxALIGN_CENTER | wxALL, 5);

	Time = new wxStaticText(this, ID_TIME, _("00:00"), wxPoint(45, 139), wxDefaultSize, 0, _("Time"));
	Time->SetFont(wxFont(20, wxSWISS, wxNORMAL, wxNORMAL, false));
	WxBoxSizer2->Add(Time, 0, wxALIGN_CENTER | wxALL, 5);

	FOVText = new wxStaticText(this, ID_FOVTEXT, _("FOV: 60°"), wxPoint(65, 190), wxDefaultSize, 0, _("FOVText"));
	WxBoxSizer2->Add(FOVText, 0, wxALIGN_CENTER | wxALL, 5);

	FOVSlider = new wxSlider(this, ID_FOVSLIDER, 45, 45, 120, wxPoint(5, 219), wxSize(150, 45), wxSL_HORIZONTAL | wxSL_SELRANGE , wxDefaultValidator, _("FOVSlider"));
	FOVSlider->SetRange(45,120);
	FOVSlider->SetValue(45);
	WxBoxSizer2->Add(FOVSlider, 0, wxALIGN_CENTER | wxALL, 5);

	MiniMap = new wxCheckBox(this, ID_MINIMAP, _(" Minimapka"), wxPoint(31, 274), wxSize(97, 17), 0, wxDefaultValidator, _("MiniMap"));
	WxBoxSizer2->Add(MiniMap, 0, wxALIGN_CENTER | wxALL, 5);

	WxOpenFileDialog =  new wxFileDialog(this, _("Choose a file"), _(""), _(""), _("*.map"), wxFD_OPEN);
	
	m_pTimer = new wxTimer(this,TIMER_ID);

	m_pTimer->Start(1000);      
	double m_nCountDown=50;

	SetTitle(_("Labirynt 3D"));
	SetIcon(wxNullIcon);
	
	Layout();
	GetSizer()->Fit(this);
	GetSizer()->SetSizeHints(this);
	Center();
	
	////GUI Items Creation End

	WxMessageDialog1 =  new wxMessageDialog(this, _(""), _("Uwaga!"));
	
	FOVSlider->SetValue(60);
	FOV = (double) FOVSlider->GetValue();
	
	UP = 0;
    DOWN = 0;
    LEFT = 0;
    RIGHT = 0;
    SHIFT = 0;
    
    canPlay = false;
    drawMiniMap=false;
    map=NULL;
    extraSpeed=false;

    
}

void Project1Frm::OnClose(wxCloseEvent& event)
{
	Destroy();
}

void Project1Frm::StartGame(){
    canPlay = true;
    map = new MapReader(pathToMap);
    
    posX = map->getPlayerPosX() + 0.5 - 1;
	posY = map->getPlayerPosY() + 0.5;

	dirX = -1;
	dirY = 0;
	planeX = 0;
	planeY = tan((FOV / 2 * M_PI) / 180);
    extraSpeed=false;
	
	startTime= time(0);
	m_pTimer->Start(100);      
	FOVSlider->Enable(false);
		
	draw();
}

void Project1Frm::StartButtonClick(wxCommandEvent& event)
{
    if(pathToMap.empty()){
        WxMessageDialog1->SetMessage(_("Nale¿y wybraæ planszê przed rozpoczêciem gry!"));
        WxMessageDialog1->ShowModal();
        return;
    }
    StartGame();
    
}


void Project1Frm::LoadButtonClick(wxCommandEvent& event)
{
    m_pTimer->Stop();     
    if (WxOpenFileDialog->ShowModal() == wxID_OK)
    {
        wxString in = WxOpenFileDialog->GetPath();
        pathToMap = in.ToStdString();     
    }
}


void Project1Frm::ExitButtonClick(wxCommandEvent& event)
{
    canPlay = false;
    if (map!=NULL)
    {
        WxMessageDialog1->SetMessage(_("Nie uda³ol Ci siê znaleŸæ wyjœcia!"));
        WxMessageDialog1->ShowModal();
        m_pTimer->Stop();      
        delete map;
    }
    else
    {
        WxMessageDialog1->SetMessage(_("Nie mo¿na zakoñczyæ gry przed jej rozpoczêciem!"));
        WxMessageDialog1->ShowModal();
    }
    FOVSlider->Enable(true);

}

void Project1Frm::OnTimerTimeout(wxTimerEvent& event)
{
    if (canPlay)
    {
        time_t endTime;
        struct tm * timeinfo;
        char buffer[80];
            
        time (&endTime);
        endTime += 86400;
        time_t diffTime = difftime (endTime, startTime);
        timeinfo = localtime(&diffTime);
            
        strftime(buffer,80,"%M:%S",timeinfo);
        std::string str(buffer);
        Time->SetLabel(str);
    }
}

void Project1Frm::FOVSliderScroll(wxScrollEvent& event)
{
    FOV = (double)FOVSlider->GetValue();
    this->SetFocusIgnoringChildren();
    
    int x=FOVSlider->GetValue();
    std::string str;
    std::ostringstream temp;
    temp<<x;
    str=temp.str();
    FOVText->SetLabel("FOV: "+str+"°");
}


void Project1Frm::MiniMapClick(wxCommandEvent& event)
{
    if(pathToMap.empty() || !canPlay){
        MiniMap->SetValue(false);
        WxMessageDialog1->SetMessage(_("Nale¿y najpierw rozpocz¹æ grê!"));
        WxMessageDialog1->ShowModal();
        return;
    }
	drawMiniMap = MiniMap->GetValue();
	this->SetFocusIgnoringChildren();
	draw();
}

void Project1Frm::OnKeyDown(wxKeyEvent& event) {
    if(canPlay) {
        
        UP = event.GetKeyCode() == WXK_UP;
        DOWN = event.GetKeyCode() == WXK_DOWN;
        LEFT = event.GetKeyCode() == WXK_LEFT;
        RIGHT = event.GetKeyCode() == WXK_RIGHT;
        SHIFT = event.GetKeyCode() == WXK_SHIFT;

        draw();
    }
}

void Project1Frm::OnKeyUp(wxKeyEvent& event) {

}

void Project1Frm::draw() 
{    

    int w, h;

	DrawPanel->GetSize(&w, &h);
	
	rotSpeed = 0.1;
	moveSpeed = 0.25;
	
	wxClientDC dc_org(DrawPanel);
	wxBufferedDC dc(&dc_org);

	dc.Clear();

    dc.SetPen(wxPen(wxColour(186, 232, 252)));
    dc.SetBrush(wxBrush(wxColour(186, 232, 252)));
    dc.DrawRectangle(0, 0, w, h/2);


    dc.SetPen(wxPen(wxColour(51, 149, 107)));
    dc.SetBrush(wxBrush(wxColour(51, 149, 107)));
    dc.DrawRectangle(0, h/2, w, h/2);

	if (SHIFT) 
	{
        extraSpeed=(!extraSpeed);
	}
	
	if (extraSpeed)
			moveSpeed *= 2;

	if(LEFT) 
	{       
        double oldDirX = dirX;
        dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
        dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
      
        double oldPlaneX = planeX;
        planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
        planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
        LEFT=0;
    }

    if(RIGHT) 
    {           
        double oldDirX = dirX;
        dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
        dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
      
        double oldPlaneX = planeX;
        planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
        planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
        RIGHT=0;
    }

    if(UP) 
    {
        if(map->getElement(int(posX + dirX * moveSpeed), int(posY)) == false) {
            posX += dirX * moveSpeed;
        }
      
        if(map->getElement(int(posX), int(posY + dirY * moveSpeed)) == false) {
            posY += dirY * moveSpeed;
        }

		// warunek wyjscia z labirytnu
		if (map->getElement(int(posX + dirX * moveSpeed), int(posY)) == 2 ||
			map->getElement(int(posX), int(posY + dirY * moveSpeed)) == 2) {
        	wxString result = Time->GetLabel();
            m_pTimer->Stop();      
			WxMessageDialog1->SetMessage(_("Koniec gry!\nTwój czas: " + result));
            WxMessageDialog1->ShowModal();
            canPlay=false;
            FOVSlider->Enable(true);
            dc.Clear();
		}
		UP=0;
    }

    if(DOWN) 
    {
        if (map->getElement(int(posX - dirX * moveSpeed), int(posY)) == false) {
            posX -= dirX * moveSpeed;
        }
      
        if(map->getElement(int(posX), int(posY - dirY * moveSpeed)) == false) {
            posY -= dirY * moveSpeed;
        }
        DOWN=0;
    }
    
    for (int x = 0; x < w; ++x) 
    {
		double cameraX = 2 * x / double(w) - 1;
		double rayPosX = posX;
		double rayPosY = posY;
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;

		int mapX = int(rayPosX);
		int mapY = int(rayPosY);

		double sideDistX;
		double sideDistY;

		double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
		double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;

		if (rayDirX < 0) {
			stepX = -1;
			sideDistX = (rayPosX - mapX) * deltaDistX;
		}
		else {
			stepX = 1;
			sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
		}

		if (rayDirY < 0) {
			stepY = -1;
			sideDistY = (rayPosY - mapY) * deltaDistY;
		}
		else {
			stepY = 1;
			sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
		}

		while (hit == 0) {
			if (sideDistX < sideDistY) {
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else {
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}

			if (map->getElement(mapX, mapY) > 0) {
				hit = 1;
			}
		}

		if (side == 0) {
			perpWallDist = (mapX - rayPosX + (1 - stepX) / 2) / rayDirX;
		}
		else {
			perpWallDist = (mapY - rayPosY + (1 - stepY) / 2) / rayDirY;
		}

		int lineHeight = abs(int(h / perpWallDist));

		int drawStart = -lineHeight / 2 + h / 2;
		if (drawStart < 0) {
			drawStart = 0;
		}

		int drawEnd = lineHeight / 2 + h / 2;
		if (drawEnd >= h) {
			drawEnd = h - 1;
		}

		wxColour lineColor;
		switch (map->getElement(mapX, mapY)) {
			case 1:
				lineColor = *wxYELLOW;
				break;
			default:
				lineColor = *wxRED;
				break;
		}

		if (side == 1) {
		  lineColor = wxColour(lineColor.Red()/2 , lineColor.Green()/2 , lineColor.Blue()/2);
		}

		dc.SetPen(wxPen(lineColor));
		dc.DrawLine(x, drawStart, x, h - drawStart);
	}
	
	if (drawMiniMap)
	{
		//rysowanie mini mapki
		int l = w/map->getWidth()/3;
		for (int i = 0; i < map->getWidth(); ++i)
		{
			for (int j = 0; j < map->getHeight(); ++j)
			{
				if (map->getElement(j, i) == 0)
				{
				    dc.SetBrush(*wxWHITE_BRUSH);
				    dc.SetPen(wxPen(*wxWHITE));
                }
				else if (map->getElement(j, i) == 1)
				{
					dc.SetBrush(*wxBLACK_BRUSH);
					dc.SetPen(wxPen(*wxBLACK));
                }
				else
				{
					dc.SetBrush(*wxRED_BRUSH);
					dc.SetPen(wxPen(*wxRED));
                }

		        dc.DrawRectangle(5 + i * l, h - 5 - map->getHeight() * l + j *l, l, l);
			}
		}
		dc.SetBrush(*wxBLUE_BRUSH);
		dc.SetPen(wxPen(*wxBLUE));
		dc.DrawCircle(5 + posY * l, h - 5 - map->getHeight() * l + posX * l, l*0.3);
    }	
	dc.UnMask();

    this->SetFocusIgnoringChildren();
}
