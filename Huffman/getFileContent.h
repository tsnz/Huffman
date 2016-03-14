#ifndef getFileContent
#define getFileContent

#include<string>
#include<fstream>

using namespace std;

string getFileContents(string pathToFile){
	ifstream input(pathToFile);
	if (!input) {
		system("cls");
		cout << "Datei " << pathToFile << "kann nicht geöffnet werden oder existiert nicht!\nProgramm wird beendet.\n";
		system("pause");
		exit(2);

	}
	string inputString;

	for (string line; getline(input, line); ) {
		inputString.append(line + "\n");
	}
	return inputString;
}
int getLineCount(string pathToFile) {
	ifstream inputfile(pathToFile);
	int linecount = 0;
	string line;

	while (getline(inputfile, line))
		++linecount;

	return linecount;
}




#endif
