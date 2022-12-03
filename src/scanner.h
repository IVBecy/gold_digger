/*

Loop through all the patterns and offsets

*/
#pragma once
#include <fstream>
#include "../headers/json.hpp"
#include "../headers/source_sdk_classes.h"

using json = nlohmann::json;


// Getting data from the offset array
json processOffsetArray(json parent, json offsetArray);

// Scanneing operation
class scannerClass
{
public:
	json sigs;
	std::ofstream out;
	ClientClass* clientClass;

	// File info and headers
	void fileStart();

	// Signature scanning
	void Signatures();

	// Netvar scanning
	void Netvars();

	// Clean Up
	void cleanUp();
};

// Main function for scanning
void Scanner();