#ifndef FILELIST_H_SEARCHLINE
#define FILELIST_H_SEARCHLINE

#include "BetterString.h"
#include "Entry.h"
#include "File.h"
#include "Vector.h"

class FileList
{
private:
	Vector<File> _files;
	BString _name;
	int _size;
public:
	FileList();
	FileList(BString& name);
	FileList(FileList& f);
	~FileList() { };
	void addFile(File& f);
	File& getFile(int index);
	int size();
}

#endif
