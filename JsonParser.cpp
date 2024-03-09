#include "JsonParser.h"
#include "iostream"
#include <fstream>

using namespace std;

JsonParser::JsonParser()
{
}

json JsonParser::loads(string json_string)
{
	json result;
	try {
		result = json::parse(json_string);
		return result;
	}
	catch (json::parse_error& ex) {
		cout << ex.what() << endl;
		throw "json decoding error";
	}
}

string JsonParser::dumps(json data)
{
	string result;
	try {
		result = data.dump(2);
		return result;
	}
	catch (exception) {
		throw "json encoding error";
	}
}

json JsonParser::loads_from_file(string filename)
{
	string line = "";
	try {
		ifstream in(filename);
		json result = json::parse(in);
		in.close();
		return result;
	}
	catch (json::parse_error& ex) {
		throw "file " + filename + " does not exist";
	}
}

void JsonParser::dumps_to_file(string filename, json data)
{
	string result = this->dumps(data);
	try {
		ofstream outfile;
		outfile.open(filename);
		if (outfile.is_open())
		{
			outfile << result;
		}
		outfile.close();
		cout << "result has written in " << filename << endl;
	}
	catch (exception) {
		throw "outfile is not a file path";
	}
}

void JsonParser::validate_document(json document)
{
	if (!document.contains("notes")) {
		throw "notes expected";
	}

	if (!document["notes"].is_object()) {
		throw "notes must be dict";
	}

	if (document.contains("classes") && !document["classes"].is_object()) {
		throw "classes must be dict";
	}
}

void JsonParser::validate_note(json note)
{
	if (!note.is_object()) {
		throw "note must be dict[str, int | list[int]]";
	}

	for (auto it = note.begin(); it != note.end(); ++it)
	{
		if (!(it.value().is_number_integer() || it.value().is_array())) {
			throw "property value must be list[int] | int";
		};
		if (it.value().is_array()) {
			if (sizeof(it.value()) == 0) {
				throw "property value cannot be empty list";
			};
			for (auto iv = it.value().begin(); iv != it.value().end(); ++iv) {
				if (!iv.value().is_number_integer()) {
					throw "property value must be list[int] | int";
				};
			}
		}
	}
}

void JsonParser::validate_rules(json rules)
{
	if (!rules.is_object()) {
		throw "rules must be declared as dict";
	}

	for (auto it = rules.begin(); it != rules.end(); ++it) {
		if (it.key() == "properties") {
			if (!(it.value().is_array() || it.value().is_string())) {
				throw "rule \'properties\' must be list[str] or str";
			}
			if (it.value().is_array()) {
				for (auto iv = it.value().begin(); iv != it.value().end(); ++iv) {
					if (!(iv.value().is_string())) {
						throw "rule \'properties\' must be list[str] or str";
					}
				}
			}
		}
		else if (it.key() == "count") {
			if (!rules.contains("properties")) {
				throw "cannot use rule \'count\' without rule \'properties\'";
			}
			if (!it.value().is_object()) {
				throw "rule \'count\' must be dict[str, int]";
			}
			for (auto iv = it.value().begin(); iv != it.value().end(); ++iv) {
				json::iterator index = find(rules["properties"].begin(), rules["properties"].end(), iv.key());
				if (index == rules["properties"].end()) {
					string message = "property " + iv.key() + " declared in rule \'count\' have not declared in rule \'properties\'";
					throw message;
				}
				if (!iv.value().is_number_integer()) {
					throw "rule \'count\' must be dict[str, int]";
				}
			}
		}
		else if (it.key() == "values") {
			if (!rules.contains("properties")) {
				throw "cannot use rule \'values\' without rule \'properties\'";
			}
			if (!it.value().is_object()) {
				throw "rule \'values\' must be dict[str, int | list[int]]";
			}
			for (auto iv = it.value().begin(); iv != it.value().end(); ++iv) {
				json::iterator index = find(rules["properties"].begin(), rules["properties"].end(), iv.key());
				if (index == rules["properties"].end()) {
					throw "property " + iv.key() + " declared in rule \'values\' have not declared in rule \'properties\'";
				}
				if (!(iv.value().is_number_integer() || iv.value().is_array())) {
					throw "rule \'values\' must be dict[str, int | list[int]]";
				}
				if (iv.value().is_array()) {
					for (auto ivv = iv.value().begin(); ivv != iv.value().end(); ++ivv) {
						if (!ivv.value().is_number_integer()) {
							throw "rule \'values\' must be dict[str, int | list[int]]";
						}
					}
				}
			}
		}
		else {
			throw "can't parse rule " + it.key() + "!";
		}
	}
}

