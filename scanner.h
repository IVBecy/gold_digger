/*

Loop through all the patterns and offsets

*/
#pragma once
#include <fstream>
#include "headers/pattern.h"
#include "headers/interface.h"
#include "headers/netvars.h"
#include "headers/utils.h"

using json = nlohmann::json;


// Getting data from the offset array
json processOffsetArray(json parent,json offsetArray){
	if (parent.contains("offsets")) {
		return offsetArray[0];
	}
	return 0;
}

class scannerClass
{
public:
	json sigs;
	std::ofstream out;
	ClientClass* clientClass;

	// File info and headers
	void fileStart() {
		out << "#pragma once\n#include <cstdint>\n";
		out << "constexpr ::std::int64_t timestamp = " << std::time(NULL) << "\n\n";
	}

	// Signature scanning
	void Signatures() {
		out << "// Signatures\n";
		out << "namespace signatures {\n";
		for (auto& s : sigs["signatures"]) {
			patternData sigData = comboConvert(s["pattern"].get<std::string>().c_str());
			try {
				json offsetArray = processOffsetArray(s, s["offsets"]);
				DWORD offset = ReadAddress(s["module"].get<std::string>().c_str(), sigData.bytes, sigData.mask, offsetArray, s["extra"], s["relative"]);
				out << "constexpr uintpty" << s["name"].get<std::string>() << " = " << hex(offset) << "; \n";
			}
			catch (json::type_error& ex) {
				continue;
			}
		}
		out << "}";
	}

	// Netvar scanning
	void Netvars() {
		out << "\n// Netvars\n";
		out << "namespace netvars {\n";
		for (auto& netvar : sigs["netvars"]) {
			try {
				int dataOffset;
				bool reMatch = regexComp(netvar["prop"].get<std::string>().c_str(), arrayOffset);
				dataOffset = (strcmp(netvar["prop"].get<std::string>().c_str(), netvar["name"].get<std::string>().c_str()) && reMatch == false) ? dataOffset = netvar["offset"].get<int>() : dataOffset = 0;
				uintptr_t offset = GetNetvarOffset(netvar["table"].get<std::string>().c_str(), netvar["name"].get<std::string>().c_str(), clientClass, netvar["prop"].get<std::string>().c_str(), dataOffset);
				out << "constexpr ::std::ptrdiff_t " << netvar["name"].get<std::string>() << " = " << hex(offset) << ";\n";
			}
			catch (json::type_error& ex) {
				out << ex.what();
				continue;
			}
		}
		out << "}";
	}

	// Clean Up
	void cleanUp() {
		out.close();
	};
};

void Scanner() {

	// Loading all the needed interfaces
	IBaseClientDLL* baseClient = (IBaseClientDLL*)GetInterface("VClient018", "client.dll");
	IClientEntityList* baseEngine = (IClientEntityList*)GetInterface("VEngineClient014", "engine.dll");
	IClientEntityList* entityList = (IClientEntityList*)GetInterface("VClient018", "client.dll");
	ClientClass* clientClass = baseClient->GetAllClasses();

	// Load file paths
	paths p = pathLocator();

	// Load up scanner
	scannerClass scanOps(readFromJsonFile(p.config.string().c_str()), std::ofstream(p.outFile.string().c_str()), clientClass);

	// Run the scan for offsets
	scanOps.fileStart();
	scanOps.Signatures();
	scanOps.Netvars();
	scanOps.cleanUp();
}