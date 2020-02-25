#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<bitset>
#include<string>
#include<list>
#include<memory>
#include<vector>
#include<set>
#ifndef _DATABASE_MANGEMENT_
#include"databaseMangement.h"
#endif
using namespace std;
namespace dbm {
	using namespace std;
#define B_PLUS_TREE_KEYWORD_SIZE 4
#define B_PLUS_TREE_POINTER_SIZE B_PLUS_TREE_KEYWORD_SIZE+1
#define B_PLUS_TREE_EXTEND_KEYWORD_SIZE 5
#define B_PLUS_TREE_EXTEND_POINTER_SIZE B_PLUS_TREE_EXTEND_KEYWORD_SIZE+1
#define B_PLUS_TREE_KEYWORD_MIN_SIZE B_PLUS_TREE_KEYWORD_SIZE/2
#define INDEX_FILE_HOME "C:\\databaseMangementSystem\\index.ini"
//#define CHAR_MAX 1000
	//using bPlusType =string;
	/*
					b+ tree
	*/
	enum treeProerty { bt_leaf, bt_internal_node };
//	enum AttributeType { integer, real, str };
	struct bPlusType {
		bPlusType();
		bPlusType(const char*ch);
		bPlusType(const string&str);
		void set_category(const AttributeType &category);
		friend bool operator==(const bPlusType&objOne, const bPlusType&objTwo);
		friend bool operator!=(const bPlusType&objOne, const bPlusType&objTwo);
		friend bool operator>(const bPlusType&objOne, const bPlusType&objTwo);
		friend bool operator<(const bPlusType&objOne, const bPlusType&objTwo);
		friend bool operator>=(const bPlusType&objOne, const bPlusType&objTwo);
		friend bool operator<=(const bPlusType&objOne, const bPlusType&objTwo);
		bPlusType& operator=(const bPlusType&obj);
		bPlusType&operator=(const string&str);
		bPlusType&operator=(const char*ch);
	public:
		string s;
		AttributeType category;
	};
	struct PagePosi {
		PagePosi();
		unsigned pageNumber;//页号
		unsigned posi;//页内位置
		PagePosi&operator=(const PagePosi&obj) = default;
		friend bool operator==(const PagePosi&objOne, const PagePosi&objTwo);
		~PagePosi();
	};

	struct OriginalData {//数据源结构
		OriginalData();
		//shared_ptr<Item>itemPtr;//指针数据指针
		PagePosi pagePosi;//页内位置信息
		~OriginalData();
		OriginalData&operator=(const OriginalData&obj);
		friend bool operator==(const OriginalData&objOne, const OriginalData&objTwo);
		friend bool operator!=(const OriginalData&objOne, const OriginalData&objTwo);
	};
	using OriginalData_ptr = OriginalData*;
	struct BPlusData {//B+数据结构
		bPlusType keyword;//键值 
		OriginalData orignalData;//源数据
		BPlusData() = default;
		BPlusData(const BPlusData&values);
		BPlusData(const bPlusType&keyword, const OriginalData&orignalData);
		BPlusData&operator=(const BPlusData&obj);
		friend bool operator==(const BPlusData&objOne, const BPlusData&objTwo);
		void set_values(const bPlusType&keyword, const OriginalData&orignalData);
	};
	struct BPlusNode;
	using BPlusNode_ptr = struct BPlusNode*;

	struct BPlusLeaf {
		BPlusLeaf();
		using BPlusLeaf_ptr = struct BPlusLeaf*;
		OriginalData position[B_PLUS_TREE_KEYWORD_SIZE]; BPlusNode_ptr next;
		BPlusLeaf&operator=(const BPlusLeaf&obj);
	};
	using BPlusLeaf_ptr = struct BPlusLeaf*;
	struct BPlusNode {
		BPlusNode();
		BPlusNode(const BPlusNode&obj);
		treeProerty proerty;//性质
		int cot, pointCot;//数量
		BPlusNode_ptr parent;//父类指针
		bPlusType keyword[B_PLUS_TREE_KEYWORD_SIZE];//关键字
		friend bool operator==(const BPlusNode&objOne, const BPlusNode&objTwo);
		BPlusNode&operator=(const BPlusNode&obj);
		union Node {
			BPlusNode_ptr next[B_PLUS_TREE_POINTER_SIZE];
			BPlusLeaf leaf;
			Node(); ~Node();
		};
		Node nextNode;
		void clear();
		void set_values(const BPlusNode&obj);
	};

	using BPlusNode_ptr = BPlusNode*;

	struct ExtendInternalNode {//扩展内部结点
		bPlusType keyword[B_PLUS_TREE_EXTEND_KEYWORD_SIZE];//扩展关键字
		BPlusNode_ptr nextPtr[B_PLUS_TREE_EXTEND_POINTER_SIZE];//指针扩展
		int cot;//数量
	};
	struct BPlusResultData {
		BPlusResultData() = default;
		BPlusResultData( const shared_ptr<OriginalData>&dataPtr);
		void set_value( const shared_ptr<OriginalData>&dataPtr);
//		int dataPosi;//数据位置
		shared_ptr<OriginalData>dataPtr;
	};

	using BPlusResult = list<BPlusResultData>;
	struct indexResultData {
		indexResultData() = default;
		indexResultData(const bPlusType&keyword, const OriginalData&info);
		indexResultData& operator=(const indexResultData&resultData);
		bPlusType keyword;
		OriginalData info;
	};
///	using indexReusltDataSet = 
	struct indexResultDataSet {
		list<indexResultData>list;
		indexResultDataSet& operator+=( indexResultDataSet&dataSet);
	};
	/* 命名方式需要更改，未带ptr无法分辨是变量还是指针 */
	using indexResultDataSetPtr = shared_ptr<indexResultDataSet>;
	struct BPlusTreeInterface {
	public:
		BPlusTreeInterface();
		indexResultDataSetPtr range_query(bPlusType keywordOne, bPlusType keywordTwo);
		indexResultDataSetPtr range_query(bPlusType keyword);
		bool modifiy(BPlusData&isModifiy, BPlusData&modifiryer);
		bool insert(BPlusData&value);//插入value
		bool insert(BPlusNode_ptr node, BPlusData&value);
		bool erase(BPlusData&data);//删除data
		bool erase(BPlusNode_ptr nodePtr, BPlusData&value, BPlusNode_ptr ptr);
		void clear();
		~BPlusTreeInterface();
	private:
		BPlusNode_ptr inner_query(BPlusNode&node, bPlusType& keyword);
	//	indexResultDataSetPtr range_query( bPlusType keywordOne, bPlusType keywordTwo);
		BPlusResult find(BPlusData&value);//检索value
		BPlusResult find(BPlusNode&node, BPlusData&value);
		ExtendInternalNode insert_extendInternalNode(BPlusNode_ptr parent, bPlusType& keyword, BPlusNode_ptr ptr);
		inline BPlusNode_ptr crate_new_node(BPlusNode_ptr ptrOne, bPlusType keyword, BPlusNode_ptr ptrTwo);
		inline bool replace_keyword_on_one_node(BPlusNode_ptr parentPtr, bPlusType replacer, bPlusType isReplaced, BPlusNode_ptr nodePtr);
		//	inline bool replace_keyword_on_one_leaf_node(BPlusNode_ptr parentPtr, bPlusType replacer, bPlusType isReplaced, BPlusNode_ptr data);
		inline bool borrow_one_values_from_adjacent_internal_node(BPlusNode_ptr borrower, bPlusType keyword, BPlusNode_ptr isBorrowed);
		inline bool borrow_one_values_from_adjacent_leaf_node(BPlusNode_ptr borrower, BPlusNode_ptr isBorrowed);
		inline bool insert_keyword_and_values_to_internal_node(BPlusNode_ptr ptrOne, bPlusType&keyword, BPlusNode_ptr ptrTwo);
		inline bool insert_keyword_and_values_to_leaf_node(BPlusNode_ptr ptrOne, BPlusNode_ptr ptrTwo);
		inline pair<pair<BPlusNode_ptr, bPlusType>, pair<int, int>>find_appropriate_pointer_and_values(BPlusNode_ptr parent, BPlusNode_ptr nodePtr);
		inline bool erase_leaf_values(BPlusNode_ptr nodePtr, BPlusData&data);
		inline bool erase_internode_values(BPlusNode_ptr nodePtr, bPlusType &keyword, BPlusNode_ptr ptr);
		BPlusNode_ptr find_leaf(BPlusNode_ptr&node, BPlusData&value)const;
		bool insert_in_leaf(BPlusNode_ptr node, BPlusData&value);
		bool insert_in_parent(BPlusNode_ptr node, bPlusType&value, BPlusNode_ptr p);
		bool insert_in_middle_of_node(BPlusNode_ptr node, bPlusType&keyword, BPlusNode_ptr p, const unsigned num);
		bool insert_in_middle_of_leaf(BPlusNode_ptr node, BPlusData&value, const unsigned num);

		void clear(BPlusNode_ptr nodePtr);
		string tableName;
		BPlusNode_ptr bPlusRoot;
	};
	struct index {
		BPlusTreeInterface bplus;
		string libraryName, tableName, colName;
	};
	using indexPtr = shared_ptr<index>;
	class indexMangement {
	public:
		bool read_index_ini();
		bool save_index_ini();
		indexPtr query_index(const string&libraryName, const string&tableName, const string&colName);
		shared_ptr<index> create_index(const string&libraryName, const string&tableName, const string&colName,const int colIndex, Record&record);
		bool erase_index(const string&libraryName, const string&tableName, const string&colName);
		vector<shared_ptr<index>> indexSet;
	};
	template<typename Type>
	void swap_values(Type& valuesOne, Type& valuesTwo);

	/*
	输入：两个类型变量 注意：需要有=运算符
	功能：交换两个变量里面的内容
	输出：void
	*/
	template<typename Type>
	inline void swap_values(Type& valuesOne, Type& valuesTwo)
	{
		Type temp;
		temp = valuesOne;
		valuesOne = valuesTwo;
		valuesTwo = temp;
	}
}