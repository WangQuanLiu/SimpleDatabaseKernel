#ifndef _GrammaticalAnalysis_
#include"GrammaticalAnalysis.h"
#endif
const GramType Grammatical::v_start{
	GramDataType{DataType("s"),DataType("$",eof)}
};
const GramType Grammatical::v_s{
	GramDataType{DataType("v_create_def")},
	GramDataType{DataType("v_select_def")},
	GramDataType{DataType("v_create_database_def")},
	GramDataType{DataType("v_use_database_def")},
	GramDataType{DataType("v_delete_element_def")},
	GramDataType{DataType("v_delete_table_def")},
	GramDataType{DataType("v_alter_table_add_column_def")},
	GramDataType{DataType("v_alter_table_drop_column_def")},
	GramDataType{DataType("v_insert_def")},
	GramDataType{DataType("v_update_def")},
	GramDataType{DataType("v_create_view_def")},
	GramDataType{DataType("v_drop_view_def")},
	GramDataType{DataType("v_create_index_def")},
	GramDataType{DataType("v_drop_index_def")}
};
const GramType Grammatical::v_create_def{
	GramDataType{
	DataType("create",keyword),
	DataType("table",keyword),
	DataType("id",id),
	DataType("(",l_block),
	DataType("v_create_data_def"),
	DataType("v_constraint_def"),
	DataType(")",r_block)}
};
const GramType Grammatical::v_create_data_def{
	GramDataType{
	DataType("id",id),
	DataType("v_data_type_def"),
	DataType("v_data_type_suffix"),},

	GramDataType{  //repeat
	DataType("id",id),
	DataType("v_data_type_def"),
	DataType("v_data_type_suffix"),
	DataType(",",comma), 
	DataType("v_create_data_def")}

};
const GramType Grammatical::v_create_data_type_def{
	GramDataType{
	DataType("float",keyword),},

	GramDataType{
	DataType("int",keyword)
	},
	
	GramDataType{  //char(n)
	DataType("char",keyword),
	DataType("(",l_block),
	DataType("integer",integer),
	DataType(")",r_block)
	}

};
const  GramType Grammatical::v_create_data_type_suffx_def{

};