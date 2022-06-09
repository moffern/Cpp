#include "TrustAccount.h"



TrustAccount::TrustAccount(const char* name, double balance, double intRate)
	: SavingsAccount{name, balance, intRate}, withdrawCount{0}
{ printf("TrustAccount constructor called for %s\n", name); }

bool TrustAccount::Deposit(double amount)
{
	if (amount >= bonusThreshold)
		amount += bonusAmount;

	return SavingsAccount::Deposit(amount);
}

bool TrustAccount::Withdraw(double amount)
{
	if (withdrawCount >= maxWithdraws || amount > (balance * maxWithdrawPercent / 100))
		return false;

	++withdrawCount;
	return SavingsAccount::Withdraw(amount);
}

void TrustAccount::print(std::ostream& os) const
{
	os.precision(2);
	os << std::fixed;
	os << "Balance: $" << balance << "\n"
		<< "Withdawals left: " << maxWithdraws - withdrawCount << "\n"
		<< "Interest rate: %" << intRate << "\n"
		<< "Max withdraw amount: " << (balance * maxWithdrawPercent / 100)
		<< "\n\n" << std::endl;
}