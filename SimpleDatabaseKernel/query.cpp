#include"query.h"
namespace dbm {
	queryMangement::queryMangement()
	{
	}
	/*
	输入：条件类型，结果集
	功能：筛选出符合结果的结果集
	输出：成功返回true,失败返回false
	*/
	bool queryMangement::condition_query_single_table(const QueryData & condition, dbm::resultData_ptr resultPtr)
	{
		if (condition.tableName != resultPtr->recordHeadInfo.tableName)return false;
		int colIndex, i;
		for (i = 0; i < resultPtr->ColName.size(); i++) {
			if (resultPtr->ColName[i].colName == condition.columnName) {
				colIndex = i;
				break;
			}
		}
		dbm::indexPtr ptr = inner_query_index(get_currently_library_name(),
			condition.tableName, condition.columnName);
		if (ptr == nullptr) {
			erase_condition(condition, colIndex, resultPtr);
		}
		else {
			erase_index_condition(condition, colIndex, ptr, resultPtr);
		}

		return true;
	}
	/*
	输入：结果集指针
	功能：去重复
	*/
	void queryMangement::remove_duplicate(dbm::resultData_ptr resultPtr)
	{
		std::set<string>s;
		string str;
		int i, total = 0;
		list<dbm::Page>::iterator pageBegn(resultPtr->page.begin()),
			pageEnd(resultPtr->page.end());
		int columnSize = resultPtr->recordHeadInfo.usedSpaceSize / resultPtr->recordHeadInfo.totalDataNum;
		int totalColSize = 0;
		for (; pageBegn != pageEnd; pageBegn++) {
			dbm::Page&page = *pageBegn;
			list<shared_ptr<dbm::Item>>::iterator itemBegin(page.itemPtrSet.begin()),
				itemEnd(page.itemPtrSet.end());
			for (; itemBegin != itemEnd; itemBegin++) {
				for (i = 0; i < (*itemBegin)->item.size(); i++) {
					str += (*itemBegin)->item[i].get_data();
				}
				if (s.count(str) > 0) {
					(*itemBegin)->item.clear();
					(*itemBegin) = nullptr;
					page.itemPtrSet.erase(itemBegin);
					page.usedSpaceSize -= columnSize;
					page.dirtyPage = true;
				}
				else
					s.insert(str);
				str.clear();
			}
			page.unUsedSpaceSize = page.pageSpaceMax - page.usedSpaceSize;
			page.itemSize = page.itemPtrSet.size();
			total += page.itemSize;
		}
		resultPtr->recordHeadInfo.usedSpaceSize = totalColSize;
		resultPtr->recordHeadInfo.totalDataNum = total;
	}
	/*
	输入：结果集1和结果集2
	功能：连接结果集1和结果集2
	输出：返回连接后的结果集
	*/
	dbm::resultData_ptr queryMangement::one_table_natual_connect_another_table(dbm::resultData_ptr ptrOne, dbm::resultData_ptr ptrTwo)
	{
		dbm::resultData_ptr ptr = new dbm::resultData();
		list<dbm::Page>::iterator ptrOnePageBegin(ptrOne->page.begin()), ptrOnePageEnd(ptrOne->page.end()),
			ptrTwoPageBegin, ptrTwoPageEnd;
		dbm::Page_ptr pagePtr = new dbm::Page();
		int t, x;
		set<unsigned>sOne, sTwo;
		list<shared_ptr<dbm::Item>>::iterator itemOneBegin, itemTwoBegin, itemOneEnd, itemTwoEnd;
		for (; ptrOnePageBegin != ptrOnePageEnd; ptrOnePageBegin++) {
			itemOneBegin = (*ptrOnePageBegin).itemPtrSet.begin();
			itemOneEnd = (*ptrOnePageBegin).itemPtrSet.end();
			sOne.clear();
			for (t = 0; t < (*ptrOnePageBegin).deletedFlag.size(); t++)
				sOne.insert((*ptrOnePageBegin).deletedFlag[t]);
			for (t=0; itemOneBegin != itemOneEnd; itemOneBegin++,t++) {
				if (sOne.count(t) != 0)continue;
				ptrTwoPageBegin=ptrTwo->page.begin(), ptrTwoPageEnd=ptrTwo->page.end();
				for (; ptrTwoPageBegin != ptrTwoPageEnd; ptrTwoPageBegin++) {
					sTwo.clear();
					for (x = 0; x < (*ptrTwoPageBegin).deletedFlag.size(); x++)
						sTwo.insert((*ptrTwoPageBegin).deletedFlag[x]);
					itemTwoBegin = (*ptrTwoPageBegin).itemPtrSet.begin();
					itemTwoEnd = (*ptrTwoPageBegin).itemPtrSet.end();
					for (x=0; itemTwoBegin != itemTwoEnd; itemTwoBegin++,x++) {
						if (sTwo.count(x) != 0)continue;
						shared_ptr < dbm::Item > itemTemp = make_shared<dbm::Item>(new dbm::Item());
						(*itemTemp) = (**itemOneBegin);
						(*itemTemp) += (**itemTwoBegin);
						pagePtr->itemPtrSet.push_back(itemTemp);
						pagePtr->itemSize++;
					}

				}
			}
		}
		ptr->page.push_back(*pagePtr);
		return ptr;
	}
	/*
	输入：条件类型，列号，索引指针，结果集指针
	功能：通过索引得到符号条件类型的结果集
	输出：
	*/
	void queryMangement::erase_index_condition(const QueryData & condition, int colIndex, dbm::indexPtr ptr, dbm::resultData_ptr resultPtr)
	{

		dbm::bPlusType keywordOne = condition.condition, keywordTwo;
		keywordTwo.category = keywordOne.category = resultPtr->recordHeadInfo.type[colIndex];
		dbm::indexResultDataSetPtr indexSetPtr;
		string str;
		if (condition.conditionType == qd_equal) {
			indexSetPtr = ptr->bplus.range_query(keywordOne);
		}
		else if (condition.conditionType == qd_less_than || condition.conditionType == qd_equal_or_less_then) {
			keywordTwo = to_string(INT_MIN);
			indexSetPtr = ptr->bplus.range_query(keywordTwo, keywordOne);
			if (condition.conditionType == qd_equal_or_less_then) {
				*indexSetPtr += *ptr->bplus.range_query(keywordOne);
			}
		}
		else if (condition.conditionType == qd_greater_than || condition.conditionType == qd_equal_greater_than) {
			keywordTwo = to_string(INT_MAX);
			indexSetPtr = ptr->bplus.range_query(keywordOne, keywordTwo);
			if (condition.conditionType == qd_equal_greater_than) {
				*indexSetPtr += *ptr->bplus.range_query(keywordOne);
			}
		}
		else {
			keywordTwo = to_string(INT_MIN);
			indexSetPtr = ptr->bplus.range_query(keywordTwo, keywordOne);
			keywordTwo = to_string(INT_MAX);
			*indexSetPtr += (*ptr->bplus.range_query(keywordOne, keywordTwo));
		}
		erase_index_condition_values(indexSetPtr, resultPtr);
	}
	/*
	输入：条件类型，列号，结果集指针
	功能：按条件筛选结果集
	*/
	void queryMangement::erase_condition(const QueryData & condition, int colIndex, dbm::resultData_ptr resultPtr)
	{
		QueryData conditionTemp = condition;
		if (condition.conditionType == qd_equal) {
			erase_condition_values(condition, colIndex, resultPtr);
		}
		else if (condition.conditionType == qd_less_than || condition.conditionType == qd_equal_or_less_then) {

			conditionTemp.condition = qd_less_than;
			erase_condition_values(condition, colIndex, resultPtr);
			if (condition.conditionType == qd_equal_or_less_then) {
				conditionTemp.condition = qd_equal;
				erase_condition_values(condition, colIndex, resultPtr);
			}
		}
		else if (condition.conditionType == qd_greater_than || condition.conditionType == qd_equal_greater_than) {
			conditionTemp.condition = qd_greater_than;
			erase_condition_values(condition, colIndex, resultPtr);
			if (condition.conditionType == qd_equal_greater_than) {
				conditionTemp.condition = qd_equal;
				erase_condition_values(condition, colIndex, resultPtr);
			}
		}
		else {
			erase_condition_values(condition, colIndex, resultPtr);
		}
	}
	/*
	输入：索引结果数据集合指针，结果集指针
	功能：通过索引结果数据集合指针得到结果集
	*/
	void queryMangement::erase_index_condition_values(dbm::indexResultDataSetPtr indexSetPtr, dbm::resultData_ptr resultPtr)
	{
		int i, j;
		std::set<string> s;
		string str;
		int columnSize = resultPtr->recordHeadInfo.usedSpaceSize / resultPtr->recordHeadInfo.totalDataNum;
		int totalColSize = 0;
		list<dbm::indexResultData>::iterator resultDataBegin(indexSetPtr->list.begin()),
			resultDataEnd(indexSetPtr->list.end());
		for (; resultDataBegin != resultDataEnd; resultDataBegin++) {
			s.insert(to_string((*resultDataBegin).info.pagePosi.pageNumber) +
				to_string((*resultDataBegin).info.pagePosi.posi));
		}
		list<dbm::Page>::iterator pageBegin(resultPtr->page.begin()), pageEnd(resultPtr->page.end());
		int totalCot = 0;
		for (i = 0; pageBegin != pageEnd; pageBegin++, i++) {
			dbm::Page&page = *pageBegin;
			list<shared_ptr<dbm::Item>>::iterator itemBegin(page.itemPtrSet.begin()), itemEnd(page.itemPtrSet.end());
			for (j = 0; itemBegin != itemEnd; itemBegin++, j++) {
				str = to_string(i) + to_string(j);
				if (s.count(str) == 0) {
					(*itemBegin)->clear();
					(*itemBegin) = nullptr;
					page.itemPtrSet.erase(itemBegin);
					page.dirtyPage = true;
					page.usedSpaceSize -= columnSize;
				}
			}
			page.unUsedSpaceSize = page.pageSpaceMax - page.usedSpaceSize;
			page.itemSize = page.itemPtrSet.size();
			totalColSize += page.usedSpaceSize;
			totalCot += page.itemSize;
		}
		resultPtr->recordHeadInfo.usedSpaceSize = totalColSize;
		resultPtr->recordHeadInfo.totalDataNum = totalCot;
	}
	/*
	输入：条件，列号，结果集
	功能：筛选条件结果集得到新结果集
	*/
	void queryMangement::erase_condition_values(const QueryData  condition, int colIndex, dbm::resultData_ptr resultPtr)
	{
		dbm::AttributeType type = resultPtr->recordHeadInfo.type[colIndex];
		dbm::DataType temp = condition.condition, tempTwo;
		list<dbm::Page>::iterator pageBegin(resultPtr->page.begin()), pageEnd(resultPtr->page.end());
		int totalCot = 0;
		int columnSize = resultPtr->recordHeadInfo.usedSpaceSize / resultPtr->recordHeadInfo.totalDataNum;
		int totalColSize = 0;
		for (; pageBegin != pageEnd; pageBegin++) {
			dbm::Page&page = *pageBegin;
			list<shared_ptr<dbm::Item>>::iterator itemBegin(page.itemPtrSet.begin()), itemEnd(page.itemPtrSet.end());
			for (; itemBegin != itemEnd; itemBegin++) {
				tempTwo = (*itemBegin)->item[colIndex];
				if (!compare_single_symbol_values(type, condition.conditionSymbol, tempTwo, temp)) {
					(*itemBegin)->clear();
					(*itemBegin) = nullptr;
					page.itemPtrSet.erase(itemBegin);
					page.dirtyPage = true;
					page.unUsedSpaceSize -= columnSize;
				}
			}
			page.usedSpaceSize = page.pageSpaceMax - page.unUsedSpaceSize;
			totalColSize += page.usedSpaceSize;
			page.itemSize = page.itemPtrSet.size();
			totalCot += page.itemSize;
		}
		resultPtr->recordHeadInfo.usedSpaceSize = totalColSize;
		resultPtr->recordHeadInfo.totalDataNum = totalCot;
	}

	bool compare_single_symbol_values(dbm::AttributeType type, queryData queryType, dbm::DataType dataOne, dbm::DataType dataTwo)
	{
		if (type == dbm::a_int) {
			return inner_compare_single_symbol_values<int>(queryType, atoi(dataOne.get_data().c_str()), atoi(dataTwo.get_data().c_str()));
		}
		else if (type == dbm::a_flaot) {
			return inner_compare_single_symbol_values<float>(queryType, atof(dataOne.get_data().c_str()), atof(dataTwo.get_data().c_str()));
		}
		else {
			return inner_compare_single_symbol_values<string>(queryType, dataOne.get_data(), dataTwo.get_data());
		}
		return false;
	}

	QueryData & QueryData::operator=(const QueryData & data)
	{
		this->columnName = data.columnName;
		this->condition = data.condition;
		this->conditionSymbol = data.conditionSymbol;
		this->conditionType = data.conditionType;
		this->tableName = data.tableName;
		return *this;
	}

}
