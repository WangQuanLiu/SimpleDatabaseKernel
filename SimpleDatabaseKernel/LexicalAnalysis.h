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
 // !_TESTSWITCH_
#ifndef _TESTSWITCH_
#include"testswitch.h"
#include"file.h"
#endif
#ifndef _LexicalAnalysis_
#define _LexicalAnalysis_
#define ALPH_MAX 50 //字符的个数
#define NFA_ROW_MAX 292 //NFA的行
#define NFA_COL_MAX 51 //NFA的列
#define START_STATUS_MAX 34 //开始状态的个数
#define END_STATUS_MAX 69 //结束状态的个数

#define KEYWORD "keyword"
#define NUM "num"
#define REAL "real"
#define ID "id"
#define ADD_SUB_SYMBOL "add_sub_symbol"
#define MUL_SYMBOL "mul_symbol"
#define DIV_SYMBOL "div_symbol"
#define LOGCIAL_SYMBOL "logcial_symbol"
#define CHARACTER "character"
#define CHARACTERMATCH "characterMatch"
#define L_BRACKET "l_bracket"
#define R_BRACKET "r_bracket"
#define COMMA "comma"
#define ASSIGNMENT_SYMBOL "assignment_symbol"
#define BLANK "blank"
#define MAX 1000
enum endStatusType {
	logcial_symbol=1,//逻辑符号
	keyword ,//关键字
	num,//数字
	real,//浮点数
	id,//自定义id
	add_sub_symbol,//加法运算符号
	mul_symbol,//乘法符号
	div_symbol,//除法符号
	assignment_symbol,//赋值符号
	character,//字符串
	characterMatch,//字符串匹配
	l_bracket,//左括号 
	r_bracket,//右括号
	comma//逗号
};//对语句进行分类
using namespace std;

struct ConverTable {//映射表
private:
	vector<vector<int>>status;
	map<int, int>mapStatus;

public:
	
	ConverTable() = default;
//添加映射，即sta行ch在字符表下标中的值为val
	void add_map(int sta,char ch,int val);
inline	int get_values(int sta, char ch);//获取映射的值 
	vector<vector<int>>getStatus();
#if LEXICAL_TEST==true
	friend  class LexicalTest;
#endif

};
 struct StatusSet {
private:
	vector<int>status;
public:
	StatusSet()=default;
	//初始化status
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
	
	string outFilePath;//语法分析后产生的文件
	map<int, string>endStatusMapCategory;//终态映射类别
	static vector<StatusSet>status;//dfa状态集合
	 inline void init_end_status_map_category();//初始化终态映射类别
	static ConverTable conver;//转换表
	void set_out_file_path();//产生.lex文件
	//求在状态S,输入字符C而得到的最大集合 
	static std::vector<int> edge(int s, char c);

	//状态S，求无需任何字符而得到的最大集合
	static std::vector<int>closure(int s);

	/*	dfa_edge函数是输入一状态集合，然后返回出这个状态集合吃入字符ch后得到的一组状态集合	*/
	static std::vector<int>dfa_edge(vector<int>&vec, char ch);

	//NFA转换成DFA
	 void nfa_Convert_to_dfa();

public:
	CFilePtr file;
	bool set_file_path(string filename);//设置文件路径
	LexicalAnalysis(string filePath);
	static const char alphabet[ALPH_MAX];//字符数组
	static const int nfa[NFA_ROW_MAX][NFA_COL_MAX];//nfa自动机
	static const int startStatus[START_STATUS_MAX];//开始状态集
	static const int endStatus[END_STATUS_MAX];//结束状态集
	static int string_map_category(string str);//str映射类别
	void run();
#if LEXICAL_TEST==true
	friend  class LexicalTest;
#endif

};
//ch字符在alphabet数组中的下标
inline int letter_convert_to_index(const char alphabet[] ,size_t size, char ch);
/*
  ---------------字母表------------------
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
#endif
 