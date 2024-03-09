#pragma once
#include <nlohmann/json.hpp>

using namespace nlohmann;
using namespace std;


/************************************************
 *  NoteClass - set and use rules for validating notes.
 ***********************************************/
 //class NoteClass {
class NoteClass
{
	json rules;
public:
	//! Name of current class.
	string classname;

	//! A constructor that sets classname and rules for created instance.
	/*!
	\param classname a string argument.
	\param rules a json argument.
	*/
	NoteClass(string classname, json rules);

	//! Validate properties of current note by calling existing in this->rules validators.
	/*!
	\param properties a json argument.
	\return bool, means note with this properties can be/can't be an instance of class.
	*/
	bool validate(json properties);

	//! Validate properties of current note by this->rules["properties"] if it exists else return true.
	/*!
	\param properties a json argument.
	\return bool, means note with this properties can be/can't be valid for this->rules["properties"].
	*/
	bool validate_has_prop(json properties);

	//! Validate properties of current note by this->rules["count"] if it exists else return true.
	/*!
	\param properties a json argument.
	\return bool, means note with this properties can be/can't be valid for this->rules["count"].
	*/
	bool validate_count(json properties);

	//! Validate properties of current note by this->rules["values"] if it exists else return true.
	/*!
	\param properties a json argument.
	\return bool, means note with this properties can be/can't be valid for this->rules["values"].
	*/
	bool validate_values(json properties);


};

