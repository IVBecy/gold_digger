/*

All the utility functions

*/
#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <regex>
#include "json.hpp"

using json = nlohmann::json;

// Regex checker
inline std::regex const arrayOffset{ R"([m][_][a-zA-Z]*\[.*?\])" };
inline bool regexComp(const char* valueToScan, std::regex pattern) {
	bool match = std::regex_match(valueToScan, pattern);
	return match;
}

// File locations
struct paths {
	std::filesystem::path pwd;
	std::filesystem::path config;
	std::filesystem::path outFile;
};
inline paths pathLocator() {
	paths p = { };
	p.pwd = std::filesystem::current_path();
	p.config = p.pwd / "config.json";
	p.outFile = p.pwd / "csgo.h";
	return p;
};


// Read from JSON file
inline json readFromJsonFile(const char* fileName) {
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
inline std::string hex(uintptr_t offset) {
	std::ostringstream ss;
	ss << std::hex << "0x" << std::uppercase << offset;
	std::string result = ss.str();
	return result;
}
