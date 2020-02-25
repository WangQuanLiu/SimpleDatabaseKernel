
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
	struct NameQuery { //���ֲ�ѯ�ṹ
		NameQuery(const string&libraryName);
		NameQuery(const string&libraryName, const string&tableName);
		NameQuery(const string&libraryName, const string&tableName, const string&colName);
		NameQuery& operator=(const NameQuery&obj);
		string libraryName, tableName, colName;
		QueryType queryType;
	};
	struct NameQueryIndex { //���ֲ�ѯ�±�ṹ
		size_t databaseNameIndex, tableNameIndex, colNameIndex;//���±ꡢ���±ꡢ���±�
		bool flag;//falseʧ�� true�ɹ�
		QueryType queryType;
		NameQueryIndex(const size_t&libraryIndex);
		NameQueryIndex(const size_t&libraryIndex, const size_t&tableIndex);
		NameQueryIndex(const size_t&libraryIndex, const size_t&tableIndex, const size_t&colIndex);
		NameQueryIndex();
	};
	struct DataType { //���ݻ�����
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
	enum AttributeType { a_int, a_flaot, a_string, a_error };//�������
	typedef struct ColNameAndType {
		string colName, type;//����������
		AttributeType attributeType;//�������
		ColNameAndType() = default;
		void set_values(const string&colName, const string&coltype);
		ColNameAndType(const string&colName, const string&coltype);
		size_t type_size();
	}CNT;//������������
	struct TableNameMangement//��������
	{
		string tableName;//����
		size_t colSize;//����
		vector<CNT>column;//����
		TableNameMangement() = default;
		TableNameMangement(const string&tableName, const size_t&colSize, const vector<CNT>&column);
	public:
		void clear();
	};
	struct LibraryNameMangement//������������
	{
		string libraryName;//���ݿ���
		size_t tableSize;//��������
		vector<TableNameMangement> tableMangement;//��������
		void clear();
		~LibraryNameMangement();
	};
	struct NameMangementFile {//���ݿ����ֹ���
	public:
		NameMangementFile() = default;
		vector<string>libraryNameTable;//�����ֹ����
		LibraryNameMangement nameTable;//��
		string curLibraryName;//��ǰ���ݿ�
		void clear();
		~NameMangementFile();
	};
	struct Item {//���е�һ������
		Item() = default;
		//Item & operator==(const Item & objOne, const Item & objTwo);
		Item(const Item&obj);
		Item(const Item*obj);
		Item&operator=(const Item&obj);
		Item&operator+=(const Item&obj);
		vector<DataType>item;//һ������
		friend bool operator==(const Item&itemOne, const Item&itemTwo);
	//	Item&operator=(const Item&obj);
		//	 int nextDataNumber;//��һ�����ݺ�
		void clear();//�������

	};
	using Item_ptr = Item*;
	inline bool is_spacial_directory(const char*path);
	inline bool is_directory(int attrib);
	inline void get_file_path(const char*path, const char*fileName, char*filePath);
	bool delete_file(const char*path);
	bool delete_all_file(const char*path);//ɾ���ļ��������µ������ļ�
	string get_current_time();//��ȡ��ǰʱ��
	bool create_file(const string&filePath);//����filePath�ļ�
}