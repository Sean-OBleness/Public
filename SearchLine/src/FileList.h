#ifndef FILELIST_H_SEARCHLINE
#define FILELIST_H_SEARCHLINE

#include "Entry.h"
#include "File.h"
#include "Vector.h"

class FileList
{
private:
	Vector<File*> _files;
public:
	FileList();
	FileList(FileList& f);
	~FileList() { };
	void addFile(File* f);
	File* getFile(int index);
	int size();
};

FileList::FileList()
{

}

FileList::FileList(FileList& f)
{
	_files = f._files;
}

void FileList::addFile(File* f)
{
	_files.add(f);
}

File* FileList::getFile(int index)
{
	if(index > _files.size()-1)
		return _files[_files.size()-1];

	if(index < 0)
		return _files[0];

	return _files[index];
}

int FileList::size()
{
	return _files.size();
}

#endif
