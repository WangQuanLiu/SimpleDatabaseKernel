#ifndef _FILE_
#define _CRT_SECURE_NO_WARNINGS
#define _FILE_
#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<list>
#include<string>
#include<Windows.h>
#ifndef _TESTSWITCH_
#include"testswitch.h"
#endif
#define CHARACTER_MAX 257
#define READ_MAX 10
#undef EOF
#define EOF ""
#endif
using namespace std;
using FilePtr = FILE * ;
class File
{
public:
	static string GetProgramDir();
	File(string filename);
	File() { flag = false; };
	bool set_file_name(string filename);//�����ļ� ��
	bool set_file_name(char*filename);
	string executeRellback();//�ع�����,ֻ�ܻع�һ��
	string getRellback();//��ȡ�ع�ֵ 
	//��ȡ����
	string getToken();
	string getFile();//��ȡ�ļ���
	bool get_flag() { return flag; }
#if FILE_TEST==true
	friend class FileTest;
#endif

private:
	bool flag;//����ļ��Ƿ�ɹ��� 
	//��ȡ�ļ�
	static string split_file_name(string fullPath);//��ȡ�ļ���
	static string split_file_name(char*fullPath);
	bool read_file();//��ȡ�ļ�
	string rellback;//�ع�ֵ
	list<string>token;//�洢����
	std::string filename;//�ļ���
};






