
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<math.h>
#include<bitset>
#include<vector>
#include<list>
#include<initializer_list>
#include<cstdlib>
#include<cstdio>
#include<memory>
#include<fstream>
#include<time.h>
#include <errno.h>
#include<Windows.h>
#include <io.h>
#include <direct.h>
namespace dbm {
#define _DATABASE_HEAD_
#define BUFF_SIZE 4096
#define LIBRARY_NAME_EMPTY ""
#define TIME_STRUCT_SIZE 64
	using namespace std;
	using Address = int*;
	using data_size = int;
	enum QueryType { q_library_name, q_table_name, q_col_name };
	struct NameQuery { //名字查询结构
		NameQuery(const string&libraryName);
		NameQuery(const string&libraryName, const string&tableName);
		NameQuery(const string&libraryName, const string&tableName, const string&colName);
		NameQuery& operator=(const NameQuery&obj);
		string libraryName, tableName, colName;
		QueryType queryType;
	};
	struct NameQueryIndex { //名字查询下标结构
		size_t databaseNameIndex, tableNameIndex, colNameIndex;//库下标、表下标、列下标
		bool flag;//false失败 true成功
		QueryType queryType;
		NameQueryIndex(const size_t&libraryIndex);
		NameQueryIndex(const size_t&libraryIndex, const size_t&tableIndex);
		NameQueryIndex(const size_t&libraryIndex, const size_t&tableIndex, const size_t&colIndex);
		NameQueryIndex();
	};
	struct DataType { //数据基本项
	public:
		DataType() = default;
		DataType(int);
		DataType(const string&);
		DataType(double);
		friend bool operator==(const DataType&, const DataType&);
		friend bool operator!=(const DataType&, const DataType&);
		friend bool operator>=(const DataType&, const DataType&);
		friend bool operator<=(const DataType&, const DataType&);
		friend bool operator>(const DataType&, const DataType&);
		friend bool operator<(const DataType&, const DataType&);
		DataType& operator=(DataType);
		void set_data(const string&);
		string get_data()const;
	private:
		string data;
	//	AttributeType type;
	};
	enum AttributeType { a_int, a_flaot, a_string, a_error };//属性类别
	typedef struct ColNameAndType {
		string colName, type;//列名与类型
		AttributeType attributeType;//属性类别
		ColNameAndType() = default;
		void set_values(const string&colName, const string&coltype);
		ColNameAndType(const string&colName, const string&coltype);
		size_t type_size();
	}CNT;//列名与列类型
	struct TableNameMangement//表名管理
	{
		string tableName;//表名
		size_t colSize;//列数
		vector<CNT>column;//列名
		TableNameMangement() = default;
		TableNameMangement(const string&tableName, const size_t&colSize, const vector<CNT>&column);
	public:
		void clear();
	};
	struct LibraryNameMangement//整个库名管理
	{
		string libraryName;//数据库名
		size_t tableSize;//表名数量
		vector<TableNameMangement> tableMangement;//表名管理
		void clear();
		~LibraryNameMangement();
	};
	struct NameMangementFile {//数据库名字管理
	public:
		NameMangementFile() = default;
		vector<string>libraryNameTable;//库名字管理表
		LibraryNameMangement nameTable;//库
		string curLibraryName;//当前数据库
		void clear();
		~NameMangementFile();
	};
	struct Item {//表中的一行数据
		Item() = default;
		//Item & operator==(const Item & objOne, const Item & objTwo);
		Item(const Item&obj);
		Item(const Item*obj);
		Item&operator=(const Item&obj);
		Item&operator+=(const Item&obj);
		vector<DataType>item;//一行数据
		friend bool operator==(const Item&itemOne, const Item&itemTwo);
	//	Item&operator=(const Item&obj);
		//	 int nextDataNumber;//下一个数据号
		void clear();//清空重置

	};
	using Item_ptr = Item*;
	inline bool is_spacial_directory(const char*path);
	inline bool is_directory(int attrib);
	inline void get_file_path(const char*path, const char*fileName, char*filePath);
	bool delete_file(const char*path);
	bool delete_all_file(const char*path);//删除文件包括其下的所有文件
	string get_current_time();//获取当前时间
	bool create_file(const string&filePath);//创建filePath文件
}