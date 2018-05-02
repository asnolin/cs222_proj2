
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdint>

using namespace std;

struct cache_params
{
	bool alloc = true;
	int block = 1;
	int level = 1;
	int size = 1;
	int ways = 1;
	string replace = "a";
	string type = "a";
	string write = "a";
};

vector<cache_params> get_params(string path)
{
	
	vector<cache_params> params_vect;
	cache_params params;

	ifstream f_in;
	f_in.open(path);

	string line;
	vector<string> parse_result;

	while (f_in)
	{
		getline(f_in, line);
		if (line[0] != '#')
		{
			parse_result.push_back(line);
		}
	}

	f_in.close();

	for (string segment : parse_result)
	{
		cout << segment << "\n";

		istringstream ss(segment);
		string token;

		while (getline(ss, token, ','))
		{
			//cout << token << '\n';
			string param_name = "";
			string param_value = "";
			bool on_name = true;
			for (int i = 0; i < token.length(); ++i)
			{
				if (token[i] == ':')
				{
					on_name = false;
				}

				if (on_name)
				{
					param_name += token[i];
				}

				else
				{
					if (token[i] != ':')
					{
						param_value += token[i];
					}
				}
			}

			//cout << param_name << '\n';
			//cout << param_value << '\n';

			if (param_name == "alloc")
			{
				if (param_value == "true")
				{
					params.alloc = true;
				}
			}

			if (param_name == "block")
			{
				params.block = stoi(param_value);
			}

			if (param_name == "level")
			{
				params.level = stoi(param_value);
			}

			if (param_name == "replace")
			{
				params.replace = param_value;
			}

			if (param_name == "size")
			{
				params.size = stoi(param_value);
			}

			if (param_name == "type")
			{
				params.type = param_value;
			}

			if (param_name == "ways")
			{
				params.ways = stoi(param_value);
			}

			if (param_name == "write")
			{
				params.write = param_value;
			}
		}

		params_vect.push_back(params);
	}

	return params_vect;
}

void print_contents(string path)
{
	ifstream f_in;
	f_in.open(path);

	string line;

	while (f_in)
	{
		getline(f_in, line);

		if (line[0] != '#')
		{
			cout << line << "\n";
		}

		//cout << line << "\n";
	}

	f_in.close();
}

void print_params(cache_params params)
{
	cout << "alloc: " << params.alloc << "\n";
	cout << "block: " << params.block << "\n";
	cout << "level: " << params.level << "\n";
	cout << "replace: " << params.replace << "\n";
	cout << "size: " << params.size << "\n";
	cout << "type: " << params.type << "\n";
	cout << "ways: " << params.ways << "\n";
	cout << "write: " << params.write << "\n";
}

int64_t hexstrToInt64(std::string hexstr) {
	return std::stol(hexstr, nullptr, 16);
}

vector<string> parse_trace(string path)
{
	vector<string> accesses;
	
	ifstream f_in;
	f_in.open(path);

	string line;

	while (f_in)
	{
		getline(f_in, line);
		accesses.push_back(line);
	}

	f_in.close();

	return accesses;
}

int main() {

	string config_path = "stuff/config/";
	string trace_path = "stuff/trace/";
	string filename;
	cout << "Enter filename: ";
	cin >> filename;
	trace_path += filename;

	//print_contents(path);
	//vector<cache_params> params = get_params(path);
	//print_params(params);

	/*
	for (int i = 0; i < 3; ++i)
	{
		print_params(params[i]);
	}
	*/

	vector<string> accesses = parse_trace(trace_path);

	return 0;
}