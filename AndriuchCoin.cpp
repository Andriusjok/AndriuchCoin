#define TRANSNUMBER 1000
#include <iostream>
#include <iomanip>
#include <string>
#include <climits>
#include <cstring>
#include <sstream>
#include <vector>
#include <random>
#include <chrono>
#include <time.h>
#include <list>
#include <algorithm>
#include <functional>
#include <stdlib.h> 
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::list;

class transaction
{
private:
	string SenderKey;
	string ReceiverKey;
	float amount;
	string transID;
public:
	transaction(string SenderKey_, string  ReceiverKey_, float amount_, string transID_): SenderKey(SenderKey_), ReceiverKey(ReceiverKey_), amount(amount_), transID(transID_) {}


	void printtrans()
	{
		cout << " Skey " << SenderKey << " rkey " << ReceiverKey << " amt " << amount << " transID " << transID << endl;
		cout << endl;
	}
	string getSkey()
	{
		return SenderKey;
	}
	string getRkey()
	{
		return ReceiverKey;
	}
	string getamount()
	{
		return (std::to_string(amount));
	}
	string getID()
	{
		return transID;
	}
};

class user
{
private:
	string userName;
	float money;
	string publicKey;
public:
	user(string userName_, float money_, string publicKey_): userName(userName_), money(money_), publicKey(publicKey_) {}
	string getpublicKey()
	{
		return publicKey;
	}
	float getmoney()
	{
		return money;
	}
	void updateBalance(float money_)
	{
		money = money_;
	}

	void printuser()
	{
		cout << userName << endl;
		cout << money << endl;
		cout << publicKey << endl;
		cout << endl;
	}
};
class block {
private:
	string HashBlock = "";
	string prevHash;
	string TimeStamp;
	string Version = "1.0";
	string treeHash;
	long int nonce;
	int difficulty;
	vector<transaction> trans;
	unsigned int maxTrans;
public:
	block(string prevHash_,  string TimeStamp_, string treeHash_, long int nonce_, int difficulty_, std::vector<transaction> trans_, unsigned int maxTrans_):
		prevHash(prevHash_), TimeStamp(TimeStamp_), treeHash(treeHash_), nonce(nonce_), difficulty(difficulty_), trans(trans_), maxTrans(maxTrans_) {}
	void setHashBlock(string HashBlock_)
	{
		HashBlock = HashBlock_;
	}
	string getprevHash()
	{
		return prevHash;
	}
	string ReturnHashable()
	{
		return (HashBlock + prevHash + TimeStamp + Version + treeHash + std::to_string(nonce) + std::to_string(difficulty) + std::to_string(maxTrans));
	}
	string getHash()
	{
		return HashBlock;
	}
	void printblock()
	{
		cout << "Bloko hashas" << endl;
		cout << HashBlock << endl;
		cout << "Praeito bloko hashas" << endl;
		cout << prevHash << endl;
		cout << "Data" << endl;
		cout << TimeStamp << endl;
		cout << "Versija" << endl;
		cout << Version << endl;
		cout << "Merkletreehashas (neimplementuota)" << endl;
		cout << treeHash << endl;
		cout << "Nonce su kuriuo pavyko suhashint" << endl;
		cout << nonce << endl;
		cout << "Kiek nuliu reikejo" << endl;
		cout << difficulty << endl;
		cout << "transakcijos" << endl;
		for (int i = 0 ; i < trans.size(); i++)
		{
			trans[i].printtrans();
		}
		cout << endl;
	}

};
string generate(int max_length) {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	string possible_characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#@$^&*()_+-:;,./<>?@|";
	std::default_random_engine generator (seed);
	std::uniform_real_distribution<double> distribution (0.0, 100.0);
	string ret = "";
	for (int i = 0; i < max_length; i++) {
		int random_index = distribution(generator); //get index between 0 and possible_characters.size()-1
		ret += possible_characters[random_index];
	}
	return ret;
}

string Hash(const char* input, unsigned int length)
{

	string output;
	unsigned int hash1 = 0x9e3479b9;
	unsigned int hash2 = 0x4b3429c9;
	unsigned int hashxor = 0x003479b9;
	unsigned int z = length - 1;
	for (int i = 0; i < length; i++)
	{
		hash1 += input[i];
		hash2 += input[i];
		hashxor += input[z];
		hashxor = hashxor >> 3;
		hashxor += 0x9e3479b9;
		z--;
		hash1 = hash1 ^ hashxor;
		hash1 += (hash1 >> 1) ^ (hash1 << 3);
		hash1 += (hash1 >> 3) ^ (hash1 << 4);
		hash1 += (hash1 >> 24) ^ (hash1 << 16);
		hash1 += (hash1 >> 28) ^ (hash1 << 10);
		hash2 = hash2 ^ hashxor;
		hash2 += (hash2 >> 17) ^ (hash2 << 11);
		hash2 += (hash2 >> 3) ^ (hash2);
		hash2 += (hash2 >> 5) ^ (hash2 << 9);
		hash2 += (hash2 >> 28) ^ (hash2 << 10);
	}
	std::stringstream ss;
	ss << std::hex << hash1 << hash2;
	output = ss.str();
	while (output.length() < 16)
	{
		output.insert(0, "0");
	}
	return output;
}
void GenerateUsers(size_t amount, vector <user>& accounts)
{
	for (int i = 0; i < amount; i++)
	{
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> distribution(20, 200);
	auto roll = std::bind ( distribution, generator );
	
		string input = generate(10);
		string name = generate(8);
		user temp(name, roll(), Hash(input.c_str(), input.length()));
		//temp.printuser();
		accounts.push_back(temp);
		_sleep(20);
	}
}


void GenerateTransactions(size_t amount, vector <transaction>& transac, vector<user>& accounts)
{
	

	while(transac.size()<amount)
	{
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_int_distribution<int> distribution(1, amount);
	auto roll = std::bind ( distribution, generator );


	std::uniform_int_distribution<int> reziai(10, 50);
	auto kiekis = std::bind ( reziai, generator );

		user SendAccount = accounts[roll()];
		string sender = SendAccount.getpublicKey();
		string sendHash = Hash(sender.c_str(), sender.length());
		_sleep(20);
		user ReceivAccount = accounts[roll()];
		string receiv = ReceivAccount.getpublicKey();
		string receivHash = Hash(receiv.c_str(), receiv.length());
		float pinigai = kiekis();
		string ID = sendHash + receivHash + std::to_string(pinigai);
		transaction tempTrans(sendHash, receivHash, pinigai, Hash(ID.c_str(), ID.length()));
		if (pinigai <= SendAccount.getmoney())
		{
			transac.push_back(tempTrans);
			SendAccount.updateBalance(SendAccount.getmoney() - pinigai);
			ReceivAccount.updateBalance(ReceivAccount.getmoney() + pinigai);
		}
		else cout << "Nepakankamas balansas transakcijai " << pinigai << " > " << SendAccount.getmoney() << endl;
		//tempTrans.printtrans();
		_sleep(60);
	}

}
void GenerateBlock(int blockNr, vector<user>& accounts, vector<transaction>& transac, list<block>& blockchain)
{
	//				string check = transac[a1].getSkey() + transac[a1].getRkey() + transac[a1].getamount();
	//			if (Hash(check.c_str(), check.length()) == transac[a1].getID())
	//				transa1.push_back(transac[a1]);

	int diff = 4;


	//idedam pirma tuscia bloka
	while (blockNr == 0)
	{
		srand(time(NULL));
		int nonceas = 0;

		time_t now = time(0);
		char* dt = ctime(&now);
		vector<transaction> tempor;
		transaction temp("Andrius", "Andrius", 1, "PirmasBlokas");
		tempor.push_back(temp);
		block GenesisBlock("0", dt, "0", nonceas, 1, tempor, 1);
		string hashable = GenesisBlock.ReturnHashable();
		string blockHash = Hash(hashable.c_str(), hashable.length());
		int nuliai = 0;
		for (int i = 0; i < 1; i++)
		{
			if (blockHash[i] == '0')
				nuliai++;
		}
		if (nuliai == 1)
		{
			GenesisBlock.setHashBlock(blockHash);
			GenesisBlock.printblock();
			blockchain.push_back(GenesisBlock);
			blockNr++;
		}
	}
	while (true)
	{
		srand(time(NULL));
		cout << "Jei norite testi bloku generavima spauskite bet koki mygtuka" << endl;
		cin.get();

		if (transac.size() < 100)
		{
			cout << "TRUKSTA TRANSAKCIJU" << endl;
			throw std::runtime_error("Nebera transakciju. Programa stabdoma");

		}
		//kuris gauna teisę formuoti bloką
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::array<int, 5> foo {0, 1, 2, 3, 4};
		shuffle (foo.begin(), foo.end(), std::default_random_engine(seed));

		int nonceas = 0;
		int k = 0;

		int a1 = rand() % (transac.size() - 101);
		int b1 = rand() % (transac.size() - 101);
		int c1 = rand() % (transac.size() - 101);
		int d1 = rand() % (transac.size() - 101);
		int e1 = rand() % (transac.size() - 101);

		vector <transaction> transa1;
		vector <transaction> transb1;
		vector <transaction> transc1;
		vector <transaction> transd1;
		vector <transaction> transe1;

		//sudaromi 5 transakciju poolai su patikrinimu
		for (int i = 0; i < 100; i++)
		{
			string check = transac[a1 + i].getSkey() + transac[a1 + i].getRkey() + transac[a1 + i].getamount();
			if (Hash(check.c_str(), check.length()) == transac[a1 + i].getID())
				transa1.push_back(transac[a1 + i]);
			check = transac[b1 + i].getSkey() + transac[b1 + i].getRkey() + transac[b1 + i].getamount();
			if (Hash(check.c_str(), check.length()) == transac[b1 + i].getID())
				transb1.push_back(transac[b1 + i]);
			check = transac[c1 + i].getSkey() + transac[c1 + i].getRkey() + transac[c1 + i].getamount();
			if (Hash(check.c_str(), check.length()) == transac[c1 + i].getID())
				transc1.push_back(transac[c1 + i]);
			check = transac[d1 + i].getSkey() + transac[d1 + i].getRkey() + transac[d1 + i].getamount();
			if (Hash(check.c_str(), check.length()) == transac[d1 + i].getID())
				transd1.push_back(transac[d1 + i]);
			check = transac[e1 + i].getSkey() + transac[e1 + i].getRkey() + transac[e1 + i].getamount();
			if (Hash(check.c_str(), check.length()) == transac[e1 + i].getID())
				transe1.push_back(transac[e1 + i]);
		}

		vector < vector<transaction>> transakcijos;
		transakcijos.push_back(transa1);
		transakcijos.push_back(transb1);
		transakcijos.push_back(transc1);
		transakcijos.push_back(transd1);
		transakcijos.push_back(transe1);

		int maxtries = 10000;
		while (1)
		{
			k++;
			int p = 0;
			time_t now = time(0);
			char* dt = ctime(&now);

			if (k % maxtries == 0)
			{
				p++;
			}
			if (p > 4)
			{
				maxtries = maxtries * 10;
				p = 0;
			}

			block temp = blockchain.back();
			block BlockAttempt(temp.getHash(), dt, "0", nonceas, diff, transakcijos[foo[p]], TRANSNUMBER);
			string hashable = BlockAttempt.ReturnHashable();
			string blockHash = Hash(hashable.c_str(), hashable.length());
			int nuliai = 0;
			for (int i = 0; i < diff; i++)
			{
				if (blockHash[i] == '0')
					nuliai++;
			}
			if (diff == nuliai)
			{
				BlockAttempt.setHashBlock(blockHash);
				BlockAttempt.printblock();
				blockchain.push_back(BlockAttempt);
				if (foo[p] == 0)
				{
					std::vector<transaction>::iterator begin = transac.begin() + a1;
					std::vector<transaction>::iterator end = transac.begin() + a1 + 100;

					transac.erase(begin, end);
					cout << "bloka sukure a1" << endl;
				} else
				{
					if (foo[p] == 1)
					{
						std::vector<transaction>::iterator begin = transac.begin() + b1;
						std::vector<transaction>::iterator end = transac.begin() + b1 + 100;

						transac.erase(begin, end);

						cout << "bloka sukure b1" << endl;
						;
					} else
					{
						if (foo[p] == 2)
						{	std::vector<transaction>::iterator begin = transac.begin() + c1;
							std::vector<transaction>::iterator end = transac.begin() + c1 + 100;

							transac.erase(begin, end);

							cout << "bloka sukure c1" << endl;

						} else {
							if (foo[p] == 3)
							{
								std::vector<transaction>::iterator begin = transac.begin() + d1;
								std::vector<transaction>::iterator end = transac.begin() + d1 + 100;

								transac.erase(begin, end);

								cout << "bloka sukure d1" << endl;

							} else {
								if (foo[p] == 4)
								{
									std::vector<transaction>::iterator begin = transac.begin() + e1;
									std::vector<transaction>::iterator end = transac.begin() + e1 + 100;

									transac.erase(begin, end);

									cout << "bloka sukure e1" << endl;

								}
							}
						}
					}
				}
				cout << "cia blokas nr" << blockNr + 1 << endl;
				break;
			}
			nonceas++;
		}
		blockNr++;
	}
}
int main(int argc, char *argv[])
{
	try {
		vector <transaction> transac;
		vector <user> accounts;
		list<block> blockchain;
		int blockNr = 0;
		GenerateUsers(TRANSNUMBER, accounts);
		GenerateTransactions(TRANSNUMBER, transac, accounts);
		GenerateBlock(blockNr, accounts, transac, blockchain);
	}
	catch (const std::exception&)
	{
		return EXIT_SUCCESS;
	}
	return 0;
}


