#ifndef _GrammaticalAnalysis_
#include"GrammaticalAnalysis.h"
#endif
const GramType Grammatical::v_start{
	//start s'->s $
	GramDataType{DataType("s"),DataType("$",eof)}
};
const GramType Grammatical::v_s{

	// s->v_create_def | v_select_def | v_create_database_def |v_use_database_def|
	// v_delete_element_def | v_delete_table_def |v_alter_table_add_column_def|
	// v_alter_table_drop_column_def | v_insert_def |v_update_def|v_crate_view|
	// v_drop_view | v_crate_index |v_drop_index
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
	//v_create_def-> crate table table_name ( v_create_data_def v_constraint_def)
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
	//v_create_data_def-> data_name v_create_data_type_def v_create_data_type_suffx_def {, v_create_data}    {}representative repeat
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
	//v_create_data_type_def->flaot|int|char(number) 
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
	// v_create_data_type_suffx_def-> ¦Å |not null     ¦Å representive  empty
	GramDataType{
	DataType("empty",GramCategory::empty)
	
	}
	,GramDataType{
	DataType("null",keyword)
}

};
const GramType Grammatical::v_constraint_def{
	//v_constraint_def -> [ v_primary_def ] {v_for_che_uni_def}   [] representive optional
	GramDataType{
	DataType("v_primary_def"),
	DataType("v_for_che_uni_def")
	},
	GramDataType{
	DataType("empty",GramCategory::empty)
	},
	GramDataType{
	DataType("v_primary_def")
	},
	GramDataType{
	DataType("v_")
	}
};