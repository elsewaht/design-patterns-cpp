#pragma once
class Database
{
public:
	static Database* GetInstance();

	void Run() const;

private:
	Database(){}
	static Database* database;
};

