
#include"file.h"

string File::GetProgramDir()
{
	char exeFullPath[MAX_PATH]; // Full path 
	string strPath = "";

	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	strPath = (string)exeFullPath;    // Get full path of the file 

	int pos = strPath.find_last_of('\\', strPath.length());
	return strPath.substr(0, pos);  // Return the directory without the file name 
}

File::File(string filename):File(){
	set_file_name(filename);
}

inline bool File::set_file_name(string filename)
{
	ifstream input(filename);
	if (!input) {
		cerr << "�ļ������ڣ�·����������ļ��ѱ�ɾ����";
		return false;
	}
	this->filename = filename;
	if (!read_file())return false;
	flag = true;
	return true;

}

bool File::set_file_name(char * filename)
{
	char ch;
	string temp;
	for (ch = *filename; ch; ch = *(++filename))
		temp += ch;
	return set_file_name(temp);
}

string File::executeRellback()
{
	token.push_front(rellback);
	return rellback;
}

string File::getRellback()
{
	return rellback;
}

string File::getToken()
{
	string str;
	if (token.empty()||!flag)return EOF;//����Ϊ�գ�����EOF
	rellback=str = token.front();
	token.pop_front();
	return str;
}

string File::getFile()
{
	return filename;
}

string File::split_file_name(string fullPath)
{
	string fileName = "";
	for (int i = fullPath.length() - 1; i >= 0; i--) {

		fileName = fullPath[i] + fileName;
		if (fullPath[i] == '.') {
			fileName = "";
		}
		else if (fullPath[i] == 92)break;
	}

	return fileName;
}

string File::split_file_name(char * fullPath)
{
	string filePath="";
	int i;
	for (i = 0; fullPath[i] != '\0'; i++)
		filePath = fullPath[i];
	return split_file_name(filePath);
}

bool File::read_file()
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
			token.push_back(str);
		}
		fclose(file);
	}
	flag = true;
	return true;
}


