#include "Transaction.h"

Transaction::Transaction()
{
	ID = -1;
	description = "";
	type = TransactionType::NONE;
	amount = 0;
	envelope = "blank";
	source = "";
}

Transaction::Transaction(int id, const std::string& desc, TransactionType t, double amt,
		const std::string& env, const std::chrono::system_clock::time_point& date) 
	: ID(id), description(desc), type(t), amount(amt), envelope(env), date(date), source("") {}

Transaction::Transaction(int id, const std::string& desc, TransactionType t, double amt, 
		const std::string& env, const std::chrono::system_clock::time_point& date, std::string source) 
	: ID(id), description(desc), type(t), amount(amt), envelope(env), date(date), source(source) {}

int Transaction::getId() const 
{
	return ID;
}

std::string Transaction::getDescription() const 
{
	return description;
}

std::string Transaction::getEnvelope() const 
{
	return envelope;
}

TransactionType Transaction::getType() const 
{
	return type;
}

double Transaction::getAmount() const 
{
	return amount;
}

std::string Transaction::getSource() const 
{
	return source;
}

std::chrono::system_clock::time_point Transaction::getDate() const
{
	return date;
}

std::string Transaction::getDateAsString() const
{
	return formatDate(date);
}

void Transaction::setDateFromString(const std::string& dateStr)
{
	date = parseDate(dateStr);
}

std::chrono::system_clock::time_point Transaction::parseDate(const std::string& dateStr) 
{
	std::istringstream ss(dateStr);
	std::tm tm = {};
	ss >> std::get_time(&tm, "%Y-%m-%d");
	if (ss.fail()) throw std::runtime_error("Failed to parse date");
	return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

std::string Transaction::formatDate(const std::chrono::system_clock::time_point& tp) const
{
	auto timeT = std::chrono::system_clock::to_time_t(tp);
	std::tm localTime = {};
	localtime_s(&localTime, &timeT); // Use localtime_s instead of localtime

	std::ostringstream ss;
	ss << std::put_time(&localTime, "%Y-%m-%d");
	return ss.str();
}