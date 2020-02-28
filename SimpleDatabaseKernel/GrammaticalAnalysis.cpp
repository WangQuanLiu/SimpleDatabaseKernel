
#ifndef _GrammaticalAnalysis_
#include"GrammaticalAnalysis.h"
#endif
namespace cfe{
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
	 DataType(e_create_data_def),
	 DataType(e_r_bracket),

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
	DataType(e_int),
	DataType(e_create_data_type_def)

 },
	 GramDataType{
	 DataType(e_id),
	 DataType(e_float),
	 DataType(e_create_data_type_def)

 },
	 GramDataType{
	 DataType(e_id),
	 DataType(e_char),
	 DataType(e_l_bracket),
	 DataType(e_integer),
	 DataType(e_r_bracket),
	 DataType(e_create_data_type_def)
 },

	
};
 GramType Grammatical::v_create_data_type_def{
	//v_create_data_type_def->flaot|int|char(number) 
/*
	v_create_data_type_def->float
	v_create_data_type_def->int
	v_create_data_type_def->char(number)


	/*无e_create_data_type_suffix_def end*/
	 GramDataType{  //repeat
	 DataType(e_comma),
	 DataType(e_id),
	 DataType(e_int),
	 DataType(e_create_data_type_def)
 },

	 GramDataType{
	 DataType(e_comma),
	 DataType(e_id),
	 DataType(e_float),
	 DataType(e_create_data_type_def)
 },

	 GramDataType{
	 DataType(e_comma),
	 DataType(e_id),
	 DataType(e_char),
	 DataType(e_l_bracket),
	 DataType(e_integer),
	 DataType(e_r_bracket),
	 DataType(e_create_data_type_def)
 },
	 GramDataType{
	 DataType(e_empty)
 },
	 GramDataType{
	 DataType(e_create_data_type_def),
	 DataType(e_create_data_type_def)
 }
};
  GramType Grammatical::v_create_data_type_suffix_def{
	

};
 GramType Grammatical::v_constraint_def{
	//v_constraint_def -> [ v_primary_def ] {v_for_che_uni_def}   [] representive optional
	/*
	v_constraint_def -> v_primary_def
	v_constraint_def->v_for_che_uni_def
	v_constraint_def->ε
	v_constraint_def->v_primary_def for_che_uni_def
	*/
};
 GramType Grammatical::v_primary_def {
	/*
	
	v_primary_def ->primary key (col_name_rep_def)
	primary_def->ε
	*/

};
 GramType Grammatical::v_for_che_uni_def{
	/*
	v_for_che_uni_def->v_foreign_def v_for_che_uni_def
	v_for_che_uni_def->v_check_def v_for_che_uni_def
	v_for_che_uni_def->v_unique_def v_for_che_uni_def
	v_for_che_uni_def->ε
	*/
};
 GramType Grammatical::v_col_name_rep_def{

	/*
	v_col_name_rep_def -> col_name
	v_col_name_rep_def->col_name,v_col_name_rep_def
	*/
	GramDataType{
	DataType(e_comma),
	DataType(e_id),
	DataType(e_col_name_rep_def)
	},
	 GramDataType{
	 DataType(e_empty)
 },

};
 GramType Grammatical::v_foreign_def{


	/*
	v_foreign_def->foreign key ( col_name_rep_def) references table_name ( col_name_rep_def)
	v_foreign_def->foreign key ( col_name_rep_def) references table_name ( col_name_rep_def),v_foreign_def
	*/
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
};
 GramType Grammatical::v_unique_def{
	/*
	v_unique_def->unique ( col_name_rep_def)
	v_unique_def->unique (col_name_erp_def),unique_def
	*/
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
//GramDataType{
//	DataType(e_equal)
//}
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
}/*,
GramDataType{
	DataType(e_not)
}*/
};
 GramType Grammatical::v_gather_fuc_def{
	/*
	v_gather_fuc_def->sum
	v_gather_fuc_def->avg
	v_gather_fuc_def->count
	v_gather_fuc_def->min
	v_gather_fuc_def->max
	*/
	
};
 GramType Grammatical::v_int_real_col_name_def{
	/*
	v_int_real_col_name_def -> int
	v_int_real_col_name_def->flaot
	v_int_real_col_name->col_name
	*/
	
};
 GramType Grammatical::v_int_real_col_name_rep_def{
	/*
	v_int_real_col_name_rep_def ->v_int_real_col_name_def,v_int_rel_col_name_rep_def
	v_int_real_col_name_rep_def->v_int_real_col_name_def
	*/
	 GramDataType{
	 DataType(e_comma),
	 DataType(e_integer),
	
	 DataType(e_int_real_col_name_rep_def)
	},
	 GramDataType{
	 DataType(e_comma),
	 DataType(e_real),
	
	 DataType(e_int_real_col_name_rep_def)
 },
	 GramDataType{
	 DataType(e_comma),
	 DataType(e_str),
	 DataType(e_int_real_col_name_rep_def)
	},
	 GramDataType{
	 DataType(e_empty)

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
	DataType(e_integer),
	DataType(e_where_algorithm_operator_def)
},

GramDataType{
	DataType(e_real),
	DataType(e_where_algorithm_operator_def)
},

GramDataType{
	DataType(e_id),
	DataType(e_where_algorithm_operator_def)
},
GramDataType{
	 DataType(e_str),
	 DataType(e_where_algorithm_operator_def)
	 },
GramDataType{
	DataType(e_empty)
}
};
  GramType Grammatical::v_where_algorithm_operator_or_string_def{
	/*
	v_where_algorithm_operator_or_string_def->v_where_algorithm_opeartor_def
	v_where_algorithm_operator_or_string_def->string
	*/

	
	


};
 GramType Grammatical::v_where_compare_def{
	/*
	v_where_compare_def->v_where_algorithm_operator_or_string_def compare v_where_algorithm_operator_or_string_def
	*/
	GramDataType{
	 DataType(e_where_algorithm_operator_def),
	DataType(e_compare_def),
	 DataType(e_where_algorithm_operator_def),
	},
	 GramDataType{
	 DataType(e_id),
	 DataType(e_compare_def),
	 DataType(e_where_algorithm_operator_def),
 },
	 GramDataType{
	 DataType(e_integer),
	 DataType(e_compare_def),
	 DataType(e_where_algorithm_operator_def),
 },
	 GramDataType{
	 DataType(e_real),
	 DataType(e_compare_def),
	 DataType(e_where_algorithm_operator_def),
 },
	 GramDataType{
	 DataType(e_str),
	 DataType(e_compare_def),
	 DataType(e_where_algorithm_operator_def),
 },
	 GramDataType{
	 DataType(e_where_algorithm_operator_def),
	 DataType(e_equal),
	 DataType(e_where_algorithm_operator_def),
 },
	 GramDataType{
	 DataType(e_id),
	 DataType(e_equal),
	 DataType(e_where_algorithm_operator_def),
 },
	 GramDataType{
	 DataType(e_integer),
	 DataType(e_equal),
	 DataType(e_where_algorithm_operator_def),
 },
	 GramDataType{
	 DataType(e_real),
	 DataType(e_equal),
	 DataType(e_where_algorithm_operator_def),
 },
	 GramDataType{
	 DataType(e_str),
	 DataType(e_equal),
	 DataType(e_where_algorithm_operator_def),
 },
};
 GramType Grammatical::v_where_compare_or_string_match_def{
	/*
	v_where_compare_or_string_match_def-> v_where_compare_def
	v_where_compare_or_string_match_def-> col_name like string_match
	*/
	/*GramDataType{
	DataType(e_where_compare_def)
	},
	GramDataType{
	DataType(e_id),
	DataType(e_like),
	DataType(e_strMatch)
	}*/

};
 GramType Grammatical::v_logic_and_where_compare_string_match_def{
	/*
	v_logic_and_where_compare_string_match_def->logic v_where_compare_or_string_match_def
	v_logic_and_where_compare_string_match_def->logic v_where_compare_or_string_match_def v_logic_and_where_compare_string_match_def
	v_logic_and_where_compare_string_match_def->logic ( v_where_compare_or_string_match_def logic_and_where_compare_string_match_def)
	v_logic_and_where_compare_string_match_def->ε
	*/
	/*GramDataType{
	DataType(e_logic_def),
	DataType(e_where_compare_or_string_match_def),
	},*/
	GramDataType{
	DataType(e_logic_def),
	DataType(e_where_compare_def),
	DataType(e_logic_and_where_compare_string_match_def)
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
	DataType(e_where_compare_def),
	DataType(e_logic_and_where_compare_string_match_def)
	},

};
 GramType Grammatical::v_where_def{
	/*
	v_where_def->where v_where_logic_def
	*/
	GramDataType{
	DataType(e_where),
	DataType(e_where_logic_def),
	},
	 GramDataType{
	 DataType(e_empty),
	
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
};
  GramType Grammatical::v_group_def{
	/*
	v_group_def->group by col_name
	v_group_def->group by col_name v_comma_and_col_name_def
	
	*/

};
 GramType Grammatical:: v_having_def{

	/*
	v_having_def-> having v_where_logic_def
	
	*/
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
};
 GramType Grammatical::v_connect_mulop_def{
	/*
	v_connect_mulop_def->mulop v_int_real_col_name_def
	v_connect_mulop_def->v_connect_addop
	v_connect_mulop_def->mulop ( v_int_real_col_name_def )
	v_connect_mulop_def -> ε
	*/
};
 GramType Grammatical::v_connect_algorithm_operator_def{
	/*
	v_connect_algorithm_operator_def->( v_int_real_col_name_def v_connect_addop_def )
	v_connect_algorithm_operator_def->v_int_real_col_name_def v_connect_addop_def
	*/
};
 GramType Grammatical::v_connect_algorithm_operator_or_string_def{
	/*
	v_connect_algorithm_operator_or_string_def->v_connect_algorithm_operator_def
	v_connect_algorithm_operator_or_string_def->string
	
	*/
	
};
 GramType Grammatical::v_connect_compare_def{
	/*
	v_connect_compare_def->v_connect_algorithm_operator_or_string compare v_connect_algorithm_operator_or_string 
	*/
};
 GramType Grammatical::v_connect_compare_or_str_match_def{
	/*
	v_connect_compare_or_str_match_def->v_connect_compare_def
	v_connect_compare_or_str_match_def->col_name like string_match
	*/
};
 GramType Grammatical::v_logic_connect_compare_or_str_match_def{
	/*
	v_logic_connect_compare_or_str_match_def->logic v_connect_compare_or_str_match_def v_logic_connect_compare_or_str_match_def
	v_logic_connect_compare_or_str_match_def->ε
	*/
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
};
 GramType Grammatical::v_constraint_group_def{
	/*
	v_constraint_group_def->v_group_def
	v_constraint_group_def->v_group_def v_constriant_having_def
	v_constraint_group_def->v_constriant_having_def
	
	*/
};
 GramType Grammatical::v_select_connect_def{
	/*
	v_select_connect_def->*
	v_select_connect_def->v_select_operator_def
	*/
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
	 DataType(e_comma),
	 DataType(e_id),
	 DataType(e_table_name_def)
 },
	 GramDataType{
	 DataType(e_empty)
 },
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
	 DataType(e_mulop),
	 DataType(e_from),
	 DataType(e_id),
	 DataType(e_table_name_def),
	 DataType(e_where_def)
	 },
	 GramDataType{
	 DataType(e_select),
	 DataType(e_distance),
	 DataType(e_id),
	 DataType(e_col_name_rep_def),
	 DataType(e_from),
	 DataType(e_id),
	 DataType(e_table_name_def),
	 DataType(e_where_def)
 },


	 GramDataType{
	 DataType(e_select),
	 DataType(e_mulop),
	 DataType(e_from),
	 DataType(e_id),
	 DataType(e_table_name_def),
	 DataType(e_where_def)
 },
	 GramDataType{
	 DataType(e_select),
	 DataType(e_id),
	 DataType(e_col_name_rep_def),
	 DataType(e_from),
	 DataType(e_id),
	 DataType(e_table_name_def),
	 DataType(e_where_def)
 },
};
 GramType Grammatical::v_create_database_def{
	/*
	v_create_database_def-> create database database_name
	
	*/
	GramDataType{
	DataType(e_create),
	DataType(e_database),
	DataType(e_id),

	},

};
 GramType Grammatical::v_use_database_def{
	 /*
	 v_use_database_def->use database_name
	 */
	GramDataType{
	DataType(e_use),
	DataType(e_id),
	
}

};
 GramType Grammatical::v_delete_element_def{
	/*
	v_delete_element_def->delete from table_name
	
	*/
	/*GramDataType{
	DataType(e_delete),
	DataType(e_from),
	DataType(e_id),
	 DataType(e_where_def),
	},*/
	 GramDataType{
	 DataType(e_delete),
	 DataType(e_from),
	 DataType(e_id),
	 DataType(e_where_def),
	
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
	}
};
 GramType Grammatical::v_alter_table_add_col_name_def{
	/*
	v_alter_table_col_name_def -> alter table table_name add column col_name v_int_real_col_name
	
	*/
};
 GramType Grammatical::v_alter_table_drop_col_name_def{
	 /*
	 v_alter_table_drop_col_name_def->alter table table_name drop col_name
	 */
};
 GramType Grammatical::v_insert_def{
	 /*
	 v_insert_def->insert into table_name ( v_col_name_rep_def ) values ( v_int_real_col_name_rep_def)
	 */
	 GramDataType{
	  DataType(e_insert),
	  DataType(e_into),
	  DataType(e_id),
	  DataType(e_values),
	  DataType(e_l_bracket),
	  DataType(e_integer),
	  DataType(e_int_real_col_name_rep_def),
	  DataType(e_r_bracket)
 },
	 GramDataType{
	 DataType(e_insert),
	 DataType(e_into),
	 DataType(e_id),
	 DataType(e_values),
	 DataType(e_l_bracket),
	 DataType(e_real),
	 DataType(e_int_real_col_name_rep_def),
	 DataType(e_r_bracket)
 },
	 GramDataType{
	 DataType(e_insert),
	 DataType(e_into),
	 DataType(e_id),
	 DataType(e_values),
	 DataType(e_l_bracket),
	 DataType(e_str),
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
	 /*add begin*/
	GramDataType{
	DataType(e_addop),
	DataType(e_id),
	 DataType(e_update_addop_def)
	},

	 GramDataType{
	 DataType(e_addop),
	 DataType(e_real),
	 DataType(e_update_addop_def)
 },
	 GramDataType{
	 DataType(e_addop),
	 DataType(e_integer),
	 DataType(e_update_addop_def)
 },

	 /*add end*/
	GramDataType{
	DataType(e_subop),
	DataType(e_real),
	 DataType(e_update_addop_def)
	},
	 GramDataType{
	 DataType(e_subop),
	 DataType(e_integer),
	 DataType(e_update_addop_def)
 },
	 GramDataType{
	 DataType(e_subop),
	 DataType(e_id),
	 DataType(e_update_addop_def)
 },

	 /*sub end*/
	 GramDataType{
	 DataType(e_mulop),
	 DataType(e_real),
	 DataType(e_update_addop_def)
 },
	 GramDataType{
	 DataType(e_mulop),
	 DataType(e_integer),
	 DataType(e_update_addop_def)
 },
	 GramDataType{
	 DataType(e_mulop),
	 DataType(e_id),
	 DataType(e_update_addop_def)
 },
	/*mulop end*/
	 GramDataType{
	 DataType(e_divop),
	 DataType(e_real),
	 DataType(e_update_addop_def)
 },
	 GramDataType{
	 DataType(e_divop),
	 DataType(e_integer),
	 DataType(e_update_addop_def)
 },
	 GramDataType{
	 DataType(e_divop),
	 DataType(e_id),
	 DataType(e_update_addop_def)
 },
	 /*divop end*/
	GramDataType{
	DataType(e_empty)
	},
	
};

  GramType Grammatical::v_update_mulop_def{
	/*
	v_update_mulop_def-> mulop ( v_int_real_col_name v_update_addop)
	v_update_mulop_def-> mulop v_int_real_col_name v_update_addop
	v_update_mulop_def-> v_update_addop_def
	v_update_mulop_def->ε
	*/
	
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
	DataType(e_str),
	DataType(e_where_def)
	},
	 GramDataType{
	 DataType(e_update),
	 DataType(e_id),
	 DataType(e_set),
	 DataType(e_id),
	 DataType(e_equal),
	 DataType(e_real),
	 DataType(e_update_addop_def),
	 DataType(e_where_def)
 },
	 GramDataType{
	 DataType(e_update),
	 DataType(e_id),
	 DataType(e_set),
	 DataType(e_id),
	 DataType(e_equal),
	 DataType(e_integer),
	 DataType(e_update_addop_def),
	 DataType(e_where_def)
 },
	 GramDataType{
	 DataType(e_update),
	 DataType(e_id),
	 DataType(e_set),
	 DataType(e_id),
	 DataType(e_equal),
	 DataType(e_id),
	 DataType(e_update_addop_def),
	 DataType(e_where_def)
 },
};
 GramType Grammatical::v_create_view_def{
	/*
	v_create_view_def->create view view_name as v_select_def
	*/
	
};
 GramType Grammatical::v_drop_view_def{
	 /*
	 v_drop_view_def->drop view view_name
	 */
	 GramDataType{
	 DataType(e_drop),
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
	DataType(e_r_bracket),
	
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
	DataType(e_on),
	DataType(e_id)
	}
};
 GramType Grammatical::v_drop_database_def{
	 GramDataType{
	 DataType(e_drop),
	 DataType(e_id),
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
		init();
}
void GrammaticalAnalysis::run()
{
	fstream statusFile(CONFIGURATION_FILE_HOME("status.txt"), ios::in);
	fstream gotoTableFile (CONFIGURATION_FILE_HOME("table.txt"), ios::in);
	fstream reduFile(CONFIGURATION_FILE_HOME("redu.txt"), ios::in);
	if (!statusFile || !gotoTableFile) {
		GramType gramTypeTemp = gramArray[0];
		for (int i = 0; i < gramTypeTemp.vec.size(); i++) {
			gramTypeTemp.vec[i].symbol = e_eof;
		}
		status = items(gramTypeTemp);
		save_file();
	}
	else {
		read_file();
	}
	check_grammatical();
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
	for (i = 0; i < GRAM_MAX; i++) {
		gramArray[i].setGramName(static_cast<Gram>(i));
		for (int j = 0; j < gramArray[i].vec.size(); j++) {
			gramArray[i].vec[j].setGramName(static_cast<Gram>(i));
		}
	}

	generate_firstSet();
}
bool GrammaticalAnalysis::check_grammatical()
{
	stack<int>statusStack;
	stack<Gram>gramStack;
	vector<GramDataType>curStatus = status[0];
	statusStack.push(0);
	gramStack.push(e_s);
	GramTokenType temp;
	string str;
	int lastLineNum = 0;
	while (file->get_token_size()>0) {
		 str = file->get_token();
		if (!strcmp(str.c_str() , ""))continue;
		lastLineNum = file->get_cur_line();
		temp = string_convert_to_GramToken(str);
		if (action(temp.getGram(), statusStack, gramStack) == error) {
			str = get_original_string(str);
			cout <<"line: "<< lastLineNum <<" " << str << " error!" << endl;
			break;
		}
	}
	if (gramStack.size() > 1) {
		str = get_original_string(str);
		cout << "line: " << lastLineNum << " " << str << " error!" << endl;
	}
	return false;
}
void GrammaticalAnalysis::print(int GotoTable[GOTO_TABLE_MAX][GRAM_ENUM_MAX])
{
	cout << "-------------print(int GotoTable[GRAM_MAX][GRAM_ENUM_MAX])---------------" << endl;
	int i,k,l;
	for (i = 0; i < GOTO_TABLE_MAX; i++) {
		vector<GramDataType>temp = status[i];
		cout << "status:" << i << "-->" << endl;
				

		for (k = 0; k < temp.size(); k++) {
			cout <<"gram->"<< gram_map_to_string(temp[k].getGramName()) << "  symbol  "/* <<gram_map_to_string( temp[k].symbol)*/ <<"	"<<gram_map_to_string(static_cast<Gram>(k))<< "  posi " << temp[k].posi << endl;
					for (l = 0; l < temp[k].ls.size(); l++)
						cout <<gram_map_to_string( temp[k].ls[l].getCategory() )<< "	";	
					cout << endl;
				}
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
	//char ch[BUFF_SIZE];
		vector<GramDataType>temp = closure(obj.vec);
			vec.push_back(temp);

#if (TEST&&GRAM_TEST&&ITEMS_FUNC)
	cout << "-----init----" << endl;
	for (i = 0; i < vec.size(); i++) {
		for (j = 0; j < vec[i].size();j++)
		cout << gram_map_to_string(vec[i][j].gramName)<<"  "<<vec[i][j].getSymbol()<<"  "<<vec[i][j].posi << endl;//BUG position add 2020/1/21
	}
#endif
	int size;
	map<Gram, int>numMap;
//do {
		size = vec.size();
		for (i = 0; i < vec.size(); i++) {
			for (k = 0; k < GRAM_ENUM_MAX; k++) {
				
				vector<GramDataType>temp = Goto(vec[i], static_cast<Gram>(k));
				if (temp.size() <= 0)continue;
				
				char ch[BUFF_SIZE];
				bool flag = false;
				string str = is_grammatical(static_cast<Gram>(k)) ? "s" : "g";
				for (t = 0; t < vec.size(); t++) {
					//if (vec[t].size() != temp.size())break;

					if (vec[t] == temp) {	//有相同的文法				
						str = str + _itoa(static_cast<int>(t), ch, 10);
						GotoTable[i][k] = str;
						flag = true;
						break;
					}
				}
		
				if (t >= vec.size()) {//无相同的文法
					
					cout << "status:" << i << "->" << gram_map_to_string(static_cast<Gram>(k))<<"  ";
					str = str + _itoa(static_cast<int>(vec.size()), ch, 10);
					GotoTable[i][k] = str;					
					cout << vec.size() << endl;
 					vec.push_back(temp);
					for (t = 0; t < temp.size(); t++) {//添加归约
						if (temp[t].getPosi() == 0 && numMap.count(temp[t].getGramName()) == 0) {
							numMap[temp[t].getGramName()] = vec.size() - 1;
						}
						if (temp[t].getPosi() == temp[t].ls.size()) {
							redu.push_back(Redu(numMap[temp[t].getGramName()],  static_cast<Gram>(k), temp[t]));//vec.size 改成i
						}
					}
				}
			
				str.clear();
			}

		}
//} while (size != vec.size());//add at  2020/1/13 21:33
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
		if ((temp.posi < temp.ls.size())) {
			if ((temp.ls[temp.posi].getCategory() == gram)) {
				//if (gram == e_empty)//add at 2020/2/14 15:19
				//	vec.push_back(temp);
				vec.push_back(temp + 1);

			}
			else {
			//	vector<Gram>gramTemp = first(temp.ls[temp.posi].getCategory()); //delete at 2020/2/12 20.45
				vector<Gram>gramTemp = first_set[temp.ls[temp.posi].getCategory()];
				int j;
				for (j = 0; j < gramTemp.size(); j++) {
					if (gram == gramTemp[j])
						vec.push_back(temp + 1);
				}
			}
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
void GrammaticalAnalysis::generate_firstSet()
{
	int i;
	bool visit[GRAM_ENUM_MAX]{ false };
	for (i = 0; i < GRAM_ENUM_MAX; i++) {
		first(static_cast<Gram>(i),visit);
		memset(visit, 0, GRAM_ENUM_MAX);
	}

}
vector<Gram> GrammaticalAnalysis::first(const Gram gram, bool visit[GRAM_ENUM_MAX]) {

	if (first_set[gram].size() >0)return first_set[gram];
	vector<Gram>gloFirstSet{};
	vector<Gram>tempFirstSet{};
	vector<DataType>list;
	if (is_grammatical(gram) || visit[gram]) {
		first_set[gram] = vector<Gram>{ gram };
		return vector<Gram>{ gram };
	}
	int i, size = 0, k;
	bool flag = true, empty;
	GramType gramTypeTemp = gramArray[gram];
	visit[gram] = true;
	for (i = 0; i < gramTypeTemp.vec.size(); i++) {
		list = gramTypeTemp.vec[i].ls;
		
		k = 0; flag = true;
		while (flag == true && k < list.size()) {
			if (first_set[list[k].getCategory()].size() > 0) {
				tempFirstSet = first_set[list[k].getCategory()];
			}
			else {
				tempFirstSet = first(list[k].getCategory(),visit);
				first_set[list[k].getCategory()] = tempFirstSet;
			}
			empty = true;
			vector<Gram>::iterator begin(tempFirstSet.begin()), end;
			end = tempFirstSet.end();
			while (begin != end) {
				if (*begin == e_empty) {
					empty = false;
					tempFirstSet.erase(begin);
					break;
				}
				begin++;
			}
			
			gloFirstSet = gloFirstSet + tempFirstSet;
			if (empty)flag = false;
			k++;
		}
		if (flag)gloFirstSet.push_back(e_empty);
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
	// temp=get_derived_grammar(obj[0].)
	 int size,i,k,p,u; //保存容器大小
do {
		 size = temp.size();
		 for (i = 0; i < temp.size(); i++) {
			 if (temp[i].posi >= temp[i].ls.size())continue;//2020/1/8 21:23 add
			 GramType vec;
			 if (!is_grammatical(temp[i].ls[temp[i].posi].getCategory())) {//文法
				 vec = gramArray[temp[i].ls[temp[i].posi].getCategory()];

				 Gram z;
				 vector<Gram>gramSymbol;
				if (temp[i].posi + 1 < temp[i].ls.size()) {
					z = temp[i].ls[temp[i].posi + 1].getCategory();
					//gramSymbol = first(z); //delete at 2020/2/12 20.43
					gramSymbol = gramSymbol + first_set[z];
				}
				else {
					//gramSymbol = gramSymbol + first(temp[i].getSymbol()); //delete at 2020/2/12/20.44
					gramSymbol = gramSymbol + first_set[temp[i].getSymbol()];
				}
				//if(temp[i].posi==0) //2020-1-27
				//gramSymbol = gramSymbol + first(temp[i].getSymbol());
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
	file = fopen(CONFIGURATION_FILE_HOME("redu.txt").c_str(), "w");
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
ActionStatus GrammaticalAnalysis::action( const Gram &symbol,  stack<int>&statusStack,  stack<Gram>&gramStack)
{
	bool flag = true;
	ActionStatus act=error;
	if (GotoTable[statusStack.top()][symbol] != EMPTY) {	//移进
		 act = shift;
		 shift_in(symbol, statusStack, gramStack);
	}
	while (flag) {
		flag = false;
		if (reduction(symbol, statusStack, gramStack)) {
			act = reduc;
			flag = true;
		}		
	}
	if (gramStack.top()==e_s) {
		statusStack.pop(statusStack.size());
		gramStack.pop(gramStack.size());
		statusStack.push(0);
		gramStack.push(e_s);
		act = acc;
	}
	return act;
}
string GrammaticalAnalysis::get_next_token()
{
	string temp;
	bool tokenFlag = true;
	temp = file->get_token();
	while (tokenFlag&&file->get_token_size() >= 1) {
		if (temp == ""&&file->get_token_size() >= 1) {
			temp = file->get_token();
		}
		else {
			tokenFlag = false;
		}
	}
	if (strcmp(temp.c_str(),""))
		file->roll_back();
	else
		return "";
	return temp;
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
   Grammatical::v_drop_index_def,//65
   Grammatical::v_drop_database_def
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

		 int i;
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
		 for (int i = 0; i <objA.ls.size(); i++) {
			 if (objA.ls[i] != objB.ls[i])return false;
		 }
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
	 if (!strcmp(str.c_str(), "e_l_bracket" )|| !strcmp(str.c_str(), "e_r_bracket") ||
		 !strcmp( str.c_str() , "e_comma" )|| !strcmp(str.c_str(), "e_equal")) /*为e_r_bracket、e_l_bracket、e_comma、e_assignment_symbol*/{
		 int i;
		 for (i = 0; i < GRAM_STRING_TABLE_MAX; i++)
			 if (GramStringTable[i] == str)break;
		 if (i >= GRAM_STRING_TABLE_MAX) {
			 cerr << "GramTokenType index error " << endl;
		 }
		 this->gram = static_cast<Gram>(i);
		 this->string = str;
		 return;
	 }
	 else {
		 std::string gramTemp = "", strTemp;
		 int i, j, lastIndex = 0;
		 for (i = 0; i < str.length(); i++) {
			 if (str[i] == ' ') {
				 lastIndex = i + 1;
				 for (j = 0; j < GRAM_STRING_TABLE_MAX; j++)
					 if ( GramStringTable[j]== gramTemp.c_str())break;
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
	 set_value(str);
 }

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

  dbm::AttributeType syntaxTree::gram_data_type_convert_to_AttributeType(Gram gram)
  {
	  if (gram == e_integer) {
		  return dbm::a_int;
	  }
	  else if (gram == e_float) {
		  return dbm::a_flaot;
	  }
	  else if (gram == e_str) {
		  return dbm::a_string;
	  }
	  return dbm::a_error;
  }

  /*
  功能：保存状态表和跳转表到文件
  */
  bool GrammaticalAnalysis::save_file()
  {
	  return save_redu()&&save_GotoTable()&&save_status();
  }
  bool GrammaticalAnalysis::save_status()
  {
	  int i, j, k;
	  FILE*file = fopen(CONFIGURATION_FILE_HOME("status.txt").c_str(), "w");
	  if (file == NULL)return false;
	  for (i = 0; i < status.size(); i++) {
		  fprintf(file, "status-begin:\n");
		  for (j = 0; j < status[i].size(); j++) {
			  fprintf(file, "gram-begin:\n");
			  fprintf(file, "%s %s %d\n", GramStringTable[status[i][j].getGramName()].c_str(), GramStringTable[status[i][j].getSymbol()].c_str(), status[i][j].getPosi());
			  for (k = 0; k < status[i][j].ls.size(); k++) {
				  fprintf(file, "%s\n", GramStringTable[status[i][j].ls[k].getCategory()].c_str());
			  }
			  fprintf(file, "gram-end:\n");
		  }
		  fprintf(file, "status-end:\n");
	  }
	  fclose(file);
	  return true;
  }
  bool GrammaticalAnalysis::save_GotoTable()
  {
	  int i, j;
	  FILE* file = fopen( CONFIGURATION_FILE_HOME("table.txt").c_str(), "w");
	  if (file == NULL)return false;
	  for (i = 0; i < GOTO_TABLE_MAX; i++) {
		  for (j = 0; j < GRAM_ENUM_MAX; j++) {
			  fprintf(file, "%s ", GotoTable[i][j].c_str());
		  }
		  fprintf(file, "\n");
	  }
	  fclose(file);
	  return true;
  }
  bool GrammaticalAnalysis::save_redu()
  {
	  int i, j;
	  FILE*file = fopen(CONFIGURATION_FILE_HOME("redu.txt").c_str(), "w");
	  if (file == NULL)return false;
	  for (i = 0; i < redu.size(); i++) {
		  fprintf(file, "%d %s %s %s %d \n", redu[i].statusNumber, gram_map_to_string(redu[i].symbol).c_str(), gram_map_to_string(redu[i].gram.getGramName()).c_str(), gram_map_to_string(redu[i].gram.getSymbol()).c_str(), redu[i].gram.getPosi());
		  fprintf(file, "begin\n");
		  for (j = 0; j < redu[i].gram.ls.size(); j++) {
			  fprintf(file, "%s \n", gram_map_to_string(redu[i].gram.ls[j].getCategory()).c_str());
		  }
		  fprintf(file, "end\n");
	  }
	  fclose(file);
	  return true;
  }
  /*
  功能：读取状态表和跳转表
  */
  bool GrammaticalAnalysis::read_status()
  {
	  int  k;
	  vector<GramDataType> vec;
	  char ch[CHAR_SIZE];
	  memset(ch, 0, CHAR_SIZE);
	  FILE*file = fopen(CONFIGURATION_FILE_HOME("status.txt").c_str(), "r");
	  if (file == NULL)return false;
	  while (!feof(file)) {
		  fscanf(file, "%s", ch);
		  while (strcmp(ch, "status-end:")) {
			  fscanf(file, "%s", ch);
			  if (!strcmp(ch, "status-end:"))break;
			  GramDataType temp;
			  char gramName[BUFF_SIZE], symbol[BUFF_SIZE];
			  
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
	 
	  
	  return true;
  }

  bool GrammaticalAnalysis::read_GotoTable()
  {
	  int i, j;
	  char ch[CHAR_SIZE];
	  memset(ch, 0, CHAR_SIZE);
	 FILE* file = fopen(CONFIGURATION_FILE_HOME("table.txt").c_str(), "r");
	  if (file == NULL)return false;
	  for (i = 0; i < GOTO_TABLE_MAX; i++) {
		  for (j = 0; j < GRAM_ENUM_MAX; j++) {
			  fscanf(file, "%s", ch);
			  GotoTable[i][j] = ch;//读取 
		  }
	  }
	  fclose(file);
	  return true;
  }

  bool GrammaticalAnalysis::read_redu()
  {
	  int statusNumber, posi;
	  char ch[CHAR_SIZE];
	  memset(ch, 0, CHAR_SIZE);
	  FILE* file = fopen(CONFIGURATION_FILE_HOME("redu.txt").c_str(), "r");
	  if (file == NULL)return false;
	  while (!feof(file)) {
		  Redu temp;
	
		  char  reduSymbol[BUFF_SIZE], getGramName[BUFF_SIZE], gramGetSymbol[BUFF_SIZE];
		  Gram gramReduSymbol, gramGetGramName, gramGetSymbolTemp;
		  
		  fscanf(file, "%d %s %s %s %d", &statusNumber, &reduSymbol, &getGramName, &gramGetSymbol, &posi);
		  fscanf(file, "%s", ch);
		  temp.statusNumber = statusNumber;
		  /*Gram */gramReduSymbol = string_map_to_gram(reduSymbol),
			  gramGetGramName = string_map_to_gram(getGramName),
			  gramGetSymbolTemp = string_map_to_gram(gramGetSymbol);
		  if (gramReduSymbol == e_error || gramGetGramName == e_error || gramGetSymbolTemp == e_error)continue;
		  temp.statusNumber = statusNumber;
		  temp.symbol = gramReduSymbol;
		  temp.gram.setGramName(gramGetGramName);
		  temp.gram.set_symbol(gramGetSymbolTemp);
		  temp.gram.posi = posi;

		  while (fscanf(file, "%s", ch) && strcmp(ch, "end")) {
			  temp.gram.ls.push_back(string_map_to_gram(ch));

		  }
		  redu.push_back(temp);
	  }
	  fclose(file);
	  return true;
  }

  bool GrammaticalAnalysis::read_file()
  {
	  return read_status()&&read_redu()&&read_GotoTable();
  }

  string GrammaticalAnalysis::get_original_string( string str)
  {
	  if (str == "e_l_bracket") {
		  str == "(";
	  }
	  else if (str == "e_r_bracket") {
		  str = ")";
	  }
	  else if (str == "e_equal") {
		  str = "=";
	  }
	  else if (str == "e_comma") {
		  str = ",";
	  }
	  else {
		  int i;
		  for (i = 0; i < str.size(); i++)
			  if (str[i] == ' ')break;
		  str = str.substr(i, str.size() - i);
	  }
	  return str;
  }

  bool GrammaticalAnalysis::reduction(const Gram&symbol,stack<int>& statusStack, stack<Gram>& gramStack)
  {
	  int i,j,k,reduNum;
	  bool flag = false;
	  for (i = gramStack.size() - 1; i >= 1; i--) {
		  	GramDataType temp;
		  	vector<Gram>vec = gramStack.top(i);
		  	for (j = 0; j < redu.size(); j++) {
		  		if (vec.size() != redu[j].gram.ls.size())continue;
		  		for (k = 0; k < vec.size(); k++) {
		  			if (vec[k] != redu[j].gram.ls[k])break;
		  		}
		  		if (k >= vec.size()&&(redu[j].gram.ls.size()==vec.size()|| redu[j].gram.getSymbol() == symbol) /*&& redu[j].symbol == symbol*/) {
		  			flag = true;
		  			gramStack.pop(i);//出栈i+1个元素
		  			statusStack.pop(i);//出栈i+1个元素		
		  			statusStack.push(redu[j].statusNumber); 
					reduNum = k;
					cout << j << endl;
		  			gramStack.push(redu[j].gram.getGramName());
		  			i = gramStack.size() - 1;
		  				cout << "归约" << endl;
		  				break;
		  		}

		  	}
		  }

	  if (flag) {
		  string str = GotoTable[statusStack.top()][static_cast<int>(gramStack.top())];
		  statusStack.pop();
		  str = str.substr(1, str.size() - 1);
		  statusStack.push(atoi(str.c_str()));
	  }
	  reuction_empty(statusStack, gramStack);
	  return flag;
  }

  bool GrammaticalAnalysis::shift_in(const Gram & symbol, stack<int>& statusStack, stack<Gram>& gramStack)
  {

	  string str = GotoTable[statusStack.top()][symbol];
	  bool nextShift = false;
	  str = str.substr(1, str.size() - 1);
	  statusStack.push(atoi(str.c_str()));
	  gramStack.push(symbol);
	  cout << "移进" << endl;
	  reuction_empty(statusStack, gramStack);
	  return true;
  }

  void GrammaticalAnalysis::reuction_empty(stack<int>&statusStack, stack<Gram>&gramStack)
  {
	  vector<GramDataType>&vecTemp = this->status[statusStack.top()];
	  int i;
	  string temp,str;
	  temp = get_next_token();
	  if (!strcmp(temp.c_str(), ""))return ;
	  cout << temp << endl;
	  Gram gram = string_convert_to_GramToken(temp).getGram();
	  int emptyIndex = -1;
	  for (i = 0; i < vecTemp.size(); i++) {
		  if (vecTemp[i].ls.size() == 1 && vecTemp[i].ls[0] == e_empty) {
			  emptyIndex = i;
			  if (gram == vecTemp[i].symbol) {
				  cout << gram_map_to_string(gram) << "  " << gram_map_to_string(vecTemp[i].symbol) << endl;
				  break;
			  }
		  }
	  }
	  if (emptyIndex != -1 && GotoTable[statusStack.top()][gram] == EMPTY) {
		  gramStack.push(vecTemp[emptyIndex].getGramName());
		  str = GotoTable[statusStack.top()][vecTemp[emptyIndex].getGramName()];
		  str = str.substr(1, str.size() - 1);
		  statusStack.push(atoi(str.c_str()));
	  }
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
  template<typename type>
  vector<type> stack<type>::top(int num)
  {
	  int i;
	  int min = num > vec.size() ? vec.size() : num;
	  vector<type>temp;
	  for (i = vec.size() - num; i < vec.size(); i++) {
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

  wcs syntaxTree::semantic_analysis_where(dbm::resultData_ptr ptr, vector<GramToken>& vec, vector<CDIT>& columnInfoInTable)
  {
	  list<dbm::Page>::iterator pageBegin(ptr->page.begin()), pageEnd(ptr->page.end());
	  list<shared_ptr<dbm::Item>>::iterator itemBegin, itemEnd;
	  wcs wcsTemp;
	  int num;
	  unsigned lineDataSize=0, i,j;
	  for (i = 0; columnInfoInTable.size(); i++) {
		  for (j = 0; j < columnInfoInTable[i].columnInfo.size(); j++) {
			  lineDataSize += columnInfoInTable[i].columnInfo[j].type_size();
		  }
	  }
	  ptr->recordHeadInfo.usedSpaceSize = ptr->recordHeadInfo.totalDataNum = 0;
	  for (; pageBegin != pageEnd; pageBegin++) {
		  dbm::Page&page = *pageBegin;
		   itemBegin=page.itemPtrSet.begin(),itemEnd=page.itemPtrSet.end();
		  for (num=0; itemBegin != itemEnd; itemBegin++,num++) {
			  dbm::shared_ptr<dbm::Item>&item =*itemBegin;
			  wcsTemp = semantic_analysis_where(item, vec, columnInfoInTable);
			  if (wcsTemp == wcs_error)return wcs_error;
			  else if (wcsTemp == wcs_false) {
				  page.deletedFlag.push_back( num);
				  page.dirtyPage = true;
				  page.itemSize--;
				  page.unUsedSpaceSize += lineDataSize;
				  page.usedSpaceSize -= lineDataSize;
			  }
		  }
		  ptr->recordHeadInfo.usedSpaceSize += page.usedSpaceSize;
		  ptr->recordHeadInfo.totalDataNum += page.itemSize;
	  }
	  return wcs_ture;
  }

  wcs syntaxTree::semantic_analysis_where(dbm::shared_ptr<dbm::Item> itemPtr, vector<GramToken>& vec, vector<CDIT>&columnInfoInTable)
  {
	  int i,j,colNum;
	  dbm::queryData queryType;
	  string valuesOne, valuesTwo;
	  bool leftLogic;
	  wcs wcsFlag = where_compare_analysis(vec[1], vec[2], vec[3], columnInfoInTable);
	  if(wcsFlag ==wcs_error)return wcs_error;
	  else if (wcsFlag == wcs_ture) leftLogic=true;
	  else  leftLogic = false;
	  for (i = 4; i < vec.size(); i+=4) {
		  wcsFlag = where_compare_analysis(vec[i + 1], vec[i + 2], vec[i + 3], columnInfoInTable);
		  if (wcsFlag == wcs_error)return wcs_error;
		  else if (wcsFlag == wcs_ture) {
			  leftLogic = semantic_analysis_logic(leftLogic, vec[i], true);
		  }
		  else {
			  leftLogic = semantic_analysis_logic(leftLogic, vec[i], false);
		  }
	  }
	  if (leftLogic == true)return wcs_ture;
	  else return wcs_false;
  }


  bool syntaxTree::semantic_analysis_where_compare(syntaxCondition condition)
  {
	  return compare_values(condition.conditionType, condition.conditionSymbol, condition.valueOne, condition.valueTwo);
  }

  bool syntaxTree::semantic_analysis_logic(bool expressionOne, GramToken symbol, bool expressionTwo)
  {
	  if (symbol.getGram() == e_and) {
		  return expressionOne&&expressionTwo;
	  }
	  else if (symbol.getGram() == e_or) {
		  return expressionOne || expressionTwo;
	  }
	  return false;
  }

  bool syntaxTree::semantic_analysis_select(vector<GramTokenType>& vec)
  {
	  int fromPosi, wherePosi,i;
	  vector<string>tableName;
	  for (i = 0; i < vec.size(); i++) {
		  if (vec[i].getString() == "from")fromPosi = i;
		  else if (vec[i].getString() == "where")wherePosi = i;
	  }
	  for (i = fromPosi + 1; i <= wherePosi - 1; i+=2) {
		  tableName.push_back(vec[i].getString());
	  }
	  vector<CDIT>columnDetails=get_column_details(tableName);
	dbm::resultData_ptr ptr=queryMangement.table_data(tableName[0]),ptrTemp;
	for (i = 1; i < tableName.size(); i++) {
		ptrTemp = queryMangement.table_data(tableName[i]);
		ptr = queryMangement.one_table_natual_connect_another_table(ptr, ptrTemp);
	}
	vector<GramTokenType>whereStatement(vec.begin()+wherePosi,vec.end());
	if (semantic_analysis_where(ptr, whereStatement, columnDetails)==wcs_error) {
		return false;
	}
	else {

	}
	  return true;
  }
  /*
  输入：插入数据语句
  功能：插入数据
  输出：插入成功返回true,否则返回false
  */
  bool syntaxTree::semantic_analysis_insert_data(vector<GramTokenType>& vec)
  {
	  if (queryMangement.query_name(dbm::NameQuery(vec[2].getString()))) {
		  int i;
		  vector<dbm::AttributeType>atrributeType;
		  vector<string>values;
		  for (i = 5; i < vec.size() - 1; i += 2) {
			  values.push_back(vec[i].getString());
			  atrributeType.push_back(gram_data_type_convert_to_AttributeType(vec[i].getGram()));
		  }
		  return queryMangement.check_all_column_type_in_table(
			  this->queryMangement.get_currently_library_name(), vec[2].getString(), values, atrributeType);
	  }
	  else {
		  printf_symbol_status("table name", vec[2].getString(), "doesn't exist");
		  return false;
	  }
  }
  /*
  输入：删除表语句
  功能：删除表
  输出：删除表成功返回true,否则返回false
  */
  bool syntaxTree::semantic_analysis_delete_table(vector<GramTokenType>& vec)
  {
	  if (queryMangement.query_name(dbm::NameQuery(vec[2].getString()))) {
		  queryMangement.delete_talbe_or_library(dbm::NameQuery(queryMangement.get_currently_library_name(), vec[2].getString()));
		  return true;
	  }
	  else {
		  printf_symbol_status("table name", vec[2].getString() , "doesn't exist");
		  return false;
	  }
  }
  /*
  输入：创建库语句
  功能：创建库
  输出：创建成功返回true,否则返回false
  */
  bool syntaxTree::semantic_analysis_create_database(vector<GramTokenType>& vec)
  {
	  if (!queryMangement.query_name(dbm::NameQuery(vec[2].getString()))) {
		  queryMangement.add_table_or_library(dbm::NameQuery(vec[2].getString()));
		  return true;
	  }
	  else {
		  printf_symbol_status("library name", vec[2].getString(), "already exist");
		  return false;
	  }
  }
  /*
  输入：切换库语句
  功能：切换库
  输出：切换成功返回true,否则返回false
  */
  bool syntaxTree::semantic_analysis_use_database(vector<GramTokenType>& vec)
  {
	  if (queryMangement.query_name(dbm::NameQuery(vec[1].getString()))) {
		  queryMangement.set_cur_library_name(vec[1].getString());
		  return true;
	  }
	  else {
		  printf_symbol_status("library name",vec[1].getString(),"doesn't exist");
		  return false;
	  }
  }
  /*
  输入：创建表语句
  功能：创建表
  输出：创建成功返回true,否则返回false
  */
  bool syntaxTree::semantic_analysis_create(vector<GramTokenType>& vec)
  {
	  int i;
	  if (!queryMangement.query_name(dbm::NameQuery(queryMangement.get_currently_library_name(), vec[2].getString()))) {
		  vector<string>type, id;
		  for (i = 4; i < vec.size(); i += 3) {
			  id.push_back(vec[i].getString());
			  type.push_back( vec[i + 1].getString());
		  }
		  for (i = 0; i < id.size(); i++) {
			  queryMangement.add_name(dbm::NameQuery(queryMangement.get_currently_library_name(), vec[2].getString(), id[i]), type[i]);
		  }
		  return true;
	  }
	  else {
		  printf_symbol_status("table name",vec[2].getString(),"already exist");
		  return false;
	  }
  }
  /*
  输入：删除数据库语句
  功能：删除数据库
  输出：找到数据库返回true,否则返回false
  */
  bool syntaxTree::semantic_analysis_drop_database(vector<GramTokenType>& vec)
  {
	  if (queryMangement.query_name(dbm::NameQuery(vec[1].getString()))) {
		  queryMangement.delete_name(dbm::NameQuery(vec[1].getString()));
		  return true;
	  }
	  else {
		  printf_symbol_status("library name", vec[1].getString(),"doesn't exist");
		  return false;
	  }
  }
  /*
  输入：删除索引语句
  功能：删除索引
  输出：找到索引返回true,否则返回false
  */
  bool syntaxTree::semantic_analysis_drop_index(vector<GramTokenType>& vec)
  {
	  if (queryMangement.query_index(queryMangement.get_currently_library_name(),vec[2].getString(),vec[4].getString())) {
		  queryMangement.erase_index(queryMangement.get_currently_library_name(), vec[2].getString(), vec[4].getString());
		  return true;
	  }
	  else {
		  printf_symbol_status("index name",vec[2].getString(),"doesn't exist");
		  return false;
	  }
  }
  /*
  输入：结果集
  功能：去除重复
  */
  inline void syntaxTree::execute_distance(dbm::resultData_ptr resultPtr)
  {
	  queryMangement.remove_duplicate(resultPtr);
  }

  inline void syntaxTree::printf_symbol_status(const string symbolType,const string & name,const string&status)
  {
	  cout << "语义分析：" << symbolType <<" "<<name <<" "<<status << endl;
  }

 
  /*
  输入：数据类型，比较类型，数据1，数据2
  功能：比较数据1与数据2
  输出：数据1通过比较类型大小数据2返回true,否则返回false
  */
  bool syntaxTree::compare_values(dbm::AttributeType type, dbm::queryData queryType, dbm::DataType dataOne, dbm::DataType dataTwo)
  {
	  if (queryType == dbm::qd_equal_greater_than) {
		  if (type == dbm::a_int) {
			  return atoi(dataOne.get_data().c_str())>= atoi(dataTwo.get_data().c_str());
		  }
		  else if (type == dbm::a_flaot) {
			  return atof(dataOne.get_data().c_str()) >= atof(dataTwo.get_data().c_str());
		  }
		  return dataOne.get_data() >= dataTwo.get_data();
	  }
	  else if (queryType == dbm::qd_equal_or_less_then) {
		  if (type == dbm::a_int) {
			  return atoi(dataOne.get_data().c_str()) <= atoi(dataTwo.get_data().c_str());
		  }
		  else if (type == dbm::a_flaot) {
			  return atof(dataOne.get_data().c_str()) <= atof(dataTwo.get_data().c_str());
		  }
		  else {
			  return dataOne.get_data() <= dataTwo.get_data();
		  }
	  }
	  else {
		  return dbm::compare_single_symbol_values(type, queryType, dataOne, dataTwo);
	  }
	 }
  /*
  输入：表名
  功能：获取表中列的详细信息
  输出：返回详细信息
  */
	 vector<CDIT> syntaxTree::get_column_details(vector<string>& tableName)
	{
		int i;
		vector<CDIT>columnInfo;
		for (i = 0; i < tableName.size(); i++) {
			CDIT temp;
			temp.tableName = tableName[i];
			temp.columnInfo = queryMangement.get_column_info_in_table(tableName[i]);
			columnInfo.push_back(temp);
		}
		return columnInfo;
	}
	 /*
	 输入：列名，连接表的列信息集合
	 功能：获取列在连接表中位置
	 输出：找到返回位置，否则返回-1
	 */
	 columnPosi syntaxTree::get_column_position_in_connect_table(const string & columnName, vector<CDIT>& columnInfoInTable)
	 {
		 int i,j,position=0;
		 columnPosi temp;
		 for (i = 0; i < columnName.size(); i++) {
			 if (columnName[i] == '.')break;
		 }
		 if (i < columnName.size()) {
			 string tableName = columnName.substr(0, i),columnNameTemp = columnName.substr(i + 1, columnName.size() - i);
			 for (i = 0; i < columnInfoInTable.size(); i++) {
				 if (tableName == columnInfoInTable[i].tableName) {
					 temp.tableIndex = i;
					 break;
				 }
				// position += columnInfoInTable[i].columnInfo.size();
			 }
			 for (j = 0; j < columnInfoInTable[i].columnInfo.size(); j++) {
				 if (columnInfoInTable[i].columnInfo[j].colName == columnName) {
					 temp.columnIndex = j;
					 break;
				 }
				// position++;
			 }
			 if (j > columnInfoInTable[i].columnInfo.size())return columnPosi();
		 }
		 else {
			 int columnCount = 0;
			 for (i = 0; i < columnInfoInTable.size(); i++) {
				 for (j = 0; j < columnInfoInTable[i].columnInfo.size(); j++) {
					 if (columnInfoInTable[i].columnInfo[j].colName == columnName) {
						 temp.tableIndex = i;
						 temp.columnIndex = j;
						 columnCount++;
					 }
					// position++;
				 }
				 //position += columnInfoInTable[i].columnInfo.size();
			 }
			 if (columnCount > 1)return columnPosi();
		 }
		 return temp;
	 }
	 /*
	 输入：where like 字符匹配中的字符匹配
	 功能：找到字符匹配中的关键数字或字符位置，即排除%,_
	 输出：返回位置集合
	  */
	 vector<matchKeyword> syntaxTree::find_match_keyword(string & condition)
	 {
		 vector<matchKeyword>keyword;
		 matchKeyword temp;
		 bool conti = false;
		 int i;
		 for (i = 0; i < condition.size(); i++) {
			 if (condition[i] != '%'&&condition[i] != '_') {
				 if (conti == true&&i+1<condition.size()) {
					 temp.keyword.push_back(condition[i]);
					 temp.position = i;
				 }
				 else {
					 if (temp.keyword.size()>0) {
						 temp.position = temp.position - temp.keyword.size() + 1;
						 keyword.push_back(temp);
					 }
					 conti = true;
					 temp.keyword = condition[i];
					 temp.position = i;
				 }
			 }else
				 conti = false;
		 }
		 return keyword;
	 }
	 /*
	 输入：主串，子串
	 功能：寻找子串在主串中的位置		sunday 算法
	 输出：位置集合
	 */
	 vector<int> syntaxTree::find_substring_position(string primaryString, string subString)
	 {
		 const int max = 200;
		 int priStrSize = primaryString.size() - 1, subStrSize = subString.size() - 1;
		 int i, offset=0, binary[max];
		 bool flag;
		 vector<int>position;
		 for (i = 0; i < max; i++)
			 binary[i] = -1;
		 for (i = 0; i <= subStrSize; i++)
			 binary[i] = subString[i];
		 while (offset + subStrSize <= priStrSize) {
			 i = 0;
			 flag = false;
			 for (; i <= subStrSize&&!flag; i++) {
				 if (primaryString[offset + i] != subString[i])flag = true;
			 }
			 if (flag) {
				 i = subStrSize + 1;
				 if (binary[primaryString[offset + i]] == -1)offset += i + 1;
				 else offset = offset + i - binary[primaryString[offset + i]];
			 }
			 else {
				 position.push_back(offset);
				 offset++;
			 }
		 }
		 return position;
	 }
	 void syntaxTree::printf_column_type_not_match(string & columnOne, string & columnTwo)
	 {
		 cout << columnOne << " and " << columnTwo << " type isn't match" << endl;
	 }
	 dbm::queryData syntaxTree::gram_convert_to_queryData(const Gram & gram)
	 {
		//e_less_than, e_less_than_or_equal, e_equal, e_unequal, e_greater_than, e_greater_than_or_equal
		 switch (gram)
		 {
		 case e_less_than:
			 return dbm::qd_less_than;
		 case e_less_than_or_equal:
			 return dbm::qd_equal_or_less_then;
		 case e_greater_than:
			 return dbm::qd_greater_than;
		 case e_greater_than_or_equal:
			 return dbm::qd_equal_greater_than;
		 case e_equal:
			 return dbm::qd_equal;
		 case e_unequal:
			 return dbm::qd_unequal;
		 default:
			 break;
		 }
		 return dbm::queryData();
	 }
	 wcs syntaxTree::where_compare_analysis(GramToken& valuesOne, GramToken& compareSymbol, GramToken& valuesTwo, vector<CDIT>&columnInfoInTable)
	 {
		  
		 int bin = (valuesOne.getGram() == e_id) ? 1 * 2 : 0 + valuesTwo.getGram() == e_id ? 1 : 0;
		 switch (bin)
		 {
		 case 3:
			 return where_compare_analysis_both_column(valuesOne, compareSymbol, valuesTwo, columnInfoInTable);
		 case 2:
			 return where_compare_analysis_column_and_literal_char(valuesOne, compareSymbol, valuesTwo, columnInfoInTable);
		 case 1:
			 return where_compare_analysis_column_and_literal_char(valuesTwo, compareSymbol, valuesOne, columnInfoInTable);
		 case 0:
			 return where_compare_analysis_both_literal_char(valuesOne, compareSymbol, valuesTwo);
			 break;
		 }
		 return wcs_error;
	 }
	 wcs syntaxTree::where_compare_analysis_both_column(GramToken& valuesOne, GramToken& compareSymbol, GramToken& valuesTwo, vector<CDIT>& columnInfoInTable)
	 {
		 columnPosi columnPosiLeft, columnPosiRight;
		 bool leftLogic;
		 syntaxCondition temp;
		 columnPosiLeft = get_column_position_in_connect_table(valuesOne.getString(), columnInfoInTable),
			 columnPosiRight = get_column_position_in_connect_table(valuesTwo.getString(), columnInfoInTable);
		 if (!columnPosiLeft.flag || !columnPosiRight.flag ||
			 (columnInfoInTable[columnPosiLeft.tableIndex].columnInfo[columnPosiLeft.columnIndex].attributeType
				 != columnInfoInTable[columnPosiRight.tableIndex].columnInfo[columnPosiRight.columnIndex].attributeType)) {
			 printf_column_type_not_match(valuesOne.getString(), valuesTwo.getString());
			 return wcs_error;
		 }
		 temp.conditionSymbol = gram_convert_to_queryData(compareSymbol.getGram());
		 temp.conditionType = columnInfoInTable[columnPosiLeft.tableIndex].columnInfo[columnPosiLeft.columnIndex].attributeType;
		 temp.valueOne = valuesOne.getString();
		 temp.valueTwo = valuesTwo.getString();
		 leftLogic = semantic_analysis_where_compare(temp);
		 if (leftLogic == true) {
			 return wcs_ture;
		 }
		 else {
			 return wcs_false;
		 }
		
	 }
	 wcs syntaxTree::where_compare_analysis_column_and_literal_char(GramToken & valuesOne, GramToken & compareSymbol, GramToken & valuesTwo, vector<CDIT>& columnInfoInTable)
	 {
		 columnPosi columnPosi;
		 syntaxCondition temp;
		 columnPosi = get_column_position_in_connect_table(valuesOne.getString(), columnInfoInTable);
		 if (!columnPosi.flag || columnInfoInTable[columnPosi.tableIndex].columnInfo[columnPosi.columnIndex].attributeType !=
			 gram_data_type_convert_to_AttributeType(valuesTwo.getGram())) {
			 printf_column_type_not_match(valuesOne.getString(), valuesTwo.getString());
			 return wcs_error;
		 }
		 temp.conditionSymbol = gram_convert_to_queryData(compareSymbol.getGram());
		 temp.conditionType = gram_data_type_convert_to_AttributeType(valuesTwo.getGram());
		 temp.valueOne = valuesOne.getString();
		 temp.valueTwo = valuesTwo.getString();
		 if (semantic_analysis_where_compare(temp)) {
			 return wcs_ture;
		 }
		 else {
			 return wcs_false;
		 }
	 }
	 wcs syntaxTree::where_compare_analysis_both_literal_char(GramToken & valuesOne, GramToken & compareSymbol, GramToken & valuesTwo)
	 {
		 syntaxCondition temp;
		 if (valuesOne.getGram() != valuesTwo.getGram()) {
			 printf_column_type_not_match(valuesOne.getString(), valuesTwo.getString());
			 return wcs_error;
		 }
		 temp.conditionSymbol = gram_convert_to_queryData(compareSymbol.getGram());
		 temp.conditionType = gram_data_type_convert_to_AttributeType(valuesOne.getGram());
		 temp.valueOne = valuesOne.getString();
		 temp.valueTwo = valuesTwo.getString();
		 if (semantic_analysis_where_compare(temp))return wcs_ture;
		 else return wcs_false;
	 }
	 wcs syntaxTree::display_select_statement(dbm::resultData_ptr ptr, vector<GramToken>& vec, vector<CDIT>& columnInfoInTable)
	 {
		 int i,j,k;
		 vector<int>posi;
		 columnPosi temp;
		 int position = 0;
		 if (vec.size() == 1) {	
			 for (i = 0; i < columnInfoInTable.size(); i++) {
				 for (j = 0; j < columnInfoInTable[i].columnInfo.size(); j++) {
					 cout << columnInfoInTable[i].columnInfo[j].colName << " ";
					 posi.push_back(position);
					 position++;
				 }
			 }
			 cout << endl;
		 }
		 else {	
			 for (i = 0; i < vec.size(); i++) {
				 temp = get_column_position_in_connect_table(vec[i].getString(), columnInfoInTable);
				 if (temp.flag == false)return wcs_error;
				 for (j = 0; j <= temp.tableIndex; j++)
					 for (k = 0; k <= temp.tableIndex; k++) 
						 position++;
				 posi.push_back(position);
			 }
		 }
		 return wcs_ture;
	 }
	 void syntaxTree::display_select_statement(dbm::resultData_ptr ptr, vector<int>& posi)
	 {
		 int i;
		 list<dbm::Page>::iterator pageBegin=ptr->page.begin(), pageEnd=ptr->page.end();
		 list<shared_ptr<dbm::Item>>::iterator itemBegin, itemEnd;
		 for (; pageBegin != pageEnd; pageBegin++) {
			 dbm::Page page = *pageBegin;
			 itemBegin = page.itemPtrSet.begin();
			 itemEnd = page.itemPtrSet.end();
			 for (; itemBegin != itemEnd; itemBegin++) {
				 for (i = 0; i < (*itemBegin)->item.size(); i++) {
					 cout << (*itemBegin)->item[i].get_data() << " ";
				 }
				 cout << endl;
			 }
		 }
	 }
  }