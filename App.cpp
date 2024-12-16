#include "App.h"
#include "MainFrame.h"
#include "BudgetManager.h"
#include <iostream>
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	BudgetManager* budgetManager = new BudgetManager("C:\\Users\\grant\\source\\repos\\AlSum_Savings");  
	MainFrame* mainFrame = new MainFrame("AlSum Savings", budgetManager);
	mainFrame->SetClientSize(800, 600);
	mainFrame->Center();
	mainFrame->Show();
	return true;
}
