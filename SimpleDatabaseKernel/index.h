#pragma once
#include<iostream>
#include<bitset>
#include<string>
#ifndef _DATABASE_MANGEMENT_
#include"databaseMangement.h"
#endif
namespace dbm {
	using namespace std;
#define B_PLUS_TREE_KEYWORD_SIZE 4
#define B_PLUS_TREE_POINTER_SIZE B_PLUS_TREE_KEYWORD_SIZE+1
#define B_PLUS_TREE_EXTEND_KEYWORD_SIZE 5
#define B_PLUS_TREE_EXTEND_POINTER_SIZE B_PLUS_TREE_EXTEND_KEYWORD_SIZE+1
#define B_PLUS_TREE_KEYWORD_MIN_SIZE B_PLUS_TREE_KEYWORD_SIZE/2
	//using bPlusType =string;
	/*
					b+ tree
	*/
	enum treeProerty { bt_leaf, bt_internal_node };
	enum bPlusTypeCategory { integer, real, str };
	struct bPlusType {
		bPlusType();
		bPlusType(const char*ch);
		bPlusType(const string&str);
		void set_category(const bPlusTypeCategory &category);
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
		bPlusTypeCategory category;
	};
	struct PagePosi {
		PagePosi();
		unsigned pageNumber;//ҳ��
		unsigned posi;//ҳ��λ��
		PagePosi&operator=(const PagePosi&obj) = default;
		friend bool operator==(const PagePosi&objOne, const PagePosi&objTwo);
		~PagePosi();
	};

	struct OriginalData {//����Դ�ṹ
		OriginalData();
		//shared_ptr<Item>itemPtr;//ָ������ָ��
		PagePosi pagePosi;//ҳ��λ����Ϣ
		~OriginalData();
		OriginalData&operator=(const OriginalData&obj);
		friend bool operator==(const OriginalData&objOne, const OriginalData&objTwo);
		friend bool operator!=(const OriginalData&objOne, const OriginalData&objTwo);
	};
	using OriginalData_ptr = OriginalData*;
	struct BPlusData {//B+���ݽṹ
		bPlusType keyword;//��ֵ 
		OriginalData orignalData;//Դ����
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
		using BPlusLeaf_ptr = struct BPlusLeaf*;
		OriginalData position[B_PLUS_TREE_KEYWORD_SIZE]; BPlusNode_ptr next;
		BPlusLeaf&operator=(const BPlusLeaf&obj);
	};
	using BPlusLeaf_ptr = struct BPlusLeaf*;
	struct BPlusNode {
		BPlusNode();
		BPlusNode(const BPlusNode&obj);
		treeProerty proerty;//����
		int cot, pointCot;//����
		BPlusNode_ptr parent;//����ָ��
		bPlusType keyword[B_PLUS_TREE_KEYWORD_SIZE];//�ؼ���
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

	struct ExtendInternalNode {//��չ�ڲ����
		bPlusType keyword[B_PLUS_TREE_EXTEND_KEYWORD_SIZE];//��չ�ؼ���
		BPlusNode_ptr nextPtr[B_PLUS_TREE_EXTEND_POINTER_SIZE];//ָ����չ
		int cot;//����
	};
	struct BPlusResultData {
		BPlusResultData() = default;
		BPlusResultData(const int &dataPosi, const shared_ptr<OriginalData>&dataPtr);
		void set_value(const int &dataPosi, const shared_ptr<OriginalData>&dataPtr);
		int dataPosi;//����λ��
		shared_ptr<OriginalData>dataPtr;
	};

	using BPlusResult = list<BPlusResultData>;//B+���ݷ���
	/* ������ʽ��Ҫ���ģ�δ��ptr�޷��ֱ��Ǳ�������ָ�� */
	struct BPlusTreeInterface {
	public:
		BPlusTreeInterface();
		BPlusResult find(BPlusData&value);//����value
		BPlusResult find(BPlusNode&node, BPlusData&value);

		bool insert(BPlusData&value);//����value
		bool insert(BPlusNode_ptr node, BPlusData&value);
		bool erase(BPlusData&data);//ɾ��data
		bool erase(BPlusNode_ptr nodePtr, BPlusData&value, BPlusNode_ptr ptr);

		~BPlusTreeInterface();
	private:
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
		string tableName;
		BPlusNode_ptr bPlusRoot;
	};
	template<typename Type>
	void swap_values(Type& valuesOne, Type& valuesTwo);

	/*
	���룺�������ͱ��� ע�⣺��Ҫ��=�����
	���ܣ����������������������
	�����void
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