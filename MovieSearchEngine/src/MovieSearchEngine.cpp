// MovieSearchEngine.cpp: определяет точку входа для приложения.
//
#include "MovieSearchEngine.h"

int main()
{
	ConverterJSON converterJSON;
	try
	{
		converterJSON.start();
	}
	catch (const exception& x)
	{
		cerr << "The file is not found.";
		return 1;
	}
	converterJSON.openFile("requests.json");
	converterJSON.openFile("answers.json");
	converterJSON.requerysInputFunction(converterJSON.getRequests);
	converterJSON.wordCountFunction(converterJSON.countWordsMap);
	converterJSON.searchAnswerFunction(converterJSON.countWordsMap);
	return 0;
}
