#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include<istream>
#include<Windows.h>
#include<ctime>
#define MAX 1000  // ͨѶ¼��������
int daysUntilBirthday(int birthYear, int birthMonth, int birthDay);
int daysBetweenDates(int year1, int mon1, int day1, int year2, int mon2, int day2);
//void jumpmainmenu();
struct person {
    std::string name;   // ����
    std::string sex;            // �Ա� 1���� 2��Ů
//    std::string age;    // ���� 
    std::string year;   //�������
    std::string mon;    //�����·�
    std::string day;    //��������
    std::string phone;  // �绰����
    std::string add;    // ��ַ
    std::string note;   //��ע
};

struct Addressbooks {
    // ͨѶ¼�б������ϵ������
    struct person personArray[MAX];
    int size;
};

// ��ӡ�˵�
void showmenu() {
    std::cout << "ע���������κ�ʱ�����롰���˵����Կɷ������˵�" << std::endl;
    std::cout << "====***************************====" << std::endl;
    std::cout << "====*****  1�������ϵ��  *****====" << std::endl;
    std::cout << "====*****  2����ʾ��ϵ��  *****====" << std::endl;
    std::cout << "====*****  3����ѯ��ϵ��  *****====" << std::endl;
    std::cout << "====*****  4���޸���ϵ��  *****====" << std::endl;
    std::cout << "====*****  5��ɾ����ϵ��  *****====" << std::endl;
    std::cout << "====*****  6�������ϵ��  *****====" << std::endl;
    std::cout << "====*****  7������ͨѶ¼  *****====" << std::endl;
    //std::cout << "==*****  8����ϵ������  *****==" << std::endl;
    std::cout << "====*****  �����˳�ͨѶ¼ *****====" << std::endl;
    std::cout << "====***************************====" << std::endl;

}

// �����ϵ��
void addperson(Addressbooks* abs) {
    // �ж��Ƿ����������������
    if (abs->size == MAX) {
        std::cout << "ͨѶ¼�������޷���ӣ�" << std::endl;
        return;
    }
    else {
        // ��Ӿ�����ϵ��
        // ����
        std::string name;
        nojump_addname:
        std::cout << "������������ " << std::endl;
        std::cin >> name;
        if (name == "���˵�") {

            std::cout << "�����������˵���������" << std::endl;
            std::cout << "���� ��ȷ�ϡ� �������˵�����" << std::endl;
            std::string yesjumpmaimenu = "-6";
            std::cin >> yesjumpmaimenu;
            if (yesjumpmaimenu == "ȷ��") {
                std::cout << "���ڷ������˵�����" << std::endl;
                return;
            }
            else {
                std::cout << "��ȡ���������˵������������  " << std::endl;
                goto nojump_addname;
            }

        }
        abs->personArray[abs->size].name = name;
        int temp_mon;
        // �Ա�
        std::string sex = "0";
        while (1) {               
            nojump_addsex:
            //std::cout << "�������ֱ�ӻص����˵�����-v-��~~" << std::endl;
            std::cout << "����1 ��������\t" << "����2 ����Ů��" << std::endl;
            std::cout << "�������Ա� " << std::endl;
            int yes = 0;
            std::cin >> sex;
            if (sex == "���˵�") {

                std::cout << "�����������˵���������" << std::endl;
                std::cout << "���� ��ȷ�ϡ� �������˵�����" << std::endl;
                std::string yesjumpmaimenu = "-6";
                std::cin >> yesjumpmaimenu;
                if (yesjumpmaimenu == "ȷ��") {
                    std::cout << "���ڷ������˵�����" << std::endl;
                    return;
                }
                else {
                    std::cout << "��ȡ���������˵������������  " << std::endl;
                    goto nojump_addsex;
                }

            }
            // ��ȷ����ֹͣѭ��
            if (sex == "1" || sex == "2") {
                abs->personArray[abs->size].sex = sex;
                break;
                yes = 1;
            }
            if (!yes) {
                std::cout << "��-v-��~~�����������������룺 " << std::endl;
               // std::cout << "�������󼴽��������˵���" << endl;
               // return;
               // system("cls");
            }
        }
        // ����
        //std::string age = "0";
        //std::cout << "���������䣺 " << std::endl;
        //    std::cin >> age;
        //    abs->personArray[abs->size].age = age;
        while (1) {
            std::string year = "0";   // �������
            nojump_addyear:
            std::cout << "������������(����0Ϊδ֪)�� ";
            std::cin >> year;
            if (year == "���˵�") {

                std::cout << "�����������˵���������" << std::endl;
                std::cout << "���� ��ȷ�ϡ� �������˵�����" << std::endl;
                std::string yesjumpmaimenu = "-6";
                std::cin >> yesjumpmaimenu;
                if (yesjumpmaimenu == "ȷ��") {
                    std::cout << "���ڷ������˵�����" << std::endl;
                    return;
                }
                else {
                    std::cout << "��ȡ���������˵������������  " << std::endl;
                    goto nojump_addyear;
                }

            }
            int tempyear = std::stoi(year);
            if ((tempyear > 1800 && tempyear < 3000)||tempyear == 0) {   // �����Ч
                abs->personArray[abs->size].year = year;
                break;
            }
            else {
                std::cout << "�����������������룡����" << std::endl;
                system("cls");
            }
        }
        while (1) {
            nojump_addmon:
            std::string mon = "0";   // �����·�
            std::cout << "����������·�(����0Ϊδ֪)�� ";
            std::cin >> mon;
            if (mon == "���˵�") {

                std::cout << "�����������˵���������" << std::endl;
                std::cout << "���� ��ȷ�ϡ� �������˵�����" << std::endl;
                std::string yesjumpmaimenu = "-6";
                std::cin >> yesjumpmaimenu;
                if (yesjumpmaimenu == "ȷ��") {
                    std::cout << "���ڷ������˵�����" << std::endl;
                    return;
                }
                else {
                    std::cout << "��ȡ���������˵������������  " << std::endl;
                    goto nojump_addmon;
                }

            }
            int tempm = std::stoi(mon);
            if (tempm >= 0 && tempm <= 12) {   // �·���Ч
                abs->personArray[abs->size].mon = mon;
                temp_mon = std::stoi(mon);
                break;
            }
            else {
                std::cout << "�����������������룡����" << std::endl;
                system("pause");
                system("cls");
            }
        }
        while (1) {
            nojump_addday:
            std::string day = "0";   // ��������
            std::cout << "�������������(����0Ϊδ֪)�� ";
            int tempy = std::stoi(abs->personArray[abs->size].year);
            std::cin >> day;
            if (day == "���˵�") {

                std::cout << "�����������˵���������" << std::endl;
                std::cout << "���� ��ȷ�ϡ� �������˵�����" << std::endl;
                std::string yesjumpmaimenu = "-6";
                std::cin >> yesjumpmaimenu;
                if (yesjumpmaimenu == "ȷ��") {
                    std::cout << "���ڷ������˵�����" << std::endl;
                    return;
                }
                else {
                    std::cout << "��ȡ���������˵������������  " << std::endl;
                    goto nojump_addday;
                }

            }
            int tempd = std::stoi(day);
            if (tempd >= 0 && tempd <= 31 &&( temp_mon == 1 || temp_mon == 3 || temp_mon == 5 || temp_mon == 7
                || temp_mon == 8 || temp_mon == 10 || temp_mon == 12||temp_mon == 0)) {   // ������Ч
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
                        std::cout << "�����������������룡����" << std::endl;
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
                std::cout << "�����������������룡����" << std::endl;
                system("pause");
                system("cls");
            }else if(temp_mon == 2&&tempd > 29){
                std::cout << "�����������������룡����" << std::endl;
                system("pause");
                system("cls");
            }
            else if (tempd < 0) {
                std::cout << "�����������������룡����" << std::endl;
                system("pause");
                system("cls");
            }
        }
        // �绰����
        nojump_addphone:
        std::cout << "��������ϵ�绰��" << std::endl;
        std::string phone;
        std::cin >> phone;
        if (phone == "���˵�") {

            std::cout << "�����������˵���������" << std::endl;
            std::cout << "���� ��ȷ�ϡ� �������˵�����" << std::endl;
            std::string yesjumpmaimenu = "-6";
            std::cin >> yesjumpmaimenu;
            if (yesjumpmaimenu == "ȷ��") {
                std::cout << "���ڷ������˵�����" << std::endl;
                return;
            }
            else {
                std::cout << "��ȡ���������˵������������  " << std::endl;
                goto nojump_addphone;
            }

        }
        abs->personArray[abs->size].phone = phone;
        // ��ַ
        nojump_addaddress:
        std::cout << "�������ͥסַ�� " << std::endl;
        std::string address;
        std::cin >> address;
        if (address == "���˵�") {

            std::cout << "�����������˵���������" << std::endl;
            std::cout << "���� ��ȷ�ϡ� �������˵�����" << std::endl;
            std::string yesjumpmaimenu = "-6";
            std::cin >> yesjumpmaimenu;
            if (yesjumpmaimenu == "ȷ��") {
                std::cout << "���ڷ������˵�����" << std::endl;
                return;
            }
            else {
                std::cout << "��ȡ���������˵������������  " << std::endl;
                goto nojump_addaddress;
            }

        }
        abs->personArray[abs->size].add = address;

        //��ע
        nojump_addnote:
        std::cout << "��������ϵ�˱�ע��" << std::endl;
        std::string note;
        std::cin >> note;
        if (note == "���˵�") {

            std::cout << "�����������˵���������" << std::endl;
            std::cout << "���� ��ȷ�ϡ� �������˵�����" << std::endl;
            std::string yesjumpmaimenu = "-6";
            std::cin >> yesjumpmaimenu;
            if (yesjumpmaimenu == "ȷ��") {
                std::cout << "���ڷ������˵�����" << std::endl;
                return;
            }
            else {
                std::cout << "��ȡ���������˵������������  " << std::endl;
                goto nojump_addnote;
            }

        }
        abs->personArray[abs->size].note = note;

        abs->size++;
        std::cout << "��ӳɹ�����" << std::endl;
        //system("pause");  // �밴���������
        //system("cls");    // ����
    }
}

void showPerson(Addressbooks* abs) {
    time_t currentTime;
    time(&currentTime);
    struct tm localTime;
    localtime_s(&localTime, &currentTime);
    // ���ͨѶ¼Ϊ0  ��¼Ϊ��
    // ���ͨѶ¼��Ϊ0  ������м�¼����ϵ����Ϣ
    if (abs->size == 0) {
        std::cout << "���޼�¼��ϵ�ˣ�" << std::endl;
    }
    else {
        for (int i = 0; i < abs->size; i++) {
            int tempy = std::stoi(abs->personArray[i].year);   // ��ʱ��
            int tempm = std::stoi(abs->personArray[i].mon);    // ��ʱ��
            int tempd = std::stoi(abs->personArray[i].day);    // ��ʱ��
            std::cout << "������ " << abs->personArray[i].name << "\t";
            std::cout << "�Ա� " << (abs->personArray[i].sex == "1" ? "��" : "Ů") << "\t";
            if (tempy != 0) {
                if (localTime.tm_mday - tempd >= 0 && localTime.tm_mon - tempm >= 0) {
                    std::cout << "���䣺 " << localTime.tm_year - tempy + 1900 << std::endl;
                }
                else {
                    std::cout << "���䣺 " << localTime.tm_year - tempy - 1 + 1900 << std::endl;
                }
            }
            else {
                std::cout << "���䣺 δ֪" << std::endl;
            }
            std::cout << "���������գ�  ";
            if (tempy == 0) {
                std::cout << "δ֪  �� ";
            }
            else {
                std::cout << tempy << "�� ";
            }
            if (tempm == 0) {
                std::cout << "δ֪  �� ";
            }
            else {
                std::cout << tempm << "�� ";
            }
            if (tempd == 0) {
                std::cout << "δ֪  ��" << '\t';
            }
            else {
                std::cout << tempd << "��" << '\t';
            }
            if (tempy == 0 || tempd == 0) {
                std::cout << "����δ֪����ȥ�������ѵ����հɣ���" << std::endl;
            }
            else {
                // ����������յ�����
                int days = daysUntilBirthday(tempy, tempm, tempd);

                // ������
                std::cout << "������|�������ջ��� " << days << " �졣" << std::endl;

            }
            std::cout << "�绰���룺 " << abs->personArray[i].phone << "\t";
            std::cout << "��ͥסַ�� " << abs->personArray[i].add << "\t";
            std::cout << "��ϵ�˱�ע��" << abs->personArray[i].note << "\n";
            //std::cout << "��ϵ�˱�ע��" << abs->personArray[i].note << std::endl;
            std::cout << "-------------------------------------------------------------" << std::endl;
        }
    }
    //system("pause");
    //system("cls");
}
// �����ϵ���Ƿ���ڣ�������ڷ�����ϵ��������ľ���λ�ã������ڷ��ظ�һ
int isExist(Addressbooks* abs, std::string name) {
    for (int i = 0; i < abs->size; i++) {
        // �ҵ���
        if (abs->personArray[i].name == name) {
            return i;
        }
    }
    // û����
    return -1;
}

// ������������֮���������
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

    // ���������ת��Ϊ����
    return static_cast<int>(std::difftime(time2, time1) / (60 * 60 * 24));
}

// ����������ջ��ж�����
int daysUntilBirthday(int birthyear, int birthmonth, int birthday) {
    // ��ȡ��ǰ����
    time_t currentTime;
    time(&currentTime);
    struct tm localTime;
    localtime_s(&localTime, &currentTime);
    std::time_t now = std::time(nullptr);
    int currentYear = localTime.tm_year + 1900;
    int currentMonth = localTime.tm_mon + 1;
    int currentDay = localTime.tm_mday;

    // ����������������
    int thisYearBirthdayYear = currentYear;
    int thisYearBirthdayMonth = birthmonth;
    int thisYearBirthdayDay = birthday;

    // �жϽ���������Ƿ��Ѿ���ȥ
    if ((currentMonth > birthmonth) || (currentMonth == birthmonth && currentDay > birthday)) {
        // ����Ѿ���ȥ���������һ�������
        thisYearBirthdayYear++;
    }
    if (birthmonth == 2 && (birthyear % 4 == 0 || birthyear % 400 == 0)
        && birthday == 29 && (currentMonth > birthmonth)) {
        thisYearBirthdayYear += currentYear % 4 + 1;
    }
    // ����������յ�����
    return daysBetweenDates(currentYear, currentMonth, currentDay, thisYearBirthdayYear, thisYearBirthdayMonth, thisYearBirthdayDay);
}

void findPerson(Addressbooks* abs) {
    nojump_findperson:
    std::cout << "�������ѯ����ϵ�������� " << std::endl;
    std::string name;
    std::cin >> name;
    if (name == "���˵�") {

        std::cout << "�����������˵���������" << std::endl;
        std::cout << "���� ��ȷ�ϡ� �������˵�����" << std::endl;
        std::string yesjumpmaimenu = "-6";
        std::cin >> yesjumpmaimenu;
        if (yesjumpmaimenu == "ȷ��") {
            std::cout << "���ڷ������˵�����" << std::endl;
            return;
        }
        else {
            std::cout << "��ȡ���������˵������������  " << std::endl;
            goto nojump_findperson;
        }

    }
    int ret = isExist(abs, name);
    time_t currentTime;
    time(&currentTime);
    struct tm localTime;
    localtime_s(&localTime, &currentTime);
    if (ret != -1)  // �ҵ���
    {
        int tempy = std::stoi(abs->personArray[ret].year);
        int tempm = std::stoi(abs->personArray[ret].mon);
        int tempd = std::stoi(abs->personArray[ret].day);
        std::cout << "������ " << abs->personArray[ret].name << "\t";
        std::cout << "�Ա� " << (abs->personArray[ret].sex == "1" ? "��" : "Ů") << "\t";
        if (tempy != 0) {
            if (localTime.tm_mday - tempd >= 0 && localTime.tm_mon - tempm + 1 >= 0) {
                std::cout << "���䣺 " << localTime.tm_year - tempy + 1900 << std::endl;
            }
            else {
                std::cout << "���䣺 " << localTime.tm_year - tempy - 1 + 1900 << std::endl;
            }
        }
        else {
            std::cout << "���䣺 δ֪" << std::endl;
        }
        std::cout << "���������գ�  ";
        if (tempy == 0) {
            std::cout << "δ֪  �� ";
        }
        else {
            std::cout << tempy << "�� ";
        }
        if (tempm == 0) {
            std::cout << "δ֪  �� ";
        }
        else {
            std::cout << tempm << "�� ";
        }
        if (tempd == 0) {
            std::cout << "δ֪  ��      " ;
        }
        else {
            std::cout << tempd << "��      " ;
        }
        if (tempy == 0 || tempd == 0) {
            std::cout << "����δ֪����ȥ�������ѵ����հɣ���" << std::endl;
        }
        else {
            // ����������յ�����
            int days = daysUntilBirthday(tempy, tempm, tempd);

            // ������
            std::cout << "������|�������ջ��� " << days << " �졣" << std::endl;

        }
        std::cout << "�绰���룺 " << abs->personArray[ret].phone << "  ";
        std::cout << "��ͥסַ�� " << abs->personArray[ret].add << std::endl;
        std::cout << "��ϵ�˱�ע��" << abs->personArray[ret].note << std::endl;
        std::cout << "-------------------------------------------------------------" << std::endl;
    }
    else {
        std::cout << "ͨѶ¼��δ��ѯ�����ˣ�" << std::endl;
    }
    // �����������
    //system("pause");
    //system("cls");
}

void modifyPerson(Addressbooks* abs) {
    nojump_modifyperson:
    std::cout << "������Ҫ�޸ĵ���ϵ�ˣ� " << std::endl;
    std::string name;
    std::cin >> name;
    if (name == "���˵�") {

        std::cout << "�����������˵���������" << std::endl;
        std::cout << "���� ��ȷ�ϡ� �������˵�����" << std::endl;
        std::string yesjumpmaimenu = "-6";
        std::cin >> yesjumpmaimenu;
        if (yesjumpmaimenu == "ȷ��") {
            std::cout << "���ڷ������˵�����" << std::endl;
            return;
        }
        else {
            std::cout << "��ȡ���������˵������������  " << std::endl;
            goto nojump_modifyperson;
        }

    }

    int ret = isExist(abs, name);
    if (ret != -1) {
        system("cls");
        std::cout << "ע���������κ�ʱ�����롰���˵����Կɷ������˵�" << std::endl;
        std::cout << "+++++{+ ���ҵ�����ϵ�ˣ�+}+++++" << std::endl;
        std::cout << "!!!!-- �����ǿɲ�������  --!!!!" << std::endl;
        std::cout << "==***************************==" << std::endl;
        std::cout << "==*****  1����ϵ������  *****==" << std::endl;
        std::cout << "==*****  2����ϵ���Ա�  *****==" << std::endl;
        std::cout << "==*****  3����ϵ������  *****==" << std::endl;
        std::cout << "==*****  4����ϵ�˵绰  *****==" << std::endl;
        std::cout << "==*****  5����ϵ��סַ  *****==" << std::endl;
        std::cout << "==*****  6����ϵ�˱�ע  *****==" << std::endl;
        std::cout << "==*****  7�����޸�ȫ��  *****==" << std::endl;
        std::cout << "==*****   �����˳��޸�  *****==" << std::endl;
        std::cout << "==***************************==" << std::endl;
        std::cout << "�����������޸ĵ����ݣ�";
        int select = 0;
        std::cin >> select;
        // �ҵ���ϵ��
        int temp_mon;
        switch (select) {
            // ����
        case 1:
        {
            std::string name;
            nojump_modifyname:
            std::cout << "�������޸ĺ��������" << std::endl;
            std::cin >> name;
            if (name == "���˵�") {

                std::cout << "�����������˵���������" << std::endl;
                std::cout << "���� ��ȷ�ϡ� �������˵�����" << std::endl;
                std::string yesjumpmaimenu = "-6";
                std::cin >> yesjumpmaimenu;
                if (yesjumpmaimenu == "ȷ��") {
                    std::cout << "���ڷ������˵�����" << std::endl;
                    return;
                }
                else {
                    std::cout << "��ȡ���������˵������������  " << std::endl;
                    goto nojump_modifyname;
                }

            }

            abs->personArray[ret].name = name;
        }
        break;
        // �Ա�
        case 2:
        {
            std::string sex = "0";
        while (1) {
            nojump_modifysex:
            //std::cout << "�������ֱ�ӻص����˵�����-v-��~~" << std::endl;
            std::cout << "����1 ��������\t" << "����2 ����Ů��" << std::endl;
            std::cout << "�������޸ĺ���Ա� " << std::endl;

                int yes = 0;
                std::cin >> sex;
                if (sex == "���˵�") {

                    std::cout << "�����������˵���������" << std::endl;
                    std::cout << "���� ��ȷ�ϡ� �������˵�����" << std::endl;
                    std::string yesjumpmaimenu = "-6";
                    std::cin >> yesjumpmaimenu;
                    if (yesjumpmaimenu == "ȷ��") {
                        std::cout << "���ڷ������˵�����" << std::endl;
                        return;
                    }
                    else {
                        std::cout << "��ȡ���������˵������������  " << std::endl;
                        goto nojump_modifysex;
                    }

                }

                // ��ȷ����ֹͣѭ��
                if (sex == "1" || sex == "2") {
                    abs->personArray[abs->size].sex = sex;
                    break;
                    yes = 1;
                }
                if (!yes) {
                    std::cout << "��-v-��~~�����������������룺 " << std::endl;
                    //std::cout << "�������󼴽��������˵�����" << endl;
                    //return;
                }
            }
        }
        break;
        // ����
        case 3:
            while (1) {
                std::string year = "0";   // �������
                nojump_modifyyear:
                std::cout << "������������(����0Ϊδ֪)�� ";
                std::cin >> year;
                if (year == "���˵�") {

                    std::cout << "�����������˵���������" << std::endl;
                    std::cout << "���� ��ȷ�ϡ� �������˵�����" << std::endl;
                    std::string yesjumpmaimenu = "-6";
                    std::cin >> yesjumpmaimenu;
                    if (yesjumpmaimenu == "ȷ��") {
                        std::cout << "���ڷ������˵�����" << std::endl;
                        return;
                    }
                    else {
                        std::cout << "��ȡ���������˵������������  " << std::endl;
                        goto nojump_modifyyear;
                    }

                }
                int tempyear = std::stoi(year);
                if (tempyear > 1800 && tempyear < 3000) {   // �����Ч
                    abs->personArray[abs->size].year = year;
                    break;
                }
                else {
                    std::cout << "�����������������룡����" << std::endl;
                    system("cls");
                }
            }
            while (1) {
                std::string mon = "0";   // �����·�
                nojump_modifymon:
                std::cout << "����������·�(����0Ϊδ֪)�� ";
                std::cin >> mon;
                if (mon == "���˵�") {

                    std::cout << "�����������˵���������" << std::endl;
                    std::cout << "���� ��ȷ�ϡ� �������˵�����" << std::endl;
                    std::string yesjumpmaimenu = "-6";
                    std::cin >> yesjumpmaimenu;
                    if (yesjumpmaimenu == "ȷ��") {
                        std::cout << "���ڷ������˵�����" << std::endl;
                        return;
                    }
                    else {
                        std::cout << "��ȡ���������˵������������  " << std::endl;
                        goto nojump_modifymon;
                    }

                }

                int tempm = std::stoi(mon);
                if (tempm >= 0 && tempm <= 12) {   // �����Ч
                    abs->personArray[abs->size].mon = mon;
                    temp_mon = std::stoi(mon);
                    break;
                }
                else {
                    std::cout << "�����������������룡����" << std::endl;
                    system("pause");
                    system("cls");
                }
            }
            while (1) {
                std::string day = "0";   // ��������
                nojump_modifday:
                std::cout << "�������������(����0Ϊδ֪)�� ";
                int tempy = std::stoi(abs->personArray[abs->size].year);
                std::cin >> day;
                if (day == "���˵�") {

                    std::cout << "�����������˵���������" << std::endl;
                    std::cout << "���� ��ȷ�ϡ� �������˵�����" << std::endl;
                    std::string yesjumpmaimenu = "-6";
                    std::cin >> yesjumpmaimenu;
                    if (yesjumpmaimenu == "ȷ��") {
                        std::cout << "���ڷ������˵�����" << std::endl;
                        return;
                    }
                    else {
                        std::cout << "��ȡ���������˵������������  " << std::endl;
                        goto nojump_modifday;
                    }

                }

                int tempd = std::stoi(day);
                if (tempd >= 0 && tempd <= 31 && (temp_mon == 1 || temp_mon == 3 || temp_mon == 5 || temp_mon == 7
                    || temp_mon == 8 || temp_mon == 10 || temp_mon == 12)) {   // ������Ч
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
                            std::cout << "�����������������룡����" << std::endl;
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
                    std::cout << "�����������������룡����" << std::endl;
                    system("pause");
                    system("cls");
                }
                else if (temp_mon == 2 && tempd > 29) {
                    std::cout << "�����������������룡����" << std::endl;
                    system("pause");
                    system("cls");
                }
                else if (tempd < 0) {
                    std::cout << "�����������������룡����" << std::endl;
                    system("pause");
                    system("cls");
                }
            }
        break;
        // �绰
        case 4:
        {
            std::string phone;
            nojump_modifyphone:
            std::cout << "�������޸ĺ����ϵ�绰��" << std::endl;

            std::cin >> phone;

            if (phone == "���˵�") {

                std::cout << "�����������˵���������" << std::endl;
                std::cout << "���� ��ȷ�ϡ� �������˵�����" << std::endl;
                std::string yesjumpmaimenu = "-6";
                std::cin >> yesjumpmaimenu;
                if (yesjumpmaimenu == "ȷ��") {
                    std::cout << "���ڷ������˵�����" << std::endl;
                    return;
                }
                else {
                    std::cout << "��ȡ���������˵������������  " << std::endl;
                    goto nojump_modifyphone;
                }

            }

            abs->personArray[ret].phone = phone;
        }
        break;
        // סַ
        case 5:
        {
            std::string address;
            std::cout << "�������޸ĺ�ļ�ͥסַ�� " << std::endl;
            nojump_modifyaddress:
            std::cin >> address;

            if (address == "���˵�") {

                std::cout << "�����������˵���������" << std::endl;
                std::cout << "���� ��ȷ�ϡ� �������˵�����" << std::endl;
                std::string yesjumpmaimenu = "-6";
                std::cin >> yesjumpmaimenu;
                if (yesjumpmaimenu == "ȷ��") {
                    std::cout << "���ڷ������˵�����" << std::endl;
                    return;
                }
                else {
                    std::cout << "��ȡ���������˵������������  " << std::endl;
                    goto nojump_modifyaddress;
                }

            }

            abs->personArray[ret].add = address;
        }
        break;
        case 6:
        {
            //��ע
            std::string note;
            nojump_modifynote:
            std::cout << "�������޸ĺ����ϵ�˱�ע��" << std::endl;

            std::cin >> note;

            if (note == "���˵�") {

                std::cout << "�����������˵���������" << std::endl;
                std::cout << "���� ��ȷ�ϡ� �������˵�����" << std::endl;
                std::string yesjumpmaimenu = "-6";
                std::cin >> yesjumpmaimenu;
                if (yesjumpmaimenu == "ȷ��") {
                    std::cout << "���ڷ������˵�����" << std::endl;
                    return;
                }
                else {
                    std::cout << "��ȡ���������˵������������  " << std::endl;
                    goto nojump_modifynote;
                }

            }

            abs->personArray[ret].note = note;
        }
        break;
        // ȫ��
        case 7:
        {
            // ����
            std::string name;
            nojump_allmodifyname:
            std::cout << "�������޸ĺ�������� " << std::endl;
            std::cin >> name;

            if (name == "���˵�") {

                std::cout << "�����������˵���������" << std::endl;
                std::cout << "���� ��ȷ�ϡ� �������˵�����" << std::endl;
                std::string yesjumpmaimenu = "-6";
                std::cin >> yesjumpmaimenu;
                if (yesjumpmaimenu == "ȷ��") {
                    std::cout << "���ڷ������˵�����" << std::endl;
                    return;
                }
                else {
                    std::cout << "��ȡ���������˵������������  " << std::endl;
                    goto nojump_allmodifyname;
                }

            }

            abs->personArray[ret].name = name;
            // �Ա�
            std::string sex = "0";
            nojump_allmodifysex:
            std::cout << "�������ֱ�ӻص����˵�����-v-��~~" << std::endl;
            std::cout << "����1 ��������\t" << "����2 ����Ů��" << std::endl;
            std::cout << "�������޸ĺ���Ա� " << std::endl;
            //while (1) {
            int yes = 0;
            std::cin >> sex;

            if (sex == "���˵�") {

                std::cout << "�����������˵���������" << std::endl;
                std::cout << "���� ��ȷ�ϡ� �������˵�����" << std::endl;
                std::string yesjumpmaimenu = "-6";
                std::cin >> yesjumpmaimenu;
                if (yesjumpmaimenu == "ȷ��") {
                    std::cout << "���ڷ������˵�����" << std::endl;
                    return;
                }
                else {
                    std::cout << "��ȡ���������˵������������  " << std::endl;
                    goto nojump_allmodifysex;
                }

            }

            // ��ȷ����ֹͣѭ��
            if (sex == "1" || sex == "2") {
                abs->personArray[abs->size].sex = sex;
                //    break;
                yes = 1;
            }
            if (!yes) {
                std::cout << "�����������������룺 " << std::endl;
                std::cout << "�����ص����˵�������" << std::endl;
                system("pause");
                return;
            }
            //// ����
            //std::string age = "0";
            //std::cout << "�������޸ĺ�����䣺 " << std::endl;
            //std::cin >> age;
            //abs->personArray[ret].age = age;
            while (1) {
                std::string year = "0";   // �������
                nojump_allmodifyyear:
                std::cout << "������������(����0Ϊδ֪)�� ";
                std::cin >> year;

                if (year == "���˵�") {

                    std::cout << "�����������˵���������" << std::endl;
                    std::cout << "���� ��ȷ�ϡ� �������˵�����" << std::endl;
                    std::string yesjumpmaimenu = "-6";
                    std::cin >> yesjumpmaimenu;
                    if (yesjumpmaimenu == "ȷ��") {
                        std::cout << "���ڷ������˵�����" << std::endl;
                        return;
                    }
                    else {
                        std::cout << "��ȡ���������˵������������  " << std::endl;
                        goto nojump_allmodifyyear;
                    }

                }

                if (year > "1800" && year < "3000") {   // �����Ч
                    abs->personArray[abs->size].year = year;
                    break;
                }
                else {
                    std::cout << "�����������������룡����" << std::endl;
                    system("cls");
                }
            }
            while (1) {
                std::string mon = "0";   // �����·�
                nojump_allmodifymon:
                std::cout << "����������·�(����0Ϊδ֪)�� ";
                std::cin >> mon;

                if (mon == "���˵�") {

                    std::cout << "�����������˵���������" << std::endl;
                    std::cout << "���� ��ȷ�ϡ� �������˵�����" << std::endl;
                    std::string yesjumpmaimenu = "-6";
                    std::cin >> yesjumpmaimenu;
                    if (yesjumpmaimenu == "ȷ��") {
                        std::cout << "���ڷ������˵�����" << std::endl;
                        return;
                    }
                    else {
                        std::cout << "��ȡ���������˵������������  " << std::endl;
                        goto nojump_allmodifymon;
                    }

                }

                int tempm = std::stoi(mon);
                if (tempm >= 0 && tempm <= 12) {   // �����Ч
                    abs->personArray[abs->size].mon = mon;
                    temp_mon = std::stoi(mon);
                    break;
                }
                else {
                    std::cout << "�����������������룡����" << std::endl;
                    system("pause");
                    system("cls");
                }
            }
            while (1) {
                std::string day = "0";   // ��������
                nojump_allmodifyday:
                std::cout << "�������������(����0Ϊδ֪)�� ";
                int tempy = std::stoi(abs->personArray[abs->size].year);
                std::cin >> day;

                if (day == "���˵�") {

                    std::cout << "�����������˵���������" << std::endl;
                    std::cout << "���� ��ȷ�ϡ� �������˵�����" << std::endl;
                    std::string yesjumpmaimenu = "-6";
                    std::cin >> yesjumpmaimenu;
                    if (yesjumpmaimenu == "ȷ��") {
                        std::cout << "���ڷ������˵�����" << std::endl;
                        return;
                    }
                    else {
                        std::cout << "��ȡ���������˵������������  " << std::endl;
                        goto nojump_allmodifyday;
                    }

                }

                int tempd = std::stoi(day);
                if (tempd >= 0 && tempd <= 31 && (temp_mon == 1 || temp_mon == 3 || temp_mon == 5 || temp_mon == 7
                    || temp_mon == 8 || temp_mon == 10 || temp_mon == 12)) {   // ������Ч
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
                            std::cout << "�����������������룡����" << std::endl;
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
                    std::cout << "�����������������룡����" << std::endl;
                    system("pause");
                    system("cls");
                }
                else if (temp_mon == 2 && tempd > 29) {
                    std::cout << "�����������������룡����" << std::endl;
                    system("pause");
                    system("cls");
                }
                else if (tempd < 0) {
                    std::cout << "�����������������룡����" << std::endl;
                    system("pause");
                    system("cls");
                }
            }
            // �绰����
            std::string phone;
            nojump_allmodifyphone:
            std::cout << "�������޸ĺ����ϵ�绰��" << std::endl;

            std::cin >> phone;

            if (phone == "���˵�") {

                std::cout << "�����������˵���������" << std::endl;
                std::cout << "���� ��ȷ�ϡ� �������˵�����" << std::endl;
                std::string yesjumpmaimenu = "-6";
                std::cin >> yesjumpmaimenu;
                if (yesjumpmaimenu == "ȷ��") {
                    std::cout << "���ڷ������˵�����" << std::endl;
                    return;
                }
                else {
                    std::cout << "��ȡ���������˵������������  " << std::endl;
                    goto nojump_allmodifyphone;
                }

            }

            abs->personArray[ret].phone = phone;
            // ��ַ           
            std::string address;
            nojump_allmodifyaddress:
            std::cout << "�������޸ĺ�ļ�ͥסַ�� " << std::endl;
 
            std::cin >> address;

            if (address == "���˵�") {

                std::cout << "�����������˵���������" << std::endl;
                std::cout << "���� ��ȷ�ϡ� �������˵�����" << std::endl;
                std::string yesjumpmaimenu = "-6";
                std::cin >> yesjumpmaimenu;
                if (yesjumpmaimenu == "ȷ��") {
                    std::cout << "���ڷ������˵�����" << std::endl;
                    return;
                }
                else {
                    std::cout << "��ȡ���������˵������������  " << std::endl;
                    goto nojump_allmodifyaddress;
                }

            }

            // ��ע
            std::string note;
            nojump_allmodifynote:
            std::cout << "�������޸ĺ����ϵ�˱�ע" << std::endl;
            std::cin >> note;

            if (note == "���˵�") {

                std::cout << "�����������˵���������" << std::endl;
                std::cout << "���� ��ȷ�ϡ� �������˵�����" << std::endl;
                std::string yesjumpmaimenu = "-6";
                std::cin >> yesjumpmaimenu;
                if (yesjumpmaimenu == "ȷ��") {
                    std::cout << "���ڷ������˵�����" << std::endl;
                    return;
                }
                else {
                    std::cout << "��ȡ���������˵������������  " << std::endl;
                    goto nojump_allmodifynote;
                }

            }

        }
        break;
        // �˳�
        default:
        {
            std::cout << "���˳��޸���ϵ�ˣ�" << std::endl;
            //system("pause");
            //system("cls");
            return;
            break;
        }
        }
        //system("pause");
        //system("cls");    // ����
    }
    else {
        // δ�ҵ���ϵ��
        std::cout << "���޴��ˣ���" << std::endl;
        //system("pause");
        return;
    }
    std::cout << "���޸���ɣ�" << std::endl;
}
void saveaddressbooks(Addressbooks* abs)  // ����ͨѶ¼
{
    while (1) {
        std::cout << "ע�⣡������" << std::endl;//�������
        std::cout << "�˲����Ḳ���ϴα����ͨѶ¼\n�������ټ��һ��" << std::endl;
        std::cout << "���ȷ����ϣ������롰ȷ�ϡ��Ը����ϴα�������" << std::endl;
        std::cout << "���뱣�棬�����롰ȡ������ȡ������" << std::endl;
        std::string right = "0";
        std::cin >> right;

        if (right == "ȷ��") {
            std::ofstream fout("C:\\ͨѶ¼����.txt", std::ios::out);
            for (int i = 0; i < abs->size; i++) {
                fout << "����:" << abs->personArray[i].name << "\t";
                fout << "�Ա�:" << (abs->personArray[i].sex == "1" ? "��" : "Ů") << "\t";
                fout << "����������:" << abs->personArray[i].year  << "\t"
                     << "��:" << abs->personArray[i].mon << "\t"
                     << "��:" << abs->personArray[i].day << "\t";
                fout << "�绰����:" << abs->personArray[i].phone << "\n";
                fout << "��ͥסַ:" << abs->personArray[i].add << std::endl;
                fout << "��ϵ�˱�ע:" << abs->personArray[i].note << std::endl;
                //fout << "-------------------------------------------------------------" << std::endl;
                std::cout << "�ѱ��� ��" << abs->personArray[i].name << "�� �����ݣ���" << std::endl;
            }
            std::cout << "����ɹ�����" << std::endl;
            fout.close();
            return;
        }
        else if(right == "ȡ��"){
            std::cout << "��ȡ������" << std::endl;
            return;
        }
        else {
            //system("cls");

            std::cout << "���������������������Ƿ���ȷ" << std::endl;
            std::cout << "�����롰ȷ�ϡ����ߡ�ȡ����������!" << std::endl;
        }

        system("cls");
    }
}
void to_select(int n, Addressbooks* abs) {
    switch (n) {
    // 0:  // �˳�ͨѶ¼
    //    for (int o = 10;o > 0;o--)std::cout << "\\( * - v - * )/ �� ӭ �� �� ʹ �� �� �� !" << std::endl;
    //    break;
    case 1:  // �����ϵ��
        addperson(abs);
        break;
    case 2:  // ��ʾ��ϵ��
        showPerson(abs);
        break;
    case 3:  // ��ѯ��ϵ��
        findPerson(abs);
        break;
    case 4:  // �޸���ϵ��
        modifyPerson(abs);
        break;
    case 5:  // ɾ����ϵ��
    {
        std::string name;

        nojump_deleteperson:
        std::cout << "������ɾ����ϵ�˵������� " << std::endl;
         std::cin >> name;
        if (name == "���˵�") {

            std::cout << "�����������˵���������" << std::endl;
            std::cout << "���� ��ȷ�ϡ� �������˵�����" << std::endl;
            std::string yesjumpmaimenu = "-6";
            std::cin >> yesjumpmaimenu;
            if (yesjumpmaimenu == "ȷ��") {
                std::cout << "���ڷ������˵�����" << std::endl;
                return;
            }
            else {
                std::cout << "��ȡ���������˵������������  " << std::endl;
                goto nojump_deleteperson;
            }

        }

        int ret = isExist(abs, name);
        // �ж���ϵ���Ƿ����
        if (ret == -1) {
            std::cout << "���޴��ˣ���" << std::endl;
        }
        else {
            std::string right = "��";
            nojump_rightdeleteperson:
            std::cout << "�ҵ����ˣ�" << std::endl;
            std::cout << "���롰ȷ����ɾ������" << std::endl;
    
            std::cin >> right;
            if (right == "���˵�") {

                std::cout << "�����������˵���������" << std::endl;
                std::cout << "���� ��ȷ�ϡ� �������˵�����" << std::endl;
                std::string yesjumpmaimenu = "-6";
                std::cin >> yesjumpmaimenu;
                if (yesjumpmaimenu == "ȷ��") {
                    std::cout << "���ڷ������˵�����" << std::endl;
                    return;
                }
                else {
                    std::cout << "��ȡ���������˵������������  " << std::endl;
                    goto nojump_rightdeleteperson;
                }

            }

            if (right == "ȷ��") {
                for (int i = ret; i < abs->size; i++) {
                    abs->personArray[i] = abs->personArray[i + 1];
                }
                std::cout << "ɾ���ɹ���" << std::endl;
                abs->size--;
            }

        }
     //   system("pause");
     //   system("cls");
    }
    break;
    case 6:  // �����ϵ��
    {
        std::string right;
        std::cout << "���������������˵�" << std::endl;
        std::cout << "�����롰ȷ��������" << std::endl;
        std::cin >> right;
        if (right == "ȷ��") {
            std::cout << "����ĺ�Σ�գ������롰ȷ�������" << std::endl;
            std::cin >> right;
            if (right == "ȷ��") {
                abs->size = 0;
                std::cout << "�����ϣ���������" << std::endl;
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
    case 7:  // ����ͨѶ¼
        saveaddressbooks(abs);
    break;
    default: break;
    }
}

// ��ȡͨѶ¼���ݺ���
void readAddressbooks(Addressbooks* abs) {
    std::string filename = R"(C:\\ͨѶ¼����.txt)";
    std::string part;
    std::ifstream fin;
    fin.open(filename, std::ios::in);
    if (fin.is_open())
    {
        fin.seekg(std::ios::beg);
        while (std::getline(fin, part, ':') && abs->size < MAX)
        {
            person temp;// ��ʼ�� temp
            // 1����ȡ����
            std::getline(fin, part, '\t');
            temp.name = part;
            // 2����ȡ�Ա�
            std::getline(fin, part, ':');
            std::getline(fin, part, '\t');
            if (part == "��") {
                temp.sex = "1";
            }
            else {
                temp.sex = "2";
            }
            // 3����ȡ����
            std::getline(fin, part, ':');
            std::getline(fin, part, '\t');
            temp.year = part;
            std::getline(fin, part, ':');
            std::getline(fin, part, '\t');
            temp.mon = part;
            std::getline(fin, part, ':');
            std::getline(fin, part, '\t');
            temp.day = part;
            // 4����ȡ�绰
            std::getline(fin, part, ':');
            std::getline(fin, part, '\n');
            temp.phone = part;
            // 5����ȡסַ
            std::getline(fin, part, ':');
            std::getline(fin, part, '\n');
            temp.add = part;
            // 6����ȡ��ע
            std::getline(fin, part, ':');
            std::getline(fin, part, '\n');
            temp.note = part;
            abs->personArray[abs->size] = temp;
            std::cout << "�Ѷ�ȡ " << temp.name << " ������" << std::endl;
            abs->size++;
            //std::getline(fin,part);
        }
    }
    else {
        std::cout << "δ��⵽�ѱ���ͨѶ¼" << std::endl;
        std::cout << "�� �� �� �� �� һ �� ��" << std::endl;
        system("pause");
        return;
    }
    std::cout << "��ȡ�ϴα����ͨѶ¼ �ɹ�������" << std::endl;
    std::cout << "C:\\ͨѶ¼����.txt" << std::endl;
    system("pause");

}
void UpdateLog()
{
	system("cls");
	std::cout << "������־" << std::endl;
	std::cout << "�汾�ţ�V2.0" << std::endl;
	std::cout << "����ʱ�䣺2021��5��20��" << std::endl;
	std::cout << "�������ݣ�" << std::endl;
	std::cout << "1.�Ż����������ʱΪ ��0�� �����벻�˵�bug" << std::endl;
	std::cout << "(��ʵ����Ϊ����д��һ���ж�����)" << std::endl;
	std::cout << "2.�����˸�����־����" << std::endl;
	system("pause");
}

int main() {
    
    //for (int ii = 0;ii < 8;ii++) {
        std::cout << "���ڲ�����ı���Ŀ¼����Ĭ�ϱ�����C��Ŷuwu~" << std::endl;
        std::cout << "�鷳�Լ�����C�̴���һ�����ֽ� ��ͨѶ¼���ݡ� ��txt�ļ�" << std::endl;
    //}
    system("pause");
    system("cls");
    for (int ii = 0;ii < 5;ii++) {
        std::cout << std::endl << "��������Ƚ��-�������ṩ \\�� * V * �� / \t" << "�Ҹ��˸о�ͦ����Ŷ����" << std::endl;
    }
    std::cout << "�� �� �� �� �� . . . . . ." << std::endl;
    system("pause");
    system("cls");
    std::string select = "-6";  // �û�����ı���
    // ����ͨѶ¼
    Addressbooks abs;
    // ��ʼ����Ա����
    abs.size = 0;
    while (1) {
        time_t currentTime;
        time(&currentTime);
        struct tm   localTime;
        localtime_s(&localTime, &currentTime);
        std::string yesread = "0";
        std::cout << "�Ѵ�ͨѶ¼����" << "\n" << "�����Ƿ������ϴα����ͨѶ¼\n" << "�� �밴 ��1�� �� �밴��2��" << std::endl;
        std::cin >> yesread;
        if (yesread == "1") {
            readAddressbooks(&abs);
            break;
        }
        else if (yesread == "2") {
            std::cout << "ȡ������ͨѶ¼���ݣ�" << std::endl;
            system("pause");
            break;
        }
        else {
            std::cout << "������������" << std::endl;
            system("pause");
            system("cls");
        }
    }
    system("cls");
    while (1) {
    mainmenu:// ���˵�FLAG
        showmenu();
        std::cin >> select;
        try {

            int temps = std::stoi(select);
            if (temps < 1 || temps > 7) break;
            //        for (int ii = 0;ii < 5;ii++) {
            //            std::cout << endl << "��������Ƚ��-�������ṩ \\�� * V * �� / \t" << "�Ҹ��˸о�ͦ����Ŷ����" << std::endl;
            //        }
            //            std::cout << "�� �� �� �� �� һ �� . . . . . . " << endl;
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
        std::cout << "�����������������Զ����棡��������( ! U ! )" << std::endl;
    }
    saveaddressbooks(&abs);
    while (1) {
        std::cout << "���� ��ȷ���� �رճ��򡪡������������� ��ȡ���� �������˵�\n���� �����¡� �鿴������־\\(*V*)/" << std::endl;

        std::string yesoff;
        std::cin >> yesoff;
        if (yesoff == "ȷ��") {
            std::cout << "�����˳�ͨѶ¼" << std::endl;
            system("pause");
            system("cls");
            break;
        }
        else if (yesoff == "ȡ��") {
            std::cout << "���ڷ������˵�������" << std::endl;
            system("pause");
            system("cls");
            goto mainmenu;
        }
        else if (yesoff == "����") {
            UpdateLog();
        }
    }
    for (int o = 10;o > 0;o--) {
        std::cout << "\\( * - v - * )/ �� ӭ �� �� ʹ �� �� �� !" << std::endl;
        Sleep(50);
        std::cout << std::endl;

    }
    system("pause");
    return 0;
}