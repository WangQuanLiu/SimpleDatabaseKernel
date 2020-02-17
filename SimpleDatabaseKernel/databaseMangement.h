#ifndef _DATABASE_FILE_
#include"databaseFile.h"
#endif
#include<Windows.h>
#include<io.h>
#include<time.h>
namespace dbm {
#define _DATABASE_
#define NAME_QUERY_INDEX_ERROR -1
#define Q_EMPTY	""
#define _DATABASE_MANGEMENT_
	class NameMangement {//��������������������
	public:
		NameMangement(shared_ptr<NameMangementFile>);
		NameMangement() = default;
		NameMangement&operator=(const NameMangement&obj);
		void set_nameMangementFile(shared_ptr<NameMangementFile>ptr);
		bool query_name(const NameQuery&nameQuery)const;//��ѯ����
		bool nameMangeMent_modification_name(const NameQuery&nameQuery, const string&modificationedName);//�޸�����
		bool delete_name(const NameQuery&nameQuery);//ɾ������
		bool add_name(const NameQuery&nameQuery);//��ӿ���������
		bool add_name(const NameQuery&nameQuery, const string&colType);//�������
		void set_cur_library_name(const string&libraryName);
		AttributeType quer_column_type(const string&libraryName, const string&tableName, const string&columnName);//��ѯ������
	protected:
		NameQueryIndex query_name_inner(const NameQuery&nameQuery)const;
		bool add_database_name_or_table_name(const NameQuery&nameQuery);
		bool add_col_name(const NameQuery&nameQuery, const string&colType);
		shared_ptr<NameMangementFile>nameMangementFilePtr;
	};
	struct Data {
		Data() = default;
		size_t size()const;
		vector<string>values;
		//vector<AttributeType>type;
		//vector<int>typeSize;
	};
	struct InsertData {
		InsertData() = default;
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
		shared_ptr<RecordHeadInfo>recordHeadInfoPtr;
		list<shared_ptr<Page>>pagePtr;//ҳ
		resultData&operator=(const resultData&obj);
	};
	class dataMangement :public  NameMangement {
	public:
		dataMangement();
		dataMangement(const string&libraryName);
		void set_library(const string&librarName);
		bool query_data(const NameQuery&nameQuery)const;//��ѯ����
		bool modification_name(const NameQuery&nameQuery, const string&modeficationedName);//�޸����ּ��ļ�
		bool delete_talbe_or_library(const NameQuery&nameQuery);//ɾ���������������ļ�
		bool delete_column(const string&libraryName, const string&tableName, const string&colName);//ɾ������
		bool add_table_or_library(const NameQuery&nameQuery);//��ӿ������������ļ�
		bool add_column(const string&libraryName, const string&tableName, const string&columnName, const string & type);
		bool add_data(const InsertData&data);
		bool delete_data(const DeleteData&data);
		bool save();//������������
		bool table_data(const string&tableName, resultData&result);
	private:

		//NameMangement nameMangement;//���ֹ���
		DatabaseFile databaseFile;//���ݿ�����
	};
}
