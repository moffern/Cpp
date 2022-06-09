#pragma once
#include "Account.h"



class SavingsAccount : public Account
{
public:
	SavingsAccount(const char* name = defName, double balance = defBalance, double intRate = defIntRate);
	virtual ~SavingsAccount() { std::cout << "SavingsAccount Destructor called for " << name << std::endl; }

	virtual bool Deposit(double amount) override;
	virtual bool Withdraw(double amount) override;
	virtual void print(std::ostream& os) const override;

private:
	static constexpr const char* defName = "Unnamed";
	static constexpr double defBalance = 0.0;
	static constexpr double defIntRate = 5.0;
};

