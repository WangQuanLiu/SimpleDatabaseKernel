#include"test.h"
void LexicalTest::check_dfa()//²é¿´DFA
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
void LexicalTest::check_edge()
{
	char c;
	while(cin>>c&&c!='#')
	LexicalAnalysis::edge(0, c);
}

void LexicalTest::check_closure()
{
	cout << "check closure:" << endl;
	int s;
	while (cin >> s &&s!=0&&s<NFA_ROW_MAX) {
		vector<int>temp(LexicalAnalysis::closure(s));
		cout << "it has status item as follow:" << endl;
		print<int>(temp);
	}
}

void LexicalTest::check_dfa_edge()
{

	cout << "check dfa_edge:" << endl;
	char  ch;
	int input;
	vector<int>vec;
	do {
		cout << "ÊäÈë×´Ì¬¼¯ -1½áÊø" << endl;
		while (cin >> input && input != -1)
			vec.push_back(input);
		cout << "ÊäÈë×Ö·û" << endl;
		cin >> ch;
		vec = LexicalAnalysis::dfa_edge(vec, ch);
		print<int>(vec);
		vec.clear();
		cout << "#½áÊøÑ­»·" << endl;

	} while (cin>>ch&&ch != '#');

}

void LexicalTest::check_conver_table()
{
	ConverTable con;
	int status, val;
	char ch;
	while (cout << "ÊäÈë×´Ì¬ºÅ£¬×Ö·ûÓëÖµ ÊäÈë×´Ì¬ºÅÎª-1½áÊø"<<endl&&cin >> status >> ch
		>> val&&status!=-1) {
		con.add_map(status, ch, val);
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
		int index(letter_convert_to_index(LexicalAnalysis::alphabet, ALPH_MAX, ch));
		cout << con.status[con.mapStatus[status]][index] << endl;
	}

}

void LexicalTest::check_nfa_conver_to_dfa()
{
	LexicalAnalysis lex;
	lex.nfa_Convert_to_dfa();
	/*StatusSet s1({ 1,3,4,5,9 }), s2({ 1,4,5,3,8 });
	if (s1 == s2)cout << "yes";*/

}

void LexicalTest::test()
{
#if  LEXICAL_TEST==true
		  // check_dfa();
          //check_edge();
          //check_closure();
	//check_dfa_edge();
	//check_conver_table();
	check_nfa_conver_to_dfa();

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

void FileTest::check_get_token()
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
	check_get_token();

}
