#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include "Configuration.h"
#include "Entry.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

 class ConverterJSON
{
public: ConverterJSON() = default;
	  Configuration configuration;
	  map <int, vector< string>> getRequests;
	  multimap<string, vector< Entry>> countWordsMap;
	  mutex film_mutex;
	  condition_variable cond;
//	  ifstream file[DOCUMENT_NUMBER];

	  //������� ������ ������ ������
	   void start();

	  //������� �������� ������� �����
	   bool FileIsExist(string filePath);

	  //������� �������� �������� �����
	  void openFile(string path);

	  //������� ��������� ��������
	  void getRequestsFunction(map<int, vector<string>>& getRequests);

	  //������� ����� �������
	//   void requerysInputFunction(vector<string>& getRequests);
	  void requerInputFunction(map<int, vector<string>>& getRequests);

	  //������� ��������� ����
	   void wordSplitFunction(vector<string>& sentence, vector<string>& setWords);
	//   void  wordSplitFunction(map<int, vector<string>>& sentence);/////////////////

	  //������� ������ ������ � �����
	    void multiMapFillFunction(vector<Entry> &vectEntr, vector<Entry>& getWC, multimap<string, vector< Entry>>& countWM);

	  //������� ���������� ������� Entry
	  void vectorEntryFillFunction(vector<string>& vectWord, vector<Entry>& getWC, int fileCount); 
	//	void vectorEntryFillFunction(map<int,vector<string>>& vectWord, vector<Entry>& getWC);/////////////////////

	  //������� �������
	  void readingFromDatabase(queue<string>& q, mutex& mtx, condition_variable &cond, atomic<bool>& fileComplete);
	  void ProcessData(const string& line);

	  //������� �������� ���� � ���������
      void wordCountFunction(multimap<string, vector< Entry>> &countWordsMap);

	  //������� ������ �������. ����� ������ ����� � ����������.
	//   void searchAnswerFunction(multimap<string, vector< Entry>> &countWordsMap);
	  void searchAnswerFunction(multimap<string, vector< Entry>>& countWordsMap, map <int, vector< string>> getRequest); 

	  //������� ������ ����������� ������
	  void getAnswerFunction();
};