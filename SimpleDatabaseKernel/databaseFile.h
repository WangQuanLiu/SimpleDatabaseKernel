#ifndef _DATABASEHEAD_
#include"databaseHead.h"
#endif
#include<direct.h>
namespace dbm {
#define _DATABASE_FILE_
#define RECORD_SIZE (int)(pow(2,14))
#define PAGE_SIZE 40960
#define DATABASE_HOME string("C:\\databaseMangementSystem\\")
#define DATABASE_HOME_PATH(x) string(DATABASE_HOME+(x))
#define ITEM_EMPTY -1
#define STRING_EMPTY ""

	
	class Page {
	public:
		Page();
		Page(const Page*page);
		Page(const Page&obj);
		Page&operator=(const Page&obj);
		list<shared_ptr<Item>> itemPtrSet;//������
		bool dirtyPage;//��ҳ
		unsigned curPageNum;//��ǰҳ��
		unsigned itemSize;//������Ŀ����
		vector<unsigned>deletedFlag;//δʹ�����ݺ�
		unsigned pageSpaceMax;//���ҳ�ռ�
		unsigned usedSpaceSize;//��ʹ�ÿռ�
		unsigned unUsedSpaceSize;//δʹ�ÿռ�
		bool nextPageFlag;//�Ƿ�����һ��ҳ
		unsigned nextPageNum;//��һҳҳ��
		void clear();
	};
	using Page_ptr = Page*;
	using Page_ptr_ptr = Page_ptr*;
	struct RecordHeadInfo {//ͷ���ļ���Ϣ
		RecordHeadInfo();
		RecordHeadInfo(const RecordHeadInfo&obj);
		RecordHeadInfo&operator=(const RecordHeadInfo&obj);
		string tableName;//����
		unsigned totalDataNum;//�ܼ����ݸ���
		unsigned usedSpaceSize;//��ʹ�ÿռ��С
		int tableTypeNum;//�и���
		vector<AttributeType> type;//��������
		unsigned pageNumber;//ҳ��
		vector<unsigned>pageOrder;//ҳ��
		string addTiem, modificationTime;//���ʱ�䣬�޸�ʱ��
		void clear();
		~RecordHeadInfo();
	};
	struct Record {	//��¼�ṹ
		Record();
		Record(const Record&obj);
		Record&operator=(const Record&obj);
		using Record_ptr = Record*;
		RecordHeadInfo headInfo;//�ײ���Ϣ
		list<shared_ptr<Page>>pagePtrSet;//ҳ
		void clear();
		~Record();
	};
	struct RecordTable {
		string libraryName;//���ݿ���
		vector<Record> table;//���ݿ����������
		size_t tableNumber;//������
		void clear();
		~RecordTable();
		//string addTiem, modificationTime;//���ʱ�䣬�޸�ʱ��
	};

	class DatabaseFile
	{
	public:
		DatabaseFile();
		~DatabaseFile();
		bool read_database_data(const string&libraryName);//��ȡ���ݿ�����
		shared_ptr<RecordTable> dataMangementPtr;//���ݿ�����
		shared_ptr<NameMangementFile> nameMangementTablePtr;
		bool save();
		friend class dataMangement;
	private:
		void set_current_database_name(const string&libraryName);//�л���ǰ���ݿ�
		bool read_database_mangement_system_ini_file();//��ȡ���ݿ����ϵͳ�����ļ�
		bool save_database_mangement_system_ini_file();//�������ݿ����ϵͳ�����ļ�
		bool read_database_ini_file(const string&libraryName);//��ȡ�������ݿ������ļ�
		bool save_database_ini_file(const string&libraryName);//���浥�����ݿ������ļ�
		bool read_table_ini_file(const string&tableName);//��ȡtableName�������ļ�
		bool save_table_ini_file(const string&tableName);//����tableName�������ļ�
		bool read_table_data(const string&tableName);//��ȡ������
		bool save_table_data(const string&tableName);//���������
		
	};

}
