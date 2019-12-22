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
enum GramCategory{ real=1,integer,str,keyword,grammatical,id,strMatch,eof,mul,add,sub,divison,logical,compare,l_block,r_block,comma,empty}; //数据类别
 //文法数据	
union Date { public:Date() {} ~Date() {} string strVal; int intVal; float realVal; };
//template<typename T>
struct DataType   {
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
	const static GramType v_start; //start s'->s $
	const static GramType v_s; // s->v_create_def | v_select_def | v_create_database_def |v_use_database_def|
	                         // v_delete_element_def | v_delete_table_def |v_alter_table_add_column_def|
							// v_alter_table_drop_column_def | v_insert_def |v_update_def|v_crate_view|
							// v_drop_view | v_crate_index |v_drop_index
	const static GramType v_create_def; //v_create_def-> crate table table_name ( v_create_data_def v_constraint_def)
	const static GramType v_create_data_def; //v_create_data_def-> data_name v_create_data_type_def v_create_data_type_suffx_def {, v_create_data}    {}representative repeat
	const static GramType v_constraint_def; //v_constraint_def-> 
	const static GramType v_create_data_type_def; //v_create_data_type_def->flaot|int|char(number) 
	const static GramType v_create_data_type_suffx_def;// v_create_data_type_suffx_def-> ε |not null     ε representive  empty
	
};
class GrammaticalAnalysis {
public:
	CFilePtr file;
	/*GrammaticalAnalysis() {

	}*/

};

