#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

string get_contents(const char* filename)
{
	ifstream stream;
	stream.open(filename);
	stream.seekg(0, ios::end);
	
	int length = stream.tellg();
	stream.seekg(0, ios::beg);
	
	char buffer[length+1] = {0};
	
	if (buffer != NULL)
	{
		stream.read(buffer, length);
	}
	else 
	{
		cout << "Not enough memory for input file" << endl;
	}
	stream.close();
	
	return buffer;
}

void process(const char *inputfilename, const char *outputfilename)
{
	string contents = get_contents(inputfilename);
	cout << contents << endl;
}

int main()
{
	string input = "PreciseDB.txt";
	const char *inputfilename = input.c_str();
	string output = "first_trial.txt";
	const char *outputfilename = output.c_str();
	process(inputfilename, outputfilename);
	
	return 0;
}
