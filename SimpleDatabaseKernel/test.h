#ifndef _LexicalAnalysis_
#include"LexicalAnalysis.h"
#endif
#ifndef _TEST_
#define _TEST_
#endif
class FileTest {
public:
	void check_get_token();
	void test();
};
class LexicalTest {
public:
	void  check_dfa();
	void check_edge();
	void check_closure();
	void check_dfa_edge();
	void check_conver_table();
	void check_nfa_conver_to_dfa();
	void test();
};
class Test {
public:
	void test();
};
