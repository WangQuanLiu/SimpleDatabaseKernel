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
	输出：文件路径
	功能：判断是否是".."和"."目录
	输出：是返回true，不是返回false
	*/
	inline bool is_spacial_directory(const char * path)
	{
		return strcmp(path, "..") == 0 || strcmp(path, ".") == 0;
	}
	/*
	输入:文件属性
	功能：判断文件属性是目录还是文件
	输出:是目录返回true,否则返回false
	*/
	inline bool is_directory(int attrib)
	{
		return attrib == 16 || attrib == 18 || attrib == 20;
	}
	/*
	输入：目录、文件名、完整路径字符
	功能：获取文件完整路径
	*/
	inline void get_file_path(const char * path, const char * fileName, char * filePath)
	{
		strcpy_s(filePath, sizeof(char) * _MAX_PATH, path);
		filePath[strlen(filePath) - 1] = '\0';
		strcat_s(filePath, sizeof(char) * _MAX_PATH, fileName);
	}
	/*
	输入：文件路径
	功能：删除这个文件路径下的所有文件及文件夹
	*/
	bool delete_file(const char * path)
	{
		char pcSearchPath[_MAX_PATH];
		sprintf_s(pcSearchPath, _MAX_PATH, "%s\\*", path); //pcSearchPath 为搜索路径，* 代表通配符

		_finddata_t DirInfo; //文件夹信息
		_finddata_t FileInfo; //文件信息
		intptr_t f_handle; //查找句柄

		char pcTempPath[_MAX_PATH];
		if ((f_handle = _findfirst(pcSearchPath, &DirInfo)) != -1)
		{
			while (_findnext(f_handle, &FileInfo) == 0)
			{
				if (is_spacial_directory(FileInfo.name))
					continue;
				if (FileInfo.attrib & _A_SUBDIR)//如果是目录，生成完整的路径
				{
					get_file_path(pcSearchPath, FileInfo.name, pcTempPath);
					delete_file(pcTempPath); //开始递归删除目录中的内容
					if (FileInfo.attrib == 20)
						printf("This is system file, can't delete!\n");
					else
					{
						//删除空目录，必须在递归返回前调用_findclose,否则无法删除目录
						if (_rmdir(pcTempPath) == -1)
						{
							return false;//目录非空则会显示出错原因
						}
					}
				}
				else
				{
					strcpy_s(pcTempPath, pcSearchPath);
					pcTempPath[strlen(pcTempPath) - 1] = '\0';
					strcat_s(pcTempPath, FileInfo.name);//生成完整的文件路径

					if (remove(pcTempPath) == -1)
					{
						return false;
					}

				}
			}
			_findclose(f_handle);//关闭打开的文件句柄，并释放关联资源，否则无法删除空目录
		}
		else
		{
			return false;//若路径不存在
		}
		return true;
	}
	/*
	输入：文件路径
	功能：删除这个文件以及包括这个文件夹下的所有子文件
	*/
	bool delete_all_file(const char * path)
	{
		if (!delete_file(path))return false; //删除该文件夹里的所有文件

		if (_rmdir(path) == -1) //删除此文件夹
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
	功能：返回列类型占字节大小
	输出：占字节大小
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
	功能：获取当前时间 年/月/日 时:分:秒
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
	功能：清空、重置
	*/
	void Item::clear()
	{
		this->item.clear();
		//this->nextDataNumber = ITEM_EMPTY;
	}

}
