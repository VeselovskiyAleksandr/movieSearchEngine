#include "Configuration.h"
#define MAX_SIZE 10000 //���������� ����� ���������� ���� � ����������
#define MAX_RESPONS 5 //���������� ����� �������

struct Configuration
{
	string name;//�������� �������� ������
	string version;//������ ������
	map<int, string> movieTitles;
	static const int maxRequest = 1000;//������������ ���������� �������
	static const int documentsNumber = 10; //���������� ����������
	static const int maxStrRequestLength = 80; //���������� ���������� ������ � �������
};