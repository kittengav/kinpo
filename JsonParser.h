#pragma once

#include <vector>
#include <string>
#include <nlohmann/json.hpp>

using namespace nlohmann;
using namespace std;

/************************************************
 *  JsonParser - parse, dumps and validate json file, or json string.
 ***********************************************/
class JsonParser
{
private:
	//! Allowed in json input names of class rules.
	vector<string> ALLOWED_KWORDS{ "properties", "values", "count" };
public:
	//! An empty constructor of JsonParser class.
	JsonParser();

	//! Parse json string by using nlohmann/json library.
	/*!
	\param json_string a string argument.
	\return the instance of json parsed from json_string.
	*/
	json loads(string json_string);

	//! Dumps json instance to string instance.
	/*!
	\param data a json argument.
	\return the instance of string dumped from data.
	*/
	string dumps(json data);

	//! Parse json from file by using nlohmann/json library.
	/*!
	\param filename a string argument.
	\return the instance of json parsed from data of file.
	*/
	json loads_from_file(string filename);

	//! Dumps json instance to string instance and writes it to file.
	/*!
	\param filename a string argument.
	\param data a json argument.
	*/
	void dumps_to_file(string filename, json data);

	//! validate types and values of input document on first level of json objects. If not valid - throws exception.
	/*!
	\param document a json argument.
	*/
	void validate_document(json document);

	//! validate types and values of current note. If not valid - throws exception.
	/*!
	\param note a json argument.
	*/
	void validate_note(json note);

	//! validate types and values of rules of current class. If not valid - throws exception.
	/*!
	\param rules a json argument.
	*/
	void validate_rules(json rules);
};

