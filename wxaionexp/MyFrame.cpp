#include "MyFrame.h"


wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_BUTTON(ID_Start, MyFrame::OnStart)
EVT_BUTTON(ID_Pause, MyFrame::OnExit)
EVT_BUTTON(ID_Stop, MyFrame::OnAbout)
EVT_BUTTON(ID_Previous, MyFrame::OnPrevious)
EVT_BUTTON(ID_Next, MyFrame::OnNext)
EVT_BUTTON(ID_ExpUpdate, MyFrame::OnExpUpdate)
EVT_BUTTON(ID_ApUpdate, MyFrame::OnApUpdate)


EVT_TIMER(TIMER_ID, MyFrame::OnTimer)

wxEND_EVENT_TABLE()

/*********************************************************************************************
Constructor: Create all panels for the application
*********************************************************************************************/
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size, (wxDEFAULT_FRAME_STYLE | wxSTAY_ON_TOP) & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	parentSizer = new wxBoxSizer(wxVERTICAL);
	this->SetSizer(parentSizer);

	// ===========================================================================

	expSizer = new wxGridBagSizer(4, 4);	
		
	panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(FRAME_WIDTH, PANEL_HEIGHT));
	parentSizer->Add(panel, wxGROW);

	labela1 = new wxStaticText(panel, -1, wxT("XP Gained")); 
	expSizer->Add(labela1, wxGBPosition(0, 0));
	labela2 = new wxStaticText(panel, -1, wxT("XP / Hour")); 
	expSizer->Add(labela2, wxGBPosition(1, 0));
	labela3 = new wxStaticText(panel, -1, wxT("Last Change")); 
	expSizer->Add(labela3, wxGBPosition(2, 0));
	valuea1 = new wxStaticText(panel, -1, wxT("x,xxx,xxx,xxx")); 
	expSizer->Add(valuea1, wxGBPosition(0, 1), wxGBSpan(1, 2), wxALIGN_RIGHT);
	valuea2 = new wxStaticText(panel, -1, wxT("x.xx k / h")); 
	expSizer->Add(valuea2, wxGBPosition(1, 1), wxGBSpan(1, 2), wxALIGN_RIGHT);
	valuea3 = new wxStaticText(panel, -1, wxT("x,xxx,xxx")); 
	expSizer->Add(valuea3, wxGBPosition(2, 1), wxGBSpan(1, 2), wxALIGN_RIGHT);
	gauge = new wxGauge(panel, XP_BAR_ID, 10000, wxDefaultPosition, wxDefaultSize, wxGA_SMOOTH);	
	
	expSizer->Add(gauge, wxGBPosition(3, 0), wxGBSpan(1, 2));
	percent = new wxStaticText(panel, -1, wxT("x.xx%"));
	expSizer->Add(percent, wxGBPosition(3, 2));
	currentExp = new wxStaticText(panel, -1, wxT("xxx,xxx,xxx / xxx,xxx,xxx"));
	expSizer->Add(currentExp, wxGBPosition(4, 0), wxGBSpan(1, 2), wxALIGN_CENTER);
	
	expSizer->SetDimension(0, 0, FRAME_WIDTH, PANEL_HEIGHT);
	panel->SetSizer(expSizer);
	//panel->Hide();

	// ===========================================================================

	apSizer = new wxGridBagSizer(4, 4);	
		
	apPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(FRAME_WIDTH, PANEL_HEIGHT));
	parentSizer->Add(apPanel, wxGROW);

	labelb1 = new wxStaticText(apPanel, -1, wxT("AP Gained [Relics]")); 
	apSizer->Add(labelb1, wxGBPosition(0, 0));
	labelb2 = new wxStaticText(apPanel, -1, wxT("AP / Hour")); 
	apSizer->Add(labelb2, wxGBPosition(1, 0));
	labelb3 = new wxStaticText(apPanel, -1, wxT("Last Change")); 
	apSizer->Add(labelb3, wxGBPosition(2, 0));
	valueb1 = new wxStaticText(apPanel, -1, wxT("x,xxx,xxx (xxx,xxx)")); 
	apSizer->Add(valueb1, wxGBPosition(0, 1), wxGBSpan(1, 2), wxALIGN_RIGHT);
	valueb2 = new wxStaticText(apPanel, -1, wxT("x.xx k / h")); 
	apSizer->Add(valueb2, wxGBPosition(1, 1), wxGBSpan(1, 2), wxALIGN_RIGHT);
	valueb3 = new wxStaticText(apPanel, -1, wxT("x,xxx,xxx")); 
	apSizer->Add(valueb3, wxGBPosition(2, 1), wxGBSpan(1, 2), wxALIGN_RIGHT);
	apGauge = new wxGauge(apPanel, XP_BAR_ID, 10000, wxDefaultPosition, wxDefaultSize, wxGA_SMOOTH);	
	
	apSizer->Add(apGauge, wxGBPosition(3, 0), wxGBSpan(1, 2));
	apPercent = new wxStaticText(apPanel, -1, wxT("x.xx%"));
	apSizer->Add(apPercent, wxGBPosition(3, 2));
	currentAp = new wxStaticText(apPanel, -1, wxT("x,xxx,xxx,xxx / x,xxx,xxx,xxx"));
	apSizer->Add(currentAp, wxGBPosition(4, 0), wxGBSpan(1, 2), wxALIGN_CENTER);

	apSizer->SetDimension(0, 0, FRAME_WIDTH, 130);
	apPanel->SetSizer(apSizer);

	// ===========================================================================

	cashSizer = new wxGridBagSizer(4, 4);

	cashPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(FRAME_WIDTH, PANEL_HEIGHT));
	parentSizer->Add(cashPanel, wxGROW);

	labelc1 = new wxStaticText(cashPanel, -1, wxT("Cash Flow In")); 
	cashSizer->Add(labelc1, wxGBPosition(0, 0));
	labelc2 = new wxStaticText(cashPanel, -1, wxT("Cash Flow Out")); 
	cashSizer->Add(labelc2, wxGBPosition(1, 0));
	labelc3 = new wxStaticText(cashPanel, -1, wxT("Net Change")); 
	cashSizer->Add(labelc3, wxGBPosition(2, 0));
	labelc4 = new wxStaticText(cashPanel, -1, wxT("Sales to NPCs")); 
	cashSizer->Add(labelc4, wxGBPosition(3, 0));
	labelc5 = new wxStaticText(cashPanel, -1, wxT("Last Transaction")); 
	cashSizer->Add(labelc5, wxGBPosition(4, 0));
	valuec1 = new wxStaticText(cashPanel, -1, wxT("x,xxx,xxx,xxx")); 
	cashSizer->Add(valuec1, wxGBPosition(0, 1), wxDefaultSpan, wxALIGN_RIGHT);
	valuec2 = new wxStaticText(cashPanel, -1, wxT("x,xxx,xxx,xxx")); 
	cashSizer->Add(valuec2, wxGBPosition(1, 1), wxDefaultSpan, wxALIGN_RIGHT);
	valuec3 = new wxStaticText(cashPanel, -1, wxT("x,xxx,xxx,xxx")); 
	cashSizer->Add(valuec3, wxGBPosition(2, 1), wxDefaultSpan, wxALIGN_RIGHT);
	valuec4 = new wxStaticText(cashPanel, -1, wxT("xx,xxx,xxx")); 
	cashSizer->Add(valuec4, wxGBPosition(3, 1), wxDefaultSpan, wxALIGN_RIGHT);
	valuec5 = new wxStaticText(cashPanel, -1, wxT("x,xxx,xxx,xxx")); 
	cashSizer->Add(valuec5, wxGBPosition(4, 1), wxDefaultSpan, wxALIGN_RIGHT);
	
	labelca = new wxStaticText(cashPanel, -1, wxT("Repose Used")); 
	cashSizer->Add(labelca, wxGBPosition(0, 2), wxDefaultSpan, wxALIGN_RIGHT);
	valueca = new wxStaticText(cashPanel, -1, wxT("xx,xxx,xxx")); 
	cashSizer->Add(valueca, wxGBPosition(1, 2), wxDefaultSpan, wxALIGN_RIGHT);
	labelcb = new wxStaticText(cashPanel, -1, wxT("Salvtn Used")); 
	cashSizer->Add(labelcb, wxGBPosition(2, 2), wxDefaultSpan, wxALIGN_RIGHT);
	valuecb = new wxStaticText(cashPanel, -1, wxT("xx,xxx,xxx")); 
	cashSizer->Add(valuecb, wxGBPosition(3, 2), wxDefaultSpan, wxALIGN_RIGHT);

	cashSizer->SetDimension(0, 0, FRAME_WIDTH, 130);
	cashPanel->SetSizer(cashSizer);	
	
	// ===========================================================================

	gatherSizer = new wxGridBagSizer(4, 4);

	gatherPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(FRAME_WIDTH, PANEL_HEIGHT));
	parentSizer->Add(gatherPanel, wxGROW);
	
	headerd1 = new wxStaticText(gatherPanel, -1, wxT("Success")); 
	gatherSizer->Add(headerd1, wxGBPosition(0, 1));
	headerd2 = new wxStaticText(gatherPanel, -1, wxT("Failure")); 
	gatherSizer->Add(headerd2, wxGBPosition(0, 2));
	headerd3 = new wxStaticText(gatherPanel, -1, wxT("Cancel")); 
	gatherSizer->Add(headerd3, wxGBPosition(0, 3));
	headerd4 = new wxStaticText(gatherPanel, -1, wxT("Procs")); 
	gatherSizer->Add(headerd4, wxGBPosition(0, 4));

	labeld1 = new wxStaticText(gatherPanel, -1, wxT("Gathering")); 
	gatherSizer->Add(labeld1, wxGBPosition(1, 0));
	valued11 = new wxStaticText(gatherPanel, -1, wxT("xxx")); 
	gatherSizer->Add(valued11, wxGBPosition(1, 1), wxDefaultSpan, wxALIGN_RIGHT);
	valued12 = new wxStaticText(gatherPanel, -1, wxT("xxx")); 
	gatherSizer->Add(valued12, wxGBPosition(1, 2), wxDefaultSpan, wxALIGN_RIGHT);
	valued13 = new wxStaticText(gatherPanel, -1, wxT("xxx")); 
	gatherSizer->Add(valued13, wxGBPosition(1, 3), wxDefaultSpan, wxALIGN_RIGHT);
	//valued14 = new wxStaticText(gatherPanel, -1, wxT("xxx")); 
	//gatherSizer->Add(valued14, wxGBPosition(1, 4), wxDefaultSpan, wxALIGN_RIGHT);

	rated1 = new wxStaticText(gatherPanel, -1, wxT("xxx.x / h")); 
	gatherSizer->Add(rated1, wxGBPosition(2, 0), wxDefaultSpan, wxALIGN_RIGHT);
	percentd11 = new wxStaticText(gatherPanel, -1, wxT("xx.x%")); 
	gatherSizer->Add(percentd11, wxGBPosition(2, 1), wxDefaultSpan, wxALIGN_RIGHT);
	percentd12 = new wxStaticText(gatherPanel, -1, wxT("xx.x%")); 
	gatherSizer->Add(percentd12, wxGBPosition(2, 2), wxDefaultSpan, wxALIGN_RIGHT);
	percentd13 = new wxStaticText(gatherPanel, -1, wxT("xx.x%")); 
	gatherSizer->Add(percentd13, wxGBPosition(2, 3), wxDefaultSpan, wxALIGN_RIGHT);
	
	labeld2 = new wxStaticText(gatherPanel, -1, wxT("Crafting")); 
	gatherSizer->Add(labeld2, wxGBPosition(3, 0));
	valued21 = new wxStaticText(gatherPanel, -1, wxT("xxx")); 
	gatherSizer->Add(valued21, wxGBPosition(3, 1), wxDefaultSpan, wxALIGN_RIGHT);
	valued22 = new wxStaticText(gatherPanel, -1, wxT("xxx")); 
	gatherSizer->Add(valued22, wxGBPosition(3, 2), wxDefaultSpan, wxALIGN_RIGHT);
	valued23 = new wxStaticText(gatherPanel, -1, wxT("xxx")); 
	gatherSizer->Add(valued23, wxGBPosition(3, 3), wxDefaultSpan, wxALIGN_RIGHT);
	valued24 = new wxStaticText(gatherPanel, -1, wxT("xxx")); 
	gatherSizer->Add(valued24, wxGBPosition(3, 4), wxDefaultSpan, wxALIGN_RIGHT);

	rated2 = new wxStaticText(gatherPanel, -1, wxT("xxx.x / h")); 
	gatherSizer->Add(rated2, wxGBPosition(4, 0), wxDefaultSpan, wxALIGN_RIGHT);
	percentd21 = new wxStaticText(gatherPanel, -1, wxT("xx.x%")); 
	gatherSizer->Add(percentd21, wxGBPosition(4, 1), wxDefaultSpan, wxALIGN_RIGHT);
	percentd22 = new wxStaticText(gatherPanel, -1, wxT("xx.x%")); 
	gatherSizer->Add(percentd22, wxGBPosition(4, 2), wxDefaultSpan, wxALIGN_RIGHT);
	percentd23 = new wxStaticText(gatherPanel, -1, wxT("xx.x%")); 
	gatherSizer->Add(percentd23, wxGBPosition(4, 3), wxDefaultSpan, wxALIGN_RIGHT);
	percentd24 = new wxStaticText(gatherPanel, -1, wxT("xx.x%")); 
	gatherSizer->Add(percentd24, wxGBPosition(4, 4), wxDefaultSpan, wxALIGN_RIGHT);
	

	gatherSizer->SetDimension(0, 0, FRAME_WIDTH, 130);
	gatherPanel->SetSizer(gatherSizer);	

	// ===========================================================================

	gatherLevelSizer = new wxGridBagSizer(4, 4);

	gatherLevelPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(FRAME_WIDTH, PANEL_HEIGHT));
	parentSizer->Add(gatherLevelPanel, wxGROW);

	labele11 = new wxStaticText(gatherLevelPanel, -1, wxT("Gather Lvl Ups")); 
	gatherLevelSizer->Add(labele11, wxGBPosition(0, 0), wxGBSpan(1, 2));
	labele12 = new wxStaticText(gatherLevelPanel, -1, wxT("Lvl Ups / Hour")); 
	gatherLevelSizer->Add(labele12, wxGBPosition(0, 3), wxGBSpan(1, 2));
	labele13 = new wxStaticText(gatherLevelPanel, -1, wxT("This Level")); 
	gatherLevelSizer->Add(labele13, wxGBPosition(1, 0), wxGBSpan(1, 2));
	labele14 = new wxStaticText(gatherLevelPanel, -1, wxT("Last Level")); 
	gatherLevelSizer->Add(labele14, wxGBPosition(1, 3), wxGBSpan(1, 2));

	valuee11 = new wxStaticText(gatherLevelPanel, -1, wxT("xxx")); 
	gatherLevelSizer->Add(valuee11, wxGBPosition(0, 2), wxDefaultSpan, wxALIGN_RIGHT);
	valuee12 = new wxStaticText(gatherLevelPanel, -1, wxT("xx.x / h")); 
	gatherLevelSizer->Add(valuee12, wxGBPosition(0, 5), wxDefaultSpan, wxALIGN_RIGHT);
	valuee13 = new wxStaticText(gatherLevelPanel, -1, wxT("xx")); 
	gatherLevelSizer->Add(valuee13, wxGBPosition(1, 2), wxDefaultSpan, wxALIGN_RIGHT);
	valuee14 = new wxStaticText(gatherLevelPanel, -1, wxT("xx")); 
	gatherLevelSizer->Add(valuee14, wxGBPosition(1, 5), wxDefaultSpan, wxALIGN_RIGHT);

	labele21 = new wxStaticText(gatherLevelPanel, -1, wxT("Craft Lvl Ups")); 
	gatherLevelSizer->Add(labele21, wxGBPosition(2, 0), wxGBSpan(1, 2));
	labele22 = new wxStaticText(gatherLevelPanel, -1, wxT("Lvl Ups / Hour")); 
	gatherLevelSizer->Add(labele22, wxGBPosition(2, 3), wxGBSpan(1, 2));
	labele23 = new wxStaticText(gatherLevelPanel, -1, wxT("This Level")); 
	gatherLevelSizer->Add(labele23, wxGBPosition(3, 0), wxGBSpan(1, 2));
	labele24 = new wxStaticText(gatherLevelPanel, -1, wxT("Last Level")); 
	gatherLevelSizer->Add(labele24, wxGBPosition(3, 3), wxGBSpan(1, 2));

	valuee21 = new wxStaticText(gatherLevelPanel, -1, wxT("xxx")); 
	gatherLevelSizer->Add(valuee21, wxGBPosition(2, 2), wxDefaultSpan, wxALIGN_RIGHT);
	valuee22 = new wxStaticText(gatherLevelPanel, -1, wxT("xx.x / h")); 
	gatherLevelSizer->Add(valuee22, wxGBPosition(2, 5), wxDefaultSpan, wxALIGN_RIGHT);
	valuee23 = new wxStaticText(gatherLevelPanel, -1, wxT("xx")); 
	gatherLevelSizer->Add(valuee23, wxGBPosition(3, 2), wxDefaultSpan, wxALIGN_RIGHT);
	valuee24 = new wxStaticText(gatherLevelPanel, -1, wxT("xx")); 
	gatherLevelSizer->Add(valuee24, wxGBPosition(3, 5), wxDefaultSpan, wxALIGN_RIGHT);

	labele31 = new wxStaticText(gatherLevelPanel, -1, wxT("G XPe")); 
	gatherLevelSizer->Add(labele31, wxGBPosition(4, 0));
	gatherGauge = new wxGauge(gatherLevelPanel, XP_BAR_ID, 10000, wxDefaultPosition, wxSize(FRAME_WIDTH / 3, -1), wxGA_SMOOTH);	
	gatherLevelSizer->Add(gatherGauge, wxGBPosition(4, 1), wxGBSpan(1, 2));
	labele32 = new wxStaticText(gatherLevelPanel, -1, wxT("C XPe")); 
	gatherLevelSizer->Add(labele32, wxGBPosition(4, 3));
	craftGauge = new wxGauge(gatherLevelPanel, XP_BAR_ID, 10000, wxDefaultPosition, wxSize(FRAME_WIDTH / 3, -1), wxGA_SMOOTH);	
	gatherLevelSizer->Add(craftGauge, wxGBPosition(4, 4), wxGBSpan(1, 2));

	gatherLevelSizer->SetDimension(0, 0, FRAME_WIDTH, 130);
	gatherLevelPanel->SetSizer(gatherLevelSizer);	

	// ===========================================================================

	initSizer = new wxGridBagSizer(4, 4);
	
	initPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(FRAME_WIDTH, PANEL_HEIGHT + NAV_HEIGHT));
	parentSizer->Add(initPanel, wxGROW);
	
	initLabel1 = new wxStaticText(initPanel, -1, wxT("Char Level")); 
	initSizer->Add(initLabel1, wxGBPosition(0, 0));
	initLabel2 = new wxStaticText(initPanel, -1, wxT("Current XP")); 
	initSizer->Add(initLabel2, wxGBPosition(1, 0));
	initLabel3 = new wxStaticText(initPanel, -1, wxT("Current AP")); 
	initSizer->Add(initLabel3, wxGBPosition(2, 0));
	initValue1 = new wxTextCtrl(initPanel, -1, wxEmptyString, wxDefaultPosition, wxSize(LEVEL_INPUT_WIDTH, -1)); 
	initValue1->SetMaxLength(2);
	initSizer->Add(initValue1, wxGBPosition(0, 1));
	initValue2 = new wxTextCtrl(initPanel, -1, wxEmptyString, wxDefaultPosition, wxSize(XP_AP_INPUT_WIDTH, -1)); 
	initSizer->Add(initValue2, wxGBPosition(1, 1));
	initValue3 = new wxTextCtrl(initPanel, -1, wxEmptyString, wxDefaultPosition, wxSize(XP_AP_INPUT_WIDTH, -1)); 
	initSizer->Add(initValue3, wxGBPosition(2, 1));
	startButton = new wxButton(initPanel, ID_Start, wxT("Start"));
	initSizer->Add(startButton, wxGBPosition(3, 2));

	initSizer->SetDimension(0, 0, FRAME_WIDTH, PANEL_HEIGHT + NAV_HEIGHT);
	initPanel->SetSizer(initSizer);

	// ===========================================================================

	logFileNotFoundSizer = new wxBoxSizer(wxVERTICAL);

	logFileNotFoundPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(FRAME_WIDTH, PANEL_HEIGHT + NAV_HEIGHT));
	parentSizer->Add(logFileNotFoundPanel, wxGROW);

	notFoundLabel1 = new wxStaticText(logFileNotFoundPanel, -1, wxT("Unable to find Chat.log file. It is required for this application to be functional.")); 
	notFoundLabel1->Wrap(FRAME_WIDTH);
	logFileNotFoundSizer->Add(notFoundLabel1);
	notFoundLabel2 = new wxStaticText(logFileNotFoundPanel, -1, wxT("The Chat.log file can be enabled by using Aion RainMeter (ARM).")); 
	notFoundLabel2->Wrap(FRAME_WIDTH);
	logFileNotFoundSizer->Add(notFoundLabel2);

	logFileNotFoundSizer->SetDimension(0, 0, FRAME_WIDTH, PANEL_HEIGHT + NAV_HEIGHT);
	logFileNotFoundPanel->SetSizer(logFileNotFoundSizer);

	// ===========================================================================

	expUpdateSizer = new wxGridBagSizer(4, 4);

	manualExpUpdatePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(FRAME_WIDTH, PANEL_HEIGHT + NAV_HEIGHT));
	parentSizer->Add(manualExpUpdatePanel, wxGROW);

	expInputMessage1 = new wxStaticText(manualExpUpdatePanel, -1, wxT("You have lost XP because you were killed by a monster."));
	expInputMessage1->Wrap(FRAME_WIDTH);
	expUpdateSizer->Add(expInputMessage1, wxGBPosition(0, 0), wxGBSpan(1, 3)); 
	expInputMessage2 = new wxStaticText(manualExpUpdatePanel, -1, wxT("Visit a Soul Healer to automatically update your XP. Alternatively you can update XP manually."));
	expInputMessage2->Wrap(FRAME_WIDTH);
	expUpdateSizer->Add(expInputMessage2, wxGBPosition(1, 0), wxGBSpan(1, 3)); 
	expInputLabel = new wxStaticText(manualExpUpdatePanel, -1, wxT("Current XP")); 
	expUpdateSizer->Add(expInputLabel, wxGBPosition(2, 0));
	expInputValue = new wxTextCtrl(manualExpUpdatePanel, -1, wxEmptyString, wxDefaultPosition, wxSize(XP_AP_INPUT_WIDTH, -1), wxALIGN_RIGHT); 
	expUpdateSizer->Add(expInputValue, wxGBPosition(2, 1));
	expInputButton = new wxButton(manualExpUpdatePanel, ID_ExpUpdate, wxT("Manual update XP"));
	expUpdateSizer->Add(expInputButton, wxGBPosition(3, 2));

	expUpdateSizer->SetDimension(0, 0, FRAME_WIDTH, PANEL_HEIGHT + NAV_HEIGHT);
	manualExpUpdatePanel->SetSizer(expUpdateSizer);

	// ===========================================================================

	apUpdateSizer = new wxGridBagSizer(4, 4);

	manualApUpdatePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(FRAME_WIDTH, PANEL_HEIGHT + NAV_HEIGHT));
	parentSizer->Add(manualApUpdatePanel, wxGROW);

	apInputMessage1 = new wxStaticText(manualApUpdatePanel, -1, wxT("You have lost AP because you were PKed by an opposing faction player."));
	apInputMessage1->Wrap(FRAME_WIDTH);
	apUpdateSizer->Add(apInputMessage1, wxGBPosition(0, 0), wxGBSpan(1, 3)); 
	apInputMessage2 = new wxStaticText(manualApUpdatePanel, -1, wxT("Since AP loss are not logged in Chat.log, manual AP update is required."));
	apInputMessage2->Wrap(FRAME_WIDTH);
	apUpdateSizer->Add(apInputMessage2, wxGBPosition(1, 0), wxGBSpan(1, 3)); 
	apInputLabel = new wxStaticText(manualApUpdatePanel, -1, wxT("Current AP")); 
	apUpdateSizer->Add(apInputLabel, wxGBPosition(2, 0));
	apInputValue = new wxTextCtrl(manualApUpdatePanel, -1, wxEmptyString, wxDefaultPosition, wxSize(XP_AP_INPUT_WIDTH, -1), wxALIGN_RIGHT); 
	apUpdateSizer->Add(apInputValue, wxGBPosition(2, 1));
	apInputButton = new wxButton(manualApUpdatePanel, ID_ApUpdate, wxT("update AP"));
	apUpdateSizer->Add(apInputButton, wxGBPosition(3, 2));

	apUpdateSizer->SetDimension(0, 0, FRAME_WIDTH, PANEL_HEIGHT + NAV_HEIGHT);
	manualApUpdatePanel->SetSizer(apUpdateSizer);

	// ===========================================================================

	navigationSizer = new wxBoxSizer(wxHORIZONTAL);

	navigationPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(FRAME_WIDTH, NAV_HEIGHT));
	parentSizer->Add(navigationPanel, wxGROW);

	nextButton = new wxButton(navigationPanel, ID_Next, wxT("Mode"));
	navigationSizer->Add(nextButton);
	
	navigationSizer->SetDimension(0, 0, FRAME_WIDTH, NAV_HEIGHT);
	navigationPanel->SetSizer(navigationSizer);

	// ===========================================================================

	currentMode = INITIAL_INPUT_MODE;

	panel->Hide();
	apPanel->Hide();
	cashPanel->Hide();
	gatherPanel->Hide();
	gatherLevelPanel->Hide();
	navigationPanel->Hide();
	logFileNotFoundPanel->Hide();
	manualExpUpdatePanel->Hide();
	manualApUpdatePanel->Hide();
	
	wxFileConfig *config = new wxFileConfig(wxEmptyString, wxEmptyString, INI_FILE, wxEmptyString, wxCONFIG_USE_RELATIVE_PATH);
	wxConfigBase::Set(config);
	wxConfigBase *conf = wxConfigBase::Get(false);

	//Try to load from current directory
	aionPath = "./";
	if (FileExists(aionPath + LOG_FILE)){
		//Log file exists
	}
	else if (FileExists(aionPath + AION_BIN_32) || FileExists(aionPath + AION_BIN_64)){
		//Appears to be an Aion directory
	}
	else{
		//Try to load from ini's directory
		if(conf) {			
			aionPath = conf->Read( wxT("AionPath"));		      

		}
		if (FileExists(aionPath + LOG_FILE)){

		}
		else if (FileExists(aionPath + AION_BIN_32) || FileExists(aionPath + AION_BIN_64)){
	
		}
		// Ask for user to browser for Aion's directory
		else{
			wxDirDialog dlg(NULL, "Locate your AION directory", "wxEmptyString", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
			int success = dlg.ShowModal();
			aionPath = dlg.GetPath() + '/';
			if (success != wxID_OK){ // Cancel button
				Close(true);
			}
			else{ // Write directory choice to ini
				conf->Write(wxT("AionPath"), aionPath.c_str());
			}
			if (!FileExists(aionPath + AION_BIN_32) &&  !FileExists(aionPath + AION_BIN_64)){
				notFoundLabel1->SetLabel("This does not appear to be an Aion directory. Also, Aion's Chat.log file must be enabled.");
				notFoundLabel1->Wrap(FRAME_WIDTH);
			}
		}

	}

	expHourCalc = new ExpHourCalc();
	gatheringLog = new GatheringLog();
	locationPinger = new LocationPinger();
	
	parser = new LogFileParser(aionPath + LOG_FILE);
	parser->setExpHourCalc(expHourCalc);
	parser->setGatheringLog(gatheringLog);
	parser->setLocationPinger(locationPinger);

	if (!parser->isOK){
		initPanel->Hide();
		logFileNotFoundPanel->Show();		
	}
	this->Layout();
	
	timer = new wxTimer(this, TIMER_ID);

	//summaryFrame = new SummaryFrame("sdklfjslkdfj", wxPoint(-1, -1), wxSize(400, 600));
	//summaryFrame->Show(true);
}


/*********************************************************************************************
Timer function involved every second - read and parse new lines from Aion chat log
*********************************************************************************************/
void MyFrame::OnTimer(wxTimerEvent& event){
	
	parser->processLines();

	if (gatheringLog->currentlyCrafting)
		this->SetTitle("[CRAFT] " + expHourCalc->getElapsedTime());
	else if (expHourCalc->level != -1)
		this->SetTitle("L" + formatNumber(expHourCalc->level) + " | " + expHourCalc->getElapsedTime());
	else 
		this->SetTitle(expHourCalc->getElapsedTime());

	//Whenever player gains XP, clear the manual XP update field
	//Whenever player gains AP, clear the manual AP update field
	if (expHourCalc->lastTickHasChanges){
		if (expHourCalc->numExpPacketsOnLastChange) expInputValue->SetValue("");
		if (expHourCalc->numApPacketsOnLastChange) apInputValue->SetValue("");
	}

	if (currentMode != UPDATE_XP_MODE && currentMode != UPDATE_AP_MODE){
		if (expHourCalc->needExpUpdate && expHourCalc->currentExp >= 0){
			panel->Hide();
			apPanel->Hide();
			cashPanel->Hide();
			gatherPanel->Hide();
			gatherLevelPanel->Hide();
			navigationPanel->Hide();
			manualExpUpdatePanel->Show();
			this->Layout();
			currentMode = UPDATE_XP_MODE;
		}
		else if (expHourCalc->needApUpdate){
			panel->Hide();
			apPanel->Hide();
			cashPanel->Hide();
			gatherPanel->Hide();
			gatherLevelPanel->Hide();
			navigationPanel->Hide();
			manualApUpdatePanel->Show();
			this->Layout();
			currentMode = UPDATE_AP_MODE;
		}
	}

	switch(currentMode){
		case XP_MODE:				
			refreshExpPanel();
			break;
		case AP_MODE:
			refreshApPanel();
			break;
		case CASH_MODE:
			refreshCashPanel();			
			break;
		case GATHER_MODE:
			refreshGatherPanel();
			break;
		case GATHER_LEVEL_MODE:
			refreshGatherLevelPanel();
			break;
		case UPDATE_XP_MODE:
			if (!expHourCalc->needExpUpdate){
				manualExpUpdatePanel->Hide();
				refreshExpPanel();
				panel->Show();
				navigationPanel->Show();		
				this->Layout();
				currentMode = XP_MODE;
			}
			break;
	}

}

/*********************************************************************************************
Refresh EXP gains panel
*********************************************************************************************/
void MyFrame::refreshExpPanel(){
	
	valuea1->SetLabelText(formatNumber(expHourCalc->expGained));

	valuea2->SetLabelText(formatKiloMega(expHourCalc->getExpPerHour()));

	if (expHourCalc->level > 0 && expHourCalc->level <= LEVEL_CAP) 
		valuea3->SetLabelText(formatNumber(expHourCalc->lastExpPacket, true) + " (" + formatPercentChange(expHourCalc->getLastExpPacketPercent()) + ")");
	else 
		valuea3->SetLabelText(formatNumber(expHourCalc->lastExpPacket, true));

	gauge->SetValue(expHourCalc->getExpPercent() * 100);
	if (expHourCalc->currentExp >= 0)
		percent->SetLabelText(formatPercent(expHourCalc->getExpPercent()));	
	else
		percent->SetLabelText("?.??%");
	
	currentExp->SetLabelText(formatCurrentAndNextValues(
		expHourCalc->currentExp, 
		expHourCalc->getExpChartEntry(expHourCalc->level)
	));
	panel->Layout();
}

/*********************************************************************************************
Refresh Abyss Points gains panel
*********************************************************************************************/
void MyFrame::refreshApPanel(){
	if (expHourCalc->relicAp != 0){
		valueb1->SetLabelText(formatNumber(expHourCalc->apGained) + " [" + formatNumber(expHourCalc->relicAp) + "]");	
		valueb2->SetLabelText(formatKiloMega(expHourCalc->getApPerHour()) + " [" + formatKiloMega(expHourCalc->getRelicApPerHour()) + "]");
	}
	else{
		valueb1->SetLabelText(formatNumber(expHourCalc->apGained));	
		valueb2->SetLabelText(formatKiloMega(expHourCalc->getApPerHour()));
	}	
	
	if (expHourCalc->getNextRankAp() > 0)
		valueb3->SetLabelText(formatNumber(expHourCalc->lastApPacket, true) + " (" + formatPercentChange(expHourCalc->getLastApPacketPercent()) + ")");
	else 
		valueb3->SetLabelText(formatNumber(expHourCalc->lastApPacket, true));

	apGauge->SetValue(expHourCalc->getApPercent() * 100);
	if (expHourCalc->currentAp >= 0)
		apPercent->SetLabelText(formatPercent(expHourCalc->getApPercent()));	
	else
		apPercent->SetLabelText("?.??%");

	currentAp->SetLabelText(formatCurrentAndNextValues(
		expHourCalc->currentAp, 
		expHourCalc->getNextRankAp()
	));
	apPanel->Layout();
}

/*********************************************************************************************
Refresh kinah panel
*********************************************************************************************/
void MyFrame::refreshCashPanel(){
	valuec1->SetLabelText(formatNumber(expHourCalc->cashGained));
	valuec2->SetLabelText(formatNumber(expHourCalc->cashSpent));
	valuec3->SetLabelText(formatNumber(expHourCalc->getNetCashFlow(), true));
	valuec4->SetLabelText(formatNumber(expHourCalc->npcSales));
	valuec5->SetLabelText(formatNumber(expHourCalc->lastCashTransaction, true));

	valueca->SetLabelText(formatNumber(expHourCalc->reposeExp));
	valuecb->SetLabelText(formatNumber(expHourCalc->salvationExp));
	
	cashPanel->Layout();
}

/*********************************************************************************************
Refresh gather/craft panel
*********************************************************************************************/
void MyFrame::refreshGatherPanel(){
	valued11->SetLabelText(formatNumber(gatheringLog->numGatheringSuccesses));
	valued12->SetLabelText(formatNumber(gatheringLog->numGatheringFailures));
	valued13->SetLabelText(formatNumber(gatheringLog->numGatheringCancellations));
	
	rated1->SetLabelText(formatDecimal(gatheringLog->getNumGatheredPerHour()) + " / h"); 	
	percentd11->SetLabelText(formatPercent(gatheringLog->getGatherSuccessRate(), 1)); 	
	percentd12->SetLabelText(formatPercent(gatheringLog->getGatherFailureRate(), 1)); 
	percentd13->SetLabelText(formatPercent(gatheringLog->getGatherCancellationRate(), 1)); 

	valued21->SetLabelText(formatNumber(gatheringLog->numCraftingSuccesses));
	valued22->SetLabelText(formatNumber(gatheringLog->numCraftingFailures));
	valued23->SetLabelText(formatNumber(gatheringLog->numCraftingCancellations));
	valued24->SetLabelText(formatNumber(gatheringLog->numCraftingProcs));

	rated2->SetLabelText(formatDecimal(gatheringLog->getNumCraftedPerHour()) + " / h"); 	
	percentd21->SetLabelText(formatPercent(gatheringLog->getCraftSuccessRate(), 1));
	percentd22->SetLabelText(formatPercent(gatheringLog->getCraftFailureRate(), 1)); 
	percentd23->SetLabelText(formatPercent(gatheringLog->getCraftCancellationRate(), 1)); 
	percentd24->SetLabelText(formatPercent(gatheringLog->getCraftProcRate(), 1)); 

	gatherPanel->Layout();
}

/*********************************************************************************************
Refresh gather/craft leveling panel
*********************************************************************************************/
void MyFrame::refreshGatherLevelPanel(){
	valuee11->SetLabelText(formatNumber(gatheringLog->gatherLevelUps.size()));
	valuee12->SetLabelText(formatDecimal(gatheringLog->getNumGatherLvlsPerHour()) + " / h");
	valuee13->SetLabelText(formatPositiveNumber(gatheringLog->numGatheredSinceLevelUp));
	valuee14->SetLabelText(formatPositiveNumber(gatheringLog->lastNumGatheredToLevelUp));
	gatherGauge->SetValue(gatheringLog->estimatedGatherExpBar * 10000 );

	valuee21->SetLabelText(formatNumber(gatheringLog->craftLevelUps.size()));
	valuee22->SetLabelText(formatDecimal(gatheringLog->getNumCraftLvlsPerHour()) + " / h");
	valuee23->SetLabelText(formatPositiveNumber(gatheringLog->numCraftedSinceLevelUp));
	valuee24->SetLabelText(formatPositiveNumber(gatheringLog->lastNumCraftedToLevelUp));
	craftGauge->SetValue(gatheringLog->estimatedCraftExpBar * 10000);	

	gatherLevelPanel->Layout();
}

/*********************************************************************************************
Start button handler - starts the exp/hour calculator
*********************************************************************************************/
void MyFrame::OnStart(wxCommandEvent& event){
	// For verifyNumericInput function, -2 is blank input, -1 is invalid input
	int level = verifyNumericInput(initValue1->GetValue().ToStdString());
	int currentExp = verifyNumericInput(initValue2->GetValue().ToStdString());
	int currentAp = verifyNumericInput(initValue3->GetValue().ToStdString());
	
	if (level > LEVEL_CAP) level = -1;	
	else if (level < 1 && level != -2) level = -1;
	if (level > 0 && currentExp > expHourCalc->getExpChartEntry(level)) currentExp = -1;
	if (currentExp < 0 && currentExp != -2) currentExp = -1;
	if (currentAp < 0 && currentAp != -2) currentAp = -1;

	if (level != -1 && currentExp != -1 && currentAp != -1){

		// Inside ExpHourCalc class, -1 now means no input

		// If level is not entered, mark initial XP as not entered
		if (level == -2){
			level = -1;
			currentExp = -1;
		}
		else if (currentExp == -2){
			currentExp = -1;
		}
		if (currentAp == -2) currentAp = -1;

		if (level == -1 || currentExp == -1){
			expInputLabel->Hide();
			expInputValue->Hide();
			expInputButton->Hide();
			expInputMessage2->SetLabel("To determine your EXP loss, you must visit a Soul Healer.");
			expInputMessage2->Wrap(FRAME_WIDTH);
		}
		parser->processLines();
		expHourCalc->start(level, currentExp, currentAp);
		gatheringLog->start();
		timer->Start(1000);

		currentMode = XP_MODE;
	
		refreshExpPanel();	
	
		initPanel->Hide();
	
		panel->Show();
		navigationPanel->Show();
	
		this->Layout();
		
	}
	else{
		wxMessageBox( "One or more of your entered values are invalid.", "Error", wxOK);
	
	}
	
}

/*********************************************************************************************
User manual XP update handler
*********************************************************************************************/
void MyFrame::OnExpUpdate(wxCommandEvent& event){
	bool success = expHourCalc->updateExp(verifyNumericInput(expInputValue->GetValue().ToStdString()));
	if (success){
		manualExpUpdatePanel->Hide();
		refreshExpPanel();
		panel->Show();
		navigationPanel->Show();
		this->Layout();
		currentMode = XP_MODE;
	}
	else{
		wxMessageBox( "Invalid XP Input", "Error", wxOK);
	}
}

/*********************************************************************************************
User manual AP update handler
*********************************************************************************************/
void MyFrame::OnApUpdate(wxCommandEvent& event){
	bool success = expHourCalc->updateAp(verifyNumericInput(apInputValue->GetValue().ToStdString()));
	if (success){
		manualApUpdatePanel->Hide();
		refreshApPanel();
		apPanel->Show();
		navigationPanel->Show();
		this->Layout();
		currentMode = AP_MODE;
	}
	else{
		wxMessageBox( "Invalid AP Input", "Error", wxOK);
	}
}

void MyFrame::OnPrevious(wxCommandEvent& event){
}

/*********************************************************************************************
"Mode" button handler
*********************************************************************************************/
void MyFrame::OnNext(wxCommandEvent& event){
	switch(currentMode){
	case XP_MODE:
		currentMode = AP_MODE;
		refreshApPanel();
		panel->Hide();
		apPanel->Show();		
		break;
	case AP_MODE:
		currentMode = CASH_MODE;
		refreshCashPanel();
		apPanel->Hide();
		cashPanel->Show();		
		break;
	case CASH_MODE:
		currentMode = GATHER_MODE;
		refreshGatherPanel();
		cashPanel->Hide();
		gatherPanel->Show();
		
		break;
	case GATHER_MODE:
		currentMode = GATHER_LEVEL_MODE;
		refreshGatherLevelPanel();
		gatherPanel->Hide();
		gatherLevelPanel->Show();
		break;
	case GATHER_LEVEL_MODE:
		currentMode = XP_MODE;
		refreshExpPanel();
		gatherLevelPanel->Hide();
		panel->Show();		
		break;
	}
	
	this->Layout();

}

void MyFrame::OnExit(wxCommandEvent& event)
{
	Close( true );
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox( "This is a wxWidgets' Hello world sample",
	"About Hello World", wxOK | wxICON_INFORMATION );
}

void MyFrame::OnHello(wxCommandEvent& event)
{
	wxLogMessage("Hello world from wxWidgets!");
}

/*********************************************************************************************
Check if file exists or not
*********************************************************************************************/
bool MyFrame::FileExists(string filename){
	bool fileExists;
	ifstream file;
	file.open(filename);	
	fileExists = !file.fail();		
	file.close();
	return fileExists;
}