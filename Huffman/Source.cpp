#include "generateHuffman.h"
#include "getFileContent.h"

#include<string>
#include<fstream>
#include<stdlib.h>


void encode();
void decode();

using namespace std;

int main() {


	/*
	ifstream bindateistream;
	bindateistream.open("D:/test.txt.comp", ios::in | ios::binary);
	//bindateistream.open("D:/test.txt.comp", ios::binary | ios::in);
	string outcont;
	bitChar tempBit;
	tempBit.readByBits(bindateistream);
	system("pause");
	exit(2);
	*/



	int inputOption = 0;
	bool valid = false;
	while (!valid) {
		cout << "(1) Encode\n(2) Decode\n";
		cin >> inputOption;
		if (inputOption == 1) {
			encode();
			valid = true;
		}
		else { if (inputOption == 2) {
			decode();
			valid = true;
			}
			else {
				cout << "Not a valid option. Please try again.\n";
				system("PAUSE");
				system("cls");
			}
		}
	}
	
}

void encode(void) {
	string pathToFile = "";
	cout << "Enter path to .txt file:\n";
	cin >> pathToFile;
	generateHuffmanTree(getFileContents(pathToFile), pathToFile);
}

void decode(void) {
	string pathToKeyFile = "";
	string pathToCompFile = "";
	cout << "Enter path to .key file:\n";
	cin >> pathToKeyFile;
	cout << "Enter path to .comp file:\n";
	cin >> pathToCompFile;
	vector<vector<string>> codeTable;

	codeTable = restoreHuffmanTree(pathToKeyFile);

	decodeHuffman(codeTable, pathToCompFile, getLineCount(pathToKeyFile));

	system("pause");
}





