#include <iostream>
#include <future>
#include <string>

using namespace ::std;

std::string read_console()
{
	string result;
	cin >> result;
	return result;
}

int main(int argc, char **argv)
{
	auto result = async(launch::async, read_console);
	chrono::milliseconds zero_ms(0);

	while(result.wait_for(zero_ms) == future_status::timeout)
		cout << "." << flush;

	cout << result.get() << endl;

	return 0;
}
