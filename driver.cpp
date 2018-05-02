
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdint>

using namespace std;



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
