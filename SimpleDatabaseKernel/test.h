#ifndef _LexicalAnalysis_
#include"LexicalAnalysis.h"
#endif
#ifndef _TEST_
#define _TEST_
#endif
class FileTest {
public:
	void checkGetToken();
	void test();
};
class LexicalTest {
public:
	void  checkDfa();
	void checkedge();
	void checkclosure();
	void checkDfaEdge();
	void checkConverTable();
	void checkNfaConvertToDfa();
	void test();
};
class Test {
public:
	void test();
};
