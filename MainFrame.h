#pragma once
#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/grid.h>
#include <wx/datectrl.h>
#include "BudgetManager.h"
#include "BudgetItemDialog.h"

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title, BudgetManager* manager);

    ~MainFrame();

private:
    BudgetManager* budgetManager;

    // Tabs
    wxNotebook* notebook;

    // Tab 1 - Home
    wxPanel* homePanel;
    wxGrid* envelopeGrid;
    wxStaticText* netGoalsText;
    wxStaticText* netBalancesText;
    wxStaticText* netDifferenceText;

    // Tab 2 - Specific Envelope
    wxPanel* envelopePanel;
    wxChoice* envelopeDropdown;
    wxGrid* transactionGridEnvelope;
    wxStaticText* envelopeGoalText;
    wxStaticText* envelopeBalanceText;

    // Tab 3 - All Transactions
    wxPanel* transactionsPanel;
    wxGrid* transactionGridAll;

    // Methods
    void setupUI();

    void populateHomeTab();
    void populateSpecificEnvelopeTab();
    void populateAllTransactionsTab();

    void onAddBudgetItem(wxCommandEvent& evnt);
    void onDeleteEnvelope(wxCommandEvent& event);

    void onEnvelopeSelection(wxCommandEvent& evnt);

    void OnResize(wxSizeEvent& evnt);
    void AdjustColumWidths(wxGrid* grid);

    wxDECLARE_EVENT_TABLE();
};