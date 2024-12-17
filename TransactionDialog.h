#pragma once
#include <wx/wx.h>
#include <wx/datectrl.h>
#include <wx/choice.h>

class TransactionDialog : public wxDialog {
public:
    TransactionDialog(wxWindow* parent);

    wxString GetDescription() const;
    int GetType() const;
    double GetAmount() const;
    wxString GetDate() const;
    wxString GetSource() const;

private:
    wxTextCtrl* descriptionCtrl;
    wxChoice* typeChoice;
    wxTextCtrl* amountCtrl;
    wxDatePickerCtrl* dateCtrl;
    wxTextCtrl* sourceCtrl;
};
