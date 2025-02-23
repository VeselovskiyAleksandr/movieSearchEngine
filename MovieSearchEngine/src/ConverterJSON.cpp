
#include "ConverterJSON.h"
#include "nlohmann/json.hpp"
#include <future>
//#pragma omp parallel 

	  void ConverterJSON :: start()
	  {
		  cout << "                              Launching a search engine... " << "\n";
		  nlohmann::json config;
		  ifstream cnfile("config.json");
		  if (!cnfile)
		  {
			  throw exception();
		  }
			  cnfile >> config;
		  config["config"]["maxResponses"] = { MAX_RESPONS };
		  cout << config["config"] << "\n";
		  for (const auto& item : config["config"].items())
		  {
			  if (item.key() == "name")
			  {
				  configuration.name = item.value();
			  }
			  else if (item.key() == "version")
			  {
				  configuration.version = item.value();
			  }		  
		  }
		  int count = 0;
		  for (const auto& item : config["files"].items())
		  {
			  int id = stoi(item.key());
			  pair<int, string> oPair(id, item.value());
			  configuration.movieTitles.insert(oPair);
			  count++;
		  }
		  cnfile.close();
	  };

	  bool ConverterJSON :: FileIsExist(string filePath)
	  {
		  bool isExist = false;
		  std::ifstream fin(filePath.c_str());

		  if (fin.is_open())
			  isExist = true;

		  fin.close();
		  return isExist;
	  }

	  void ConverterJSON :: openFile(string path)
	  {
		  if (FileIsExist(path))
		  {
			  ofstream file;
			  file.open(path, std::ofstream::out | std::ofstream::trunc);
			  file.close();
		  }
		  else
		  {
			  ofstream reqFile(path);
			  reqFile.close();
		  }
	  };

	  void ConverterJSON :: requerysInputFunction(vector<string>& getRequests)
	  {
		  if (getRequests.size() < configuration.maxRequest)
		  {
			  cout << "\n" << "                                      Information about domestic and foreign films" << "\n" << "\n";
			  cout << "               Search query field" << "\n" << "\n";
			  string requerie = "";
			  getline(cin, requerie);
			  if (requerie.length() > configuration.maxStrRequestLength)
				  requerie.erase(requerie.length() - configuration.maxStrRequestLength);
			  getRequests.push_back(requerie);
			  requerie = "";
			  ofstream reqfile("requests.json");
			  nlohmann::json reqconfig;
			  reqconfig["number"] = getRequests.size();
			  reqconfig["request"] = getRequests[getRequests.size() - 1];
			  reqfile << reqconfig;
			  reqfile.close();
		  }
	  }

	  void ConverterJSON :: wordSplitFunction(string &sentence, vector<string>& setWords)
//	  void ConverterJSON::wordSplitFunction(int n, int t, string sentence, vector<string> setWords[DOCUMENT_NUMBER])////////////////////////
	  {
	//	  cout << "\n00000 "<<" " << sentence.length() << " " << " " << sentence;///////////////////////
		  string highlightedWord = "";
	//	  string highlightedWord[DOCUMENT_NUMBER];//////////////////
	//	  highlightedWord[n] = {0};///////////////////////
		  int j = 0, k = 0;
		  for (int ir = 0; ir < sentence.length(); ++ir)
	//	  for (int ir = 0; ir < t; ++ir)////////////////////////////////////
		  {

			  if (sentence[ir] != '-' && sentence[ir] != '\'' && sentence[ir] != '/'  && sentence[ir] != ')' && sentence[ir] != '(' && sentence[ir] != ' ' && sentence[ir] != ';' && sentence[ir] != ':' && sentence[ir] != ',' && sentence[ir] != '.')
	//		  if (sentence[ir] != '-' && sentence[ir] != '\'' && sentence[n][ir] != '/' && sentence[n][ir] != ')' && sentence[n][ir] != '(' && sentence[n][ir] != ' ' && sentence[n][ir] != ';' && sentence[n][ir] != ':' && sentence[n][ir] != ',' && sentence[n][ir] != '.')////////////////////////
			  {
				  if (sentence[ir] >= 65 && sentence[ir] <= 90)
		//		  if (sentence[n][ir] >= 65 && sentence[n][ir] <= 90)///////////////////
				  {
					  sentence[ir] += 32;
				  }
		//		  highlightedWord += sentence[ir];
	
				  highlightedWord += sentence[ir];//////////////////

				  j++;
		   }
			  else
			  {
				  setWords.push_back(highlightedWord);
		//		  cout << "\n0000011111112277777777777777 " << sizeof(setWords)<<" "<< sentence << " " << highlightedWord << "\n";////////////////////
		//		  setWords[n].push_back(highlightedWord);//////////////////
				  highlightedWord = "";
				  j = 0;
			  }

			  if(ir==sentence.length()-1)
		//	  if (ir == sizeof(sentence[n]))////////////////////////
				  setWords.push_back(highlightedWord);
		//		  setWords[n].push_back(highlightedWord);/////////////
		  }
	  }

	  //void ConverterJSON :: multiMapFillFunction(vector<Entry> &vectEntr, vector<Entry>& getWC, multimap<string, vector< Entry>>& countWordM)
	  void ConverterJSON :: multiMapFillFunction(int n, vector<Entry> vectEntr[DOCUMENT_NUMBER], vector<Entry> getWC[DOCUMENT_NUMBER], multimap<string, vector< Entry>>& countWordM)//////////////////////////
	  {
	//	  for (int ip = 0; ip < getWC.size(); ++ip)
		  for (int ip = 0; ip < getWC[n].size(); ++ip)/////////////////////
		  {
			  int match—ount = 0;
	//		  for (int iq = 0; iq < getWC.size(); ++iq)
			  for (int iq = 0; iq < getWC[n].size(); ++iq)//////////////////
			  {
		//		  if ((getWC[ip].word == getWC[iq].word) && (match—ount == 0))
				  if ((getWC[n][ip].word == getWC[n][iq].word) && (match—ount == 0))///////////////////
				  {
		//			  vectEntr.push_back(getWC[iq]);
					  vectEntr[n].push_back(getWC[n][iq]);///////////////////
					  match—ount++;
				  }
			  }
		//	  countWordM.insert({ getWC[ip].word, vectEntr });
			  countWordM.insert({ getWC[n][ip].word, vectEntr[n] });////////////////
		//	  vectEntr.clear();
			  vectEntr[n].clear();///////////////////
		  }
	//	  getWC.clear();
		  getWC[n].clear();////////////
	  }

//	  void ConverterJSON :: vectorEntryFillFunction(vector<string>& vectWord, vector<Entry>& getWC, int fileCount)
	  void ConverterJSON::vectorEntryFillFunction(vector<string> vectWord, vector<Entry> getWC[DOCUMENT_NUMBER], int fileCount)///////////////////////
	  {
		  size_t wordRepetitionCount = 0;
	//	  int wordRepetitionCount = 0;///
	//	  size_t wordRepetitionCount[DOCUMENT_NUMBER];////////////////////////////
	//	  wordRepetitionCount[f] = 0;//////////////////////////
		  int entryCount = 0;
		  vector<string> checkRepetition;
#pragma omp parallel for
		  for (int itr = 0; itr < vectWord.size(); ++itr)
	//	  for (size_t itr = 0; itr < vectWord[f].size(); ++itr)//////////////////////
		  {

			  Entry* entry = new Entry[MAX_SIZE];
			  entry[entryCount].docId = fileCount;
			  for (int iter = itr + 1; iter < vectWord.size(); ++iter)
		//	  for (size_t iter = itr + 1; iter < vectWord[f].size(); ++iter)///////////////////////////
			  {
				  if (vectWord[itr] == vectWord[iter])
				  {
					  wordRepetitionCount++;
	//				  wordRepetitionCount[f]++;////////////////////////////////////
				  }
			  }
			  wordRepetitionCount++;
	//		  wordRepetitionCount[f]++;///////////////////////////////////////////
    			  auto pointer = find(checkRepetition.begin(), checkRepetition.end(), vectWord[itr]);
	//		  auto pointer = find(checkRepetition.begin(), checkRepetition.end(), vectWord[f][itr]);///////////////////////
			  if ((pointer == end(checkRepetition)) && (vectWord[itr].size() > 3))
	//		  if ((pointer == end(checkRepetition)) && (vectWord[f][itr].size() > 3))
			  {
				  entry[entryCount].freqWordsCount = wordRepetitionCount;
		//		  entry[entryCount].freqWordsCount = wordRepetitionCount[f];////////////////////////////
				  entry[entryCount].word = vectWord[itr];
		//		  entry[entryCount].word = vectWord[f][itr]; ////////////////////////////
		//		  getWC.push_back(entry[entryCount]);
				  getWC[fileCount].push_back(entry[entryCount]);///////////////////////////////
			  }
			  checkRepetition.push_back(vectWord[itr]);
		//	  checkRepetition.push_back(vectWord[f][itr]);//////////////////////////
			  wordRepetitionCount = 0;
	//		  wordRepetitionCount[f]; ///////////////////////////////////////////////
			  ++entryCount;
			  delete[entryCount] entry;
		  }
		  checkRepetition.clear();
	  }

			  ///////////////////////////////////////////////////////////
//	  void ConverterJSON::readingFromDatabase(int n, mutex film_mutex[DOCUMENT_NUMBER], string movPath[DOCUMENT_NUMBER], vector<string> vWord[DOCUMENT_NUMBER], vector<Entry> getWC[DOCUMENT_NUMBER], string  strWrd[DOCUMENT_NUMBER], int filesC[DOCUMENT_NUMBER], vector<Entry> vectEntr[DOCUMENT_NUMBER], multimap<string, vector< Entry>> &countWordMap)
   //   void ConverterJSON::readingFromDatabase(promise<string>& promise)
//	  {
//		  string input;
//		  getline(cin, input);
//		  promise.set_value(input);
//	  }
	  /// //////////////////////////////////////////////////

	//  void ConverterJSON :: wordCountFunction(multimap<string, vector< Entry>>& countWMap)
//	  void ConverterJSON::wordCountFunction(multimap<string, vector< Entry>>countWordMap)
	  void ConverterJSON::wordCountFunction(multimap<string, vector< Entry>> &countWordMap)
	  {
		  static const int dcN = configuration.documentsNumber;
		  vector<string> vectorWord;
	//	  vector<string> vectorWord[DOCUMENT_NUMBER];///////////////////
	//	  vector<Entry> getWordCount;
		  vector<Entry> getWordCount[DOCUMENT_NUMBER];//////////////////////
		  string strWord = "";
	//	  string strWord[DOCUMENT_NUMBER];//////////////////
		  int filesCount = 0;
	//	  int filesCount[DOCUMENT_NUMBER];////////////////////
	//	  vector<Entry> vectorEntry;
		  vector<Entry> vectorEntry[DOCUMENT_NUMBER];//////////////////
	//	  ThreadPool pool(dcN);////////////////////////////
	//	  std::vector< std::future<int> > results;/////////////////
		  string moviePath[DOCUMENT_NUMBER];//////////////////////
	//	  string moviePath;
		  thread film[DOCUMENT_NUMBER];//////////////////////
		  thread EntryFill[DOCUMENT_NUMBER];
//		  thread wordSplit[DOCUMENT_NUMBER];
		  thread multiMap[DOCUMENT_NUMBER];
		  mutex film_mutex[DOCUMENT_NUMBER];
		  promise<string> promise;/////////////////
			  ifstream file[DOCUMENT_NUMBER];
		  for (int i = 0; i < DOCUMENT_NUMBER; ++i)
		  {

			  size_t it = configuration.movieTitles.count(i + 1);
			  moviePath[i] = configuration.movieTitles.at(i + 1);
			  file[i].open(moviePath[i]);
			  		  if (!file[i].is_open())
			  		  {
			  			  cerr << "\n" << "The file is not found." << "\n";
			  		  }
		  }

#pragma omp parallel for

		  for (int i =0; i<DOCUMENT_NUMBER ; ++i)
		  {

			  //	  for (auto it = configuration.movieTitles.begin(); it != configuration.movieTitles.end(); ++it)
			  //	  {
			  //		  film[i] = thread( this, i, film_mutex, moviePath, vectorWord, getWordCount, strWord, filesCount, vectorEntry, countWordMap);
	//		  film[i] = thread(&ConverterJSON::readingFromDatabase, this, i, film_mutex, moviePath, vectorWord, strWord);

				///////////////////////////////////////////////////////////
//		  size_t it = configuration.movieTitles.count(i + 1);
//		  moviePath[i] = configuration.movieTitles.at(i + 1);
	//		  file[i].seekg(0, ios::end);
		//	 int t=  file[i].tellg();
			 file[i].seekg(0);////////////////////////
//			 auto future = promise.get_future();///////////////////////
//			 thread file(&ConverterJSON::readingFromDatabase, ref(strWord));////////////////////////
//			 while (future.wait_for(std::chrono::seconds(0)) != std::future_status::ready)
//			 {
//				 this_thread::sleep_for(std::chrono::seconds(1));
//			 }
				  while (getline(file[i], strWord))
				  {	

					  film_mutex[i].lock();

					  film[i] = thread(&ConverterJSON::wordSplitFunction, this, strWord, vectorWord);
					  cout << "\n4444444444 " << " " << strWord;
					  film_mutex[i].unlock();
				  }
			strWord = "";
		  };
		  for (int i = 0; i < DOCUMENT_NUMBER; ++i)
		  {
		  film_mutex[i].lock();
			  film_mutex[i].unlock();
			  film[i].join();
		  file[i].close();
		  };

		  for (int i = 0; i < DOCUMENT_NUMBER; ++i)
		  {
	
			  EntryFill[i] = thread(&ConverterJSON::vectorEntryFillFunction, this, vectorWord, getWordCount, i);
			  vectorWord.clear();
	
		  };

		  for (int i = 0; i < DOCUMENT_NUMBER; ++i)
		  {
			  EntryFill[i].join();
		  };
		  for (int i = 0; i < DOCUMENT_NUMBER; ++i)
		  {
			  multiMap[i]=thread(&ConverterJSON::multiMapFillFunction, this, i, vectorEntry, getWordCount, countWordMap);
			  getWordCount[i].clear();
	  };
		  for (int i = 0; i < DOCUMENT_NUMBER; ++i)
		  {
			  multiMap[i].join();
	//		  cout << "\n000001111111222222222 " << " " << i;///////////////////////
		  };
	//	  );
		  /////////////////////////////////////////////////////////
		  
//		  string moviePath = it->second;
//		  ifstream file;
//		  file.open(moviePath);
//		  file.seekg(0);
//		  if (!file.is_open())
//		  {
//			  cerr << "\n" << "The file is not found." << "\n";
//		  }
//		  while (getline(file, strWord))
//		  {
//			  wordSplitFunction(strWord, vectorWord);
//		  }
//		  file.close();
//		  int entryCount = 0;
//			  vector<string> checkRepetition;
	//		  vectorEntryFillFunction(vectorWord, getWordCount, filesCount);
	//		  filesCount++;
	//		  vectorWord.clear();
	//		  multiMapFillFunction(vectorEntry, getWordCount, countWMap);
	//		  getWordCount.clear();
		//  };
	  }

	  void ConverterJSON :: searchAnswerFunction(multimap<string, vector< Entry>>& countWordMap)
	//  void ConverterJSON::searchAnswerFunction(multimap<string, vector< Entry>> &countWordMap)//////////////////
	  {
	//	  cout << "\n4444444444 " << countWordMap.size();///////////////////////
		  vector<string> requestWord;
	//	  vector<string> requestWord[1];///////////////////
		  ifstream requestFile("requests.json");
		  if (!requestFile)
			  cout << "\n " << "The file is not found.";
		  nlohmann::json configr;
			  requestFile >> configr;
		  requestFile.close();
			  for (const auto& iterator : configr["number"].items())
			  {
				  string strRequest = configr["request"];
	//			  string strRequest[1] = { "request"};
			  wordSplitFunction(strRequest, requestWord);
	//			  wordSplitFunction(0,0, strRequest, requestWord);//////////////////////
			  multimap<size_t, size_t> searchResult;
			  ofstream ansfile("answers.json");
			  nlohmann::json ansconfig[MAX_RESPONS], ansconfigur, answerconfig, answconfig;
		//	  int absoluteRelevance = 0,
			  size_t absoluteRelevance = 0,////////////////////
				  maxAbsoluteRelevanceDoc = 0,
				  maxAbsoluteRelevance = 0,
				  nlohmArrayCount = 0;
			  answerconfig = { {"request", iterator.value()} };
		//	  for (int i = 0; i < requestWord.size(); ++i)
			  for (int i = 0; i < requestWord[0].size(); ++i)//////////////////////
			  {
				  for (auto it = countWordMap.begin(); it != countWordMap.end(); ++it)
				  {
					  if (requestWord[i] == it->first)
		//			  if (requestWord[0][i] == it->first)/////////////////////////
					  {
						  for (auto m : it->second)
						  {
							  searchResult.insert({ m.freqWordsCount, m.docId });
							  absoluteRelevance += m.freqWordsCount;
							  if (absoluteRelevance > maxAbsoluteRelevance)
								  maxAbsoluteRelevanceDoc = absoluteRelevance;
						  } // Á‡Í˚‚‡ÂÚ ˆËÍÎ ÔÓ auto m : it->second
					  }
				  }//Á‡Í˚‚‡ÂÚ auto it = countWMap
				  int countResponses = 0;
				  for (auto iter = searchResult.crbegin(); iter != searchResult.crend(); ++iter)
				  {
					  if (countResponses < MAX_RESPONS)
					  {
						  if (iter->first > 0)
						  {
							  ansconfigur += { { "Document number", iter->second }, { "Number of matches",iter->first }, };
						  }
					  }
					  else
					  {
						  searchResult.clear();
						  break;
					  }
					  countResponses++;
				  } //Á‡Í˚‚‡ÂÚ ˆËÍÎ ÔÓ searchResult.cr
				  if (absoluteRelevance > 0)
					  ansconfig[nlohmArrayCount] = { { "word ", requestWord[i]},{"result", { absoluteRelevance > 0} }, {"Absolute relevance", absoluteRelevance},{"Relative relevance",0.}, { ansconfigur} };
				  if (absoluteRelevance == 0)
				  {
					  ansconfig[nlohmArrayCount] = { { "word ", requestWord[i]}, {"result", { absoluteRelevance != 0}}, {"Absolute relevance", absoluteRelevance},{"Relative relevance",0.}, { ansconfigur == 0} };
				  }
				  nlohmArrayCount++;
				  ansconfigur.clear();
				  absoluteRelevance = 0;
				  searchResult.clear();
				  if (maxAbsoluteRelevanceDoc > maxAbsoluteRelevance)
					  maxAbsoluteRelevance = maxAbsoluteRelevanceDoc;
			  } //Á‡Í˚‚‡ÂÚ i < requestWord.size()
			  double relativeRelevance = 0;
			  for (int id = 0; id < MAX_RESPONS; ++id)
			  {
				  for (const auto& item : ansconfig[id].items())
				  {
					  relativeRelevance = (double)ansconfig[id][2].at(1) / (double)maxAbsoluteRelevance;
					  relativeRelevance = round(relativeRelevance * 100) / 100;
					  ansconfig[id][3].at(1) = relativeRelevance;
					  cout << "\n " << item.value();
				  }
				  cout << "\n";
				  if (ansconfig[id] > 0)
					  answconfig += {{ansconfig[id]}};
			  }
			  answerconfig = { {"request",  configr["number"]},{answconfig}};
			  ansfile << answerconfig;
			  answerconfig.clear();
		       searchResult.clear();
		       ansconfig->clear();
		       ansfile.close();
	//		   cout << "\n000000000000 " << " " << countWMap.size();/////////////////////////////
	      } //Á‡Í˚‚‡ÂÚ auto& item : configr["number"].items
	  }// ‚˚ıÓ‰ ËÁ ÙÛÌÍˆËË
