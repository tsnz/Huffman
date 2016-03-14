#ifndef generateHuffman
#define generateHuffman

#include <fstream>
#include <queue>
#include <map>
#include <climits> // for CHAR_BIT
#include <iterator>
#include <algorithm>
#include <iostream>
#include <string>
#include "bitChar.h"
#include "getFileContent.h"
using namespace std;



const int UniqueSymbols = 1 << CHAR_BIT;

typedef vector<bool> HuffCode;
typedef map<char, HuffCode> HuffCodeMap;

class INode
{
public:
	const int f;

	virtual ~INode() {}

protected:
	INode(int f) : f(f) {}
};

class InternalNode : public INode
{
public:
	INode *const left;
	INode *const right;

	InternalNode(INode* c0, INode* c1) : INode(c0->f + c1->f), left(c0), right(c1) {}
	~InternalNode()
	{
		delete left;
		delete right;
	}
};

class LeafNode : public INode
{
public:
	const char c;

	LeafNode(int f, char c) : INode(f), c(c) {}
};

struct NodeCmp
{
	bool operator()(const INode* lhs, const INode* rhs) const { return lhs->f > rhs->f; }
};

INode* BuildTree(const int(&frequencies)[UniqueSymbols])
{
	priority_queue<INode*, vector<INode*>, NodeCmp> trees;

	for (int i = 0; i < UniqueSymbols; ++i)
	{
		if (frequencies[i] != 0)
			trees.push(new LeafNode(frequencies[i], (char)i));
	}
	while (trees.size() > 1)
	{
		INode* childR = trees.top();
		trees.pop();

		INode* childL = trees.top();
		trees.pop();

		INode* parent = new InternalNode(childR, childL);
		trees.push(parent);
	}
	return trees.top();
}

void GenerateCodes(const INode* node, const HuffCode& prefix, HuffCodeMap& outCodes)
{
	if (const LeafNode* lf = dynamic_cast<const LeafNode*>(node))
	{
		outCodes[lf->c] = prefix;
	}
	else if (const InternalNode* in = dynamic_cast<const InternalNode*>(node))
	{
		HuffCode leftPrefix = prefix;
		leftPrefix.push_back(false);
		GenerateCodes(in->left, leftPrefix, outCodes);

		HuffCode rightPrefix = prefix;
		rightPrefix.push_back(true);
		GenerateCodes(in->right, rightPrefix, outCodes);
	}
}


void generateHuffmanTree(string inputString, string pathToInputFile)
{
	// Build frequency table
	int frequencies[UniqueSymbols] = { 0 };
	const char* ptr = inputString.c_str();
	while (*ptr != '\0') {
		++frequencies[*ptr++];
	}
	INode* root = BuildTree(frequencies);

	HuffCodeMap codes;
	GenerateCodes(root, HuffCode(), codes);
	delete root;

	ofstream keyfile;
	stringstream keyStringstream;
	keyfile.open(pathToInputFile + ".key",ios::out);
	for (HuffCodeMap::const_iterator it = codes.begin(); it != codes.end(); ++it)
	{
		keyfile << std::hex << (int)it->first << "=";
		copy(it->second.begin(), it->second.end(),
			ostream_iterator<bool>(keyfile));
		keyfile << endl;
	}
	cout << keyStringstream.str();
	keyfile.close();

	cout << "Press Enter to start compressing\n";
	system("PAUSE");

	ofstream outfile;
	outfile.open(pathToInputFile + ".comp", ios::binary | ios::out);
	string compressedData = "";
	for (char& c : inputString) {
		if (c == 0xa)
			cout << "\\n" << std::hex << (int)c;
		else {
			cout << (c) << std::hex << (int)c;
		}
		for (HuffCodeMap::const_iterator it = codes.begin(); it != codes.end(); ++it)
		{		
			stringstream stringStream;

			if ((int)c == (int)it->first) {
				cout << "->";
				copy(it->second.begin(), it->second.end(),
					ostream_iterator<bool>(stringStream));

				cout << stringStream.str() << endl;
				compressedData.append(stringStream.str());
				break;
			}
		}		
	}

	cout << compressedData;

	bitChar bchar;
	bchar.setBITS(compressedData);
	bchar.insertBits(outfile);

	outfile.close();
	system("pause");
	return;
}

vector<vector<string>> restoreHuffmanTree(string pathToKeyFile) {

	string keyFileContents;
	int symbolCount = 0;
	keyFileContents = getFileContents(pathToKeyFile);
	symbolCount = getLineCount(pathToKeyFile);

	vector< vector<string> > codeTable(symbolCount, vector<string>(2));
	stringstream split(keyFileContents);
	string token;
	vector<string> binaryCodes;
	for (int i = 0; getline(split, token, '\n'); i++) {
		binaryCodes.push_back(token);
	}


	for (int i = 0; i < symbolCount; i++) {
		split.str("");
		split.clear();
		split.str(binaryCodes[i]);
		for (int k = 0; getline(split, token, '='); k++) {
			codeTable[symbolCount - i - 1][k] = token;
			//cout << codeTable[symbolCount - i - 1][k] << endl;
		}
	}
	

	return codeTable;
}


void decodeHuffman(vector<vector<string>> codeTable, string pathToCompFile, int symbolCount) {


	bitChar bchar;
	ifstream input;
	input.open(pathToCompFile, ios::in | ios::binary);
	string compFileContents = bchar.readByBits(input);
	//cout << compFileContents;

	// cout << codeTable[1][0]; 34

	string code;
	int output;
	string temp;

	stringstream conversionStream;
	bool found = false;
	//code[0] = compFileContents[0];

	for (char c : compFileContents) {

		if (found) {
			code.clear();
			found = false;
		}
		
			code += c;

		for (int i = 0; i < symbolCount; i++) {
			
			if (code == codeTable[i][1]) {

				temp = "0x" + codeTable[i][0];
				output = strtol(temp.c_str(), NULL, 16);
				c = output;
				cout << c;
				found = true;
				break;
			}
			

		}
	}

}

#endif
