//
// The equivalence in C/C++
// between C's main()'s signature
// and
// C++ vector<string> arg;
// signature.
//
// Alexandru Goia, 2026
// Unix Temple,
// Bucharest,
// Europe
//

#include <cstdio>
#include <vector>
#include <string>
#include <ostream>
#include <iostream>

using namespace std;

void maincpp(vector<string> arg);

int main(int argc, char *argv[])
{
	vector<string> arg;

	int i;
	for(i = 0; i < argc; i++)
		arg.push_back(argv[i]);

	maincpp(arg);
	return 0;
}

void maincpp(vector<string> arg)
{
	for (const auto& s : arg) {
		std::cout << s << ' ';
	}
	std::cout << std::endl;
}
