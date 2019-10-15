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
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::list;
class block {
private:
	string prevHash;
	time_t TimeStamp;
	string Version;
	string treeHash;
	long int nonce;
	int difficulty;
	vector<transaction> trans;
	unsigned int maxTrans;
public:
	block(string prevHash_, string treeHash_, unsigned int maxTrans_, string Version = "v1.0", std::vector<transaction> trans_): prevHash(prevHash_), treeHash(treeHash_), maxTrans(maxTrans_), trans(trans_);
		void MerkleTree(string & treeHash, std::vector<transactions> & trans);
	}

	class transaction
{
private:
	unsigned int number;
	string SenderKey;
	string ReceiverKey;
	float amount;
public:
	transaction(unsigned int number_ = 0, SenderKey_ = 0, ReceiverKey_, amount_): number(number_), SenderKey(SenderKey_), ReceiverKey(ReceiverKey_), amount(amount_);
	}

	class user
{
private:
	string userName;
	float money;
	string publicKey;
public:
	user(string userName_, float money_, string publicKey_): userName(userName_), money(money_), publicKey(publicKey_);
	string getpublicKey()
	{
		return publicKey;
	}
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
		string input = i * 432 + "101" + "abc";
		user temp("vardas" + i + i * 2, 10 * i, Hash(input.c_str(), input.length()));
		accounts.push_back(temp);
	}
}

void GenerateTransactions(size_t amount, vector <transaction>& transac, vector<user>& accounts)
{
	srand(time(NULL));
	for (int i = 0; i < amount; i++)
	{
		transaction tempTrans(i,Hash(accounts[rand()%1000].getpublicKey()),Hash(accounts[rand()%1000].getpublicKey()), rand%100+10);
		transac.push_back(tempTrans);
	}
}
void GenerateBlock(int blockNr, vector<user>& accounts, vector<transaction>& transac, list<block>& blockchain)
{
	
}
int main(int argc, char *argv[])
{
	vector <transaction> transac;
	vector <user> accounts;
	list<block> blockchain;
	GenerateUsers(1000, accounts);
	GenerateTransactions(10000, transac, accounts, list<block> blockchain);


	return 0;
}


