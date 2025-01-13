#pragma once

#include <fstream>
#include <vector>
#include <exception>
#include "nlohmann/json.hpp"
#include "Configuration.cpp"
#include "Entry.cpp"

using namespace std;

class ConverterJSON
{
public: ConverterJSON() = default;
	  Configuration configuration;
	  vector<string> getRequests;

	  //функция начала работы движка
	  inline  void start();

	  //функция проверки наличия файла
	  inline  bool FileIsExist(string filePath);

	  //функция проверки открытия файла
	  inline  void openFile(string path);

	  //функция ввода запроса
	  inline  void requerysInputFunction(vector<string>& getRequests);

	  //функция выделения слов
	  inline  void wordSplitFunction(string sentence, vector<string>& setWords);

	  //функция записи данных в карту
	  inline  void multiMapFillFunction(vector<Entry>& vectEntr, vector<Entry>& getWC, multimap<string, vector< Entry>>& countWM);

	  //функция заполнения вектора Entry
	  inline  void vectorEntryFillFunction(vector<string>& vectWord, vector<Entry>& getWC, int fileCount);

	  //функция подсчёта слов в документе
	  multimap<string, vector< Entry>> countWordsMap;
	  inline  void wordCountFunction(multimap<string, vector< Entry>>& countWMap);

	  //функция поиска ответов. Здесь ведётся поиск в контейнере.
	  inline  void searchAnswerFunction(multimap<string, vector< Entry>>& countWMap);
};