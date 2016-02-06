#include "generateHuffman.h"
#include "getFileContent.h"

#include<string>
#include<fstream>
#include<stdlib.h>





using namespace std;

int main() {
	int inputOption = 0;
	string pathToFile = "";
	bool valid = false;
	while (!valid) {
		cout << "(1) Encode\n(2) Decode\n";
		cin >> inputOption;
		if (inputOption == 1) {
			cout << "Encode\n";
			valid = true;
		}
		else { if (inputOption == 2) {
			cout << "Decode\n";
			valid = true;
			}
			else {
				cout << "Not a valid option. Please try again.\n";
				system("PAUSE");
				system("cls");
			}
		}
	}
	cout << "Enter path to .txt file:";
	cin >> pathToFile;
	

	generateHuffmanTree( getFileContents("D:/test.txt") );
}





