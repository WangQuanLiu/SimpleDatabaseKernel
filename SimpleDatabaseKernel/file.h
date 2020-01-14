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
using namespace std;
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
		//	string executeRellback();//�ع�����,ֻ�ܻع�һ��
		//	string getRellback();//��ȡ�ع�ֵ 
			//��ȡ����
		virtual	string get_token() = 0;//��ȡ����
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
	};
	using CFilePtr = File *;
	class LexicalAnalysisFile :public File { //�﷨�����ļ�����
	protected:

		bool read_file();

	public:
		string get_token();
		LexicalAnalysisFile(string filePath) :File(filePath) {  }
		bool set_file_path(string fileName);
		/*LexicalAnalysisFile(char*ch) {

		}*/
	};
	typedef struct GramTokenType {
	public: GramTokenType() = default;
			GramTokenType(const GramTokenType&obj);
			void setGram(const string&gram);
			void setString(const string&string);
			std::string getGram();
			std::string getString();
		explicit	GramTokenType(const string&gram, const string&str);
		explicit	GramTokenType(const char*, const char*);
	private:
		string gram, string;
	}GramToken;

	class GrammaticalAnalysisFile :public File {
	public:
		string get_token();
	protected:
		bool read_file();
	public:
		GrammaticalAnalysisFile(string filePath) :File(filePath) {}
		bool set_file_path(string fileName);
	private:
		deque<deque<GramToken>>token;
	
	};

}




