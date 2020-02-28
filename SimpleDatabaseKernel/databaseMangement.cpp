#include"databaseMangement.h"
namespace dbm {
	
	/*
	输入：库名
		  库名、表名
		  库名、表名、列名
	功能：有该名字NameQuery->flag 为true 并设置库名下标，表名下标，列名下标
		  没有该名字NameQuery->flag为false
	输出：flag
	*/
	NameQueryIndex dataMangement::query_name_inner(const NameQuery &nameQuery) const {
		int i;
		for (i = 0; i < nameMangementFilePtr->libraryNameTable.size(); i++) //查询库名
			if (nameQuery.libraryName == nameMangementFilePtr->libraryNameTable[i]) {
				break;
			}
		if (i < nameMangementFilePtr->libraryNameTable.size()) {
			if (nameQuery.queryType == q_library_name)return NameQueryIndex(i);
			int j;
			if (nameMangementFilePtr->curLibraryName == nameQuery.libraryName) {
				for (j = 0; j < nameMangementFilePtr->nameTable.tableMangement.size(); j++) {//查询表名
					if (nameQuery.tableName == nameMangementFilePtr->nameTable.tableMangement[j].tableName) break;
				}
				if (j < nameMangementFilePtr->nameTable.tableSize) {
					if (nameQuery.queryType == q_table_name)return NameQueryIndex(i, j);
					int k;
					for (k = 0; k < nameMangementFilePtr->nameTable.tableMangement[j].colSize; k++) {//查询列名
						if (nameQuery.colName == nameMangementFilePtr->nameTable.tableMangement[j].column[k].colName)return NameQueryIndex(i, j, k);
					}
				}
			}
		}
		return NameQueryIndex();
	}
	/*
	输入：库名
		  库名、表名
		  库名、表名、列名
	功能：query_name 查询该库名 或 表名 或列名
	输出：有该名字返回true,没有返回false
	*/
	bool dataMangement::query_name(const NameQuery &nameQuery) const {
		return query_name_inner(nameQuery).flag;
	}
	/*
	输入：	库名				新名字
			库名、表名			新名字
			库名、表名、列名	新名字
	功能：改库名、表名、列名为nameQuery
	输出：有该名字返回true,没有返回false
	*/
	bool dataMangement::nameMangeMent_modification_name(const NameQuery &nameQuery, const string &modficationedName) {
		NameQueryIndex temp = query_name_inner(nameQuery);
		if (temp.flag) {
			if (temp.queryType == q_library_name) {//修改库名
				nameMangementFilePtr->libraryNameTable[temp.databaseNameIndex] = modficationedName;
				if (nameMangementFilePtr->curLibraryName == nameQuery.libraryName) {
					nameMangementFilePtr->nameTable.libraryName = modficationedName;
					nameMangementFilePtr->curLibraryName = modficationedName;
				}
			}
			else if (temp.queryType == q_table_name) {//修改表名
				nameMangementFilePtr->nameTable.tableMangement[temp.tableNameIndex].tableName = modficationedName;

			}
			else {//修改列名
				nameMangementFilePtr->nameTable.tableMangement[temp.tableNameIndex].column[temp.colNameIndex].colName = modficationedName;
			}

		}
		return temp.flag;
	}
	/*
	输入：	库名
			库名、表名
			库名、表名、列名
	功能：删除库名、表名、列名为nameQuery
	输出：有该名字返回true,没有返回false
	*/
	bool dataMangement::delete_name(const NameQuery &nameQuery) {
		const NameQueryIndex temp = static_cast<const NameQueryIndex>(query_name_inner(nameQuery));
		if (temp.flag) {
			if (temp.queryType == q_library_name) {	//删除库名
				vector<string>::iterator iter = nameMangementFilePtr->libraryNameTable.begin() + temp.databaseNameIndex;
				if (nameMangementFilePtr->nameTable.libraryName == nameMangementFilePtr->libraryNameTable[temp.databaseNameIndex]) {
					nameMangementFilePtr->nameTable.clear();//清空库中的配置文件
					nameMangementFilePtr->curLibraryName = Q_EMPTY;
				}
				nameMangementFilePtr->libraryNameTable.erase(iter);

			}
			else if (temp.queryType == q_table_name) {//删除表名
				vector<TableNameMangement>::iterator iter = nameMangementFilePtr->nameTable.tableMangement.begin() + temp.tableNameIndex;
				nameMangementFilePtr->nameTable.tableMangement.erase(iter);
				nameMangementFilePtr->nameTable.tableSize = nameMangementFilePtr->nameTable.tableMangement.size();
			}
			//删除列名
			else {
				vector<CNT>::iterator iter =
					nameMangementFilePtr->nameTable.tableMangement[temp.tableNameIndex].column.begin() + temp.colNameIndex;
				nameMangementFilePtr->nameTable.tableMangement[temp.tableNameIndex].column.erase(iter);
				nameMangementFilePtr->nameTable.tableMangement[temp.tableNameIndex].colSize -= 1;

			}
		}
		return temp.flag;
	}
	/*
	输入：nameQUuery 库名
					 库名、表名
	功能：添加添加库名、表名
	输出：成功返回true,失败返回false
	*/
	bool dataMangement::add_name(const NameQuery &nameQuery) {
		if (nameQuery.queryType == q_library_name || nameQuery.queryType == q_table_name)
			return add_database_name_or_table_name(nameQuery);
		return false;
	}
	/*
	输入：nameQUuery 库名
					库名、表名
		  colType	列类型
	功能：添加列名
	输出：成功返回true,失败返回false
	*/
	bool dataMangement::add_name(const NameQuery &nameQuery, const string &colType) {
		if (nameQuery.queryType == q_col_name)
			return add_col_name(nameQuery, colType);
		return false;
	}
	void dataMangement::set_cur_library_name(const string &libraryName)
	{
		this->nameMangementFilePtr->curLibraryName = libraryName;
		this->nameMangementFilePtr->nameTable.libraryName = libraryName;
		

	}
	/*
	输入：库名、表名、列名
	功能：查询这个列的类型
	输出：成功返回这个列的类型，失败返回a_error
	*/
	AttributeType dataMangement::quer_column_type(const string & libraryName, const string & tableName, const string & columnName)
	{
		const NameQueryIndex index = query_name_inner(NameQuery(libraryName, tableName, columnName));
		if (index.flag) {
			return this->nameMangementFilePtr->nameTable.tableMangement[index.tableNameIndex].column[index.colNameIndex].attributeType;
		}

		return a_error;
	}
	bool dataMangement::check_all_column_type_in_table(const string&libraryName, const string&tableName, vector<string>&str, vector<AttributeType>&type)
	{
		int i;
		const NameQueryIndex index = query_name_inner(NameQuery(libraryName, tableName));
		if (index.flag) {
			vector<CNT>&columnMangement = this->nameMangementFilePtr->nameTable.tableMangement[index.databaseNameIndex].column;
			if (columnMangement.size() != type.size())return false;
			for (i = 0; columnMangement.size(); i++) {
				if (columnMangement[i].attributeType != type[i]||
					(type[i] == a_string&&columnMangement[i].type_size()<str.size()-1)) {
					return false;
				}
			}
		}
		return true;
	}
	/*
	输入：nameQUuery 库名
					 库名、表名
	功能：添加库名或者表名
	输出：成功返回true，失败返回false
	*/
	bool dataMangement::add_database_name_or_table_name(const NameQuery &nameQuery) {
		if (nameQuery.queryType == q_col_name)return false;
		if (nameQuery.queryType == q_library_name) {
			NameQueryIndex databaseTemp = query_name_inner(nameQuery);
			if (!databaseTemp.flag) {
				nameMangementFilePtr->libraryNameTable.push_back(nameQuery.libraryName);
				return true;
			}
		}
		else if (nameQuery.queryType == q_table_name) {
			NameQuery tableNameQuery = nameQuery;
			tableNameQuery.queryType = q_table_name;
			NameQueryIndex talbeTemp = query_name_inner(tableNameQuery);
			if (nameMangementFilePtr->curLibraryName == nameQuery.libraryName&&!talbeTemp.flag) { //数据库查询成功，表名未找到
				nameMangementFilePtr->nameTable.tableMangement.push_back(TableNameMangement(nameQuery.tableName, 0, vector<CNT>()));
				nameMangementFilePtr->nameTable.tableSize = nameMangementFilePtr->nameTable.tableMangement.size();
				return true;
			}
		}

		return false;
	}
	/*
	输入：			 nameQUuery 库名	列类型
					 库名、表名			列类型
	功能：添加列名
	输出：成功返回true,失败返回false
	*/
	bool dataMangement::add_col_name(const NameQuery &nameQuery, const string &colType) {
		if (nameQuery.queryType == q_col_name) {
			NameQuery tableNameQuery = nameQuery;
			tableNameQuery.queryType = q_table_name;
			NameQueryIndex tableTemp = query_name_inner(tableNameQuery), colTemp = query_name_inner(nameQuery);
			if (nameMangementFilePtr->curLibraryName == nameQuery.libraryName&&tableTemp.flag&&!colTemp.flag) {
				nameMangementFilePtr->nameTable.tableMangement[tableTemp.tableNameIndex].column.push_back(CNT(nameQuery.colName, colType));
				return true;
			}
		}
		return false;
	}
	/*数据库名*/
	NameQuery::NameQuery(const string &databaseName) {
		this->libraryName = databaseName;
		queryType = q_library_name;
	}
	/*数据库名，表名*/
	NameQuery::NameQuery(const string &databaseName, const string &tableName) {
		this->libraryName = databaseName;
		this->tableName = tableName;
		queryType = q_table_name;
	}
	/*数据库名，表名，列名*/
	NameQuery::NameQuery(const string &databaseName, const string &tableName, const string &colName) {
		this->libraryName = databaseName;
		this->tableName = tableName;
		this->colName = colName;
		queryType = q_col_name;
	}

	NameQuery & NameQuery::operator=(const NameQuery &obj) {
		this->colName = obj.colName;
		this->libraryName = obj.libraryName;
		this->queryType = obj.queryType;
		this->tableName = obj.tableName;
		return *this;
	}

	NameQueryIndex::NameQueryIndex(const size_t & databaseNameIndex) {
		this->databaseNameIndex = databaseNameIndex;
		this->flag = true;
		queryType = q_library_name;
	}

	NameQueryIndex::NameQueryIndex(const size_t & databaseNameIndex, const size_t & tableNameIndex) {
		this->databaseNameIndex = databaseNameIndex;
		this->tableNameIndex = tableNameIndex;
		this->flag = true;
		queryType = q_table_name;
	}

	NameQueryIndex::NameQueryIndex(const size_t & databaseNameIndex, const size_t & tableNameIndex, const size_t & colNameIndex) {
		this->databaseNameIndex = databaseNameIndex;
		this->tableNameIndex = tableNameIndex;
		this->colNameIndex = colNameIndex;
		this->flag = true;
		queryType = q_col_name;
	}

	NameQueryIndex::NameQueryIndex() {
		flag = false;
	}

	dataMangement::dataMangement()
	{
		nameMangementFilePtr = databaseFile.nameMangementTablePtr;
		//	this->nameMangement.set_nameMangementFile( this->databaseFile.nameMangementTablePtr);//delete at 2020/2/16
	//	set_nameMangementFile(this->databaseFile.nameMangementTablePtr);
	
		//read_index_ini();
	}

	dataMangement::dataMangement(const string & libraryName)
	{
		//read_index_ini();
		set_library(libraryName);
	}

	string dataMangement::get_currently_library_name()
	{
		return this->nameMangementFilePtr->curLibraryName;
	}

	void dataMangement::set_library(const string & librarName)
	{
		this->databaseFile.set_current_database_name(librarName);
		this->databaseFile.read_database_data(librarName);
	}

	bool dataMangement::query_data(const NameQuery & nameQuery)const
	{
		//	return this->nameMangement.query_name(nameQuery);//delete at 2020/2/16
		return query_name(nameQuery);
	}
	/*
	输入：	库名
			库名、表名
			库名、表名、列名
	功能：修改库名、表名、列名为nameQuery，并执行文件名字的更改
	输出：有该名字返回true,没有返回false
	*/
	bool dataMangement::modification_name(const NameQuery & nameQuery, const string&modeficationedName)
	{
		//bool flag = this->nameMangement.modification_name(nameQuery, modeficationedName);//delete at 2020/2/16
		bool flag = nameMangeMent_modification_name(nameQuery, modeficationedName);
		if (flag) {
			if (nameQuery.queryType == q_library_name) {//修改库名
				string oldPath = DATABASE_HOME_PATH(nameQuery.libraryName), newPath = DATABASE_HOME_PATH(modeficationedName);
				string oldIniPath = string(oldPath + "\\" + nameQuery.libraryName + ".ini");
				string newIniPath = DATABASE_HOME_PATH(nameQuery.libraryName + "\\" + modeficationedName + ".ini");
				if (rename(oldIniPath.c_str(), newIniPath.c_str()))return false;//修改库配置文件的名字
				if (rename(oldPath.c_str(), newPath.c_str()))return false;//修改库文件的名字
				if (nameQuery.libraryName == this->databaseFile.dataMangementPtr->libraryName)
					this->databaseFile.dataMangementPtr->libraryName = nameQuery.libraryName;
			}
			int i;
			for (i = 0; i < this->databaseFile.dataMangementPtr->tableNumber; i++) {
				if (this->databaseFile.dataMangementPtr->table[i].headInfo.tableName == nameQuery.tableName)
					break;
			}
			if (i > this->databaseFile.dataMangementPtr->tableNumber)
				return false;
			if (nameQuery.queryType == q_table_name) {//修改表名
				string oldPath = DATABASE_HOME_PATH(nameQuery.libraryName + "\\" + nameQuery.tableName),
					newPath = DATABASE_HOME_PATH(nameQuery.libraryName + "\\" + modeficationedName);
				string oldIniPath = DATABASE_HOME_PATH(nameQuery.libraryName + "\\" + nameQuery.tableName + "\\" + nameQuery.tableName + ".ini"),
					newIniPath = DATABASE_HOME_PATH(nameQuery.libraryName + "\\" + nameQuery.tableName + "\\" + modeficationedName + ".ini");
				if (rename(oldIniPath.c_str(), newIniPath.c_str()))return false;//修改表配置文件的名字
				if (rename(string(oldPath).c_str(), string(newPath).c_str()))return false;//修改表文件夹名字
				this->databaseFile.dataMangementPtr->table[i].headInfo.tableName = modeficationedName;
				this->databaseFile.nameMangementTablePtr->nameTable.tableMangement[i].tableName = modeficationedName;
				//	this->databaseFile.dataMangementPtr->table[i].headInfo.modificationTime = get_current_time();
			}
			return true;
		}
		return false;
	}
	/*
	输入：	库名
			库名、表名
	功能：删除库名、表名nameQuery，并执行文件名字的更改
	输出：有该名字返回true,没有返回false
	*/
	bool dataMangement::delete_talbe_or_library(const NameQuery & nameQuery)
	{
		if (nameQuery.queryType == q_col_name)return false;
		//bool flag=this->nameMangement.query_name(nameQuery); //delete at 2020/2/16
		bool flag = query_name(nameQuery);
		if (flag) {
			string filePath;
			if (nameQuery.queryType == q_col_name) {

				flag = delete_column(nameQuery.libraryName, nameQuery.tableName, nameQuery.colName);
				if (!flag)return false;
				/*flag=this->nameMangement.delete_name(nameQuery);
				if (!flag)return false;*/
			}

			else {//库名或表名
			//	flag  = this->nameMangement.delete_name(nameQuery);//delete at 2020/2/16
				flag = delete_name(nameQuery);
				if (nameQuery.queryType == q_library_name) {//库名
					filePath = DATABASE_HOME_PATH(nameQuery.libraryName);
				}
				else {//表名
					filePath = DATABASE_HOME_PATH(nameQuery.libraryName + "\\" + nameQuery.tableName);
				}
				if (_access(filePath.c_str(), 0) == 0) {//如果文件夹存在

					if (!delete_all_file(filePath.c_str())) {//删除失败
						cerr << nameQuery.libraryName << " delete failed!" << endl;
						return false;
					}
				}
				else {//文件夹不存在
					cerr << nameQuery.libraryName << "isn't exist!" << endl;
					return false;
				}

			}

		}
		else return false;
		return true;
	}
	/*
	输入：表名
	功能：获取表中列的信息
	输出：存在在表返回列信息，否则返回大小零的集合
	*/
	vector<CNT> dataMangement::get_column_info_in_table(const string & tableName)
	{
		NameQueryIndex index = query_name_inner(NameQuery(this->get_currently_library_name(), tableName));
		if (index.flag) {
			return this->nameMangementFilePtr->nameTable.tableMangement[index.tableNameIndex].column;
		}
		return vector<CNT>();
	}
	/*
	输入:libraryName库名、tableName表名、colName列名
	功能：删除colName列名
	输出:删除成功返回true,失败返回flase
	*/
	bool dataMangement::delete_column(const string&libraryName, const string&tableName, const string&colName)
	{

		if (this->databaseFile.dataMangementPtr->libraryName == libraryName) {
			int i;
			for (i = 0; i < this->databaseFile.nameMangementTablePtr->nameTable.tableSize; i++) {//寻找表
				if (tableName == this->databaseFile.nameMangementTablePtr->nameTable.tableMangement[i].tableName)break;
			}
			if (i >= this->databaseFile.nameMangementTablePtr->nameTable.tableSize)return false;
			else {
				int j;
				for (j = 0; j < this->databaseFile.nameMangementTablePtr->nameTable.tableMangement[i].colSize; j++) {//寻找列号
					if (this->databaseFile.nameMangementTablePtr->nameTable.tableMangement[i].column[j].colName == colName)break;
				}
				if (j >= this->databaseFile.nameMangementTablePtr->nameTable.tableMangement[i].colSize)return false;
				int temp = j;
				vector<AttributeType>::iterator begin = this->databaseFile.dataMangementPtr->table[i].headInfo.type.begin(),
					end = this->databaseFile.dataMangementPtr->table[i].headInfo.type.end();
				while (begin != end&&temp > 0) {
					begin++;
					temp--;
				}
				this->databaseFile.dataMangementPtr->table[i].headInfo.type.erase(begin);//删除列类型
				this->databaseFile.dataMangementPtr->table[i].headInfo.tableTypeNum -= 1;
				size_t size = this->databaseFile.nameMangementTablePtr->nameTable.tableMangement[i].column[j].type_size();
				list<shared_ptr<Page>>::iterator pageBegin = this->databaseFile.dataMangementPtr->table[i].pagePtrSet.begin(),
					pageEnd = this->databaseFile.dataMangementPtr->table[i].pagePtrSet.end();
				unsigned tableUsedSpaceSize = 0;
				while (pageBegin != pageEnd) {//页遍历
					list<shared_ptr<Item>>&itemSetPtr = (*pageBegin)->itemPtrSet;
					list<shared_ptr<Item>>::iterator itemBegin(itemSetPtr.begin()), itemEnd(itemSetPtr.end());
					vector<DataType>::iterator iter;
					while (itemBegin != itemEnd) {//数据遍历
						iter = (*itemBegin)->item.begin();
						iter += j;
						(*itemBegin)->item.erase(iter);
						itemBegin++;
					}
					(*pageBegin)->dirtyPage = true;
					(*pageBegin)->usedSpaceSize -= (*pageBegin)->itemSize*size;//减去已删除的列所占用的空间
					(*pageBegin)->unUsedSpaceSize = (*pageBegin)->pageSpaceMax - (*pageBegin)->usedSpaceSize;//未使用空间
					tableUsedSpaceSize += (*pageBegin)->usedSpaceSize;//统计表已使用大小
					pageBegin++;

				}
				this->databaseFile.dataMangementPtr->table[i].headInfo.usedSpaceSize = tableUsedSpaceSize;
				//this->databaseFile.dataMangementPtr->table[i].headInfo.
				//this->nameMangement.delete_name(NameQuery(libraryName, tableName, colName)); //delete at 2020/2/16
				delete_name(NameQuery(libraryName, tableName, colName));
			}
			return true;
		}
		return false;
	}
	/*
	输入：库名
		  库名	表名
	功能：添加库名、表名及文件操作
	输出：添加成功返回true,失败返回false
	*/
	bool dataMangement::add_table_or_library(const NameQuery & nameQuery)
	{
		if (nameQuery.queryType == q_col_name)return false;//不支持列添加
		if (query_data(nameQuery))return false;//有此名字
		if (nameQuery.queryType == q_library_name) {//添加库名
			this->databaseFile.nameMangementTablePtr->libraryNameTable.push_back(nameQuery.libraryName);
			string path = DATABASE_HOME_PATH(nameQuery.libraryName);
			if (_mkdir(path.c_str()))return false;//文件夹创建失败
			path += "\\" + nameQuery.libraryName + ".ini";
			if (!create_file(path))return false;
		}
		else {//添加表名
			Record record;
			if (nameQuery.libraryName != this->databaseFile.nameMangementTablePtr->curLibraryName)return false;
			record.headInfo.tableName = nameQuery.tableName;
			record.headInfo.addTiem = record.headInfo.modificationTime = get_current_time();
			this->databaseFile.dataMangementPtr->table.push_back(record);
			this->databaseFile.nameMangementTablePtr->nameTable.tableSize++;

			TableNameMangement temp;
			temp.tableName = nameQuery.tableName;
			temp.colSize = 0;
			this->databaseFile.nameMangementTablePtr->nameTable.tableMangement.push_back(temp);
			this->databaseFile.dataMangementPtr->tableNumber++;
			string path = DATABASE_HOME_PATH(nameQuery.libraryName + "\\" + nameQuery.tableName);
			if (_mkdir(path.c_str()))return false;
			path += "\\" + nameQuery.tableName + ".ini";
			if (!create_file(path))return false;
		}
		return true;
	}
	/*
	输入：库名、表名、列名、列类型
	功能：添加列
	输出：成功返回true,失败返回false
	*/
	bool dataMangement::add_column(const string & libraryName, const string & tableName, const string & columnName, const string& type)
	{
		if (query_data(NameQuery(libraryName, tableName, columnName)))return false;
		int i;
		if (this->databaseFile.nameMangementTablePtr->curLibraryName != libraryName)return false;
		for (i = 0; i < this->databaseFile.nameMangementTablePtr->nameTable.tableSize; i++) {//find talbe name
			if (this->databaseFile.nameMangementTablePtr->nameTable.tableMangement[i].tableName == tableName)break;
		}
		if (i >= this->databaseFile.nameMangementTablePtr->nameTable.tableSize)return false;// talbe name not found
		this->databaseFile.nameMangementTablePtr->nameTable.tableMangement[i].column.push_back(CNT(columnName, type));
		this->databaseFile.nameMangementTablePtr->nameTable.tableMangement[i].colSize =
			this->databaseFile.nameMangementTablePtr->nameTable.tableMangement[i].column.size();
		this->databaseFile.dataMangementPtr->table[i].headInfo.tableTypeNum++;
		if (type[0] == 'i')
			this->databaseFile.dataMangementPtr->table[i].headInfo.type.push_back(a_int);
		else if (type[0] == 'f')
			this->databaseFile.dataMangementPtr->table[i].headInfo.type.push_back(a_flaot);
		else
			this->databaseFile.dataMangementPtr->table[i].headInfo.type.push_back(a_string);
		return true;
	}
	inline void dataMangement::newPage(int tableIndex, size_t colSize, size_t pageSize, Item item)
	{
		shared_ptr<Page> temp=make_shared<Page>(new Page());
		temp->curPageNum = ++this->databaseFile.dataMangementPtr->table[tableIndex].headInfo.pageNumber;//当前页数
		temp->dirtyPage = true;
		temp->nextPageFlag = false;
		temp->itemSize++;
		temp->usedSpaceSize += colSize;
		temp->unUsedSpaceSize -= colSize;
		temp->itemPtrSet.push_back(make_shared<Item>(item));
		this->databaseFile.dataMangementPtr->table[tableIndex].headInfo.pageOrder.push_back(temp->curPageNum);
		this->databaseFile.dataMangementPtr->table[tableIndex].headInfo.totalDataNum++;
		this->databaseFile.dataMangementPtr->table[tableIndex].headInfo.usedSpaceSize += colSize;
		this->databaseFile.dataMangementPtr->table[tableIndex].pagePtrSet.push_back(temp);
	}
	/*
	输入：InsertData类型
	功能：插入数据
	输出：成功返回true,失败返回false
	*/
	bool dataMangement::add_data(const InsertData & data)
	{
		if (/*data.data.values.size() != data.data.type.size()|| */
			!query_data(NameQuery(this->databaseFile.dataMangementPtr->libraryName, data.tableName)))
			return false;
		int i;
		for (i = 0; i < this->databaseFile.dataMangementPtr->table.size(); i++)
			if (data.tableName == this->databaseFile.nameMangementTablePtr->nameTable.tableMangement[i].tableName)break;
		if (i >= this->databaseFile.dataMangementPtr->table.size())return false;

		int j, pageSize = this->databaseFile.dataMangementPtr->table[i].headInfo.pageNumber, colSize = 0;//页大小
		if (this->databaseFile.nameMangementTablePtr->nameTable.tableMangement[i].colSize != data.data.size())return false;//两者列数不等
		bool flag = false;//表示未插入
		for (j = 0; j < this->databaseFile.nameMangementTablePtr->nameTable.tableMangement[i].colSize; j++) {
			colSize += this->databaseFile.nameMangementTablePtr->nameTable.tableMangement[i].column[j].type_size();
		}
		list<shared_ptr<Page>>&page = this->databaseFile.dataMangementPtr->table[i].pagePtrSet;
		list<shared_ptr<Page>>::iterator pageBegin(page.begin()), pageEnd(page.end());
		list<shared_ptr<Page>>::iterator pageTemp = page.begin();
		for (j = 0; j < pageSize; j++) {//遍历页
			if ((*pageTemp)->unUsedSpaceSize >= colSize) {//有空间可插
				flag = true;
				break;
			}
			pageTemp++;
		}
		Item item;
		for (j = 0; j < data.data.size(); j++) {
			item.item.push_back(DataType(data.data.values[j]));
		}
		if (flag) {//有空间可插
			if ((*pageTemp)->deletedFlag.size()>0) {
				int deleteIndex = (*pageTemp)->deletedFlag[0];
				(*pageTemp)->deletedFlag.erase((*pageTemp)->deletedFlag.begin());
				list<shared_ptr<Item>>::iterator itemBegin((*pageTemp)->itemPtrSet.begin()),
					itemEnd((*pageTemp)->itemPtrSet.end());
				for (j = 0; j < deleteIndex; j++) {
					itemBegin++;
				}
				*(*itemBegin) = item;
			}
			else
				(*pageTemp)->itemPtrSet.push_back(make_shared<Item>(item));//增加增

			(*pageTemp)->dirtyPage = true;//脏页
			(*pageTemp)->itemSize++;//项数加一
			(*pageTemp)->unUsedSpaceSize -= colSize;//未使用空间-列空间
			(*pageTemp)->usedSpaceSize += colSize;//已使用空间+列空间
			this->databaseFile.dataMangementPtr->table[i].headInfo.usedSpaceSize += colSize;//总计空间+列空间
			this->databaseFile.dataMangementPtr->table[i].headInfo.totalDataNum++;//总数加一

		}
		else {//新开一页
			if (pageSize > 0) {

				(*pageTemp)->nextPageFlag = true;//脏页
				(*pageTemp)->nextPageNum = this->databaseFile.dataMangementPtr->table[i].headInfo.pageNumber + 1;//下一页
			}
			newPage(i, colSize, pageSize, item);
		}

		return true;
	}
	/*
	输入：删除数据结构
	功能：删除数据
	输出：成功返回true,失败返回false
	*/
	bool dataMangement::delete_data(const DeleteData & data)
	{
		if (!query_data(NameQuery(this->databaseFile.nameMangementTablePtr->curLibraryName, data.tableName)))return false;
		int i, j;
		for (i = 0; i < this->databaseFile.nameMangementTablePtr->nameTable.tableSize; i++) {//find table index
			if (data.tableName == this->databaseFile.nameMangementTablePtr->nameTable.tableMangement[i].tableName)break;
		}
		if (i < this->databaseFile.nameMangementTablePtr->nameTable.tableSize) {//founded table 
			list<shared_ptr<Page>>&pageSet = this->databaseFile.dataMangementPtr->table[i].pagePtrSet;
			unsigned pageSize = this->databaseFile.dataMangementPtr->table[i].headInfo.pageNumber;
			list<shared_ptr<Page>>::iterator pageBegin(pageSet.begin()), pageEnd(pageSet.end());
			list<shared_ptr<Item>>::iterator itemBegin, itemEnd;
			bool flag = false;
			Item item;
			unsigned deletedIndex = 0;
			for (j = 0; j < data.values.size(); j++) {
				item.item.push_back(data.values[j]);
			}
			for (; pageBegin != pageSet.end(); pageBegin++) {
				itemBegin = (*pageBegin)->itemPtrSet.begin(),
					itemEnd = (*pageBegin)->itemPtrSet.end();
				deletedIndex = 0;
				for (; itemBegin != itemEnd; itemBegin++, deletedIndex++) {//寻找数据
					if (item == *(*itemBegin)) {
						flag = true;
						break;
					}
				}
				if (flag)break;
			}
			if (!flag)return false;
			//(*pageBegin)->itemPtrSet.erase(itemBegin);
			unsigned colSize = 0;
			for (j = 0; j < this->databaseFile.nameMangementTablePtr->nameTable.tableMangement[i].colSize; j++) {
				colSize += this->databaseFile.nameMangementTablePtr->nameTable.tableMangement[i].column[j].type_size();
			}
			(*pageBegin)->deletedFlag.push_back(deletedIndex);//伪删除
			(*pageBegin)->dirtyPage = true;
			(*pageBegin)->itemSize--;
			(*pageBegin)->unUsedSpaceSize += colSize;
			(*pageBegin)->usedSpaceSize -= colSize;
			this->databaseFile.dataMangementPtr->table[i].headInfo.usedSpaceSize -= colSize;
			this->databaseFile.dataMangementPtr->table[i].headInfo.totalDataNum--;
		}


		return true;
	}


	bool dataMangement::save()
	{
		return this->databaseFile.save();
	}
	/*
	输入：表名、result
	功能：get表名为tableName的数据
	输出：成功返回true,失败返回false
	*/
	resultData_ptr dataMangement::table_data(const string&tableName)
	{
		resultData_ptr result=new resultData();
		if (!query_data(NameQuery(this->databaseFile.nameMangementTablePtr->curLibraryName, tableName)))return nullptr;
		int i;
		for (i = 0; i < this->databaseFile.dataMangementPtr->tableNumber; i++)
			if (tableName == this->databaseFile.dataMangementPtr->table[i].headInfo.tableName)break;
		if (i >= this->databaseFile.dataMangementPtr->tableNumber)return nullptr;
		result->ColName = this->databaseFile.nameMangementTablePtr->nameTable.tableMangement[i].column;
		result->recordHeadInfo =this->databaseFile.dataMangementPtr->table[i].headInfo;
		list<shared_ptr<Page>>&pageSet = this->databaseFile.dataMangementPtr->table[i].pagePtrSet;
		list<shared_ptr<Page>>::iterator pageBegn(pageSet.begin()), pageEnd(pageSet.end());
		for (; pageBegn != pageEnd; pageBegn++) {
			result->page.push_back(**pageBegn);
		}
		return result;
	}


	size_t Data::size()const
	{
		return this->values.size();
	}


	InsertData::InsertData(const string & tableName, const string & values)
	{
		this->set_tableName(tableName);
		this->add_data(values);
	}

	InsertData::InsertData(const string & tableName, const vector<string>& values)
	{
		this->set_tableName(tableName);
		this->add_data(values);
	}

	void InsertData::set_tableName(const string & tableName)
	{

		this->tableName = tableName;
	}

	void InsertData::add_data(const string & value)
	{
		this->data.values.push_back(value);
	}

	void InsertData::add_data(const vector<string>& value)
	{
		this->data.values = value;
	}


	void InsertData::check()
	{
	}

	void DeleteData::set_tableName(const string & tableName)
	{
		this->tableName = tableName;
	}

	void DeleteData::add_data(const string & value)
	{
		this->values.push_back(value);
	}

	resultData & resultData::operator=(const resultData & obj)
	{
		this->page = obj.page;
		this->recordHeadInfo = obj.recordHeadInfo;
		return *this;
	}
}