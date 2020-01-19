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
	class File //���ļ�����
	{
	public:
		unsigned long long get_cur_line();//��ȡ��ǰ��
		static string split_file_dir(string fullPath);//��ȡ�ļ�·��
		static string split_file_dir(char*fullPath);
		static string split_file_name(string fullPath);//��ȡ�ļ���
		static string split_file_name(char*fullPath);
		static string get_program_dir();//��ȡ��ǰ�����·��
		File(string filename);
		unsigned long long get_token_size();//��ȡ���Ŵ�С
		File() { flag = false; curLine = 1; };
		inline virtual	bool set_file_path(string filename);//�����ļ� ��
		inline virtual	bool set_file_path(char*filename);
		void roll_back();//�ع�
		//	string executeRellback();//�ع�����,ֻ�ܻع�һ��
		//	string getRellback();//��ȡ�ع�ֵ 
			//��ȡ����
	virtual string get_token();//��ȡ����
		string get_file();//��ȡ�ļ���
		bool get_flag() { return flag; }
		
#if FILE_TEST==true
		friend class FileTest;
#endif

	protected:
		bool flag;//����ļ��Ƿ�ɹ��� 
		//��ȡ�ļ�
		unsigned long long curLine;//��ǰ�洢���ŵ��±�
		virtual	bool read_file() = 0;//��ȡ�ļ�
		string rellback;//�ع�ֵ
		list<list<string>>token;//�洢����
		std::string filename;//�ļ���
		bool lineFeed;//���з�
	};
	using CFilePtr = File *;
	class LexicalAnalysisFile :public File { //�﷨�����ļ�����
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




