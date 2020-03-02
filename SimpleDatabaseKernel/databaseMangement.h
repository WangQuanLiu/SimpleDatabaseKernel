#ifndef _DATABASE_FILE_
#include"databaseFile.h"
#endif
#include<Windows.h>
#include<io.h>
#include<time.h>
#include<set>
namespace dbm {
#define _DATABASE_
#define NAME_QUERY_INDEX_ERROR -1
#define Q_EMPTY	""
#define _DATABASE_MANGEMENT_
	//class NameMangement {//��������������������
	//public:
	//	NameMangement(shared_ptr<NameMangementFile>);
	//	NameMangement() = default;
	//	NameMangement&operator=(const NameMangement&obj);
	//	void set_nameMangementFile(shared_ptr<NameMangementFile>ptr);
	//	bool query_name(const NameQuery&nameQuery)const;//��ѯ����
	//	bool nameMangeMent_modification_name(const NameQuery&nameQuery, const string&modificationedName);//�޸�����
	//	bool delete_name(const NameQuery&nameQuery);//ɾ������
	//	bool add_name(const NameQuery&nameQuery);//��ӿ���������
	//	bool add_name(const NameQuery&nameQuery, const string&colType);//�������
	//	void set_cur_library_name(const string&libraryName);
	//	AttributeType quer_column_type(const string&libraryName, const string&tableName, const string&columnName);//��ѯ������
	//	bool check_all_column_type_in_table(const string&libraryName, const string&tableName, vector<string>&strType,vector<AttributeType>&type);
	//protected:
	//	NameQueryIndex query_name_inner(const NameQuery&nameQuery)const;
	//	bool add_database_name_or_table_name(const NameQuery&nameQuery);
	//	bool add_col_name(const NameQuery&nameQuery, const string&colType);
	//	shared_ptr<NameMangementFile>nameMangementFilePtr;
	//};
	struct Data {
		Data() = default;
		size_t size()const;
		vector<string>values;
	};
	struct InsertData {
		InsertData() = default;
		InsertData(const string&tableName, const string&values);
		InsertData(const string&tableName, const vector<string>&values);
		void set_tableName(const string&tableName);
		void add_data(const string&value);
		void add_data(const vector<string>&value);
		string  tableName;
		Data data;
	private:
		void check();
	};
	struct DeleteData {
		DeleteData() = default;
		string tableName;
		void set_tableName(const string&tableName);
		void add_data(const string&value);
		vector<string>values;
	};

	struct resultData {
		vector<CNT>ColName;
		RecordHeadInfo recordHeadInfo;
		list<Page>page;//ҳ
		resultData&operator=(const resultData&obj);
	};
	using resultData_ptr = resultData*;
	class dataMangement /*:public  NameMangement*/{
	public:
		dataMangement();
		dataMangement(const string&libraryName);
		string get_currently_library_name();
		void set_library(const string&librarName);
		bool query_data(const NameQuery&nameQuery)const;//��ѯ����
		bool modification_name(const NameQuery&nameQuery, const string&modeficationedName);//�޸����ּ��ļ�
		bool delete_talbe_or_library(const NameQuery&nameQuery);//ɾ���������������ļ�
		bool add_table_or_library(const NameQuery&nameQuery);//��ӿ������������ļ�	
		bool add_data(const InsertData&data);
		bool delete_data(const DeleteData&data);
		bool save();//������������
		vector<CNT>get_column_info_in_table(const string&tableName);
		resultData_ptr table_data(const string&tableName);
		DatabaseFile databaseFile;//���ݿ�����
	protected:
		bool delete_column(const string&libraryName, const string&tableName, const string&colName);//ɾ������
		bool add_column(const string&libraryName, const string&tableName, const string&columnName, const string & type);
		inline void newPage(int tableIndex, size_t colSize,size_t pageSize, Item item);
		public:
			bool query_name(const NameQuery&nameQuery)const;//��ѯ����
			bool nameMangeMent_modification_name(const NameQuery&nameQuery, const string&modificationedName);//�޸�����
			bool delete_name(const NameQuery&nameQuery);//ɾ������
			bool add_name(const NameQuery&nameQuery);//��ӿ���������
			bool add_name(const NameQuery&nameQuery, const string&colType);//�������
			void set_cur_library_name(const string&libraryName);
			AttributeType quer_column_type(const string&libraryName, const string&tableName, const string&columnName);//��ѯ������
			bool check_all_column_type_in_table(const string&libraryName, const string&tableName, vector<string>&strType,vector<AttributeType>&type);
		protected:
			NameQueryIndex query_name_inner(const NameQuery&nameQuery)const;
			bool add_database_name_or_table_name(const NameQuery&nameQuery);
			bool add_col_name(const NameQuery&nameQuery, const string&colType);
			shared_ptr<NameMangementFile>nameMangementFilePtr;
	};
}
