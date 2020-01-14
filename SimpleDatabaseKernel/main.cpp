/*

MIT License
Copyright (c) 2020 WangQuanLiu

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Project address :https://github.com/WangQuanLiu/SimpleDatabaseKernel
*/
#ifndef _LexicalAnalysis_
#include"LexicalAnalysis.h"
#ifndef _FILE_
#include"file.h"
#endif
#endif
#if TEST==true
#include"test.h"
#endif
#include"GrammaticalAnalysis.h"
using namespace std;
using namespace file;
class Compile { //主类，完成编译与实现任务，把词法分析、语法分析与后面的数据库联系起来
public :
	void run();
	void lexical_run(string Path);
	void grammatical_run(string Path);
	Compile(int argc,char*argv[]);
private:
	CFilePtr file;
};
bool check_input_file(int argc, char*argv[]) {
	
	if (argc != 3 ) {
		cerr<< "SimpleDatabaseKernel:未输入文件名或未输入编译命令" << endl;
		return false;
	}
	if (argv[1][0]!='-'||argv[1][1]!='c') {
		cerr << "SimpleDatabaseKernel:编译命令不正确" << endl;
		return false;
	}
	ifstream input(argv[2]);
	if (!input) {
		cerr << "SimpleDatabaseKernel:文件不存在，路径错误或者文件已被删除！"<<endl;
		return false;
	}
	return true;
}
void Compile::run()
{
	/*file = new LexicalAnalysisFile;*/
	lexical_run(file->get_file());
	grammatical_run("C:\\Users\\THINKPAD\\Desktop\\sql.lex");

}
void Compile::lexical_run(string filePath)
{
	LexicalAnalysis lex(filePath);
		lex.run();
	//	cout << "file.get_token() " << temp << endl;
	//	cout << "getRellback() " << file.getRellback() << endl;

}
void Compile::grammatical_run(string Path)
{
	GrammaticalAnalysis gram(Path);
	/*gra.test_first();
	gra.test();*/
}
Compile::Compile(int argc,char*argv[])
{
	string str = "C:\\Users\\THINKPAD\\Desktop\\sql.txt";
	file = new LexicalAnalysisFile(str);
		//file->set_file_path(argv[2]);
}
int main(int argc,char *argv[]) {
/*#if TEST==true
	Test test;
	test.test();
#endif*/ // TEST==TRUE	
	//if (!check_input_file(argc, argv))return -1;
//	if (!check_input_file(argc, argv))return 0;
	argv = (char**)malloc(sizeof(char *[3]));
	
	
	argv[2] = "C:\\Users\\THINKPAD\\Desktop\\sql.txt";
	cout << argv[2] << endl;
	Compile compile(argc, argv);
	compile.run();



	system("pause");
	return 0;
}