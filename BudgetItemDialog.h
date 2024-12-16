#pragma once
#include <wx/wx.h>

class BudgetItemDialog : public wxDialog {
public:
    BudgetItemDialog(wxWindow* parent);

    // Getters for the entered values
    wxString GetName() const;
    double GetGoal() const;
    double GetBalance() const;

private:
    wxTextCtrl* nameTextCtrl;
    wxTextCtrl* goalTextCtrl;
    wxTextCtrl* balanceTextCtrl;
};
