#ifndef _FILE_
#define _CRT_SECURE_NO_WARNINGS
#define _FILE_
#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<cstdio>
#include<cstdlib>
#include<list>
#include<string>
#include<Windows.h>
#include<direct.h>
#ifndef _TESTSWITCH_
#include"testswitch.h"
//#include"GrammaticalAnalysis.h"
#endif
#define CHARACTER_MAX 257
#define READ_MAX 10
#define ENTER ""
#endif
#define FILE_LINE_MAX_NUMBER 1024
#define SYMBOL_SIZE 15
#define KEYWORD_TABLE 49
using namespace std;
extern enum Gram;
namespace file {
	
	using FilePtr = FILE *;
	class File //父文件类型
	{
	public:
		unsigned long long get_cur_line();//获取当前列
		static string split_file_dir(string fullPath);//获取文件路径
		static string split_file_dir(char*fullPath);
		static string split_file_name(string fullPath);//获取文件名
		static string split_file_name(char*fullPath);
		static string get_program_dir();//获取当前程序的路径
		File(string filename);
		unsigned long long get_token_size();//获取符号大小
		File() { flag = false; curLine = 1; };
		inline virtual	bool set_file_path(string filename);//设置文件 名
		inline virtual	bool set_file_path(char*filename);
		void roll_back();//回滚
		//	string executeRellback();//回滚函数,只能回滚一次
		//	string getRellback();//获取回滚值 
			//获取符号
	virtual string get_token();//获取符号
		string get_file();//获取文件名
		bool get_flag() { return flag; }
		
#if FILE_TEST==true
		friend class FileTest;
#endif

	protected:
		bool flag;//检测文件是否成功打开 
		//读取文件
		unsigned long long curLine;//当前存储符号的下标
		virtual	bool read_file() = 0;//读取文件
		string rellback;//回滚值
		list<list<string>>token;//存储符号
		std::string filename;//文件名
		bool lineFeed;//换行符
	};
	using CFilePtr = File *;
	class LexicalAnalysisFile :public File { //语法分析文件类型
	protected:

		bool read_file();

	public:
		//string get_token();
		LexicalAnalysisFile(string filePath) :File(filePath) {  }
		bool set_file_path(string fileName);
		/*LexicalAnalysisFile(char*ch) {

		}*/
	};
	

	class GrammaticalAnalysisFile :public File {
		
	public:
		//string get_token();
		
	protected:
		bool read_file();
		
	public:
		GrammaticalAnalysisFile(string filePath) :File(filePath) { set_file_path(filePath); }
		bool set_file_path(string fileName);
	private:
		string string_map_to_gram(const string&);
	inline   int string_hash(const string&);
	enum symbol{ keyword , num, real, id, add_sub_symbol, mul_symbol,
		div_symbol, logical_symbol, compare_symbol, character, characterMatch,
		l_bracket, r_bracket, comma, assignment_symbol, blank
	};
	static const string symbolStringTable[SYMBOL_SIZE];
	static const string keywordTable[KEYWORD_TABLE];
		//deque<deque<string>>token;
		//string rollBack;
	
	};

}




