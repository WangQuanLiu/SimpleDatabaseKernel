#include"databaseFile.h"
namespace dbm {
	DatabaseFile::DatabaseFile()
	{
		nameMangementTablePtr = shared_ptr<NameMangementFile>(new NameMangementFile());
		dataMangementPtr = shared_ptr<RecordTable>(new RecordTable());
		read_database_mangement_system_ini_file();
	}
	DatabaseFile::~DatabaseFile()
	{
		this->dataMangementPtr->clear();
		this->nameMangementTablePtr->clear();
	}
	/*
	���룺libraryName����
	����:��ȡlibraryName������
	���:�ɹ�����true,ʧ�ܷ���false
	*/
	bool DatabaseFile::read_database_data(const string & libraryName)
	{
		int i;
		set_current_database_name(libraryName);
		bool flag = read_database_ini_file(libraryName);
		if (flag == false)return false;
		for (i = 0; i < this->nameMangementTablePtr->nameTable.tableSize; i++) {
			flag = read_table_ini_file(this->nameMangementTablePtr->nameTable.tableMangement[i].tableName);//��ȡ�������ļ�
			if (!flag)return false;
			flag = read_table_data(this->nameMangementTablePtr->nameTable.tableMangement[i].tableName);//��ȡ������ 
			if (!flag)return false;
		}
		return true;
	}

	/*
	���ܣ���ȡlibraryname�Ŀ�����
	*/
	void DatabaseFile::set_current_database_name(const string & libraryName)
	{
		this->nameMangementTablePtr->curLibraryName = libraryName;
		this->dataMangementPtr->libraryName = libraryName;
		this->nameMangementTablePtr->nameTable.libraryName = libraryName;

	}
	/*
	���ܣ���ȡ���ݿ�������ļ�
	������ɹ�����true,ʧ�ܷ���false
	*/
	bool DatabaseFile::read_database_mangement_system_ini_file()
	{
		int size = 0, i, databaseNumber = 0, tableNumber = 0, tableSize = 0;
		char ch[BUFF_SIZE];
		LibraryNameMangement nameMangementTemp;//��
		TableNameMangement tableNameTemp;//��
		FILE*file = fopen(DATABASE_HOME_PATH("database.ini").c_str(), "r");
		vector<string>databaseName, tableName;//���ݿ���,����
		if (file == NULL)return false;
		fscanf(file, "<datbase number>\t%d", &size);
		fscanf(file, "%s %s\n", ch, ch);//�����ã���ȡ������ַ�
		for (i = 0; i < size; i++) {
			fscanf(file, "%s\n", ch);
			databaseName.push_back(ch);
		}
		fclose(file);
		this->nameMangementTablePtr->libraryNameTable = databaseName;
		return true;
	}
	/*
	���ܣ��������ݿ������ļ�
	������ɹ�����true,ʧ�ܷ���false
	*/
	bool DatabaseFile::save_database_mangement_system_ini_file()
	{
		FILE*file = fopen(DATABASE_HOME_PATH("database.ini").c_str(), "w");
		size_t size = nameMangementTablePtr->libraryNameTable.size(), i, databaseNumber = 0, tableNumber = 0, tableSize = 0;
		if (file == NULL)return false;
		fprintf(file, "<datbase number>\t%zd\n", size);
		fprintf(file, "<database name>\n");
		for (i = 0; i < nameMangementTablePtr->libraryNameTable.size(); i++) {
			fprintf(file, "%s\n", nameMangementTablePtr->libraryNameTable[i].c_str());
		}
		fclose(file);
		return true;
	}
	/*
	���룺databaseName���ݿ���
	���ܣ���ȡ��ΪdatabaseNmae�������ļ���������������
	������ɹ�����true,ʧ�ܷ���false
	*/
	bool DatabaseFile::read_database_ini_file(const string &databaseName)
	{
		int size = 0, i, tableNumber = 0, tableSize = 0, colSize = 0;
		char ch[BUFF_SIZE];
		TableNameMangement tableNameTemp;//��
		vector<string>tableName, colName, colType;
		FILE*file = fopen(DATABASE_HOME_PATH(databaseName + "\\" + databaseName + ".ini").c_str(), "r");
		if (file == NULL)return false;
		fscanf(file, "<table number>\t%d\n", &tableSize);
		if (tableSize == 0) {
			fclose(file);
			return true;
		}
		this->nameMangementTablePtr->nameTable.tableSize = tableSize;
		dataMangementPtr->tableNumber = tableSize;
		this->nameMangementTablePtr->nameTable.libraryName = databaseName;
		tableName.clear();//���
		fscanf(file, "%s %s", ch, ch);//�����ã���ȡ������ַ�
		while (tableSize--) {//��ȡ����
			fscanf(file, "%s", ch);
			tableName.push_back(ch);
		}
		tableNumber = 0;//���������
		while (!feof(file)) {
			while (fscanf(file, "%s", ch) && strcmp(ch, "<end>")) {
				//	fscanf(file, "col_number:%d", &colSize);//��ȡ������
				fscanf(file, "%s %s", ch, ch);
				fscanf(file, "%d", &colSize);
				fscanf(file, "%s %s", ch, ch);//col_name
				for (i = 0; i < colSize; i++) {//��ȡ��
					fscanf(file, "%s", ch);
					colName.push_back(ch);
				}
				fscanf(file, "%s %s", ch, ch);//col_type
				for (i = 0; i < colSize; i++) {//��ȡ��
					fscanf(file, "%s", ch);
					colType.push_back(ch);
				}
				for (i = 0; i < colSize; i++) {
					tableNameTemp.column.push_back(CNT(colName[i], colType[i]));
				}
				tableNameTemp.colSize = tableNameTemp.column.size();//����
				tableNameTemp.tableName = tableName[tableNumber];
				tableNumber++;//������ һ
				this->nameMangementTablePtr->nameTable.tableMangement.push_back(tableNameTemp);
				tableNameTemp.clear();
				colName.clear();
				colType.clear();
			}
		}
		fclose(file);
		this->nameMangementTablePtr->curLibraryName = databaseName;
		return true;
	}
	/*
	���룺databaseName���ݿ���
	���ܣ�������ΪdatabaseNmae�������ļ���������������
	������ɹ�����true,ʧ�ܷ���false
	*/
	bool DatabaseFile::save_database_ini_file(const string & databaseName)
	{
		int i, j;
		FILE*file = fopen(DATABASE_HOME_PATH(databaseName + "\\" + databaseName + ".ini").c_str(), "w");
		if (file == NULL)return false;
		fprintf(file, "<table number>\t%zd\n", nameMangementTablePtr->nameTable.tableSize);
		fprintf(file, "<table name>\t");
		for (i = 0; i < nameMangementTablePtr->nameTable.tableSize; i++) { //д�����
			fprintf(file, "%s ", nameMangementTablePtr->nameTable.tableMangement[i].tableName.c_str());
		}
		for (i = 0; i < nameMangementTablePtr->nameTable.tableSize; i++) {
			fprintf(file, "\n<begin>\n");
			fprintf(file, "<column number>\t%zd\n", nameMangementTablePtr->nameTable.tableMangement[i].colSize);//����
			fprintf(file, "<column name>\t");
			for (j = 0; j < nameMangementTablePtr->nameTable.tableMangement[i].colSize; j++) {//д������
				fprintf(file, "%s ", nameMangementTablePtr->nameTable.tableMangement[i].column[j].colName.c_str());
			}
			fprintf(file, "\n<column type>\t");
			for (j = 0; j < nameMangementTablePtr->nameTable.tableMangement[i].colSize; j++) {
				fprintf(file, "%s ", nameMangementTablePtr->nameTable.tableMangement[i].column[j].type.c_str());
			}
			fprintf(file, "\n<end>\n");
		}
		fclose(file);
		return true;
	}
	/*
	����:����
	���ܣ���ȡ��ΪtableName�ı�������ļ�
	������ɹ�����true,ʧ�ܷ���false
	*/
	bool DatabaseFile::read_table_ini_file(const string & tableName)
	{
		if (nameMangementTablePtr->curLibraryName == LIBRARY_NAME_EMPTY)return false;

		char ch[BUFF_SIZE];
		Record record;
		string filePath = DATABASE_HOME_PATH(nameMangementTablePtr->curLibraryName + "\\" + tableName + "\\" + tableName + ".ini");
		FILE*file = fopen(filePath.c_str(), "r");
		if (file == NULL)return false;
		fscanf(file, "<table name> %s", ch);
		record.headInfo.tableName = ch;//����
		fscanf(file, "%s %s %s %u", ch, ch, ch, &record.headInfo.totalDataNum);//��Ŀ����
		fscanf(file, "%s %s %s %u", ch, ch, ch, &record.headInfo.usedSpaceSize);//��ʹ�ÿռ�
		fscanf(file, "%s %s %s %u", ch, ch, ch, &record.headInfo.tableTypeNum);
		fscanf(file, "%s", ch);//<type_begin>
		while (fscanf(file, "%s", ch) && strcmp(ch, "<type_end>")) { //��ȡtype
			record.headInfo.type.push_back(static_cast<AttributeType>(atoi(ch)));
		}
		fscanf(file, "%s %s %d", ch, ch, &record.headInfo.pageNumber);//ҳ��
		fscanf(file, "%s", ch);//<page_order_begin>
		while (fscanf(file, "%s", ch) && strcmp(ch, "<page_order_end>")) {
			record.headInfo.pageOrder.push_back(atoi(ch));
		}
		//���ʱ��
		fscanf(file, "%s %s %s", ch, ch, ch);//��/��/��
		record.headInfo.addTiem = ch;
		fscanf(file, "%s\n", ch);//ʱ��
		record.headInfo.addTiem += string(" ") + ch;
		//�޸�ʱ��
		fscanf(file, "%s %s %s", ch, ch, ch);//��/��/��
		record.headInfo.modificationTime = ch;
		fscanf(file, "%s\n", ch);//ʱ��
		record.headInfo.modificationTime += string(" ") + ch;
		fclose(file);
		dataMangementPtr->table.push_back(record);
		return true;
	}
	/*
	����:����
	���ܣ�������ΪlibraryName�ı�������ļ�
	������ɹ�����true,ʧ�ܷ���false
	*/
	bool DatabaseFile::save_table_ini_file(const string & tableName)
	{
		if (nameMangementTablePtr->curLibraryName == LIBRARY_NAME_EMPTY)return false;
		string filePath = DATABASE_HOME_PATH(nameMangementTablePtr->curLibraryName + "\\" + tableName + "\\" + tableName + ".ini");
		FILE*file = fopen(filePath.c_str(), "w");
		if (file == NULL)return false;
		int i;
		for (i = 0; i < dataMangementPtr->table.size(); i++) { //�����Ƿ��иñ�
			if (dataMangementPtr->table[i].headInfo.tableName == tableName)break;
		}
		Record& record = dataMangementPtr->table[i];
		if (i < dataMangementPtr->table.size()) {
			fprintf(file, "<table name>\t%s\n", record.headInfo.tableName.c_str());
			fprintf(file, "<total data num>\t%d\n", record.headInfo.totalDataNum);
			fprintf(file, "<used space size>\t%d\n", record.headInfo.usedSpaceSize);
			fprintf(file, "<table type num>\t%d\n", record.headInfo.tableTypeNum);
			fprintf(file, "<type_begin>\n");
			vector<AttributeType>::iterator begin(record.headInfo.type.begin()), end(record.headInfo.type.end());
			while (begin != end) {//����
				fprintf(file, "%d\n", static_cast<int>(*begin));
				begin++;
			}
			fprintf(file, "<type_end>\n");
			fprintf(file, "\n<page number>\t%d", record.headInfo.pageNumber);//дҳ��
			fprintf(file, "\n<page_order_begin>\n");
			vector<unsigned>::iterator unBegin(record.headInfo.pageOrder.begin()), unEnd(record.headInfo.pageOrder.end());
			while (unBegin != unEnd) {//ҳ��
				fprintf(file, "%u\n", (*unBegin));
				unBegin++;
			}
			fprintf(file, "<page_order_end>\n");
			fprintf(file, "<add time>\t%s\n", record.headInfo.addTiem.c_str());
			fprintf(file, "<modification time>\t%s\n", record.headInfo.modificationTime.c_str());

		}
		fclose(file);
		return true;
	}
	/*
	���룺tableName ����
	���ܣ���ȡ���е�����
	������ɹ�����true,ʧ�ܷ���false
	*/
	bool DatabaseFile::read_table_data(const string & tableName)
	{
		if (nameMangementTablePtr->curLibraryName == LIBRARY_NAME_EMPTY)return false;//����ǵ�ǰ���ݿ�
		int i;
		for (i = 0; i < dataMangementPtr->tableNumber; i++) {
			if (dataMangementPtr->table[i].headInfo.tableName == tableName)break;
		}
		if (i < dataMangementPtr->tableNumber) {	//�ҵ�����
			char ch[BUFF_SIZE];
			unsigned firstPageNumber, j, l;
			FILE*file; string filePath;
			shared_ptr<Page> page;
			shared_ptr<Item> itemPtr;
			int  k, colNum;;//����

			if (dataMangementPtr->table[i].headInfo.pageOrder.size()>0) {

				colNum = dataMangementPtr->table[i].headInfo.tableTypeNum;//����
				for (l = 0; l < dataMangementPtr->table[i].headInfo.pageOrder.size(); l++) {
					firstPageNumber = dataMangementPtr->table[i].headInfo.pageOrder[l];//��һ��ҳ��
					filePath = DATABASE_HOME_PATH(nameMangementTablePtr->curLibraryName + "\\" + tableName + "\\" + to_string(firstPageNumber) + ".txt");
					file = fopen(filePath.c_str(), "r");
					if (file == NULL)return false;
					page = make_shared<Page>(new Page());

					if (page == nullptr) {
						cerr << "read_table_data DatabaseFile page memory  allocation failure!" << endl;
						return false;
					}
					fscanf(file, "%s %s %s %u", ch, ch, ch, &page->curPageNum);
					fscanf(file, "%s %s %s %u", ch, ch, ch, &page->pageSpaceMax);//<page space max> �ռ��ܴ�С
					fscanf(file, "%s %s %s %u", ch, ch, ch, &page->usedSpaceSize);//<used space size>��ʹ�ÿռ��С
					fscanf(file, "%s %s %s %u", ch, ch, ch, &page->unUsedSpaceSize);//<unused space size>δʹ�ÿռ��С
					fscanf(file, "%s %s %s %s", ch, ch, ch, ch);//<next page flag>
					if (!strcmp(ch, "true")) {
						page->nextPageFlag = true;
					}
					else {
						page->nextPageFlag = false;
					}
					fscanf(file, "%s %s %s %u", ch, ch, ch, &page->nextPageNum);//<next page num>
					fscanf(file, "%s %s %u", ch, ch, &page->itemSize);//<item size>
					//fscanf(file, "%s", ch);//<deletedFlag_begin>
					//while (fscanf(file, "%s", ch) && strcmp(ch, "<deletedFlag_end>")) { //�����ɾ������
					//	page->deletedFlag.push_back(atoi(ch));
					//}
					for (j = 0; j < page->itemSize /*+ page->deletedFlag.size()*/; j++) {	//���ݸ���
						itemPtr = make_shared<Item>(new Item());
						if (itemPtr == nullptr) {
							cerr << "read_table_data DatabaseFile iterPtr memory  allocation failure!" << endl;
							return false;
						}
						for (k = 0; k < colNum; k++) {	//��ȡ����
							fscanf(file, "%s", ch);
							itemPtr->item.push_back(DataType(ch));
						}
						fscanf(file, "%s", ch);
						//	itemPtr->nextDataNumber = atoi(ch);
						page->itemPtrSet.push_back(itemPtr);
						itemPtr = nullptr;
					}
					dataMangementPtr->table[i].pagePtrSet.push_back(page);//����ҳ
					page = nullptr;
					fclose(file);
				}
			}

		}
		else return false;//δ�ҵ�����
		return true;
	}
	/*
	���룺tableName ����
	���ܣ�������е�����
	������ɹ�����true,ʧ�ܷ���false
	*/
	bool DatabaseFile::save_table_data(const string & tableName)
	{
		if (nameMangementTablePtr->curLibraryName == LIBRARY_NAME_EMPTY)return false;//����ǵ�ǰ���ݿ�
		int i, j, colTypeNum;
		for (i = 0; i < dataMangementPtr->tableNumber; i++) {
			if (dataMangementPtr->table[i].headInfo.tableName == tableName)break;
		}
		if (i < dataMangementPtr->tableNumber) {//�ҵ���
			list<shared_ptr<Page>>::iterator begin(dataMangementPtr->table[i].pagePtrSet.begin()), end(dataMangementPtr->table[i].pagePtrSet.end());
			FILE*file;
			string filePath;
			colTypeNum = dataMangementPtr->table[i].headInfo.tableTypeNum;
			for (; begin != end; begin++) {
				if ((*begin)->dirtyPage != true)continue;//������ҳ
				shared_ptr<Page>&page = *begin;
				filePath = DATABASE_HOME_PATH(nameMangementTablePtr->curLibraryName + "\\" + tableName + "\\" + to_string(page->curPageNum) + ".txt");
				file = fopen(filePath.c_str(), "w");
				if (file == NULL)return false;
				//write data begin
				fprintf(file, "<current page number>\t%u\n", page->curPageNum);
				fprintf(file, "<page space max>\t%u\n", page->pageSpaceMax);
				fprintf(file, "<used space size>\t%u\n", page->usedSpaceSize);
				fprintf(file, "<unused space size>\t%u\n", page->unUsedSpaceSize);
				fprintf(file, "<next page flag>\t%s\n", page->nextPageFlag == true ? "true" : "false");
				fprintf(file, "<next page num>\t%u\n", page->nextPageNum);
				fprintf(file, "<item size>\t%u\n", page->itemSize);
				fprintf(file, "\n<deletedFlag_begin>\n");
				for (j = 0; j < page->deletedFlag.size(); j++) {//write deleted item number
					fprintf(file, "%u\n", page->deletedFlag[j]);
				}
				fprintf(file, "<deletedFlag_end>\n");
				list<shared_ptr<Item>>::iterator itemSetBegin(page->itemPtrSet.begin()), itemSetEnd(page->itemPtrSet.end());
				for (; itemSetBegin != itemSetEnd; itemSetBegin++) {	//write data
					for (j = 0; j < (*itemSetBegin)->item.size(); j++) {
						fprintf(file, "%s\t", (*itemSetBegin)->item[j].get_data().c_str());
					}
					fprintf(file, "\n");
					//fprintf(file, "%u\n", (*itemSetBegin)->nextDataNumber);
				}

				//write data end
				fclose(file);

			}
		}
		else return false;//δ�ҵ���
		return true;
	}

	shared_ptr<NameMangementFile> DatabaseFile::get_nameMangementTablePtr()
	{
		return nameMangementTablePtr;
	}
	shared_ptr<RecordTable> DatabaseFile::get_dataMangementPtr()
	{
		return dataMangementPtr;
	}
	/*
	����:�������ݿ��з��������ݼ������ļ�
	������ɹ�����true,ʧ�ܷ���false
	*/
	bool DatabaseFile::save()
	{
		if (this - save_database_mangement_system_ini_file() == false)
			return false;
		if (this->nameMangementTablePtr->curLibraryName != LIBRARY_NAME_EMPTY&&!this->save_database_ini_file(this->nameMangementTablePtr->curLibraryName))
			return false;
		int i, j;
		bool flag;
		for (j = 0; j < this->dataMangementPtr->tableNumber; j++) {
			flag = false;
			list<shared_ptr<Page>>::iterator begin(this->dataMangementPtr->table[j].pagePtrSet.begin()),
				end(this->dataMangementPtr->table[j].pagePtrSet.end());
			for (; begin != end; begin++) {
				if ((*begin)->dirtyPage == true) {
					flag = true;
					break;
				}
			}
			if (flag)
				this->dataMangementPtr->table[j].headInfo.modificationTime = get_current_time();
		}
		for (i = 0; i < this->nameMangementTablePtr->nameTable.tableSize; i++) {

			if (!save_table_data(this->nameMangementTablePtr->nameTable.tableMangement[i].tableName) ||
				!save_table_ini_file(this->nameMangementTablePtr->nameTable.tableMangement[i].tableName))return false;
		}
		return true;
	}
	
	Page::Page()
	{
		this->curPageNum = 0;
		this->deletedFlag;
		this->dirtyPage = false;
		this->itemPtrSet;
		this->itemSize = 0;
		this->nextPageFlag = false;
		this->nextPageNum = 0;
		this->pageSpaceMax = PAGE_SIZE;
		this->usedSpaceSize = 0;
		this->unUsedSpaceSize = PAGE_SIZE;
	}
	Page::Page(const Page * page)
	{
		this->curPageNum = page->curPageNum;
		this->deletedFlag = page->deletedFlag;
		this->dirtyPage = page->dirtyPage;
		this->itemPtrSet = page->itemPtrSet;
		this->nextPageFlag = page->nextPageFlag;
		this->nextPageNum = page->nextPageNum;
		this->pageSpaceMax = page->pageSpaceMax;
		this->unUsedSpaceSize = page->unUsedSpaceSize;
		this->usedSpaceSize = page->usedSpaceSize;
	}
	Page::Page(const Page & obj)
	{
		(*this) = obj;
	}
	Page & Page::operator=(const Page & obj)
	{
		this->curPageNum = obj.curPageNum;
		this->deletedFlag = obj.deletedFlag;
		this->dirtyPage = obj.dirtyPage;
		this->itemPtrSet = obj.itemPtrSet;
		this->itemSize = obj.itemSize;
		this->nextPageFlag = obj.nextPageFlag;
		this->pageSpaceMax = obj.pageSpaceMax;
		this->unUsedSpaceSize = obj.unUsedSpaceSize;
		this->usedSpaceSize = obj.usedSpaceSize;
		return *this;
	}
	/*
	���ܣ���ա�����
	*/
	void Page::clear()
	{
		this->deletedFlag.clear();
		this->dirtyPage = false;
		this->curPageNum = 0;
		this->itemSize = 0;
		this->nextPageFlag = false;
		this->nextPageNum = 0;
		this->pageSpaceMax = 0;
		this->unUsedSpaceSize = 0;
		this->usedSpaceSize = 0;
		list<shared_ptr<Item>>::iterator begin(itemPtrSet.begin()), end(itemPtrSet.end());
		while (begin != end) {
			(*begin) = nullptr;
			begin++;
		}
		itemPtrSet.clear();
	}

	RecordHeadInfo::RecordHeadInfo()
	{
		this->addTiem = this->modificationTime = STRING_EMPTY;
		this->pageNumber = 0;
		this->pageOrder;
		this->tableName = STRING_EMPTY;
		this->tableTypeNum = 0;
		this->totalDataNum = 0;
		this->usedSpaceSize = 0;

	}

	RecordHeadInfo::RecordHeadInfo(const RecordHeadInfo & obj)
	{
		(*this) = obj;
	}
	RecordHeadInfo & RecordHeadInfo::operator=(const RecordHeadInfo & obj)
	{
		this->addTiem = obj.addTiem;
		this->modificationTime = obj.addTiem;
		this->pageNumber = obj.pageNumber;
		this->pageOrder = obj.pageOrder;
		this->tableName = obj.tableName;
		this->tableTypeNum = obj.tableTypeNum;
		this->totalDataNum = obj.totalDataNum;
		this->type = obj.type;
		this->usedSpaceSize = obj.usedSpaceSize;
		return *this;
	}
	/*
	���ܣ���ա�����
	*/
	void RecordHeadInfo::clear()
	{
		this->addTiem = this->modificationTime = STRING_EMPTY;
		this->pageNumber = 0;
		this->pageOrder.clear();
		this->tableName = STRING_EMPTY;
		this->tableTypeNum = 0;
		this->totalDataNum = 0;
		this->type.clear();
		this->usedSpaceSize = 0;

	}

	RecordHeadInfo::~RecordHeadInfo()
	{

	}

	Record::Record()
	{

	}

	Record::Record(const Record & obj)
	{
		(*this) = obj;
	}

	Record & Record::operator=(const Record & obj)
	{
		this->headInfo = obj.headInfo;
		this->pagePtrSet = obj.pagePtrSet;
		return *this;
	}

	void Record::clear()
	{
		list<shared_ptr<Page>>::iterator begin(this->pagePtrSet.begin()), end(pagePtrSet.end());
		while (begin != end) {
			(*begin)->clear();
			(*begin) = nullptr;
			begin++;
		}

		headInfo.clear();
	}

	Record::~Record()
	{
		//clear();
	}

	void RecordTable::clear()
	{
		libraryName = STRING_EMPTY;
		tableNumber = 0;
		int i;
		size_t size = table.size();
		for (i = 0; i < size; i++) {
			table[i].clear();
		}

	}

	RecordTable::~RecordTable()
	{
		clear();
	}
}