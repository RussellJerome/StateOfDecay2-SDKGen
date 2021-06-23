#include "ObjectsStore.hpp"
#include "PatternFinder.hpp"
class FUObjectItem
{
public:
	UObject * Object;
	__int32 Flags;
	__int32 ClusterIndex;
	__int32 SerialNumber;
};

class TUObjectArray
{
public:
	FUObjectItem * Objects;
	__int32 MaxElements;
	__int32 NumElements;
};

class FUObjectArray
{
public:
	int ObjFirstGCIndex;
	int ObjLastNonGCIndex;
	int MaxObjectsNotConsideredByGC;
	bool OpenForDisregardForGC;
	TUObjectArray ObjObjects;
};

FUObjectArray* GlobalObjects;

bool ObjectsStore::Initialize()
{

	auto GObjectPattern = FindPattern(GetModuleHandleW(0), (unsigned char*)"\x48\x8D\x0D\x00\x00\x00\x00\x48\x8B\xD3\xE8\x00\x00\x00\x00\x85\xFF\x74\x22", "xxx????xxxx????xxxx");
	GlobalObjects = (FUObjectArray*)(GObjectPattern + *(DWORD*)(GObjectPattern + 0x3) + 0x7);

	return true;
}

void* ObjectsStore::GetAddress()
{
	return GlobalObjects;
}

size_t ObjectsStore::GetObjectsNum() const
{
	return GlobalObjects->ObjObjects.NumElements;
}

UEObject ObjectsStore::GetById(size_t id) const
{
	return GlobalObjects->ObjObjects.Objects[id].Object;
}
