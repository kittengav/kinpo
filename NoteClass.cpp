#include "NoteClass.h"

NoteClass::NoteClass(string classname, json rules)
{
	this->rules = rules;
	this->classname = classname;
}

bool NoteClass::validate(json properties)
{
	if (this->validate_has_prop(properties) && this->validate_count(properties) && this->validate_values(properties)) {
		return true;
	}
	return false;
}

bool NoteClass::validate_has_prop(json properties)
{
	if (!this->rules.contains("properties")) {
		return true;
	}

	if (this->rules["properties"].is_array()) {
		for (auto it = this->rules["properties"].begin(); it != this->rules["properties"].end(); ++it) {
			if (!properties.contains(it.value())) {
				return false;
			}
		}
	}
	if (this->rules["properties"].is_string()) {
		return properties.contains(this->rules["properties"]);
	}

	return true;
}

bool NoteClass::validate_count(json properties)
{
	if (!this->rules.contains("count")) {
		return true;
	}

	for (auto it = this->rules["count"].begin(); it != this->rules["count"].end(); ++it) {
		if (!properties.contains(it.key())) {
			return false;
		}
		if (properties[it.key()].is_number_integer() && it.value() != 1) {
			return false;
		}
		if (properties[it.key()].is_array() && properties[it.key()].size() != it.value()) {
			return false;
		}
	}
	return true;
}

bool NoteClass::validate_values(json properties)
{
	if (!this->rules.contains("values")) {
		return true;
	}
	for (auto it = this->rules["values"].begin(); it != this->rules["values"].end(); ++it) {
		if (!properties.contains(it.key())) {
			return false;
		}
		if (it.value().is_array()) {
			if (properties[it.key()].is_array()) {
				for (auto iv = it.value().begin(); iv != it.value().end(); ++iv) {
					json::iterator index = find(properties[it.key()].begin(), properties[it.key()].end(), iv.value());
					if (index == properties[it.key()].end()) {
						return false;
					}
				}
			}

			if (properties[it.key()].is_number_integer()) {
				if (it.value().size() != 1) {
					return false;
				}
				else {
					if (it.value()[0] != properties[it.key()]) {
						return false;
					}
				}
			}
		}
		if (it.value().is_number_integer()) {
			if (properties[it.key()].is_array()) {
				json::iterator index = find(properties[it.key()].begin(), properties[it.key()].end(), it.value());
				if (index == properties[it.key()].end()) {
					return false;
				}
			}

			if (properties[it.key()].is_number_integer()) {
				if (it.value() != properties[it.key()]) {
					return false;
				}
			}
		}
	}
	return true;
}
