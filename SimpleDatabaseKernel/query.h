#pragma once
#include"databaseMangement.h"
enum queryData {
	qd_greater_than, qd_equal_greater_than,
	qd_less_than, qd_equal_or_less_then, qd_equal
};
struct QueryData {
	queryData conditionType;//��������
	string columnName;//����
	string condition;//����
};
class query {

private:
	dataMangement dataMengementer;
	resultData result;
};