#include "Account.h"



Account::Account(const char* name, double balance, double intRate)
	: name{ name }, balance{ balance }, intRate{ intRate }
{ printf("Account constructor called for %s\n", name); }

bool Account::Deposit(double amount)
{
	if (amount <= 0)
		return false;

	balance += amount;
	return true;
}

bool Account::Withdraw(double amount)
{
	if (balance < amount)
		return false;

	balance -= amount;
	return true;
}

void Account::print(std::ostream& os) const
{
	os.precision(2);
	os << std::fixed;
	os << "[Account]: Name: " << name << ", Balance: " << balance << std::endl;
}