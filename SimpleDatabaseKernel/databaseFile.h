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
		list<shared_ptr<Item>> itemPtrSet;//数据项
		bool dirtyPage;//脏页
		unsigned curPageNum;//当前页号
		unsigned itemSize;//数据项目个数
		vector<unsigned>deletedFlag;//未使用数据号
		unsigned pageSpaceMax;//最大页空间
		unsigned usedSpaceSize;//已使用空间
		unsigned unUsedSpaceSize;//未使用空间
		bool nextPageFlag;//是否还有下一个页
		unsigned nextPageNum;//下一页页号
		void clear();
	};
	using Page_ptr = Page*;
	using Page_ptr_ptr = Page_ptr*;
	struct RecordHeadInfo {//头部文件信息
		RecordHeadInfo();
		RecordHeadInfo(const RecordHeadInfo&obj);
		RecordHeadInfo&operator=(const RecordHeadInfo&obj);
		string tableName;//表名
		unsigned totalDataNum;//总计数据个数
		unsigned usedSpaceSize;//已使用空间大小
		int tableTypeNum;//列个数
		vector<AttributeType> type;//类型数组
		unsigned pageNumber;//页数
		vector<unsigned>pageOrder;//页序
		string addTiem, modificationTime;//添加时间，修改时间
		void clear();
		~RecordHeadInfo();
	};
	struct Record {	//记录结构
		Record();
		Record(const Record&obj);
		Record&operator=(const Record&obj);
		using Record_ptr = Record*;
		RecordHeadInfo headInfo;//首部信息
		list<shared_ptr<Page>>pagePtrSet;//页
		void clear();
		~Record();
	};
	struct RecordTable {
		string libraryName;//数据库名
		vector<Record> table;//数据库的所有内容
		size_t tableNumber;//表数量
		void clear();
		~RecordTable();
		//string addTiem, modificationTime;//添加时间，修改时间
	};

	class DatabaseFile
	{
	public:
		DatabaseFile();
		~DatabaseFile();
		bool read_database_data(const string&libraryName);//读取数据库数据
		shared_ptr<RecordTable> dataMangementPtr;//数据库数据
		shared_ptr<NameMangementFile> nameMangementTablePtr;
		bool save();
		friend class dataMangement;
	private:
		void set_current_database_name(const string&libraryName);//切换当前数据库
		bool read_database_mangement_system_ini_file();//读取数据库管理系统配置文件
		bool save_database_mangement_system_ini_file();//保存数据库管理系统配置文件
		bool read_database_ini_file(const string&libraryName);//读取单个数据库配置文件
		bool save_database_ini_file(const string&libraryName);//保存单个数据库配置文件
		bool read_table_ini_file(const string&tableName);//读取tableName表配置文件
		bool save_table_ini_file(const string&tableName);//保存tableName表配置文件
		bool read_table_data(const string&tableName);//读取表数据
		bool save_table_data(const string&tableName);//保存表数据
		
	};

}
