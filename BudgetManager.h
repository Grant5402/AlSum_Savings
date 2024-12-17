#pragma once
#include <vector>
#include <unordered_map>
#include <map>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>
#include <math.h>
#include <ctime>
#include <chrono>
#include <iomanip>

#include <windows.h>

#include "Envelope.h"
#include "Transaction.h" 



class BudgetManager
{
public:
	BudgetManager(const std::string& filename);

	// +--------------------------------------------------------------------+
	// |						Envelope Managment							|
	// +--------------------------------------------------------------------+

	void addEnvelope(const std::string& name, double initialBalance, double goal);

	void removeEnvelope(const std::string& name);

	Envelope& getEnvelope(const std::string& name);

	std::unordered_map<std::string, Envelope> getAllEnvelopes();

	void saveEnvelopes(const std::string& filename);

	void loadEnvelopes(const std::string& filename);


	// +--------------------------------------------------------------------+
	// |					  Transaction Managment							|
	// +--------------------------------------------------------------------+

	void addTransaction(const std::string& desc, TransactionType t, double amt,
		const std::string& env, const std::string& date);

	void addTransaction(const std::string& desc, TransactionType t, double amt,
		const std::string& env, const std::string& date, std::string source);

	std::vector<Transaction> getTransactionsForEnvelope(std::string env);

	void removeTransaction(int transactionId);

	void removeTransactionsForEnvelope(const std::string& envelopeName);

	void transferTransaction(int id, std::string& env);

	void saveTransactions(const std::string& filename);

	void loadTransactions(const std::string& filename);

	void DebugPrint(const std::string& message);


private:
	int transactionCounter = 0; // ID counter
	std::string filename;


	std::unordered_map<std::string, Envelope> envelopes; // Stores all envelopes
	std::unordered_map<int, Transaction> transactions; // Stores all transactions
	std::unordered_map<std::string, std::vector<int>> envelopeIndexTransactions; // Provides way of quickly connecting transactions with date
	std::multimap <std::string, std::vector<int>> envelopeIndexDate; //

	std::string toLowerCase(const std::string& input);

	std::chrono::system_clock::time_point parseDateString(const std::string& dateStr);

	
};

