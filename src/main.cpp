//
// EPITECH PROJECT, 2019
// 302separation
//

#include "header.h"

int main(int argc, char *argv[])
{
	if(argc <= 2 || argc >= 5) //Check if there are any arguments
	{
		cerr << "Error: arguments\n";
		return 84;
	}
	else if (strcmp(argv[1], "-h") == 0) //Check for the -h command
	{
		cout << "USAGE\n\
	./302separation file [n | p1 p2]\n\
DESCRIPTION\n\
	file	file that contains the list of Facebook connections\n\
	n	maximum length of the paths\n\
	pi	name of someone in the file\n" << endl;
		return 0;
	}

	ifstream file(argv[1]);
	vector<pair<string, string>> list;

	file.seekg(0, file.end);
	if (file.tellg() == 0)
	{
		cerr << "Empty file\n";
		file.close();
		return 84;
	}
	else if (file) //Check if the file exists
	{
		file.seekg(0, file.beg);
		list = fileToList(file);
	}	
	else 
	{
   		cerr << "File Error\n";
		return 84;
	}
	
	if(list.size() == 0) //Check for file invalid
		return 84;
	if (argc == 4) //Conexion between 2 people
	{
		string person1 = string(argv[2]), person2 = string(argv[3]);
		findConexion(list, person1, person2);
	}
	else //Find Matrix
	{
		int maxLen;
		try
		{
			maxLen = stoi(argv[2]);
		}
		catch (const std::exception&)
		{
			cerr << "Argument n not a number\n";
			return 84;
		}
		findMatrix(list, maxLen);
	}

	
	return 0;
}