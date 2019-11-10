
#include"file.h"

File::File(string filename){
	setFileName(filename);
}

inline bool File::setFileName(string filename)
{
	ifstream input(filename);
	if (!input) {
		cerr << "�ļ������ڣ�·����������ļ��ѱ�ɾ����";
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
	if (token.empty()||!flag)return EOF;//����Ϊ�գ�����EOF
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
		cerr << "�ļ���ʧ�ܣ�" << endl;
		flag = false;
		return false;
	}
	else {
		while (!feof(file)&& cin >> str) {//��ȡ�ļ����������
			token.push(str);

		}
		fclose(file);
	}
	flag = true;
	return true;
}


