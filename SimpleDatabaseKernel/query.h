#pragma once
//#include"databaseMangement.h"
#include"index.h"
#include<set>
#include<limits>
#define _QUERY_
namespace dbm {
	enum queryData {
		qd_greater_than,//大于
		qd_equal_greater_than,//大于等于
		qd_less_than, //小于
		qd_equal_or_less_then,//小于等于 
		qd_equal,//等于
		qd_unequal//不等于
	};
	using queryType = dbm::AttributeType;
	struct QueryData {
		QueryData&operator=(const QueryData&data);
		queryData conditionSymbol;//条件类型
		string tableName, columnName;//列名
		string condition;//条件
		dbm::AttributeType conditionType;//条件类型
	};
	class queryMangement :public dbm::dataMangement, public dbm::indexMangement {
	public:
		queryMangement() = default;
		bool condition_query_single_table(const QueryData&condition, dbm::resultData_ptr resultPtr);
		void remove_duplicate(dbm::resultData_ptr resultPtr);
		dbm::resultData_ptr one_table_natual_connect_another_table(dbm::resultData_ptr ptrOne, dbm::resultData_ptr ptrTwo);
	private:
		void erase_index_condition(const QueryData&condition, int colIndex, dbm::indexPtr ptr, dbm::resultData_ptr resultPtr);
		void erase_condition(const QueryData&condition, int colIndex, dbm::resultData_ptr resultPtr);
		void erase_index_condition_values(dbm::indexResultDataSetPtr indexSetPtr, dbm::resultData_ptr resultPtr);
		void erase_condition_values(const QueryData condition, int colIndex, dbm::resultData_ptr resultPtr);
		bool compare_single_symbol_values(dbm::AttributeType type, queryData queryType, dbm::DataType dataOne, dbm::DataType dataTwo);
		template<typename Type>
		bool inner_compare_single_symbol_values(queryData type, Type dataOne, Type dataTwo);
		//dbm::indexMangement indexMangement;
	};
	template<typename Type>
	inline bool queryMangement::inner_compare_single_symbol_values(queryData queryType, Type dataOne, Type dataTwo)
	{
		if (queryType == qd_equal) {
			return dataOne == dataTwo;
		}
		else if (queryType == qd_unequal) {
			return dataOne != dataTwo;
		}
		else if (queryType == qd_less_than) {
			return dataOne < dataTwo;
		}
		else if (queryType == qd_greater_than) {
			return dataOne > dataTwo;
		}
		return false;
	}
}