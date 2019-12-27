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
enum GramCategory{ real=1,integer,str,keyword,grammatical,id,strMatch,eof,addop,mulop,logical,compare,l_bracket,r_bracket,comma,empty}; //数据类别
 //文法数据	
union Date { public:Date() {} ~Date() {} string strVal; int intVal; float realVal; };
//template<typename T>
struct DataType   {
 public: DataType(string str, GramCategory category=grammatical) {
	 this->str = str;
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
	string str;
	GramCategory category;

};
class GramDataType {
public: GramDataType(initializer_list<DataType>initializer) {
		initializer_list<DataType>::const_iterator begin, end;
		begin = initializer.begin();
		end = initializer.end();
		posi = 0;
	}
	list<DataType>ls;
	int posi;
	vector<string>symbol;

};
 /*using DataType = struct DataType;
 using GramDataType = list<DataType>;*/
 using GramType = vector<GramDataType>;
//typedef GrammaticalType{
//	
//}GraType;
class Grammatical {
	const static GramType v_start; 
	const static GramType v_s;

	/*
	v_create_def -> create table table_name (v_create_data_def v_constraint_def)
	*/
	const static GramType v_create_def; 
	const static GramType v_create_data_def; 
	const static GramType v_constraint_def; 
	const static GramType v_create_data_type_def; 
	const static GramType v_create_data_type_suffix_def;
	const static GramType v_primary_def;
	const static GramType v_for_che_uni_def;
	const static GramType v_col_name_rep_def;
	const static GramType v_foreign_def;
	const static GramType v_str_rep_def;
	const static GramType v_check_def;
	const static GramType v_unique_def;
	const static GramType v_addop_def;
	const static GramType v_mulop_def;
	const static GramType v_compare_def;
	const static GramType v_logic_def;
	const static GramType v_gather_fuc_def;
	const static GramType v_int_real_col_name_def;
	const static GramType v_int_real_col_name_rep_def;
	const static GramType v_where_addop_def;
};
class GrammaticalAnalysis {
public:
	CFilePtr file;
	/*GrammaticalAnalysis() {

	}*/

};

