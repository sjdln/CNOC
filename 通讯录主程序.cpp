#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include<istream>
#include<Windows.h>
#include<ctime>
#define MAX 1000  // 通讯录人数上限
int daysUntilBirthday(int birthYear, int birthMonth, int birthDay);
int daysBetweenDates(int year1, int mon1, int day1, int year2, int mon2, int day2);
//void jumpmainmenu();
struct person {
    std::string name;   // 姓名
    std::string sex;            // 性别 1、男 2、女
//    std::string age;    // 年龄 
    std::string year;   //出生年份
    std::string mon;    //出生月份
    std::string day;    //出生日期
    std::string phone;  // 电话号码
    std::string add;    // 地址
    std::string note;   //备注
};

struct Addressbooks {
    // 通讯录中保存的联系人数组
    struct person personArray[MAX];
    int size;
};

// 打印菜单
void showmenu() {
    std::cout << "注：本代码任何时候输入“主菜单”皆可返回主菜单" << std::endl;
    std::cout << "====***************************====" << std::endl;
    std::cout << "====*****  1、添加联系人  *****====" << std::endl;
    std::cout << "====*****  2、显示联系人  *****====" << std::endl;
    std::cout << "====*****  3、查询联系人  *****====" << std::endl;
    std::cout << "====*****  4、修改联系人  *****====" << std::endl;
    std::cout << "====*****  5、删除联系人  *****====" << std::endl;
    std::cout << "====*****  6、清空联系人  *****====" << std::endl;
    std::cout << "====*****  7、保存通讯录  *****====" << std::endl;
    //std::cout << "==*****  8、联系人生日  *****==" << std::endl;
    std::cout << "====*****  其他退出通讯录 *****====" << std::endl;
    std::cout << "====***************************====" << std::endl;

}

// 添加联系人
void addperson(Addressbooks* abs) {
    // 判断是否已满，已满不添加
    if (abs->size == MAX) {
        std::cout << "通讯录已满！无法添加！" << std::endl;
        return;
    }
    else {
        // 添加具体联系人
        // 姓名
        std::string name;
        nojump_addname:
        std::cout << "请输入姓名： " << std::endl;
        std::cin >> name;
        if (name == "主菜单") {

            std::cout << "即将返回主菜单！！！！" << std::endl;
            std::cout << "输入 “确认” 返回主菜单！！" << std::endl;
            std::string yesjumpmaimenu = "-6";
            std::cin >> yesjumpmaimenu;
            if (yesjumpmaimenu == "确认") {
                std::cout << "正在返回主菜单！！" << std::endl;
                return;
            }
            else {
                std::cout << "已取消返回主菜单操作请继续：  " << std::endl;
                goto nojump_addname;
            }

        }
        abs->personArray[abs->size].name = name;
        int temp_mon;
        // 性别
        std::string sex = "0";
        while (1) {               
            nojump_addsex:
            //std::cout << "乱输入就直接回到主菜单咯（-v-）~~" << std::endl;
            std::cout << "输入1 代表男性\t" << "输入2 代表女性" << std::endl;
            std::cout << "请输入性别： " << std::endl;
            int yes = 0;
            std::cin >> sex;
            if (sex == "主菜单") {

                std::cout << "即将返回主菜单！！！！" << std::endl;
                std::cout << "输入 “确认” 返回主菜单！！" << std::endl;
                std::string yesjumpmaimenu = "-6";
                std::cin >> yesjumpmaimenu;
                if (yesjumpmaimenu == "确认") {
                    std::cout << "正在返回主菜单！！" << std::endl;
                    return;
                }
                else {
                    std::cout << "已取消返回主菜单操作请继续：  " << std::endl;
                    goto nojump_addsex;
                }

            }
            // 正确输入停止循环
            if (sex == "1" || sex == "2") {
                abs->personArray[abs->size].sex = sex;
                break;
                yes = 1;
            }
            if (!yes) {
                std::cout << "（-v-）~~输入有误请重新输入： " << std::endl;
               // std::cout << "输入有误即将返回主菜单！" << endl;
               // return;
               // system("cls");
            }
        }
        // 年龄
        //std::string age = "0";
        //std::cout << "请输入年龄： " << std::endl;
        //    std::cin >> age;
        //    abs->personArray[abs->size].age = age;
        while (1) {
            std::string year = "0";   // 出生年份
            nojump_addyear:
            std::cout << "请输入出生年份(输入0为未知)： ";
            std::cin >> year;
            if (year == "主菜单") {

                std::cout << "即将返回主菜单！！！！" << std::endl;
                std::cout << "输入 “确认” 返回主菜单！！" << std::endl;
                std::string yesjumpmaimenu = "-6";
                std::cin >> yesjumpmaimenu;
                if (yesjumpmaimenu == "确认") {
                    std::cout << "正在返回主菜单！！" << std::endl;
                    return;
                }
                else {
                    std::cout << "已取消返回主菜单操作请继续：  " << std::endl;
                    goto nojump_addyear;
                }

            }
            int tempyear = std::stoi(year);
            if ((tempyear > 1800 && tempyear < 3000)||tempyear == 0) {   // 年份有效
                abs->personArray[abs->size].year = year;
                break;
            }
            else {
                std::cout << "输入有误请重新输入！！！" << std::endl;
                system("cls");
            }
        }
        while (1) {
            nojump_addmon:
            std::string mon = "0";   // 出生月份
            std::cout << "请输入出生月份(输入0为未知)： ";
            std::cin >> mon;
            if (mon == "主菜单") {

                std::cout << "即将返回主菜单！！！！" << std::endl;
                std::cout << "输入 “确认” 返回主菜单！！" << std::endl;
                std::string yesjumpmaimenu = "-6";
                std::cin >> yesjumpmaimenu;
                if (yesjumpmaimenu == "确认") {
                    std::cout << "正在返回主菜单！！" << std::endl;
                    return;
                }
                else {
                    std::cout << "已取消返回主菜单操作请继续：  " << std::endl;
                    goto nojump_addmon;
                }

            }
            int tempm = std::stoi(mon);
            if (tempm >= 0 && tempm <= 12) {   // 月份有效
                abs->personArray[abs->size].mon = mon;
                temp_mon = std::stoi(mon);
                break;
            }
            else {
                std::cout << "输入有误请重新输入！！！" << std::endl;
                system("pause");
                system("cls");
            }
        }
        while (1) {
            nojump_addday:
            std::string day = "0";   // 出生日期
            std::cout << "请输入出生日期(输入0为未知)： ";
            int tempy = std::stoi(abs->personArray[abs->size].year);
            std::cin >> day;
            if (day == "主菜单") {

                std::cout << "即将返回主菜单！！！！" << std::endl;
                std::cout << "输入 “确认” 返回主菜单！！" << std::endl;
                std::string yesjumpmaimenu = "-6";
                std::cin >> yesjumpmaimenu;
                if (yesjumpmaimenu == "确认") {
                    std::cout << "正在返回主菜单！！" << std::endl;
                    return;
                }
                else {
                    std::cout << "已取消返回主菜单操作请继续：  " << std::endl;
                    goto nojump_addday;
                }

            }
            int tempd = std::stoi(day);
            if (tempd >= 0 && tempd <= 31 &&( temp_mon == 1 || temp_mon == 3 || temp_mon == 5 || temp_mon == 7
                || temp_mon == 8 || temp_mon == 10 || temp_mon == 12||temp_mon == 0)) {   // 日期有效
                abs->personArray[abs->size].day = day;
                break;
            }
            else if (tempd >= 0 && tempd <= 29 && temp_mon == 2) {

                if (tempd == 29) {
                    if (tempy % 4 == 0 || tempy % 400 == 0) {
                        abs->personArray[abs->size].day = day;
                        break;
                    
                    }
                    else {
                        std::cout << "输入有误请重新输入！！！" << std::endl;
                        system("pause");
                        system("cls");
                    }
                }
                else {
                    abs->personArray[abs->size].day = day;
                    break;
                
                }
            }
            else if (tempd >= 0 && tempd <= 30 &&( temp_mon == 4
                || temp_mon == 6 || temp_mon == 9 || temp_mon == 11)) {
                abs->personArray[abs->size].day = day;
                break;
            }
            else if(tempd > 31 || tempd < 0 ) {
                std::cout << "输入有误请重新输入！！！" << std::endl;
                system("pause");
                system("cls");
            }else if(temp_mon == 2&&tempd > 29){
                std::cout << "输入有误请重新输入！！！" << std::endl;
                system("pause");
                system("cls");
            }
            else if (tempd < 0) {
                std::cout << "输入有误请重新输入！！！" << std::endl;
                system("pause");
                system("cls");
            }
        }
        // 电话号码
        nojump_addphone:
        std::cout << "请输入联系电话：" << std::endl;
        std::string phone;
        std::cin >> phone;
        if (phone == "主菜单") {

            std::cout << "即将返回主菜单！！！！" << std::endl;
            std::cout << "输入 “确认” 返回主菜单！！" << std::endl;
            std::string yesjumpmaimenu = "-6";
            std::cin >> yesjumpmaimenu;
            if (yesjumpmaimenu == "确认") {
                std::cout << "正在返回主菜单！！" << std::endl;
                return;
            }
            else {
                std::cout << "已取消返回主菜单操作请继续：  " << std::endl;
                goto nojump_addphone;
            }

        }
        abs->personArray[abs->size].phone = phone;
        // 地址
        nojump_addaddress:
        std::cout << "请输入家庭住址； " << std::endl;
        std::string address;
        std::cin >> address;
        if (address == "主菜单") {

            std::cout << "即将返回主菜单！！！！" << std::endl;
            std::cout << "输入 “确认” 返回主菜单！！" << std::endl;
            std::string yesjumpmaimenu = "-6";
            std::cin >> yesjumpmaimenu;
            if (yesjumpmaimenu == "确认") {
                std::cout << "正在返回主菜单！！" << std::endl;
                return;
            }
            else {
                std::cout << "已取消返回主菜单操作请继续：  " << std::endl;
                goto nojump_addaddress;
            }

        }
        abs->personArray[abs->size].add = address;

        //备注
        nojump_addnote:
        std::cout << "请输入联系人备注：" << std::endl;
        std::string note;
        std::cin >> note;
        if (note == "主菜单") {

            std::cout << "即将返回主菜单！！！！" << std::endl;
            std::cout << "输入 “确认” 返回主菜单！！" << std::endl;
            std::string yesjumpmaimenu = "-6";
            std::cin >> yesjumpmaimenu;
            if (yesjumpmaimenu == "确认") {
                std::cout << "正在返回主菜单！！" << std::endl;
                return;
            }
            else {
                std::cout << "已取消返回主菜单操作请继续：  " << std::endl;
                goto nojump_addnote;
            }

        }
        abs->personArray[abs->size].note = note;

        abs->size++;
        std::cout << "添加成功！！" << std::endl;
        //system("pause");  // 请按任意键继续
        //system("cls");    // 清屏
    }
}

void showPerson(Addressbooks* abs) {
    time_t currentTime;
    time(&currentTime);
    struct tm localTime;
    localtime_s(&localTime, &currentTime);
    // 如果通讯录为0  记录为空
    // 如果通讯录不为0  输出所有记录的联系人信息
    if (abs->size == 0) {
        std::cout << "暂无记录联系人！" << std::endl;
    }
    else {
        for (int i = 0; i < abs->size; i++) {
            int tempy = std::stoi(abs->personArray[i].year);   // 临时年
            int tempm = std::stoi(abs->personArray[i].mon);    // 临时月
            int tempd = std::stoi(abs->personArray[i].day);    // 临时日
            std::cout << "姓名： " << abs->personArray[i].name << "\t";
            std::cout << "性别： " << (abs->personArray[i].sex == "1" ? "男" : "女") << "\t";
            if (tempy != 0) {
                if (localTime.tm_mday - tempd >= 0 && localTime.tm_mon - tempm >= 0) {
                    std::cout << "年龄： " << localTime.tm_year - tempy + 1900 << std::endl;
                }
                else {
                    std::cout << "年龄： " << localTime.tm_year - tempy - 1 + 1900 << std::endl;
                }
            }
            else {
                std::cout << "年龄： 未知" << std::endl;
            }
            std::cout << "出生年月日：  ";
            if (tempy == 0) {
                std::cout << "未知  年 ";
            }
            else {
                std::cout << tempy << "年 ";
            }
            if (tempm == 0) {
                std::cout << "未知  月 ";
            }
            else {
                std::cout << tempm << "月 ";
            }
            if (tempd == 0) {
                std::cout << "未知  日" << '\t';
            }
            else {
                std::cout << tempd << "日" << '\t';
            }
            if (tempy == 0 || tempd == 0) {
                std::cout << "生日未知！快去问问朋友的生日吧！！" << std::endl;
            }
            else {
                // 计算距离生日的天数
                int days = daysUntilBirthday(tempy, tempm, tempd);

                // 输出结果
                std::cout << "距离他|她的生日还有 " << days << " 天。" << std::endl;

            }
            std::cout << "电话号码： " << abs->personArray[i].phone << "\t";
            std::cout << "家庭住址： " << abs->personArray[i].add << "\t";
            std::cout << "联系人备注：" << abs->personArray[i].note << "\n";
            //std::cout << "联系人备注：" << abs->personArray[i].note << std::endl;
            std::cout << "-------------------------------------------------------------" << std::endl;
        }
    }
    //system("pause");
    //system("cls");
}
// 检测联系人是否存在，如果存在返回联系人在数组的具体位置，不存在返回负一
int isExist(Addressbooks* abs, std::string name) {
    for (int i = 0; i < abs->size; i++) {
        // 找到了
        if (abs->personArray[i].name == name) {
            return i;
        }
    }
    // 没找着
    return -1;
}

// 计算两个日期之间的天数差
int daysBetweenDates(int year1, int mon1, int day1, int year2, int mon2, int day2) {
    struct std::tm tm1 = { 0 };
    tm1.tm_year = year1 - 1900;
    tm1.tm_mon = mon1 - 1;
    tm1.tm_mday = day1;
    std::time_t time1 = std::mktime(&tm1);

    struct std::tm tm2 = { 0 };
    tm2.tm_year = year2 - 1900;
    tm2.tm_mon = mon2 - 1;
    tm2.tm_mday = day2;
    std::time_t time2 = std::mktime(&tm2);

    // 计算秒数差并转换为天数
    return static_cast<int>(std::difftime(time2, time1) / (60 * 60 * 24));
}

// 计算距离生日还有多少天
int daysUntilBirthday(int birthyear, int birthmonth, int birthday) {
    // 获取当前日期
    time_t currentTime;
    time(&currentTime);
    struct tm localTime;
    localtime_s(&localTime, &currentTime);
    std::time_t now = std::time(nullptr);
    int currentYear = localTime.tm_year + 1900;
    int currentMonth = localTime.tm_mon + 1;
    int currentDay = localTime.tm_mday;

    // 计算今年的生日日期
    int thisYearBirthdayYear = currentYear;
    int thisYearBirthdayMonth = birthmonth;
    int thisYearBirthdayDay = birthday;

    // 判断今年的生日是否已经过去
    if ((currentMonth > birthmonth) || (currentMonth == birthmonth && currentDay > birthday)) {
        // 如果已经过去，则计算下一年的生日
        thisYearBirthdayYear++;
    }
    if (birthmonth == 2 && (birthyear % 4 == 0 || birthyear % 400 == 0)
        && birthday == 29 && (currentMonth > birthmonth)) {
        thisYearBirthdayYear += currentYear % 4 + 1;
    }
    // 计算距离生日的天数
    return daysBetweenDates(currentYear, currentMonth, currentDay, thisYearBirthdayYear, thisYearBirthdayMonth, thisYearBirthdayDay);
}

void findPerson(Addressbooks* abs) {
    nojump_findperson:
    std::cout << "请输入查询的联系人姓名： " << std::endl;
    std::string name;
    std::cin >> name;
    if (name == "主菜单") {

        std::cout << "即将返回主菜单！！！！" << std::endl;
        std::cout << "输入 “确认” 返回主菜单！！" << std::endl;
        std::string yesjumpmaimenu = "-6";
        std::cin >> yesjumpmaimenu;
        if (yesjumpmaimenu == "确认") {
            std::cout << "正在返回主菜单！！" << std::endl;
            return;
        }
        else {
            std::cout << "已取消返回主菜单操作请继续：  " << std::endl;
            goto nojump_findperson;
        }

    }
    int ret = isExist(abs, name);
    time_t currentTime;
    time(&currentTime);
    struct tm localTime;
    localtime_s(&localTime, &currentTime);
    if (ret != -1)  // 找到了
    {
        int tempy = std::stoi(abs->personArray[ret].year);
        int tempm = std::stoi(abs->personArray[ret].mon);
        int tempd = std::stoi(abs->personArray[ret].day);
        std::cout << "姓名； " << abs->personArray[ret].name << "\t";
        std::cout << "性别： " << (abs->personArray[ret].sex == "1" ? "男" : "女") << "\t";
        if (tempy != 0) {
            if (localTime.tm_mday - tempd >= 0 && localTime.tm_mon - tempm + 1 >= 0) {
                std::cout << "年龄： " << localTime.tm_year - tempy + 1900 << std::endl;
            }
            else {
                std::cout << "年龄： " << localTime.tm_year - tempy - 1 + 1900 << std::endl;
            }
        }
        else {
            std::cout << "年龄： 未知" << std::endl;
        }
        std::cout << "出生年月日：  ";
        if (tempy == 0) {
            std::cout << "未知  年 ";
        }
        else {
            std::cout << tempy << "年 ";
        }
        if (tempm == 0) {
            std::cout << "未知  月 ";
        }
        else {
            std::cout << tempm << "月 ";
        }
        if (tempd == 0) {
            std::cout << "未知  日      " ;
        }
        else {
            std::cout << tempd << "日      " ;
        }
        if (tempy == 0 || tempd == 0) {
            std::cout << "生日未知！快去问问朋友的生日吧！！" << std::endl;
        }
        else {
            // 计算距离生日的天数
            int days = daysUntilBirthday(tempy, tempm, tempd);

            // 输出结果
            std::cout << "距离他|她的生日还有 " << days << " 天。" << std::endl;

        }
        std::cout << "电话号码： " << abs->personArray[ret].phone << "  ";
        std::cout << "家庭住址： " << abs->personArray[ret].add << std::endl;
        std::cout << "联系人备注：" << abs->personArray[ret].note << std::endl;
        std::cout << "-------------------------------------------------------------" << std::endl;
    }
    else {
        std::cout << "通讯录中未查询到此人！" << std::endl;
    }
    // 按任意键清屏
    //system("pause");
    //system("cls");
}

void modifyPerson(Addressbooks* abs) {
    nojump_modifyperson:
    std::cout << "输入您要修改的联系人： " << std::endl;
    std::string name;
    std::cin >> name;
    if (name == "主菜单") {

        std::cout << "即将返回主菜单！！！！" << std::endl;
        std::cout << "输入 “确认” 返回主菜单！！" << std::endl;
        std::string yesjumpmaimenu = "-6";
        std::cin >> yesjumpmaimenu;
        if (yesjumpmaimenu == "确认") {
            std::cout << "正在返回主菜单！！" << std::endl;
            return;
        }
        else {
            std::cout << "已取消返回主菜单操作请继续：  " << std::endl;
            goto nojump_modifyperson;
        }

    }

    int ret = isExist(abs, name);
    if (ret != -1) {
        system("cls");
        std::cout << "注：本代码任何时候输入“主菜单”皆可返回主菜单" << std::endl;
        std::cout << "+++++{+ 已找到该联系人！+}+++++" << std::endl;
        std::cout << "!!!!-- 以下是可操作内容  --!!!!" << std::endl;
        std::cout << "==***************************==" << std::endl;
        std::cout << "==*****  1、联系人姓名  *****==" << std::endl;
        std::cout << "==*****  2、联系人性别  *****==" << std::endl;
        std::cout << "==*****  3、联系人年龄  *****==" << std::endl;
        std::cout << "==*****  4、联系人电话  *****==" << std::endl;
        std::cout << "==*****  5、联系人住址  *****==" << std::endl;
        std::cout << "==*****  6、联系人备注  *****==" << std::endl;
        std::cout << "==*****  7、想修改全部  *****==" << std::endl;
        std::cout << "==*****   其他退出修改  *****==" << std::endl;
        std::cout << "==***************************==" << std::endl;
        std::cout << "请输入您想修改的内容：";
        int select = 0;
        std::cin >> select;
        // 找到联系人
        int temp_mon;
        switch (select) {
            // 姓名
        case 1:
        {
            std::string name;
            nojump_modifyname:
            std::cout << "请输入修改后的姓名：" << std::endl;
            std::cin >> name;
            if (name == "主菜单") {

                std::cout << "即将返回主菜单！！！！" << std::endl;
                std::cout << "输入 “确认” 返回主菜单！！" << std::endl;
                std::string yesjumpmaimenu = "-6";
                std::cin >> yesjumpmaimenu;
                if (yesjumpmaimenu == "确认") {
                    std::cout << "正在返回主菜单！！" << std::endl;
                    return;
                }
                else {
                    std::cout << "已取消返回主菜单操作请继续：  " << std::endl;
                    goto nojump_modifyname;
                }

            }

            abs->personArray[ret].name = name;
        }
        break;
        // 性别
        case 2:
        {
            std::string sex = "0";
        while (1) {
            nojump_modifysex:
            //std::cout << "乱输入就直接回到主菜单咯（-v-）~~" << std::endl;
            std::cout << "输入1 代表男性\t" << "输入2 代表女性" << std::endl;
            std::cout << "请输入修改后的性别： " << std::endl;

                int yes = 0;
                std::cin >> sex;
                if (sex == "主菜单") {

                    std::cout << "即将返回主菜单！！！！" << std::endl;
                    std::cout << "输入 “确认” 返回主菜单！！" << std::endl;
                    std::string yesjumpmaimenu = "-6";
                    std::cin >> yesjumpmaimenu;
                    if (yesjumpmaimenu == "确认") {
                        std::cout << "正在返回主菜单！！" << std::endl;
                        return;
                    }
                    else {
                        std::cout << "已取消返回主菜单操作请继续：  " << std::endl;
                        goto nojump_modifysex;
                    }

                }

                // 正确输入停止循环
                if (sex == "1" || sex == "2") {
                    abs->personArray[abs->size].sex = sex;
                    break;
                    yes = 1;
                }
                if (!yes) {
                    std::cout << "（-v-）~~输入有误请重新输入： " << std::endl;
                    //std::cout << "输入有误即将返回主菜单！！" << endl;
                    //return;
                }
            }
        }
        break;
        // 年龄
        case 3:
            while (1) {
                std::string year = "0";   // 出生年份
                nojump_modifyyear:
                std::cout << "请输入出生年份(输入0为未知)： ";
                std::cin >> year;
                if (year == "主菜单") {

                    std::cout << "即将返回主菜单！！！！" << std::endl;
                    std::cout << "输入 “确认” 返回主菜单！！" << std::endl;
                    std::string yesjumpmaimenu = "-6";
                    std::cin >> yesjumpmaimenu;
                    if (yesjumpmaimenu == "确认") {
                        std::cout << "正在返回主菜单！！" << std::endl;
                        return;
                    }
                    else {
                        std::cout << "已取消返回主菜单操作请继续：  " << std::endl;
                        goto nojump_modifyyear;
                    }

                }
                int tempyear = std::stoi(year);
                if (tempyear > 1800 && tempyear < 3000) {   // 年份有效
                    abs->personArray[abs->size].year = year;
                    break;
                }
                else {
                    std::cout << "输入有误请重新输入！！！" << std::endl;
                    system("cls");
                }
            }
            while (1) {
                std::string mon = "0";   // 出生月份
                nojump_modifymon:
                std::cout << "请输入出生月份(输入0为未知)： ";
                std::cin >> mon;
                if (mon == "主菜单") {

                    std::cout << "即将返回主菜单！！！！" << std::endl;
                    std::cout << "输入 “确认” 返回主菜单！！" << std::endl;
                    std::string yesjumpmaimenu = "-6";
                    std::cin >> yesjumpmaimenu;
                    if (yesjumpmaimenu == "确认") {
                        std::cout << "正在返回主菜单！！" << std::endl;
                        return;
                    }
                    else {
                        std::cout << "已取消返回主菜单操作请继续：  " << std::endl;
                        goto nojump_modifymon;
                    }

                }

                int tempm = std::stoi(mon);
                if (tempm >= 0 && tempm <= 12) {   // 年份有效
                    abs->personArray[abs->size].mon = mon;
                    temp_mon = std::stoi(mon);
                    break;
                }
                else {
                    std::cout << "输入有误请重新输入！！！" << std::endl;
                    system("pause");
                    system("cls");
                }
            }
            while (1) {
                std::string day = "0";   // 出生日期
                nojump_modifday:
                std::cout << "请输入出生日期(输入0为未知)： ";
                int tempy = std::stoi(abs->personArray[abs->size].year);
                std::cin >> day;
                if (day == "主菜单") {

                    std::cout << "即将返回主菜单！！！！" << std::endl;
                    std::cout << "输入 “确认” 返回主菜单！！" << std::endl;
                    std::string yesjumpmaimenu = "-6";
                    std::cin >> yesjumpmaimenu;
                    if (yesjumpmaimenu == "确认") {
                        std::cout << "正在返回主菜单！！" << std::endl;
                        return;
                    }
                    else {
                        std::cout << "已取消返回主菜单操作请继续：  " << std::endl;
                        goto nojump_modifday;
                    }

                }

                int tempd = std::stoi(day);
                if (tempd >= 0 && tempd <= 31 && (temp_mon == 1 || temp_mon == 3 || temp_mon == 5 || temp_mon == 7
                    || temp_mon == 8 || temp_mon == 10 || temp_mon == 12)) {   // 日期有效
                    abs->personArray[abs->size].day = day;
                    break;
                }
                else if (tempd >= 0 && tempd <= 29 && temp_mon == 2) {

                    if (tempd == 29) {
                        if (tempy % 4 == 0 || tempy % 400 == 0) {
                            abs->personArray[abs->size].day = day;
                            break;

                        }
                        else {
                            std::cout << "输入有误请重新输入！！！" << std::endl;
                            system("pause");
                            system("cls");
                        }
                    }
                    else {
                        abs->personArray[abs->size].day = day;
                        break;

                    }
                }
                else if (tempd >= 0 && tempd <= 30 && (temp_mon == 4
                    || temp_mon == 6 || temp_mon == 9 || temp_mon == 11)) {
                    abs->personArray[abs->size].day = day;
                    break;
                }
                else if (tempd > 31 || tempd < 0) {
                    std::cout << "输入有误请重新输入！！！" << std::endl;
                    system("pause");
                    system("cls");
                }
                else if (temp_mon == 2 && tempd > 29) {
                    std::cout << "输入有误请重新输入！！！" << std::endl;
                    system("pause");
                    system("cls");
                }
                else if (tempd < 0) {
                    std::cout << "输入有误请重新输入！！！" << std::endl;
                    system("pause");
                    system("cls");
                }
            }
        break;
        // 电话
        case 4:
        {
            std::string phone;
            nojump_modifyphone:
            std::cout << "请输入修改后的联系电话：" << std::endl;

            std::cin >> phone;

            if (phone == "主菜单") {

                std::cout << "即将返回主菜单！！！！" << std::endl;
                std::cout << "输入 “确认” 返回主菜单！！" << std::endl;
                std::string yesjumpmaimenu = "-6";
                std::cin >> yesjumpmaimenu;
                if (yesjumpmaimenu == "确认") {
                    std::cout << "正在返回主菜单！！" << std::endl;
                    return;
                }
                else {
                    std::cout << "已取消返回主菜单操作请继续：  " << std::endl;
                    goto nojump_modifyphone;
                }

            }

            abs->personArray[ret].phone = phone;
        }
        break;
        // 住址
        case 5:
        {
            std::string address;
            std::cout << "请输入修改后的家庭住址； " << std::endl;
            nojump_modifyaddress:
            std::cin >> address;

            if (address == "主菜单") {

                std::cout << "即将返回主菜单！！！！" << std::endl;
                std::cout << "输入 “确认” 返回主菜单！！" << std::endl;
                std::string yesjumpmaimenu = "-6";
                std::cin >> yesjumpmaimenu;
                if (yesjumpmaimenu == "确认") {
                    std::cout << "正在返回主菜单！！" << std::endl;
                    return;
                }
                else {
                    std::cout << "已取消返回主菜单操作请继续：  " << std::endl;
                    goto nojump_modifyaddress;
                }

            }

            abs->personArray[ret].add = address;
        }
        break;
        case 6:
        {
            //备注
            std::string note;
            nojump_modifynote:
            std::cout << "请输入修改后的联系人备注：" << std::endl;

            std::cin >> note;

            if (note == "主菜单") {

                std::cout << "即将返回主菜单！！！！" << std::endl;
                std::cout << "输入 “确认” 返回主菜单！！" << std::endl;
                std::string yesjumpmaimenu = "-6";
                std::cin >> yesjumpmaimenu;
                if (yesjumpmaimenu == "确认") {
                    std::cout << "正在返回主菜单！！" << std::endl;
                    return;
                }
                else {
                    std::cout << "已取消返回主菜单操作请继续：  " << std::endl;
                    goto nojump_modifynote;
                }

            }

            abs->personArray[ret].note = note;
        }
        break;
        // 全部
        case 7:
        {
            // 姓名
            std::string name;
            nojump_allmodifyname:
            std::cout << "请输入修改后的姓名： " << std::endl;
            std::cin >> name;

            if (name == "主菜单") {

                std::cout << "即将返回主菜单！！！！" << std::endl;
                std::cout << "输入 “确认” 返回主菜单！！" << std::endl;
                std::string yesjumpmaimenu = "-6";
                std::cin >> yesjumpmaimenu;
                if (yesjumpmaimenu == "确认") {
                    std::cout << "正在返回主菜单！！" << std::endl;
                    return;
                }
                else {
                    std::cout << "已取消返回主菜单操作请继续：  " << std::endl;
                    goto nojump_allmodifyname;
                }

            }

            abs->personArray[ret].name = name;
            // 性别
            std::string sex = "0";
            nojump_allmodifysex:
            std::cout << "乱输入就直接回到主菜单咯（-v-）~~" << std::endl;
            std::cout << "输入1 代表男性\t" << "输入2 代表女性" << std::endl;
            std::cout << "请输入修改后的性别： " << std::endl;
            //while (1) {
            int yes = 0;
            std::cin >> sex;

            if (sex == "主菜单") {

                std::cout << "即将返回主菜单！！！！" << std::endl;
                std::cout << "输入 “确认” 返回主菜单！！" << std::endl;
                std::string yesjumpmaimenu = "-6";
                std::cin >> yesjumpmaimenu;
                if (yesjumpmaimenu == "确认") {
                    std::cout << "正在返回主菜单！！" << std::endl;
                    return;
                }
                else {
                    std::cout << "已取消返回主菜单操作请继续：  " << std::endl;
                    goto nojump_allmodifysex;
                }

            }

            // 正确输入停止循环
            if (sex == "1" || sex == "2") {
                abs->personArray[abs->size].sex = sex;
                //    break;
                yes = 1;
            }
            if (!yes) {
                std::cout << "输入有误请重新输入： " << std::endl;
                std::cout << "即将回到主菜单！！！" << std::endl;
                system("pause");
                return;
            }
            //// 年龄
            //std::string age = "0";
            //std::cout << "请输入修改后的年龄： " << std::endl;
            //std::cin >> age;
            //abs->personArray[ret].age = age;
            while (1) {
                std::string year = "0";   // 出生年份
                nojump_allmodifyyear:
                std::cout << "请输入出生年份(输入0为未知)： ";
                std::cin >> year;

                if (year == "主菜单") {

                    std::cout << "即将返回主菜单！！！！" << std::endl;
                    std::cout << "输入 “确认” 返回主菜单！！" << std::endl;
                    std::string yesjumpmaimenu = "-6";
                    std::cin >> yesjumpmaimenu;
                    if (yesjumpmaimenu == "确认") {
                        std::cout << "正在返回主菜单！！" << std::endl;
                        return;
                    }
                    else {
                        std::cout << "已取消返回主菜单操作请继续：  " << std::endl;
                        goto nojump_allmodifyyear;
                    }

                }

                if (year > "1800" && year < "3000") {   // 年份有效
                    abs->personArray[abs->size].year = year;
                    break;
                }
                else {
                    std::cout << "输入有误请重新输入！！！" << std::endl;
                    system("cls");
                }
            }
            while (1) {
                std::string mon = "0";   // 出生月份
                nojump_allmodifymon:
                std::cout << "请输入出生月份(输入0为未知)： ";
                std::cin >> mon;

                if (mon == "主菜单") {

                    std::cout << "即将返回主菜单！！！！" << std::endl;
                    std::cout << "输入 “确认” 返回主菜单！！" << std::endl;
                    std::string yesjumpmaimenu = "-6";
                    std::cin >> yesjumpmaimenu;
                    if (yesjumpmaimenu == "确认") {
                        std::cout << "正在返回主菜单！！" << std::endl;
                        return;
                    }
                    else {
                        std::cout << "已取消返回主菜单操作请继续：  " << std::endl;
                        goto nojump_allmodifymon;
                    }

                }

                int tempm = std::stoi(mon);
                if (tempm >= 0 && tempm <= 12) {   // 年份有效
                    abs->personArray[abs->size].mon = mon;
                    temp_mon = std::stoi(mon);
                    break;
                }
                else {
                    std::cout << "输入有误请重新输入！！！" << std::endl;
                    system("pause");
                    system("cls");
                }
            }
            while (1) {
                std::string day = "0";   // 出生日期
                nojump_allmodifyday:
                std::cout << "请输入出生日期(输入0为未知)： ";
                int tempy = std::stoi(abs->personArray[abs->size].year);
                std::cin >> day;

                if (day == "主菜单") {

                    std::cout << "即将返回主菜单！！！！" << std::endl;
                    std::cout << "输入 “确认” 返回主菜单！！" << std::endl;
                    std::string yesjumpmaimenu = "-6";
                    std::cin >> yesjumpmaimenu;
                    if (yesjumpmaimenu == "确认") {
                        std::cout << "正在返回主菜单！！" << std::endl;
                        return;
                    }
                    else {
                        std::cout << "已取消返回主菜单操作请继续：  " << std::endl;
                        goto nojump_allmodifyday;
                    }

                }

                int tempd = std::stoi(day);
                if (tempd >= 0 && tempd <= 31 && (temp_mon == 1 || temp_mon == 3 || temp_mon == 5 || temp_mon == 7
                    || temp_mon == 8 || temp_mon == 10 || temp_mon == 12)) {   // 日期有效
                    abs->personArray[abs->size].day = day;
                    break;
                }
                else if (tempd >= 0 && tempd <= 29 && temp_mon == 2) {

                    if (tempd == 29) {
                        if (tempy % 4 == 0 || tempy % 400 == 0) {
                            abs->personArray[abs->size].day = day;
                            break;

                        }
                        else {
                            std::cout << "输入有误请重新输入！！！" << std::endl;
                            system("pause");
                            system("cls");
                        }
                    }
                    else {
                        abs->personArray[abs->size].day = day;
                        break;

                    }
                }
                else if (tempd >= 0 && tempd <= 30 && (temp_mon == 4
                    || temp_mon == 6 || temp_mon == 9 || temp_mon == 11)) {
                    abs->personArray[abs->size].day = day;
                    break;
                }
                else if (tempd > 31 || tempd < 0) {
                    std::cout << "输入有误请重新输入！！！" << std::endl;
                    system("pause");
                    system("cls");
                }
                else if (temp_mon == 2 && tempd > 29) {
                    std::cout << "输入有误请重新输入！！！" << std::endl;
                    system("pause");
                    system("cls");
                }
                else if (tempd < 0) {
                    std::cout << "输入有误请重新输入！！！" << std::endl;
                    system("pause");
                    system("cls");
                }
            }
            // 电话号码
            std::string phone;
            nojump_allmodifyphone:
            std::cout << "请输入修改后的联系电话：" << std::endl;

            std::cin >> phone;

            if (phone == "主菜单") {

                std::cout << "即将返回主菜单！！！！" << std::endl;
                std::cout << "输入 “确认” 返回主菜单！！" << std::endl;
                std::string yesjumpmaimenu = "-6";
                std::cin >> yesjumpmaimenu;
                if (yesjumpmaimenu == "确认") {
                    std::cout << "正在返回主菜单！！" << std::endl;
                    return;
                }
                else {
                    std::cout << "已取消返回主菜单操作请继续：  " << std::endl;
                    goto nojump_allmodifyphone;
                }

            }

            abs->personArray[ret].phone = phone;
            // 地址           
            std::string address;
            nojump_allmodifyaddress:
            std::cout << "请输入修改后的家庭住址； " << std::endl;
 
            std::cin >> address;

            if (address == "主菜单") {

                std::cout << "即将返回主菜单！！！！" << std::endl;
                std::cout << "输入 “确认” 返回主菜单！！" << std::endl;
                std::string yesjumpmaimenu = "-6";
                std::cin >> yesjumpmaimenu;
                if (yesjumpmaimenu == "确认") {
                    std::cout << "正在返回主菜单！！" << std::endl;
                    return;
                }
                else {
                    std::cout << "已取消返回主菜单操作请继续：  " << std::endl;
                    goto nojump_allmodifyaddress;
                }

            }

            // 备注
            std::string note;
            nojump_allmodifynote:
            std::cout << "请输入修改后的联系人备注" << std::endl;
            std::cin >> note;

            if (note == "主菜单") {

                std::cout << "即将返回主菜单！！！！" << std::endl;
                std::cout << "输入 “确认” 返回主菜单！！" << std::endl;
                std::string yesjumpmaimenu = "-6";
                std::cin >> yesjumpmaimenu;
                if (yesjumpmaimenu == "确认") {
                    std::cout << "正在返回主菜单！！" << std::endl;
                    return;
                }
                else {
                    std::cout << "已取消返回主菜单操作请继续：  " << std::endl;
                    goto nojump_allmodifynote;
                }

            }

        }
        break;
        // 退出
        default:
        {
            std::cout << "已退出修改联系人！" << std::endl;
            //system("pause");
            //system("cls");
            return;
            break;
        }
        }
        //system("pause");
        //system("cls");    // 清屏
    }
    else {
        // 未找到联系人
        std::cout << "查无此人！！" << std::endl;
        //system("pause");
        return;
    }
    std::cout << "已修改完成！" << std::endl;
}
void saveaddressbooks(Addressbooks* abs)  // 保存通讯录
{
    while (1) {
        std::cout << "注意！！！！" << std::endl;//输出警告
        std::cout << "此操作会覆盖上次保存的通讯录\n建议您再检查一遍" << std::endl;
        std::cout << "如果确认完毕，请输入“确认”以覆盖上次保存内容" << std::endl;
        std::cout << "不想保存，请输入“取消“以取消保存" << std::endl;
        std::string right = "0";
        std::cin >> right;

        if (right == "确认") {
            std::ofstream fout("C:\\通讯录数据.txt", std::ios::out);
            for (int i = 0; i < abs->size; i++) {
                fout << "姓名:" << abs->personArray[i].name << "\t";
                fout << "性别:" << (abs->personArray[i].sex == "1" ? "男" : "女") << "\t";
                fout << "出生年月日:" << abs->personArray[i].year  << "\t"
                     << "月:" << abs->personArray[i].mon << "\t"
                     << "日:" << abs->personArray[i].day << "\t";
                fout << "电话号码:" << abs->personArray[i].phone << "\n";
                fout << "家庭住址:" << abs->personArray[i].add << std::endl;
                fout << "联系人备注:" << abs->personArray[i].note << std::endl;
                //fout << "-------------------------------------------------------------" << std::endl;
                std::cout << "已保存 “" << abs->personArray[i].name << "” 的数据！！" << std::endl;
            }
            std::cout << "保存成功！！" << std::endl;
            fout.close();
            return;
        }
        else if(right == "取消"){
            std::cout << "已取消保存" << std::endl;
            return;
        }
        else {
            //system("cls");

            std::cout << "输入有误请检查输入内容是否正确" << std::endl;
            std::cout << "请输入“确认”或者“取消”！！！!" << std::endl;
        }

        system("cls");
    }
}
void to_select(int n, Addressbooks* abs) {
    switch (n) {
    // 0:  // 退出通讯录
    //    for (int o = 10;o > 0;o--)std::cout << "\\( * - v - * )/ 欢 迎 下 次 使 用 ！ ！ !" << std::endl;
    //    break;
    case 1:  // 添加联系人
        addperson(abs);
        break;
    case 2:  // 显示联系人
        showPerson(abs);
        break;
    case 3:  // 查询联系人
        findPerson(abs);
        break;
    case 4:  // 修改联系人
        modifyPerson(abs);
        break;
    case 5:  // 删除联系人
    {
        std::string name;

        nojump_deleteperson:
        std::cout << "请输入删除联系人的姓名： " << std::endl;
         std::cin >> name;
        if (name == "主菜单") {

            std::cout << "即将返回主菜单！！！！" << std::endl;
            std::cout << "输入 “确认” 返回主菜单！！" << std::endl;
            std::string yesjumpmaimenu = "-6";
            std::cin >> yesjumpmaimenu;
            if (yesjumpmaimenu == "确认") {
                std::cout << "正在返回主菜单！！" << std::endl;
                return;
            }
            else {
                std::cout << "已取消返回主菜单操作请继续：  " << std::endl;
                goto nojump_deleteperson;
            }

        }

        int ret = isExist(abs, name);
        // 判断联系人是否存在
        if (ret == -1) {
            std::cout << "查无此人！！" << std::endl;
        }
        else {
            std::string right = "否";
            nojump_rightdeleteperson:
            std::cout << "找到此人！" << std::endl;
            std::cout << "输入“确定”删除此人" << std::endl;
    
            std::cin >> right;
            if (right == "主菜单") {

                std::cout << "即将返回主菜单！！！！" << std::endl;
                std::cout << "输入 “确认” 返回主菜单！！" << std::endl;
                std::string yesjumpmaimenu = "-6";
                std::cin >> yesjumpmaimenu;
                if (yesjumpmaimenu == "确认") {
                    std::cout << "正在返回主菜单！！" << std::endl;
                    return;
                }
                else {
                    std::cout << "已取消返回主菜单操作请继续：  " << std::endl;
                    goto nojump_rightdeleteperson;
                }

            }

            if (right == "确定") {
                for (int i = ret; i < abs->size; i++) {
                    abs->personArray[i] = abs->personArray[i + 1];
                }
                std::cout << "删除成功！" << std::endl;
                abs->size--;
            }

        }
     //   system("pause");
     //   system("cls");
    }
    break;
    case 6:  // 清空联系人
    {
        std::string right;
        std::cout << "输入其他返回主菜单" << std::endl;
        std::cout << "请输入“确定”继续" << std::endl;
        std::cin >> right;
        if (right == "确定") {
            std::cout << "这真的很危险，请输入“确定”清空" << std::endl;
            std::cin >> right;
            if (right == "确定") {
                abs->size = 0;
                std::cout << "清空完毕！！！！！" << std::endl;
            //    system("pause");
            //    system("cls");
            }
            else {
                break;
            }
        }
        else {
            break;
        }
    }
    break;
    case 7:  // 保存通讯录
        saveaddressbooks(abs);
    break;
    default: break;
    }
}

// 读取通讯录数据函数
void readAddressbooks(Addressbooks* abs) {
    std::string filename = R"(C:\\通讯录数据.txt)";
    std::string part;
    std::ifstream fin;
    fin.open(filename, std::ios::in);
    if (fin.is_open())
    {
        fin.seekg(std::ios::beg);
        while (std::getline(fin, part, ':') && abs->size < MAX)
        {
            person temp;// 初始化 temp
            // 1、读取姓名
            std::getline(fin, part, '\t');
            temp.name = part;
            // 2、读取性别
            std::getline(fin, part, ':');
            std::getline(fin, part, '\t');
            if (part == "男") {
                temp.sex = "1";
            }
            else {
                temp.sex = "2";
            }
            // 3、读取年龄
            std::getline(fin, part, ':');
            std::getline(fin, part, '\t');
            temp.year = part;
            std::getline(fin, part, ':');
            std::getline(fin, part, '\t');
            temp.mon = part;
            std::getline(fin, part, ':');
            std::getline(fin, part, '\t');
            temp.day = part;
            // 4、读取电话
            std::getline(fin, part, ':');
            std::getline(fin, part, '\n');
            temp.phone = part;
            // 5、读取住址
            std::getline(fin, part, ':');
            std::getline(fin, part, '\n');
            temp.add = part;
            // 6、读取备注
            std::getline(fin, part, ':');
            std::getline(fin, part, '\n');
            temp.note = part;
            abs->personArray[abs->size] = temp;
            std::cout << "已读取 " << temp.name << " 的数据" << std::endl;
            abs->size++;
            //std::getline(fin,part);
        }
    }
    else {
        std::cout << "未检测到已保存通讯录" << std::endl;
        std::cout << "请 至 少 保 存 一 次 ！" << std::endl;
        system("pause");
        return;
    }
    std::cout << "读取上次保存的通讯录 成功！！！" << std::endl;
    std::cout << "C:\\通讯录数据.txt" << std::endl;
    system("pause");

}
void UpdateLog()
{
	system("cls");
	std::cout << "更新日志" << std::endl;
	std::cout << "版本号：V2.0" << std::endl;
	std::cout << "更新时间：2021年5月20日" << std::endl;
	std::cout << "更新内容：" << std::endl;
	std::cout << "1.优化了输入年份时为 “0” 会输入不了的bug" << std::endl;
	std::cout << "(其实是因为我少写了一个判断条件)" << std::endl;
	std::cout << "2.增加了更新日志功能" << std::endl;
	system("pause");
}

int main() {
    
    //for (int ii = 0;ii < 8;ii++) {
        std::cout << "由于不会更改保存目录所以默认保存在C盘哦uwu~" << std::endl;
        std::cout << "麻烦自己现在C盘创建一个名字叫 “通讯录数据” 的txt文件" << std::endl;
    //}
    system("pause");
    system("cls");
    for (int ii = 0;ii < 5;ii++) {
        std::cout << std::endl << "本程序由冉神-春霁柟提供 \\（ * V * ） / \t" << "我个人感觉挺好用哦！！" << std::endl;
    }
    std::cout << "程 序 加 载 中 . . . . . ." << std::endl;
    system("pause");
    system("cls");
    std::string select = "-6";  // 用户输入的变量
    // 创建通讯录
    Addressbooks abs;
    // 初始化人员个数
    abs.size = 0;
    while (1) {
        time_t currentTime;
        time(&currentTime);
        struct tm   localTime;
        localtime_s(&localTime, &currentTime);
        std::string yesread = "0";
        std::cout << "已打开通讯录程序" << "\n" << "请问是否下载上次保存的通讯录\n" << "是 请按 “1” 否 请按“2”" << std::endl;
        std::cin >> yesread;
        if (yesread == "1") {
            readAddressbooks(&abs);
            break;
        }
        else if (yesread == "2") {
            std::cout << "取消下载通讯录数据！" << std::endl;
            system("pause");
            break;
        }
        else {
            std::cout << "您的输入有误" << std::endl;
            system("pause");
            system("cls");
        }
    }
    system("cls");
    while (1) {
    mainmenu:// 主菜单FLAG
        showmenu();
        std::cin >> select;
        try {

            int temps = std::stoi(select);
            if (temps < 1 || temps > 7) break;
            //        for (int ii = 0;ii < 5;ii++) {
            //            std::cout << endl << "本程序由冉神-春霁柟提供 \\（ * V * ） / \t" << "我个人感觉挺好用哦！！" << std::endl;
            //        }
            //            std::cout << "正 在 载 入 下 一 步 . . . . . . " << endl;
            to_select(temps, &abs);
        }
        catch (const std::invalid_argument& e) {
            break;
        }
        system("pause");
        system("cls");
    }
    system("cls");
    for (int aa = 0; aa < 5;aa++) {
        std::cout << "——————即将自动保存！！！——( ! U ! )" << std::endl;
    }
    saveaddressbooks(&abs);
    while (1) {
        std::cout << "输入 “确定” 关闭程序——————输入 “取消” 返回主菜单\n输入 “更新” 查看更新日志\\(*V*)/" << std::endl;

        std::string yesoff;
        std::cin >> yesoff;
        if (yesoff == "确定") {
            std::cout << "正在退出通讯录" << std::endl;
            system("pause");
            system("cls");
            break;
        }
        else if (yesoff == "取消") {
            std::cout << "正在返回主菜单！！！" << std::endl;
            system("pause");
            system("cls");
            goto mainmenu;
        }
        else if (yesoff == "更新") {
            UpdateLog();
        }
    }
    for (int o = 10;o > 0;o--) {
        std::cout << "\\( * - v - * )/ 欢 迎 下 次 使 用 ！ ！ !" << std::endl;
        Sleep(50);
        std::cout << std::endl;

    }
    system("pause");
    return 0;
}