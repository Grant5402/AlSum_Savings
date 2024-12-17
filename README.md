# Personal Budgeting and Finance Management System

## **Project Description**
This project is a **Personal Budgeting and Finance Management System** built in C++ using **wxWidgets** for the graphical user interface. The system demonstrates a practical application of **Object-Oriented Programming (OOP)** principles, including encapsulation, inheritance, and polymorphism. It allows users to manage their finances efficiently by creating envelopes, tracking expenses, and analyzing transactions.

This project was developed as part of an independent study course **CMSC 391**, focused on mastering OOP concepts in C++.

---

## **Features**
- **Envelope Management**:
  - Create, view, and delete envelopes to categorize financial goals.
  - Track balance and goal amounts for each envelope.

- **Transaction Management**:
  - Add income and expense transactions.
  - Associate transactions with envelopes and record the transaction date and source.
  - View all transactions for a specific envelope.

- **Dynamic Budget Summaries**:
  - View summaries of net spent, goals, and differences.
  - Progress indicators to visualize envelope goals.

- **Persistent Data Storage**:
  - Transactions and envelopes are saved to CSV files (`envelopeData.csv` and `transactionData.csv`) and automatically reloaded on startup.

- **Error Handling and Validation**:
  - Input validation for incorrect values.
  - Safe operations for adding, editing, and removing data.

---
## **High Level & Simplified UML Diagrams**
                     +---------------------------------------------------------------------+
                     |                           BudgetManager                             |
                     +---------------------------------------------------------------------+
                     | - transactionCounter:int                                            |
                     | - envelopes:unordered_map<string, Envelope>                         |
                     | - transactions:unordered_map<int, Transaction>                      |
                     |                                                                     |
                     +---------------------------------------------------------------------+
                     | + addEnvelope(name: string, balance: double, goal: double): void    |
                     | + removeEnvelope(name: string): void                                |
                     | + addTransaction(description: string, type: TransactionType,        |
                     |   amount: double, envelope: string, date: string): void             |
                     | + getTransactionsForEnvelope(envelope: string): vector<Transaction> |
                     | + saveTransactions(filename: string): void                          |
                     | + loadTransactions(filename: string): void                          |
                     +---------------------------------------------------------------------+
                                                          |      
                  ------------------------------------------------------------------------------
                 |                                                                              |
    +------------------------------------+                                    +------------------------------------------+
    |              Envelope              |                                    |                Transaction               |
    +------------------------------------+                                    +------------------------------------------+
    | - idName: string                   |                                    | - ID: int                                |
    | - displayName: string              |                                    | - description: string                    |
    | - balance: double                  |                                    | - type: TransactionType                  |
    | - goal: double                     |                                    | - amount: double                         |
    +------------------------------------+                                    | - envelope: string                       |
    | + addFunds(amount: double): void   |                                    | - date: time_point                       |
    | + deductFunds(amount: double): bool|                                    | - source: string                         |
    | + getBalance(): double             |                                    +------------------------------------------+
    | + inDebt(): bool                   |                                    | + getEnvelope(): string                  |
    +------------------------------------+                                    | + getAmount(): double                    |
                                                                              +------------------------------------------+
---

## **System Requirements**
To run the project, ensure you have the following dependencies installed:

- **wxWidgets**: A C++ library for GUI applications
- **C++ Compiler**: GCC, Clang, or MSVC (Microsoft Visual C++)
- **CMake** (optional): For project builds
- **Standard C++17 or higher**


