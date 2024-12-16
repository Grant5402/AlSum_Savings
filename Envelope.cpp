#include "Envelope.h"


Envelope::Envelope()
{
	idName = "blank";
	displayName = "blank";
	balance = 0;
	goal = 0;
}

Envelope::Envelope(const std::string& name, double starting_balance, double starting_goal) {
	idName = Envelope::toLowerCase(name);
	displayName = name;
	balance = starting_balance;
	goal = starting_goal;
}

std::string Envelope::getIDName() const
{
	return std::string();
}

std::string Envelope::getDisplayName() const {
	return displayName;
}

double Envelope::getBalance() const {
	return balance;
}

double Envelope::getGoal() const {
	return goal;
}

bool Envelope::inDebt() {
	return balance <= 0;
}

void Envelope::addFunds(double amount) {
	balance += amount;
}

bool Envelope::deductFunds(double amount) {
	balance -= amount;
	return balance >= 0;
}

std::string Envelope::toLowerCase(const std::string& input) {
	std::string result = input;
	std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
		return std::tolower(c);
		});
	return result;
}