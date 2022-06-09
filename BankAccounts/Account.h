#pragma once
#include "Printable.h"


class Account : public Printable
{
public:
	Account(const char* name = defName, double balance = defBalance, double intRate = defIntRate);
	virtual ~Account() { std::cout << "Account Destructor called for " << name << std::endl; }

	virtual bool Deposit(double amount) = 0;
	virtual bool Withdraw(double amount) = 0;
	virtual void print(std::ostream& os) const override;

	const char* getName() const { return name; }
	double getBalance() const { return balance; }
	double getIntRate() const { return intRate; }

protected:
	const char* name;
	double balance;
	double intRate;

private:
	static constexpr const char* defName = "Unnamed";
	static constexpr double defBalance = 0.0;
	static constexpr double defIntRate = 0.0;
};

