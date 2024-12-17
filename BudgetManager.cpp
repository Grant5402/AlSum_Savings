#include "BudgetManager.h"

BudgetManager::BudgetManager(const std::string& filename)
{
	std::cout << "here" << std::endl;
	this->loadEnvelopes("envelopeData.csv");
	this->loadTransactions("transactionData.csv");
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
	std::string lowerName = toLowerCase(name);
	if (envelopes.erase(lowerName)) {
		removeTransactionsForEnvelope(lowerName); // Delete related transactions
		std::cout << "Envelope, " << name.c_str() << ", deleted successfully.\n";
	}
	else {
		std::cout << "Envelope, " << name.c_str() << ", not found.\n";
	}
}

Envelope& BudgetManager::getEnvelope(const std::string& name) {
	auto it = envelopes.find(toLowerCase(name));
	if (it == envelopes.end()) {
		throw std::runtime_error("Envelope not found: " + name);
	}
	return it->second;
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
	const std::string& env, const std::string& date) {

	if (t == TransactionType::INCOME) {
		getEnvelope(env).addFunds(amt);
	}

	if (t == TransactionType::EXPENSE) {
		getEnvelope(env).deductFunds(amt);
	}

	transactions[transactionCounter] = Transaction(transactionCounter,desc, t, amt, env, parseDateString(date));
	
	if (envelopeIndexTransactions.find(BudgetManager::toLowerCase(env)) == envelopeIndexTransactions.end())
	{
		std::vector<int> transactionID;

		transactionID.push_back(transactionCounter);

		envelopeIndexTransactions[BudgetManager::toLowerCase(env)] = transactionID;
	}
	else
	{
		envelopeIndexTransactions[BudgetManager::toLowerCase(env)].push_back(transactionCounter);
	}

	envelopeIndexDate.emplace(transactions[transactionCounter].getDateAsString(), transactionCounter);

	transactionCounter++;

	saveTransactions("transactionData.csv");
}

void BudgetManager::addTransaction(const std::string& desc, TransactionType t, double amt, 
	const std::string& env, const std::string& date,std::string source) {

	if (t == TransactionType::INCOME) {
		getEnvelope(env).addFunds(amt);
	}

	if (t == TransactionType::EXPENSE) {
		getEnvelope(env).deductFunds(amt);
	}

	transactions[transactionCounter] = Transaction(transactionCounter, desc, t, amt, env, parseDateString(date), source);
	
	if (envelopeIndexTransactions.find(BudgetManager::toLowerCase(env)) == envelopeIndexTransactions.end())
	{
		std::vector<int> transactionID;

		transactionID.push_back(transactionCounter);

		envelopeIndexTransactions[BudgetManager::toLowerCase(env)] = transactionID;
	}
	else
	{
		envelopeIndexTransactions[BudgetManager::toLowerCase(env)].push_back(transactionCounter);
	}

	envelopeIndexDate.emplace(transactions[transactionCounter].getDateAsString(), transactionCounter);

	transactionCounter++; 

	saveTransactions("transactionData.csv");
}

std::vector<Transaction> BudgetManager::getTransactionsForEnvelope(std::string env)
{
	std::vector<Transaction> envelopeTransactions;  // Renamed local vector for clarity

	// Debug: Print all envelopes in the index
	for (const auto& pair : envelopeIndexTransactions) {
		DebugPrint("Envelope in envelopeIndexTransactions: " +
			pair.first + ", " + std::to_string(pair.second.size()) + "\n");
	}

	// Debug: Print the target envelope name
	std::string lowerEnv = BudgetManager::toLowerCase(env);
	DebugPrint("HERE: " + lowerEnv + "\n");

	// Access transactions for the given envelope
	auto it = envelopeIndexTransactions.find(lowerEnv);
	//DebugPrint("Total Transactions: " + std::to_string(it->second.size()) + "\n");
	if (it != envelopeIndexTransactions.end()) {
		for (const auto id : it->second) {
			//DebugPrint("HERE:1 - Transaction ID: " + std::to_string(id) + "\n");

			// Access the member map transactions
			if (transactions.find(id) != transactions.end()) {
				envelopeTransactions.push_back(transactions[id]);
			}
			else {
				DebugPrint("Transaction ID not found: " + std::to_string(id) + "\n");
			}
		}
	}
	else {
		DebugPrint("Envelope not found in index: " + lowerEnv + "\n");
	}

	DebugPrint("Total Transactions Found: " + std::to_string(envelopeTransactions.size()) + "\n");
	return envelopeTransactions;
}

void BudgetManager::removeTransaction(int transactionId) {
	auto it = transactions.find(transactionId);
	if (it != transactions.end()) {
		// Retrieve the transaction details
		Transaction transaction = it->second;
		std::string envelopeName = toLowerCase(transaction.getEnvelope());

		// Adjust envelope balance based on transaction type
		if (envelopes.find(envelopeName) != envelopes.end()) {
			if (transaction.getType() == EXPENSE) {
				envelopes[envelopeName].addFunds(transaction.getAmount()); 
			}
			else if (transaction.getType() == INCOME) {
				envelopes[envelopeName].deductFunds(transaction.getAmount()); 
			}
		}

		// Remove transaction from envelope index
		auto& transactionList = envelopeIndexTransactions[envelopeName];
		transactionList.erase(std::remove(transactionList.begin(), transactionList.end(), transactionId), transactionList.end());

		// Remove the transaction itself
		transactions.erase(it);
		DebugPrint("Transaction " + std::to_string(transactionId) + " deleted and balance updated.\n");
	}
	else {
		throw std::runtime_error("Transaction ID not found.");
	}
}


void BudgetManager::removeTransactionsForEnvelope(const std::string& envelopeName) {
	auto it = envelopeIndexTransactions.find(toLowerCase(envelopeName));
	if (it != envelopeIndexTransactions.end()) {
		for (int id : it->second) {
			transactions.erase(id); // Delete the transaction
		}
		envelopeIndexTransactions.erase(it); // Remove index entry
	}
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
		auto date = std::chrono::system_clock::now();
		DebugPrint("here\n");
		auto id = std::stoi(idStr); 
		transactions[id] = Transaction(id, desc, type, amount, envName, date, source);  
		transactionCounter = transactionCounter > id + 1 ? transactionCounter : id + 1;

		if (envelopeIndexTransactions.find(BudgetManager::toLowerCase(envName)) == envelopeIndexTransactions.end())
		{
			std::vector<int> transactionID;

			transactionID.push_back(id);

			envelopeIndexTransactions[BudgetManager::toLowerCase(envName)] = transactionID;
		}
		else
		{
			envelopeIndexTransactions[BudgetManager::toLowerCase(envName)].push_back(id);
		}

		if (envelopeIndexDate.find(transactions[id].getDateAsString()) != envelopeIndexDate.end())
		{
			std::vector<int> transactionID;

			transactionID.push_back(id);

			envelopeIndexDate.emplace(transactions[id].getDateAsString(), transactionID);
		}
		else
		{
			// Add later
		}
	}

	DebugPrint("Number of transactions loaded: " + std::to_string(transactions.size()) +"\n");

	file.close(); 
}

void BudgetManager::DebugPrint(const std::string& message) {
	OutputDebugStringA(message.c_str()); // Use A for ANSI strings
}

std::chrono::system_clock::time_point BudgetManager::parseDateString(const std::string& dateStr) {
	std::tm tm = {};
	std::istringstream ss(dateStr);

	// Parse the string into the tm structure
	ss >> std::get_time(&tm, "%Y-%m-%d");
	if (ss.fail()) {
		throw std::runtime_error("Failed to parse date: " + dateStr);
	}

	// Convert tm to time_t (seconds since epoch)
	std::time_t time = std::mktime(&tm);
	if (time == -1) {
		throw std::runtime_error("Failed to convert date to time_t: " + dateStr);
	}

	// Convert time_t to system_clock::time_point
	return std::chrono::system_clock::from_time_t(time);
}