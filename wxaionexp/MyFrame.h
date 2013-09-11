#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/fileconf.h>
#include <wx/gbsizer.h>

#include "LogFileParser.h"
#include "stringFunctions.h"

#define APP_TITLE "Aion Grind Meter"
#define APP_VERSION "1.00"

#define FRAME_WIDTH 230
#define FRAME_HEIGHT 140
#define PANEL_HEIGHT 95
#define NAV_HEIGHT 25

#define LEVEL_INPUT_WIDTH 30
#define XP_AP_INPUT_WIDTH 85

#define LOG_FILE "Chat.log"

#define AION_BIN_32 "/bin32/AION.bin"
#define AION_BIN_64 "/bin64/AION.bin"

#define INI_FILE "aiongrindmeter.ini"

class MyFrame: public wxFrame
{
	public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

	wxBoxSizer *parentSizer;

	wxGridBagSizer* expSizer;
	wxGridBagSizer* apSizer;
	wxGridBagSizer* cashSizer;
	wxGridBagSizer* initSizer;
	wxGridBagSizer* expUpdateSizer;
	wxGridBagSizer* apUpdateSizer;
	wxBoxSizer *navigationSizer;
	wxBoxSizer *logFileNotFoundSizer;

	wxPanel *panel;
	wxPanel *apPanel;
	wxPanel *cashPanel;
	wxPanel *initPanel;
	wxPanel *navigationPanel;
	wxPanel *manualExpUpdatePanel;
	wxPanel *manualApUpdatePanel;
	wxPanel *logFileNotFoundPanel;
	
	// XP Panel
	wxStaticText *labela1;
	wxStaticText *labela2;
	wxStaticText *labela3;
	wxStaticText *valuea1;
	wxStaticText *valuea2;
	wxStaticText *valuea3;
	
	wxGauge *gauge;
	wxStaticText *percent;
	wxStaticText *currentExp;

	// AP Panel
	wxStaticText *labelb1;
	wxStaticText *labelb2;
	wxStaticText *labelb3;
	wxStaticText *valueb1;
	wxStaticText *valueb2;
	wxStaticText *valueb3;
		
	wxGauge *apGauge;
	wxStaticText *apPercent;
	wxStaticText *currentAp;

	// Cash Panel
	wxStaticText *labelc1;
	wxStaticText *labelc2;
	wxStaticText *labelc3;
	wxStaticText *labelc4;
	wxStaticText *labelc5;
	wxStaticText *valuec1;
	wxStaticText *valuec2;
	wxStaticText *valuec3;
	wxStaticText *valuec4;
	wxStaticText *valuec5;

	wxStaticText *labelca;
	wxStaticText *labelcb;
	wxStaticText *valueca;
	wxStaticText *valuecb;

	// Manual XP Update Panel
	wxStaticText *expInputMessage1;
	wxStaticText *expInputMessage2;
	wxStaticText *expInputLabel;
	wxTextCtrl *expInputValue;
	wxButton *expInputButton;

	// Manual AP Update Panel
	wxStaticText *apInputMessage1;
	wxStaticText *apInputMessage2;
	wxStaticText *apInputLabel;
	wxTextCtrl *apInputValue;
	wxButton *apInputButton;	
		
	// Initialization Panel
	wxStaticText *initLabel1;
	wxStaticText *initLabel2;
	wxStaticText *initLabel3;
	wxTextCtrl *initValue1;
	wxTextCtrl *initValue2;
	wxTextCtrl *initValue3;
	wxButton *startButton;

	// Log File Not Found Panel
	wxStaticText *notFoundLabel1;
	wxStaticText *notFoundLabel2;

	// Navigation Buttons
	wxButton *nextButton;

	wxButton *pauseButton;
	wxButton *stopButton;

	wxButton *previousButton;
	
	// System
	string aionPath;
	
	ExpHourCalc *expHourCalc;
	LogFileParser *parser;

	int currentMode;

	wxTimer *timer;
		
	bool test;

	bool FileExists(string filename);

	private:
	void OnHello(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnStart(wxCommandEvent& event);

	void OnExpUpdate(wxCommandEvent& event);
	void OnApUpdate(wxCommandEvent& event);

	void OnPrevious(wxCommandEvent& event);
	void OnNext(wxCommandEvent& event);

	void OnTimer(wxTimerEvent& event);

	void refreshExpPanel();
	void refreshApPanel();
	void refreshCashPanel();
	
	wxDECLARE_EVENT_TABLE();

};

enum {
	ID_Start,
	ID_Pause,
	ID_Stop,
	ID_Previous,
	ID_Next,
	ID_ExpUpdate,
	ID_ApUpdate,
	INITIAL_INPUT_MODE,
	XP_MODE,
	AP_MODE,
	CASH_MODE,
	UPDATE_XP_MODE,
	UPDATE_AP_MODE,
	XP_BAR_ID,
	AP_BAR_ID,
	TIMER_ID
};


