#include<iostream>
#ifndef _TESTSWITCH_
#include"testswitch.h"
#include"file.h"
#endif
#define _GrammaticalAnalysis_
#define NFA_MAX 34
#define ALPHA_MAX 40
//using GrammaticalType= vector<list<string>>;
//using GrammaticalDataType = list<string>;
enum GramCategory{ real=1,integer,str,keyword,grammatical,id,strMatch,eof,mul,add,sub,divison,logical,compare,l_block,r_block}; //�������
 //�ķ�����	
union Date { public:Date() {} ~Date() {} string strVal; int intVal; float realVal; };
//template<typename T>
 class DataType   {
 public: DataType(string str, GramCategory category=grammatical) {
	date = str;
	 set_category(category);
	 }
		/* DataType(int integer, GramCategory cateory) {
			 date.intVal = integer;
			 set_category(category);
		 }
		 DataType(float real, GramCategory cateory) {
			 date.realVal;
			 set_category(category);
		 }*/
		 void set_category(GramCategory category) { this->category = category; }
	string date;
	GramCategory category;

};
 using DataType = struct DataType;
 using GramDataType = list<DataType>;
 using GramType = vector<GramDataType>;
//typedef GrammaticalType{
//	
//}GraType;
class Grammatical {
	const static GramType start;
	const static GramType s;
	const static GramType v_create_def;
	const static GramType v_create_data_def;
	const static GramType v_constraint_def;
	
};
class GrammaticalAnalysis {
public:
	CFilePtr file;
	/*GrammaticalAnalysis() {

	}*/

};

