#ifndef SEARCHLINEGUI_CPP
#define SEARCHLINEGUI_CPP

#include "BetterString.h"
#include "Entry.h"
#include "File.h"
#include "FileList.h"
#include "ArrayClass.h"
#include "Vector.h"
#include <ctype.h>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string>

//prototypes
ArrayClass<int> computeNext(BString& pattern);
int KMPStringMatch(BString& T, BString& P);
void SearchFile(BString& target, string filename, FileList& currentCollection);

int main()
{
	FileList currentCollection;
	cout << "ENTER FILE TO SEARCH: ";
	string filename;
	cin >> filename;

	cout << '\n' << "Enter String to look for: ";
	char* tmp = new char[200];
	cin >> tmp;
	BString target(tmp);
	cout << '\n';

	SearchFile(target, filename, currentCollection);

	for(int i =0; i < currentCollection.size(); ++i)
	{
		File* pfile= currentCollection.getFile(i);
		cout << pfile->name() << '\n';
		for(int j = 0; j < pfile->instances(); ++j)
		{
			Entry* pentry = pfile->getEntry(j);
			cout << pentry->line() << " : " << pentry->contents() << '\n';
		}
	}

	cout << '\n';
	return 0;
}

void SearchFile(BString& target, string filename, FileList& currentCollection)
{
	char c;
	bool addFileToCollection = false;
	int lineNumber =0;
	ifstream SearchFile(filename.c_str());//
	BString test(filename.c_str());

	//make a new freestore file
	File* tmp = new File(test);

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
					//set bool to add file
					addFileToCollection = true;
					//create new entry and add to tmp file
					Entry* tmpentry = new Entry(MyLine, lineNumber);
					tmp->addEntry(tmpentry);
					
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
		return;
	}//!argv[2]

	if(addFileToCollection)
		//cout << " adding Entry \n";
		currentCollection.addFile(tmp);

	return;

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


#endif
