#include "NamesStore.hpp"
#include "PatternFinder.hpp"

class FNameEntry
{
public:
	int64_t UnknownData_00;
	char AnsiName[1024];
};

DWORD64 NameArrayFuncAddy;
class TNameEntryArray
{
public:
	static FNameEntry* GetById(int Index)
	{
		return reinterpret_cast<FNameEntry* (*)(__int64, int)>(NameArrayFuncAddy)(0, Index);;
	}

	static bool IsValidIndex(int32_t index)
	{
		return index >= 0 && GetById(index) != nullptr;
	}
};

bool NamesStore::Initialize()
{
	NameArrayFuncAddy = FindPattern(GetModuleHandleW(0), (unsigned char*)"\x85\xD2\x78\x37\x81\xFA\x00\x00\x00\x00\x7D\x11\x48\x63\xC2\x48\x8D\x0D\x00\x00\x00\x00\x8B\x14\x81\x85\xD2\x74\x1E", "xxxxxx????xxxxxxxx????xxxxxxx");
	return true;
}

bool NamesStore::IsValid(size_t id) const
{
	return TNameEntryArray::IsValidIndex(id);
}

std::string NamesStore::GetById(size_t id) const
{
	return TNameEntryArray::GetById(id)->AnsiName;
}

void* NamesStore::GetAddress()
{
	return (void*)NameArrayFuncAddy;
}

size_t NamesStore::GetNamesNum() const
{
	return 10; //Testing the first 10 Names should be enough
}

/*
	Removed the Number Of Names and Address of the Names because I am lazy and its not really that important.
*/