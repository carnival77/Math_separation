#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

#define MIDDLE " is friends with"
#define SIZEM sizeof(MIDDLE)

//Recieve file name with a list of numbers
//Return the list of numbers in a vector type list
//Close the file at the end
vector < pair<string, string>> fileToList(ifstream &file);

void findMatrix(vector<pair<string, string>>, int);
void findConexion(vector<pair<string, string>>, string, string);
vector<string> getPeopleList(vector < pair<string, string>> &);
int findPerson(vector<string>&, string& );
void outVector(vector<string>&);
void outMatrix(int **, int);
void setValue(int ** , int, int);
int ** generateMatrix(int);
void populateAMatrix(int **, vector<pair<string, string>> &, vector<string>&);
void populateSPMatrix(int **, int, int);
bool areFriends(vector<pair<string, string>> &, string&, string&);
void copyMatrix(int **, int**, int);
void spTree(int **, int, int, int root);
void recursivePath(int **, int, int, int, int, int);