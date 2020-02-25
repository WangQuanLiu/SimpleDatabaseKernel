
#include"file.h"
using namespace file;
#define GRAM_CREATE_POSI 79
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
/*

���ܣ���ȡ���ŵĴ�С
*/
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
/*
����:void
���ܣ��ع�һ����Ԫ��token������
�����void

*/
void file::File::roll_back()
{
	if (lineFeed) {
		list<string>temp;
		temp.push_back(rellback);
		token.push_front(temp);
		curLine--;
		return;
	}
	else {
		list<list<string>>::iterator iter = token.begin();
		iter->push_front(rellback);
	}
}
/*
���룺void
���ܣ���token�����л�ȡһ����Ԫ��С��ֵ,����tokenɾ����������
�����string
*/
string file::File::get_token()
{
	string str;
	if (token.empty() || !flag)return ENTER;//����Ϊ�գ�����EOF
	rellback = "";
	if (((token.front()).size() <= 0)||
		((token.front()).size() <= 1 && (token.front().front() == ""))) {
		token.pop_front();
		curLine++;
		lineFeed = true;
		return "";
	}
	/*else if ((token.front()).size() <= 1 && (token.front().front() == "")) {
		token.pop_front();
		curLine++;
		return "";
	}*/
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
	rellback = str;
	lineFeed = false;
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
/*
���룺void
���ܣ���ȡ�ļ��е����ݵ�token�����У��ļ���ȡ�ɹ�����true��ʧ�ܷ���false
���:bool
*/
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
						if ((i + 1<str.length())&&
							(str[i] == '<' || (str[i] == '>'&&str[i+1]!='>'))&&
							(str[i+1]=='>'||str[i+1]=='=')) {
							temp.clear();
							temp.push_back(str[i]); 
							temp.push_back(str[i+1]);
							ls.push_back(temp);
							lastIndex = i + 2;
							i++;
						}
						else {
							temp = str[i];	//���������
							ls.push_back(temp);
							lastIndex = i + 1;
						}
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



/*
���룺void
���ܣ���ȡ�ļ��е����ݵ�token�����У��ļ���ȡ�ɹ�����true��ʧ�ܷ���false
���:bool
*/
bool GrammaticalAnalysisFile::read_file()
{
	fstream file(filename, ios::in);
	string str, temp;

	int i,lastLeftBracket=0,lastRightBracket=0,lastIndex=0;
	list<string>ls;//������ʱ�б�
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
					if(str[i]!=' ')
					temp = temp + str[i];
					if (str[i] == ' '||i==str.size()-1) {
						if (i - lastIndex != 0) {		
							temp=string_map_to_gram(temp);
							ls.push_back(temp);	
							lastIndex = i;
						}	
						temp = "";
						continue;
					}
					

				}
			}
			else {
				ls.push_back(string(""));
			}
			
			token.push_back(ls);//����һ�����ݵ�token��
		}
		
	}


	return true;
}



bool GrammaticalAnalysisFile::set_file_path(string fileName)
{
	return File::set_file_path(fileName) && read_file();
}



/*
���룺һ�����ַ�������(�ķ���ؼ����ַ���)
���ܣ�ͨ�������ַ����õ��ķ�
���������õ�����ķ�
*/
	string file::GrammaticalAnalysisFile::string_map_to_gram(const string &str)
	{
		
		if (str == "l_bracket" || str == "r_bracket" || str == "comma" || str == "assignment_symbol")
			if (str == "assignment_symbol")
				return "e_equal";
			else
			return "e_" + str;
	string gramTemp, strTemp,temp="";
	int i,lastIndex=0;
	for (i = 0; i < str.size(); i++) {
		if (str[i] == '(') {
			gramTemp = str.substr(lastIndex, i - lastIndex);
			lastIndex = i + 1;
			temp.clear();
		}
		else if (str[i] == ')') {
			strTemp = str.substr(lastIndex, i - lastIndex);
			break;
		}
		else {
			temp = temp + str[i];
		}
	}
	/*
	�������Ƿ���ǣ�δ��ƺôʷ��������﷨�����Ľӿ�	
	*/
	symbol symbolTemp;
	string gram;
	try {
		
		for (i = 0; i < SYMBOL_SIZE; i++)
			if (gramTemp == symbolStringTable[i]) { 
				symbolTemp = static_cast<symbol>(i); break; }
		if (i >= SYMBOL_SIZE)
			throw "error";
	}
	catch(string&){
		cerr << " GrammaticalAnalysisFile class string_map_to_gram function  occur symbol error ";
		return "";
	}
	switch (symbolTemp)
	{
	case keyword:
		try {
			for (i = 0; i < KEYWORD_TABLE; i++) {
				if (keywordTable[i] == strTemp)
					break;
			}
			if (i >= KEYWORD_TABLE)throw "error";
		}
		catch (string&) {
			cerr << "GrammaticalAnalysisFile class string_map_to_gram function switch error" << endl;
		}
		gram ="e_"+ keywordTable[i];
			break;
	case num:
		gram = "e_integer";break;
	case real:
		gram = "e_real";break;
	case id:
		gram = "e_id";break;
	case add_sub_symbol:
		if (strTemp == "-")
			gram = "e_subop";
		else
			gram = "e_addop";
		break;
	case mul_symbol:
		gram = "e_mulop";break;
	case div_symbol:
		gram = "e_divop";break;
	case logical_symbol:
		if (strTemp == "and")
			gram = "e_and";
		else if (strTemp == "or")
			gram = "e_or";
		else
			gram = "e_not";
		break;
	case compare_symbol:
		if (strTemp == ">")
			gram = "e_greater_than";
		else if (strTemp == ">=")
			gram = "e_greater_than_or_equal";
		else if (strTemp == "<")
			gram = "e_less_than";
		else if (strTemp == "<=")
			gram = "e_less_than_or_equal";
		else
			gram = "e_unequal";
			break;
	case character:
		gram = "e_str"; break;
	case characterMatch:
		gram = "e_strMatch"; break;
	
	//case assignment_symbol:
	//	gram = "e_equal"; break;
	default:
		break;
	}

	return gram+" "+strTemp;
}
const string file::GrammaticalAnalysisFile::keywordTable[]{
	"and","or","sum","avg","count","min","max", //constriant															  //keyword
	"create","table","char","not","null","primary","key","foreign","references","check","in","unique", "like","where",
	"order","by","desc","asc","group","having","right","left","full","join","on","distance","from",
	"database","use","delete","alter","add","drop","column","insert","into","values","update","set",
	"view","as","index","int","float","select","natural",

};
const string file::GrammaticalAnalysisFile::symbolStringTable[SYMBOL_SIZE]{
	"keyword" , "num", "real", "id", "add_sub_symbol", "mul_symbol",
	"div_symbol", "logical_symbol", "compare_symbol", "character", "characterMatch",
	"l_bracket", "r_bracket", "comma", "assignment_symbol",
};
/*
���룺Ҫ����ɢ���ַ���
���ܣ����ַ�����ɢ������
�������ɢ֮�����������
*/
inline  int file::GrammaticalAnalysisFile::string_hash(const string &str)
{
	int sum = 0;
	int i;
	for (i = 0; i < str.size(); i++)
		sum = sum * 5 + str[i];
	return sum;
}


