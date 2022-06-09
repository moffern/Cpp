#include "SavingsAccount.h"



SavingsAccount::SavingsAccount(const char* name, double balance, double intRate)
	: Account{ name, balance , intRate }
{ printf("SavingsAccount constructor called for %s\n", name); }

bool SavingsAccount::Deposit(double amount)
{
	amount += amount * intRate / 100;
	return Account::Deposit(amount);
}

bool SavingsAccount::Withdraw(double amount)
{
	return Account::Withdraw(amount);
}

void SavingsAccount::print(std::ostream& os) const
{
	os.precision(2);
	os << std::fixed;
	os << "Balance: $" << balance << "\n"
		<< "Interest rate: %" << intRate << "\n\n" << std::endl;
}