// MovieSearchEngine.cpp: определяет точку входа для приложения.

#include "ConverterJSON.h"
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
	converterJSON.getRequestsFunction(converterJSON.getRequests);
//	converterJSON.requerInputFunction(converterJSON.getRequests);
	converterJSON.wordCountFunction(converterJSON.countWordsMap);
	converterJSON.searchAnswerFunction(converterJSON.countWordsMap, converterJSON.getRequests);
	converterJSON.getAnswerFunction();
	return 0;
}
