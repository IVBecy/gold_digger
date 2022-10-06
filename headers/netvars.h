/*

Functions for dumping netvars

*/

#pragma once

#include <windows.h>
#include "source_sdk_classes.h"

// Finding Offsets
uintptr_t GetOffset(RecvTable* table,const char* tableName,const char* netvarName){
	for (int i = 0; i < table->m_nProps; i++) {
		RecvProp prop = table->m_pProps[i];

		if (strcmp(prop.m_pVarName,netvarName) == 0) {
			return prop.m_Offset;
		}

		if(prop.m_pDataTable) {
			uintptr_t offset = GetOffset(prop.m_pDataTable,tableName,netvarName);

			if (offset) {
				return offset + prop.m_Offset;
			}
		}
	}
	return 0;
}

// Looping through the linked list to call `GetOffset`
uintptr_t GetNetvarOffset(const char* tableName,const char* netvarName,ClientClass* clientClass) {
	ClientClass* currentNode = clientClass;

	for (auto currentNode = clientClass; currentNode;currentNode = currentNode->m_pNext) {
		if (strcmp(tableName, currentNode->m_pRecvTable->m_pNetTableName) == 0) {
			return GetOffset(currentNode->m_pRecvTable, tableName, netvarName);
		}
	}
	return 0;
}