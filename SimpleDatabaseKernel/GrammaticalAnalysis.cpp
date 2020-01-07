#ifndef _GrammaticalAnalysis_
#include"GrammaticalAnalysis.h"
#endif
#define CLOSURE_FUNC true
#define GOTO_FUNC true
#define ITEMS_FUNC true
#define GET_DERIVED_GRAMMAR true
 GramType Grammatical::v_start{
	//start s'->s $
	GramDataType{
	DataType(e_s),
	DataType(e_eof),
	}
};
 GramType Grammatical::v_s{

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
	GramDataType{DataType(e_select_def)},
	GramDataType{DataType( e_create_database_def)},
	GramDataType{DataType( e_use_database_def)},
	GramDataType{DataType( e_delete_element_def)},
	GramDataType{DataType(e_delete_table_def)},
	GramDataType{DataType(e_alter_table_add_col_name_def)},
	GramDataType{DataType( e_alter_table_drop_col_name_def)},
	GramDataType{DataType( e_insert_def)},
	GramDataType{DataType(e_update_def)},
	GramDataType{DataType(e_create_view_def)},
	GramDataType{DataType( e_drop_view_def)},
	GramDataType{DataType(e_create_index_def)},
	GramDataType{DataType( e_drop_index_def)}
};
 GramType Grammatical::v_create_def{
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
 GramType Grammatical::v_create_data_def{
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
 GramType Grammatical::v_create_data_type_def{
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
  GramType Grammatical::v_create_data_type_suffix_def{
	// v_create_data_type_suffx_def-> ε |not null     ε representive  empty

	/*
	v_create_data_type_suffix_def->ε
	v_create_data_type_suffix_def->not null
	*/
	GramDataType{
	DataType(Gram::e_empty)
	
	}
	,GramDataType{
	DataType(e_not),
	DataType(e_null)
}

};
 GramType Grammatical::v_constraint_def{
	//v_constraint_def -> [ v_primary_def ] {v_for_che_uni_def}   [] representive optional
	/*
	v_constraint_def -> v_primary_def
	v_constraint_def->v_for_che_uni_def
	v_constraint_def->ε
	v_constraint_def->v_primary_def for_che_uni_def
	*/
	GramDataType{
	DataType(e_primary_def),
	DataType(e_for_che_uni_def)
	},
	GramDataType{
	DataType(Gram::e_empty)
	},
	GramDataType{
	DataType(e_primary_def)
	},
	GramDataType{
	DataType(e_for_che_uni_def)
	}
};
 GramType Grammatical::v_primary_def {
	/*
	
	v_primary_def ->primary key (col_name_rep_def)
	primary_def->ε
	*/
	GramDataType{
	DataType(e_primary),
	DataType(e_key),
	DataType(e_l_bracket),
	DataType(e_col_name_rep_def),
	DataType(e_r_bracket)
},
GramDataType{
	DataType(Gram::e_empty)
}

};
 GramType Grammatical::v_for_che_uni_def{
	/*
	v_for_che_uni_def->v_foreign_def v_for_che_uni_def
	v_for_che_uni_def->v_check_def v_for_che_uni_def
	v_for_che_uni_def->v_unique_def v_for_che_uni_def
	v_for_che_uni_def->ε
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

		},
	GramDataType{
	DataType(e_empty)
	}
};
 GramType Grammatical::v_col_name_rep_def{

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
 GramType Grammatical::v_foreign_def{


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
 GramType Grammatical::v_str_rep_def{
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
 GramType Grammatical::v_check_def{
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
 GramType Grammatical::v_unique_def{
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
 GramType Grammatical::v_addop_def{
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

 GramType Grammatical::v_mulop_def{
	/*
	v_mulop_def->/
	v_mulop_def->*
	*/
	GramDataType{
	DataType(e_mulop),
	DataType(e_divop)
	}
};
 GramType Grammatical::v_compare_def{
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
 GramType Grammatical::v_logic_def{
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
 GramType Grammatical::v_gather_fuc_def{
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
	DataType(e_avg)
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
 GramType Grammatical::v_int_real_col_name_def{
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
 GramType Grammatical::v_int_real_col_name_rep_def{
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
  GramType Grammatical::v_where_addop_def{
	/*
	v_where_addop_def->addop (v_int_real_col_name_def v_where_mulop_def)
	v_where_addop_def->addop v_gather_fuc_def ( v_int_real_col_name_def v_where_mulop_def)
	v_where_addop_def->addop v_gather_fuc_def(  v_where_algorithm_operator_def)
	v_where_addop_def->addop v_int_real_col_name_def v_where_mulop_def
	v_where_addop_def->ε
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
	DataType(Gram::e_empty)
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
 GramType Grammatical::v_where_mulop_def{
	/*
	v_where_mulop_def-> mulop ( v_int_real_col_name v_where_addop_def)
	v_where_mulop_def->mulop v_gather_fuc_def ( v_int_real_col_name v_where_addop_def)
	v_where_mulop_def->mulop v_gather_fuc_def ( v_where_algorithm_operator_def )
	v_where_mulop_def->mulop v_int_real_col_name_def v_where_addop_def
	v_where_mulop_def->ε
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
	DataType(Gram::e_empty)
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

 GramType Grammatical::v_where_algorithm_operator_def{

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
  GramType Grammatical::v_where_algorithm_operator_or_string_def{
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
 GramType Grammatical::v_where_compare_def{
	/*
	v_where_compare_def->v_where_algorithm_operator_or_string_def compare v_where_algorithm_operator_or_string_def
	*/
	GramDataType{
	DataType(e_where_algorithm_operator_or_string_def),
	DataType(e_compare_def),
	DataType(e_where_algorithm_operator_or_string_def)
	}
};
 GramType Grammatical::v_where_compare_or_string_match_def{
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
 GramType Grammatical::v_logic_and_where_compare_string_match_def{
	/*
	v_logic_and_where_compare_string_match_def->logic v_where_compare_or_string_match_def
	v_logic_and_where_compare_string_match_def->logic v_where_compare_or_string_match_def v_logic_and_where_compare_string_match_def
	v_logic_and_where_compare_string_match_def->logic ( v_where_compare_or_string_match_def logic_and_where_compare_string_match_def)
	v_logic_and_where_compare_string_match_def->ε
	*/
	GramDataType{
	DataType(e_logic_def),
	DataType(e_where_compare_or_string_match_def),
	},
	GramDataType{
	DataType(e_logic_def),
	DataType(e_where_compare_or_string_match_def),
	DataType(e_logic_and_where_compare_string_match_def)
},
GramDataType{
	DataType(e_logic_def),
	DataType(e_l_bracket),
	DataType(e_where_compare_or_string_match_def),
	DataType(e_logic_and_where_compare_string_match_def),
	DataType(e_r_bracket)
	},
	GramDataType{
	DataType(e_empty)
	}
};
 GramType Grammatical::v_where_logic_def{
	/*
	v_where_logic_def->v_where_compare_or_string_match_def logic_and_where_compare_string_match_def
	v_where_logic_def->( v_where_compare_or_string_match_def v_logic_and_where_compare_string_match_def)

	*/

	GramDataType{
	DataType(e_where_compare_or_string_match_def),
	DataType(e_logic_and_where_compare_string_match_def)
	},
	
	GramDataType{
	DataType(e_l_bracket),
	DataType(e_where_compare_or_string_match_def),
	DataType(e_logic_and_where_compare_string_match_def),
	DataType(e_r_bracket)
	},

};
 GramType Grammatical::v_where_def{
	/*
	v_where_def->where v_where_logic_def
	*/
	GramDataType{
	DataType(e_where),
	DataType(e_where_logic_def)
	}
};
 GramType Grammatical::v_comma_and_col_name_def{
	/*
	v_comma_and_col_name_def->, col_name comma_and_name_def
	v_comma_and_col_name_def->ε
	*/
	GramDataType{
	DataType(e_comma),
	DataType(e_id),
	DataType(e_comma_and_col_name_def)
	},
	GramDataType{
	DataType(e_empty)
	}
};
 GramType Grammatical::v_order_def{
	/*
	v_order_def->order by col_name
	v_order_def->order by col_name comma_and_col_name_def
	v_order_def->order by col_name desc
	v_order_def->order by col_name asc
	v_order_def->order by col_name comma_and_col_name_def desc
	v_order_def->order by col_name comma_and_col_name_def asc
	
	*/

	GramDataType{
	DataType(e_order),
	DataType(e_by),
	DataType(e_id)
	},
	GramDataType{
	DataType(e_order),
	DataType(e_by),
	DataType(e_id),
	DataType(e_comma_and_col_name_def)
	},
	GramDataType{
	DataType(e_order),
	DataType(e_by),
	DataType(e_id),
	DataType(e_desc)
	},
	GramDataType{
	DataType(e_order),
	DataType(e_by),
	DataType(e_id),
	DataType(e_asc)
	},

	GramDataType{
	DataType(e_order),
	DataType(e_by),
	DataType(e_id),
	DataType(e_comma_and_col_name_def),
	DataType(e_desc)
	},
	GramDataType{
	DataType(e_order),
	DataType(e_by),
	DataType(e_id),
	DataType(e_comma_and_col_name_def),
	DataType(e_asc)
	},
};
  GramType Grammatical::v_group_def{
	/*
	v_group_def->group by col_name
	v_group_def->group by col_name v_comma_and_col_name_def
	
	*/
	GramDataType{
	DataType(e_group),
	DataType(e_by),
	DataType(e_id)
	},
	GramDataType{
	DataType(e_group),
	DataType(e_by),
	DataType(e_id),
	DataType(e_comma_and_col_name_def)
	}

};
 GramType Grammatical:: v_having_def{

	/*
	v_having_def-> having v_where_logic_def
	
	*/
	GramDataType{
	DataType(e_having),
	DataType(e_where_logic_def)
}
};
 GramType Grammatical::v_where_algorithm_operator_rep_def{
	/*
	v_where_algorithm_operator_rep_def->, v_where_algorithm_operator_def v_where_algorithm_operator_rep_def
	v_where_algorithm_operator_rep_def->ε
	*/
	GramDataType{
	DataType(e_comma),
	DataType(e_where_algorithm_operator_def),
	DataType(e_where_algorithm_operator_rep_def)
	},
	GramDataType{
	DataType(e_empty)
	}
};
 GramType Grammatical::v_select_operator_def{
	/*
	v_select_operator_def-> v_where_algorithm_operator_def v_where_algorithm_operator_rep_def
	*/
	GramDataType{
	DataType(e_where_algorithm_operator_def),
	DataType(e_where_algorithm_operator_rep_def)
	}
};
 GramType Grammatical::v_connect_mode_def{
	/*
	v_connect_mode_def->right
	v_connect_mode_def->left
	v_connect_mode_def->full
	v_connect_mode_def->v_connect_mode_def join table_name on v_connect_logic_def
	*/
	GramDataType{
	DataType(e_right)
	},
	GramDataType{
	DataType(e_left)
},
GramDataType{
	DataType(e_full)
}

};
 GramType Grammatical::v_connect_def{
	GramDataType{
	DataType(e_connect_mode_def),
	DataType(e_join),
	DataType(e_id),
	DataType(e_on),
	DataType(e_connect_logic_def)
}
};
 GramType Grammatical::v_connect_addop_def{
	/*
	v_connect_addop_def->addop v_int_real_col_name v_connect_mulop_def
	v_connect_addop_def->v_connect_mulop_def
	v_connect_addop_def->addop ( v_int_real_col_name v_connect_mulop_def )
	v_conenct_addop_def->ε
	*/
	GramDataType{
	DataType(e_addop),
	DataType(e_int_real_col_name_def),
	DataType(e_connect_mulop_def),
	},
	GramDataType{
	DataType(e_connect_mulop_def)
	},
	GramDataType{
	DataType(e_addop),
	DataType(e_l_bracket),
	DataType(e_int_real_col_name_def),
	DataType(e_connect_mulop_def),
	DataType(e_r_bracket)
	},
	GramDataType{
	DataType(e_empty)
	}
};
 GramType Grammatical::v_connect_mulop_def{
	/*
	v_connect_mulop_def->mulop v_int_real_col_name_def
	v_connect_mulop_def->v_connect_addop
	v_connect_mulop_def->mulop ( v_int_real_col_name_def )
	v_connect_mulop_def -> ε
	*/
	GramDataType{
	DataType(e_mulop),
	DataType(e_int_real_col_name_def)
	},
	GramDataType{
	DataType(e_connect_addop_def)
	},
	GramDataType{
	DataType(e_mulop),
	DataType(e_l_bracket),
	DataType(e_int_real_col_name_def),
	DataType(e_r_bracket),
	},
	GramDataType{
	DataType(e_empty)
	}
};
 GramType Grammatical::v_connect_algorithm_operator_def{
	/*
	v_connect_algorithm_operator_def->( v_int_real_col_name_def v_connect_addop_def )
	v_connect_algorithm_operator_def->v_int_real_col_name_def v_connect_addop_def
	*/
	GramDataType{
	DataType(e_l_bracket),
	DataType(e_int_real_col_name_def),
	DataType(e_connect_addop_def),
	DataType(e_r_bracket)
	},
	GramDataType{
	DataType(e_int_real_col_name_def),
	DataType(e_connect_addop_def)
}
};
 GramType Grammatical::v_connect_algorithm_operator_or_string_def{
	/*
	v_connect_algorithm_operator_or_string_def->v_connect_algorithm_operator_def
	v_connect_algorithm_operator_or_string_def->string
	
	*/
	GramDataType{
	DataType(e_connect_algorithm_operator_def)
	},
	GramDataType{
	DataType(e_str)
	},
	
};
 GramType Grammatical::v_connect_compare_def{
	/*
	v_connect_compare_def->v_connect_algorithm_operator_or_string compare v_connect_algorithm_operator_or_string 
	*/
	GramDataType{
	DataType(e_connect_algorithm_operator_or_string_def),
	DataType(e_compare_def),
	DataType(e_connect_algorithm_operator_or_string_def)
	}
};
 GramType Grammatical::v_connect_compare_or_str_match_def{
	/*
	v_connect_compare_or_str_match_def->v_connect_compare_def
	v_connect_compare_or_str_match_def->col_name like string_match
	*/
	GramDataType{
	DataType(e_connect_compare_def)
	},
	GramDataType{
	DataType(e_id),
	DataType(e_like),
	DataType(e_strMatch)
}
};
 GramType Grammatical::v_logic_connect_compare_or_str_match_def{
	/*
	v_logic_connect_compare_or_str_match_def->logic v_connect_compare_or_str_match_def v_logic_connect_compare_or_str_match_def
	v_logic_connect_compare_or_str_match_def->ε
	*/
	GramDataType{
	DataType(e_logic_def),
	DataType(e_connect_compare_or_str_match_def),
	DataType(e_logic_connect_compare_or_str_match_def),
	},
	GramDataType{
	DataType(e_empty)
	}
};
 GramType Grammatical::v_connect_logic_def{
	/*
	v_connect_logic_def->v_connect_compare_or_str_match_def v_logic_connect_compare_or_str_match_def
	v_connect_logic_def->(v_connect_compare_or_str_match_def v_logic_connect_compare_or_str_match_def)
	*/
	GramDataType{
	DataType(e_connect_compare_or_str_match_def),
	DataType(e_logic_connect_compare_or_str_match_def)
	},
	GramDataType{
	DataType(e_l_bracket),
	DataType(e_connect_compare_or_str_match_def),
	DataType(e_logic_connect_compare_or_str_match_def),
	DataType(e_r_bracket)
	}
};
 GramType Grammatical::v_constriant_having_def{
	/*
	v_constriant_having_def->v_having_def
	v_constriant_having_def->v_having_def v_order_def
	v_constriant_having_def->ε
	*/
	GramDataType{
	DataType(e_having_def)
	},
	GramDataType{
	DataType(e_having_def),
	DataType(e_order_def)
	},
	GramDataType{
	DataType(e_empty)
	}
};
 GramType Grammatical::v_constraint_group_def{
	/*
	v_constraint_group_def->v_group_def
	v_constraint_group_def->v_group_def v_constriant_having_def
	v_constraint_group_def->v_constriant_having_def
	
	*/
	GramDataType{
	DataType(e_group_def)
	},
	GramDataType{
	DataType(e_group_def),
	DataType(e_constraint_having_def)
	},
	GramDataType{
	DataType(e_constraint_having_def)}
};
 GramType Grammatical::v_select_connect_def{
	/*
	v_select_connect_def->*
	v_select_connect_def->v_select_operator_def
	*/
	GramDataType{
	DataType(e_mulop)
	},
	GramDataType{
	DataType(e_select_operator_def)
	}
};
 GramType Grammatical::v_constriant_connect_def{
	/*
	v_constriant_connect_def->v_connect_def
	v_constriant_connect_def->v_connect_def v_constriant_where_def
	*/
	GramDataType{
	DataType(e_connect_def)
	},
	GramDataType{
	DataType(e_connect_def),
	DataType(e_where_def)
	}
};
 GramType Grammatical::v_table_name_def{
	/*
	v_table_name_def-> table_name,v_table_name_def
	v_table_name_def->table_name
	*/
	GramDataType{
	DataType(e_id),
	DataType(e_comma),
	DataType(e_table_name_def)
	},
	GramDataType{
	DataType(e_id)
	}
};
 GramType Grammatical::v_select_def{
	/*
	v_select_def-> distance v_select_connect_def from v_table_name_def v_constriant_connect_def
	v_select_def->v_select_connect_def from v_table_name_def v_constriant_connect_def
	v_select_def->v_select_connect_def from v_table_name_def v_where_def
	*/
	GramDataType{
	DataType(e_distance),
	DataType(e_select_connect_def),
	DataType(e_from),
	DataType(e_table_name_def),
	DataType(e_constriant_connect_def)
	},
	GramDataType{
	DataType(e_select_connect_def),
	DataType(e_from),
	DataType(e_table_name_def),
	DataType(e_constriant_connect_def)
	},

	GramDataType{
	DataType(e_select_connect_def),
	DataType(e_from),
	DataType(e_table_name_def),
	DataType(e_where_def)
	},

	GramDataType{
	DataType(e_distance),
	DataType(e_select_connect_def),
	DataType(e_from),
	DataType(e_table_name_def),
	DataType(e_where_def)
		}
};
 GramType Grammatical::v_create_database_def{
	/*
	v_create_database_def-> create database database_name
	v_create_database_def->use database_name
	*/
	GramDataType{
	DataType(e_create),
	DataType(e_database),
	DataType(e_id),
	},

};
 GramType Grammatical::v_use_database_def{
	GramDataType{
	DataType(e_use),
	DataType(e_id),
}

};
 GramType Grammatical::v_delete_element_def{
	/*
	v_delete_element_def->delete from table_name
	v_delete_table_def-> delete table table_name
	*/
	GramDataType{
	DataType(e_delete),
	DataType(e_from),
	DataType(e_id),
	}
	
};
 GramType Grammatical::v_delete_table_def{
	GramDataType{
	DataType(e_delete),
	DataType(e_table),
	DataType(e_id),
}
};
 GramType Grammatical::v_alter_table_col_name_def{
	/*
	v_alter_table_col_name_def -> alter table table_name add column col_name v_int_real_col_name
	v_alter_table_drop_col_name_def->alter table table_name drop col_name
	*/
	GramDataType{
	DataType(e_alter),
	DataType(e_table),
	DataType(e_id),
	DataType(e_add),
	DataType(e_column),
	DataType(e_id),
	DataType(e_int_real_col_name_def)
	}
	
};
 GramType Grammatical::v_alter_table_drop_col_name_def{
	GramDataType{
	DataType(e_alter),
	DataType(e_table),
	DataType(e_id),
	DataType(e_drop),
	DataType(e_id)
}
};
 GramType Grammatical::v_insert_def{
	/*
	v_insert_def->insert into table_name ( v_col_name_rep_def ) values ( v_int_real_col_name_rep_def)
	*/
	GramDataType{
	DataType(e_insert),
	DataType(e_into),
	DataType(e_id),

	DataType(e_l_bracket),
	DataType(e_col_name_rep_def),
	DataType(e_r_bracket),

	DataType(e_values),

	DataType(e_l_bracket),
	DataType(e_int_real_col_name_rep_def),
	DataType(e_r_bracket)
	}
};
 GramType Grammatical::v_update_addop_def{
	/*
	v_update_addop_def-> addop ( v_int_real_col_name_def v_update_mulop_def)
	v_update_addop_def-> addop v_int_real_col_name_def v_update_mulop_def

	v_update_addop_def->ε
	v_update_addop_def->v_update_mulop_def
	*/
	GramDataType{
	DataType(e_addop),
	DataType(e_l_bracket),
	DataType(e_int_real_col_name_def),
	DataType(e_update_mulop_def),
	DataType(e_r_bracket),
	},

	GramDataType{
	DataType(e_addop),
	DataType(e_int_real_col_name_def),
	DataType(e_update_mulop_def),
	},
	GramDataType{
	DataType(e_empty)
	},
	GramDataType{
	DataType(e_update_mulop_def)
	}
};

  GramType Grammatical::v_update_mulop_def{
	/*
	v_update_mulop_def-> mulop ( v_int_real_col_name v_update_addop)
	v_update_mulop_def-> mulop v_int_real_col_name v_update_addop
	v_update_mulop_def-> v_update_addop_def
	v_update_mulop_def->ε
	*/
	GramDataType{
	DataType(e_mulop),
	DataType(e_l_bracket),
	DataType(e_int_real_col_name_def),
	DataType(e_update_addop_def),
	DataType(e_r_bracket),
	},

	GramDataType{
	DataType(e_mulop),
	DataType(e_int_real_col_name_def),
	DataType(e_update_addop_def),
		},
	GramDataType{
	DataType(e_update_addop_def)
	},
	GramDataType{
	DataType(e_empty)
	}
};
 GramType Grammatical::v_update_def{
	/*
	v_update_def->update table_name set col_name = v_int_real_col_name_def v_update_addop_def
	v_update_def->update table_name set col_name = v_int_real_col_name_def v_update_addop_def v_where_def
	*/
	GramDataType{
	DataType(e_update),
	DataType(e_id),
	DataType(e_set),
	DataType(e_id),
	DataType(e_equal),
	DataType(e_int_real_col_name_def),
	DataType(e_update_addop_def)
	},

	GramDataType{
	DataType(e_update),
	DataType(e_id),
	DataType(e_set),
	DataType(e_id),
	DataType(e_equal),
	DataType(e_int_real_col_name_def),
	DataType(e_update_addop_def),
	DataType(e_where_def)
	}
};
 GramType Grammatical::v_create_view_def{
	/*
	v_create_view_def->create view view_name as v_select_def
	*/
	GramDataType{
	DataType(e_create),
	DataType(e_view),
	DataType(e_id),
	DataType(e_as),
	DataType(e_select_def)
	}
};
 GramType Grammatical::v_drop_view_def{
	/*
	v_drop_view_def->drop view view_name
	*/
	GramDataType{
	DataType(e_drop),
	DataType(e_view),
	DataType(e_id),
	}
};
 GramType Grammatical::v_create_index_def{
	/*
	v_create_index_def-> create index index_name on table_name ( col_name)
	*/
	GramDataType{
	DataType(e_create),
	DataType(e_index),
	DataType(e_id),
	DataType(e_on),
	DataType(e_id),
	DataType(e_l_bracket),
	DataType(e_id),
	DataType(e_r_bracket)
	}
};
 GramType Grammatical::v_drop_index_def{
	/*
	v_drop_index_def-> drop index view_name
	*/
	GramDataType{
	DataType(e_drop),
	DataType(e_index),
	DataType(e_id)
	}
};

GramDataType& GramDataType::operator=(const GramDataType& obj) 
{
	this->ls = obj.ls;
	this->posi = obj.posi;
	this->symbol = obj.symbol;
	return *this;
}

GramDataType & GramDataType::operator+=(int num)
{
	// TODO: 在此处插入 return 语句
	*this = *this + num;
	return*this;
}

GramDataType GramDataType::operator+(int num)
{
	try {
		if (this->posi+ num > ls.size())
			throw "error";
	}
	catch (string) {
		cerr << "GramDataType::operator+ array index exceed value of max";
	}
	GramDataType temp =*this;
	temp.posi +=  num;;
	
	return temp;;
}

void GrammaticalAnalysis::init()
{
	int i;
	for (i = 0; i < GRAM_MAX; i++) {
		//gramArray[i].setGramName = static_cast<Gram>(i);
		gramArray[i].setGramName(static_cast<Gram>(i));
		for (int j = 0; j < gramArray[i].vec.size(); j++) {
			gramArray[i].vec[j].setGramName(static_cast<Gram>(i));
		}
	}
}
/*
功能：两个容器的内容相加
join 为加入的对象
beJoined 为被加入的对象
返回：被加入的对象
*/
//vector<GramDataType>& GrammaticalAnalysis::vector_join_other_vector(vector<GramDataType>& join, vector<GramDataType>& beJoined)
//{
//
//
//	// TODO: 在此处插入 return 语句
//	return vector<GramDataType>;
//}

vector<GramDataType> GrammaticalAnalysis::items(GramType obj )
{
#if (TEST==true&&GRAM_TEST==true&&ITEMS_FUNC==true)
	cout << "---------items--------" << endl;
#endif
	vector<GramDataType>vec;
	int i;
	for (i = 0; i < obj.vec.size(); i++) {
		vector<GramDataType>temp = closure(obj.vec);
		for (int j = 0; j < temp.size(); j++)
			vec.push_back(temp[j]);
	}
#if (TEST==true&&GRAM_TEST==true&&ITEMS_FUNC==true)
	cout << "-----init----" << endl;
	for (i = 0; i < vec.size(); i++) {
		cout << gram_map_to_string(vec[i].gramName) << endl;
	}
#endif
	int size;
	do {
		size = vec.size();
		for (int i = 0; i < vec.size(); i++) {
			for (int j = 0; j < vec[i].ls.size(); j++) {
				//vector_join_other_vector()
			}
		}
	} while (size != vec.size());

	return vec;
}

vector<GramDataType> GrammaticalAnalysis::Goto(const GramType &obj,const Gram&gram)
{
	vector<GramDataType>vec;
	int i;
	for (i = 0; i < obj.vec.size(); i++) {
		GramDataType temp = obj.vec[i];
		while (temp.posi+1 < temp.ls.size()) {
			if ((temp.ls[temp.posi+1].getCategory() == gram)) {
				vec.push_back(temp+1);

			}
			temp = temp + 1;
		}	
	}
#if(TEST==true&&GRAM_TEST==true&&GOTO_FUNC==true)
	cout << "----------Goto function-----------" << endl;
	for (i = 0; i < vec.size(); i++) {
		cout << gram_map_to_string( vec[i].gramName )<< endl;
	}
#endif
	return closure(vec);
}

vector<GramType> GrammaticalAnalysis::get_derived_grammar( DataType obj)
{
#if (TEST==true&&GRAM_TEST==true&&GET_DERIVED_GRAMMAR==true)
	cout << "---------get_derived_grammar function-----------" << endl;
	cout << gram_map_to_string(obj.getCategory()) << endl;
#endif
	vector<GramType>temp;
	int i;
	bool set[GRAM_STRING_TABLE_MAX]{ false };
	/*for (int i = 0; i < GRAM_STRING_TABLE_MAX; i++)
		cout << set[i] << endl;*/
	if (is_grammatical(obj.getCategory()))return temp;//非文法
	queue<Gram>q;
	q.push(obj.getCategory());
	while (!q.empty()) {
		Gram gramTemp = q.front();
		q.pop();
		//if (!is_grammatical(gramTemp))continue;
		GramType gramTypeTemp = gramArray[gramTemp];
		/*for (i = 0; i < gramTypeTemp.size(); i++)
			cout << GramStringTable[gramTypeTemp[i].ls[0].getCategory()] << endl;
		cout << "\n\n\n" << endl;*/
		for (i = 0; i < gramTypeTemp.vec.size(); i++) {
			Gram index = gramTypeTemp.vec[i].ls[0].getCategory();
			if (!is_grammatical(index)&& !set[index]) {//文法且未被加入
				q.push(index);
				cout << GramStringTable[index] << endl;
				temp.push_back(gramArray[index]);
				set[index] = true;
			}
		}
	}
	return temp;
}

Gram GrammaticalAnalysis::first(GramDataType & obj)
{

	if (obj.posi >= obj.ls.size())return e_gram_end;
	if (is_grammatical((obj.ls[obj.posi]).getCategory())) { //非文法 non-grammatical
		return obj.ls[obj.posi].getCategory();
	}
	//grammatical 文法
	GramType temp = gram_map_to_gramtype(obj.ls[obj.posi].getCategory());
	while (!is_grammatical(temp.vec[0].ls[0].getCategory())) {
		temp = gram_map_to_gramtype(temp.vec[0].ls[0].getCategory());
	}
	return temp.vec[0].ls[0].getCategory();
}

 GramCategory GrammaticalAnalysis::is_grammatical(Gram  obj)
{
	return obj>=GRAM_MAX?non_gram:gram;
}

 void GrammaticalAnalysis::grammatical_convert_to_dfa()
 {
	 GramType startGrama = gramArray[0];
	 cout << gram_map_to_string(startGrama.vec[0].ls[0].getCategory());
 }

 vector<GramDataType> GrammaticalAnalysis::closure(const vector<GramDataType> &obj)
 {
	 vector<GramDataType> temp = { obj };
	// bool set[GRAM_STRING_TABLE_MAX]{ false };
	// set[e_s] = true;
	// set[obj.gramName] = true;
	 int size,i,j,k,l,p; //保存容器大小
	//	set[temp[0].]
	 do {
		 size = temp.size();
		 for (i = 0; i < temp.size(); i++) {
			 vector<GramType>vec = get_derived_grammar(temp[i].ls[temp[i].posi]);
			 if (temp[i].posi >= temp[i].ls.size())continue;
			 vector<GramDataType> z;
			 vector<Gram>gramSymbol;
			 z.push_back(temp[i]+1);

			 if (is_grammatical(temp[i].symbol)) {
				 gramSymbol.push_back(temp[i].symbol);
			 }
			// if(gramArray(temp[i].symbol))
	//		 GramType gramTypeTemp = gramArray[temp[i].symbol];
			 else {
				 cout << gramArray[temp[i].symbol].vec.size() << endl;
				 for (j = 0; j < gramArray[temp[i].symbol].vec.size(); j++) {
					 z.push_back(gramArray[temp[i].symbol].vec[j]);

				 }
			 }
			 //for (j = 0; j < temp[i].symbol.size(); j++) { // b and z join vector varible z
				// for (k = 0; k < gramArray[temp[i].symbol[j]].size(); k++) {
				//	 z.push_back(gramArray[temp[i].symbol[j]][k]);
				// }
			 //}
			 //z.push_back()
			// vector<Gram>symbol;
		//	 z.push_back(temp[i].ls[temp[i].posi + 1].getCategory());
			 for (j = 0; j < vec.size(); j++) { // (A->a.XB,z)
				// cout << j << endl;
				 vector<Gram>symbol=gramSymbol;
				 for (l = 0; l < z.size(); l++) { //B and Z set
					 symbol.push_back(first(z[l]));	 //symbol.push_back(first(z[i]));
				 }
				 for (k = 0; k < vec[j].vec.size(); k++) { //	X->y
					// cout << vec[i][k].ls[0].getCategory() << endl;
					 for (p = 0; p < symbol.size(); p++) {
						 GramDataType gramDataTypeTemp = vec[j].vec[k];
						 gramDataTypeTemp.set_symbol(symbol[p]);
						 int u;
						 for ( u = 0; u < temp.size(); u++) { //find repeat grammatical
							 if (gramDataTypeTemp == temp[u])break;
						 }
						 if (u >= temp.size()) {							
							 cout << gram_map_to_string(gramDataTypeTemp.gramName) << " " << gram_map_to_string(gramDataTypeTemp.symbol) << endl;
							 temp.push_back(gramDataTypeTemp);
						 }
						// for (int u = 0;u<)
						 //temp.push_back()
						// if(vec[i].vec[k])
					 
					//	vec[i].gramName
				//		 
						//if(gramArray[vec[i])
					//	 
					 }

				 }


			 }

		 }

#if(TEST==true&&GRAM_TEST==true&&CLOSURE_FUNC==true)
		 cout << "----------closure function-----------" << endl;
		 for (int t = 0; t < temp.size(); t++) {
			 cout << gram_map_to_string( temp[t].gramName )<<"  "<<gram_map_to_string(temp[t].symbol)<<"  "<<temp[t].posi<< endl;;
		 }
#endif

	 } while (size != temp.size());
	 
	 return temp;
 }

 string GrammaticalAnalysis::gram_map_to_string(const Gram&obj)
 {
	 try {
		 if (obj >GRAM_STRING_TABLE_MAX)
			 throw "error";
	 }
	 catch (string) { cerr << "gram_map_to_string index exceed value of max" << endl; }
	 return GramStringTable[obj];
 }

 GramType GrammaticalAnalysis::gram_map_to_gramtype(const Gram & obj)
{
	try {
		if (obj > GRAM_MAX)
			throw "error";
	}
	catch (string) { cerr << "gram_map_to_gramtype index exceed value of max" << endl; }

	return gramArray[obj];
}
 GramType GrammaticalAnalysis::gramArray[GRAM_MAX]{
	Grammatical::v_start,//0
	Grammatical::v_s,//1
	Grammatical::v_create_def,//2
	Grammatical::v_create_data_def,//3
	Grammatical::v_constraint_def,//4
	Grammatical::v_create_data_type_def,//5
	Grammatical::v_create_data_type_suffix_def,//6
	Grammatical::v_primary_def,//7
	Grammatical::v_for_che_uni_def,//8
	Grammatical::v_col_name_rep_def,//9
	Grammatical::v_foreign_def,//10
	Grammatical::v_str_rep_def,//11
	Grammatical::v_check_def,//12
	Grammatical::v_unique_def,//13
	Grammatical::v_addop_def,//14
	Grammatical::v_mulop_def,//15
	Grammatical::v_compare_def,//16
	Grammatical::v_logic_def,//17
	Grammatical::v_gather_fuc_def,//18
	Grammatical::v_int_real_col_name_def,//19
	Grammatical::v_int_real_col_name_rep_def,//20
	Grammatical::v_where_addop_def,//21
	Grammatical::v_where_mulop_def,//22
	Grammatical::v_where_algorithm_operator_def,//23
	Grammatical::v_where_algorithm_operator_or_string_def,//24
	Grammatical::v_where_compare_def,//25
	Grammatical::v_where_compare_or_string_match_def,//26
	Grammatical::v_logic_and_where_compare_string_match_def,//27
	Grammatical::v_where_logic_def,//28
	Grammatical::v_where_def,//29
	Grammatical::v_comma_and_col_name_def,//30
	Grammatical::v_order_def,//31
	Grammatical::v_group_def,//32
	Grammatical::v_having_def,//33
	Grammatical::v_where_algorithm_operator_rep_def,//34
	Grammatical::v_select_operator_def,//35
	Grammatical::v_connect_mode_def,//36
	Grammatical::v_connect_def,//37
	Grammatical::v_connect_addop_def,//38
	Grammatical::v_connect_mulop_def,//39
	Grammatical::v_connect_algorithm_operator_def,//40
	Grammatical::v_connect_algorithm_operator_or_string_def,//41
	Grammatical::v_connect_compare_def,//42
	Grammatical::v_connect_compare_or_str_match_def,//43
	Grammatical::v_logic_connect_compare_or_str_match_def,//44
	Grammatical::v_connect_logic_def,//45
	Grammatical::v_constriant_having_def,//46
	Grammatical::v_constraint_group_def,//47
	Grammatical::v_select_connect_def,//48
	Grammatical::v_constriant_connect_def,//49
	Grammatical::v_table_name_def,//50
	Grammatical::v_select_def,//51
	Grammatical::v_create_database_def,//52
	Grammatical::v_use_database_def,//53
	Grammatical::v_delete_element_def,//54
	Grammatical::v_delete_table_def,//55
	Grammatical::v_alter_table_col_name_def,//56
	Grammatical::v_alter_table_drop_col_name_def,//57
	Grammatical::v_insert_def,//58
	Grammatical::v_update_addop_def,//59
	Grammatical::v_update_mulop_def,//60
	Grammatical::v_update_def,//61
	Grammatical::v_create_view_def,//62
	Grammatical::v_drop_view_def,//63
	Grammatical::v_create_index_def,//64
	Grammatical::v_drop_index_def//65
};
