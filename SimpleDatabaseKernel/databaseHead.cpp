#include"databaseHead.h"
namespace dbm {
	DataType::DataType(int data)
	{
		this->data = to_string(data);
	}

	DataType::DataType(const string &data) {
		this->data = data;
	}

	DataType::DataType(double data)
	{
		this->data = to_string(data);
	}

	DataType& DataType::operator=(DataType obj)
	{
		this->data = obj.data;
	
		return *this;
	}

	void DataType::set_data(const string &data)
	{
		this->data = data;
	}

	string DataType::get_data() const
	{
		return this->data;
	}
	bool operator==(const DataType&obj_one, const DataType&obj_two) {
		return obj_one.data == obj_two.data;
	}
	bool operator!=(const DataType&obj_one, const DataType&obj_two) {
		return obj_one.data != obj_two.data;
	}
	bool operator>=(const DataType&obj_one, const DataType&obj_two) {
		return obj_one.data >= obj_two.data;
	}
	bool operator<=(const DataType&obj_one, const DataType&obj_two) {
		return obj_one.data <= obj_two.data;
	}
	bool operator>(const DataType&obj_one, const DataType&obj_two) {
		return obj_one.data > obj_two.data;
	}
	bool operator<(const DataType&obj_one, const DataType&obj_two) {
		return obj_one.data < obj_two.data;
	}
	/*
	������ļ�·��
	���ܣ��ж��Ƿ���".."��"."Ŀ¼
	������Ƿ���true�����Ƿ���false
	*/
	inline bool is_spacial_directory(const char * path)
	{
		return strcmp(path, "..") == 0 || strcmp(path, ".") == 0;
	}
	/*
	����:�ļ�����
	���ܣ��ж��ļ�������Ŀ¼�����ļ�
	���:��Ŀ¼����true,���򷵻�false
	*/
	inline bool is_directory(int attrib)
	{
		return attrib == 16 || attrib == 18 || attrib == 20;
	}
	/*
	���룺Ŀ¼���ļ���������·���ַ�
	���ܣ���ȡ�ļ�����·��
	*/
	inline void get_file_path(const char * path, const char * fileName, char * filePath)
	{
		strcpy_s(filePath, sizeof(char) * _MAX_PATH, path);
		filePath[strlen(filePath) - 1] = '\0';
		strcat_s(filePath, sizeof(char) * _MAX_PATH, fileName);
	}
	/*
	���룺�ļ�·��
	���ܣ�ɾ������ļ�·���µ������ļ����ļ���
	*/
	bool delete_file(const char * path)
	{
		char pcSearchPath[_MAX_PATH];
		sprintf_s(pcSearchPath, _MAX_PATH, "%s\\*", path); //pcSearchPath Ϊ����·����* ����ͨ���

		_finddata_t DirInfo; //�ļ�����Ϣ
		_finddata_t FileInfo; //�ļ���Ϣ
		intptr_t f_handle; //���Ҿ��

		char pcTempPath[_MAX_PATH];
		if ((f_handle = _findfirst(pcSearchPath, &DirInfo)) != -1)
		{
			while (_findnext(f_handle, &FileInfo) == 0)
			{
				if (is_spacial_directory(FileInfo.name))
					continue;
				if (FileInfo.attrib & _A_SUBDIR)//�����Ŀ¼������������·��
				{
					get_file_path(pcSearchPath, FileInfo.name, pcTempPath);
					delete_file(pcTempPath); //��ʼ�ݹ�ɾ��Ŀ¼�е�����
					if (FileInfo.attrib == 20)
						printf("This is system file, can't delete!\n");
					else
					{
						//ɾ����Ŀ¼�������ڵݹ鷵��ǰ����_findclose,�����޷�ɾ��Ŀ¼
						if (_rmdir(pcTempPath) == -1)
						{
							return false;//Ŀ¼�ǿ������ʾ����ԭ��
						}
					}
				}
				else
				{
					strcpy_s(pcTempPath, pcSearchPath);
					pcTempPath[strlen(pcTempPath) - 1] = '\0';
					strcat_s(pcTempPath, FileInfo.name);//�����������ļ�·��

					if (remove(pcTempPath) == -1)
					{
						return false;
					}

				}
			}
			_findclose(f_handle);//�رմ򿪵��ļ���������ͷŹ�����Դ�������޷�ɾ����Ŀ¼
		}
		else
		{
			return false;//��·��������
		}
		return true;
	}
	/*
	���룺�ļ�·��
	���ܣ�ɾ������ļ��Լ���������ļ����µ��������ļ�
	*/
	bool delete_all_file(const char * path)
	{
		if (!delete_file(path))return false; //ɾ�����ļ�����������ļ�

		if (_rmdir(path) == -1) //ɾ�����ļ���
		{
			return false;
		}
		return true;
	}

	TableNameMangement::TableNameMangement(const string &tableName, const size_t &colSize, const vector<CNT>&column)
	{
		this->tableName = tableName;
		this->colSize = colSize;
		this->column = column;

	}

	void TableNameMangement::clear() {
		tableName = "";
		colSize = 0;
		column.clear();
	}

	void LibraryNameMangement::clear() {
		libraryName = LIBRARY_NAME_EMPTY;
		tableSize = 0;
		tableMangement.clear();
	}
	LibraryNameMangement::~LibraryNameMangement()
	{
		clear();
	}
	void ColNameAndType::set_values(const string &colName, const string &colType)
	{
		this->colName = colName;
		this->type = colType;
		if (colType.at(0) == 'i') {
			this->attributeType = a_int;
		}
		else if (colType.at(0) == 'c') {
			this->attributeType = a_string;
		}
		else {
			this->attributeType = a_flaot;
		}
	}

	ColNameAndType::ColNameAndType(const string &colName, const string &colType)
	{
		set_values(colName, colType);
	}
	/*
	���ܣ�����������ռ�ֽڴ�С
	�����ռ�ֽڴ�С
	*/
	size_t ColNameAndType::type_size()
	{
		if (attributeType == a_int)return sizeof(int);
		else if (attributeType == a_flaot)return sizeof(float);
		else {
			int i;
			bool flag = false;
			string temp;
			for (i = 0; i < type.size(); i++) {
				if (type[i] == '(') {
					flag = true;
					continue;
				}
				else if (type[i] == ')')break;
				if (flag)temp += type[i];
			}
			return atoi(temp.c_str());
		}

	}
	/*
	���ܣ���ȡ��ǰʱ�� ��/��/�� ʱ:��:��
	*/
	string get_current_time()
	{
		time_t t = time(NULL);
		char ch[TIME_STRUCT_SIZE]{ 0 };
		strftime(ch, sizeof(ch) - 1, "%Y/%m/%d %H:%M:%S", localtime(&t));
		return ch;
	}
	bool create_file(const string & filePath)
	{
		ofstream file(filePath.c_str());
		if (!file)return false;
		file.close();
		return true;
	}
	void NameMangementFile::clear()
	{
		libraryNameTable.clear();
		nameTable.clear();
		curLibraryName = LIBRARY_NAME_EMPTY;
	}

	NameMangementFile::~NameMangementFile()
	{
		clear();
	}
	bool operator==(const Item&objOne, const Item&objTwo) {
		if (objOne.item.size() != objTwo.item.size())return false;
		int i;
		for (i = 0; i < objOne.item.size(); i++) {
			if (objOne.item[i] != objTwo.item[i])return false;
		}
		return true;
	}
	Item::Item(const Item & obj)
	{
		this->item = obj.item;
		//this->nextDataNumber = obj.nextDataNumber;
	}
	Item::Item(const Item * obj)
	{
		this->item = obj->item;
		//this->nextDataNumber = obj->nextDataNumber;
	}
	Item & Item::operator=(const Item & obj)
	{
		this->item = obj.item;
		//this->nextDataNumber = obj.nextDataNumber;
		return *this;
	}
	Item & Item::operator+=(const Item & obj)
	{
		int i=0;
		for (; i < obj.item.size(); i++) {
			this->item.push_back(obj.item[i]);
		}
		return *this;
	}
	/*
	���ܣ���ա�����
	*/
	void Item::clear()
	{
		this->item.clear();
		//this->nextDataNumber = ITEM_EMPTY;
	}

}
