// MovieSearchEngine.cpp: определяет точку входа для приложения.
//
#include "ConverterJSON.h"
#include <thread>

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
//	cout << "\n000000000000 " << " " << converterJSON.countWordsMap.size();// 
	converterJSON.searchAnswerFunction(converterJSON.countWordsMap);
//	for (auto it = converterJSON.countWordsMap.begin(); it != converterJSON.countWordsMap.end(); it++)
//	{
//		cout << "\n000000000000 " <<" "<< converterJSON.countWordsMap.size();// << " " << it->second;
//	}
	return 0;
}
