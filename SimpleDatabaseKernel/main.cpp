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

The project address :https://github.com/WangQuanLiu/SimpleDatabaseKernel
completed date:2020/1/19 11:38
create by WangQuanLiu
E-mail:wangquanliu@163.com

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

class Compile { //主类，完成编译与实现任务，把词法分析、语法分析与后面的数据库联系起来
public :
	void run();
	void lexical_run(string Path);
	void grammatical_run(string Path)noexcept;
	Compile(int argc,char*argv[]);
private:
	cfe::CFilePtr file;
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
	
	lexical_run(file->get_file());
	cout << "词法分析完成！" << endl;
	string str = file->get_file();
	str[str.size() - 3] = 'l';
	str[str.size() - 2] = 'e';
	str[str.size() - 1] = 'x';
	//cout << str << endl;
	grammatical_run(str);

}
void Compile::lexical_run(string filePath)
{
	cfe::LexicalAnalysis lex(filePath);
		lex.run();

}
void Compile::grammatical_run(string Path)noexcept
{
	cfe::GrammaticalAnalysis gram(Path);
	gram.run();
}
Compile::Compile(int argc,char*argv[])
{
	string str = argv[2];
	file = new cfe::LexicalAnalysisFile(str);
}
int main(int argc,char *argv[]) {
	argv = (char**)malloc(sizeof(char *[3]));
	argv[2] = "C:\\Users\\THINKPAD\\Desktop\\sql.txt";
	//cout << string(argv[0]) << endl;
	//cout << string(argv[1]) << endl;
	//cout << string(argv[2]) << endl;

	Compile compile(argc, argv);
	compile.run();

	system("pause");
	return 0;
}