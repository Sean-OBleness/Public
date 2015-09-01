#ifndef FILELIST_H_SEARCHLINE
#define FILELIST_H_SEARCHLINE

#include "Entry.h"
#include "File.h"
#include "Vector.h"

class FileList
{
private:
	Vector<File> _files;
	int _size;
public:
	FileList();
	FileList(FileList& f);
	~FileList() { };
	void addFile(File& f);
	File& getFile(int index);
	int size();
};

FileList::FileList()
{
	_size = 0;
}

FileList::FileList(FileList& f)
{
	_files = f._files;
	_size = f._size;
}

void FileList::addFile(File& f)
{
	_files.add(f);
	_size++;
}

File& FileList::getFile(int index)
{
	if(index > _files.size()-1)
		return _files[_files.size()-1];

	if(index < 0)
		return _files[0];

	return _files[index];
}

int FileList::size()
{
	return _size;
}

#endif
