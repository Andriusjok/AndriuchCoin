#define TRANSNUMBER 10000
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
		string input = generate(16);
		string name = generate(8);
		user temp(name, rand() % 100 + 100, Hash(input.c_str(), input.length()));
		//temp.printuser();
		accounts.push_back(temp);
	}
}

void GenerateTransactions(size_t amount, vector <transaction>& transac, vector<user>& accounts)
{
	srand(time(NULL));
	for (int i = 0; i < amount; i++)
	{
		user SendAccount = accounts[rand() % 1000];
		string sender = SendAccount.getpublicKey();
		string sendHash = Hash(sender.c_str(), sender.length());

		user ReceivAccount = accounts[rand() % 1000];
		string receiv = ReceivAccount.getpublicKey();
		string receivHash = Hash(receiv.c_str(), receiv.length());
		float amount = rand() % 100 + 10;
		string ID = sendHash + receivHash + std::to_string(amount);
		transaction tempTrans(sendHash, receivHash, amount, Hash(ID.c_str(), ID.length()));
		if (amount <= SendAccount.getmoney())
			transac.push_back(tempTrans);
		else cout << "Nepakankamas balansas transakcijai " << amount << " > " << SendAccount.getmoney() << endl;
		//tempTrans.printtrans();
	}
}
void GenerateBlock(int blockNr, vector<user>& accounts, vector<transaction>& transac, list<block>& blockchain)
{
	while (true)
	{
		int diff = 4;
		if (blockNr == 0)
		{
			vector <transaction> transa1;
			vector <transaction> transb1;
			vector <transaction> transc1;
			vector <transaction> transd1;
			vector <transaction> transe1;
			if (transac.size() < 100)
				cout << "TRUKSTA TRANSAKCIJU" << endl;
			while (transa1.size() < 100)
			{
				int a1 = rand() % transac.size();
				int b1 = rand() % transac.size();
				int c1 = rand() % transac.size();
				int d1 = rand() % transac.size();
				int e1 = rand() % transac.size();

				string check = transac[a1].getSkey() + transac[a1].getRkey() + transac[a1].getamount();
				if (Hash(check.c_str(), check.length()) == transac[a1].getID())
					transa1.push_back(transac[a1]);
				check = transac[b1].getSkey() + transac[b1].getRkey() + transac[b1].getamount();
				if (Hash(check.c_str(), check.length()) == transac[b1].getID())
					transb1.push_back(transac[b1]);
				check = transac[c1].getSkey() + transac[c1].getRkey() + transac[c1].getamount();
				if (Hash(check.c_str(), check.length()) == transac[c1].getID())
					transc1.push_back(transac[c1]);
				check = transac[d1].getSkey() + transac[d1].getRkey() + transac[d1].getamount();
				if (Hash(check.c_str(), check.length()) == transac[d1].getID())
					transd1.push_back(transac[a1]);
				check = transac[e1].getSkey() + transac[e1].getRkey() + transac[e1].getamount();
				if (Hash(check.c_str(), check.length()) == transac[e1].getID())
					transe1.push_back(transac[e1]);
			}
			int nonceas = 0;
			int k = 0;
			int saka = 1;
			vector < vector<transaction>> transakcijos;
			transakcijos.push_back(transa1);
			transakcijos.push_back(transb1);
			transakcijos.push_back(transc1);
			transakcijos.push_back(transd1);
			transakcijos.push_back(transe1);

			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

			std::array<int, 5> foo {0, 1, 2, 3, 4};
			shuffle (foo.begin(), foo.end(), std::default_random_engine(seed));
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
				if (p >4)
				{
					maxtries = maxtries * 10;
					p = 0;
				}
				block GenesisBlock("0", dt, "0", nonceas, diff, transakcijos[foo[p]], TRANSNUMBER);
				//std::ostringstream stream; // a stream is built
				//stream << GenesisBlock;// the stream is filled
				//string hashable = stream.str(); // we extract the contents of the stream
				string hashable = GenesisBlock.ReturnHashable();
				string blockHash = Hash(hashable.c_str(), hashable.length());
				int nuliai = 0;
				for (int i = 0; i < diff; i++)
				{
					if (blockHash[i] == '0')
						nuliai++;
				}
				//if (nuliai==3)
				//cout << nuliai << endl;
				if (diff == nuliai)
				{
					GenesisBlock.setHashBlock(blockHash);
					GenesisBlock.printblock();
					blockchain.push_back(GenesisBlock);
					break;
				}
				nonceas++;
			}
			blockNr++;
		}
		else
		{
			cout << "Jei norite testi bloku generavima spauskite bet koki mygtuka" << endl;
			cin.get();
			vector <transaction> trans;
			if (transac.size() < 100)
				cout << "TRUKSTA TRANSAKCIJU" << endl;
			while (trans.size() < 100)
			{
				trans.push_back(transac.back());
				transac.pop_back();

			}
			int nonceas = 0;
			while (1)
			{


				time_t now = time(0);
				char* dt = ctime(&now);
				block temp = blockchain.back();
				block GenesisBlock(temp.getprevHash(), dt, "0", nonceas, diff, trans, TRANSNUMBER);
				//std::ostringstream stream; // a stream is built
				//stream << GenesisBlock;// the stream is filled
				//string hashable = stream.str(); // we extract the contents of the stream
				string hashable = GenesisBlock.ReturnHashable();
				string blockHash = Hash(hashable.c_str(), hashable.length());
				int nuliai = 0;
				for (int i = 0; i < diff; i++)
				{
					if (blockHash[i] == '0')
						nuliai++;
				}
				//if (nuliai==3)
				//cout << nuliai << endl;
				if (diff == nuliai)
				{
					GenesisBlock.setHashBlock(blockHash);
					GenesisBlock.printblock();
					blockchain.push_back(GenesisBlock);
					break;
				}
				nonceas++;
			}
			blockNr++;
		}

	}
}
int main(int argc, char *argv[])
{
	vector <transaction> transac;
	vector <user> accounts;
	list<block> blockchain;
	int blockNr = 0;
	GenerateUsers(1000, accounts);
	GenerateTransactions(TRANSNUMBER, transac, accounts);
	GenerateBlock(blockNr, accounts, transac, blockchain);

	return 0;
}


