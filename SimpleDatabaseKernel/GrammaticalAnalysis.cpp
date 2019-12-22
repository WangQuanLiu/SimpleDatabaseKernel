#ifndef _GrammaticalAnalysis_
#include"GrammaticalAnalysis.h"
#endif
const GrammaticalType Grammatical::start{
	GrammaticalDataType{"s","$"}
};
const GrammaticalType Grammatical::s{
	GrammaticalDataType{"v_create_def"},
	GrammaticalDataType{"v_select_def"},
	GrammaticalDataType{"v_create_database_def"},
	GrammaticalDataType{"v_use_database_def"},
	GrammaticalDataType{"v_delete_element_def"},
	GrammaticalDataType{"v_delete_table_def"},
	GrammaticalDataType{"v_alter_table_add_column_def"},
	GrammaticalDataType{"v_alter_table_drop_column_def"},
	GrammaticalDataType{"v_insert_def"},
	GrammaticalDataType{"v_update_def"},
	GrammaticalDataType{"v_create_view_def"},
	GrammaticalDataType{"v_drop_view_def"},
	GrammaticalDataType{"v_create_index_def"},
	GrammaticalDataType{"v_drop_index_def"}
};