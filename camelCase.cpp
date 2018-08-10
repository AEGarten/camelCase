#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct fileTraits {
	string justFileName;
	string newName;
	string pathFile;
	string path;
};


bool CheckFile(string);

//Returns a possibly shifted case of char, default to upper case
char ChangeCase(char workingChar, bool reverseMode = false);

string ConvertString(string);

void GetFileTraits(fileTraits &);


int main() {
	string workingString, flush;
	fileTraits userInput;
	bool fileGood = false;	
	ifstream baseFile;
	ofstream convertedFile;
	char proceed;
	
	cout << "This program takes in a text file path and outputs a new text file.\n"
		<< "This new file has all text entries (newline delimited) converted to camelCase.\n" << endl;
	cout << "ex:\n"
		<< "Full Text 1 		>>		fullText1\n"
		<< "^   ^    ^\n"
		<< "full  Text  two		>>		fullTextTwo\n"
		<< "    ^^    ^^^\n" << endl;
		
	do {
		do {
			cout << "Drag and drop a text file to terminal and press enter (type exit to quit) >";
			getline(cin, userInput.pathFile);
			
			if (userInput.pathFile == "exit")
				break;
				
			GetFileTraits(userInput);
			fileGood = CheckFile(userInput.pathFile);
		} while (!fileGood);
			
		if (fileGood) {
			fileGood = false;
			cout << endl;
			baseFile.open(userInput.pathFile);
			convertedFile.open(userInput.path + userInput.newName);
			
			while (!baseFile.eof()) {
				getline(baseFile, workingString);
				workingString = ConvertString(workingString);
				convertedFile << workingString;
				
				if (!baseFile.eof())
					convertedFile << endl;
			}
			baseFile.close();
			convertedFile.close();
			cout << userInput.justFileName + "  =>  converted  =>  " + userInput.newName << endl;
			cout << "Files found at:	" << userInput.path << endl << endl;
		}
		cout << "Another file? Type y and press enter >";
		proceed = 'n';
		cin >> proceed;
		getline(cin, flush);
	} while (proceed == 'y');

	cout << "Program complete." << endl;
	return 0;
}

void GetFileTraits(fileTraits &workingFile) {
	char index;	//low numbered index, char used for less memory
	string pathFile = workingFile.pathFile;
	char stringLength = pathFile.length();
	
	if (pathFile.at(stringLength - 1) == ' ') {
		pathFile.pop_back();
		--stringLength;
	}
	for (index = 0; index < stringLength; ++index) {
		if (pathFile.at(index) == '\\') {
			pathFile.erase(index, 1);	
			--stringLength;
			--index;
		}
	}
	workingFile.pathFile = pathFile;
	index = pathFile.rfind("/") + 1;
	workingFile.path = pathFile.substr(0, index);
	workingFile.justFileName = pathFile.substr(index);
	index = workingFile.justFileName.length() - 4;
	workingFile.newName = workingFile.justFileName.substr(0, index);
	workingFile.newName = ConvertString(workingFile.newName) + " cC.txt";
}

string ConvertString(string toBeWorked) {
	bool firstLetterCheck = false;
	char stringEnd = toBeWorked.length();

	for (char i = 0; i < stringEnd; ++i) {
		if (!firstLetterCheck) {
			char focus = toBeWorked.at(i);
			
			if (focus >= 'A' && focus <= 'z') {
				firstLetterCheck = true;
				toBeWorked.at(i) = ChangeCase(focus, true);
			}
		}
		if (toBeWorked.at(i) == ' ') {
			if (i + 1 < stringEnd)
				toBeWorked.at(i + 1) = ChangeCase(toBeWorked.at(i + 1));
			
			toBeWorked.erase(i, 1);	
			--stringEnd;
			--i;
		}
	}
	return toBeWorked;
}

//if reverseMode = true included in fn call convert to lower case, else convert to upper case
char ChangeCase(char workingChar, bool reverseMode) {
	
	if (reverseMode) {
		if (workingChar <= 'Z' && workingChar >= 'A')
			workingChar += 32;
		
	} else {
		if (workingChar <= 'z' && workingChar >= 'a')
			workingChar -= 32;
	}
	return workingChar;
}	

bool CheckFile(string titleToCheck) {
	ifstream testFile;
	bool isTextFile = !titleToCheck.compare(titleToCheck.length() - 4, 4, ".txt");
	
	if (isTextFile) {
		testFile.open(titleToCheck);
			
		if (testFile) {
			testFile.close();
			return true;
		}
		cout << "File not found." << endl;
		testFile.close();	
	} else {
		cout << "Only .txt files!" << endl;
	}
	return false;
}