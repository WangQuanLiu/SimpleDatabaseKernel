
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
		cerr << "文件不存在，路径错误或者文件已被删除！";
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
输入:void
功能：回滚一个单元到token容器中
输出：void

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

//string LexicalAnalysisFile::get_token()
//{
//	string str;
//	if (token.empty()||!flag)return ENTER;//队列为空，返回EOF
//	if ((token.front()).size() <= 0) {
//		token.pop_front();
//		curLine++;
//		return "";
//	}
//	else if ((token.front()).size() <= 1 && (token.front().front() == "")) {
//		token.pop_front();
//		curLine++;
//		return "";
//	}
//	list<list<string>>::iterator begin;
//	begin = token.begin();
//	list<string>::iterator iter;
//	iter = (*begin).begin();
//
//	str = *iter;
//	/*if ((token.front()).size() <= 1) {
//		token.pop_front();
//		curLine++;
//		return str;
//	}*/
//	begin->pop_front();
//	return str;
//}
/*
输入：void
功能：在token容器中获取一个单元大小的值,并在token删除，并返回
输出：string
*/
string file::File::get_token()
{
	string str;
	if (token.empty() || !flag)return ENTER;//队列为空，返回EOF
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
输入：void
功能：读取文件中的内容到token容器中，文件读取成功返回true，失败返回false
输出:bool
*/
bool LexicalAnalysisFile::read_file()
{
	//FilePtr file = freopen(filename.c_str(), "r", stdin);
	
	fstream file(filename, ios::in);
	string str,temp;
	list<string>ls;//保存临时列表
	int i;
	
	int lastIndex;//上一个下标
	if (!file) {
		cerr << "文件打开失败！" << endl;
		flag = false;
		return false;
	}
	else {
		char tempCharacter[FILE_LINE_MAX_NUMBER];
		list<string>saveList;
		while (!file.eof()) {	//读出文件数据到saveList
			file.getline(tempCharacter, FILE_LINE_MAX_NUMBER);
			saveList.push_back(tempCharacter);
		}
		while (!saveList.empty()) {//读取文件，放入队列
			str.clear();
			ls.clear();
			lastIndex = 0;//置为零
			str = saveList.front();//出数据
			saveList.pop_front();
			if (str != "") {	//不为回车
				
				for (i = 0; i < str.length(); i++) {	//如果为操作运算符或逻辑运算符
					if (str[i] == ',' || str[i] == '+' || str[i] == '-' || str[i] == '*' ||
						str[i] == '/' || str[i] == '<' || str[i] == '>' || str[i] == '=' ||
						str[i] == ')' || str[i] == '(' || str[i] == ' ') {
						if (lastIndex != i) {			//先保存与运算符连接在一起的数据
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
							temp = str[i];	//保存运算符
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

				if (lastIndex < str.length()) {		//后面一截数据
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

//string GrammaticalAnalysisFile::get_token()
//{
//	return "";
//}

/*
输入：void
功能：读取文件中的内容到token容器中，文件读取成功返回true，失败返回false
输出:bool
*/
bool GrammaticalAnalysisFile::read_file()
{
	fstream file(filename, ios::in);
	string str, temp;

	int i,lastLeftBracket=0,lastRightBracket=0,lastIndex=0;
	list<string>ls;//保存临时列表
	if (!file) {
		cerr << "文件打开失败！" << endl;
		flag = false;
		return false;
	}
	else {
		char tempCharacter[FILE_LINE_MAX_NUMBER];
		list<string>saveList;
		while (!file.eof()) { //保存到saveList
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
					if (str[i] == ' ') {
						if (i - lastIndex != 0) {
							string_map_to_gram(temp);
							ls.push_back(temp);	
							lastIndex = i;
						}
						//ls.push_back(" ");
						temp = "";
					}
					temp = temp + str[i];
					/*if (str[i] == '(') lastLeftBracket = i;
					else if (str[i] == ')') {
						lastRightBracket = i;
						temp = str.substr(lastIndex, lastLeftBracket - lastIndex);
						string gramTokenTemp;
						gramTokenTemp=temp;
						temp = str.substr(lastLeftBracket+1, i - lastLeftBracket);
						gramTokenTemp.setString(temp);
						ls.push_back(gramTokenTemp);
					}
					else if (str[i] == ' ')lastIndex = i+1;*/

				}
			}
			else {
				ls.push_back(string(""));
				token.push_back(ls);
			}

			token.push_back(ls);//插入一行数据到token中
		}
		
	}


	return true;
}



bool GrammaticalAnalysisFile::set_file_path(string fileName)
{
	return File::set_file_path(fileName) && read_file();
}
/*
输入：一整块字符串包括(文法与关键字字符串)
功能：通过整场字符串得到文法
输出：输出得到后的文法
*/
inline	Gram file::GrammaticalAnalysisFile::string_map_to_gram(const string &str)
{
	string gram, strTemp,temp="";
	int i,lastIndex=0;
	for (i = 0; i < str.size(); i++) {
		if (str[i] == '(') {
			gram = str.substr(lastIndex, i - lastIndex);
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
	初期设计欠考虑，未设计好词法分析与语法分析的接口	
	*/
	symbol symbolTemp;
	try {
		
		for (i = 0; i < SYMBOL_SIZE; i++)
			if (gram == symbolStringTable[i]) { symbolTemp = static_cast<symbol>(i); break; }
		if (i >= SYMBOL_SIZE)
			throw "error";
	}
	catch(string&str){
		cerr << " GrammaticalAnalysisFile class string_map_to_gram function  occur symbol error ";
		return Gram();
	}
	switch (symbolTemp)
	{
	case keyword:
		/*for (i = 0; i < )*/
			break;
	case num:
	case real:
	case id:
	case add_sub_symbol:
	case mul_symbol:
	case div_symbol:
	case logical_symbol:
	case compare_symbol:
	case character:
	case characterMatch:
	case l_bracket:
	case r_bracket:
	case comma:
	case assignment_symbol:
	case blank:
	default:
		break;
	}

	return Gram();
}
const string file::GrammaticalAnalysisFile::keywordTable[KEYWORD_TABLE]{
	"and","or","sum","avg","count","min","max", //constriant															  //keyword
	"create","table","char","not","null","primary","key","foreign","references","check","in","unique", "like","where",
	"order","by","desc","asc","group","having","right","left","full","join","on","distance","from",
	"database","use","delete","alter","add","drop","column","insert","into","values","update","set",
	"view","as","index",

};
const string file::GrammaticalAnalysisFile::symbolStringTable[SYMBOL_SIZE]{
	"keyword" , "num", "real", "id", "add_sub_symbol", "mul_symbol",
	"div_symbol", "logical_symbol", "compare_symbol", "character", "characterMatch",
	"l_bracket", "r_bracket", "comma", "assignment_symbol", "blank"
};
/*
输入：要被离散的字符串
功能：把字符串离散成数字
输出：离散之后产生的数字
*/
inline  int file::GrammaticalAnalysisFile::string_hash(const string &str)
{
	int sum = 0;
	int i;
	for (i = 0; i < str.size(); i++)
		sum = sum * 5 + str[i];
	return sum;
}


