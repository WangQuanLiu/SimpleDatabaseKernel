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
#define ALPH_MAX 50
#define NFA_ROW_MAX 258
#define NFA_COL_MAX 51
#define START_STATUS_MAX 33
using namespace std;

struct ConverTable {//ӳ���
private:
	
	vector<vector<int>>status;
	map<int, int>mapStatus;
public:
	
	ConverTable() = default;
//���ӳ�䣬��sta��ch���ַ����±��е�ֵΪval
	void addMap(int sta,char ch,int val);
	int getValues(int sta, char ch);//��ȡӳ���ֵ 
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
	//��ʼ��status
	StatusSet(initializer_list<int>list);
	StatusSet(vector<int>&vec);
	StatusSet& operator=(initializer_list<int>list);
	void print();
	vector<int>getSet();
	StatusSet&operator=(vector<int>&obj);
	StatusSet&operator=(StatusSet&obj);
	bool operator==(StatusSet&obj)const;
};
class LexicalAnalysis {
private:
	string filename;
	static vector<StatusSet>status;//dfa״̬����
	static ConverTable conver;//ת����
	//����״̬S,�����ַ�C���õ�����󼯺� 
	static std::vector<int> edge(int s, char c);

	//״̬S���������κ��ַ����õ�����󼯺�
	static std::vector<int>closure(int s);

	/*	dfaedge����������һ״̬���ϣ�Ȼ�󷵻س����״̬���ϳ����ַ�ch��õ���һ��״̬����	*/
	static std::vector<int>dfaEdge(vector<int>&vec, char ch);
	//NFAת����DFA
	 void NfaConvertToDfa();

public:
	bool setFileName(string filename);
	static const char alphabet[ALPH_MAX];//�ַ�����
	static const int nfa[NFA_ROW_MAX][NFA_COL_MAX];//nfa�Զ���
	static const int startStatus[START_STATUS_MAX];
#if LEXICAL_TEST==true
	friend  class LexicalTest;
#endif

};
//ch�ַ���alphabet�����е��±�
int letterConvertToIndex(const char alphabet[] ,size_t size, char ch);
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
#endif
 