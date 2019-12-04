#include "header.h"

vector<pair<string,string>> fileToList(ifstream &file)
{
	vector<pair<string, string>> list;
	pair<string, string> dummy;
	string temp;
	int pos;
	while (getline(file, temp))
	{
		pos = temp.find(MIDDLE);
		if (pos == -1)
		{
			list.clear();
			return list;
		}
		dummy.first = temp.substr(0, pos);
		dummy.second = temp.substr(pos + SIZEM);
		list.push_back(dummy);
	}
	file.close();
	return list;
}

void findMatrix(vector<pair<string, string>> conexion, int maxLen)
{
	vector<string> people = getPeopleList(conexion);
	outVector(people);
	int nPeople = people.size();

	int ** aMatrix = generateMatrix(nPeople);
	populateAMatrix(aMatrix, conexion, people);
	outMatrix(aMatrix, nPeople);
	cout << "\n";
	int ** spMatrix = generateMatrix(nPeople);
	if (maxLen >= 1)
	{
		copyMatrix(aMatrix, spMatrix, nPeople);
		populateSPMatrix(spMatrix, nPeople, maxLen);
		outMatrix(spMatrix, nPeople);
	}
	else
		outMatrix(spMatrix, nPeople);
}

void findConexion(vector<pair<string, string>> conexion, string a, string b)
{
	cout << "Degree of separation between " << a << " and " << b << ": ";

	vector<string> people = getPeopleList(conexion);
	int nPeople = people.size();
	int pos1 = findPerson(people, a);
	int pos2 = findPerson(people, b);

	if (pos1 == -1 || pos2 == -1)
	{
		cout << "-1\n";
		return;
	}
	if(pos1 == pos2)
	{ 
		cout << "0\n";
		return;
	}
	
	int ** aMatrix = generateMatrix(nPeople);
	populateAMatrix(aMatrix, conexion, people);

	int ** spMatrix = generateMatrix(nPeople);
	copyMatrix(aMatrix, spMatrix, nPeople);
	spTree(spMatrix, nPeople, nPeople - 1, pos1);
	cout << spMatrix[pos1][pos2] << "\n";

}

vector<string> getPeopleList(vector < pair<string, string>> & conexion)
{
	vector<string> people;
	for (int i = 0; i < (int)conexion.size(); i++)
	{
		if (findPerson(people, conexion[i].first) == -1)
			people.push_back(conexion[i].first);
		if (findPerson(people, conexion[i].second) == -1)
			people.push_back(conexion[i].second);
	}
	sort(people.begin(), people.end());
	return people;
}

int findPerson(vector<string>& list, string& person)
{
	for (int i = 0; i < (int)list.size(); i++)
		if (list[i] == person)
			return i;
	return -1;
}

void outVector(vector<string>& list)
{
	for (string x : list)
		cout << x << "\n";
	cout << "\n";
}

void outMatrix(int ** matrix, int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size - 1; j++)
		{
			cout << matrix[j][i] << " ";
		}
		cout << matrix[size - 1][i] << "\n";
	}
}

void setValue(int ** matrix, int size, int value)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			matrix[j][i] = value;
		}
	}
}

int ** generateMatrix(int size)
{
	int ** matrix = new int *[size];
	for (int i = 0; i < size; i++)	matrix[i] = new int[size];
	setValue(matrix, size, 0);
	return matrix;
}

void populateAMatrix(int ** matrix, vector<pair<string, string>> & conexion, vector<string>& people)
{
	int pos1, pos2;
	for (int i = 0; i < (int)conexion.size(); i++)
	{
		pos1 = findPerson(people, conexion[i].first);
		pos2 = findPerson(people, conexion[i].second);
		matrix[pos1][pos2] = 1;
		matrix[pos2][pos1] = 1;
	}
}

bool areFriends(vector<pair<string, string>> & conexion, string& person1, string& person2)
{
	for (int i = 0; i < (int)conexion.size(); i++)
	{
		if (conexion[i].first == person1 && conexion[i].second == person2)
			return true;
		else if (conexion[i].first == person2 && conexion[i].second == person1)
			return true;
	}
	return false;
}

void copyMatrix(int ** org, int** dest, int size)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			dest[i][j] = org[i][j];
}

void populateSPMatrix(int ** spMatrix, int size, int max)
{
	for (int i = 0; i < size; i++)
	{
		spTree(spMatrix, size, max, i);
	}
}

void spTree(int ** matrix, int size, int maxLen, int root)
{
	if (maxLen > size)
		maxLen = size - 1;

	for (int i = 0; i < size; i++)
		if (matrix[i][root] == 1)
			recursivePath(matrix, size, maxLen, i, root, 2);
}

void recursivePath(int ** matrix, int size, int maxLen, int tarjet, int root, int level)
{
	if (level > maxLen) return;
	for (int i = 0; i < size; i++)
		if (matrix[i][tarjet] == 1)
		{
			if (i != root && (matrix[i][root] == 0 || matrix[i][root] > level))
			{
				matrix[i][root] = level;
				matrix[root][i] = level;				
			}
			recursivePath(matrix, size, maxLen, i, root, level + 1);
		}
}