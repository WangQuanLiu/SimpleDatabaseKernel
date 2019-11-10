
#ifndef _LexicalAnalysis_
#include"LexicalAnalysis.h"
#ifndef _FILE_
#include"file.h"
#endif
#endif
#if TEST==true
#include"test.h"
#endif
using namespace std;

class Compile { //���࣬��ɱ�����ʵ�����񣬰Ѵʷ��������﷨�������������ݿ���ϵ����
public :
	void run(char* ch);
	void lexical(char*ch);
private:
	File file;
};
bool checkInputFile(int argc, char*argv[]) {
	
	if (argc != 3 ) {
		cerr<< "SimpleDatabaseKernel:δ�����ļ�����δ�����������" << endl;
		return false;
	}
	if (argv[1][0]!='-'||argv[1][1]!='c') {
		cerr << "SimpleDatabaseKernel:���������ȷ" << endl;
		return false;
	}
	ifstream input(argv[2]);
	if (!input) {
		cerr << "SimpleDatabaseKernel:�ļ������ڣ�·����������ļ��ѱ�ɾ����"<<endl;
		return false;
	}
	return true;
}
void Compile::run(char *ch)
{
	lexical(ch);


}
void Compile::lexical(char*ch)
{
	file.setFileName(ch);
	vector<string>str;
	/*for (string temp = file.getToken(); temp != EOF; temp = file.getToken())
		cout << temp << endl;*/


}
int main(int argc,char *argv[]) {
#if TEST==true
	Test test;
	test.test();
#endif // TEST==TRUE	
	if (!checkInputFile(argc, argv))return -1;
	Compile compile;
	compile.run(argv[2]);
	



	system("pause");
	return 0;
}