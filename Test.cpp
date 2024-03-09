#include "Test.h"
#include <string>
#include <iostream>
#include "JsonParser.h"
#include "NoteClass.h"
#include <nlohmann/json.hpp>


using namespace std;

void Test::run_tests()
{
	string result;
	int test_number = 0;

	try {
		test_number++;
		result = "test_validate_document";
		this->test_validate_document();
		test_number++;
		result = "test_validate_note";
		this->test_validate_note();
		test_number++;
		result = "test_validate_rules";
		this->test_validate_rules();
		test_number++;
		result = "test_validate_count";
		this->test_validate_count();
		test_number++;
		result = "test_validate_props";
		this->test_validate_props();
		test_number++;
		result = "test_has_value";
		this->test_has_value();
		test_number++;

	}
	catch (const char* message) {
		cout << test_number - 1 << " tests passed of 6." << endl;
		cout << "failed on " << "\'" << result << "\'" << endl;
		cout << "message: " << message << endl;
		return ;
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		cout << test_number - 1 << " tests passed of 6." << endl;
		cout << "failed on " << "\'" << result << "\'" << endl;
		cout << "message: " << message << endl;
		return ;
	}
	cout << "passed 6 tests of 6" << endl;
	return ;
}

void Test::test_validate_document()
{	
	JsonParser parser = JsonParser();
	json value = json();
	try {
		parser.validate_document(value);
	}
	catch (const char* message) {
		if (message != "notes expected") {
			throw  "got \'" + string(message) + "\'; expected 'notes expected'";
		}
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		if (message != "notes expected") {
			throw "got \'" + string(message) + "\'; expected 'notes expected'";
		}
	}


	value = json();
	value["some_key"] = 123;
	try {
		parser.validate_document(value);
	}
	catch (const char* message) {
		if (message != "notes expected") {
			throw  "got \'" + string(message) + "\'; expected 'notes expected'";
		}
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		if (message != "notes expected") {
			throw "got \'" + string(message) + "\'; expected 'notes expected'";
		}
	}

	value = json();
	value["classes"] = "not dictionary type";

	try {
		parser.validate_document(value);
	}
	catch (const char* message) {
		if (message != "notes expected") {
			throw  "got \'" + string(message) + "\'; expected 'notes expected'";
		}
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		if (message != "notes expected") {
			throw  "got \'" + string(message) + "\'; expected 'notes expected'";
		}
	}

	value = json();
	value["classes"] = json::object();
	try {
		parser.validate_document(value);
	}
	catch (const char* message) {
		if (message != "notes expected") {
			throw "got \'" + string(message) + "\'; expected 'notes expected'";
		}
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		if (message != "notes expected") {
			throw "got \'" + string(message) + "\'; expected 'notes expected'";
		}
	}

	value = json();
	value["classes"] = json::object();
	value["some_key"] = 123;

	try {
		parser.validate_document(value);
	}
	catch (const char* message) {
		if (message != "notes expected") {
			throw "got \'" + string(message) + "\'; expected 'notes expected'";
		}
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		if (message != "notes expected") {
			throw "got \'" + string(message) + "\'; expected 'notes expected'";
		}
	}

	value = json();
	value["notes"] = "not dictionary type";

	try {
		parser.validate_document(value);
	}
	catch (const char* message) {
		if (message != "notes must be dict") {
			throw "got \'" + string(message) + "\'; expected 'notes must be dict'";
		}
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		if (message != "notes must be dict") {
			throw "got \'" + string(message) + "\'; expected 'notes must be dict'";
		}
	}

	value = json();
	value["notes"] = json::object();

	try {
		parser.validate_document(value);
	}
	catch (const char* message) {
		throw "got \'" + string(message) + "\'; expected void";
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		throw "got \'" + string(message) + "\'; expected void";
		
	}

	value = json();
	value["notes"] = json::object();
	value["some_key"] = 123;

	try {
		parser.validate_document(value);
	}
	catch (const char* message) {
		throw "got \'" + string(message) + "\'; expected void";
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		throw "got \'" + string(message) + "\'; expected void";
	}

	value = json();
	value["notes"] = json::object();
	value["classes"] = "not dictionary type";

	try {
		parser.validate_document(value);
	}
	catch (const char* message) {
		if (message != "classes must be dict") {
			throw "got \'" + string(message) + "\'; expected 'classes must be dict'";
		}
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		if (message != "classes must be dict") {
			throw "got \'" + string(message) + "\'; expected 'classes must be dict'";
		}
	}

	value = json();
	value["notes"] = json::object();
	value["classes"] = json::object();

	try {
		parser.validate_document(value);
	}
	catch (const char* message) {
		throw "got \'" + string(message) + "\'; expected void";
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		throw "got \'" + string(message) + "\'; expected void";
	}

	value = json();
	value["notes"] = json::object();
	value["classes"] = json::object();
	value["some_key"] = 123;

	try {
		parser.validate_document(value);
	}
	catch (const char* message) {
		throw "got \'" + string(message) + "\'; expected void";
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		throw "got \'" + string(message) + "\'; expected void";
	}
}

void Test::test_validate_note()
{
	JsonParser parser = JsonParser();
	json value = json::object();
	try {
		parser.validate_note(value);
	}
	catch (const char* message) {
		if (message != "property value must be list[int] | int") {
			throw "got \'" + string(message) + "\'; expected 'property value must be list[int] | int'";
		}
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		if (message != "property value must be list[int] | int") {
			throw "got \'" + string(message) + "\'; expected 'property value must be list[int] | int'";
		}
	}
	
	value = json::object();
	value["prop1"] = "not int type";

	try {
		parser.validate_note(value);
	}
	catch (const char* message) {
		if (message != "property value must be list[int] | int") {
			throw "got \'" + string(message) + "\'; expected 'property value must be list[int] | int'";
		}
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		if (message != "property value must be list[int] | int") {
			throw "got \'" + string(message) + "\'; expected 'property value must be list[int] | int'";
		}
	}

	value = json::object();
	value["prop1"] = json::array();
	value["prop1"].push_back("not list[int] type");

	try {
		parser.validate_note(value);
	}
	catch (const char* message) {
		if (message != "property value must be list[int] | int") {
			throw "got \'" + string(message) + "\'; expected 'property value must be list[int] | int'";
		}
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		if (message != "property value must be list[int] | int") {
			throw "got \'" + string(message) + "\'; expected 'property value must be list[int] | int'";
		}
	}

	value = json::object();
	value["prop1"] = 123;
	value["prop2"] = "not list[int] type";

	try {
		parser.validate_note(value);
	}
	catch (const char* message) {
		if (message != "property value must be list[int] | int") {
			throw "got \'" + string(message) + "\'; expected 'property value must be list[int] | int'";
		}
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		if (message != "property value must be list[int] | int") {
			throw "got \'" + string(message) + "\'; expected 'property value must be list[int] | int'";
		}
	}

	value = json::object();
	value["prop1"] = 123;
	value["prop2"] = json::array();
	value["prop2"].push_back("not list[int] type");

	try {
		parser.validate_note(value);
	}
	catch (const char* message) {
		if (message != "property value must be list[int] | int") {
			throw "got \'" + string(message) + "\'; expected 'property value must be list[int] | int'";
		}
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		if (message != "property value must be list[int] | int") {
			throw "got \'" + string(message) + "\'; expected 'property value must be list[int] | int'";
		}
	}

	value = json::object();
	value["prop1"] = 123;
	value["prop2"] = json::array();
	value["prop2"].push_back(1);
	value["prop2"].push_back(2);

	try {
		parser.validate_note(value);
	}
	catch (const char* message) {
		throw "got \'" + string(message) + "\'; expected void";
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		throw "got \'" + string(message) + "\'; expected void";
	}

	value = json::object();
	value["prop1"] = json::array();

	try {
		parser.validate_note(value);
	}
	catch (const char* message) {
		if (message != "property value must be list[int] | int") {
			throw "got \'" + string(message) + "\'; expected 'property value must be list[int] | int'";
		}
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		if (message != "property value must be list[int] | int") {
			throw "got \'" + string(message) + "\'; expected 'property value must be list[int] | int'";
		}
	}
}

void Test::test_validate_rules()
{
	JsonParser parser = JsonParser();
	json value = json::object();
	try {
		parser.validate_rules(value);
		
	}
	catch (const char* message) {
		throw "got \'" + string(message) + "\'; expected void";
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		throw "got \'" + string(message) + "\'; expected void";
	}

	value = json::object();
	value["wrong_key"] = 123;
	try {
		parser.validate_rules(value);
	}
	catch (const char* message) {
		if (message != "can't parse rule wrong_key!") {
			throw "got \'" + string(message) + "\'; expected 'can't parse rule wrong_key!'";
		}
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		if (message != "can't parse rule wrong_key!") {
			throw "got \'" + string(message) + "\'; expected 'can't parse rule wrong_key!'";
		}
	}

	value = json::object();
	value["properties"] = 123;
	try {
		parser.validate_rules(value);
	}
	catch (const char* message) {
		if (message != "rule 'properties' must be list[str] or str") {
			throw "got \'" + string(message) + "\'; expected 'rule 'properties' must be list[str] or str'";
		}
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		if (message != "rule 'properties' must be list[str] or str") {
			throw "got \'" + string(message) + "\'; expected 'rule 'properties' must be list[str] or str'";
		}
	}

	value = json::object();
	value["properties"] = json::array();
	value["properties"].push_back(123);
	value["properties"].push_back(123);

	try {
		parser.validate_rules(value);
	}
	catch (const char* message) {
		if (message != "rule 'properties' must be list[str] or str") {
			throw "got \'" + string(message) + "\'; expected 'rule 'properties' must be list[str] or str'";
		}
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		if (message != "rule 'properties' must be list[str] or str") {
			throw "got \'" + string(message) + "\'; expected 'rule 'properties' must be list[str] or str'";
		}	
	}

	value = json::object();
	value["properties"] = json::array();

	try {
		parser.validate_rules(value);
	}
	catch (const char* message) {
		throw "got \'" + string(message) + "\'; expected void'";
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		throw "got \'" + string(message) + "\'; expected void";
	}








	value = json::object();
	value["count"] = json::array();
	value["count"].push_back(123);
	value["count"].push_back(123);

	try {
		parser.validate_rules(value);
	}
	catch (const char* message) {
		if (message != "cannot use rule 'count' without rule 'properties'") {
			throw "got \'" + string(message) + "\'; expected 'cannot use rule 'count' without rule 'properties''";
		}
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		if (message != "cannot use rule 'count' without rule 'properties'") {
			throw "got \'" + string(message) + "\'; expected 'cannot use rule 'count' without rule 'properties''";
		}
	}


	value = json::object();
	value["values"] = json::array();
	value["values"].push_back(123);
	value["values"].push_back(123);

	try {
		parser.validate_rules(value);
	}
	catch (const char* message) {
		if (message != "cannot use rule 'values' without rule 'properties'") {
			throw "got \'" + string(message) + "\'; expected 'cannot use rule 'values' without rule 'properties''";
		}
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		if (message != "cannot use rule 'values' without rule 'properties'") {
			throw "got \'" + string(message) + "\'; expected 'cannot use rule 'values' without rule 'properties''";
		}
	}








	value = json::object();
	value["properties"] = json::array();
	value["count"] = "not dictionary type";


	try {
		parser.validate_rules(value);
	}
	catch (const char* message) {
		if (message != "rule 'count' must be dict[str, int]") {
			throw "got \'" + string(message) + "\'; expected 'rule 'count' must be dict[str, int]'";
		}
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		if (message != "rule 'count' must be dict[str, int]") {
			throw "got \'" + string(message) + "\'; expected 'rule 'count' must be dict[str, int]'";
		}
	}

	value = json::object();
	value["properties"] = json::array();
	value["properties"].push_back("pr1");
	value["properties"].push_back("pr2");
	value["count"] = json::object();
	value["count"]["pr3"] = "some val";

	try {
		parser.validate_rules(value);
	}
	catch (const char* message) {
		if (message != "property pr3 declared in rule 'count' have not declared in rule 'properties'") {
			throw "got \'" + string(message) + "\'; expected 'property pr3 declared in rule 'count' have not declared in rule 'properties''";
		}
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		if (message != "property pr3 declared in rule 'count' have not declared in rule 'properties'") {
			throw "got \'" + string(message) + "\'; expected 'property pr3 declared in rule 'count' have not declared in rule 'properties''";
		}
	}

	value = json::object();
	value["properties"] = json::array();
	value["properties"].push_back("pr1");
	value["properties"].push_back("pr2");
	value["count"] = json::object();
	value["count"]["pr2"] = "not int type";

	try {
		parser.validate_rules(value);
	}
	catch (const char* message) {
		if (message != "rule 'count' must be dict[str, int]") {
			throw "got \'" + string(message) + "\'; expected 'rule 'count' must be dict[str, int]'";
		}
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		if (message != "rule 'count' must be dict[str, int]") {
			throw "got \'" + string(message) + "\'; expected 'rule 'count' must be dict[str, int]'";
		}
	}

	value = json::object();
	value["properties"] = json::array();
	value["properties"].push_back("pr1");
	value["properties"].push_back("pr2");
	value["count"] = json::object();
	value["count"]["pr2"] = 2;

	try {
		parser.validate_rules(value);
	}
	catch (const char* message) {
		throw "got \'" + string(message) + "\'; expected void";
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		throw "got \'" + string(message) + "\'; expected void";
	}

	value = json::object();
	value["properties"] = json::array();
	value["properties"].push_back("pr1");
	value["properties"].push_back("pr2");
	value["count"] = json::object();

	try {
		parser.validate_rules(value);
	}
	catch (const char* message) {
		throw "got \'" + string(message) + "\'; expected void";
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		throw "got \'" + string(message) + "\'; expected void";
	}









	value = json::object();
	value["properties"] = json::array();
	value["values"] = "not dictionary type";

	try {
		parser.validate_rules(value);
	}
	catch (const char* message) {
		if (message != "rule 'values' must be dict[str, int | list[int]]") {
			throw "got \'" + string(message) + "\'; expected 'rule 'values' must be dict[str, int | list[int]]'";
		}
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		if (message != "rule 'values' must be dict[str, int | list[int]]") {
			throw "got \'" + string(message) + "\'; expected 'rule 'values' must be dict[str, int | list[int]]'";
		}
	}

	value = json::object();
	value["properties"] = json::array();
	value["values"] = json::object();
	value["values"]["pr2"] = 2;

	try {
		parser.validate_rules(value);
	}
	catch (const char* message) {
		if (message != "property pr2 declared in rule 'values' have not declared in rule 'properties'") {
			throw "got \'" + string(message) + "\'; expected 'property pr2 declared in rule 'values' have not declared in rule 'properties''";
		}
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		if (message != "property pr2 declared in rule 'values' have not declared in rule 'properties'") {
			throw "got \'" + string(message) + "\'; expected 'property pr2 declared in rule 'values' have not declared in rule 'properties''";
		}
	}

	value = json::object();
	value["properties"] = json::array();
	value["properties"].push_back("pr1");
	value["values"] = json::object();
	value["values"]["pr2"] = 2;

	try {
		parser.validate_rules(value);
	}
	catch (const char* message) {
		if (message != "property pr2 declared in rule 'values' have not declared in rule 'properties'") {
			throw "got \'" + string(message) + "\'; expected 'property pr2 declared in rule 'values' have not declared in rule 'properties''";
		}
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		if (message != "property pr2 declared in rule 'values' have not declared in rule 'properties'") {
			throw "got \'" + string(message) + "\'; expected 'property pr2 declared in rule 'values' have not declared in rule 'properties''";
		}
	}

	value = json::object();
	value["properties"] = json::array();
	value["values"] = json::object();
	value["values"]["pr1"] = "not int type";

	try {
		parser.validate_rules(value);
	}
	catch (const char* message) {
		if (message != "property pr1 declared in rule 'values' have not declared in rule 'properties'") {
			throw "got \'" + string(message) + "\'; expected 'property pr1 declared in rule 'values' have not declared in rule 'properties''";
		}
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		if (message != "property pr1 declared in rule 'values' have not declared in rule 'properties'") {
			throw "got \'" + string(message) + "\'; expected 'property pr1 declared in rule 'values' have not declared in rule 'properties''";
		}
	}

	value = json::object();
	value["properties"] = json::array();
	value["properties"].push_back("pr1");
	value["values"] = json::object();
	value["values"]["pr1"] = json::array();
	value["values"]["pr1"].push_back("not list[int] type");

	try {
		parser.validate_rules(value);
	}
	catch (const char* message) {
		if (message != "rule 'values' must be dict[str, int | list[int]]") {
			throw "got \'" + string(message) + "\'; expected 'rule 'values' must be dict[str, int | list[int]]'";
		}
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		if (message != "rule 'values' must be dict[str, int | list[int]]") {
			throw "got \'" + string(message) + "\'; expected 'rule 'values' must be dict[str, int | list[int]]'";
		}
	}

	value = json::object();
	value["properties"] = json::array();
	value["properties"].push_back("pr1");
	value["values"] = json::object();
	value["values"]["pr1"] = json::array();

	try {
		parser.validate_rules(value);
	}
	catch (const char* message) {
		throw "got \'" + string(message) + "\'; expected void";
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		throw "got \'" + string(message) + "\'; expected void";
	}

	value = json::object();
	value["properties"] = json::array();
	value["properties"].push_back("pr1");
	value["values"] = json::object();


	try {
		parser.validate_rules(value);
	}
	catch (const char* message) {
		throw "got \'" + string(message) + "\'; expected void";
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		throw "got \'" + string(message) + "\'; expected void";
	}








	value = json::object();
	value["properties"] = json::array();
	value["properties"].push_back("pr1");
	value["values"] = json::object();
	value["values"]["pr1"] = 1;

	try {
		parser.validate_rules(value);
	}
	catch (const char* message) {
		throw "got \'" + string(message) + "\'; expected void";
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		throw "got \'" + string(message) + "\'; expected void";
	}

	value = json::object();
	value["properties"] = json::array();
	value["properties"].push_back("pr1");
	value["values"] = json::object();
	value["values"]["pr1"] = json::array();
	value["values"]["pr1"].push_back(1);
	value["values"]["pr1"].push_back(2);

	try {
		parser.validate_rules(value);
	}
	catch (const char* message) {
		throw "got \'" + string(message) + "\'; expected void";
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		throw "got \'" + string(message) + "\'; expected void";
	}
}

void Test::test_validate_count()
{
	json note = json::object();
	note["prop1"] = 1;
	note["prop2"] = json::array();
	note["prop3"] = json::array();
	note["prop3"].push_back(1);
	note["prop3"].push_back(2);
	note["prop4"] = json::array();
	note["prop4"].push_back(1);
	note["prop4"].push_back(2);
	note["prop4"].push_back(3);

	json rules = json::object();
	rules["count"] = json::object();

	NoteClass validator = NoteClass(string("someclass"), rules);
	bool result = validator.validate_count(note);
	if (result != true) {
		string got;
		string expected;
		if (result) {
			got = "true";
			expected = "false";
		}
		else {
			got = "false";
			expected = "true";
		}
		throw "got " + got + "; expected " + expected;
	}


	rules = json::object();
	rules["count"] = json::object();
	rules["count"]["prop1"] = 1;
	rules["count"]["prop2"] = 0;
	rules["count"]["prop3"] = 2;
	rules["count"]["prop4"] = 3;

	validator = NoteClass(string("someclass"), rules);
	result = validator.validate_count(note);
	if (result != true) {
		string got;
		string expected;
		if (result) {
			got = "true";
			expected = "false";
		}
		else {
			got = "false";
			expected = "true";
		}
		throw "got " + got + "; expected " + expected;
	}

	rules = json::object();
	rules["count"] = json::object();
	rules["count"]["prop1"] = 1;

	validator = NoteClass(string("someclass"), rules);
	result = validator.validate_count(note);
	if (result != true) {
		string got;
		string expected;
		if (result) {
			got = "true";
			expected = "false";
		}
		else {
			got = "false";
			expected = "true";
		}
		throw "got " + got + "; expected " + expected;
	}


	rules = json::object();
	rules["count"] = json::object();
	rules["count"]["prop2"] = 0;

	validator = NoteClass(string("someclass"), rules);
	result = validator.validate_count(note);
	if (result != true) {
		string got;
		string expected;
		if (result) {
			got = "true";
			expected = "false";
		}
		else {
			got = "false";
			expected = "true";
		}
		throw "got " + got + "; expected " + expected;
	}


	rules = json::object();
	rules["count"] = json::object();
	rules["count"]["prop3"] = 2;

	validator = NoteClass(string("someclass"), rules);
	result = validator.validate_count(note);
	if (result != true) {
		string got;
		string expected;
		if (result) {
			got = "true";
			expected = "false";
		}
		else {
			got = "false";
			expected = "true";
		}
		throw "got " + got + "; expected " + expected;
	}


	rules = json::object();
	rules["count"] = json::object();
	rules["count"]["prop4"] = 3;

	validator = NoteClass(string("someclass"), rules);
	result = validator.validate_count(note);
	if (result != true) {
		string got;
		string expected;
		if (result) {
			got = "true";
			expected = "false";
		}
		else {
			got = "false";
			expected = "true";
		}
		throw "got " + got + "; expected " + expected;
	}


	rules = json::object();
	rules["count"] = json::object();
	rules["count"]["prop3"] = 3;

	validator = NoteClass(string("someclass"), rules);
	result = validator.validate_count(note);
	if (result != false) {
		string got;
		string expected;
		if (result) {
			got = "true";
			expected = "false";
		}
		else {
			got = "false";
			expected = "true";
		}
		throw "got " + got + "; expected " + expected;
	}
}

void Test::test_validate_props()
{
	json note = json::object();

	json rules = json::object();
	rules["properties"] = json::array();

	NoteClass validator = NoteClass(string("someclass"), rules);
	bool result = validator.validate_has_prop(note);
	if (result != true) {
		string got;
		string expected;
		if (result) {
			got = "true";
			expected = "false";
		}
		else {
			got = "false";
			expected = "true";
		}
		throw "got " + got + "; expected " + expected;
	};


	rules = json::object();
	rules["properties"] = "prop1";

	validator = NoteClass(string("someclass"), rules);
	result = validator.validate_has_prop(note);
	if (result != false) {
		string got;
		string expected;
		if (result) {
			got = "true";
			expected = "false";
		}
		else {
			got = "false";
			expected = "true";
		}
		throw "got " + got + "; expected " + expected;
	}


	rules = json::object();
	rules["properties"] = json::array();
	rules["properties"].push_back("prop1");

	validator = NoteClass(string("someclass"), rules);
	result = validator.validate_has_prop(note);
	if (result != false) {
		string got;
		string expected;
		if (result) {
			got = "true";
			expected = "false";
		}
		else {
			got = "false";
			expected = "true";
		}
		throw "got " + got + "; expected " + expected;
	}


	note["prop1"] = 2;
	rules = json::object();
	rules["properties"] = "prop1";

	validator = NoteClass(string("someclass"), rules);
	result = validator.validate_has_prop(note);
	if (result != true) {
		string got;
		string expected;
		if (result) {
			got = "true";
			expected = "false";
		}
		else {
			got = "false";
			expected = "true";
		}
		throw "got " + got + "; expected " + expected;
	}


	rules = json::object();
	rules["properties"] = json::array();
	rules["properties"].push_back("prop1");

	validator = NoteClass(string("someclass"), rules);
	result = validator.validate_has_prop(note);
	if (result != true) {
		string got;
		string expected;
		if (result) {
			got = "true";
			expected = "false";
		}
		else {
			got = "false";
			expected = "true";
		}
		throw "got " + got + "; expected " + expected;
	}


	note["prop2"] = 2;
	rules = json::object();
	rules["properties"] = json::array();
	rules["properties"].push_back("prop1");
	rules["properties"].push_back("prop3");

	validator = NoteClass(string("someclass"), rules);
	result = validator.validate_has_prop(note);
	if (result != false) {
		string got;
		string expected;
		if (result) {
			got = "true";
			expected = "false";
		}
		else {
			got = "false";
			expected = "true";
		}
		throw "got " + got + "; expected " + expected;
	}


	rules = json::object();
	rules["properties"] = json::array();
	rules["properties"].push_back("prop1");
	rules["properties"].push_back("prop2");

	validator = NoteClass(string("someclass"), rules);
	result = validator.validate_has_prop(note);
	if (result != true) {
		string got;
		string expected;
		if (result) {
			got = "true";
			expected = "false";
		}
		else {
			got = "false";
			expected = "true";
		}
		throw "got " + got + "; expected " + expected;
	}

}

void Test::test_has_value()
{
	json note = json::object();
	json rules = json::object();
	rules["values"] = json::object();

	NoteClass validator = NoteClass(string("someclass"), rules);
	bool result = validator.validate_values(note);
	if (result != true) {
		string got;
		string expected;
		if (result) {
			got = "true";
			expected = "false";
		}
		else {
			got = "false";
			expected = "true";
		}
		throw "got " + got + "; expected " + expected;
	}


	rules = json::object();
	rules["values"] = json::object();
	rules["values"]["prop1"] = 2;

	validator = NoteClass(string("someclass"), rules);
	result = validator.validate_values(note);
	if (result != false) {
		string got;
		string expected;
		if (result) {
			got = "true";
			expected = "false";
		}
		else {
			got = "false";
			expected = "true";
		}
		throw "got " + got + "; expected " + expected;
	}


	rules = json::object();
	rules["values"] = json::object();
	rules["values"]["prop1"] = json::array();
	rules["values"]["prop1"].push_back(1);
	rules["values"]["prop1"].push_back(2);

	validator = NoteClass(string("someclass"), rules);
	result = validator.validate_values(note);
	if (result != false) {
		string got;
		string expected;
		if (result) {
			got = "true";
			expected = "false";
		}
		else {
			got = "false";
			expected = "true";
		}
		throw "got " + got + "; expected " + expected;
	}

	note["prop1"] = 2;
	rules = json::object();
	rules["values"] = json::object();
	rules["values"]["prop1"] = 2;

	validator = NoteClass(string("someclass"), rules);
	result = validator.validate_values(note);
	if (result != true) {
		string got;
		string expected;
		if (result) {
			got = "true";
			expected = "false";
		}
		else {
			got = "false";
			expected = "true";
		}
		throw "got " + got + "; expected " + expected;
	}


	note["prop1"] = 1;
	rules = json::object();
	rules["values"] = json::object();
	rules["values"]["prop1"] = 2;

	validator = NoteClass(string("someclass"), rules);
	result = validator.validate_values(note);
	if (result != false) {
		string got;
		string expected;
		if (result) {
			got = "true";
			expected = "false";
		}
		else {
			got = "false";
			expected = "true";
		}
		throw "got " + got + "; expected " + expected;
	}


	note["prop1"] = json::array();
	note["prop1"].push_back(1);
	note["prop1"].push_back(2);
	rules = json::object();
	rules["values"] = json::object();
	rules["values"]["prop1"] = 2;

	validator = NoteClass(string("someclass"), rules);
	result = validator.validate_values(note);
	if (result != true) {
		string got;
		string expected;
		if (result) {
			got = "true";
			expected = "false";
		}
		else {
			got = "false";
			expected = "true";
		}
		throw "got " + got + "; expected " + expected;
	}


	note["prop1"] = json::array();
	note["prop1"].push_back(1);
	note["prop1"].push_back(3);
	rules = json::object();
	rules["values"] = json::object();
	rules["values"]["prop1"] = 2;

	validator = NoteClass(string("someclass"), rules);
	result = validator.validate_values(note);
	if (result != false) {
		string got;
		string expected;
		if (result) {
			got = "true";
			expected = "false";
		}
		else {
			got = "false";
			expected = "true";
		}
		throw "got " + got + "; expected " + expected;
	}


	note["prop1"] = 3;
	rules = json::object();
	rules["values"] = json::object();
	rules["values"]["prop1"] = json::array();
	rules["values"]["prop1"].push_back(1);
	rules["values"]["prop1"].push_back(2);

	validator = NoteClass(string("someclass"), rules);
	result = validator.validate_values(note);
	if (result != false) {
		string got;
		string expected;
		if (result) {
			got = "true";
			expected = "false";
		}
		else {
			got = "false";
			expected = "true";
		}
		throw "got " + got + "; expected " + expected;
	}


	note["prop1"] = json::array();
	note["prop1"].push_back(1);
	note["prop1"].push_back(3);
	rules = json::object();
	rules["values"] = json::object();
	rules["values"]["prop1"] = json::array();
	rules["values"]["prop1"].push_back(1);
	rules["values"]["prop1"].push_back(2);

	validator = NoteClass(string("someclass"), rules);
	result = validator.validate_values(note);
	if (result != false) {
		string got;
		string expected;
		if (result) {
			got = "true";
			expected = "false";
		}
		else {
			got = "false";
			expected = "true";
		}
		throw "got " + got + "; expected " + expected;
	}


	note["prop1"] = json::array();
	note["prop1"].push_back(1);
	note["prop1"].push_back(2);
	note["prop1"].push_back(3);
	note["prop1"].push_back(4);
	rules = json::object();
	rules["values"] = json::object();
	rules["values"]["prop1"] = json::array();
	rules["values"]["prop1"].push_back(1);
	rules["values"]["prop1"].push_back(2);

	validator = NoteClass(string("someclass"), rules);
	result = validator.validate_values(note);
	if (result != true) {
		string got;
		string expected;
		if (result) {
			got = "true";
			expected = "false";
		}
		else {
			got = "false";
			expected = "true";
		}
		throw "got " + got + "; expected " + expected;
	}


	note["prop1"] = json::array();
	note["prop1"].push_back(1);
	note["prop1"].push_back(2);
	note["prop1"].push_back(3);
	note["prop1"].push_back(4);
	note["prop2"] = 2;
	rules = json::object();
	rules["values"] = json::object();
	rules["values"]["prop1"] = json::array();
	rules["values"]["prop1"].push_back(1);
	rules["values"]["prop1"].push_back(2);
	rules["values"]["prop2"] = json::array();

	validator = NoteClass(string("someclass"), rules);
	result = validator.validate_values(note);
	if (result != false) {
		string got;
		string expected;
		if (result) {
			got = "true";
			expected = "false";
		}
		else {
			got = "false";
			expected = "true";
		}
		throw "got " + got + "; expected " + expected;
	}

}

