#include "BudgetItemDialog.h"

BudgetItemDialog::BudgetItemDialog(wxWindow* parent)
    : wxDialog(parent, wxID_ANY, "Add Budget Item", wxDefaultPosition, wxSize(300, 200))
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Name Field
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Name:"), 0, wxALL, 5);
    nameTextCtrl = new wxTextCtrl(this, wxID_ANY);
    mainSizer->Add(nameTextCtrl, 0, wxEXPAND | wxALL, 5);

    // Goal Field
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Goal Amount:"), 0, wxALL, 5);
    goalTextCtrl = new wxTextCtrl(this, wxID_ANY);
    mainSizer->Add(goalTextCtrl, 0, wxEXPAND | wxALL, 5);

    // Balance Field
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Balance Amount:"), 0, wxALL, 5);
    balanceTextCtrl = new wxTextCtrl(this, wxID_ANY);
    mainSizer->Add(balanceTextCtrl, 0, wxEXPAND | wxALL, 5);

    // Buttons
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* okButton = new wxButton(this, wxID_OK, "Add");
    wxButton* cancelButton = new wxButton(this, wxID_CANCEL, "Cancel");
    buttonSizer->Add(okButton, 0, wxALL, 5);
    buttonSizer->Add(cancelButton, 0, wxALL, 5);

    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER);

    SetSizerAndFit(mainSizer);
}

wxString BudgetItemDialog::GetName() const {
    return nameTextCtrl->GetValue();
}

double BudgetItemDialog::GetGoal() const {
    return wxAtof(goalTextCtrl->GetValue());
}

double BudgetItemDialog::GetBalance() const {
    return wxAtof(balanceTextCtrl->GetValue());
}
