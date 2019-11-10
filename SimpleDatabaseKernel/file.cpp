
#include"file.h"

File::File(string filename){
	setFileName(filename);
}

inline bool File::setFileName(string filename)
{
	ifstream input(filename);
	if (!input) {
		cerr << "文件不存在，路径错误或者文件已被删除！";
		return false;
	}
	this->filename = filename;
	if (!readFile())return false;
	return true;

}

bool File::setFileName(char * filename)
{
	char ch;
	string temp;
	for (ch = *filename; ch; ch = *(++filename))
		temp += ch;
	return setFileName(temp);
}

string File::getToken()
{
	string str;
	if (token.empty()||!flag)return EOF;//队列为空，返回EOF
	str = token.front();
	token.pop();
	return str;
}

string File::getFile()
{
	return filename;
}

bool File::readFile()
{
	FilePtr file = freopen(filename.c_str(), "r", stdin);
	string str;
	if (file == NULL) {
		cerr << "文件打开失败！" << endl;
		flag = false;
		return false;
	}
	else {
		while (!feof(file)&& cin >> str) {//读取文件，放入队列
			token.push(str);

		}
		fclose(file);
	}
	flag = true;
	return true;
}


