#include "Database.h"

#include <iostream>

Database* Database::database = nullptr;

Database* Database::GetInstance() {
	if (database == nullptr)
	{
		database = new Database();
	}
	return database;
}

void Database::Run() const {
	std::cout << "Database running!\n";
}
