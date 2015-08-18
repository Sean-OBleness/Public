#ifndef 206269e0_393b_11e5_b36d_0862664ad4ff_FILE_H
#define 206269e0_393b_11e5_b36d_0862664ad4ff_FILE_H


#include "BetterString.h"
#include "Exception.h"
#include "Vector.h"
#include "Entry.h"

class FileException : public ArrayException { };

class File()
{
private:
	BString& _filename;
	Vector<Entry&> _entries;
public:
	File();
	File(Bstring& f_name);
	File(const File& f);
	~File();
	void addEntry(const Entry& e);
	Entry& getEntry(int index);
	BString& name();

}

File::File() : _filename(100)
{
	_filename = "Default";
}

File::File(BString& f_name)
{
	_filename = f_name;
}

File::File(const File& f)
{
	_filename = f._filename;
	_entries = f._entries;
}

BString& File::name()
{
	return _filename;
}

File::~File()
{
	delete[] _entries;
}

void File::addEntry(const Entry& e)
{
	_entries.add(e);
}

Entry& File::getEntry(int index)
{
	if (index > _entries.size()) throw FileException();

	return _entries[index];
}

#endif
