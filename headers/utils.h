/*

All the utility functions

*/
#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include "json.hpp"

using json = nlohmann::json;

// File locations
struct paths {
	std::filesystem::path pwd;
	std::filesystem::path config;
	std::filesystem::path outFile;
};
paths pathLocator() {
	paths p = { };
	p.pwd = std::filesystem::current_path();
	p.config = p.pwd / "config.json";
	p.outFile = p.pwd / "csgo.h";
	return p;
};


// Read from JSON file
json readFromJsonFile(const char* fileName) {
	json sigs;
	try {
		std::ifstream f(fileName);
		sigs = json::parse(f);
		f.close();
	}
	catch (json::parse_error& ex) {
		return 0;
	}
	return sigs;
};

// Convert mem to hex
std::string hex(uintptr_t offset) {
	std::ostringstream ss;
	ss << std::hex << "0x" << std::uppercase << offset;
	std::string result = ss.str();
	return result;
}
