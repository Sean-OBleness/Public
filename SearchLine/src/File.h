#ifndef FILE_H_SEARCHLINE
#define FILE_H_SEARCHLINE

#include "Entry.h"
#include "Vector.h"
#include "BetterString.h"

class File
{
private:
	Vector<Entry> _entries;
	BString _name; //is full path
	int _instances;
public:
	File();
	File(BString& name);
	File(File& f);
	~File() { };
	void addEntry(Entry& e);
	Entry& getEntry(int index);
	BString name();
	int instances();
}

File::File() : _name(100)
{
	_instances = 0;
	_name = "Default";
}

File::File(BString& name) : _name(100) 
{
	_instances = 0;
	_name = name;
}

File::File(File& f) : _name(100)
{
	_instances = e._instances;
	_name = e.name;
	_entries = e._entries;
}

void File::addEntry(Entry& e)
{
	_entries.add(e);
	_instances++;
}

Entry& File::getEntry(int index)
{
	if(index > _entries.size()-1)
		return _entries[_entries.size - 1];
	if(index < 0)
		return _entries[0];
	
	return _entries[index];

}

BString File::name()
{
	return _name;
}

int File::instances()
{
	return _instances;
}

#endif
