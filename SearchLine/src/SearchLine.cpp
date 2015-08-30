//Written By Sean O'Bleness 
//July 2015


#include "BetterString.h"
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include "ArrayClass.h"
#include "Vector.h"


using std::cout;

//prototypes
void Help();
ArrayClass<int> computeNext(BString& pattern);
int KMPStringMatch(BString& T, BString& P);

//main
int main(int argc, char *argv[])
{

	if(argc != 3)
	{
		cout << "\nERROR: incorrect number of args:" << argc << "\n";
		Help();
		return 1;		
	}
	

	char c;
	BString target = argv[1];	
	int lineNumber =0;

	ifstream SearchFile(argv[2]);
	if(SearchFile.is_open())
	{
		Vector<char> buffer;
		while (SearchFile.get(c))
		{	
			if(c == '\n')
			{	
				++lineNumber;
				BString MyLine;
				MyLine = MyLine.convertFromVector(buffer);
				buffer.clear();
				int result = KMPStringMatch(MyLine, target);
				if(result > -1)
				{
					cout << argv[2] << ": " << lineNumber << "\n" << MyLine << "\n\n";
				}//result>-1

			}//c == '\n'
			else
			{
				buffer.add(c);
			}//c != '\n'
		}//
		
	}//argv[2]
	else
	{
		cout << "ERROR: Could not find file.\n";
	}//!argv[2]

	return 0;
}

ArrayClass<int> computeNext(BString& pattern)
{
	int p;
	int q;
	ArrayClass<int> next(pattern.length(), 0);
	for (p = 2; p < pattern.length(); p++) //p is right end
	{
		q = next[p-1]; // q is presumed value of next[p]-1
		do
		{
			if(q >= 0)
			{
				if(pattern[q] == pattern[p])
				{
					next[p] = q + 1;
					break;
				}//(pattern[q] == pattern[p])
				else
				{
					if (q == 0)
						break;
					else
						q = next[q-1];
				}//(pattern[q] != pattern[p])
			}//(q>=0)
		} while (q >= 0);
	}//(p = 2; p < pattern.length(); p++)
	return next;
}

//returns index of start of P in T 
//or -1 if P is not a substring of T
int KMPStringMatch(BString& T, BString& P)
{
	if(P.length() == 0)
		return 0; //0 length string is always a substring
	if(T.length() == 0)
		return -1; //0 length string has no substrings
	ArrayClass<int> next = computeNext(P);
	int pPos = 0;
	int tPos = 0;
	while(tPos < T.length())
	{
		if(P[pPos] == T[tPos])//matched so far
		{
			pPos++;
			tPos++;
		}//(P[pPos] == T[tPos])
		else//mismatch
		{
			if(next[pPos] <= 0)
			{
				tPos++;
				pPos = 0;
			}//(next[pPos] <= 0)
			else
			{
				pPos = next[pPos-1];
			}//!(next[pPos] <= 0)
		}
	
		if(pPos == P.length())
		{
			//matched whole pattern. now return
			//starting position
			return(tPos - P.length());
		}//(pPos == P.length())
	
	}//while(tPos < T.length())	
	return -1;
}


//some help text
void Help()
{
	cout << "HELP TEXT HERE\n";
}





