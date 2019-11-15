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
	bool set_file_name(string filename);//设置文件 名
	bool set_file_name(char*filename);
	string executeRellback();//回滚函数,只能回滚一次
	string getRellback();//获取回滚值 
	//获取符号
	string getToken();
	string getFile();//获取文件名
	bool get_flag() { return flag; }
#if FILE_TEST==true
	friend class FileTest;
#endif

private:
	bool flag;//检测文件是否成功打开 
	//读取文件
	static string split_file_name(string fullPath);//获取文件名
	static string split_file_name(char*fullPath);
	bool read_file();//读取文件
	string rellback;//回滚值
	list<string>token;//存储符号
	std::string filename;//文件名
};






