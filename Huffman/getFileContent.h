#ifndef getFileContent
#define getFileContent

#include<string>
#include<fstream>

using namespace std;

string getFileContents(string pathToFile){
	ifstream input(pathToFile);
	string inputString;

	for (string line; getline(input, line); ) {
		inputString.append(line + "\n");
		//inputString.append(line);
	}
	return inputString;
}


#endif
