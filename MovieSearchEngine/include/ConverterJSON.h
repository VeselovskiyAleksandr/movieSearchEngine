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

	  //������� ������ ������ ������
	  inline  void start();

	  //������� �������� ������� �����
	  inline  bool FileIsExist(string filePath);

	  //������� �������� �������� �����
	  inline  void openFile(string path);

	  //������� ����� �������
	  inline  void requerysInputFunction(vector<string>& getRequests);

	  //������� ��������� ����
	  inline  void wordSplitFunction(string sentence, vector<string>& setWords);

	  //������� ������ ������ � �����
	  inline  void multiMapFillFunction(vector<Entry>& vectEntr, vector<Entry>& getWC, multimap<string, vector< Entry>>& countWM);

	  //������� ���������� ������� Entry
	  inline  void vectorEntryFillFunction(vector<string>& vectWord, vector<Entry>& getWC, int fileCount);

	  //������� �������� ���� � ���������
	  multimap<string, vector< Entry>> countWordsMap;
	  inline  void wordCountFunction(multimap<string, vector< Entry>>& countWMap);

	  //������� ������ �������. ����� ������ ����� � ����������.
	  inline  void searchAnswerFunction(multimap<string, vector< Entry>>& countWMap);
};