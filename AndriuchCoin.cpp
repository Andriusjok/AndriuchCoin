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
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::list;

class transaction
{
private:
	unsigned int number;
	string SenderKey;
	string ReceiverKey;
	float amount;
public:
	transaction(unsigned int number_, string SenderKey_, string  ReceiverKey_, float amount_): number(number_), SenderKey(SenderKey_), ReceiverKey(ReceiverKey_), amount(amount_) {}

void printtrans()
	{
		cout<<"nr "<<number<<" Skey "<<SenderKey<<" rkey "<<ReceiverKey<<" amt "<<amount<<endl;
		cout<<endl;
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
	void printuser()
	{
		cout<<userName<<endl;
		cout<<money<<endl;
		cout<<publicKey<<endl;
		cout<<endl;
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
		return (HashBlock+prevHash+TimeStamp+Version+treeHash+std::to_string(nonce)+std::to_string(difficulty)+std::to_string(maxTrans));
	}
	void printblock()
	{
		cout<<"Bloko hashas"<<endl;
		cout<<HashBlock<<endl;
		cout<<"Praeito bloko hashas"<<endl;
		cout<<prevHash<<endl;
		cout<<"Data"<<endl;
		cout<<TimeStamp<<endl;
		cout<<"Versija"<<endl;
		cout<<Version<<endl;
		cout<<"Merkletreehashas (neimplementuota)"<<endl;
		cout<<treeHash<<endl;
		cout<<"Nonce su kuriuo pavyko suhashint"<<endl;
		cout<<nonce<<endl;
		cout<<"Kiek nuliu reikejo"<<endl;
		cout<<difficulty<<endl;
		cout<<"transakcijos"<<endl;
		for (int i =0 ;i < trans.size();i++)
		{
			trans[i].printtrans();
		}
		cout<<endl;
	}

};
string generate(int max_length){
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    string possible_characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!#@$^&*()_+-:;,./<>?@|";
	std::default_random_engine generator (seed);
	std::uniform_real_distribution<double> distribution (0.0,100.0);
    string ret = "";
    for(int i = 0; i < max_length; i++){
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
		string name=generate(8);
		user temp(name,i+100, Hash(input.c_str(), input.length()));
		//temp.printuser();
		accounts.push_back(temp);
	}
}

void GenerateTransactions(size_t amount, vector <transaction>& transac, vector<user>& accounts)
{
	srand(time(NULL));
	for (int i = 0; i < amount; i++)
	{
		string sender = accounts[rand() % 1000].getpublicKey();
		string receiv = accounts[rand() % 1000].getpublicKey();
		transaction tempTrans(i, Hash(sender.c_str(), sender.length()), Hash(receiv.c_str(), receiv.length()) , rand() % 100 + 10);
		transac.push_back(tempTrans);
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
			vector <transaction> trans;
			if (transac.size()<100)
				cout<<"TRUKSTA TRANSAKCIJU"<<endl;
			while(trans.size()<100)
			{	
				trans.push_back(transac.back());
				transac.pop_back();

			}
			int nonceas = 0;
			while (1)
			{


				time_t now = time(0);
				char* dt = ctime(&now);

				block GenesisBlock("0", dt, "0", nonceas, diff, trans, TRANSNUMBER);
				//std::ostringstream stream; // a stream is built
				//stream << GenesisBlock;// the stream is filled
				//string hashable = stream.str(); // we extract the contents of the stream
				string hashable=GenesisBlock.ReturnHashable();
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
			cout<<"Jei norite testi bloku generavima spauskite bet koki mygtuka"<<endl;
			cin.get();
			vector <transaction> trans;
			if (transac.size()<100)
				cout<<"TRUKSTA TRANSAKCIJU"<<endl;
			while(trans.size()<100)
			{	
				trans.push_back(transac.back());
				transac.pop_back();

			}
			int nonceas = 0;
			while (1)
			{


				time_t now = time(0);
				char* dt = ctime(&now);
				block temp=blockchain.back(); 
				block GenesisBlock(temp.getprevHash(), dt, "0", nonceas, diff, trans, TRANSNUMBER);
				//std::ostringstream stream; // a stream is built
				//stream << GenesisBlock;// the stream is filled
				//string hashable = stream.str(); // we extract the contents of the stream
				string hashable=GenesisBlock.ReturnHashable();
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


