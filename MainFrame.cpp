#include "MainFrame.h"

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_CHOICE(1001, MainFrame::onEnvelopeSelection) // Event for envelope dropdown selection
    EVT_SIZE(MainFrame::OnResize)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title, BudgetManager* manager)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)), budgetManager(manager)
{
    setupUI();
    populateHomeTab();
    populateSpecificEnvelopeTab();
    //populateAllTransactionsTab();
}

MainFrame::~MainFrame() 
{
    // Ensure all dynamically created objects are properly deleted
    delete envelopeGrid;
    delete transactionGridEnvelope;
    delete transactionGridAll;

    delete netGoalsText;
    delete netBalancesText;
    delete netDifferenceText;

    delete notebook;
}

void MainFrame::setupUI() 
{
    wxPanel* mainPanel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Create Fonts
    wxFont headingFont(wxFontInfo(22).Bold());
    wxFont subheadingFont(wxFontInfo(16));
    wxFont subheadingFont2(wxFontInfo(18));
    wxFont bodyFont(wxFontInfo(12));
    wxFont bodyFont2(wxFontInfo(14));

    notebook = new wxNotebook(mainPanel, wxID_ANY);
    notebook->SetFont(subheadingFont);

    // Tab 1 - Home
    homePanel = new wxPanel(notebook);
    wxBoxSizer* homeSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* titleLabel = new wxStaticText(homePanel, wxID_ANY, "Net Budget Summary:");
    titleLabel->SetFont(headingFont);
    homeSizer->Add(titleLabel, 0, wxALIGN_LEFT | wxALL, 10);

    // Summary Info
    wxBoxSizer* netValuesSizer = new wxBoxSizer(wxVERTICAL);

    netBalancesText = new wxStaticText(homePanel, wxID_ANY, "Net Balance: $0.00");
    netBalancesText->SetFont(subheadingFont2);
    netValuesSizer->Add(netBalancesText, 0, wxLEFT | wxRIGHT | wxBOTTOM, 5);

    netGoalsText = new wxStaticText(homePanel, wxID_ANY, "Net Goal: $0.00");
    netGoalsText->SetFont(subheadingFont2);
    netValuesSizer->Add(netGoalsText, 0, wxLEFT | wxRIGHT | wxBOTTOM, 5);

    netDifferenceText = new wxStaticText(homePanel, wxID_ANY, "Net Difference: $0.00");
    netDifferenceText->SetFont(bodyFont2); // Smaller font size
    netValuesSizer->Add(netDifferenceText, 0, wxLEFT | wxRIGHT | wxBOTTOM, 5);

    // Add the button for adding a budget item
    wxButton* addBudgetButton = new wxButton(homePanel, wxID_ANY, "Add Budget Item");
    addBudgetButton->Bind(wxEVT_BUTTON, &MainFrame::onAddBudgetItem, this); // Bind the button click event
    netValuesSizer->Add(addBudgetButton, 0, wxALIGN_LEFT | wxALL, 5);

    homeSizer->Add(netValuesSizer, 0, wxEXPAND | wxALL, 10);

    // Envelope Grid
    envelopeGrid = new wxGrid(homePanel, wxID_ANY);
    envelopeGrid->CreateGrid(0, 4); // 3 columns for Name, Goal, Balance
    envelopeGrid->SetColLabelValue(0, "Name");
    envelopeGrid->SetColLabelValue(1, "Balance");
    envelopeGrid->SetColLabelValue(2, "Goal");
    envelopeGrid->SetColLabelValue(3, "Difference");
    //envelopeGrid->SetColLabelValue(4, "Actions");
    envelopeGrid->SetLabelFont(subheadingFont);
    envelopeGrid->SetFont(bodyFont);
    envelopeGrid->EnableEditing(false); 
    homeSizer->Add(envelopeGrid, 1, wxEXPAND | wxALL, 10);

    homePanel->SetSizer(homeSizer);
    notebook->AddPage(homePanel, "Home");

    // Tab 2 - Specific Envelope
    envelopePanel = new wxPanel(notebook);
    wxBoxSizer* envelopeSizer = new wxBoxSizer(wxVERTICAL);

    // Dropdown for Envelope Selection
    envelopeDropdown = new wxChoice(envelopePanel, 1001);
    envelopeSizer->Add(new wxStaticText(envelopePanel, wxID_ANY, "Select Envelope:"), 0, wxALL, 5);
    envelopeSizer->Add(envelopeDropdown, 0, wxEXPAND | wxALL, 5);

    // Envelope Summary
    envelopeGoalText = new wxStaticText(envelopePanel, wxID_ANY, "Envelope Goal: $0.00");
    envelopeBalanceText = new wxStaticText(envelopePanel, wxID_ANY, "Envelope Balance: $0.00");
    envelopeSizer->Add(envelopeGoalText, 0, wxALL, 5);
    envelopeSizer->Add(envelopeBalanceText, 0, wxALL, 5);

    // Transaction Grid
    transactionGridEnvelope = new wxGrid(envelopePanel, wxID_ANY);
    transactionGridEnvelope->CreateGrid(0, 5); // 5 columns for Description, Type, Amount, Date, Source
    transactionGridEnvelope->SetColLabelValue(0, "Description");
    transactionGridEnvelope->SetColLabelValue(1, "Type");
    transactionGridEnvelope->SetColLabelValue(2, "Amount");
    transactionGridEnvelope->SetColLabelValue(3, "Date");
    transactionGridEnvelope->SetColLabelValue(4, "Source");
    envelopeSizer->Add(transactionGridEnvelope, 1, wxEXPAND | wxALL, 10);

    envelopePanel->SetSizer(envelopeSizer);
    notebook->AddPage(envelopePanel, "Envelope Details");

    // Tab 3 - All Transactions
    transactionsPanel = new wxPanel(notebook);
    wxBoxSizer* transactionsSizer = new wxBoxSizer(wxVERTICAL);

    // Transaction Grid
    transactionGridAll = new wxGrid(transactionsPanel, wxID_ANY);
    transactionGridAll->CreateGrid(0, 5); // 5 columns for Description, Type, Amount, Envelope, Date
    transactionGridAll->SetColLabelValue(0, "Description");
    transactionGridAll->SetColLabelValue(1, "Type");
    transactionGridAll->SetColLabelValue(2, "Amount");
    transactionGridAll->SetColLabelValue(3, "Envelope");
    transactionGridAll->SetColLabelValue(4, "Date");
    transactionsSizer->Add(transactionGridAll, 1, wxEXPAND | wxALL, 10);

    transactionsPanel->SetSizer(transactionsSizer);
    notebook->AddPage(transactionsPanel, "All Transactions");

    mainSizer->Add(notebook, 1, wxEXPAND);
    mainPanel->SetSizer(mainSizer);
}

void MainFrame::populateHomeTab() 
{
    envelopeGrid->ClearGrid();
    auto envelopes = budgetManager->getAllEnvelopes(); 
    double totalGoals = 0;
    double totalBalances = 0;
    //wxLogMessage(envelopes);
    envelopeGrid->AppendRows(envelopes.size());
    int row = 0;
    for (const auto& envelope : envelopes) {
        envelopeGrid->SetCellValue(row, 0, envelope.second.getDisplayName());
        envelopeGrid->SetCellValue(row, 1, wxString::Format("$%.2f", static_cast<double>(envelope.second.getBalance())));
        envelopeGrid->SetCellValue(row, 2, wxString::Format("$%.2f", static_cast<double>(envelope.second.getGoal())));
        envelopeGrid->SetCellValue(row, 3, wxString::Format("$%.2f", 
            static_cast<double>(envelope.second.getGoal() - envelope.second.getBalance())));
        totalGoals += envelope.second.getGoal(); 
        totalBalances += envelope.second.getBalance();  

        /* Add a delete button in the last column
        wxButton* deleteButton = new wxButton(envelopeGrid, wxID_HIGHEST + row, "Delete", wxDefaultPosition, wxSize(70, 25)); 
        deleteButton->Bind(wxEVT_BUTTON, &MainFrame::onDeleteEnvelope, this); 
        // Position the button over the grid cell
        int x, y, width, height;
        x = envelopeGrid->CellToRect(row, 4).x;
        y = envelopeGrid->CellToRect(row, 4).y;
        width = envelopeGrid->CellToRect(row, 4).width;
        height = envelopeGrid->CellToRect(row, 4).height;
        deleteButton->SetPosition(wxPoint(x + 5, y + 5)); // Offset slightly for padding*/ 

        row++;
    }

    double netDifference = totalGoals - totalBalances;

    netGoalsText->SetLabel(wxString::Format("Net Goal: $%.2f", totalGoals));
    netBalancesText->SetLabel(wxString::Format("Net Balance: $%.2f", totalBalances));
    netDifferenceText->SetLabel(wxString::Format("Net Difference: $%.2f", netDifference));
}

void MainFrame::populateSpecificEnvelopeTab() 
{
    envelopeDropdown->Clear();

    auto envelopes = budgetManager->getAllEnvelopes();
    for (const auto& envelope : envelopes) {
        envelopeDropdown->Append(envelope.second.getDisplayName());
    }
}

void MainFrame::populateAllTransactionsTab() 
{
    
}

void MainFrame::onAddBudgetItem(wxCommandEvent& event)
{
    BudgetItemDialog dialog(this);

    if (dialog.ShowModal() == wxID_OK) {
        wxString name = dialog.GetName();
        double goal = dialog.GetGoal();
        double balance = dialog.GetBalance();

        if (!name.IsEmpty() && goal >= 0 && balance >= 0) {
            // Add the budget item to the backend
            budgetManager->addEnvelope(name.ToStdString(), balance, goal);

            // Refresh the grid to reflect the new budget item
            populateHomeTab();

            budgetManager->saveEnvelopes("envelopeData.csv");

            wxMessageBox(wxString::Format("Budget item '%s' added successfully.", name),
                "Item Added", wxOK | wxICON_INFORMATION);
        }
        else {
            wxMessageBox("Invalid input. Please ensure all fields are filled with valid values.",
                "Error", wxOK | wxICON_ERROR);
        }
    }
}

void MainFrame::onDeleteEnvelope(wxCommandEvent& event)
{
    int row = event.GetId() - wxID_HIGHEST;

    wxString envelopeName = envelopeGrid->GetCellValue(row, 0);

    // Confirmation dialog
    wxMessageDialog confirmDialog(
        this,
        wxString::Format("Are you sure you want to delete the envelope '%s'?", envelopeName),
        "Delete Confirmation",
        wxYES_NO | wxNO_DEFAULT | wxICON_WARNING
    );

    if (confirmDialog.ShowModal() == wxID_YES) {
        budgetManager->removeEnvelope(envelopeName.ToStdString());
        envelopeGrid->DeleteRows(row, 1);
        wxMessageBox(wxString::Format("Envelope '%s' deleted successfully.", envelopeName), "Deleted", wxOK | wxICON_INFORMATION);
    }
}

void MainFrame::onEnvelopeSelection(wxCommandEvent& evnt) 
{
    wxString selectedEnvelope = envelopeDropdown->GetStringSelection();
    if (selectedEnvelope.IsEmpty()) return;

    try {
        // Retrieve envelope details
        Envelope envelope = budgetManager->getEnvelope(selectedEnvelope.ToStdString());
        envelopeGoalText->SetLabel(wxString::Format("Envelope Goal: $%.2f", envelope.getGoal()));
        envelopeBalanceText->SetLabel(wxString::Format("Envelope Balance: $%.2f", envelope.getBalance()));

        // Populate transaction grid
        auto transactions = budgetManager->getTransactionsForEnvelope(selectedEnvelope.ToStdString());
        transactionGridEnvelope->ClearGrid();

        int numRows = transactions.size();
        if (transactionGridEnvelope->GetNumberRows() < numRows) {
            transactionGridEnvelope->AppendRows(numRows - transactionGridEnvelope->GetNumberRows());
        }

        int row = 0;
        for (const auto& transaction : transactions) {
            transactionGridEnvelope->SetCellValue(row, 0, transaction.getDescription());
            transactionGridEnvelope->SetCellValue(row, 1, transaction.getType() == INCOME ? "Income" : "Expense");
            transactionGridEnvelope->SetCellValue(row, 2, wxString::Format("$%.2f", transaction.getAmount()));
            transactionGridEnvelope->SetCellValue(row, 3, transaction.getDateAsString());
            transactionGridEnvelope->SetCellValue(row, 4, transaction.getSource());
            row++;
        }
    }
    catch (const std::exception& e) {
        wxMessageBox("Failed to load envelope details.", "Error", wxOK | wxICON_ERROR);
    }
}

void MainFrame::OnResize(wxSizeEvent& evnt)
{
    MainFrame::AdjustColumWidths(envelopeGrid);
    MainFrame::AdjustColumWidths(transactionGridEnvelope);
    MainFrame::AdjustColumWidths(transactionGridAll);

    // Propagate the event to allow default handling
    evnt.Skip();
}

void MainFrame::AdjustColumWidths(wxGrid* grid)
{
    if (!grid || grid->GetNumberCols() == 0) {
        return;
    }
    
    int totalWidth = grid->GetClientSize().GetWidth() - grid->GetRowLabelSize(); 

    if (totalWidth <= 0) {
        return; // Avoid division by zero or negative values
    }

    int numColumns = grid->GetNumberCols();
    int columnWidth = totalWidth / (numColumns);
    int columnWidthRemander = totalWidth % (numColumns);

    for (int col = 0; col < numColumns - 1; ++col) {
        grid->SetColSize(col, columnWidth);
    }

    grid->SetColSize(numColumns - 1, columnWidth + columnWidthRemander);

    grid->ForceRefresh(); // Ensure the grid is redrawn
}