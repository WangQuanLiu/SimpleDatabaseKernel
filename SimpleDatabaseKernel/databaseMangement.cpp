#include"databaseMangement.h"
namespace dbm {
	
	/*
	���룺����
		  ����������
		  ����������������
	���ܣ��и�����NameQuery->flag Ϊtrue �����ÿ����±꣬�����±꣬�����±�
		  û�и�����NameQuery->flagΪfalse
	�����flag
	*/
	NameQueryIndex dataMangement::query_name_inner(const NameQuery &nameQuery) const {
		int i;
		for (i = 0; i < nameMangementFilePtr->libraryNameTable.size(); i++) //��ѯ����
			if (nameQuery.libraryName == nameMangementFilePtr->libraryNameTable[i]) {
				break;
			}
		if (i < nameMangementFilePtr->libraryNameTable.size()) {
			if (nameQuery.queryType == q_library_name)return NameQueryIndex(i);
			int j;
			if (nameMangementFilePtr->curLibraryName == nameQuery.libraryName) {
				for (j = 0; j < nameMangementFilePtr->nameTable.tableMangement.size(); j++) {//��ѯ����
					if (nameQuery.tableName == nameMangementFilePtr->nameTable.tableMangement[j].tableName) break;
				}
				if (j < nameMangementFilePtr->nameTable.tableSize) {
					if (nameQuery.queryType == q_table_name)return NameQueryIndex(i, j);
					int k;
					for (k = 0; k < nameMangementFilePtr->nameTable.tableMangement[j].colSize; k++) {//��ѯ����
						if (nameQuery.colName == nameMangementFilePtr->nameTable.tableMangement[j].column[k].colName)return NameQueryIndex(i, j, k);
					}
				}
			}
		}
		return NameQueryIndex();
	}
	/*
	���룺����
		  ����������
		  ����������������
	���ܣ�query_name ��ѯ�ÿ��� �� ���� ������
	������и����ַ���true,û�з���false
	*/
	bool dataMangement::query_name(const NameQuery &nameQuery) const {
		return query_name_inner(nameQuery).flag;
	}
	/*
	���룺	����				������
			����������			������
			����������������	������
	���ܣ��Ŀ���������������ΪnameQuery
	������и����ַ���true,û�з���false
	*/
	bool dataMangement::nameMangeMent_modification_name(const NameQuery &nameQuery, const string &modficationedName) {
		NameQueryIndex temp = query_name_inner(nameQuery);
		if (temp.flag) {
			if (temp.queryType == q_library_name) {//�޸Ŀ���
				nameMangementFilePtr->libraryNameTable[temp.databaseNameIndex] = modficationedName;
				if (nameMangementFilePtr->curLibraryName == nameQuery.libraryName) {
					nameMangementFilePtr->nameTable.libraryName = modficationedName;
					nameMangementFilePtr->curLibraryName = modficationedName;
				}
			}
			else if (temp.queryType == q_table_name) {//�޸ı���
				nameMangementFilePtr->nameTable.tableMangement[temp.tableNameIndex].tableName = modficationedName;

			}
			else {//�޸�����
				nameMangementFilePtr->nameTable.tableMangement[temp.tableNameIndex].column[temp.colNameIndex].colName = modficationedName;
			}

		}
		return temp.flag;
	}
	/*
	���룺	����
			����������
			����������������
	���ܣ�ɾ������������������ΪnameQuery
	������и����ַ���true,û�з���false
	*/
	bool dataMangement::delete_name(const NameQuery &nameQuery) {
		const NameQueryIndex temp = static_cast<const NameQueryIndex>(query_name_inner(nameQuery));
		if (temp.flag) {
			if (temp.queryType == q_library_name) {	//ɾ������
				vector<string>::iterator iter = nameMangementFilePtr->libraryNameTable.begin() + temp.databaseNameIndex;
				if (nameMangementFilePtr->nameTable.libraryName == nameMangementFilePtr->libraryNameTable[temp.databaseNameIndex]) {
					nameMangementFilePtr->nameTable.clear();//��տ��е������ļ�
					nameMangementFilePtr->curLibraryName = Q_EMPTY;
				}
				nameMangementFilePtr->libraryNameTable.erase(iter);

			}
			else if (temp.queryType == q_table_name) {//ɾ������
				vector<TableNameMangement>::iterator iter = nameMangementFilePtr->nameTable.tableMangement.begin() + temp.tableNameIndex;
				nameMangementFilePtr->nameTable.tableMangement.erase(iter);
				nameMangementFilePtr->nameTable.tableSize = nameMangementFilePtr->nameTable.tableMangement.size();
			}
			//ɾ������
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
	���룺nameQUuery ����
					 ����������
	���ܣ������ӿ���������
	������ɹ�����true,ʧ�ܷ���false
	*/
	bool dataMangement::add_name(const NameQuery &nameQuery) {
		if (nameQuery.queryType == q_library_name || nameQuery.queryType == q_table_name)
			return add_database_name_or_table_name(nameQuery);
		return false;
	}
	/*
	���룺nameQUuery ����
					����������
		  colType	������
	���ܣ��������
	������ɹ�����true,ʧ�ܷ���false
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
	���룺����������������
	���ܣ���ѯ����е�����
	������ɹ���������е����ͣ�ʧ�ܷ���a_error
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
	���룺nameQUuery ����
					 ����������
	���ܣ���ӿ������߱���
	������ɹ�����true��ʧ�ܷ���false
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
			if (nameMangementFilePtr->curLibraryName == nameQuery.libraryName&&!talbeTemp.flag) { //���ݿ��ѯ�ɹ�������δ�ҵ�
				nameMangementFilePtr->nameTable.tableMangement.push_back(TableNameMangement(nameQuery.tableName, 0, vector<CNT>()));
				nameMangementFilePtr->nameTable.tableSize = nameMangementFilePtr->nameTable.tableMangement.size();
				return true;
			}
		}

		return false;
	}
	/*
	���룺			 nameQUuery ����	������
					 ����������			������
	���ܣ��������
	������ɹ�����true,ʧ�ܷ���false
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
	/*���ݿ���*/
	NameQuery::NameQuery(const string &databaseName) {
		this->libraryName = databaseName;
		queryType = q_library_name;
	}
	/*���ݿ���������*/
	NameQuery::NameQuery(const string &databaseName, const string &tableName) {
		this->libraryName = databaseName;
		this->tableName = tableName;
		queryType = q_table_name;
	}
	/*���ݿ���������������*/
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
	���룺	����
			����������
			����������������
	���ܣ��޸Ŀ���������������ΪnameQuery����ִ���ļ����ֵĸ���
	������и����ַ���true,û�з���false
	*/
	bool dataMangement::modification_name(const NameQuery & nameQuery, const string&modeficationedName)
	{
		//bool flag = this->nameMangement.modification_name(nameQuery, modeficationedName);//delete at 2020/2/16
		bool flag = nameMangeMent_modification_name(nameQuery, modeficationedName);
		if (flag) {
			if (nameQuery.queryType == q_library_name) {//�޸Ŀ���
				string oldPath = DATABASE_HOME_PATH(nameQuery.libraryName), newPath = DATABASE_HOME_PATH(modeficationedName);
				string oldIniPath = string(oldPath + "\\" + nameQuery.libraryName + ".ini");
				string newIniPath = DATABASE_HOME_PATH(nameQuery.libraryName + "\\" + modeficationedName + ".ini");
				if (rename(oldIniPath.c_str(), newIniPath.c_str()))return false;//�޸Ŀ������ļ�������
				if (rename(oldPath.c_str(), newPath.c_str()))return false;//�޸Ŀ��ļ�������
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
			if (nameQuery.queryType == q_table_name) {//�޸ı���
				string oldPath = DATABASE_HOME_PATH(nameQuery.libraryName + "\\" + nameQuery.tableName),
					newPath = DATABASE_HOME_PATH(nameQuery.libraryName + "\\" + modeficationedName);
				string oldIniPath = DATABASE_HOME_PATH(nameQuery.libraryName + "\\" + nameQuery.tableName + "\\" + nameQuery.tableName + ".ini"),
					newIniPath = DATABASE_HOME_PATH(nameQuery.libraryName + "\\" + nameQuery.tableName + "\\" + modeficationedName + ".ini");
				if (rename(oldIniPath.c_str(), newIniPath.c_str()))return false;//�޸ı������ļ�������
				if (rename(string(oldPath).c_str(), string(newPath).c_str()))return false;//�޸ı��ļ�������
				this->databaseFile.dataMangementPtr->table[i].headInfo.tableName = modeficationedName;
				this->databaseFile.nameMangementTablePtr->nameTable.tableMangement[i].tableName = modeficationedName;
				//	this->databaseFile.dataMangementPtr->table[i].headInfo.modificationTime = get_current_time();
			}
			return true;
		}
		return false;
	}
	/*
	���룺	����
			����������
	���ܣ�ɾ������������nameQuery����ִ���ļ����ֵĸ���
	������и����ַ���true,û�з���false
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

			else {//���������
			//	flag  = this->nameMangement.delete_name(nameQuery);//delete at 2020/2/16
				flag = delete_name(nameQuery);
				if (nameQuery.queryType == q_library_name) {//����
					filePath = DATABASE_HOME_PATH(nameQuery.libraryName);
				}
				else {//����
					filePath = DATABASE_HOME_PATH(nameQuery.libraryName + "\\" + nameQuery.tableName);
				}
				if (_access(filePath.c_str(), 0) == 0) {//����ļ��д���

					if (!delete_all_file(filePath.c_str())) {//ɾ��ʧ��
						cerr << nameQuery.libraryName << " delete failed!" << endl;
						return false;
					}
				}
				else {//�ļ��в�����
					cerr << nameQuery.libraryName << "isn't exist!" << endl;
					return false;
				}

			}

		}
		else return false;
		return true;
	}
	/*
	���룺����
	���ܣ���ȡ�����е���Ϣ
	����������ڱ�������Ϣ�����򷵻ش�С��ļ���
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
	����:libraryName������tableName������colName����
	���ܣ�ɾ��colName����
	���:ɾ���ɹ�����true,ʧ�ܷ���flase
	*/
	bool dataMangement::delete_column(const string&libraryName, const string&tableName, const string&colName)
	{

		if (this->databaseFile.dataMangementPtr->libraryName == libraryName) {
			int i;
			for (i = 0; i < this->databaseFile.nameMangementTablePtr->nameTable.tableSize; i++) {//Ѱ�ұ�
				if (tableName == this->databaseFile.nameMangementTablePtr->nameTable.tableMangement[i].tableName)break;
			}
			if (i >= this->databaseFile.nameMangementTablePtr->nameTable.tableSize)return false;
			else {
				int j;
				for (j = 0; j < this->databaseFile.nameMangementTablePtr->nameTable.tableMangement[i].colSize; j++) {//Ѱ���к�
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
				this->databaseFile.dataMangementPtr->table[i].headInfo.type.erase(begin);//ɾ��������
				this->databaseFile.dataMangementPtr->table[i].headInfo.tableTypeNum -= 1;
				size_t size = this->databaseFile.nameMangementTablePtr->nameTable.tableMangement[i].column[j].type_size();
				list<shared_ptr<Page>>::iterator pageBegin = this->databaseFile.dataMangementPtr->table[i].pagePtrSet.begin(),
					pageEnd = this->databaseFile.dataMangementPtr->table[i].pagePtrSet.end();
				unsigned tableUsedSpaceSize = 0;
				while (pageBegin != pageEnd) {//ҳ����
					list<shared_ptr<Item>>&itemSetPtr = (*pageBegin)->itemPtrSet;
					list<shared_ptr<Item>>::iterator itemBegin(itemSetPtr.begin()), itemEnd(itemSetPtr.end());
					vector<DataType>::iterator iter;
					while (itemBegin != itemEnd) {//���ݱ���
						iter = (*itemBegin)->item.begin();
						iter += j;
						(*itemBegin)->item.erase(iter);
						itemBegin++;
					}
					(*pageBegin)->dirtyPage = true;
					(*pageBegin)->usedSpaceSize -= (*pageBegin)->itemSize*size;//��ȥ��ɾ��������ռ�õĿռ�
					(*pageBegin)->unUsedSpaceSize = (*pageBegin)->pageSpaceMax - (*pageBegin)->usedSpaceSize;//δʹ�ÿռ�
					tableUsedSpaceSize += (*pageBegin)->usedSpaceSize;//ͳ�Ʊ���ʹ�ô�С
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
	���룺����
		  ����	����
	���ܣ���ӿ������������ļ�����
	�������ӳɹ�����true,ʧ�ܷ���false
	*/
	bool dataMangement::add_table_or_library(const NameQuery & nameQuery)
	{
		if (nameQuery.queryType == q_col_name)return false;//��֧�������
		if (query_data(nameQuery))return false;//�д�����
		if (nameQuery.queryType == q_library_name) {//��ӿ���
			this->databaseFile.nameMangementTablePtr->libraryNameTable.push_back(nameQuery.libraryName);
			string path = DATABASE_HOME_PATH(nameQuery.libraryName);
			if (_mkdir(path.c_str()))return false;//�ļ��д���ʧ��
			path += "\\" + nameQuery.libraryName + ".ini";
			if (!create_file(path))return false;
		}
		else {//��ӱ���
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
	���룺������������������������
	���ܣ������
	������ɹ�����true,ʧ�ܷ���false
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
		temp->curPageNum = ++this->databaseFile.dataMangementPtr->table[tableIndex].headInfo.pageNumber;//��ǰҳ��
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
	���룺InsertData����
	���ܣ���������
	������ɹ�����true,ʧ�ܷ���false
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

		int j, pageSize = this->databaseFile.dataMangementPtr->table[i].headInfo.pageNumber, colSize = 0;//ҳ��С
		if (this->databaseFile.nameMangementTablePtr->nameTable.tableMangement[i].colSize != data.data.size())return false;//������������
		bool flag = false;//��ʾδ����
		for (j = 0; j < this->databaseFile.nameMangementTablePtr->nameTable.tableMangement[i].colSize; j++) {
			colSize += this->databaseFile.nameMangementTablePtr->nameTable.tableMangement[i].column[j].type_size();
		}
		list<shared_ptr<Page>>&page = this->databaseFile.dataMangementPtr->table[i].pagePtrSet;
		list<shared_ptr<Page>>::iterator pageBegin(page.begin()), pageEnd(page.end());
		list<shared_ptr<Page>>::iterator pageTemp = page.begin();
		for (j = 0; j < pageSize; j++) {//����ҳ
			if ((*pageTemp)->unUsedSpaceSize >= colSize) {//�пռ�ɲ�
				flag = true;
				break;
			}
			pageTemp++;
		}
		Item item;
		for (j = 0; j < data.data.size(); j++) {
			item.item.push_back(DataType(data.data.values[j]));
		}
		if (flag) {//�пռ�ɲ�
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
				(*pageTemp)->itemPtrSet.push_back(make_shared<Item>(item));//������

			(*pageTemp)->dirtyPage = true;//��ҳ
			(*pageTemp)->itemSize++;//������һ
			(*pageTemp)->unUsedSpaceSize -= colSize;//δʹ�ÿռ�-�пռ�
			(*pageTemp)->usedSpaceSize += colSize;//��ʹ�ÿռ�+�пռ�
			this->databaseFile.dataMangementPtr->table[i].headInfo.usedSpaceSize += colSize;//�ܼƿռ�+�пռ�
			this->databaseFile.dataMangementPtr->table[i].headInfo.totalDataNum++;//������һ

		}
		else {//�¿�һҳ
			if (pageSize > 0) {

				(*pageTemp)->nextPageFlag = true;//��ҳ
				(*pageTemp)->nextPageNum = this->databaseFile.dataMangementPtr->table[i].headInfo.pageNumber + 1;//��һҳ
			}
			newPage(i, colSize, pageSize, item);
		}

		return true;
	}
	/*
	���룺ɾ�����ݽṹ
	���ܣ�ɾ������
	������ɹ�����true,ʧ�ܷ���false
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
				for (; itemBegin != itemEnd; itemBegin++, deletedIndex++) {//Ѱ������
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
			(*pageBegin)->deletedFlag.push_back(deletedIndex);//αɾ��
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
	���룺������result
	���ܣ�get����ΪtableName������
	������ɹ�����true,ʧ�ܷ���false
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