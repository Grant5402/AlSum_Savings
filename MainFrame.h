#pragma once
#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/grid.h>
#include <wx/datectrl.h>
#include "BudgetManager.h"
#include "BudgetItemDialog.h"
#include "TransactionDialog.h"

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title, BudgetManager* manager);

    ~MainFrame();

private:
    BudgetManager* budgetManager;
    double netGoals;
    double netSpent;
    std::vector<int> transactionRowToId;

    // Tabs
    wxNotebook* notebook;

    // Tab 1 - Home
    wxPanel* homePanel;
    wxGrid* envelopeGrid;
    wxStaticText* netGoalsText;
    wxStaticText* netSpentText;
    wxStaticText* netDifferenceText;

    // Tab 2 - Specific Envelope
    wxPanel* envelopePanel;
    wxChoice* envelopeDropdown;
    wxGrid* transactionGridEnvelope;
    wxStaticText* envelopeGoalText;
    wxStaticText* envelopeSpentText;
    wxStaticText* envelopeDifferenceText;
    wxButton* addTransactionButton;
    wxButton* deleteEnvelopeButton;
    wxButton* deleteTransactionButton;

    // Tab 3 - All Transactions
    wxPanel* transactionsPanel;
    wxGrid* transactionGridAll;

    // Methods
    void setupUI();

    void populateHomeTab();
    void populateSpecificEnvelopeTab();
    void populateAllTransactionsTab();

    void updateSpecificEnvelopeTab();

    void onAddBudgetItem(wxCommandEvent& evnt);
    void onDeleteEnvelope(wxCommandEvent& event);
    void onAddTransaction(wxCommandEvent& event);
    void onDeleteEnvelopeButton(wxCommandEvent& event);
    void onDeleteTransaction(wxCommandEvent& event);

    void onEnvelopeSelection(wxCommandEvent& evnt);
    void onTransactionGridSelection(wxGridEvent& event);

    void OnResize(wxSizeEvent& evnt);
    void AdjustColumWidths(wxGrid* grid);

    wxDECLARE_EVENT_TABLE();
};