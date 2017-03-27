///-----------------------------------------------------------------
///
/// @file      Project1Frm.h
/// @author    Weronika, Dominika, Alicja
/// Created:   2016-12-23 22:00:56
/// @section   DESCRIPTION
///            Project1Frm class declaration
///
///------------------------------------------------------------------

#ifndef __PROJECT1FRM_H__
#define __PROJECT1FRM_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/frame.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/filedlg.h>
#include <wx/checkbox.h>
#include <wx/slider.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/sizer.h>
////Header Include End
#include "MapReader.h"
#include <wx/string.h>
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include <wx/colour.h>
#include <wx/pen.h>
#include <wx/brush.h>

#include <wx/msgout.h>
#include <ctime>

////Dialog Style Start
#undef Project1Frm_STYLE
#define Project1Frm_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class Project1Frm : public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		Project1Frm(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("Project1"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = Project1Frm_STYLE);
		virtual ~Project1Frm();
		void StartButtonClick(wxCommandEvent& event);
		void LoadButtonClick(wxCommandEvent& event);
		void ExitButtonClick(wxCommandEvent& event);
		void FOVSliderScroll(wxScrollEvent& event);
		void MiniMapClick(wxCommandEvent& event);
		void OnTimerTimeout(wxTimerEvent& event);
		void StartGame();
		
		void draw();
		
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxFileDialog *WxOpenFileDialog;
		wxCheckBox *MiniMap;
		wxSlider *FOVSlider;
		wxStaticText *FOVText;
		wxStaticText *Time;
		wxStaticText *Timer;
		wxButton *ExitButton;
		wxButton *LoadButton;
		wxButton *StartButton;
		wxBoxSizer *WxBoxSizer2;
		wxPanel *DrawPanel;
		wxBoxSizer *WxBoxSizer1;
		////GUI Control Declaration End

		wxMessageDialog *WxMessageDialog1;
		
		double FOV; //wartosc fov
		bool drawMiniMap; //czy rysujemy minimape
		
		bool UP;
		bool DOWN;
		bool LEFT;
		bool RIGHT;
		bool SHIFT;
		
		std::string pathToMap;
		bool canPlay;
		
		MapReader *map;
			    
	    double posX;
	    double posY;

	    double dirX;
	    double dirY;
	    double planeX;
	    double planeY;

	    double rotSpeed;
	    double moveSpeed;
	    time_t startTime;
	    
	    wxTimer* m_pTimer;
	    bool extraSpeed;
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_MINIMAP = 1013,
			ID_FOVSLIDER = 1012,
			ID_FOVTEXT = 1011,
			ID_TIME = 1010,
			ID_TIMER = 1009,
			ID_EXITBUTTON = 1008,
			ID_LOADBUTTON = 1007,
			ID_STARTBUTTON = 1006,
			ID_DRAWPANEL = 1004,
			TIMER_ID= 10,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
		
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
		void OnKeyDown(wxKeyEvent& event);
		void OnKeyUp(wxKeyEvent& event);
};

#endif
