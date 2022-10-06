/*

Classes from source SDK
https://github.com/ValveSoftware/source-sdk-2013/tree/master/mp/src/public/dt_recv.h

*/
#include <windows.h>


class RecvTable;

// Properties
class RecvProp
{
public:

	const char* m_pVarName;
	void* m_RecvType;
	int	m_Flags;
	int	m_StringBufferSize;
	bool m_bInsideArray;		
	const void* m_pExtraData;
	RecvProp* m_pArrayProp;
	void* m_ArrayLengthProxy;
	void* m_ProxyFn;
	void* m_DataTableProxyFn;
	RecvTable* m_pDataTable;
	int m_Offset;
	int	m_ElementStride;
	int	m_nElements;
	const char* m_pParentArrayPropName;
};

// Data table
class RecvTable
{
public:
	RecvProp* m_pProps;
	int	m_nProps;
	void** m_pDecoder;
	const char* m_pNetTableName;
	bool m_bInitialized;
	bool m_bInMainList;
};

// Client class (linked list) hence the m_pNext
class ClientClass
{
public:
	void* m_pCreateFn;
	void* m_pCreateEventFn;
	const char* m_pNetworkName;
	RecvTable* m_pRecvTable;
	ClientClass* m_pNext;
	int m_ClassID;
};


// Entity list
class IClientEntityList
{
public:
	virtual void* GetClientNetworkable(int entnum) = 0;
	virtual void* GetClientNetworkableFromHandle(DWORD hEnt) = 0;
	virtual void* GetClientUnknownFromHandle(DWORD hEnt) = 0;
	virtual void* GetClientEntity(int entnum) = 0;
	virtual void* GetClientEntityFromHandle(DWORD hEnt) = 0;
	virtual int	NumberOfEntities(bool bIncludeNonNetworkable) = 0;
	virtual int	GetHighestEntityIndex(void) = 0;
	virtual void SetMaxEntities(int maxents) = 0;
	virtual int	GetMaxEntities() = 0;
};

// Function at 8th index to get classes
// 8th index just like in the source-sdk code
class IBaseClientDLL {
public:
	virtual void fn0() = 0;
	virtual void fn1() = 0;
	virtual void fn2() = 0;
	virtual void fn3() = 0;
	virtual void fn4() = 0;
	virtual void fn5() = 0;
	virtual void fn6() = 0;
	virtual void fn7() = 0;

	virtual ClientClass* GetAllClasses() = 0;
};
