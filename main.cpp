#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>
#include <map>
#include <vector>
#include "NoteClass.h"
#include "JsonParser.h"

using namespace std;
using namespace nlohmann;


//! Parses arguments, validating them. After that parses json file and calling validators for it. If valid - validating all notes of json file and printing result in stdout or in file (if --outfile filename had given).
/*!
\param argc an integer argument.
\param argv an char[] pointer argument.
\return int, 0 if not exceptions, 1 if some exceptions had intercept.
*/
int main(int argc, char* argv[]) {
	string infile;
	string outfile = string("");
	json document;
	json result;

	if (argc < 2) {
		cout << "expected filepath" << endl;
		return 1;
	}

	if (argc == 2) {
		infile = argv[1];
	}

	if (argc == 3) {
		if (argv[2] == string("--outfile")) {
			cout << "expected filepath after --outfile flag";
			return 1;
		}
		cout << "unexpected argumets: " << argv[2] << endl;
		return 1;
	}

	if (argc == 4) {
		if (string("--outfile") != argv[2]) {
			cout << "unexpected arguments: " << argv[2] << ", " << argv[3] << endl;
			return 1;
		}
		outfile = argv[3];
		infile = argv[1];
	}
	if (argc >= 5) {
		cout << "unexpected arguments" << endl;
		return 1;
	}

	JsonParser parser = JsonParser();
	try {
		document = parser.loads_from_file(infile);
		parser.validate_document(document);
		for (auto it = document["notes"].begin(); it != document["notes"].end(); ++it) {
			parser.validate_note(it.value());
		}
		if (document.contains("classes")) {
			for (auto it = document["classes"].begin(); it != document["classes"].end(); ++it) {
				parser.validate_rules(it.value());
			}

		};
		vector<NoteClass> classes;
		if (document.contains("classes")) {
			for (auto it = document["classes"].begin(); it != document["classes"].end(); ++it) {
				NoteClass new_class = NoteClass(it.key(), it.value());
				classes.push_back(new_class);
			}
		}
		for (auto it = document["notes"].begin(); it != document["notes"].end(); ++it) {
			result[it.key()] = json::array();
			for (auto cl : classes) {
				if (cl.validate(it.value())) {
					result[it.key()].push_back(cl.classname);
				}
			}
		}

		if (outfile != string("")) {
			parser.dumps_to_file(outfile, result);
			cout << "result saved at " << outfile << endl;
			return 0;
		}
		else {
			cout << result << endl;
			return 0;
		}
	}
	catch (const char* message) {
		cout << message << endl;
		return 1;
	}
	catch (basic_string<char, char_traits<char>, allocator<char>> message) {
		cout << message << endl;
		return 1;
	}
}