#pragma once
#include"databaseMangement.h"
enum queryData {
	qd_greater_than, qd_equal_greater_than,
	qd_less_than, qd_equal_or_less_then, qd_equal
};
struct QueryData {
	queryData conditionType;//条件类型
	string columnName;//列名
	string condition;//条件
};
class query {

private:
	dataMangement dataMengementer;
	resultData result;
};