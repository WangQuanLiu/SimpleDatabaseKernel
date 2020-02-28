#include"index.h"
namespace dbm {
	OriginalData::OriginalData()
	{
		//this->itemPtr = nullptr;

	}

	OriginalData::~OriginalData()
	{
	}

	OriginalData & OriginalData::operator=(const OriginalData & obj)
	{
		//this->itemPtr = obj.itemPtr;
		this->pagePosi = obj.pagePosi;
		return *this;
	}
	bool operator!=(const OriginalData&objOne, const OriginalData&objTwo) {
		return !(objOne == objTwo);
	}
	bool operator==(const OriginalData&objOne, const OriginalData&objTwo) {
		return objOne.pagePosi == objOne.pagePosi;
	}
	bool operator==(const PagePosi&objOne, const PagePosi&objTwo) {
		return objOne.pageNumber == objTwo.pageNumber&&objOne.posi == objTwo.posi;
	}
	PagePosi::PagePosi()
	{
	}
	PagePosi::~PagePosi()
	{
	}
	BPlusTreeInterface::BPlusTreeInterface()
	{
		this->bPlusRoot = new BPlusNode();
	}
	//indexResultDataSetPtr BPlusTreeInterface::range_query(bPlusType keywordOne, bPlusType keywordTwo)
	//{
	//	return range_query( keywordOne, keywordTwo);
	//}
	indexResultDataSetPtr BPlusTreeInterface::range_query(bPlusType keyword)
	{
		return this->range_query( keyword, keyword);
	}
	bool BPlusTreeInterface::modifiy(BPlusData & isModifiy, BPlusData & modifiryer)
	{
		BPlusNode_ptr ptr = inner_query(*this->bPlusRoot, isModifiy.keyword);
		if (ptr == nullptr)return false;
		else {
			int i;
			do {
				for (i = 0; i < ptr->cot; i++) {
					if (ptr->keyword[i] == isModifiy.keyword&&
						ptr->nextNode.leaf.position[i] == isModifiy.orignalData) {
						ptr->keyword[i] = modifiryer.keyword;
						ptr->nextNode.leaf.position[i] = modifiryer.orignalData;
						return true;
					}
				}
				if (i >= ptr->cot&&ptr->keyword[ptr->cot - 1] == isModifiy.keyword) {
					ptr = ptr->nextNode.leaf.next;
				}
				else break;
			} while (ptr != nullptr);
			return false;
		}
	}
	/*
	功能：查询数据
	*/
	BPlusNode_ptr BPlusTreeInterface::inner_query(BPlusNode&node, bPlusType & keyword)
	{
		if (node.proerty == bt_leaf) {
			int i;
			for (i = 0; i < node.cot; i++) {
				if (node.keyword[i] > keyword)break;
			}
			if (i >= node.cot)return nullptr;
			else return &node;
		}
		else {
			int i, nearst = -1;
			for (i = 0; i < node.cot; i++) {
				if (keyword < node.keyword[i])nearst = i;
			}
			if (nearst == -1) {
				return inner_query(*node.nextNode.next[i], keyword);
			}
			else
				return inner_query(*node.nextNode.next[nearst], keyword);
		}
	}
	/*
	功能：按范围查询数据
	*/
	indexResultDataSetPtr BPlusTreeInterface::range_query( bPlusType keywordOne, bPlusType keywordTwo)
	{
		BPlusNode_ptr nodePtr=inner_query(*this->bPlusRoot, keywordOne);
		if (nodePtr == nullptr)return nullptr;
			bool flag = false;
			int i;
			BPlusNode_ptr next;
			indexResultDataSetPtr ptr=shared_ptr<indexResultDataSet>( new indexResultDataSet());
			do {
				for (i = 0; i < nodePtr->cot; i++) {
					if (nodePtr->keyword[i] > keywordOne&&nodePtr->keyword[i] < keywordTwo) {
						flag = true;
						ptr->list.push_back(indexResultData(nodePtr->keyword[i], nodePtr->nextNode.leaf.position[i]));
					}
					else {
						break;
					}
				}
				next = nodePtr->nextNode.leaf.next;
			} while (i>= nodePtr->cot&&next != nullptr);
			if (!flag)return nullptr;
		
			return ptr;
	}
	/*
	输入：B+树类型值 value
	功能：寻找这个值
	输出：成功返回true,失败返回false
	*/
	BPlusResult BPlusTreeInterface::find(BPlusData&value)
	{
		return find(*this->bPlusRoot, value);
	}

	/*
	输入：B+树类型值 value
	功能：寻找这个值
	输出：成功返回true,失败返回false
	*/
	BPlusResult BPlusTreeInterface::find(BPlusNode & node, BPlusData&value)
	{

		if (node.proerty == bt_internal_node) {//叶子结点

			int i = 0, cot = 0; BPlusResult result;
			BPlusNode_ptr temp = &node;
			bool flag = true;
			while (flag) {
				flag = false;
				for (; i < node.cot; i++) {
					if (node.keyword[i] == value.keyword) {
						cot++;
						result.push_back(BPlusResultData( make_shared<OriginalData>(temp->nextNode.leaf.position[i])));
					}
				}
				if (node.cot >= B_PLUS_TREE_KEYWORD_SIZE&&node.keyword[B_PLUS_TREE_KEYWORD_SIZE - 1] == value.keyword) {
					if (temp->nextNode.next != nullptr) {
						temp = temp->nextNode.leaf.next;
						flag = true;
					}

				}
			}
			if (cot == 0)return result;

		}
		else {//*内部结点*/
			  //	BPlusNode& internalNode = node.node.internalNode;
			int i = 0, nearst = -1;
			for (; i < node.cot; i++) {
				if (value.keyword <= node.keyword[i]) {
					nearst = i;
				}
			}
			if (nearst == -1)return  BPlusResult();
			else {
				if (node.nextNode.next[nearst] != nullptr) {
					find(*node.nextNode.next[nearst], value);
				}
			}

		}

		return BPlusResult();
	}
	/*
	输入：B+树类型值 value
	功能：插入这个值
	输出：成功返回true,失败返回false
	*/
	bool BPlusTreeInterface::insert(BPlusData & value)
	{
		if (this->bPlusRoot->cot == 0) {
			this->bPlusRoot->keyword[this->bPlusRoot->cot] = value.keyword;
			this->bPlusRoot->proerty = bt_leaf;
			this->bPlusRoot->keyword[this->bPlusRoot->cot] = value.keyword;
			this->bPlusRoot->nextNode.leaf.position[this->bPlusRoot->cot] = value.orignalData;
			this->bPlusRoot->cot++;
			this->bPlusRoot->pointCot++;//添加于 2020/2/15 12:39
			return true;
		}
		return insert(this->bPlusRoot, value);
	}
	/*
	输入：B+树类型值 value
	功能：插入这个值
	输出：成功返回true,失败返回false
	*/
	bool BPlusTreeInterface::insert(BPlusNode_ptr  node, BPlusData & value)
	{
		if (node->proerty == bt_leaf) {
			if (node->cot < B_PLUS_TREE_KEYWORD_SIZE - 1) {
				insert_in_leaf(node, value);
			}
			else {//有n-1个，
				BPlusNode_ptr temp = new BPlusNode(), L = new BPlusNode();
			
				int i;
				for (i = 0; i < B_PLUS_TREE_KEYWORD_SIZE - 1; i++) {
					temp->keyword[i] = node->keyword[i];
					temp->nextNode.leaf.position[i] = node->nextNode.leaf.position[i];
				}
				temp->cot = B_PLUS_TREE_KEYWORD_SIZE - 1;//删除+ 于2020/2/15 12:38	 
				temp->proerty = bt_leaf;
				temp->parent = node;
				insert_in_leaf(temp, value);
				L->keyword[B_PLUS_TREE_KEYWORD_SIZE - 1] = node->keyword[B_PLUS_TREE_KEYWORD_SIZE - 1];
				L->nextNode.leaf.position[B_PLUS_TREE_KEYWORD_SIZE - 1] = node->nextNode.leaf.position[B_PLUS_TREE_KEYWORD_SIZE - 1];
				L->nextNode.leaf.next = node->nextNode.leaf.next;
				node->nextNode.leaf.next = L;
				node->cot = 0;
				for (i = 0; i < B_PLUS_TREE_KEYWORD_SIZE; i++) {
					node->keyword[i] = "";
					node->nextNode.leaf.position[i] = OriginalData();
				}
				for (i = 0; i < B_PLUS_TREE_KEYWORD_SIZE / 2; i++) {
					node->keyword[i] = temp->keyword[i];
					node->nextNode.leaf.position[i] = temp->nextNode.leaf.position[i];
					L->keyword[i] = temp->keyword[B_PLUS_TREE_KEYWORD_SIZE / 2 + i];
					L->nextNode.leaf.position[i] = temp->nextNode.leaf.position[B_PLUS_TREE_KEYWORD_SIZE / 2 + i];
				}
				L->pointCot = node->pointCot = L->cot = node->cot = B_PLUS_TREE_KEYWORD_SIZE / 2;
				node->proerty = L->proerty = bt_leaf;
				insert_in_parent(node, L->keyword[0], L);
			}
		}
		else {

			int i;
			for (i = 0; i < node->cot; i++) {
				if (node->keyword[i] > value.keyword) {
					break;
				}
			}/*if (i >= node->cot)i--;*/
			insert(node->nextNode.next[i], value);

		}
		return true;
	}
	/*
	输入：BPlusData 数据
	功能：如果有删除此数据
	输出：如果删除成功返回ture,失败返回false
	*/
	bool BPlusTreeInterface::erase(BPlusData & data)
	{
		BPlusNode_ptr ptr = find_leaf(this->bPlusRoot, data);
		if (ptr == nullptr)return false;
		return erase(ptr, data, nullptr);
	}
	/*
	输入：BPlusData 数据
	功能：如果有删除此数据
	输出：如果删除成功返回ture,失败返回false
	*/
	bool BPlusTreeInterface::erase(BPlusNode_ptr nodePtr, BPlusData&data, BPlusNode_ptr ptr)
	{
		//删除叶节点or内部节点
		if (nodePtr->proerty == bt_leaf) {
			if (!erase_leaf_values(nodePtr, data))
				return false;
		}
		else {
			if (!erase_internode_values(nodePtr, data.keyword, ptr))
				return false;
		}
		if (*nodePtr == *this->bPlusRoot&&nodePtr->pointCot == 1) {//nodePtr为根结点
			if (nodePtr->proerty == bt_internal_node) {
				this->bPlusRoot = nodePtr->nextNode.next[0];
				this->bPlusRoot->parent = nullptr;
			}
			delete nodePtr;
		}
		else if (nodePtr->cot < B_PLUS_TREE_KEYWORD_MIN_SIZE) {
			BPlusNode_ptr tempPtr, parent = nodePtr->parent;
			bPlusType tempKeyword;
			pair<pair<BPlusNode_ptr, bPlusType>, pair<int, int>>pairTemp =
				find_appropriate_pointer_and_values(parent, nodePtr);//寻找合适相邻的指针和关键字
			tempPtr = pairTemp.first.first;
			tempKeyword = pairTemp.first.second;
			if (tempPtr->cot + nodePtr->cot < B_PLUS_TREE_KEYWORD_SIZE) {//可以放在一个结点
				if (pairTemp.second.second < pairTemp.second.first) {//选中的指针在ptr后面
					swap_values<BPlusNode>(*tempPtr, *nodePtr);//交换值,tempPtr在前,ptr在后
				}
				if (nodePtr->proerty == bt_internal_node) {//内部结点
					insert_keyword_and_values_to_internal_node(tempPtr, tempKeyword, nodePtr);
				}
				else {//叶结点
					insert_keyword_and_values_to_leaf_node(tempPtr, nodePtr);
				}
				erase(nodePtr->parent, BPlusData(tempKeyword, OriginalData()), nodePtr);
			}
			else {//借索引项
				if (pairTemp.second.second < pairTemp.second.first) {//ptr在ptrTemp前面
					if (nodePtr->proerty == bt_internal_node) {//内部结点
						borrow_one_values_from_adjacent_internal_node(nodePtr, tempKeyword, tempPtr);
						// replace_keyword_on_one_node(parent, tempKeyword, tempPtr->keyword[tempPtr->cot - 1], tempPtr);
					}
					else {//叶结点
						borrow_one_values_from_adjacent_leaf_node(nodePtr, tempPtr);
					}
					replace_keyword_on_one_node(parent, tempKeyword, tempPtr->keyword[tempPtr->cot - 1], tempPtr);
				}
				else {//ptrTemp在ptr前面
					if (nodePtr->proerty == bt_internal_node) {
						borrow_one_values_from_adjacent_internal_node(tempPtr, tempKeyword, nodePtr);
					}
					else {
						borrow_one_values_from_adjacent_leaf_node(tempPtr, nodePtr);
					}
					replace_keyword_on_one_node(parent, tempKeyword, nodePtr->keyword[nodePtr->cot - 1], nodePtr);
				}
			}
		}
		return true;
	}

	BPlusTreeInterface::~BPlusTreeInterface()
	{

	}
	/*
	输入：praent和ptr两个内部节点和keyword关键字
	功能：新建一个扩展结点，并把praent和ptr和keyword关键字插入进去
	输出：返回扩展结点
	*/
	ExtendInternalNode BPlusTreeInterface::insert_extendInternalNode(BPlusNode_ptr praent, bPlusType & keyword, BPlusNode_ptr ptr)
	{
		ExtendInternalNode extendNode;
		int j;
		for (j = 0; j < praent->cot; j++) {//先插入结点，并形成扩展内部结点结构，然后进行拆分
			extendNode.keyword[j] = praent->keyword[j];
			extendNode.nextPtr[j] = praent->nextNode.next[j];
		}
		extendNode.nextPtr[j] = praent->nextNode.next[j];
		extendNode.cot = praent->cot;
		for (j = 0; j < extendNode.cot; j++) {
			if (extendNode.keyword[j] > keyword)break;
		}
		if (j >= extendNode.cot) {//插入到最后
			extendNode.keyword[extendNode.cot] = keyword;
			extendNode.nextPtr[extendNode.cot + 1] = ptr;
			extendNode.cot++;
		}
		else {//插到中间
			bPlusType keywordTemp = keyword, keywordTempTwo;
			BPlusNode_ptr ptrTemp = ptr, ptrTempTwo;
			keywordTemp = extendNode.keyword[j];
			ptrTemp = extendNode.nextPtr[j + 1];
			extendNode.keyword[j] = keyword;
			extendNode.nextPtr[j + 1] = ptr;
			for (++j; j < extendNode.cot; j++) {
				keywordTempTwo = extendNode.keyword[j];
				ptrTempTwo = extendNode.nextPtr[j + 1];
				extendNode.keyword[j] = keywordTemp;
				extendNode.nextPtr[j + 1] = ptrTemp;
				keywordTemp = keywordTempTwo;
				ptrTemp = ptrTempTwo;
			}
			extendNode.keyword[j] = keywordTemp;
			extendNode.nextPtr[j + 1] = ptrTemp;
			extendNode.cot++;
		}

		return extendNode;
	}
	/*
	输入：ptrOne为前结点，keyword关键字在中间，ptrTwo为后结点
	功能：新建一个内部结点，并把ptrOne和ptrTwo，插入到新结点，并使内部结点的关键字为keyword
	输出：返回内部结点
	*/
	inline BPlusNode_ptr BPlusTreeInterface::crate_new_node(BPlusNode_ptr ptrOne, bPlusType keyword, BPlusNode_ptr ptrTwo)
	{
		BPlusNode_ptr ptr = new BPlusNode();
		if (ptr == nullptr)return nullptr;
		ptr->keyword[0] = keyword;
		ptr->proerty = bt_internal_node;
		ptr->cot++;
		ptr->nextNode.next[0] = ptrOne;
		ptr->nextNode.next[1] = ptrTwo;
		ptrOne->parent = ptr;
		ptrTwo->parent = ptr;
		ptr->pointCot = 2;
		this->bPlusRoot = ptr;
		return ptr;
	}
	/*
	输入：parentPtr为nodePtr的父结点,replacer为替换者，isReplaced为被替换者，
	功能：把nodePtr中的isReplaced关键字替换成replacer
	输出：成功返回true,失败返回false
	*/
	inline bool BPlusTreeInterface::replace_keyword_on_one_node(BPlusNode_ptr parentPtr, bPlusType replacer, bPlusType isReplaced, BPlusNode_ptr nodePtr)
	{
		int i;
		for (i = 0; i < parentPtr->cot; i++) {
			if (parentPtr->keyword[i] == isReplaced&&*parentPtr->nextNode.next[i + 1] == *nodePtr) {
				break;
			}
		}
		if (i >= parentPtr->cot)return false;
		parentPtr->keyword[i] = replacer;
		return true;
	}
	/*
	输入：borrow为借用者，keyword关键字，isBorrow为被借用者
	功能：把isBorrow的最后一个关键字和指针与keyword插入到borrow中
	输出：成功返回true,失败返回false
	*/
	inline bool BPlusTreeInterface::borrow_one_values_from_adjacent_internal_node(BPlusNode_ptr borrower, bPlusType keyword, BPlusNode_ptr isBorrowed)
	{
		if (borrower->proerty != bt_internal_node || isBorrowed->proerty != bt_internal_node)return false;
		BPlusNode_ptr tempPtr = isBorrowed->nextNode.next[isBorrowed->cot];
		bool flag = insert_in_middle_of_node(borrower, keyword, tempPtr, 0);
		if (flag) {
			isBorrowed->cot--;
			isBorrowed->pointCot--;
		}
		return flag;
	}
	/*
	输入：borrow为借用者，keyword关键字，isBorrow为被借用者
	功能：把isBorrow的最后一个关键字和指针与keyword插入到borrow中
	输出：成功返回true,失败返回false
	*/
	inline bool BPlusTreeInterface::borrow_one_values_from_adjacent_leaf_node(BPlusNode_ptr borrower, BPlusNode_ptr isBorrowed)
	{
		if (borrower->proerty != bt_leaf || isBorrowed->proerty != bt_leaf)return false;
		OriginalData temp = isBorrowed->nextNode.leaf.position[isBorrowed->cot - 1];
		bPlusType keyword = isBorrowed->keyword[isBorrowed->cot - 1];
		bool flag = insert_in_middle_of_leaf(borrower, BPlusData(keyword, temp), 0);
		if (flag) {
			isBorrowed->cot--;
			isBorrowed->pointCot--;
		}
		return flag;
	}
	/*
	输入：ptrOne代表被插入的结点指针，keyword关键字，ptr 要插入的指针
	功能：把keyword和ptr中的keyword和指针全部插入到ptrOne
	输出：成功返回true,失败返回false
	*/
	inline bool BPlusTreeInterface::insert_keyword_and_values_to_internal_node(BPlusNode_ptr ptrOne, bPlusType & keyword, BPlusNode_ptr ptrTwo)
	{
		if (ptrOne->proerty == bt_internal_node&&ptrTwo->proerty == bt_internal_node) {
			//内部结点ptr中的值复制到tempPtr中
			int i = ptrOne->cot, j;
			ptrOne->keyword[i] = keyword;
			for (j = 0, i++; j < ptrTwo->cot; j++, i++) {
				ptrOne->keyword[i] = ptrTwo->keyword[j];
				ptrOne->nextNode.next[i] = ptrTwo->nextNode.next[j];
			}
			ptrOne->nextNode.next[i] = ptrTwo->nextNode.next[j];
			ptrOne->cot += ptrTwo->cot;
			ptrOne->pointCot += ptrOne->pointCot;
			return true;
		}
		return false;
	}
	/*
	输入：ptrOne被插入指针，ptrTwo要插入的指针
	功能：把ptrTwo中的关键字和指针全部插入到ptrOne中
	输出：成功返回true,失败返回false
	*/
	inline bool BPlusTreeInterface::insert_keyword_and_values_to_leaf_node(BPlusNode_ptr ptrOne, BPlusNode_ptr ptrTwo)
	{

		if (ptrOne->proerty == bt_leaf&&ptrTwo->proerty == bt_leaf) {
			int i = ptrOne->cot, j;
			for (j = 0; j < ptrTwo->cot; j++, i++) {
				ptrOne->keyword[i] = ptrTwo->keyword[j];
				ptrOne->nextNode.leaf.position[i] = ptrTwo->nextNode.leaf.position[j];
			}
			ptrOne->nextNode.leaf.next = ptrTwo->nextNode.leaf.next;
			ptrOne->cot += ptrTwo->cot;
			ptrOne->pointCot += ptrTwo->pointCot;
			return true;
		}
		return false;
	}
	/*
	输入：parent 指nodePtr的父指针

	功能：	寻找nodePtr在父指针中的位置

   输出：	返回nodePtr的前一个结点或后一个结点，nodePtr和前一个结点或
		   后一个结点中间的关键字，nodePtr和它的前一个结点或后一个结在父指针
		   中的位置

	*/
	inline pair<pair<BPlusNode_ptr, bPlusType>, pair<int, int>> BPlusTreeInterface::find_appropriate_pointer_and_values(BPlusNode_ptr parent, BPlusNode_ptr nodePtr)
	{
		int i;
		for (i = 0; i <= parent->cot; i++) {
			if (*parent->nextNode.next[i] == *nodePtr) {
				break;
			}
		}
		if (i == 0) {
			return pair<pair<BPlusNode_ptr, bPlusType>, pair<int, int>>(pair<BPlusNode_ptr, bPlusType>(parent->nextNode.next[1], parent->keyword[0]), pair<int, int>(1, 0));
		}
		else if (i == parent->cot) {
			return pair<pair<BPlusNode_ptr, bPlusType>, pair<int, int>>(pair<BPlusNode_ptr, bPlusType>(parent->nextNode.next[parent->cot - 1], parent->keyword[parent->cot - 1]),
				pair<int, int>(i - 1, i));
		}
		else {
			if (parent->nextNode.next[i - 1]->cot + nodePtr->cot < B_PLUS_TREE_EXTEND_KEYWORD_SIZE) {
				return pair<pair<BPlusNode_ptr, bPlusType>, pair<int, int>>(pair<BPlusNode_ptr, bPlusType>
					(parent->nextNode.next[i - 1], parent->keyword[i - 1]), pair<int, int>(i - 1, i));
			}
			else {
				// return pair<BPlusNode_ptr, bPlusType>(parent->nextNode.next[i+1],parent->keyword[i]);
				return pair<pair<BPlusNode_ptr, bPlusType>, pair<int, int>>
					(pair<BPlusNode_ptr, bPlusType>(parent->nextNode.next[i + 1], parent->keyword[i]), pair<int, int>(i + 1, i));
			}
		}

	}
	/*
	输入：nodePtr包括data的叶子节点指针，data即将被删除的节点
	功能：从nodePtr中删除data
	输出：成功返回true,失败返回false
	*/
	inline bool BPlusTreeInterface::erase_leaf_values(BPlusNode_ptr nodePtr, BPlusData & data)
	{
		int i;
		if (nodePtr->proerty == bt_leaf) {//叶结点
			for (i = 0; i < nodePtr->cot; i++) {
				if (nodePtr->keyword[i] == data.keyword&&nodePtr->nextNode.leaf.position[i] == data.orignalData) {
					break;
				}
			}
			if (i >= nodePtr->cot)return false;
			else if (i == nodePtr->cot - 1) {//最后一个结点
			   // nodePtr->cot--;
				nodePtr->keyword[i] = "";
			}
			else {//要删除的结点在中间
				for (; i < nodePtr->cot - 1; i++) {
					nodePtr->keyword[i] = nodePtr->keyword[i + 1];
					nodePtr->nextNode.leaf.position[i] = nodePtr->nextNode.leaf.position[i + 1];
				}
				// nodePtr->cot--;
			}
			nodePtr->cot--;
			nodePtr->pointCot--;
			return true;
		}

		return false;
	}
	/*
	输入：nodePtr包括data的内部节点指针，data即将被删除的节点
	功能：从nodePtr中删除data
	输出：成功返回true,失败返回false
	*/
	inline bool BPlusTreeInterface::erase_internode_values(BPlusNode_ptr nodePtr, bPlusType & keyword, BPlusNode_ptr ptr)
	{
		if (nodePtr->proerty == bt_internal_node) {
			if (nodePtr->cot == 1) {
				int i;
				for (i = 0; i < nodePtr->pointCot; i++) {
					if (*nodePtr->nextNode.next[i] == *ptr) {
						break;
					}
				}
				if (i >= nodePtr->pointCot)return false;
				if (i == 0) {
					nodePtr->nextNode.next[i] = nodePtr->nextNode.next[i + 1];
				}
				nodePtr->pointCot--;
			}
			else {
				int i;
				for (i = 0; i < nodePtr->cot; i++) {
					if (nodePtr->keyword[i] == keyword&& *nodePtr->nextNode.next[i + 1] == *ptr) {
						break;
					}
				}
				if (i >= nodePtr->cot)return false;
				else if (i == nodePtr->cot - 1) {
					// nodePtr->cot--;
					nodePtr->keyword[nodePtr->cot].s.clear();
				}
				else {
					for (; i < nodePtr->cot - 1; i++) {
						nodePtr->keyword[i] = nodePtr->keyword[i + 1];
						nodePtr->nextNode.next[i + 1] = nodePtr->nextNode.next[i + 2];
					}
					// nodePtr->cot--;
				}
				nodePtr->cot--;
				nodePtr->pointCot--;//添加于 2020/2/15

			}
			return true;
		}
		return false;
	}
	/*
	输入：node结点，value值
	功能：寻找包含value值的叶结点
	输出：成功返回包含叶结点的指针，失败返回nullptr
	*/
	BPlusNode_ptr BPlusTreeInterface::find_leaf(BPlusNode_ptr & node, BPlusData & value)const
	{
		if (node->proerty == bt_leaf) {//叶结点
			int i;
			for (i = 0; i < node->cot; i++) {
				if (node->keyword[i] == value.keyword&&node->nextNode.leaf.position[i] == value.orignalData) {
					break;
				}
			}
			if (i < node->cot) { return node; }//找到
			else { return nullptr; }
		}
		else {//内部结点
			int i;
			for (i = 0; i < node->cot; i++) {
				if (node->keyword[i] > value.keyword) {
					break;
				}
			}
			return  find_leaf(node->nextNode.next[i], value);
		}

	}
	/*
	输入：B+树叶结点指针node，B+树类型值 value
	功能：在node插入value
	输出：成功返回true,失败返回false
	*/
	bool BPlusTreeInterface::insert_in_leaf(BPlusNode_ptr  node, BPlusData & value)
	{
		int i;
		bPlusType type; OriginalData data;
		if (node->keyword[0] > value.keyword) {
			insert_in_middle_of_leaf(node, value, 0);
		}
		else {
			for (i = 1; i < node->cot; i++) {
				if (value.keyword < node->keyword[i]) {
					break;
				}
			}
			if (i >= node->cot) {
				node->keyword[node->cot] = value.keyword;
				node->nextNode.leaf.position[node->cot] = value.orignalData;
				node->cot++;
				node->pointCot++;
				return true;
			}
			// else i++;
			insert_in_middle_of_leaf(node, value, i);
		}

		return true;
	}

	/*
	输入：B+树内部结点指针node，B+树类型值 value
	功能：插入这个值
	输出：成功返回true,失败返回false
	*/
	bool BPlusTreeInterface::insert_in_parent(BPlusNode_ptr  node, bPlusType & keyword, BPlusNode_ptr p)
	{
		if (node == this->bPlusRoot) {//根结点
			if (node->cot + p->cot < B_PLUS_TREE_KEYWORD_SIZE&&node->proerty == bt_internal_node) {
				int i, nearst = 0;
				for (i = 0; i < node->cot; i++) {
					if (node->keyword[i]>keyword)break;
					nearst = i;
				}
				nearst--;
				if (node->proerty == bt_internal_node) {//指向内部结点
					insert_in_middle_of_node(node, keyword, p, nearst);
				}
			}
			else {	//创建新结点指向这两个结点
				this->bPlusRoot = crate_new_node(node, keyword, p);
			}
			return true;
		}
		BPlusNode_ptr praent = node->parent;
		int i;
		for (i = 0; i < praent->cot + 1; i++) {
			if (*praent->nextNode.next[i] == *node) {
				break;
			}
		}
		if (praent->cot < B_PLUS_TREE_KEYWORD_SIZE) {//未满足拆分条件
			insert_in_middle_of_node(praent, keyword, p, i);
		}
		else {//拆分内部结点，向上递归并回溯
			ExtendInternalNode extendNode = insert_extendInternalNode(praent, keyword, p);
			int j;
			praent->clear();//数据清空
			BPlusNode_ptr ptr = new BPlusNode();
			ptr->clear();
			/*	六指针 五关键字	拆分成 关键字 指针 1~2左 4~5右		*/
			for (j = 0; j < B_PLUS_TREE_KEYWORD_SIZE / 2; j++) {
				praent->keyword[j] = extendNode.keyword[j];
				praent->nextNode.next[j] = extendNode.nextPtr[j];
				praent->nextNode.next[j]->parent = praent;
				ptr->keyword[j] = extendNode.keyword[B_PLUS_TREE_KEYWORD_SIZE / 2 + j + 1];
				ptr->nextNode.next[j] = extendNode.nextPtr[B_PLUS_TREE_KEYWORD_SIZE / 2 + j + 1];
				ptr->nextNode.next[j]->parent = ptr;
			}
			// ptr->keyword[j] = extendNode.keyword[j];
			ptr->nextNode.next[j] = extendNode.nextPtr[B_PLUS_TREE_KEYWORD_SIZE / 2 + j + 1];
			ptr->nextNode.next[j]->parent = ptr;
			praent->nextNode.next[j] = extendNode.nextPtr[j];
			praent->nextNode.next[j]->parent = praent;
			praent->cot = ptr->cot = B_PLUS_TREE_KEYWORD_SIZE / 2;
			praent->pointCot = ptr->pointCot = B_PLUS_TREE_KEYWORD_SIZE / 2 + 1;//添加于 2020/2/15 12:54
			ptr->proerty = praent->proerty;
			insert_in_parent(praent, extendNode.keyword[B_PLUS_TREE_KEYWORD_SIZE / 2], ptr);
		}
		return true;
	}
	/*
	输入：bPlusNode_ptr B+树内部指点指针，keyword关键字，p指针，num为插入的位置
	功能：在num位置插入关键字与指针(指针位置为num+1)到node中
	输出：成功返回true,失败返回false

	*/
	bool BPlusTreeInterface::insert_in_middle_of_node(BPlusNode_ptr  node, bPlusType&keyword, BPlusNode_ptr p, const unsigned num)
	{
		if (node->cot + 1 > B_PLUS_TREE_KEYWORD_SIZE || node->proerty == bt_leaf)return false;
		if (node->cot < num) {
			node->keyword[num] = keyword;
			node->nextNode.next[num] = p;
			node->cot++;
			return true;
		}
		bPlusType bplusType, bplusTypeTwo;
		BPlusNode_ptr temp, tempTwo;
		int i = num;
		bplusType = node->keyword[i];
		temp = node->nextNode.next[i + 1];
		node->keyword[i] = keyword;
		node->nextNode.next[i + 1] = p;
		i++;
		for (; i < node->cot; i++) {
			bplusTypeTwo = node->keyword[i];
			tempTwo = node->nextNode.next[i + 1];
			node->keyword[i] = bplusType;
			node->nextNode.next[i + 1] = temp;
			bplusType = bplusTypeTwo;
			temp = tempTwo;
		}
		node->keyword[i] = bplusType;
		node->nextNode.next[i + 1] = temp;
		p->parent = node;
		node->cot++;
		node->pointCot++;
		return true;
	}
	/*
	输入：bPlusNode_ptr B+树叶结点指针，keyword关键字，p指针，num为插入的位置
	功能：在num位置插入关键字与指针(指针位置为num+1)
	输出：成功返回true,失败返回false

	*/
	bool BPlusTreeInterface::insert_in_middle_of_leaf(BPlusNode_ptr  node, BPlusData & value, const unsigned num)
	{
		if (node->cot + 1 > B_PLUS_TREE_KEYWORD_SIZE || node->proerty == bt_internal_node)return false;
		//bPlusType bplusType;
		BPlusData temp, tempTwo;
		int i = num;
		temp.keyword = node->keyword[i];
		temp.orignalData = node->nextNode.leaf.position[i];
		node->keyword[i] = value.keyword;
		node->nextNode.leaf.position[i] = value.orignalData;
		i++;
		for (; i < node->cot; i++) {
			tempTwo.keyword = node->keyword[i];
			tempTwo.orignalData = node->nextNode.leaf.position[i];
			node->keyword[i] = temp.keyword;
			node->nextNode.leaf.position[i] = temp.orignalData;
			temp = tempTwo;
		}
		node->keyword[i] = temp.keyword;
		node->nextNode.leaf.position[i] = temp.orignalData;
		node->cot++;
		node->pointCot++;
		return true;
	}

	void BPlusTreeInterface::clear()
	{
		 clear(this->bPlusRoot);
	}

	void BPlusTreeInterface::clear(BPlusNode_ptr nodePtr)
	{
		if (nodePtr->proerty == bt_leaf) {
		
			delete nodePtr->nextNode.leaf.next;
			delete nodePtr;
		}
		else {
			int i;
			for (i = 0; i < nodePtr->pointCot; i++) {
				clear(nodePtr->nextNode.next[i]);
				delete nodePtr->nextNode.next[i];
			}
			delete nodePtr;
		}
	}

	BPlusNode::Node::Node()
	{
	}

	BPlusNode::Node::~Node()
	{
	}

	BPlusNode::BPlusNode()
	{
		this->parent = nullptr;
		this->cot = this->pointCot = 0;
	}

	BPlusNode::BPlusNode(const BPlusNode & obj)
	{
		set_values(obj);
	}
	BPlusNode & BPlusNode::operator=(const BPlusNode & obj)
	{
		set_values(obj);
		return *this;
	}
	/*
	功能：清空操作
	*/
	void BPlusNode::clear()
	{
		int i;
		for (i = 0; i < this->cot; i++) {
			this->keyword[i] = "";
			this->nextNode.next[i] = nullptr;
		}
		this->nextNode.next[i] = nullptr;
		this->cot = 0;
		this->parent = nullptr;
		this->pointCot = 0;
	}

	void BPlusNode::set_values(const BPlusNode & obj)
	{
		clear();
		int i;
		this->parent = obj.parent;
		this->cot = obj.cot;
		this->proerty = obj.proerty;
		this->pointCot = obj.pointCot;
		// this->clear();
		if (obj.proerty == bt_internal_node) {
			for (i = 0; i < this->cot; i++) {
				this->keyword[i] = obj.keyword[i];
				this->nextNode.next[i] = obj.nextNode.next[i];
			}
			this->nextNode.next[i] = obj.nextNode.next[i];
		}
		else {
			for (i = 0; i < this->cot; i++) {
				this->keyword[i] = obj.keyword[i];
			}
			this->nextNode.leaf = obj.nextNode.leaf;
			//this->nextNode.leaf
		}
	}

	BPlusResultData::BPlusResultData( const shared_ptr<OriginalData>& dataPtr)
	{
		this->set_value( dataPtr);
	}

	inline void BPlusResultData::set_value( const shared_ptr<OriginalData>& dataPtr)
	{
		
		this->dataPtr = dataPtr;
	}

	BPlusData::BPlusData(const BPlusData & values)
	{
		this->keyword = values.keyword;
		this->orignalData = values.orignalData;
	}

	BPlusData::BPlusData(const bPlusType & keyword, const OriginalData & orignalData)
	{
		this->set_values(keyword, orignalData);
	}

	BPlusData & BPlusData::operator=(const BPlusData & obj)
	{
		this->keyword = obj.keyword;
		this->orignalData = obj.orignalData;
		return *this;
	}
	bool operator==(const BPlusData&objOne, const BPlusData&objTwo) {
		return objOne.keyword == objTwo.keyword&&objOne.orignalData == objTwo.orignalData;
	}

	void BPlusData::set_values(const bPlusType & keyword, const OriginalData & orignalData)
	{
		this->keyword = keyword;
		this->orignalData = orignalData;
	}
	bool operator==(const BPlusNode&objOne, const BPlusNode&objTwo) {
		bool flag = objOne.cot == objTwo.cot&&objOne.proerty == objTwo.proerty;
		
		if (flag) {
			if (objOne.proerty == bt_internal_node) {
				int i;
				for (i = 0; i < objOne.cot; i++) {
					if (objOne.nextNode.next[i] != objTwo.nextNode.next[i] ||
						objOne.keyword[i] != objTwo.keyword[i]) {
						flag = false;
						break;
					}
				}
				if (i >= objOne.cot)
					flag = objOne.nextNode.next[i] == objTwo.nextNode.next[i];
			}
			else {

				int i;
				for (i = 0; i < objOne.cot; i++) {
					if (objOne.nextNode.leaf.position[i] != objTwo.nextNode.leaf.position[i] ||
						objOne.keyword[i] != objTwo.keyword[i]) {
						flag = false;
						break;
					}
				}
			}
		}
		return flag;
	}



	bPlusType::bPlusType()
	{
		this->category = a_int;
	}

	bPlusType::bPlusType(const char * ch)
	{
		this->s = ch;
		this->category = a_int;
	}

	bPlusType::bPlusType(const string & str)
	{
		this->s = str;
		this->category = a_int;
	}

	void bPlusType::set_category(const AttributeType & category)
	{
		this->category = category;
	}
	bPlusType& bPlusType::operator=(const bPlusType & obj)
	{
		this->category = obj.category;
		this->s = obj.s;
		return *this;
	}
	bPlusType & bPlusType::operator=(const string & str)
	{
		this->s = str;
		return *this;
	}
	bPlusType & bPlusType::operator=(const char * ch)
	{
		this->s = ch;
		return *this;
	}
	bool operator==(const bPlusType&objOne, const bPlusType&objTwo) {
		if (objOne.category != objTwo.category)return false;
		if (objOne.category == a_int) {
			return atoi(objOne.s.c_str()) == atoi(objTwo.s.c_str());
		}
		else if (objOne.category == a_flaot)return atof(objOne.s.c_str()) == atof(objTwo.s.c_str());
		else return objOne.s == objTwo.s;
	}
	bool operator!=(const bPlusType&objOne, const bPlusType&objTwo) {
		return !(objOne == objTwo);
	}
	bool operator>(const bPlusType&objOne, const bPlusType&objTwo) {
		if (objOne.category != objTwo.category)return false;
		if (objOne.category == a_int) {
			return atoi(objOne.s.c_str()) > atoi(objTwo.s.c_str());
		}
		else if (objOne.category == a_flaot)
			return atof(objOne.s.c_str()) > atof(objTwo.s.c_str());
		else return objOne.s > objTwo.s;
	}
	bool operator<(const bPlusType&objOne, const bPlusType&objTwo) {
		if (objOne.category != objTwo.category)return false;
		if (objOne.category == a_int) {
			return atoi(objOne.s.c_str()) < atoi(objTwo.s.c_str());
		}
		else if (objOne.category == a_flaot) {
			return atof(objOne.s.c_str()) < atof(objTwo.s.c_str());
		}
		else
			return objOne.s < objTwo.s;
	}
	bool operator>=(const bPlusType&objOne, const bPlusType&objTwo) {
		return objOne > objTwo || objOne == objTwo;
	}
	bool operator<=(const bPlusType&objOne, const bPlusType&objTwo) {
		return objOne < objTwo || objOne == objTwo;
	}

	BPlusLeaf::BPlusLeaf()
	{
		this->next = nullptr;
	}

	BPlusLeaf & BPlusLeaf::operator=(const BPlusLeaf & obj)
	{
		int i;
		for (i = 0; i < B_PLUS_TREE_KEYWORD_SIZE; i++)
			this->position[i] = obj.position[i];
		this->next = obj.next;
		return *this;
	}
	indexResultData::indexResultData(const bPlusType & keyword, const OriginalData & info)
	{
		this->keyword = keyword;
		this->info = info;
	}
	indexResultData & indexResultData::operator=(const indexResultData & resultData)
	{
		this->keyword = resultData.keyword;
		this->info = resultData.info;
		return *this;
	}
	indexMangement::indexMangement()
	{
		read_index_ini();
	}
	/*
	功能：读取index.ini配置文件
	*/
	bool indexMangement::read_index_ini()
	{
		FILE*file = fopen(INDEX_FILE_HOME, "r");
		if (file == NULL)return false;
		int cot,i;
		char libraryName[CHAR_MAX],tableName[CHAR_MAX],colName[CHAR_MAX];
		memset(libraryName, 0, CHAR_MAX);
		memset(tableName, 0, CHAR_MAX);
		memset(colName, 0, CHAR_MAX);
		shared_ptr<index> temp=make_shared<index>( index());
		fscanf(file, "%d", &cot);
		for (i = 0; i < cot; i++) {
			fscanf(file, "%s %s %s %s",libraryName, libraryName, tableName, colName);
			temp->libraryName = libraryName;
			temp->tableName = tableName;
			temp->colName = colName;
			this->indexSet.push_back(temp);
		}
		fclose(file);
		return true;
	}
/*
功能：输出indexSet里面的内容
*/
	bool indexMangement::save_index_ini()
	{
		FILE*file = fopen(INDEX_FILE_HOME, "w");
		if (file == NULL)return false;
		int i;
		for (i = 0; i < this->indexSet.size(); i++) {
			fprintf(file, "<index> %s %s %s", this->indexSet[i]->libraryName.c_str(),
				this->indexSet[i]->tableName.c_str(), this->indexSet[i]->colName.c_str());
		}
		fclose(file);
		return true;
	}
	bool indexMangement::query_index(const string & libraryName, const string & tableName, const string & colName)
	{
		if (inner_query_index(libraryName, tableName, colName) != nullptr)return true;
		return false;
	}
	/*
	输入：库名，表名列名
	功能：查询该列是否有索引
	输出：有该索引返回索引指针，否则返回nullptr
	*/
	indexPtr indexMangement::inner_query_index(const string & libraryName, const string & tableName, const string & colName)
	{
		int i;
		for (i = 0; i < indexSet.size(); i++) {
			if (indexSet[i]->libraryName == libraryName&&
				indexSet[i]->tableName == tableName&&indexSet[i]->colName == colName) {
				return indexSet[i];
			}
		}	
		return nullptr;
	}
	/*
	输入：库名，表名，列名，列在表中的序号，记录结构
	功能：建立该列的索引
	输出：成功返回创建成功的索引号，否则为nullptr
	*/
	shared_ptr<index> indexMangement::create_index(const string & libraryName, const string & tableName, const string & colName, const int colIndex, Record&record)
	{
		if (inner_query_index(libraryName, tableName, colName) != nullptr)return nullptr;
		shared_ptr<index>ptr = make_shared<index>( index());
		if (ptr == nullptr||record.headInfo.tableName==tableName)return nullptr;
		int i,pageNum,j=0;
		list<shared_ptr<Page>>::iterator begin(record.pagePtrSet.begin());
		BPlusData data;
		for (i = 0; i < record.headInfo.pageNumber; i++,begin++) {
			pageNum = record.headInfo.pageOrder[i];
			Page &page = **begin;
			list<shared_ptr<Item>>::iterator itemBegin(page.itemPtrSet.begin());
			for (j = 0; j < page.itemSize; j++,itemBegin++) {
				Item& items = **itemBegin;
				data.keyword = items.item[colIndex].get_data();
					data.keyword.category = record.headInfo.type[colIndex];
				data.orignalData.pagePosi.pageNumber = i;
				data.orignalData.pagePosi.posi = j;
				ptr->bplus.insert(data);
			}
		}
		indexSet.push_back(ptr);
		return ptr;
	}
	/*
	输入：库名，表名，列名
	功能：删除该索引号
	输出：成功返回true,失败返回false
	*/
	bool indexMangement::erase_index(const string & libraryName, const string & tableName, const string & colName)
	{
		vector<shared_ptr<index>>::iterator begin(indexSet.begin()), end(indexSet.end());
		for (; begin != end; begin++) {
			if ((*begin)->libraryName == libraryName && 
				(*begin)->tableName == tableName &&
				(*begin)->colName == colName) {
				(*begin)->bplus.clear();
				indexSet.erase(begin);
				return true;
			}
		}
		return false;
	}
	indexResultDataSet & indexResultDataSet::operator+=( indexResultDataSet & dataSet)
	{
	
		std::list<indexResultData>::iterator dataSetBegin(dataSet.list.begin()),dataSetEnd(dataSet.list.end());
		for (; dataSetBegin != dataSetEnd; dataSetBegin++) {
			this->list.push_back(*dataSetBegin);
		}
		return *this;
	}
}