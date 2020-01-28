/*
2020/1/23 上午 重构first函数
2020/1/23 下午 重构get_derived_grammar函数


*/

#ifndef _GrammaticalAnalysis_
#include"GrammaticalAnalysis.h"
#endif
#define CLOSURE_FUNC false
#define GOTO_FUNC false
#define ITEMS_FUNC true
#define GET_DERIVED_GRAMMAR false
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
	DataType(e_r_bracket),
 DataType(e_gram_end)//add tiem 2020/1/26 10:30
 }
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
	DataType(e_create_data_type_suffix_def),
	
 },

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
	DataType(e_real),
 },

	GramDataType{
	DataType(e_integer),
	},
	
	GramDataType{  //char(n)
	DataType(e_char),
	DataType(e_l_bracket),
	DataType(e_integer),
	DataType(e_r_bracket),

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
	v_str_rep_def->string  str_rep_def
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
	/*GramDataType{
	DataType(e_addop_def),
	DataType(e_int_real_col_name_def),
	DataType(e_where_mulop_def),
	}*/
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
//GramDataType{
//	DataType(e_mulop_def),
//	DataType(e_int_real_col_name_def),
//	DataType(e_where_addop_def),
//}

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
	DataType(e_where_logic_def),
	// DataType(e_gram_end)//add tiem 2020/1/26 10:30
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
	DataType(e_id),
	
	},
	GramDataType{
	DataType(e_order),
	DataType(e_by),
	DataType(e_id),
	DataType(e_comma_and_col_name_def),
	 
	},
	GramDataType{
	DataType(e_order),
	DataType(e_by),
	DataType(e_id),
	DataType(e_desc),
	
	},
	GramDataType{
	DataType(e_order),
	DataType(e_by),
	DataType(e_id),
	DataType(e_asc),
	
	},

	GramDataType{
	DataType(e_order),
	DataType(e_by),
	DataType(e_id),
	DataType(e_comma_and_col_name_def),
	DataType(e_desc),
	
	},
	GramDataType{
	DataType(e_order),
	DataType(e_by),
	DataType(e_id),
	DataType(e_comma_and_col_name_def),
	DataType(e_asc),
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
	DataType(e_id),
	 
	},
	GramDataType{
	DataType(e_group),
	DataType(e_by),
	DataType(e_id),
	DataType(e_comma_and_col_name_def),
	 
	}

};
 GramType Grammatical:: v_having_def{

	/*
	v_having_def-> having v_where_logic_def
	
	*/
	GramDataType{
	DataType(e_having),
	DataType(e_where_logic_def),

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
	v_connect_mode_def->natual
	v_connect_mode_def->right
	v_connect_mode_def->left
	v_connect_mode_def->full
	
	*/
	GramDataType{
	DataType(e_right)
	},
	 GramDataType{
	 DataType(e_natural)
 },
	GramDataType{
	DataType(e_left)
},
GramDataType{
	DataType(e_full)
}

};
 GramType Grammatical::v_connect_def{
	 /*
	 v_connect_def->v_connect_mode_def join table_name on v_connect_logic_def
	 */
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
	DataType(e_where_def),
	
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
	v_select_def->select distance v_select_connect_def from v_table_name_def v_constriant_connect_def
	v_select_def->select v_select_connect_def from v_table_name_def v_constriant_connect_def
	v_select_def->select v_select_connect_def from v_table_name_def v_where_def
	*/
	GramDataType{
	 DataType(e_select),
	DataType(e_distance),
	DataType(e_select_connect_def),
	DataType(e_from),
	DataType(e_table_name_def),
	DataType(e_constriant_connect_def),
	 DataType(e_gram_end)//add tiem 2020/1/26 10:30
	},
	GramDataType{
	 DataType(e_select),
	DataType(e_select_connect_def),
	DataType(e_from),
	DataType(e_table_name_def),
	DataType(e_constriant_connect_def),
	 DataType(e_gram_end)//add tiem 2020/1/26 10:30
	},

	GramDataType{
	 DataType(e_select),
	DataType(e_select_connect_def),
	DataType(e_from),
	DataType(e_table_name_def),
	DataType(e_where_def),
 DataType(e_gram_end)//add tiem 2020/1/26 10:30
	},

	GramDataType{
	 DataType(e_select),
	DataType(e_distance),
	DataType(e_select_connect_def),
	DataType(e_from),
	DataType(e_table_name_def),
	DataType(e_where_def),
	 DataType(e_gram_end)//add tiem 2020/1/26 10:30
		}
};
 GramType Grammatical::v_create_database_def{
	/*
	v_create_database_def-> create database database_name
	
	*/
	GramDataType{
	DataType(e_create),
	DataType(e_database),
	DataType(e_id),
	 DataType(e_gram_end)//add tiem 2020/1/26 10:30
	},

};
 GramType Grammatical::v_use_database_def{
	 /*
	 v_use_database_def->use database_name
	 */
	GramDataType{
	DataType(e_use),
	DataType(e_id),
	 DataType(e_gram_end)//add tiem 2020/1/26 10:30
}

};
 GramType Grammatical::v_delete_element_def{
	/*
	v_delete_element_def->delete from table_name
	
	*/
	GramDataType{
	DataType(e_delete),
	DataType(e_from),
	DataType(e_id),
	 DataType(e_gram_end)//add tiem 2020/1/26 10:30
	}
	
};
 GramType Grammatical::v_delete_table_def{
	 /*
	 v_delete_table_def-> delete table table_name
	 */
	GramDataType{
	DataType(e_delete),
	DataType(e_table),
	DataType(e_id),
	 DataType(e_gram_end)//add tiem 2020/1/26 10:30
}
};
 GramType Grammatical::v_alter_table_add_col_name_def{
	/*
	v_alter_table_col_name_def -> alter table table_name add column col_name v_int_real_col_name
	
	*/
	GramDataType{
	DataType(e_alter),
	DataType(e_table),
	DataType(e_id),
	DataType(e_add),
	DataType(e_column),
	DataType(e_id),
	DataType(e_int_real_col_name_def),
	 DataType(e_gram_end)//add tiem 2020/1/26 10:30
	}
	
};
 GramType Grammatical::v_alter_table_drop_col_name_def{
	 /*
	 v_alter_table_drop_col_name_def->alter table table_name drop col_name
	 */
	GramDataType{
	DataType(e_alter),
	DataType(e_table),
	DataType(e_id),
	DataType(e_drop),
	DataType(e_id),
	 DataType(e_gram_end)//add tiem 2020/1/26 10:30
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
	DataType(e_r_bracket),
	DataType(e_gram_end)//add tiem 2020/1/26 10:30
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
	DataType(e_update_addop_def),
	 DataType(e_gram_end)//add tiem 2020/1/26 10:30
	},

	GramDataType{
	DataType(e_update),
	DataType(e_id),
	DataType(e_set),
	DataType(e_id),
	DataType(e_equal),
	DataType(e_int_real_col_name_def),
	DataType(e_update_addop_def),
	DataType(e_where_def),
	 DataType(e_gram_end)//add tiem 2020/1/26 10:30
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
	DataType(e_select_def),
DataType(e_gram_end)//add tiem 2020/1/26 10:30
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
 DataType(e_gram_end)//add tiem 2020/1/26 10:30
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
	DataType(e_r_bracket),
	 DataType(e_gram_end)//add tiem 2020/1/26 10:30
	}
};
 GramType Grammatical::v_drop_index_def{
	/*
	v_drop_index_def-> drop index view_name
	*/
	GramDataType{
	DataType(e_drop),
	DataType(e_index),
	DataType(e_id),
	 DataType(e_gram_end)//add tiem 2020/1/26 10:30
	}
};

 GramDataType::GramDataType(initializer_list<DataType> initializer)
 {	
		 initializer_list<DataType>::const_iterator begin, end;
		 begin = initializer.begin();
		 end = initializer.end();
		 for (; begin != end; begin++) {
			 ls.push_back(*begin);
		 }
		 posi = 0;
 }

 GramDataType::GramDataType(DataType&obj)
 {
	 ls.push_back(obj);
 }

 void GramDataType::setGramName(Gram gramName)
 {
	 this->gramName = gramName; 
 }

 Gram GramDataType::getGramName()
 {
return gramName; 
 }

 Gram GramDataType::getSymbol()
 {
	  return symbol; 
 }

 int GramDataType::getPosi()
 {
	 return posi; 
 }

 void GramDataType::set_symbol(const Gram & obj)
 {
	  this->symbol = obj; 
 }

 GramDataType& GramDataType::operator=(const GramDataType& obj)
{
	this->ls = obj.ls;
	this->posi = obj.posi;
	this->symbol = obj.symbol;
	this->setGramName(obj.gramName);
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
vector<DataType> GramDataType::getLs()
{
	return  this->ls; 
}
GrammaticalAnalysis::GrammaticalAnalysis(string filePath)
{		
		file = new GrammaticalAnalysisFile(filePath);
	//	file->set_file_path(filePath);
		init();
}
void GrammaticalAnalysis::run()
{
	//init();
	fstream statusFile("C:\\Users\\THINKPAD\\Desktop\\status.txt", ios::in);
	fstream gotoTableFile ("C:\\Users\\THINKPAD\\Desktop\\table.txt", ios::in);
	if (!statusFile || !gotoTableFile) {
		GramType gramTypeTemp = gramArray[0];
		for (int i = 0; i < gramTypeTemp.vec.size(); i++) {
			gramTypeTemp.vec[i].symbol = e_eof;
		}
		status = items(gramTypeTemp);
		save_status(status,GotoTable);
	}
	else {
		read_status(status,GotoTable);
	}
	//init_reduction();
	//check_grammatical();
}
/*
功能：初始化gramArray中的文法号
*/
void GrammaticalAnalysis::init()
{
	int i,j;
	GotoTable = new string*[GOTO_TABLE_MAX];
	for (i = 0; i < GOTO_TABLE_MAX;i++)
		GotoTable[i] = new string[GRAM_ENUM_MAX];
	for (i = 0; i < GOTO_TABLE_MAX; i++) {
		for (j = 0; j < GRAM_ENUM_MAX; j++) {
			GotoTable[i][j] = EMPTY;
		}
	}
	/*GotoTable = new int*[GOTO_TABLE_MAX];
	for (i = 0; i < GOTO_TABLE_MAX; i++)
		GotoTable[i] = new int[GOTO_TABLE_MAX];*/
	//for (i = 0; i < GOTO_TABLE_MAX; i++)
	//	for (int j = 0; j < GRAM_ENUM_MAX; j++) {
	//		//GotoTable[i][j] = EMPTY;
	//		char ch[CHAR_SIZE] = EMPTY;
	//	}
	for (i = 0; i < GRAM_MAX; i++) {
		//gramArray[i].setGramName = static_cast<Gram>(i);
		gramArray[i].setGramName(static_cast<Gram>(i));
		for (int j = 0; j < gramArray[i].vec.size(); j++) {
			gramArray[i].vec[j].setGramName(static_cast<Gram>(i));
		}
	}


	
//read_status(status,GotoTable);
	//status = items(gramTypeTemp);
	//save_status(status,GotoTable);
	//vector<Gram>temp=first(e_where_def);
	//check_grammatical();
	//file = new GrammaticalAnalysisFile();
	//print(GotoTable);
}
bool GrammaticalAnalysis::check_grammatical()
{
//	int lastIndex = 0, i = 0, stuIndex = 0;
//	bool flag = false;
//	GramTokenType temp;
//	vector<GramDataType>gramTemp;
//	std::string strTemp;
//	while (file->get_token_size()) {
//		flag = true;
//		strTemp = file->get_token();
//		if (strTemp == "")continue;
//		temp = string_convert_to_GramToken(strTemp);
//	//	stuIndex = GotoTable[lastIndex][temp.getGram()];
//		gramTemp = status[stuIndex];
////		lastIndex = GotoTable[lastIndex][temp.getGram()];
//		for (i = 0; i < gramTemp.size(); i++) {
//			 Gram gram = gramTemp[i].gramName;
//			if (gram==e_start|| gram == e_create_def || gram == e_select_def || gram == e_create_database_def ||
//				gram == e_use_database_def || gram == e_delete_element_def || gram == e_delete_table_def ||
//				gram == e_alter_table_add_col_name_def || gram == e_alter_table_drop_col_name_def ||
//				gram == e_insert_def || gram == e_update_def||gram== e_create_view_def||gram== e_drop_view_def||
//				gram== e_create_index_def|| gram==e_drop_index_def
//				) {
//				if (gramTemp[i].posi + 1 == gramTemp[i].ls.size() && gramTemp[i].symbol == e_eof&&
//					gramTemp[i].ls[gramTemp[i].posi].getCategory() == e_gram_end) {
//					flag = true;
//					lastIndex = 0;
//				}
//			}
//			//if (gramTemp[i].posi+1 == gramTemp[i].ls.size()&&
//			//	gramTemp[i].ls[gramTemp[i].posi].getCategory() == temp.getGram() &&
//			//	/*gramTemp[i].ls[ gramTemp[i].posi].getCategory()==e_gram_end &&	*/		
//			//	gramTemp[i].symbol == e_eof) {
//			//	flag = true;
//			//	lastIndex = 0;
//			//}
//		}
//	}
		/*int index = GotoTable[0][temp.getGram()];
		temp = string_convert_to_GramToken(file->get_token());
		int index2 = GotoTable[index][temp.getGram()];
		tempA =status[index 	];*/

	stack<int>statusStack;
	stack<Gram>gramStack;
	vector<GramDataType>curStatus = status[0];
	int i, j;
	while (file->get_token_size()>0) {
		string str = file->get_token();

	}

	return false;
}
void GrammaticalAnalysis::print(int GotoTable[GOTO_TABLE_MAX][GRAM_ENUM_MAX])
{
	cout << "-------------print(int GotoTable[GRAM_MAX][GRAM_ENUM_MAX])---------------" << endl;
	int i, j,k,l;
	for (i = 0; i < GOTO_TABLE_MAX; i++) {
		vector<GramDataType>temp = status[i];
	/*	for (j = 0; j < GRAM_ENUM_MAX; j++) {*/
			//if (GotoTable[i][j] != EMPTY) 
		cout << "status:" << i << "-->" << endl;//<</*gram_map_to_string(static_cast<Gram>(j)) <<"	"<< gram_map_to_string(static_cast<Gram>(j))<<endl*/;
				

		for (k = 0; k < temp.size(); k++) {
			cout <<"gram->"<< gram_map_to_string(temp[k].getGramName()) << "  symbol  "/* <<gram_map_to_string( temp[k].symbol)*/ <<"	"<<gram_map_to_string(static_cast<Gram>(k))<< "  posi " << temp[k].posi << endl;
					
					/*cout << gram_map_to_string(temp[k].) << "	";*/
			//cout<<gram_map_to_string(temp[k].symbol)
					for (l = 0; l < temp[k].ls.size(); l++)
						cout <<gram_map_to_string( temp[k].ls[l].getCategory() )<< "	";	
					cout << endl;
				}
			
		
		//}

		printf("\n\n\n");
	}


}

/*
功能：得 两个容器的不重复的元素，重复元素只加入一次
vec 为加入的对象
beJoined 为被加入的对象
返回：被加入的对象
*/
inline vector<GramDataType>& GrammaticalAnalysis::vector_join_other_vector(vector<GramDataType>& vec, vector<GramDataType>& beJoined)
{
	int i, j;
	for ( i = 0; i < vec.size(); i++)
	{	
		for ( j = 0; j < beJoined.size(); j++) {
			if (vec[i] == beJoined[j]) 
				break;
			
		}
		if (j >= beJoined.size())beJoined.push_back(vec[i]);
	}
	// TODO: 在此处插入 return 语句
	return beJoined;
}
/*
输入：需要转换成的gramTokenType类型的字符串
功能：把str转换成
输出：转换后的GramTokenType
*/
 GramTokenType GrammaticalAnalysis::string_convert_to_GramToken(const string & str)
{
	GramTokenType temp;
	temp.set_value(str);
	return temp;
}
/*
输入:GramType obj
功能：得到obj文法的NFA
输出：得到的文法的集合
*/
vector< vector<GramDataType>> GrammaticalAnalysis::items(GramType obj )
{
#if (TEST&&GRAM_TEST&&ITEMS_FUNC)
	cout << "---------items--------" << endl;
#endif
	vector<vector<GramDataType>>vec;
	int i,j,k,t;
	char ch[BUFF_SIZE];
	/*for (i = 0; i < obj.vec.size(); i++) {*/
		vector<GramDataType>temp = closure(obj.vec);
	//	for (int j = 0; j < temp.size(); j++)
			vec.push_back(temp);
	//}
	//vec.push_back(obj.vec);

#if (TEST&&GRAM_TEST&&ITEMS_FUNC)
	cout << "-----init----" << endl;
	for (i = 0; i < vec.size(); i++) {
		for (j = 0; j < vec[i].size();j++)
		cout << gram_map_to_string(vec[i][j].gramName)<<"  "<<vec[i][j].getSymbol()<<"  "<<vec[i][j].posi << endl;//BUG position add 2020/1/21
	}
#endif
	int size;
//	//do {
//		size = vec.size();
//		for (i = 0; i < vec.size(); i++) {
//			for (j = 0; j < vec[i].size(); j++) {
//				if (is_grammatical(vec[i][j].getGramName()))continue;
//				for (k = 0; k < GRAM_ENUM_MAX; k++) {
//					/*if(is_grammatical())*/
//					//if(k==)
//
//					vector<GramDataType>temp=Goto(vec[i],static_cast<Gram>(k));
//					if (temp.size() <= 0)continue;
//					#if(TEST&&GRAM_TEST&&ITEMS_FUNC)
//					
//					cout << "Goto(" << gram_map_to_string(vec[i][j].getGramName()) << ", " << gram_map_to_string(static_cast<Gram>(k)) << ")" <<"	"<< vec[i][j].posi<< endl;
//					cout << "-------------temp vec----------------"<<temp.size() << endl;
//					for (int r = 0; r < temp.size(); r++) {
//						cout << gram_map_to_string(temp[r].getGramName()) << " ";
//					}
//					cout << "\n" << "end" << endl;
//#endif
//					for ( t = 0; t < vec.size(); t++) {
//						if (vec[t] == temp)break;
//					}
//					if (t >= vec.size()) {
//#if(TEST&&GRAM_TEST&&ITEMS_FUNC)
//						cout << "gram--->" << gram_map_to_string(vec[i][j].getGramName()) << "symbol-->" << gram_map_to_string(static_cast<Gram>(k)) << endl;;
//						cout << "Goto[" << static_cast<int>(vec[i][j].getGramName()) << "][" << static_cast<Gram>(k)<<"]="<<vec.size() << endl;
//#endif
//						GotoTable[i][static_cast<Gram>(k)] = vec.size();
//						vec.push_back(temp);
//						//int temp = 
//						
//					}
//					//if (vec[0] == vec[1]);
//				}
//			}
//		}
//	//} while (size != vec.size());
//	//vector<GramDataType>vec;
//
//
	/*int i,k;*/
	do {
		size = vec.size();
		for (i = 0; i < vec.size(); i++) {
			for (k = 0; k < GRAM_ENUM_MAX; k++) {
				vector<GramDataType>temp = Goto(vec[i], static_cast<Gram>(k));

				if (temp.size() <= 0)continue;
				//#if(TEST&&GRAM_TEST&&ITEMS_FUNC)
				//
				//			cout << "Goto(" << i << ", " << gram_map_to_string(static_cast<Gram>(k)) << ")" << "	"/* << vec[i][j].posi */<< endl;
				//			cout << "-------------temp vec----------------" << temp.size() << endl;
				//			for (int r = 0; r < temp.size(); r++) {
				//				cout << gram_map_to_string(temp[r].getGramName()) << " ";
				//			}
				//			cout << "\n" << "end" << endl;
				//#endif
				char ch[BUFF_SIZE];
				string str = is_grammatical(static_cast<Gram>(k)) ? "s" : "g";
				for (t = 0; t < vec.size(); t++) {
					if (vec[t] == temp) {
						
						str = str + _itoa(static_cast<int>(t), ch, 10);
						GotoTable[i][k] = str;

						break;

					}
				}

				if (t >= vec.size()) {
					cout << "status:" << i << "->" << gram_map_to_string(static_cast<Gram>(k))<<"  ";
					str = str + _itoa(static_cast<int>(vec.size()), ch, 10);
				GotoTable[i][k] = str;
					
					cout << vec.size() << endl;
 					vec.push_back(temp);
					for (t = 0; t < temp.size(); t++) {
						if (temp[t].getPosi() == temp[t].ls.size()) {
							redu.push_back(Redu(vec.size(), temp[t].getSymbol(), temp[t]));
						}
					}


					}
				str.clear();
			}


			//if (i >= 200)break;
		

		}
	} while (size != vec.size());//add at  2020/1/13 21:33
	return vec;
}
/*
输入：文法obj， 符号 gram
功能：得到文法posi中有符号gram的集合
输出：vector<GramDataType>的文法集合
*/
vector<GramDataType> GrammaticalAnalysis::Goto(const vector<GramDataType> &obj, const Gram &gram) {
	int i;
	vector<GramDataType>vec;
	for (i = 0; i < obj.size(); i++) {
		GramDataType temp = obj[i];
		/*while (temp.posi < temp.ls.size()) {*/
		if ((temp.posi < temp.ls.size())/*&&temp.ls[temp.posi].getCategory()!=e_gram_end*/) {
			if ((temp.ls[temp.posi].getCategory() == gram)) {

				vec.push_back(temp + 1);

			}
			/*else {
				vector<Gram>gramTemp = first(temp.ls[temp.posi].getCategory());
				int j;
				for (j = 0; j < gramTemp.size(); j++) {
					if (gram == gramTemp[j])
						vec.push_back(temp + 1);
				}
			}*/
		}
		
	}
#if(TEST&&GRAM_TEST&&GOTO_FUNC)
	cout << "----------Goto function-----------" << endl;
	for (i = 0; i < vec.size(); i++) {
		cout << gram_map_to_string(vec[i].gramName) << endl;
	}
#endif
	vec = closure(vec);
	return vec;
}

/*
输入：文法obj， 符号 gram
功能：得到文法posi中有符号gram的集合
输出：vector<GramDataType>的文法集合
*/
vector<GramDataType> GrammaticalAnalysis::Goto(const GramDataType &obj, const Gram &gram)
{
	int i;
	vector<GramDataType>vec;
	GramDataType temp = obj;
	/*while (temp.posi  < temp.ls.size()) {*/

		if ((temp.posi<temp.ls.size())&&(temp.ls[temp.posi ].getCategory() == gram)) {

			vec.push_back(temp+1 );

		/*}
		temp = temp + 1;*/
	}

#if(TEST==true&&GRAM_TEST==true&&GOTO_FUNC==true)
	cout << "----------Goto function-----------" << endl;
	for (i = 0; i < vec.size(); i++) {
		cout << gram_map_to_string(vec[i].gramName) << endl;
	}
#endif
	return closure(vec);
}
/*
输入：文法obj， 符号 gram
功能：得到文法posi中有符号gram的集合
输出：vector<GramDataType>的文法集合
*/
vector<GramDataType> GrammaticalAnalysis::Goto(const GramType &obj,const Gram&gram)
{
	vector<GramDataType>vec;
	int i;
	for (i = 0; i < obj.vec.size(); i++) {
		GramDataType temp = obj.vec[i];
		/*while (temp.posi < temp.ls.size()) {*/
			if ((temp.posi<temp.ls.size())&&(temp.ls[temp.posi].getCategory() == gram)) {

				vec.push_back(temp+1);

			}
		/*	temp = temp + 1;
		}	*/
	}
#if(TEST&&GRAM_TEST&&GOTO_FUNC)
	cout << "----------Goto function-----------" << endl;
	for (i = 0; i < vec.size(); i++) {
		cout << gram_map_to_string( vec[i].gramName )<<" symbol:"<<vec[i].symbol<<"  posi:"<<vec[i].posi << endl;
	}
#endif
	return closure(vec);
}
/*
输入：DataType 类型的对象，obj
功能：得到这个文法派生出来的所有文法，即不经过任何符号，但是经过文法
输出：文法集合
*/
vector<GramType> GrammaticalAnalysis::get_derived_grammar(DataType &obj)
{
#if (TEST&&GRAM_TEST&&GET_DERIVED_GRAMMAR)
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
			//	Gram index=gramTypeTemp.vec[i].get
			if (!set[index]) {
				if (!is_grammatical(index)) {//文法且未被加入
					q.push(index);
					//	cout << GramStringTable[index] << endl;
					temp.push_back(gramArray[index]);
					//set[index] = true;
					set[index] = true;
				}
				else {
					GramType gramTypeTemp2 = GramType(GramDataType(DataType(index)));
					gramTypeTemp2.setGramName(gramTypeTemp.getGramName());
					gramTypeTemp2.vec[0].posi = 0;
					if (gramTypeTemp.vec[i].ls.size()>2) {
						gramTypeTemp2.vec[0].set_symbol(gramTypeTemp.vec[i].ls[1].getCategory());
						
					}
					else {

						gramTypeTemp2.vec[0].set_symbol(e_gram_end);
					}
					gramTypeTemp2.vec[0].setGramName(gramTypeTemp.vec[i].getGramName());
					//gramTypeTemp2.setGramName(gramTypeTemp.getGramName());
				//	gramTypeTemp2.vec[0].set_symbol(gramTypeTemp.vec[0].getSymbol());

					temp.push_back(gramTypeTemp2);

				}
				//	
				//}

			}
		}
		
	}
	return temp;
}
vector<Gram> GrammaticalAnalysis::first(const Gram gram, bool visit[GRAM_ENUM_MAX]) {

	if (first_set[gram].size() >0)return first_set[gram];
	vector<Gram>gloFirstSet{};
	vector<Gram>tempFirstSet{};
	vector<DataType>list;
	if (is_grammatical(gram)|| visit[gram])return vector<Gram>{gram};
	int i, size = 0, k, j;
	bool flag = true, empty;
	GramType gramTypeTemp = gramArray[gram];
	visit[gram] = true;
	for (i = 0; i < gramTypeTemp.vec.size(); i++) {
		list = gramTypeTemp.vec[i].ls;
		/*	for (j = 0; j < list.size(); j++) {*/
		k = 0; flag = true;
		while (flag == true && k < list.size()) {
		//	if (visit[list[k].getCategory()])continue;
			if (first_set[list[k].getCategory()].size() > 0) {
				tempFirstSet = first_set[list[k].getCategory()];
			}
			else {
				tempFirstSet = first(list[k].getCategory(),visit);
				first_set[list[k].getCategory()] = tempFirstSet;
			}
			
			empty = false;
			
			vector<Gram>::iterator begin(tempFirstSet.begin()), end;
			end = tempFirstSet.end();
			while (begin != end) {
				if (*begin == e_empty) {
					empty = true;
					tempFirstSet.erase(begin);
					break;
				}
				begin++;
			}
			/*vector<Gram>::iterator values(tempFirstSet.begin());
			int p = 0;
			for (; p < tempFirstSet.size(); p++) {
				if()
			}*/
			gloFirstSet = gloFirstSet + tempFirstSet;
			if (empty)flag = false;
			k++;
		}
		if (flag)gloFirstSet.push_back(e_empty);
		/*	}*/



	}
	first_set[gram] = gloFirstSet;
	return gloFirstSet;


}
/*
输入：GramDataType&obj,单个文法对象
功能：得到obj文法所派生出来的第一个非文法符号
输出：输出这个非文法符号
*/
vector<Gram> GrammaticalAnalysis::first(const Gram  gram)
{
	bool visit[GRAM_ENUM_MAX]{ false };
	return first(gram, visit);
	//if (first_set[gram].size() >0)return first_set[gram];
	//vector<Gram>gloFirstSet{};
	//vector<Gram>tempFirstSet{};
	//vector<DataType>list;
	//if (is_grammatical(gram))return vector<Gram>{gram};
	//int i, size = 0, k, j;
	//bool flag=true, empty;
	//GramType gramTypeTemp = gramArray[gram];
	//for (i = 0; i < gramTypeTemp.vec.size(); i++) {
	//	list = gramTypeTemp.vec[i].ls;
	///*	for (j = 0; j < list.size(); j++) {*/
	//		k = 0; flag = true;
	//		while (flag == true && k < list.size()) {
	//			if (first_set[list[k].getCategory()].size() > 0) {
	//				tempFirstSet = first_set[list[k].getCategory()];
	//			}
	//			else {
	//				tempFirstSet = first(list[k].getCategory(), visit);
	//				first_set[list[k].getCategory()] = tempFirstSet;
	//			}
	//			empty = false;
	//			vector<Gram>::iterator begin(tempFirstSet.begin()), end(tempFirstSet.end());
	//			while (begin != end) {
	//				if (*begin == e_empty) {
	//					empty = true;
	//					tempFirstSet.erase(begin);
	//					break;
	//				}

	//			}
	//			gloFirstSet =gloFirstSet+ tempFirstSet;
	//			if (empty)flag = false;
	//			k++;
	//		}
	//		if (flag)gloFirstSet.push_back(e_empty);
	///*	}*/



	//}
	//return gloFirstSet;
	/*for (i = 0; i < obj.size(); i++) {*/
		/*vector<Gram>tempFirst{};
		if (first_set[static_cast<int>(obj[i])].size() == 0) {

		}*/

		//
		/*
			*///}
			//if (obj.posi >= obj.ls.size())return e_error;
			//if (is_grammatical((obj.ls[obj.posi]).getCategory())) { //非文法 non-grammatical
			//	return obj.ls[obj.posi].getCategory();
			//}
			////grammatical 文法
			//GramType temp = gram_map_to_gramtype(obj.ls[obj.posi].getCategory());
			//while (!is_grammatical(temp.vec[0].ls[0].getCategory())) {
			//	temp = gram_map_to_gramtype(temp.vec[0].ls[0].getCategory());
			//}
			//return temp.vec[0].ls[0].getCategory();

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
 /*
 输入：vector<GramDataType>&obj 文法集合
 功能：文法A->a.XB,Z 把B,Z文法或者符号加入到所有派生A->a.XB,Z文法
 输出：文法集合
 */
 vector<GramDataType> GrammaticalAnalysis::closure(const vector<GramDataType> obj)
 {
	 vector<GramDataType> temp = { obj };
	// bool set[GRAM_STRING_TABLE_MAX]{ false };
	// set[e_s] = true;
	// set[obj.gramName] = true;
	 int size,i,j,k,l,p,u; //保存容器大小
	//	set[temp[0].]
	 do {
		 size = temp.size();
		 for (i = 0; i < temp.size(); i++) {
			 if (temp[i].posi >= temp[i].ls.size())continue;//2020/1/8 21:23 add
			// vector<GramType>vec;/*= get_derived_grammar(temp[i].ls[temp[i].posi]);*/
			 GramType vec;
			 if (!is_grammatical(temp[i].ls[temp[i].posi].getCategory())) {//文法
				 vec = gramArray[temp[i].ls[temp[i].posi].getCategory()];

				 Gram z;
				 vector<Gram>gramSymbol;
				 //非文法
				/* if (is_grammatical(temp[i].symbol)&&temp[i].posi==0) {
				 gramSymbol.push_back(temp[i].symbol);
				  }*/
				//z=temp[i].symbol;
				if (temp[i].posi + 1 < temp[i].ls.size()) {
					z = temp[i].ls[temp[i].posi + 1].getCategory();
					gramSymbol = first(z);
				}//else gramSymbol = gramSymbol + first(e_gram_end);
				//if(temp[i].posi==0) //2020-1-27
				gramSymbol = gramSymbol + first(temp[i].getSymbol());
				for (k = 0; k < vec.vec.size(); k++) {
					for (p = 0; p < gramSymbol.size(); p++) {

						GramDataType gramDataTypeTemp = vec.vec[k];
						gramDataTypeTemp.set_symbol(gramSymbol[p]);
						for (u = 0; u < temp.size(); u++) {
							if (temp[u] == gramDataTypeTemp)break;
						}

						if (u >= temp.size()) {
#if (TEST&&GRAM_TEST&&CLOSURE_FUNC)
							cout << "grammatical:" << gram_map_to_string(gramDataTypeTemp.gramName) << " symbol:" << gram_map_to_string(gramDataTypeTemp.symbol) << "  posi:" << gramDataTypeTemp.posi << "--->" << endl;
							for (int r = 0; r < gramDataTypeTemp.ls.size(); r++) {
								cout << gram_map_to_string(gramDataTypeTemp.ls[r].getCategory()) << "  ";
							}
							cout << endl;
#endif
							temp.push_back(gramDataTypeTemp);
					}


				}
			 }
			 

		//	 if (vec.size()==0||(temp[i].posi >= temp[i].ls.size()))continue;
	//		 Gram z;
		//	 vector<Gram>gramSymbol;
			//if (is_grammatical(temp[i].symbol)) {//非文法
				 //gramSymbol.push_back(temp[i].symbol);
			/* }*/
			/*z.push_back(temp[i].symbol);*/
			
	/*	for (j = 0; j < vec.size(); j++) {
				if (temp[i].posi + 1 < temp[i].ls.size()) {
					z = temp[i].ls[temp[i].posi + 1].getCategory();
					gramSymbol = first(z);
				}
				gramSymbol = gramSymbol + first(temp[i].symbol);
				for (k = 0; k < vec[j].vec.size(); k++) {
					for (p = 0; p < gramSymbol.size(); p++) {
						GramDataType gramDataTypeTemp = vec[j].vec[k];
						 gramDataTypeTemp.set_symbol(gramSymbol[p]);
						 for (u = 0; u < temp.size(); u++) {
							 if (temp[u] == gramDataTypeTemp)break;
						 }
						 if (u >= temp.size()) {
#if (TEST&&GRAM_TEST&&CLOSURE_FUNC)
 cout <<"grammatical:"<< gram_map_to_string(gramDataTypeTemp.gramName) << " symbol:" << gram_map_to_string(gramDataTypeTemp.symbol)<<"  posi:"<<gramDataTypeTemp.posi<<"--->" << endl;
for (int r = 0; r < gramDataTypeTemp.ls.size(); r++) {
	cout <<gram_map_to_string( gramDataTypeTemp.ls[r].getCategory()) << "  ";
							 							 }
		cout << endl;
 #endif
					 temp.push_back(gramDataTypeTemp);
							 						 }

					}
				}




			}*/


			// if(gramArray(temp[i].symbol))
	//		 GramType gramTypeTemp = gramArray[temp[i].symbol];
//			 else {
//#if(TEST&&GRAM_TEST&&CLOSURE)
//				 cout << gramArray[temp[i].symbol].vec.size() << endl;
//#endif
//				 for (j = 0; j < gramArray[temp[i].symbol].vec.size(); j++) {
//					 z.push_back(gramArray[temp[i].symbol].vec[j]);
//
//				 }
//			 }
			 //for (j = 0; j < temp[i].symbol.size(); j++) { // b and z join vector varible z
				// for (k = 0; k < gramArray[temp[i].symbol[j]].size(); k++) {
				//	 z.push_back(gramArray[temp[i].symbol[j]][k]);
				// }
			 //}
			 //z.push_back()
			// vector<Gram>symbol;
		//	 z.push_back(temp[i].ls[temp[i].posi + 1].getCategory());
//			 for (j = 0; j < vec.size(); j++) { // (A->a.XB,z)
//				// cout << j << endl;
//				 vector<Gram>symbol=gramSymbol;
//				 for (l = 0; l < z.size(); l++) { //B and Z set
//					 Gram gramTemp = first(z[l]);
//					 if (gramTemp == e_error)continue;
//					 symbol.push_back(gramTemp);	 //symbol.push_back(first(z[i]));
//				 }
//				 for (k = 0; k < vec[j].vec.size(); k++) { //	X->y
//					// cout << vec[i][k].ls[0].getCategory() << endl;
//					 for (p = 0; p < symbol.size(); p++) {
//						 GramDataType gramDataTypeTemp = vec[j].vec[k];
//						 gramDataTypeTemp.set_symbol(symbol[p]);
//						 int u;
//						 for ( u = 0; u < temp.size(); u++) { //find repeat grammatical
//							 if (gramDataTypeTemp == temp[u])break;
//						 }
//						 if (u >= temp.size()) {
//#if (TEST&&GRAM_TEST&&CLOSURE_FUNC)
//							 cout <<"grammatical:"<< gram_map_to_string(gramDataTypeTemp.gramName) << " symbol:" << gram_map_to_string(gramDataTypeTemp.symbol)<<"  posi:"<<gramDataTypeTemp.posi<<"--->" << endl;
//							 for (int r = 0; r < gramDataTypeTemp.ls.size(); r++) {
//								 cout <<gram_map_to_string( gramDataTypeTemp.ls[r].getCategory()) << "  ";
//							 }
//							 cout << endl;
//#endif
//							 temp.push_back(gramDataTypeTemp);
//						 }
//						// for (int u = 0;u<)
//						 //temp.push_back()
//						// if(vec[i].vec[k])
//					 
//					//	vec[i].gramName
//				//		 
//						//if(gramArray[vec[i])
//					//	 
//					 }
//
				 }


			 }

	

#if(TEST&&GRAM_TEST&&CLOSURE_FUNC)
		 cout << "----------closure function-----------" << endl;
		 for (int t = 0; t < temp.size(); t++) {
			 cout << gram_map_to_string( temp[t].gramName )<<"  "<<gram_map_to_string(temp[t].symbol)<<"  "<<temp[t].posi<< endl;;
		 }
#endif

	 } while (size != temp.size());
	 
	 return temp;
 }

 inline Gram GrammaticalAnalysis::string_convert_to_gram(const string &str)
 {
	 int i;
	 try {
		 for (i = 0; i < GRAM_STRING_TABLE_MAX; i++)
			 if (GramStringTable[i] == str)break;
		 if (i > GRAM_STRING_TABLE_MAX)
			 throw "error";
	 }
	 catch (const string&) {
		 cerr << "GrammaticalAnalysis string_convert_to_gram index error!" << endl;
		 return e_error;
	 }
	 return static_cast<Gram>(i);
 }

  inline string GrammaticalAnalysis::gram_map_to_string(const Gram&obj)
 {
	 try {
		 if (obj >GRAM_STRING_TABLE_MAX)
			 throw "error";
	 }
	 catch (string) { cerr << "gram_map_to_string index exceed value of max" << endl; }
	 return GramStringTable[obj];
 }
  /*
功能：初始化归约集合
  */
  //inline void GrammaticalAnalysis::init_reduction()
  //{
	 // int i, j;
	 // for (i = 0; i < status.size(); i++) {
		//  for (j = 0; j < status[i].size(); j++) {
		//	  if (status[i][j].getPosi() == status[i][j].ls.size()) {
		//		  redu.push_back(Redu(i, status[i][j].getSymbol(), status[i][j]));
		//	  }
		//  }
	 // }


  //}



inline GramType GrammaticalAnalysis::gram_map_to_gramtype(const Gram & obj)
{
	try {
		if (obj > GRAM_MAX)
			throw "error";
	}
	catch (string) { cerr << "gram_map_to_gramtype index exceed value of max" << endl; }

	return gramArray[obj];
}
inline Gram GrammaticalAnalysis::string_map_to_gram(const string &gram)
{
	int i;
	for (i = 0; i < GRAM_STRING_TABLE_MAX; i++) {
		if (gram == GramStringTable[i])break;
	}
	if (i < GRAM_STRING_TABLE_MAX)return static_cast<Gram>(i);
	return e_error;
}
/*
功能：初始化redu集合并保存到文件
*/
void GrammaticalAnalysis::init_reduction()
{
	int i, j;
	for (i = 0; i < status.size(); i++) {
		for (j = 0; j < status[i].size(); j++) {
			if (status[i][j].getPosi() == status[i][j].ls.size()) {
				redu.push_back(Redu(i, status[i][j].getSymbol(), status[i][j]));
			}
		}

	}
	FILE*file;
	file = fopen("C:\\Users\\THINKPAD\\Desktop\\redu.txt", "w");
	if (file == NULL)return ;
	for (i = 0; i < redu.size(); i++) {
		fprintf(file, "%d %s %s %s %d \n", redu[i].statusNumber,gram_map_to_string( redu[i].symbol).c_str(),gram_map_to_string( redu[i].gram.getGramName()).c_str(),gram_map_to_string( redu[i].gram.getSymbol()).c_str(), redu[i].gram.getPosi());
		fprintf(file, "begin\n");
		for (j = 0; j < redu[i].gram.ls.size(); j++) {
			fprintf(file, "%s \n", gram_map_to_string(redu[i].gram.ls[j].getCategory()).c_str());
		}
		fprintf(file, "end\n");
	}
	fclose(file);

}
ActionStatus GrammaticalAnalysis::action(const int &number, const Gram &symbol,  stack<int>&statusStack,  stack<Gram>&gramStack)
{
	int i, j;
	vector<GramDataType>curStatus = status[number];
	if (GotoTable[number][symbol] != EMPTY) {	//移进
		string str = GotoTable[number][symbol];
		str = str.substr(1, str.size() - 1);
		statusStack.push(atoi(str.c_str()));
		gramStack.push(symbol);
	}

	return ActionStatus();
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
	Grammatical::v_alter_table_add_col_name_def,//56
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

 Gram DataType::getCategory()
 {
	 return category;
	
 }

 bool DataType::operator==(DataType category)
 {
	
		 return this->category == category.category;

 }

 void DataType::set_category(Gram category)
 {
	 this->category = category; 
 }

 bool operator!=(const DataType & category1, const DataType & category2)
 {

		 return category1.category != category2.category;
 }

 bool operator!=(const vector<GramDataType> objA, const vector<GramDataType> objB)
 {
	
		 return !(objA == objB);
	
 }

 bool operator==(const vector<GramDataType> objA, const vector<GramDataType> objB)
 {

		 int i, j;
		 if (objA.size() != objB.size())return false;
		 for (i = 0; i < objA.size(); i++) {
			 if (objA[i] != objB[i])return false;
		 }
		 return true;
	
 }

 bool operator==(GramDataType objA, GramDataType objB)
 {
	
		 bool flag = true;
		 if (objA.ls.size() != objB.ls.size())return false;
		 int objASymbol[GRAM_ENUM_MAX], objBSymbol[GRAM_ENUM_MAX];
		 for (int i = 0; i < GRAM_ENUM_MAX; i++)
			 objASymbol[i] = objBSymbol[i] = 0;

		 for (int i = 0; i <objA.ls.size(); i++) {
			 if (objA.ls[i] != objB.ls[i])return false;
			 //Gram  gramA = const_cast<Gram>(objA.ls[i].getCategory()),GramB= objB.ls[i].getCategory();
			 //objASymbol[static_cast< int>(objA.ls[i].getCategory())] ++;
			 //objBSymbol[static_cast< int>(objB.ls[i].getCategory())] ++;
			 //const Gram tempa =static_cast<int*> (objA.ls[i].getCategory());
			 //(objA.getLs()[i]).getCategory();
			 //vector<DataType>list = objA.getLs();
		 }
		 /*for (int i = 0; i < GRAM_ENUM_MAX; i++) {
		 if (objASymbol[i] != objBSymbol[i])return false;
		 }*/
		 return objA.posi == objB.posi&&objA.symbol == objB.symbol;
	
 }

 bool operator!=(GramDataType objA, GramDataType objB)
 {
	
		 return !(objA == objB);

 }

 bool operator==(const GramType & obj1, const GramType & obj2)
 {
	 if (obj1.vec.size() != obj2.vec.size())return false;
	 return obj1.vec == obj2.vec&&obj1.gramName==obj2.gramName;
 }

 GramType::GramType(initializer_list<GramDataType> list)
 {

		 initializer_list<GramDataType>::iterator begin, end;
		 begin = list.begin();
		 end = list.end();
		 for (; begin != end; begin++) {
			 vec.push_back(*begin);
		 }
	 
 }

 GramType::GramType(GramDataType &obj)
 {
	 vec.push_back(obj);

 }

 void GramType::setGramName(Gram gramName)
 {
	this->gramName = gramName; 
 }

 Gram GramType::getGramName()
 {
	  return gramName; 
 }
GramTokenType::GramTokenType(const GramTokenType & obj)
 {
	 this->gram = obj.gram;
	 this->string = obj.string;
 }

 void GramTokenType::setGram(const Gram & gram)
 {
	 this->gram = gram;
 }

 //void GramTokenType::setGram(const std::string & str)
 //{
	//// setGram(string_convert_to_gram_symbol(str));
 //}

 void GramTokenType::setString(const std::string & string)
 {
	 this->string = string;
 }
 /*
 输入：string中需要包括一个gram与str整合在一起的字符串
 功能：分解出gram与str并赋值
 输出：无
 */
 void GramTokenType::set_value(const std::string &str)
 {
	/* std::string gram, string;
	 int i, lastLeftBracket = 0, lastRightBracket = 0, lastIndex = 0;
	 for (i = 0; i < str.size(); i++) {
		 if (str[i] == '(') {
			gram=str.substr(lastIndex, i - lastIndex);
			 lastIndex = i + 1;
		 }
		 else if (str[i] == ')') {
			 string=str.substr(lastIndex, i - lastIndex);
			 break;
		 }
	 }*/
	 if (str == "e_l_bracket" || str == "e_r_bracket" || str == "e_comma" || str == "e_assignment_symbol") /*为e_r_bracket、e_l_bracket、e_comma、e_assignment_symbol*/{
		 int i;
		 for (i = 0; i < GRAM_STRING_TABLE_MAX; i++)
			 if (GramStringTable[i] == str)break;
		 if (i >= GRAM_STRING_TABLE_MAX) {
			 cerr << "GramTokenType index error " << endl;
		 }
		 gram = static_cast<Gram>(i);
		 return;
	 }
	 else {
		 std::string gramTemp = "", strTemp;
		 int i, j, lastIndex = 0;
		 for (i = 0; i < str.length(); i++) {
			 if (str[i] == ' ') {
				// gramTemp = str.substr(i-lastIndex);
				 lastIndex = i + 1;
				 for (j = 0; j < GRAM_STRING_TABLE_MAX; j++)
					 if (GramStringTable[j] == gramTemp)break;
				 if (i >= GRAM_STRING_TABLE_MAX) {
					 cerr << "GramTokenType index error " << endl;
				 }
				 gram = static_cast<Gram>(j);
				 gramTemp.clear();
				 continue;
			 }
			 gramTemp = gramTemp+ str[i];
		 }
		 string = str.substr(lastIndex,i-lastIndex);

	 }
 }

 Gram GramTokenType::getGram()
 {
	 return gram;
 }

 std::string GramTokenType::getString()
 {
	 return string;
 }

 GramTokenType::GramTokenType(const Gram & gram, const std::string & string)
 {
	 setGram(gram);
	 setString(string);
 }

 GramTokenType::GramTokenType(const std::string & str)
 {
	 /*
	 if (str == "l_bracket" || str == "r_bracket" || str == "comma" || str == "assignment_symbol")
			if (str == "assignment_symbol")
				return "e_equal";
			else
			return "e_" + str;
	 */
	
	 set_value(str);


 }

 //GramTokenType::GramTokenType(const char *chA, const char *chB)
 //{
	// std::string tempA, tempB;
	// while ((*chA != '\0') || (*chB != '\0')) {
	//	 if (*chA != '\0') {
	//		 tempA += *chA;
	//		 chA++;
	//	 }
	//	 if (*chB != '\0') {
	//		 tempB += *chB;
	//		 chB++;
	//	 }

	// }
	// //setGram(gram);
	// //setString(string);
	// GramTokenType(string_convert_to_gram_symbol( tempA,tempB), tempB);
 //}

// inline Gram GramTokenType::string_convert_to_gram_symbol(const std::string &gram,const std::string&str)
// {
//	 int i;
//	 const int keyword= 
//	 /*
//#define KEYWORD "keyword"
//#define NUM "num"
//#define REAL "real"
//#define ID "id"
//#define ADD_SUB_SYMBOL "add_sub_symbol"
//#define MUL_SYMBOL "mul_symbol"
//#define DIV_SYMBOL "div_symbol"
//#define LOGCIAL_SYMBOL "logcial_symbol"
//#define COMPARE_SYMBOL "compare_symbol"
//#define CHARACTER "character"
//#define CHARACTERMATCH "characterMatch"
//#define L_BRACKET "l_bracket"
//#define R_BRACKET "r_bracket"
//#define COMMA "comma"
//#define ASSIGNMENT_SYMBOL "assignment_symbol"
//#define BLANK "blank"
//	 */
//	
//
//	 return ;
// }

 inline int GramTokenType::string_hash(const std::string &str)
 {
	 int sum = 0;
	 int i;
	 for (i = 0; i < str.size(); i++) {
		 sum += str[i];
	 }
	 return sum;
 }

 bool operator==(const GramTokenType & objA, const GramTokenType & objB)
 {
	 return (objA.string == objB.string) && (objA.gram == objB.gram);
 }
  vector<Gram> operator+(vector<Gram> obj1, vector<Gram>obj2) {
	  std::map<Gram,int>mapTemp;
	  vector<Gram>temp = obj1;
	  int i;
	  for (i = 0; i < obj1.size(); i++) {
		  mapTemp[obj1[i]]++;
	  }
	  for (i = 0; i < obj2.size(); i++) {
		  if (mapTemp.count(obj2[i]) <= 0)
			  temp.push_back(obj2[i]);
	  }
	  return temp;
 }
 /* bool operator==(const Gram &gram_one, const Gram &gram_two)
  {
	  return static_cast<int>(gram_one)==static_cast<int>(gram_two);
  }*/
  /*
  功能：保存状态表和跳转表到文件
  */
  bool GrammaticalAnalysis::save_status(vector<vector<GramDataType>>&status, string** GotoTable)
  {
	  int i, j,k;
	  int val;
	  //fstream file= fstream ("status.txt", ios::out);
	  FILE*file = fopen("C:\\Users\\THINKPAD\\Desktop\\status.txt", "w");
	  if (file==NULL)return false;
	  for (i = 0; i < status.size(); i++) {
		  fprintf(file, "status-begin:\n");
		  for (j = 0; j < status[i].size(); j++) {
			  fprintf(file, "gram-begin:\n");
			  fprintf(file, "%s %s %d\n", GramStringTable[status[i][j].getGramName()].c_str(), GramStringTable[status[i][j].getSymbol()].c_str(), status[i][j].getPosi());
			  for (k = 0; k < status[i][j].ls.size(); k++) {
				  fprintf(file,"%s\n", GramStringTable[status[i][j].ls[k].getCategory()].c_str());
			  }
			  fprintf(file, "gram-end:\n");
		  }
		  fprintf(file, "status-end:\n");
	  }
	  fclose(file);
	  file = fopen("C:\\Users\\THINKPAD\\Desktop\\table.txt","w");
	  if (file == NULL)return false;
	  for (i = 0; i < GOTO_TABLE_MAX; i++) {
		  for (j = 0; j < GRAM_ENUM_MAX; j++) {
			  fprintf(file, "%s ", GotoTable[i][j].c_str());
		  }
		  fprintf(file, "\n");
	  }
	  fclose(file);
	  file = fopen("C:\\Users\\THINKPAD\\Desktop\\redu.txt", "w");
	  if (file == NULL)return false;
	  for (i = 0; i < redu.size(); i++) {
		  fprintf(file, "%d %s %s %s %d \n", redu[i].statusNumber,gram_map_to_string( redu[i].symbol).c_str(),gram_map_to_string(redu[i].gram.getGramName()).c_str(),gram_map_to_string( redu[i].gram.getSymbol()).c_str(),redu[i].gram.getPosi());
		  fprintf(file, "begin\n");
		  for (j = 0; j < redu[i].gram.ls.size(); j++) {
			 fprintf(file,"%s \n", gram_map_to_string( redu[i].gram.ls[j].getCategory()).c_str());
		  }
		  fprintf(file, "end\n");
	  }
	  fclose(file);
	  return true;
  }
  /*
  功能：读取状态表和跳转表
  */
  bool GrammaticalAnalysis::read_status(vector<vector<GramDataType>>&status, string **GotoTable)
  {
	  int i, j, k;
	 
	  vector<GramDataType> vec;
	  char ch[CHAR_SIZE];
	  memset(ch, 0, CHAR_SIZE);
	 
	
	  //fstream file= fstream ("status.txt", ios::out);
	  FILE*file = fopen("C:\\Users\\THINKPAD\\Desktop\\status.txt", "r");
	  if (file == NULL)return false;
	  while (!feof(file)) {
		 
		  fscanf(file, "%s", ch);
		  while (strcmp(ch, "status-end:")) {
			  fscanf(file, "%s", ch);
			  if (!strcmp(ch, "status-end:"))break;
			  GramDataType temp;
			  char gramName[BUFF_SIZE], symbol[BUFF_SIZE];
			  /* 变量定义放上面，内存暴涨，未知原因*/
			  fscanf(file, "%s %s %d", gramName, symbol, &temp.posi);
			  temp.setGramName(string_convert_to_gram(gramName));
			  temp.set_symbol(string_convert_to_gram(symbol));
			  while (strcmp(ch, "gram-end:")) {
				  fscanf(file, "%s", ch);
				 // temp.ls.push_back(ch);
				  for (k = 0; k < GRAM_STRING_TABLE_MAX; k++) {
					  if (ch == GramStringTable[k])break;
				  }
				  if (k < GRAM_STRING_TABLE_MAX)temp.ls.push_back(DataType(static_cast<Gram>(k)));
			  }
			  if(temp.ls.size()>0)
			  vec.push_back(temp);//读取
			
		  
		  }
		  if(vec.size()>0)
		  status.push_back(vec);
		  vec.clear();
	  }
	  fclose(file);
	  file = fopen("C:\\Users\\THINKPAD\\Desktop\\table.txt", "r");
	  if (file == NULL)return false;
	  for (i = 0; i < GOTO_TABLE_MAX; i++) {
		 
		  for (j = 0; j < GRAM_ENUM_MAX; j++) {
			  fscanf(file, "%s", ch);
			  GotoTable[i][j] = ch;//读取
				 
		  }
		//  fprintf(file, "\n");
	  }
	  fclose(file);
	  // redu[i].statusNumber, redu[i].symbol, redu[i].gram.getGramName(), redu[i].gram.getSymbol(), redu[i].gram.getPosi());
	 char  reduSymbol[BUFF_SIZE], getGramName[BUFF_SIZE], gramGetSymbol[BUFF_SIZE];
	  Redu temp;
	  int statusNumber, posi;
	  memset(reduSymbol, 0, BUFF_SIZE); memset(getGramName, 0, BUFF_SIZE); memset(gramGetSymbol, 0, BUFF_SIZE);
	  file = fopen("C:\\Users\\THINKPAD\\Desktop\\redu.txt", "r");
	  if (file == NULL)return false;
	  while (!feof(file)) {
		 
		  fscanf(file, "%d %s %s %s %d", &statusNumber, &reduSymbol, &getGramName, &gramGetSymbol, &posi);
		  fscanf(file, "%s", ch);
		  temp.statusNumber = statusNumber;
		  Gram gramReduSymbol = string_map_to_gram(reduSymbol),
			  gramGetGramName=string_map_to_gram(getGramName),
			  gramGetSymbolTemp=string_map_to_gram( gramGetSymbol);		  
		  if (gramReduSymbol == e_error || gramGetGramName == e_error || gramGetSymbolTemp == e_error)continue;
		  temp.statusNumber = statusNumber;
		  temp.symbol = gramReduSymbol;
		  temp.gram.setGramName(gramGetGramName);
		  temp.gram.set_symbol(gramGetSymbolTemp);
		  temp.gram.posi = posi;
		  Gram gram;
		  while (fscanf(file, "%s", ch)&&strcmp( ch, "end")) {
			 temp.gram.ls.push_back( string_map_to_gram(ch));
			  
		  }
		  redu.push_back(temp);
	  }
	  fclose(file);
	  return true;
  }

  Reduction::Reduction(const int &statusNumber, const Gram &symbol, const GramDataType &gram)
  {
	  this->statusNumber = statusNumber;
	  this->symbol = symbol;
	  this->gram = gram;
  }
  /*
  功能：返回栈大小
  */
  template<typename type>
  size_t stack<type>::size()
  {
	  return vec.size();
  }
  /*
  功能：栈是否为空，为空返回true，不为空返回flase
  */
  template<typename type>
  bool stack<type>::empty()
  {
	  return !vec.size();
  }
  /*
  功能：元素入栈
  */
  template<typename type>
  void stack<type>::push(const type& obj)
  {
	  vec.push_back(obj);
  }
  /*
 功能：元素出栈
  */
  template<typename type>
  void stack<type>::pop()
  {
	  type temp = vec[vec.size() - 1];
	  vec.pop_back();
	  return;
  }
  /*
  输入：s为开始的下标，e为s(包括s)后元素数
  功能：返回从s开始的e个元素
  输出：返回元素vector集合
  */
  template<typename type>
  vector<type> stack<type>::top(int s, int e)
  {
	  vector<type>temp;
	  int min = vec.size() > s + e ? s + e : vec.size();
	  for (int i = s; i < min; i++) {
		  temp.push_back(vec[i]);
	  }
	  return temp;
  }
  /*
  功能：返回栈顶元素
  */
  template<typename type>
  type stack<type>::top()
  {
	  try {
		  if (vec.size() <= 0)
			  throw "error";
	  }
	  catch (const char*) {
		  cerr << "stack top index error" << endl;
	  }
	  return vec[vec.size()-1];
  }
  /*
  输入：Num代表元素数
  功能：出栈num个元素
  */
  template<typename type>
  void stack<type>::pop(int num)
  {
	  int min = num > vec.size() ? vec.size() : num;
	  int i;
	  for (i = 0; i < min; i++)
		  vec.pop_back();
	  return;
  }

