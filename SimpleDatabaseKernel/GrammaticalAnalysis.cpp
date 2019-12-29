#ifndef _GrammaticalAnalysis_
#include"GrammaticalAnalysis.h"
#endif
const GramType Grammatical::v_start{
	//start s'->s $
	GramDataType{DataType(e_s),DataType(e_eof)}
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
	GramDataType{DataType(e_create_def)},
	//GramDataType{DataType(e_select_def)},
	//GramDataType{DataType("v_create_database_def")},
	//GramDataType{DataType("v_use_database_def")},
	//GramDataType{DataType("v_delete_element_def")},
	//GramDataType{DataType("v_delete_table_def")},
	//GramDataType{DataType("v_alter_table_add_column_def")},
	//GramDataType{DataType("v_alter_table_drop_column_def")},
	//GramDataType{DataType("v_insert_def")},
	//GramDataType{DataType("v_update_def")},
	//GramDataType{DataType("v_create_view_def")},
	//GramDataType{DataType("v_drop_view_def")},
	//GramDataType{DataType("v_create_index_def")},
	//GramDataType{DataType("v_drop_index_def")}
};
const GramType Grammatical::v_create_def{
	//v_create_def-> crate table table_name ( v_create_data_def v_constraint_def)

	/*
	v_create_def -> create table table_name (v_create_data_def v_constraint_def)
	*/
	GramDataType{
	DataType(e_create),
	DataType(e_table),
	DataType(e_id),
	DataType(e_l_bracket),
	DataType( e_create_data_def),
	DataType(e_constraint_def),
	DataType(e_r_bracket)}
};
const GramType Grammatical::v_create_data_def{
	//v_create_data_def-> data_name v_create_data_type_def v_create_data_type_suffx_def {, v_create_data}    {}representative repeat

	/*
	v_create_data_def-> data_name v_create_data_type_def  v_create_type_suffix_def
	v_create_data_def->data_name v_create_datatype_def v_create_type_suffix_def
	*/
	GramDataType{
	DataType(e_id),
	DataType(e_create_data_type_def),
	DataType(e_create_data_type_suffix_def),},

	GramDataType{  //repeat
	DataType(e_id),
	DataType(e_create_data_type_def),
	DataType(e_create_data_type_suffix_def),
	DataType(e_comma), 
	DataType( e_create_data_def)}

};
const GramType Grammatical::v_create_data_type_def{
	//v_create_data_type_def->flaot|int|char(number) 
/*
	v_create_data_type_def->float
	v_create_data_type_def->int
	v_create_data_type_def->char(number)

*/
	GramDataType{
	DataType(e_real),},

	GramDataType{
	DataType(e_integer)
	},
	
	GramDataType{  //char(n)
	DataType(e_char),
	DataType(e_l_bracket),
	DataType(e_integer),
	DataType(e_r_bracket)
	}

};
const  GramType Grammatical::v_create_data_type_suffix_def{
	// v_create_data_type_suffx_def-> ¦Å |not null     ¦Å representive  empty

	/*
	v_create_data_type_suffix_def->¦Å
	v_create_data_type_suffix_def->not null
	*/
	GramDataType{
	DataType(GramCategory::e_empty)
	
	}
	,GramDataType{
	DataType(e_not),
	DataType(e_null)
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
	DataType(e_primary_def),
	DataType(e_for_che_uni_def)
	},
	GramDataType{
	DataType(GramCategory::e_empty)
	},
	GramDataType{
	DataType(e_primary_def)
	},
	GramDataType{
	DataType(e_for_che_uni_def)
	}
};
const GramType Grammatical::v_primary_def {
	/*
	
	v_primary_def ->primary key (col_name_rep_def)
	primary_def->¦Å
	*/
	GramDataType{
	DataType(e_primary),
	DataType(e_key),
	DataType(e_l_bracket),
	DataType(e_col_name_rep_def),
	DataType(e_r_bracket)
},
GramDataType{
	DataType(GramCategory::e_empty)
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
	DataType(e_foreign_def),
	DataType(e_for_che_uni_def)

	},
	GramDataType{
	DataType(e_check_def),
	DataType(e_for_che_uni_def)
	
	},
	GramDataType{
	DataType(e_unique_def),
	DataType(e_for_che_uni_def)

		}
};
const GramType Grammatical::v_col_name_rep_def{

	/*
	v_col_name_rep_def -> col_name
	v_col_name_rep_def->col_name,v_col_name_rep_def
	*/
	GramDataType{
	DataType(e_id),
	DataType(e_comma),
	DataType(e_col_name_rep_def)
	},
	GramDataType{
	DataType(e_id)
	}
};
const GramType Grammatical::v_foreign_def{


	/*
	v_foreign_def->foreign key ( col_name_rep_def) references table_name ( col_name_rep_def)
	v_foreign_def->foreign key ( col_name_rep_def) references table_name ( col_name_rep_def),v_foreign_def
	*/
	GramDataType{
	DataType(e_foreign),
	DataType(e_key),
	DataType(e_l_bracket),
	DataType(e_col_name_rep_def),
	DataType(e_r_bracket),
	DataType(e_references),
	DataType(e_id),
	DataType(e_l_bracket),
	DataType(e_col_name_rep_def),
	DataType(e_r_bracket)
		},
	GramDataType{
	DataType(e_foreign),
	DataType(e_key),
	DataType(e_l_bracket),
	DataType(e_col_name_rep_def),
	DataType(e_r_bracket),
	DataType(e_references),
	DataType(e_id),
	DataType(e_l_bracket),
	DataType(e_col_name_rep_def),
	DataType(e_r_bracket),
	DataType(e_comma),
	DataType(e_foreign_def)
	}
};
const GramType Grammatical::v_str_rep_def{
	/*
	v_str_rep_def-> string
	v_str_rep_def->string , str_rep_def
	*/
	GramDataType{
	DataType(e_str)
	},
	GramDataType{
	DataType(e_str),
	DataType(e_str_rep_def)
	}
};
const GramType Grammatical::v_check_def{
	/*
	v_check_def->check ( col_name in (v_str_rep_def))
	v_check_def->check ( col_name in (v_str_rep_def)),v_check_def
	*/
	GramDataType{
	DataType(e_check),
	DataType(e_l_bracket),
	DataType(e_id),
	DataType(e_in),
	DataType(e_l_bracket),
	DataType(e_str_rep_def),
	DataType(e_r_bracket),
	DataType(e_r_bracket)

	},
	GramDataType{
	DataType(e_check),
	DataType(e_l_bracket),
	DataType(e_id),
	DataType(e_in),
	DataType(e_l_bracket),
	DataType(e_str_rep_def),
	DataType(e_r_bracket),
	DataType(e_r_bracket),
	DataType(e_comma),
	DataType(e_check_def)
	}
};
const GramType Grammatical::v_unique_def{
	/*
	v_unique_def->unique ( col_name_rep_def)
	v_unique_def->unique (col_name_erp_def),unique_def
	*/
	GramDataType{
	DataType(e_unique),
	DataType(e_l_bracket),
	DataType(e_col_name_rep_def),
	DataType(e_r_bracket)
	},

	GramDataType{
	DataType(e_unique),
	DataType(e_l_bracket),
	DataType(e_col_name_rep_def),
	DataType(e_r_bracket),
	DataType(e_comma),
	DataType(e_unique_def)
	}
};
const GramType Grammatical::v_addop_def{
	/*
	v_addop_def->+
	v_addop_def->-
	*/
	GramDataType{
	DataType(e_addop)
	},
	GramDataType{
	DataType(e_subop)
	}
	
};

const GramType Grammatical::v_mulop_def{
	/*
	v_mulop_def->/
	v_mulop_def->*
	*/
	GramDataType{
	DataType(e_mulop),
	DataType(e_divop)
	}
};
const GramType Grammatical::v_compare_def{
	/*
	v_compare_def-> >
	v_compare_def-> >=
	v_compare_def-> <
	v_compare_def-> <=
	v_compare_def-> <>
	v_compare_def-> =
	*/
	GramDataType{
	DataType(e_greater_than)
	},
	GramDataType{
	DataType(e_greater_than_or_equal)
},
GramDataType{
	DataType(e_less_than)
},
GramDataType{
	DataType(e_less_than_or_equal)
},
GramDataType{
	DataType(e_unequal)
},
GramDataType{
	DataType(e_equal)
}
};
const GramType Grammatical::v_logic_def{
	/*
	v_logic_def->and
	v_logic_def->or
	v_logic_def->not
	*/
	GramDataType{
	DataType(e_and)
	},
	GramDataType{
	DataType(e_or)
},
GramDataType{
	DataType(e_not)
}
};
const GramType Grammatical::v_gather_fuc_def{
	/*
	v_gather_fuc_def->sum
	v_gather_fuc_def->avg
	v_gather_fuc_def->count
	v_gather_fuc_def->min
	v_gather_fuc_def->max
	*/
	GramDataType{
	DataType(e_sum)
	},
	GramDataType{
	DataType(e_sub)
},
GramDataType{
	DataType(e_count)
},
GramDataType{
	DataType(e_min)
},
GramDataType{
	DataType(e_max)
}
};
const GramType Grammatical::v_int_real_col_name_def{
	/*
	v_int_real_col_name_def -> int
	v_int_real_col_name_def->flaot
	v_int_real_col_name->col_name
	*/
	GramDataType{
	DataType(e_integer)
	},
	GramDataType{
	DataType(e_real)
	},
	GramDataType{
	DataType(e_id)
	}
};
const GramType Grammatical::v_int_real_col_name_rep_def{
	/*
	v_int_real_col_name_rep_def ->v_int_real_col_name_def,v_int_rel_col_name_rep_def
	v_int_real_col_name_rep_def->v_int_real_col_name_def
	*/
	GramDataType{
	DataType(e_int_real_col_name_def),
	DataType(e_comma),
	DataType(e_int_real_col_name_rep_def)
	},
	GramDataType{
	DataType(e_int_real_col_name_def)
	}
};
const  GramType Grammatical::v_where_addop_def{
	/*
	v_where_addop_def->addop (v_int_real_col_name_def v_where_mulop_def)
	v_where_addop_def->addop v_gather_fuc_def ( v_int_real_col_name_def v_where_mulop_def)
	v_where_addop_def->addop v_gather_fuc_def(  v_where_algorithm_operator_def)
	v_where_addop_def->addop v_int_real_col_name_def v_where_mulop_def
	v_where_addop_def->¦Å
	v_where_addop_def->addop ( v_where_algorithm_operator_def )
	v_where_addop_def->addop v_int_real_col_name_def v_where_mulop_def
	*/
	GramDataType{
	DataType(e_addop_def),
	DataType(e_l_bracket),
	DataType(e_int_real_col_name_def),
	DataType(e_where_mulop_def),
	DataType(e_r_bracket)
	},
GramDataType{
	DataType(e_addop_def),
	DataType(e_gather_fuc_def),
	DataType(e_l_bracket),
	DataType(e_int_real_col_name_def),
	DataType(e_where_mulop_def),
	DataType(e_r_bracket)
	},
	GramDataType{
	DataType(e_addop_def),
	DataType(e_gather_fuc_def),
	DataType(e_l_bracket),
	DataType(e_where_algorithm_operator_def),
	DataType(e_r_bracket)
	},

	GramDataType{
	DataType(e_addop_def),
	DataType(e_int_real_col_name_def),
	DataType(e_where_mulop_def),
	},
	GramDataType{
	DataType(GramCategory::e_empty)
	},

	GramDataType {
	DataType(e_addop_def),
	DataType(e_l_bracket),
	DataType(e_where_algorithm_operator_def),
	DataType(e_r_bracket)
	},
	GramDataType{
	DataType(e_addop_def),
	DataType(e_int_real_col_name_def),
	DataType(e_where_mulop_def),
	}
};
const GramType Grammatical::v_where_mulop_def{
	/*
	v_where_mulop_def-> mulop ( v_int_real_col_name v_where_addop_def)
	v_where_mulop_def->mulop v_gather_fuc_def ( v_int_real_col_name v_where_addop_def)
	v_where_mulop_def->mulop v_gather_fuc_def ( v_where_algorithm_operator_def )
	v_where_mulop_def->mulop v_int_real_col_name_def v_where_addop_def
	v_where_mulop_def->¦Å
	v_where_mulop_def->mulop ( v_where_alogrithm_operator_def)
	v_where_mulip_def->mulop v_int_real_col_name_def v_where_addop_def
	*/


	GramDataType{
	DataType(e_mulop_def),
	DataType(e_l_bracket),
	DataType(e_int_real_col_name_def),
	DataType(e_where_addop_def),
	DataType(e_r_bracket)
},
GramDataType{
	DataType(e_mulop_def),
	DataType(e_gather_fuc_def),
	DataType(e_l_bracket),
	DataType(e_int_real_col_name_def),
	DataType(e_where_addop_def),
	DataType(e_r_bracket)
},
GramDataType{
	DataType(e_mulop_def),
	DataType(e_gather_fuc_def),
	DataType(e_l_bracket),
	DataType(e_where_algorithm_operator_def),
	DataType(e_r_bracket)
},

GramDataType{
	DataType(e_mulop_def),
	DataType(e_int_real_col_name_def),
	DataType(e_where_addop_def),
},
GramDataType{
	DataType(GramCategory::e_empty)
},

GramDataType{
	DataType(e_mulop_def),
	DataType(e_l_bracket),
	DataType(e_where_algorithm_operator_def),
	DataType(e_r_bracket)
},
GramDataType{
	DataType(e_mulop_def),
	DataType(e_int_real_col_name_def),
	DataType(e_where_addop_def),
}

};

const GramType Grammatical::v_where_algorithm_operator_def{

	/*
	v_where_algorithm_opeartor_def->v_gather_fuc_def ( v_int_real_col_name_def v_where_addop_def)
	v_where_algorithm_opeartor_def->( v_int_real_col_name_def v_where_addop_def)
	v_where_algorithm_operator_def->v_gather_def ( v_where_algorithm_operator_def)
	v_where_algorithm_operator_def->( v_where_algorithm_operator_def )
	v_where_algorithm_operator_def->v_int_real_col_name_def v_where_addop_def
	*/
	GramDataType{
	
	DataType(e_gather_fuc_def),
	DataType(e_l_bracket),
	DataType(e_int_real_col_name_def),
	DataType(e_where_addop_def),
	DataType(e_r_bracket)
	},
	GramDataType{
	DataType(e_l_bracket),
	DataType(e_int_real_col_name_def),
	DataType(e_where_addop_def),
	DataType(e_r_bracket)
	},
	GramDataType{

	DataType(e_gather_fuc_def),
	DataType(e_l_bracket),
	DataType(e_where_algorithm_operator_def),
	DataType(e_r_bracket)
	},
	GramDataType{

	DataType(e_l_bracket),
	DataType(e_where_algorithm_operator_def),
	DataType(e_r_bracket)
	},

	GramDataType{

	DataType(e_int_real_col_name_def),
	DataType(e_where_addop_def),
	}
};
const  GramType Grammatical::v_where_algorithm_operator_or_string_def{
	/*
	v_where_algorithm_operator_or_string_def->v_where_algorithm_opeartor_def
	v_where_algorithm_operator_or_string_def->string
	*/

	GramDataType{
	DataType(e_where_algorithm_operator_def)
	},
	GramDataType{
	DataType(e_str)
	},


};
const GramType Grammatical::v_where_compare_def{
	/*
	v_where_compare_def->v_where_algorithm_operator_or_string_def compare v_where_algorithm_operator_or_string_def
	*/
	GramDataType{
	DataType(e_where_algorithm_operator_or_string_def),
	DataType(e_compare),
	DataType(e_where_algorithm_operator_or_string_def)
	}
};
const GramType Grammatical::v_where_compare_or_string_match_def{
	/*
	v_where_compare_or_string_match_def-> v_where_compare_def
	v_where_compare_or_string_match_def-> col_name like string_match
	*/
	GramDataType{
	DataType(e_where_compare_def)
	},
	GramDataType{
	DataType(e_id),
	DataType(e_like),
	DataType(e_strMatch)
	}

};
const GramType Grammatical::v_logic_and_where_compare_string_match_def{
	/*
	v_logic_and_where_compare_compare
	*/
};