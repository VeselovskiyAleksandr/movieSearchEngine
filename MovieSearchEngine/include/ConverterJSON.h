#pragma once

#include <fstream>
#include <vector>
#include <exception>
#include "Configuration.h"
#include "Entry.h"
#include <thread>
#include <mutex>
//#include "ThreadPool.h"

using namespace std;

 class ConverterJSON
{
public: ConverterJSON() = default;
	  Configuration configuration;
	  vector<string> getRequests;

	  //функция начала работы движка
	   void start();

	  //функция проверки наличия файла
	   bool FileIsExist(string filePath);

	  //функция проверки открытия файла
	  void openFile(string path);

	  //функция ввода запроса
	   void requerysInputFunction(vector<string>& getRequests);

	  //функция выделения слов
	   void wordSplitFunction(string &sentence, vector<string>& setWords);
	//   void wordSplitFunction(int n, int k, string sentence, vector<string> setWords[DOCUMENT_NUMBER]);/////////////////

	  //функция записи данных в карту
	//    void multiMapFillFunction(vector<Entry> &vectEntr, vector<Entry>& getWC, multimap<string, vector< Entry>>& countWM);
	   void multiMapFillFunction(int n, vector<Entry> vectEntr[DOCUMENT_NUMBER], vector<Entry> getWC[DOCUMENT_NUMBER], multimap<string, vector< Entry>>& countWM);

	  //функция заполнения вектора Entry
	//  void vectorEntryFillFunction(vector<string>& vectWord, vector<Entry>& getWC, int fileCount);
		void vectorEntryFillFunction(vector<string> vectWord, vector<Entry> getWC[DOCUMENT_NUMBER], int fileCount);///////////////////

	  /// /////////////////////////////
	//  void readingFromDatabase( int n, mutex film_mutex[DOCUMENT_NUMBER], string movPath[DOCUMENT_NUMBER], vector<string> vWord[DOCUMENT_NUMBER], vector<Entry> getWC[DOCUMENT_NUMBER], string strWrd[DOCUMENT_NUMBER], int filesC[DOCUMENT_NUMBER], vector<Entry> vEntry[DOCUMENT_NUMBER], multimap<string, vector< Entry>> &countWMap);
	//  void readingFromDatabase(promise<string>& promise);
	//  void readingFromDatabase(int n, mutex film_mutex[DOCUMENT_NUMBER], string movPath[DOCUMENT_NUMBER], vector<string> vWord[DOCUMENT_NUMBER], string  strWrd[DOCUMENT_NUMBER]);
	  ///////////////////////////////////////////

	  //функция подсчёта слов в документе
	   multimap<string, vector< Entry>> countWordsMap;
	    void wordCountFunction(multimap<string, vector< Entry>> &countWordMap);//////
	  //функция поиска ответов. Здесь ведётся поиск в контейнере.
	   void searchAnswerFunction(multimap<string, vector< Entry>> &countWMap);///////////
};