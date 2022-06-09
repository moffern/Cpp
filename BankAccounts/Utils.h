#pragma once
#include <vector>



void StartMenu()
{
	std::cout << "**** WELCOME ****\n\n"
		<< "Choose one of the following options:\n"
		<< "1) Login\n"
		<< "2) Register\n"
		<< "3) Quit\n"
		<< std::endl;
}

void UserMenu()
{
	std::cout << "OPTIONS:\n"
		<< "1) SavingsAccount\n"
		<< "2) TrustAccount\n"
		<< "3) Logout\n"
		<< std::endl;
}

void AccountMenu()
{
	std::cout << "OPTIONS:\n"
		<< "1) Deposit\n"
		<< "2) Withdraw\n"
		<< "3) Exit\n"
		<< std::endl;
}

bool EqualName(const std::string& s1, const std::string& s2)
{
	if (s1.size() != s2.size())
		return false;

	for (int i = 0; i < s1.size(); ++i)
	{
		if (tolower(s1.at(i)) != tolower(s2.at(i)))
			return false;
	}

	return true;
}

bool IsLoggedIn(const std::string& username)
{
	std::string password, un, pw;

	std::ifstream read{ "User\\" + username + ".txt" };
	std::getline(read, un);
	if (EqualName(username, un))
	{
		std::cout << "Enter password: "; std::cin >> password;
		std::getline(read, pw);

		if (password == pw)
		{
			std::cout << "Succecssfully logged in!\n";
			read.close();
			return true;
		}
		else
		{
			int attempts{ 3 };
			do
			{
				std::cout << "Invalid password! Try again...\n"
					<< attempts << " attempts left\n";

				std::cout << "Enter password: "; std::cin >> password;

				if (password == pw)
				{
					std::cout << "Succecssfully logged in!\n";
					read.close();
					return true;
				}
				--attempts;

			} while (attempts > 0);

			std::cout << attempts << " attempts left\n";
			read.close();
			return false;
		}
	}
	else
	{
		std::cout << "Login failed!\n" << username << " not found...\n";
		read.close();
		return false;
	}	
}

auto RetrieveAccount(const std::string& username)
{
	auto vec = new std::vector<std::pair<std::string, Account*>>;
	std::pair<std::string, Account*> user;

	std::ifstream read{ "User\\Account\\" + username + "SavingsAccount.txt"};
	std::string balance, intRate;
	std::getline(read, balance);
	std::getline(read, intRate);
	user.first = "SavingsAccount";
	user.second = new SavingsAccount(username.c_str(), strtod(balance.c_str(), 0), strtod(intRate.c_str(), 0));
	vec->emplace_back(user);
	read.close();

	read.open("User\\Account\\" + username + "TrustAccount.txt");
	std::getline(read, balance);
	std::getline(read, intRate);
	user.first = "TrustAccount";
	user.second = new TrustAccount(username.c_str(), strtod(balance.c_str(), 0), strtod(intRate.c_str(), 0));
	vec->emplace_back(user);
	read.close();

	return vec;
}

void CleanUp(std::vector<std::pair<std::string, Account*>>* vec)
{
	for (int i = 0; i < vec->size(); ++i)
		delete vec->at(i).second;
	delete vec;
}

void CreateAccount(const std::string& username)
{
	std::pair<std::string, Account*> pair;

	pair.first = "SavingsAccount";
	pair.second = new SavingsAccount(username.c_str(), 0.0, 2.5);

	std::ofstream write("User\\Account\\" + username + pair.first + ".txt");
	write << pair.second->getBalance() << "\n" << pair.second->getIntRate() << std::endl;
	write.close();
	delete pair.second;

	pair.first = "TrustAccount";
	pair.second = new SavingsAccount(username.c_str(), 0.0, 12.00);

	write.open("User\\Account\\" + username + pair.first + ".txt");
	write << pair.second->getBalance() << "\n" << pair.second->getIntRate() << std::endl;
	write.close();
	delete pair.second;
}

void CreateUser()
{
	std::string username, password, un;
	std::cout << "Enter a username: "; std::cin >> username;
	
	std::ifstream read{ "User\\" + username + ".txt" };
	std::getline(read, un);
	if (EqualName(username, un))
	{
		do
		{
			std::cout << username << " not available\n\n";

			std::cout << "Try again (Y/N)\n";
			char answer;
			std::cin >> answer;
			answer = tolower(answer);

			switch (answer)
			{
			case 'y':
				std::cout << "Enter a username: "; std::cin >> username;
				read.close();
				read.open("User\\" + username + ".txt");
				std::getline(read, un);
				break;

			default:
				return;
			}

		} while (EqualName(username, un));

		std::cout << "Enter a password: "; std::cin >> password;

		std::ofstream write;
		write.open("User\\" + username + ".txt");
		write << username << "\n" << password << std::endl;

		read.close();
		CreateAccount(username);
	}
	else
	{
		std::cout << "Enter a password: "; std::cin >> password;

		std::ofstream write;
		write.open("User\\" + username + ".txt");
		write << username << "\n" << password << std::endl;

		write.close();
		CreateAccount(username);
	}
}

void UserAccount(const std::string & username, std::vector<std::pair<std::string, Account*>>* vec)
{
	bool loggedIn = true;
	while (loggedIn)
	{
		system("cls");
		UserMenu();
		char ch;
		std::cin >> ch;
		auto index = atoi(&ch) - 1;

		switch (ch)
		{
		case '1':
		{
			bool running = true;
			std::ofstream write;

			while (running)
			{
				if (vec->at(index).first == "SavingsAccount")
				{
					system("cls");
					std::cout << *vec->at(index).second << std::endl;
					AccountMenu();
					std::cin >> ch;
					switch (ch)
					{
					case '1':
					{
						double d;
						char answer;

						std::cout << "Enter amount to deposit: ";
						std::cin >> d;

						write.open("User\\Account\\" + username + vec->at(index).first + ".txt");
						std::cout << "Deposit $" << d << " (Y/N)"; std::cin >> answer;
						answer = tolower(answer);

						switch (answer)
						{
						case 'y':
							vec->at(index).second->Deposit(d);
							write << vec->at(index).second->getBalance() << "\n"
								<< vec->at(index).second->getIntRate() << std::endl;
							break;

						default:
							write << vec->at(index).second->getBalance() << "\n"
								<< vec->at(index).second->getIntRate() << std::endl;
							break;
						}

						write.close();
						break;
					}

					case '2':
					{
						double d;
						char answer;

						std::cout << "Enter amount to withdraw: ";
						std::cin >> d;

						write.open("User\\Account\\" + username + vec->at(index).first + ".txt");
						std::cout << "Withdraw $" << d << " (Y/N)"; std::cin >> answer;
						answer = tolower(answer);

						switch (answer)
						{
						case 'y':
							vec->at(index).second->Withdraw(d);
							write << vec->at(index).second->getBalance() << "\n"
								<< vec->at(index).second->getIntRate() << std::endl;
							break;

						default:
							write << vec->at(index).second->getBalance() << "\n"
								<< vec->at(index).second->getIntRate() << std::endl;
							break;
						}

						write.close();
						break;
					}

					case '3':
						running = false;
						break;
					}
				}
			}

			//system("Pause");
			break;
		}
		case '2':
		{
			bool running = true;
			std::ofstream write;

			if (vec->at(index).first == "TrustAccount")
			{
				while (running)
				{
					system("cls");
					std::cout << *vec->at(index).second << std::endl;
					AccountMenu();
					std::cin >> ch;
					switch (ch)
					{
					case '1':
					{
						double d;
						char answer;

						std::cout << "Enter amount to deposit: ";
						std::cin >> d;

						write.open("User\\Account\\" + username + vec->at(index).first + ".txt");
						std::cout << "Deposit $" << d << " (Y/N)"; std::cin >> answer;
						answer = tolower(answer);

						switch (answer)
						{
						case 'y':
							vec->at(index).second->Deposit(d);
							write << vec->at(index).second->getBalance() << "\n"
								<< vec->at(index).second->getIntRate() << std::endl;
							break;

						default:
							write << vec->at(index).second->getBalance() << "\n"
								<< vec->at(index).second->getIntRate() << std::endl;
							break;
						}

						write.close();
						break;
					}

					case '2':
					{
						double d;
						char answer;

						std::cout << "Enter amount to withdraw: ";
						std::cin >> d;

						write.open("User\\Account\\" + username + vec->at(index).first + ".txt");
						std::cout << "Withdraw $" << d << " (Y/N)"; std::cin >> answer;
						answer = tolower(answer);

						switch (answer)
						{
						case 'y':
							vec->at(index).second->Withdraw(d);
							write << vec->at(index).second->getBalance() << "\n"
								<< vec->at(index).second->getIntRate() << std::endl;
							break;

						default:
							write << vec->at(index).second->getBalance() << "\n"
								<< vec->at(index).second->getIntRate() << std::endl;
							break;
						}

						write.close();
						break;
					}

					case '3':
						running = false;
						break;
					}
				}
			}

			//system("Pause");
			break;
		}

		case '3':
			loggedIn = false;
			break;
		}
	}
}

void Execute()
{
	bool active = true;
	while (active)
	{
		system("cls");
		StartMenu();
		char ch;
		std::cin >> ch;

		switch (ch)
		{
		case '1':
		{
			std::string username;
			std::cout << "Enter username: "; std::cin >> username;
			if (IsLoggedIn(username))
			{
				auto vec = RetrieveAccount(username);

				UserAccount(username, vec);

				CleanUp(vec);
				system("Pause");
				break;
			}
			system("Pause");
			break;
		}

		case '2':
		{
			CreateUser();
			system("Pause");
			break;
		}

		case '3':
			active = false;
			break;
		}
	}
}