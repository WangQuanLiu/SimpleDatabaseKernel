
#include"file.h"
using namespace file;
string File::get_program_dir()
{
	char exeFullPath[MAX_PATH]; // Full path 
	string strPath = "";

	GetModuleFileName(NULL, exeFullPath, MAX_PATH);
	strPath = (string)exeFullPath;    // Get full path of the file 

	int pos = strPath.find_last_of('\\', strPath.length());
	return strPath.substr(0, pos);  // Return the directory without the file name 
}

File::File(string filename):File(){
	set_file_path(filename);
}

unsigned long long File::get_token_size()
{
	return token.size();
}

inline bool File::set_file_path(string filename)
{
	ifstream input(filename);
	if (!input) {
		cerr << "�ļ������ڣ�·����������ļ��ѱ�ɾ����";
		return false;
	}
	this->filename = filename;
//	if (!read_file())return false;
	flag = true;
	return true;

}

inline bool File::set_file_path(char * filename)
{
	char ch;
	string temp;
	for (ch = *filename; ch; ch = *(++filename))
		temp += ch;
	return set_file_path(temp);
}

//string File::executeRellback()
//{
//	token.push_front(rellback);
//	return rellback;
//}
//
//string File::getRellback()
//{
//	return rellback;
//}

string LexicalAnalysisFile::get_token()
{
	string str;
	if (token.empty()||!flag)return ENTER;//����Ϊ�գ�����EOF
	if ((token.front()).size() <= 0) {
		token.pop_front();
		curLine++;
		return "";
	}
	else if ((token.front()).size() <= 1 && (token.front().front() == "")) {
		token.pop_front();
		curLine++;
		return "";
	}
	list<list<string>>::iterator begin;
	begin = token.begin();
	list<string>::iterator iter;
	iter = (*begin).begin();

	str = *iter;
	/*if ((token.front()).size() <= 1) {
		token.pop_front();
		curLine++;
		return str;
	}*/
	begin->pop_front();
	return str;
}

string File::get_file()
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
unsigned long long File::get_cur_line()
{
	return curLine;
}
string File::split_file_dir(string fullPath)
{
	string filePath = "";
	bool flag = true;
	for (int i = fullPath.length() - 1; i >= 0; i--) {
		filePath = fullPath[i] + filePath;
		if (fullPath[i] == 92 && flag) {
			filePath = "";
			flag = !flag;
		}
		//else if (fullPath[i] == 92)break;
	}
	return filePath;
}
string File::split_file_dir(char * fullPath)
{
	string filePath = "";
	int i;
	for (i = 0; fullPath[i] != '\0'; i++)
		filePath = fullPath[i];
	return split_file_dir(filePath);
}
string File::split_file_name(char * fullPath)
{
	string filePath="";
	int i;
	for (i = 0; fullPath[i] != '\0'; i++)
		filePath = fullPath[i];
	return split_file_name(filePath);
}

bool LexicalAnalysisFile::read_file()
{
	//FilePtr file = freopen(filename.c_str(), "r", stdin);
	
	fstream file(filename, ios::in);
	string str,temp;
	list<string>ls;//������ʱ�б�
	int i;
	
	int lastIndex;//��һ���±�
	if (!file) {
		cerr << "�ļ���ʧ�ܣ�" << endl;
		flag = false;
		return false;
	}
	else {
		char tempCharacter[FILE_LINE_MAX_NUMBER];
		list<string>saveList;
		while (!file.eof()) {	//�����ļ����ݵ�saveList
			file.getline(tempCharacter, FILE_LINE_MAX_NUMBER);
			saveList.push_back(tempCharacter);
		}
		while (!saveList.empty()) {//��ȡ�ļ����������
			str.clear();
			ls.clear();
			lastIndex = 0;//��Ϊ��
			str = saveList.front();//������
			saveList.pop_front();
			if (str != "") {	//��Ϊ�س�
				
				for (i = 0; i < str.length(); i++) {	//���Ϊ������������߼������
					if (str[i] == ',' || str[i] == '+' || str[i] == '-' || str[i] == '*' ||
						str[i] == '/' || str[i] == '<' || str[i] == '>' || str[i] == '=' ||
						str[i] == ')' || str[i] == '(' || str[i] == ' ') {
						if (lastIndex != i) {			//�ȱ����������������һ�������
							temp = str.substr(lastIndex, i - lastIndex);
							ls.push_back(temp);

						}
						temp = str[i];	//���������
						ls.push_back(temp);
						lastIndex = i + 1;
					}
					else if (str[i] == ' ') {
						temp = str.substr(lastIndex, i - lastIndex);
						ls.push_back(temp);
						lastIndex = i + 1;
					}
					/*else if (str[i] == 'd' || str[i] == 'r' || str[i] == 't') {

					}*/
				}

				if (lastIndex < str.length()) {		//����һ������
					temp = str.substr(lastIndex, str.length() - lastIndex);
					ls.push_back(temp);
				}
				token.push_back(ls);
				ls.clear();
			}
			else{
				ls.push_back("");
				token.push_back(ls);
			}
			
		}
		file.close();
	}
	flag = true;
	return true;
}



bool LexicalAnalysisFile::set_file_path(string fileName)
{
	return File::set_file_path(fileName) && read_file();
}

string GrammaticalAnalysisFile::get_token()
{
	return string();
}

bool GrammaticalAnalysisFile::read_file()
{
	fstream file(filename, ios::in);
	string str, temp;

	int i,lastLeftBracket=0,lastRightBracket=0,lastIndex=0;
	deque<GramToken>ls;//������ʱ�б�
	if (!file) {
		cerr << "�ļ���ʧ�ܣ�" << endl;
		flag = false;
		return false;
	}
	else {
		char tempCharacter[FILE_LINE_MAX_NUMBER];
		list<string>saveList;
		while (!file.eof()) { //���浽saveList
			file.getline(tempCharacter, FILE_LINE_MAX_NUMBER);
			saveList.push_back(tempCharacter);
		}
		file.close();
		while (!saveList.empty()) {
			ls.clear();
			str.clear();
			lastIndex=lastLeftBracket = lastRightBracket = 0;
			str = saveList.front();
			saveList.pop_front();
			if (str != "") {
				for (i = 0; i < str.size(); i++) {
					if (str[i] == '(') lastLeftBracket = i;
					else if (str[i] == ')') {
						//lastRightBracket = i;
						temp = str.substr(lastIndex, lastLeftBracket - lastIndex);
						GramToken gramTokenTemp;
						gramTokenTemp.setGram(temp);
						temp = str.substr(lastLeftBracket+1, i - lastLeftBracket);
						gramTokenTemp.setString(temp);
						ls.push_back(gramTokenTemp);
					}
					else if (str[i] == ' ')lastIndex = i+1;
				}
			}
			else {
				ls.push_back(GramToken(ENTER,ENTER));
				token.push_back(ls);
			}

			token.push_back(ls);
		}
		
	}


	return false;
}



bool GrammaticalAnalysisFile::set_file_path(string fileName)
{
	return File::set_file_path(fileName) && read_file();
}

file::GramTokenType::GramTokenType(const GramTokenType & obj)
{
	this->gram = obj.gram;
	this->string = obj.string;
}

void file::GramTokenType::setGram(const std::string & gram)
{
	this->gram = gram;
}

void file::GramTokenType::setString(const std::string & string)
{
	this->string = string;
}

std::string file::GramTokenType::getGram()
{
	return gram;
}

std::string file::GramTokenType::getString()
{
	return string;
}

 file::GramTokenType::GramTokenType(const std::string & gram, const std::string & string)
{
	setGram(gram);
	setString(string);
}

file::GramTokenType::GramTokenType(const char *chA, const char *chB)
{
	std::string tempA, tempB;
	while ((*chA != '\0') || (*chB != '\0')) {
		if (*chA != '\0') {
			tempA += *chA;
			chA++;
		}
		if (*chB != '\0') {
			tempB += *chB;
			chB++;
		}

	}
	setGram(gram);
	setString(string);
	GramTokenType(tempA, tempB);
}
