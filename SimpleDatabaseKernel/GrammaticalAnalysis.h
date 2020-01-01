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
enum Gram {

};
enum GramCategory{
	//grammatical
	e_start, e_s,
	e_create_def, e_create_data_def, e_constraint_def, e_create_data_type_def, e_create_data_type_suffix_def,
	e_primary_def, e_for_che_uni_def, e_col_name_rep_def, e_foreign_def, e_str_rep_def,
	e_check_def, e_unique_def, e_addop_def, e_mulop_def, e_compare_def,
	e_logic_def, e_gather_fuc_def, e_int_real_col_name_def, e_int_real_col_name_rep_def, e_where_addop_def,
	e_where_mulop_def, e_where_algorithm_operator_def, e_where_algorithm_operator_or_string_def, e_where_compare_def, e_where_compare_or_string_match_def,
	e_logic_and_where_compare_string_match_def,e_where_logic_def,e_where_def,e_comma_and_col_name_def,
	e_order_def,e_group_def,e_having_def,e_where_algorithm_operator_rep_def,e_select_operator_def,
	e_connect_mode_def,e_connect_def,e_connect_addop_def,e_connect_mulop_def,
	e_connect_algorithm_operator_def,e_connect_algorithm_operator_or_string_def,e_connect_compare_def,
	e_connect_compare_or_str_match_def,e_logic_connect_compare_or_str_match_def,
	e_connect_logic_def,e_constraint_having_def,e_constriant_group_def,e_select_connect_def,
	e_constriant_connect_def,e_table_name_def,e_select_def,e_create_database_def,e_use_database_def,
	e_delete_element_def,e_delete_table_def,e_alter_table_add_col_name_def,e_alter_table_drop_col_name_def,
	e_insert_def,e_update_addop_def,e_update_mulop_def,e_update_def,e_create_view_def,
	e_drop_view_def,e_create_index_def,e_drop_index_def,

	e_less_than,e_less_than_or_equal,e_equal,e_unequal, e_greater_than, e_greater_than_or_equal, //compare

	e_and,e_or,e_sum,e_avg,e_count,e_min,e_max, //constriant

	//keyword
	e_create,e_table,e_char,e_not,e_null,e_primary,e_key,e_foreign,e_references,e_check,e_in,e_unique, e_like,e_where,
	e_order,e_by,e_desc,e_asc,e_group,e_having,e_right,e_left,e_full,e_join,e_on,e_distance,e_from,
	e_database,e_use,e_delete,e_alter,e_add,e_drop,e_column,e_insert,e_into,e_values,e_update,e_set,
	e_view,e_as,e_index,

	e_real,e_integer,e_str,e_id,e_strMatch,e_eof,

	e_addop,e_subop,e_mulop,e_divop,/*e_logical,e_compare,*///operator
	e_l_bracket,e_r_bracket,//bracket
	e_comma,e_empty


}; //数据类别
 //文法数据	
union Date { public:Date() {} ~Date() {} string strVal; int intVal; float realVal; };
//template<typename T>
struct DataType   {
 public: DataType( GramCategory category) {
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
//	string str;
	GramCategory category;

};
class GramDataType {
public: GramDataType(initializer_list<DataType>initializer) {
		initializer_list<DataType>::const_iterator begin, end;
		begin = initializer.begin();
		end = initializer.end();
		for (; begin != end; begin++) {
			ls.push_back(*begin);
		}
		posi = 0;
	}
		void set_posi(int posi) { this->posi = posi; }
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

	/*
	v_create_def,		v_create_data_def,	v_constraint_def,		v_create_data_type_def,			v_create_data_type_suffix_def,
	v_primary_def,		v_for_che_uni_def,	v_col_name_rep_def,		v_foreign_def,					v_str_rep_def,
	v_check_def,		v_unique_def,		v_addop_def,			v_mulop_def,					v_compare_def,
	v_logic_def,		v_gather_fuc_def,	v_int_real_col_name_def, v_int_real_col_name_rep_def,	v_where_addop_def,
	v_where_mulop_def,	v_where_algorithm_operator_def ,v_where_algorithm_operator_or_string_def,	v_where_compare_def, v_where_compare_or_string_match_def,
	v_logic_and_where_compare_string_match_def

	*/
	const static GramType v_create_def;  //0
	const static GramType v_create_data_def; //1 
	const static GramType v_constraint_def;  //2
	const static GramType v_create_data_type_def;  //3
	const static GramType v_create_data_type_suffix_def; //4
	const static GramType v_primary_def; //5
	const static GramType v_for_che_uni_def; //6
	const static GramType v_col_name_rep_def; //7
	const static GramType v_foreign_def; //8
	const static GramType v_str_rep_def; //9
	const static GramType v_check_def; //10
	const static GramType v_unique_def; //11
	const static GramType v_addop_def; //12
	const static GramType v_mulop_def; //13
	const static GramType v_compare_def;//14
	const static GramType v_logic_def;//15
	const static GramType v_gather_fuc_def;//16
	const static GramType v_int_real_col_name_def;//17
	const static GramType v_int_real_col_name_rep_def;//18
	const static GramType v_where_addop_def;//19
	const static GramType v_where_mulop_def;//20
	const static GramType v_where_algorithm_operator_def;//21
	const static GramType v_where_algorithm_operator_or_string_def;//22
	const static GramType v_where_compare_def;//23
	const static GramType v_where_compare_or_string_match_def; //24
	const static GramType v_logic_and_where_compare_string_match_def; //25
	const static GramType v_where_logic_def;//26
	const static GramType v_where_def;//27
	const static GramType v_comma_and_col_name_def;//28
	const static GramType v_order_def;//30
	const static GramType v_group_def;//31
	const static GramType v_having_def;//32
	const static GramType v_where_algorithm_operator_rep_def;//33
	const static GramType v_select_operator_def;//34
	const static GramType v_connect_mode_def;//35
	const static GramType v_connect_def;//36
	const static GramType v_connect_addop_def;//37
	const static GramType v_connect_mulop_def;//38
	const static GramType v_connect_algorithm_operator_def;//39
	const static GramType v_connect_algorithm_operator_or_string_def;//40
	const static GramType v_connect_compare_def;//41
	const static GramType v_connect_compare_or_str_match_def;//42
	const static GramType v_logic_connect_compare_or_str_match_def;//43
	const static GramType v_connect_logic_def;//44
	const static GramType v_constriant_having_def;//45
	const static GramType v_constraint_group_def;//46
	const static GramType v_select_connect_def;//47
	const static GramType v_constriant_connect_def;//48
	const static GramType v_table_name_def;//49
	const static GramType v_select_def;//50
	const static GramType v_create_database_def;//51
	const static GramType v_use_database_def;//52
	const static GramType v_delete_element_def;//53
	const static GramType v_delete_talbe_def;//54
	const static GramType v_alter_table_col_name_def;//54
	const static GramType v_alter_table_drop_col_name_def;//55
	const static GramType v_insert_def;//56
	const static GramType v_update_addop_def;//57
	const static GramType v_update_mulop_def;//58
	const static GramType v_update_def;//59
	const static GramType v_create_view_def;//60
	const static GramType v_drop_view_def;//61
	const static GramType v_create_index_def;//62
	const static GramType v_drop_index_def;//63
};
class GrammaticalAnalysis {
public:
	CFilePtr file;
	/*GrammaticalAnalysis() {

	}*/

};

