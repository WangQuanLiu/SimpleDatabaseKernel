#include<iostream>
#include<cstdlib>
#include<vector>
#ifndef _TESTSWITCH_
#include"testswitch.h"
#include"file.h"
#endif
#define _GrammaticalAnalysis_
//#define NFA_MAX 34
//#define ALPHA_MAX 40
#define GRAM_MAX 66
#define GRAM_STRING_TABLE_MAX 136
#define GRAM_ENUM_MAX 136
#define EMPTY -1
#define GOTO_TABLE_MAX 1000
//using GrammaticalType= vector<list<string>>;
//using GrammaticalDataType = list<string>;
using namespace file;
using CFilePtr = file::File *;
enum GramCategory {
	gram,//文法 grammatical
	non_gram//非文法 non-grammatical
};
const string GramStringTable[GRAM_STRING_TABLE_MAX]{ //文法的字符串
	"e_start", "e_s",
	"e_create_def", "e_create_data_def", "e_constraint_def", "e_create_data_type_def", "e_create_data_type_suffix_def",
	"e_primary_def", "e_for_che_uni_def", "e_col_name_rep_def", "e_foreign_def", "e_str_rep_def",
	"e_check_def", "e_unique_def", "e_addop_def", "e_mulop_def", "e_compare_def",
	"e_logic_def", "e_gather_fuc_def", "e_int_real_col_name_def", "e_int_real_col_name_rep_def", "e_where_addop_def",
	"e_where_mulop_def", "e_where_algorithm_operator_def", "e_where_algorithm_operator_or_string_def", "e_where_compare_def", "e_where_compare_or_string_match_def",
	"e_logic_and_where_compare_string_match_def","e_where_logic_def","e_where_def","e_comma_and_col_name_def",
	"e_order_def","e_group_def","e_having_def","e_where_algorithm_operator_rep_def","e_select_operator_def",


	"e_connect_mode_def","e_connect_def","e_connect_addop_def","e_connect_mulop_def",
	"e_connect_algorithm_operator_def","e_connect_algorithm_operator_or_string_def","e_connect_compare_def",
	"e_connect_compare_or_str_match_def","e_logic_connect_compare_or_str_match_def",
	"e_connect_logic_def","e_constraint_having_def","e_constriant_group_def","e_select_connect_def",
	"e_constriant_connect_def","e_table_name_def","e_select_def","e_create_database_def","e_use_database_def",
	"e_delete_element_def","e_delete_table_def","e_alter_table_add_col_name_def","e_alter_table_drop_col_name_def",
	"e_insert_def","e_update_addop_def","e_update_mulop_def","e_update_def","e_create_view_def",
	"e_drop_view_def","e_create_index_def","e_drop_index_def",

	"e_less_than","e_less_than_or_equal","e_equal","e_unequal", "e_greater_than", "e_greater_than_or_equal", //compare

	"e_and","e_or","e_sum","e_avg","e_count","e_min","e_max", //constriant

												//keyword
	"e_create","e_table","e_char","e_not","e_null","e_primary","e_key","e_foreign","e_references","e_check","e_in","e_unique", "e_like","e_where",
	"e_order","e_by","e_desc","e_asc","e_group","e_having","e_right","e_left","e_full","e_join","e_on","e_distance","e_from",
	"e_database","e_use","e_delete","e_alter","e_add","e_drop","e_column","e_insert","e_into","e_values","e_update","e_set",
	"e_view","e_as","e_index",

	"e_real","e_integer","e_str","e_id","e_strMatch","e_eof",

	"e_addop","e_subop","e_mulop","e_divop",/*e_logical,e_compare,*///operator
	"e_l_bracket","e_r_bracket",//bracket
	"e_comma","e_empty",
	"e_gram_end" //grammatical end


};
enum Gram{ //文法的枚举类
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
	e_comma,e_empty,
	e_gram_end //grammatical end


}; //文法类别

 //文法数据	
union Date { public:Date() {} ~Date() {} string strVal; int intVal; float realVal; };
//template<typename T>
struct DataType   {	//单个文法类
 public: DataType( Gram category) {
	 set_category(category);
	 }
		 Gram getCategory();
		 bool operator==(DataType category);
		 friend bool operator!=(const DataType& category1, const DataType& category2);
		
		/* DataType(int integer, Gram cateory) {
			 date.intVal = integer;
			 set_category(category);
		 }
		
		 DataType(float real, Gram cateory) {
			 date.realVal;
			 set_category(category);
		 }*/
		 void set_category(Gram category);
//	string str;
private:	Gram category;

};
class GramDataType {//单个文法集合

public: 
	GramDataType() = default;
	GramDataType(initializer_list<DataType>initializer);
	friend bool operator!=(const vector<GramDataType>objA, const vector<GramDataType>objB);
	friend bool operator==(const vector<GramDataType>objA, const vector<GramDataType>objB);
	friend bool operator==(GramDataType objA, GramDataType objB);
	friend bool operator!=(GramDataType objA, GramDataType objB);
	void setGramName(Gram gramName);
	Gram getGramName();
	Gram getSymbol();
	int getPosi();
	/*	void set_symbol(vector<Gram>&vec) {
			this->symbol = vec;
		}*/
	void set_symbol(Gram &obj);
		/*void add_symbol(initializer_list<Gram>initializer) {
			initializer_list<Gram>::const_iterator begin, end;
			begin = initializer.begin();
			end = initializer.end();
			for (; begin != end; begin++)
				symbol.push_back(*begin);

		}*/
		/*void set_symbol(initializer_list<Gram>initializer) {
			initializer_list<Gram>::const_iterator begin, end;
			begin = initializer.begin();
			end = initializer.end();
			for (; begin != end; begin++)
				symbol.push_back(*begin);
		}*/
		GramDataType& operator=(const GramDataType&);
		GramDataType& operator+=(int);
		GramDataType operator+(int);
		vector<DataType>getLs();
	//	void set_posi(int posi) { this->posi = posi; }
	vector<DataType>ls;
	int posi;
	//vector<Gram>symbol;
	Gram symbol;
	Gram gramName;
};
 /*using DataType = struct DataType;
 using GramDataType = list<DataType>;*/
 //using GramType = vector<GramDataType>;
 struct GramType{//一个文法中可能指向多个文法，这个是指向多个文法集合
	 vector<GramDataType>vec;
		Gram gramName;
		GramType(initializer_list<GramDataType>list);
		void setGramName(Gram gramName);
		Gram getGramName();
 };
//typedef GrammaticalType{
//	
//}GraType;
class Grammatical { 
public :
	 static GramType v_start; //0
	 static GramType v_s;//1
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
	 static GramType v_create_def;  //2
	 static GramType v_create_data_def; //3 
	 static GramType v_constraint_def;  //4
	 static GramType v_create_data_type_def;  //5
	 static GramType v_create_data_type_suffix_def; //6
	 static GramType v_primary_def; //7
	 static GramType v_for_che_uni_def; //8
	 static GramType v_col_name_rep_def; //9
	 static GramType v_foreign_def; //10
	 static GramType v_str_rep_def; //11
	 static GramType v_check_def; //12
	 static GramType v_unique_def; //13
	 static GramType v_addop_def; //14
	 static GramType v_mulop_def; //15
	 static GramType v_compare_def;//16
	 static GramType v_logic_def;//17
	 static GramType v_gather_fuc_def;//18
	 static GramType v_int_real_col_name_def;//19
	 static GramType v_int_real_col_name_rep_def;//20
	 static GramType v_where_addop_def;//21
	 static GramType v_where_mulop_def;//22
	 static GramType v_where_algorithm_operator_def;//23
	 static GramType v_where_algorithm_operator_or_string_def;//24
	 static GramType v_where_compare_def;//25
	 static GramType v_where_compare_or_string_match_def; //26
	 static GramType v_logic_and_where_compare_string_match_def; //27
	 static GramType v_where_logic_def;//28
	 static GramType v_where_def;//29
	 static GramType v_comma_and_col_name_def;//30
	 static GramType v_order_def;//31
	 static GramType v_group_def;//32
	 static GramType v_having_def;//33
	 static GramType v_where_algorithm_operator_rep_def;//34
	 static GramType v_select_operator_def;//35
	 static GramType v_connect_mode_def;//36
	 static GramType v_connect_def;//37
	 static GramType v_connect_addop_def;//38
	 static GramType v_connect_mulop_def;//39
	 static GramType v_connect_algorithm_operator_def;//40
	 static GramType v_connect_algorithm_operator_or_string_def;//41
	 static GramType v_connect_compare_def;//42
	 static GramType v_connect_compare_or_str_match_def;//43
	 static GramType v_logic_connect_compare_or_str_match_def;//44
	 static GramType v_connect_logic_def;//45
	 static GramType v_constriant_having_def;//46
	 static GramType v_constraint_group_def;//47
	 static GramType v_select_connect_def;//48
	 static GramType v_constriant_connect_def;//49
	 static GramType v_table_name_def;//50
	 static GramType v_select_def;//51
	 static GramType v_create_database_def;//52
	 static GramType v_use_database_def;//53
	 static GramType v_delete_element_def;//54
	 static GramType v_delete_table_def;//55
	 static GramType v_alter_table_col_name_def;//56
	 static GramType v_alter_table_drop_col_name_def;//57
	 static GramType v_insert_def;//58
	 static GramType v_update_addop_def;//59
	 static GramType v_update_mulop_def;//60
	 static GramType v_update_def;//61
	 static GramType v_create_view_def;//62
	 static GramType v_drop_view_def;//63
	 static GramType v_create_index_def;//64
	 static GramType v_drop_index_def;//65
};
typedef struct GramTokenType {//读取词法分析产生的文件中单元结构
public: GramTokenType() = default;
		GramTokenType(const GramTokenType&obj);
		void setGram(const string&gram);
		void setString(const string&string);
		std::string getGram();
		std::string getString();
		explicit	GramTokenType(const string&gram, const string&str);
		explicit	GramTokenType(const char*, const char*);
		friend bool operator==(const GramTokenType&objA, const GramTokenType&objB);
private:
	string gram, //语法类别
		string;//字符串
}GramToken;
class GrammaticalAnalysis {
public:
	///CFilePtr file;
	GrammaticalAnalysis(string filePath);
	void run();
	/*GrammaticalAnalysis() {

	}*/

#if TEST&&GRAM_TEST
	void  test_first() {
		GramType temp = gramArray[0];
		GramDataType temp2 = temp.vec[0];
		//cout << temp2.ls[1].getCategory() << endl;
		 //cout << first(temp2) << endl;
	}
	void test() {
		init();
		//GramType temp = gramArray[0];
	//	temp.vec[0].symbol = e_eof;
	//	vector<GramDataType>vec;
	//	GramDataType temp = gramArray[0].vec[0];
	//	temp.symbol = e_eof;
	//	vec.push_back(temp);
	//	//closure(vec);
	//	GramType gramTypeTemp = gramArray[4];
	//	for (int i = 0; i < gramTypeTemp.vec.size(); i++) {
	//		gramTypeTemp.vec[i].symbol = e_primary_def;
	//	}
	//vector<GramDataType>temporary=	Goto(gramTypeTemp, e_primary_def);
	//	//Goto(gramTypeTemp, e_primary_def);
	//	 gramTypeTemp = gramArray[21];
	//	 for (int i = 0; i < gramTypeTemp.vec.size(); i++) {
	//		 gramTypeTemp.vec[i].symbol = e_eof;
	//	 }
	//status=items(gramTypeTemp);
	//print(GotoTable);
	//	 vector<GramDataType>tempA = status[GotoTable[e_constraint_def][e_primary]];
		/*Goto(gramArray[])*/
		//grammatical_convert_to_dfa();
		//get_derived_grammar(e_s);
		//cout << GramStringTable[135] << endl;
	}
#endif
private:
	file::CFilePtr file;
	void init();
	bool check_grammatical();
//	void print
	int GotoTable[GOTO_TABLE_MAX][GRAM_ENUM_MAX];
#if(TEST&&GRAM_TEST)
	void print(int GotoTable[GOTO_TABLE_MAX][GRAM_ENUM_MAX]);
#endif
	vector<vector<GramDataType>>status;
	inline vector<GramDataType>&vector_join_other_vector(vector<GramDataType>&join, vector<GramDataType>&beJoined);
	vector<vector<GramDataType>>items(GramType);
	vector<GramDataType>Goto(const GramDataType&, const Gram&);
	vector<GramDataType>Goto(const GramType&,const Gram&);
	vector<GramDataType>Goto(const vector<GramDataType> &, const Gram &);
	vector<GramType> get_derived_grammar( DataType obj);//派生文法，即文法推导文法，不
	Gram first(GramDataType&obj);//寻找文法中第一个非文法的字符  find first char of non-grammatical in grammatical
	GramCategory is_grammatical(Gram obj);//判断是文法还是非文法 Judge whether it is grammatical or non-grammatical
	void grammatical_convert_to_dfa();//文法转换成dfa
	vector<GramDataType> closure(const vector<GramDataType>&);
	inline string gram_map_to_string(const Gram&obj);
inline	GramType gram_map_to_gramtype(const Gram&obj);//gram map to gramtype
	static GramType gramArray[GRAM_MAX]; //文法数组 grammatical array
};

