
/*
*  Student: Soukaina Salihi
*  Course: CIT-237
*  This project involves writing a C++ program
*  that allows the user to convert a "pipe-delimited"
*  text file to a file in csv format and vice versa
*/

#include<iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <ctime>
#include <algorithm>
using namespace std;


// functions header types
void showArrayTxt(string[], int);
void showArrayCsv(string[], int);
int parseLineToArray(string inputText, string inputDelim, string outputDataValue[], int maxFields);
void openInputFile();
void openOutputFile();
void displayMenu();
bool readDataLine(string& recordText);
void outputArray(string[], int);




//  Global variables
ifstream inputFile;
ofstream outputFile;
string inputFileName;
string outputFileName;

int main(){

	// declar variables and array of strings
	const int MAX_SAMPLE_SIZE = 25;
	string arr1[MAX_SAMPLE_SIZE];
	int sampleSize = 0;
	char choice;
	string inputBuffer, delimeterChoice;
	do
	{
		// ask the user to enter the command chosen from the help menu
		cout << "\nCommand: ";
		// get the user input which is the first letter and ignore the rest
		cin >> choice; cin.ignore(80, '\n');

		// switch case to execute each case separately by calling the convenient functions
		switch (toupper(choice))
		{
			// case I: call the function openInputFile() which prompt for filename and open file for input.
		case 'I':
			openInputFile();
			break;

			// case O: call the function openOuputFile() which prompt for filename and open file for ouput.
		case 'O':
			openOutputFile();
			break;

			// case P: process data by calling parseLineToArray() and showArrayTxt() functions
		case 'P':

			// ask the user to enter a delimeter if they want to if not the program will process the "|" by default
			cout << "\nEnter a desirded delimeter or press the enter key to process by default : ";
			// get the user input which is the first char and ignore the rest
			delimeterChoice = cin.get();

			// keeps reading data until it reaches the end of the file, that when the function readDataLine(inputBuffer)returns false 
			while (readDataLine(inputBuffer))
			{
				// if the user just hit enter in the delimeter choice the delimeter will be "|" by default
				if (delimeterChoice == "\n"){
					// check if the user want to process the file in txt mode
					if (inputFileName.find(".txt") != string::npos){
						// call the fuction parseLineToArray() that takes each line and devide it to stings depending on 
						// the delimeter and store it in a string array and returns the size of array for each line 
						sampleSize = parseLineToArray(inputBuffer, "|", arr1, MAX_SAMPLE_SIZE);
						// output the processed data to a file from txt to csv format
						showArrayTxt(arr1, sampleSize);
					}
					// check if the user want to process the file in csv mode
					else if (inputFileName.find(".csv") != string::npos){
						// call the fuction parseLineToArray() that takes each line and devide it to stings depending on 
						// the delimeter and store it in a string array and returns the size of array for each line 
						sampleSize = parseLineToArray(inputBuffer, ",\"", arr1, MAX_SAMPLE_SIZE);
						// output the processed data to a file from csv to txt format
						showArrayCsv(arr1, sampleSize);
					}
					outputFile << endl;
				}
				// this part will be executed if the user choose a different delimeter
				else{
					// check if the user want to process the file in txt mode
					if (inputFileName.find(".txt") != string::npos){
						// call the fuction parseLineToArray() that takes each line and devide it to stings depending on 
						// the delimeter and store it in a string array and returns the size of array for each line 
						sampleSize = parseLineToArray(inputBuffer, delimeterChoice, arr1, MAX_SAMPLE_SIZE);
						// output the processed data to a file from txt to csv format
						showArrayTxt(arr1, sampleSize);
					}
					// check if the user want to process the file in csv mode
					else if (inputFileName.find(".csv") != string::npos){
						// call the fuction parseLineToArray() that takes each line and devide it to stings depending on 
						// the delimeter and store it in a string array and returns the size of array for each line 
						sampleSize = parseLineToArray(inputBuffer, delimeterChoice, arr1, MAX_SAMPLE_SIZE);
						// output the processed data to a file from csv to txt format
						showArrayCsv(arr1, sampleSize);
					}
					outputFile << endl;

				}

			}

			break;

			// case H: call the function displayMenu() that displays the help menu
		case 'H': displayMenu();
			break;

		default:
			// error message if the user types something that is not a letter
			cout << "\n Please enter one of the letter shown in the help menu!! " << endl;

		}// end of the switch case

		// while loop that keeps looping with any character the user enters but it breaks only with Q (exit)
	} while (toupper(choice) != 'Q');


}



/*=============================================================================
*	Function:	parseLineToArray  -	Scan through one line of text, output fields to array.
*  Inputs:
*		inputText =				string containing one line of text.
*		inputDelim =			string containing the delimiter character
*								(separates one data field from the next).
*
*  Outputs:
*		return value = number of fields parsed.
*		outputDataValue[] = output values
*
*  Desciption:
*		Starting at the beginning of the inputText string, scan for each
*		occurrence of the inputDelimiter character.  The first data field begins
*		at the starting position and ends at the position before the delimiter
*		character.
*		The SECOND data field begins at the position AFTER the delimiter, and
*		extends to the position before the NEXT ocurrence of the delimiter.
*		If no delimiter is found, the the current data field extends to the
*		end of the line.
*
*---------------------------------------------------------------------------*/

int parseLineToArray(string inputText, string inputDelim,
	string outputDataValue[], int maxFields)
{
	//	Local Variables:
	int nextFieldPosition = 0;		//	Start position of data field.
	int foundPosition;				//  Position where delimiter was found,
	int parsedFieldCount = 0;		//  Number of data fields parsed so far,
	bool endOfLine = false;			//	Flag -- end of input line detected,
	string dataField;				//  Copy of the data field.

	while (!endOfLine)
	{
		foundPosition = inputText.find(inputDelim, nextFieldPosition);
		if (foundPosition == -1)
		{
			// (Here if the string 'find' function reached the end of the input string.)
			endOfLine = true;
			foundPosition = inputText.length();

			if (foundPosition > nextFieldPosition)
			{
				dataField = inputText.substr(nextFieldPosition,
					foundPosition - nextFieldPosition);
				parsedFieldCount++;
			}
		}
		else
		{
			// (Here if 'inputDelim' was found in the input string.)
			// Copy the data field contents from the input string to 'dataField'
			// local variable.
			dataField = inputText.substr(nextFieldPosition, foundPosition - nextFieldPosition);
			parsedFieldCount++;

			// Adjust 'nextFieldPosition' as preparation for finding NEXT delimiter.
			nextFieldPosition = foundPosition + 1;
		}

		if (parsedFieldCount > 0)
		{
			if (parsedFieldCount > maxFields)
			{
				cout << "ERROR at line __LINE__: too many input fields, parsedFieldCount="
					<< parsedFieldCount << endl;
			}
			else
			{
				outputDataValue[parsedFieldCount - 1] = dataField;
			}
		}
	} // (end while)

	return parsedFieldCount;
} // (end function parseLineToArray )


void openOutputFile()
{
	// Output file:  prompt for filename, open file for output.
	cout << "Enter name of output file: ";
	getline(cin, outputFileName);
	outputFile.open(outputFileName);

	// Check for file open error.
	if (outputFile.fail())
	{
		cout << "(line " << __LINE__ << ") Error opening file:  " << outputFileName << endl;
	}
	outputFile << fixed << setprecision(2);
} // (end function openOutputFile)

// function that displays the help menu and let the user know the supported commands
void displayMenu()
{
	cout << "\n Supported commands:                        " << endl;
	cout << "\t\t   i:      Open intput file (txt/csv)     " << endl;
	cout << "\t\t   o:      Open output file (txt/csv)     " << endl;
	cout << "\t\t   p:      Process data                   " << endl;
	cout << "\t\t   H:      Print this help text           " << endl;
	cout << "\t\t   Q:      Exit the program               " << endl;

} //end of displayMenu()

void openInputFile()
{
	// Input file:  prompt for filename, open file for input.
	cout << "Enter name of input file: ";
	getline(cin, inputFileName);
	inputFile.open(inputFileName);

	// Check for file open error.
	if (inputFile.fail())
	{
		cout << "(line " << __LINE__ << ") Error opening file:  " << inputFileName << endl;
	}

} // (end function openInputfile)

//===========================================================
// readDataLine:  read one line from input file, 
//                or return false if end-of-file
//-----------------------------------------------------------
bool readDataLine(string& recordText)
{
	getline(inputFile, recordText);
	if (inputFile)
	{
		return true;
	}
	else
	{
		cout << "End of file encountered. " << endl;
		return false;
	}
}


// ********************************************************
// The showArrayTxt function outputs the contents of the array
// to the  outputFile (already open), from txt to csv format
// The size parameter is the number of elements.  
// ********************************************************
void showArrayTxt(string values[], int size)
{
	// start psition and end position of each quotes inside the field
	int startPosition, endPosition;
	// loop through the array 
	for (int count = 0; count < size; count++){
		// check if a psition for "\"" found inside the field
		if ((values[count].find("\"") != string::npos))
		{
			// store the position found by the function find() in the variable startPosition 
			startPosition = values[count].find("\"");
			// store the position found by the function rfind() in the variable endPosition 
			// rfind() start searching for the character from the end of the string toward the begining
			endPosition = values[count].rfind("\"");

			// replace whatever found in startPosition (which is "\"" 1 char) with "\"\""
			values[count].replace(startPosition, 1, "\"\"");
			// replace whatever found in endPosition (which is "\"" 1 char) with "\"\""
			values[count].replace(endPosition + 1, 1, "\"\"");
			// output the field in between two "\"" and comma at the end
			outputFile << "\"" << values[count] << "\",";

		}
		// check if a psition found for "," 
		else if (values[count].find(',') != string::npos)

			// output the field in between two "\"" and comma at the end
			outputFile << "\"" << values[count] << "\",";
		else
			// output the field with comma at the end
			outputFile << values[count] << ",";
	}
	outputFile << endl;
}// end of showArrayTxt


// ********************************************************
// The showArrayCsv function outputs the contents of the array
// to the  outputFile (already open), from csv to txt format
// The size parameter is the number of elements.  
// ********************************************************
void showArrayCsv(string values[], int size){

	// start psition and end position of each any quotes or comma inside the field
	int startPosition, endPosition, anyPosition;

	for (int count = 0; count < size; count++){

		// check if a psition for "\"," found inside the field
		if ((values[count].find("\",") != string::npos)){
			// store the position found by the function find() in the variable anyPosition 
			anyPosition = values[count].find("\",");
			// replace whatever found in anyPosition (which is "\",") with "\"\""
			values[count].replace(anyPosition + 1, 1, "|");
		}

		// in this part find any string that has comma and between quotes/and take of those quotes
		// check if a psition for "," found inside the field
		if (values[count].find(",") != string::npos)
		{
			if ((values[count].find("\"") != string::npos) && (values[count].rfind("\"") != string::npos)){
				startPosition = values[count].find("\"");
				endPosition = values[count].rfind("\"");
				values[count].replace(startPosition, 1, "");
				values[count].replace(endPosition - 1, 1, "");
			}

			// if only comma found but not the quotes just replace all commas with '|'
			else{

				std::replace(values[count].begin(), values[count].end(), ',', '|');

			}

		}
		// in this part replace all 3 quotes " \"\"\" " if found at the begining of the string with only one quotes
		if ((values[count].find("\"\"\"") != string::npos))
		{
			startPosition = values[count].find("\"\"\"");
			values[count].replace(startPosition, 3, "\"");

		}
		// in this part replace all 3 quotes " \"\"\" " if found at the end of the string with only one quotes
		if ((values[count].rfind("\"\"\"") != string::npos)){

			endPosition = values[count].rfind("\"\"\"");
			values[count].replace(endPosition, 3, "\"");

		}
		// in this part replace all 2 quotes " \"\"" if found at the begining of the string with only one quotes
		if ((values[count].find("\"\"") != string::npos))
		{
			startPosition = values[count].find("\"\"");
			values[count].replace(startPosition, 2, "\"");

		}
		// in this part replace all 2 quotes " \"\" " if found at the begining of the string with only one qutes
		if ((values[count].rfind("\"\"") != string::npos)){
			endPosition = values[count].rfind("\"\"");
			values[count].replace(endPosition, 2, "\"");

		}
		// check if this is the last field to be outputed in the line, if yes don't output the '|' at the end
		// if not just print the field with delimeter '|'
		if (count + 1 == size)

			outputFile << values[count];
		else
			outputFile << values[count] << '|';
	}

}// end of showArrayCsv
