#include <curl/curl.h>
#include <string>
#include <iostream>

using namespace ::std;

int writer(char *data, size_t size, size_t nmemb, std::string *writerData)
{
	writerData->append(data, size * nmemb);
	return size * nmemb;
}

int main(int argc, char **argv)
{
	char errorBuffer[CURL_ERROR_SIZE];
	string buffer;

	CURL *conn = nullptr;
	CURLcode code;

	curl_global_init(CURL_GLOBAL_DEFAULT);

	conn = curl_easy_init();
	code = curl_easy_setopt(conn, CURLOPT_ERRORBUFFER, errorBuffer);
	code = curl_easy_setopt(conn, CURLOPT_URL, "http://www.bluefruit.co.uk/");
	code = curl_easy_setopt(conn, CURLOPT_FOLLOWLOCATION, 1L);
	code = curl_easy_setopt(conn, CURLOPT_WRITEFUNCTION, writer);
	code = curl_easy_setopt(conn, CURLOPT_WRITEDATA, &buffer);
	// if(code != CURLE_OK) ...

	code = curl_easy_perform(conn);
	curl_easy_cleanup(conn);

	if(code == CURLE_OK)
	{
		cout << buffer << endl;
	}
	else
	{
		cout << "Error: (" << code << ") " << errorBuffer << endl;
	}

	return 0;
}
