#pragma once
#include "SavingsAccount.h"


class TrustAccount final : public SavingsAccount
{
public:
	TrustAccount(const char* name = defName, double balance = defBalance, double intRate = defIntRate);
	virtual ~TrustAccount() { std::cout << "TrustAccount destructor called for " << name << std::endl; }

	virtual bool Deposit(double amount) override final;
	virtual bool Withdraw(double amount) override final;
	virtual void print(std::ostream& os) const override final;
	double maxWithdraw() const { return balance * maxWithdrawPercent / 100; }

protected:
	int withdrawCount;

private:
	static constexpr const char* defName = "Unnamed";
	static constexpr double defBalance = 0.0;
	static constexpr double defIntRate = 10.0;
	static constexpr double maxWithdrawPercent = 20.0;
	static constexpr int maxWithdraws = 3;
	static constexpr double bonusThreshold = 1000.0;
	static constexpr double bonusAmount = 50.0;
};

