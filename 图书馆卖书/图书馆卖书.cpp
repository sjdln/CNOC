#include<iostream>
#include<cstdlib>
#include<string>
#include<ctime>
#include<fstream>
#include<ostream>
#include<istream>
#define MAX 10000

std::string intTostring(int n)
{
	std::string temp = "";
  while (n > 0) {
        temp = static_cast<char>((n % 10) + '0') + temp;
        n /= 10;
    }
    return temp;
}

struct books{//定义一个books类
public:
std::string num;  // 书号
std::string name; // 书名
std::string val ; // 价格 
std::string year; // 录入的年份 
std::string mon;  // 录入的月份 
std::string day;  // 录入的日期 
};

struct booksshop{// 定义一个存放书的结构
books book[MAX];
int size; 
	
};

 
void showmenu(){  //增 删 查 显示全部 退出； 
	std::cout << "----*************************----" << std::endl; 
	std::cout << "---******  1、新增图书  ******---" << std::endl;
	std::cout << "---******  2、显示图书  ******---" << std::endl; 
	std::cout << "---******  3、查找图书  ******---" << std::endl;
	std::cout << "---******  4、删除图书  ******---" << std::endl; 
	std::cout << "---******  5、清空图书  ******---" << std::endl; 
	std::cout << "---******  6、修改图书  ******---" << std::endl; 
	std::cout << "---******  7、保存图书  ******---" << std::endl;
	std::cout << "---******  其他退出图书 ******---" << std::endl; 
	std::cout << "----*************************----" << std::endl; 
}

int* booknameis_exist(std::string name, booksshop* bokp)
{
	int* res = new int[bokp->size];
	for(int i = 0; i < bokp->size;i++){
		res[i] = -1; 
	}
	int add = 0;
	for(int i = 0; i < bokp->size; i++ ){
		if(name == bokp->book[i].name){
			res[add] = i;
			add++;
		}
	}
	return res;
}

void addbooks(booksshop* bokp)
{
	if(bokp->size == MAX - 1 ){
		std::cout << "当前可输入的书架已满！！！" << std::endl;
		return;
	}
	std::time_t currentTime = std::time(NULL);
	std::tm*localTime = std::localtime(&currentTime);
	std::cout << "请输入书号： " << std::endl;
	std::cin >> bokp->book[bokp->size].num; 
	std::cout << "请输入书名： " << std::endl;
	std::cin >> bokp->book[bokp->size].name;
	std::cout << "请输入价格： " << std::endl;
	std::cin >> bokp->book[bokp->size].val;
	bokp->book[bokp->size].year = intTostring(localTime -> tm_year + 1900);
	bokp->book[bokp->size].mon = intTostring(localTime -> tm_mon + 1);
	bokp->book[bokp->size].day = intTostring(localTime -> tm_mday);
	bokp->size++;
 } 
 
 void showbooks(booksshop* bokp)
 {
 	for(int i = 0;i < bokp->size;i++){
	 
 		// 书号 
		std::cout << "书号为： " << bokp->book[i].num << "\t"; 
		// 书名
		std::cout << "书名为： " << bokp->book[i].name << std::endl; 
		// 价格
		std::cout << "价格为： " << bokp->book[i].val << "\t";
		// 录入日期 
		std::cout << "录入日期为： " << bokp->book[i].year << "年 " << bokp->book[i].mon << "月 "
		<< bokp->book[i].day << "日" << 
		std::endl;
		std::cout << "-----------------------------------------------" <<std::endl;
	}
	
 }
 
void findbooks(booksshop* bokp)
{
	std::string name;
	std::cout << "输入您想查找的书名： "; 
	std::cin >> name;
	int* ret = new int[bokp->size];
	for(int i = 0; i < bokp->size;i++){
		ret[i] = -1; 
	}
	ret = booknameis_exist(name, bokp);
	int yes = 0;  // 用于判断书是否存在 
	for(int i = 0;i < bokp->size; i++){
		if(ret[i] != -1){
			yes = 1;
	 		// 书号 
			std::cout << "书号为： " << bokp->book[ret[i]].num << "\t"; 
			// 书名
			std::cout << "书名为： " << bokp->book[ret[i]].name << std::endl; 
			// 价格
			std::cout << "价格为： " << bokp->book[ret[i]].val << "\t";
			// 录入日期 
			std::cout << "录入日期为： " << bokp->book[ret[i]].year << "年 " << bokp->book[i].mon << "月 "
			<< bokp->book[i].day << "日" << 
			std::endl;
			std::cout << "-----------------------------------------------" <<std::endl;
		}
	}
	if(!yes)
	{

	std::cout << "查无此书！！正在返回主菜单"  << std::endl;
	}
	delete[] ret;
	return;
} 
 
int isExist(booksshop* bokp, std::string name) {
    for (int i = 0; i < bokp->size; i++) {
        // 找到了
        if (bokp->book[i].name == name) {
            return i;
        }
    }
    // 没找着
    return -1;
}
 
void modifybook(booksshop* bokp)
{
	std::string name;
	std::cout << "请输入要修改的书本名： " << std::endl;
	std::cin >> name; 
	int ret = isExist(bokp, name);
	if(ret != -1){
		 		// 书号 
			std::cout << "书号为： " << bokp->book[ret].num << "\t"; 
			// 书名
			std::cout << "书名为： " << bokp->book[ret].name << std::endl; 
			// 价格
			std::cout << "价格为： " << bokp->book[ret].val << "\t";
			// 录入日期 
			std::cout << "录入日期为： " << bokp->book[ret].year << "年 " << bokp->book[ret].mon << "月 "
			<< bokp->book[ret].day << "日" << 
			std::endl;
			std::cout << "-----------------------------------------------" <<std::endl;
			std::cout << "请确认是否为您想修改的书的内容\\(-v-)/" << "\n输入“确定”进入下一步，否则返回主菜单"<< std::endl; 
			std::string right;
			if(right == "确定"){
				
			std::time_t currentTime = std::time(NULL);
			std::tm*localTime = std::localtime(&currentTime);
			std::cout << "请输入书号： " << std::endl;
			std::cin >> bokp->book[ret].num; 
			std::cout << "请输入书名： " << std::endl;
			std::cin >> bokp->book[ret].name;
			std::cout << "请输入价格： " << std::endl;
			std::cin >> bokp->book[bokp->size].val;
			bokp->book[ret].year = intTostring(localTime -> tm_year + 1900);
			bokp->book[ret].mon = intTostring(localTime -> tm_mon + 1);
			bokp->book[ret].day = intTostring(localTime -> tm_mday);
			}
			else{
				return;
			}
		}
		else
		{
			std::cout << "未找到该书！！！！" << std::endl;
		}
	
}
 
 void saveBooksshop(booksshop* bokp) {
    std::ofstream outFile("booksdata.txt");
    if (!outFile.is_open()) {
        std::cout << "无法打开文件进行保存！" << std::endl;
        return;
    }
    outFile << bokp->size << std::endl;
    for (int i = 0; i < bokp->size; ++i) {
        outFile << bokp->book[i].num << " " 
                << bokp->book[i].name << " " 
                << bokp->book[i].val << " " 
                << bokp->book[i].year << " " 
                << bokp->book[i].mon << " " 
                << bokp->book[i].day << std::endl;
    std::cout << "已保存《 " << bokp->book[i].name << " 》的数据" << std::endl; 
    }
    outFile.close();
    std::cout << "图书数据已成功保存！" << std::endl;
}
 
 void loadBooksshop(booksshop* bokp) {
    std::ifstream inFile("booksdata.txt");
    if (!inFile.is_open()) {
        std::cout << "无法打开文件进行读取！" << std::endl;
        return;
    }
    int bookCount;
    inFile >> bookCount;
    bokp->size = bookCount;
    for (int i = 0; i < bookCount; ++i) {
        inFile >> bokp->book[i].num 
               >> bokp->book[i].name 
               >> bokp->book[i].val 
               >> bokp->book[i].year 
               >> bokp->book[i].mon 
               >> bokp->book[i].day;
    std::cout << "已读取《 " << bokp->book[i].name << " 》的数据" << std::endl; 
    }
    inFile.close();
    std::cout << "图书数据已成功读取！" << std::endl;
    system("pause");
    system("cls");
}
 
void to_select(booksshop* bokp,std::string N)
{
	int n = atoi(N.c_str());
	
	switch(n){
		case 1:  // 增加图书 
		addbooks(bokp); 
			break;
		case 2:  // 显示所有图书 
		showbooks(bokp);
			break;
		case 3:  // 查找图书
		findbooks(bokp); 
			break;
		case 4:  // 删除图书 
		{
		std::cout << "输入要删除的书名： ";
		std::string name;
		std::cin >> name;
		int* ret1 = new int[bokp->size];
		for(int i = 0; i < bokp->size;i++){
		ret1[i] = -1; 
		}
		ret1 = booknameis_exist(name, bokp);
			int yes1 = 0;  // 用于判断书是否存在 
		for(int i = 0;i < bokp->size; i++){
			if(ret1[i] != -1){
				yes1 = 1;
				for(int j = ret1[i];j < bokp->size;j++){
					bokp->book[j] = bokp->book[j+1];
					bokp->size--;
	
				}
			std::cout << "已删除 " << i + 1 << " 本书的数据" << std::endl;; 
		}
	}
	if(!yes1)
	{

	std::cout << "查无此书！！正在返回主菜单"  << std::endl;
	}
	delete[] ret1;
}
			break;
		case 5:  // 清空图书 
		bokp->size = 0;
		std::cout << "已清空所有图书！！！！！" << std::cout;
			break;
		case 6:  // 修改图书 
		modifybook(bokp);
			break;
		case 7:  // 保存图书 
		saveBooksshop(bokp);
			break; 
		default:
			return; 
	}
}

int main(){
	
	booksshop bokp;
	bokp.size = 0;
	std::string n;//选项用于跳转 
	loadBooksshop(&bokp);
	while(1){
		showmenu();
		std::cin >> n;
		int temp = atoi(n.c_str());
		if(temp > 7 || temp < 1){
			std::cout << "即将退出程序！！！！" << std::endl; 
			for(int i = 0;i < 4;i++){
				std::cout << "即将启动保存程序！！！！！！" << std::endl;
			}
			system("pause");
			system("cls");
			break;
		}
		to_select(&bokp, n);
		system("pause");
		system("cls");
	} 
	saveBooksshop(&bokp);
	return 0;
} 
