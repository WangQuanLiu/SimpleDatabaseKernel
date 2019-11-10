#include"test.h"
void LexicalTest::checkDfa()//²é¿´DFA
{
	int i,j;
	//LexicalAnalysis lexcalAnalysis;
	for (i = 1; i <NFA_ROW_MAX; i++) {
		std::cout << "cur status:" << i << std::endl;
		for (j = 0; j < NFA_COL_MAX-1; j++) {
			if (LexicalAnalysis::nfa[i][j] != 0) {
				std::cout << LexicalAnalysis::alphabet[j] << "->" <<LexicalAnalysis:: nfa[i][j] << "  ,";
			}
		}
		if (LexicalAnalysis::nfa[i][j] != 0)
			std::cout << "¦Å" << "->" <<LexicalAnalysis::nfa[i][j];
		std::cout << "\n";
		getchar();
}

}
template<typename T>
void print(vector<T>&vec) {
	cout << "print" << endl;
	for each (T var in vec)
	{
		std::cout << var << " ";
	}
	cout << endl;
}
void LexicalTest::checkedge()
{
	char c;
	while(cin>>c&&c!='#')
	LexicalAnalysis::edge(0, c);
}

void LexicalTest::checkclosure()
{
	cout << "check closure:" << endl;
	int s;
	while (cin >> s &&s!=0&&s<NFA_ROW_MAX) {
		vector<int>temp(LexicalAnalysis::closure(s));
		cout << "it has status item as follow:" << endl;
		print<int>(temp);
	}
}

void LexicalTest::checkDfaEdge()
{

	cout << "check DfaEdge:" << endl;
	char  ch;
	int input;
	vector<int>vec;
	do {
		cout << "ÊäÈë×´Ì¬¼¯ -1½áÊø" << endl;
		while (cin >> input && input != -1)
			vec.push_back(input);
		cout << "ÊäÈë×Ö·û" << endl;
		cin >> ch;
		vec = LexicalAnalysis::dfaEdge(vec, ch);
		print<int>(vec);
		vec.clear();
		cout << "#½áÊøÑ­»·" << endl;

	} while (cin>>ch&&ch != '#');

}

void LexicalTest::checkConverTable()
{
	ConverTable con;
	int status, val;
	char ch;
	while (cout << "ÊäÈë×´Ì¬ºÅ£¬×Ö·ûÓëÖµ ÊäÈë×´Ì¬ºÅÎª-1½áÊø"<<endl&&cin >> status >> ch
		>> val&&status!=-1) {
		con.addMap(status, ch, val);
	}
	vector<vector<int>>vec(con.getStatus());
	for (unsigned i = 0; i < vec.size(); i++) {
		
		for (unsigned j = 0; j < vec[i].size(); j++) {
			if(vec[i][j])
			cout << "["<<i<<"]"<<"["<<j<<"]=" << vec[i][j] << " ";
		}
		cout << endl;
	}
	while (cout << "ÊäÈë×´Ì¬ºÅ£¬×Ö·û ÊäÈë×´Ì¬ºÅÎª-1½áÊø" << endl && cin >>
		status >> ch  && status != -1) {
		int index(letterConvertToIndex(LexicalAnalysis::alphabet, ALPH_MAX, ch));
		cout << con.status[con.mapStatus[status]][index] << endl;
	}

}

void LexicalTest::checkNfaConvertToDfa()
{
	LexicalAnalysis lex;
	lex.NfaConvertToDfa();
	/*StatusSet s1({ 1,3,4,5,9 }), s2({ 1,4,5,3,8 });
	if (s1 == s2)cout << "yes";*/

}

void LexicalTest::test()
{
#if  LEXICAL_TEST==true
		  // checkDfa();
          //checkedge();
          //checkclosure();
	//checkDfaEdge();
	//checkConverTable();
	checkNfaConvertToDfa();

#endif;
}

void Test::test()
{
#if TEST==true
//	LexicalTest lexicalTest;
//	lexicalTest.test();
	FileTest file;
	file.test();

#endif

}

void FileTest::checkGetToken()
{
	File file("C:\\Users\\THINKPAD\\Desktop\\sql.txt");
	string str;
	////while (!(file.token.empty())) {
	////	str = file.token.front();
	////	file.token.pop();
	////	cout << str << endl;
	////}
	for (str = file.getToken(); str != EOF; str = file.getToken()) {
		cout << str << endl;
	}

}

void FileTest::test()
{
	checkGetToken();

}
