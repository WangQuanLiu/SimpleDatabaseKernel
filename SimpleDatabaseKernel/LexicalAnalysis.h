#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<string>
#include<set>
#include<map>
#include<algorithm>
#include<initializer_list>
#include<memory>
#ifndef _TESTSWITCH_
#include"testswitch.h"
#include"file.h"
#endif
#define _LexicalAnalysis_
namespace cfe {
#define ALPH_MAX 50 //�ַ��ĸ���
#define NFA_ROW_MAX 292 //NFA����
#define NFA_COL_MAX 51 //NFA����
#define START_STATUS_MAX 34 //��ʼ״̬�ĸ���
#define END_STATUS_MAX 69 //����״̬�ĸ���

#define KEYWORD "keyword"
#define NUM "num"
#define REAL "real"
#define ID "id"
#define ADD_SUB_SYMBOL "add_sub_symbol"
#define MUL_SYMBOL "mul_symbol"
#define DIV_SYMBOL "div_symbol"
#define LOGCIAL_SYMBOL "logical_symbol"
#define COMPARE_SYMBOL "compare_symbol"
#define CHARACTER "character"
#define CHARACTERMATCH "characterMatch"
#define L_BRACKET "l_bracket"
#define R_BRACKET "r_bracket"
#define COMMA "comma"
#define ASSIGNMENT_SYMBOL "assignment_symbol"
#define BLANK "blank"
#define MAX 1000
#define NFA_CONVERT_TO_DFA_FUNCTION false
	enum end_statusType {
		logcial_symbol = 1,//�߼����� logical symbol
		keyword,//�ؼ��� keyword
		num,//���� number
		real,//������ real
		id,//�Զ���id 
		add_sub_symbol,//�ӷ�������� addition and subtraction operators
		mul_symbol,//�˷����� multiplication symbol 
		div_symbol,//��������
		compare_symbol,//�Ƚ���
		assignment_symbol,//��ֵ����
		character,//�ַ���
		characterMatch,//�ַ���ƥ��
		l_bracket,//������ 
		r_bracket,//������
		comma//����
	};//�������з���
	using namespace std;

	struct ConverTable {//ӳ��� mapping table
	private:
		vector<vector<int>>status;
		map<int, int>mapStatus;

	public:

		ConverTable() = default;
		//���ӳ�䣬��sta��ch���ַ����±��е�ֵΪval   add mapping,
		void add_map(int sta, char ch, int val);
		inline	int get_values(int sta, char ch);//��ȡӳ���ֵ  get the mapping value
		vector<vector<int>>getStatus();
#if LEXICAL_TEST==true
		friend  class LexicalTest;
#endif

	};
	struct StatusSet { //save status set class ����״̬����
	private:
		vector<int>status;
	public:
		StatusSet() = default;
		//��ʼ��status
		StatusSet(initializer_list<int>list);
		StatusSet(vector<int>&vec);
		StatusSet& operator=(initializer_list<int>list);
		void print();
		vector<int>get_set();
		StatusSet&operator=(vector<int>&obj);
		StatusSet&operator=(StatusSet&obj);
		bool operator==(StatusSet&obj)const;

	};
	class LexicalAnalysis {
	private:

		string outFilePath;//�﷨������������ļ�
		map<int, string>end_status_map_category;//��̬ӳ�����
		static vector<StatusSet>status;//dfa״̬����
		inline void init_end_status_map_category();//��ʼ����̬ӳ�����
		static ConverTable conver;//ת����
		void set_out_file_path();//����.lex�ļ�
		//����״̬S,�����ַ�C���õ�����󼯺� 
		static std::vector<int> edge(int s, char c);

		//״̬S���������κ��ַ����õ�����󼯺�
		static std::vector<int>closure(int s);

		/*	dfa_edge����������һ״̬���ϣ�Ȼ�󷵻س����״̬���ϳ����ַ�ch��õ���һ��״̬����	*/
		static std::vector<int>dfa_edge(vector<int>&vec, char ch);

		//NFAת����DFA
		void nfa_Convert_to_dfa();
		CFilePtr file;
	public:

		bool set_file_path(string filename);//�����ļ�·��
		LexicalAnalysis(string filePath);
		static const char alphabet[ALPH_MAX];//�ַ�����
		static const int nfa[NFA_ROW_MAX][NFA_COL_MAX];//nfa�Զ���
		static const int start_status[START_STATUS_MAX];//��ʼ״̬��
		static const int end_status[END_STATUS_MAX];//����״̬��
		static int string_map_category(string str);//strӳ�����
		void run();
#if LEXICAL_TEST==true
		friend  class LexicalTest;
#endif

	};
	//ch�ַ���alphabet�����е��±�
	inline int letter_convert_to_index(const char alphabet[], size_t size, char ch);
	/*
	  ---------------��ĸ��------------------
		0  1  2  3  4  5  6  7   8  9

		a  b  c  d  e  f  g  h	 i  j
	   10 11 12 13 14 15 16 17   18 19

		k  l  m  n  o  p  q  r   s  t
	   20 21  22 23 24 25 26 27  28 29

		u  v  w  x  y  z  >  <   =  +
		30 31 32 33 34 35 36 37  38 39

		-  *  /  (   )  '  %  _   .  ,
		40 41 42 43 44 45 46 47 48 49


	*/

}