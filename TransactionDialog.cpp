#include "TransactionDialog.h"

TransactionDialog::TransactionDialog(wxWindow* parent)
    : wxDialog(parent, wxID_ANY, "Add Transaction", wxDefaultPosition, wxSize(300, 400))
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Description
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Description:"), 0, wxALL, 5);
    descriptionCtrl = new wxTextCtrl(this, wxID_ANY);
    mainSizer->Add(descriptionCtrl, 0, wxEXPAND | wxALL, 5);

    // Type
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Type:"), 0, wxALL, 5);
    wxString types[] = { "Income", "Expense" };
    typeChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 2, types);
    typeChoice->SetSelection(1);
    mainSizer->Add(typeChoice, 0, wxEXPAND | wxALL, 5);

    // Amount
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Amount:"), 0, wxALL, 5);
    amountCtrl = new wxTextCtrl(this, wxID_ANY);
    mainSizer->Add(amountCtrl, 0, wxEXPAND | wxALL, 5);

    // Date
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Date:"), 0, wxALL, 5);
    dateCtrl = new wxDatePickerCtrl(this, wxID_ANY);
    mainSizer->Add(dateCtrl, 0, wxEXPAND | wxALL, 5);

    // Source
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Source:"), 0, wxALL, 5);
    sourceCtrl = new wxTextCtrl(this, wxID_ANY);
    mainSizer->Add(sourceCtrl, 0, wxEXPAND | wxALL, 5);

    // Buttons
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(new wxButton(this, wxID_OK, "Add"), 0, wxALL, 5);
    buttonSizer->Add(new wxButton(this, wxID_CANCEL, "Cancel"), 0, wxALL, 5);

    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER);

    SetSizerAndFit(mainSizer);
}

wxString TransactionDialog::GetDescription() const { return descriptionCtrl->GetValue(); }
int TransactionDialog::GetType() const { return typeChoice->GetSelection(); }
double TransactionDialog::GetAmount() const { return wxAtof(amountCtrl->GetValue()); }
wxString TransactionDialog::GetDate() const { return dateCtrl->GetValue().FormatISODate(); }
wxString TransactionDialog::GetSource() const { return sourceCtrl->GetValue(); }
