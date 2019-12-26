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

	/*
	v_s -> v_create_def
	v_s->v_select_def
	v_s->v_create_database_def
	v_s->v_use_database_def
	v_s->v_delete_element_def
	v_s->v_delete_table_def
	v_s->v_alter_table_add_column_def
	v_s->v_alter_table_drop_column_def
	v_s->v_insert_def
	v_s->v_update_def
	v_s->v_create_view_def
	v_s->v_drop_view_def
	v_s->v_create_index_def
	v_s->v_drop_index_def
	*/
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

	/*
	v_create_def -> create table table_name (v_create_data_def v_constraint_def)
	*/
	GramDataType{
	DataType("create",keyword),
	DataType("table",keyword),
	DataType("table_name",id),
	DataType("(",l_bracket),
	DataType("v_create_data_def"),
	DataType("v_constraint_def"),
	DataType(")",r_bracket)}
};
const GramType Grammatical::v_create_data_def{
	//v_create_data_def-> data_name v_create_data_type_def v_create_data_type_suffx_def {, v_create_data}    {}representative repeat

	/*
	v_create_data_def-> data_name v_create_data_type_def  v_create_type_suffix_def
	v_create_data_def->data_name v_create_datatype_def v_create_type_suffix_def
	*/
	GramDataType{
	DataType("data_name",id),
	DataType("v_data_type_def"),
	DataType("v_data_type_suffix_def"),},

	GramDataType{  //repeat
	DataType("data_name",id),
	DataType("v_data_type_def"),
	DataType("v_data_type_suffix_def"),
	DataType(",",comma), 
	DataType("v_create_data_def")}

};
const GramType Grammatical::v_create_data_type_def{
	//v_create_data_type_def->flaot|int|char(number) 
/*
	v_create_data_type_def->float
	v_create_data_type_def->int
	v_create_data_type_def->char(number)

*/
	GramDataType{
	DataType("float",keyword),},

	GramDataType{
	DataType("int",keyword)
	},
	
	GramDataType{  //char(n)
	DataType("char",keyword),
	DataType("(",l_bracket),
	DataType("integer",integer),
	DataType(")",r_bracket)
	}

};
const  GramType Grammatical::v_create_data_type_suffix_def{
	// v_create_data_type_suffx_def-> ¦Å |not null     ¦Å representive  empty

	/*
	v_create_data_type_suffix_def->¦Å
	v_create_data_type_suffix_def->not null
	*/
	GramDataType{
	DataType("empty",GramCategory::empty)
	
	}
	,GramDataType{
	DataType("not"),
	DataType("null",keyword)
}

};
const GramType Grammatical::v_constraint_def{
	//v_constraint_def -> [ v_primary_def ] {v_for_che_uni_def}   [] representive optional
	/*
	v_constraint_def -> v_primary_def
	v_constraint_def->v_for_che_uni_def
	v_constraint_def->¦Å
	v_constraint_def->v_primary_def for_che_uni_def
	*/
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
	DataType("v_for_che_uni_def")
	}
};
const GramType Grammatical::v_primary_def {
	/*
	
	v_primary_def ->primary key (col_name_rep_def)
	primary_def->¦Å
	*/
	GramDataType{
	DataType("primary",keyword),
	DataType("key",keyword),
	DataType("l_bracket",keyword),
	DataType("col_name_rep_def"),
	DataType("r_bracket",keyword)
},
GramDataType{
	DataType("empty",GramCategory::empty)
}

};
const GramType Grammatical::v_for_che_uni_def{
	/*
	v_for_che_uni_def->v_foreign_def v_for_che_uni_def
	v_for_che_uni_def->v_check_def v_for_che_uni_def
	v_for_che_uni_def->v_unique_def v_for_che_uni_def
	v_for_che_uni_def->¦Å
	*/
	GramDataType{
	DataType("v_foreign_def"),
	DataType("v_for_che_uni_def")

	},
	GramDataType{
	DataType("v_check_def"),
	DataType("v_for_che_uni_def")
	
	},
	GramDataType{
	DataType("v_unique_def"),
	DataType("v_for_che_uni_def")

		}
};
const GramType Grammatical::v_col_name_rep_def{

	/*
	v_col_name_rep_def -> col_name
	v_col_name_rep_def->col_name,v_col_name_rep_def
	*/
	GramDataType{
	DataType("col_name",id),
	DataType(",",comma),
	DataType("v_col_name_rep_def")
	},
	GramDataType{
	DataType("col_name",id)
	}
};
const GramType Grammatical::v_foreign_def{


	/*
	v_foreign_def->foreign key ( col_name_rep_def) references table_name ( col_name_rep_def)
	v_foreign_def->foreign key ( col_name_rep_def) references table_name ( col_name_rep_def),v_foreign_def
	*/
	GramDataType{
	DataType("foreign",keyword),
	DataType("key",keyword),
	DataType("l_bracket",l_bracket),
	DataType("v_col_name_rep_def"),
	DataType("r_bracket",r_bracket),
	DataType("references",keyword),
	DataType("table_name",id),
	DataType("l_bracket",l_bracket),
	DataType("v_col_name_rep_def"),
	DataType("r_bracket",r_bracket)
		},
	GramDataType{
	DataType("foreign",keyword),
	DataType("key",keyword),
	DataType("l_bracket",l_bracket),
	DataType("v_col_name_rep_def"),
	DataType("r_bracket",r_bracket),
	DataType("references",keyword),
	DataType("table_name",id),
	DataType("l_bracket",l_bracket),
	DataType("v_col_name_rep_def"),
	DataType("r_bracket",r_bracket),
	DataType(",",comma),
	DataType("v_foreign_def")
	}
};
const GramType Grammatical::v_str_rep_def{
	/*
	v_str_rep_def-> string
	v_str_rep_def->string , str_rep_def
	*/
	GramDataType{
	DataType("string",str)
	},
	GramDataType{
	DataType("string",str),
	DataType("v_str_rep_def")
	}
};
const GramType Grammatical::v_check_def{
	/*
	v_check_def->check ( col_name in (v_str_rep_def))
	v_check_def->check ( col_name in (v_str_rep_def)),v_check_def
	*/
	GramDataType{
	DataType("check",keyword),
	DataType("(",l_bracket),
	DataType("col_name",id),
	DataType("in",keyword),
	DataType("l_bracket",l_bracket),
	DataType("v_str_rep_def"),
	DataType("r_bracket",r_bracket),
	DataType("r_bracket",r_bracket)

	},
	GramDataType{
	DataType("check",keyword),
	DataType("(",l_bracket),
	DataType("col_name",id),
	DataType("in",keyword),
	DataType("l_bracket",l_bracket),
	DataType("v_str_rep_def"),
	DataType("r_bracket",r_bracket),
	DataType("r_bracket",r_bracket),
	DataType(",",comma),
	DataType("v_check_def")
	}
};
const GramType Grammatical::v_unique_def{
	/*
	v_unique_def->unique ( col_name_rep_def)
	v_unique_def->unique (col_name_erp_def),unique_def
	*/
	GramDataType{
	DataType("unique",keyword),
	DataType("l_bracket",l_bracket),
	DataType("v_col_name_rep_def"),
	DataType("r_bracket",r_bracket)
	},

	GramDataType{
	DataType("unique",keyword),
	DataType("l_bracket",l_bracket),
	DataType("v_col_name_rep_def"),
	DataType("r_bracket",r_bracket),
	DataType(",",comma),
	DataType("v_unique_def")
	}
};
const GramType Grammatical::v_addop_def{
	/*
	v_addop_def->+
	v_addop_def->-
	*/
	GramDataType{
	DataType("+",addop)
	},
	GramDataType{
	DataType("-",addop)
	}
	
};

const GramType Grammatical::v_mulop_def{
	/*
	v_mulop_def->/
	v_mulop_def->*
	*/
	GramDataType{
	DataType("*",mulop),
	DataType("/",mulop)
	}
};

