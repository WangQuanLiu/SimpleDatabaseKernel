#ifndef _FILE_
#define _CRT_SECURE_NO_WARNINGS
#define _FILE_
#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<string>
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
	File(string filename);
	File() {};
	//设置文件 名
	bool setFileName(string filename);
	bool setFileName(char*filename);
	//获取符号
	string getToken();
	string getFile();
	bool getFlag() { return flag; }
#if FILE_TEST==true
	friend class FileTest;
#endif

private:
	bool flag;//检测文件是否成功打开 
	//读取文件
	bool readFile();
	queue<string>token;//
	std::string filename;//文件名
};






