#include "BudgetManager.h"

BudgetManager::BudgetManager(const std::string& filename)
{
	std::cout << "here" << std::endl;
	this->loadEnvelopes("envelopeData.csv");
	this->loadTransactions(filename+"transactionData.csv");
}

std::string BudgetManager::toLowerCase(const std::string& input) {
	std::string result = input;
	std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
		return std::tolower(c);
		});
	return result;
}

// +--------------------------------------------------------------------+
// |						Envelope Managment							|
// +--------------------------------------------------------------------+

void BudgetManager::addEnvelope(const std::string& name, double initialBalance, double goal) {
	// Check if envelope already exists
	DebugPrint(name + " " + std::to_string(initialBalance) + " " + std::to_string(goal) + "\n");

	if (envelopes.find(BudgetManager::toLowerCase(name)) != envelopes.end()) {
		std::cout << "Envelope with this name: " << name.c_str() << " already exists.\n";
		return;
	}

	DebugPrint(BudgetManager::toLowerCase(name) + "\n"); 

	envelopes[BudgetManager::toLowerCase(name)] = Envelope(name, initialBalance, goal); 

}

void BudgetManager::removeEnvelope(const std::string& name) {
	if (envelopes.erase(BudgetManager::toLowerCase(name))) {
		std::cout << "Envelope, " << name.c_str() << ", deleted successfully.\n";
	}
	else {
		std::cout << "Envelope, " << name.c_str() << ", not found.\n";
	}
}

Envelope BudgetManager::getEnvelope(const std::string& name) {
	return envelopes[BudgetManager::toLowerCase(name)];
}

std::unordered_map<std::string, Envelope> BudgetManager::getAllEnvelopes()
{
	return envelopes; 
}

void BudgetManager::saveEnvelopes(const std::string& filename) {
	std::ofstream file(filename);
	for (const auto& env : envelopes) {
		file << env.second.getIDName().c_str() << "," << env.second.getDisplayName().c_str() << "," <<
			env.second.getBalance() << "," << env.second.getGoal() << "\n";
	}
	file.close();
}

void BudgetManager::loadEnvelopes(const std::string& filename) {
	std::ifstream file(filename);
	std::string line;

	std::cout << "here" << std::endl;

	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string name, displayName, goalStr, balanceStr;
		getline(ss, name, ',');
		getline(ss, displayName, ',');
		getline(ss, balanceStr, ',');
		getline(ss, goalStr, ',');

		addEnvelope(displayName, std::stod(balanceStr), std::stod(goalStr));
	}
	file.close();
}


// +--------------------------------------------------------------------+
// |					  Transaction Managment							|
// +--------------------------------------------------------------------+


void BudgetManager::addTransaction(const std::string& desc, TransactionType t, double amt,
	const std::string& env, const std::chrono::system_clock::time_point& date) {

	if (t == TransactionType::INCOME) {
		getEnvelope(env).addFunds(amt);
	}

	if (t == TransactionType::EXPENSE) {
		getEnvelope(env).deductFunds(amt);
	}

	transactions[transactionCounter] = Transaction(transactionCounter,desc, t, amt, env, date);
	envelopeIndexTransactions.emplace(BudgetManager::toLowerCase(env), transactionCounter);
	envelopeIndexDate.emplace(transactions[transactionCounter].getDateAsString(), transactionCounter);

	transactionCounter++;
}

void BudgetManager::addTransaction(const std::string& desc, TransactionType t, double amt, 
	const std::string& env, const std::chrono::system_clock::time_point& date,std::string source) {

	if (t == TransactionType::INCOME) {
		getEnvelope(env).addFunds(amt);
	}

	if (t == TransactionType::EXPENSE) {
		getEnvelope(env).deductFunds(amt);
	}

	transactions[transactionCounter] = Transaction(transactionCounter, desc, t, amt, env, date, source);
	envelopeIndexTransactions.emplace(BudgetManager::toLowerCase(env), transactionCounter);
	envelopeIndexDate.emplace(transactions[transactionCounter].getDateAsString(), transactionCounter);

	transactionCounter++; 
}

std::vector<Transaction> BudgetManager::getTransactionsForEnvelope(std::string env)
{
	std::vector<Transaction> transactions;

	for (const auto id : envelopeIndexTransactions[BudgetManager::toLowerCase(env)])
	{
		transactions.push_back(transactions[id]);
	}
	
	return std::vector<Transaction>();
}

void BudgetManager::transferTransaction(int id, std::string& env)
{
}

void BudgetManager::saveTransactions(const std::string& filename) {
	std::ofstream file(filename);
	for (const auto& transaction : transactions) {
		file << transaction.second.getId() << "," 
			<< transaction.second.getDescription().c_str() << "," 
			<< transaction.second.getType() << "," 
			<< transaction.second.getAmount() << "," 
			<< transaction.second.getEnvelope().c_str() << "," 
			<< transaction.second.getDateAsString().c_str() << ","
			<< transaction.second.getSource() << "\n";
	}
	file.close();
}

void BudgetManager::loadTransactions(const std::string& filename) {
	std::ifstream file(filename);
	std::string line;

	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string idStr, desc, envName, amountStr, typeStr, dateStr, source;
		getline(ss, idStr, ',');
		getline(ss, desc, ','); 
		getline(ss, typeStr, ','); 
		getline(ss, amountStr, ',');
		getline(ss, envName, ',');
		getline(ss, dateStr, ','); 
		getline(ss, source, ','); 

		TransactionType type = static_cast<TransactionType>(std::stoi(typeStr)); 
		double amount = std::stod(amountStr);
		auto date = Transaction::parseDate(dateStr); 
		auto id = std::stoi(idStr); 
		 
		transactions[id] = Transaction(id, desc, type, amount, envName, date, source);  
		transactionCounter = transactionCounter > id + 1 ? transactionCounter : id + 1;

		envelopeIndexTransactions.emplace(BudgetManager::toLowerCase(envName), id);
		envelopeIndexDate.emplace(transactions[id].getDateAsString(), id);
	}
	file.close(); 
}

void BudgetManager::DebugPrint(const std::string& message) {
	OutputDebugStringA(message.c_str()); // Use A for ANSI strings
}