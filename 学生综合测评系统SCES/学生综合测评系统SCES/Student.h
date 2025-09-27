// Student.h

#ifndef STUDENT_H
#define STUDENT_H

#include<iostream>
#include<string> 
#include<iomanip>
#include<cmath>
#include<cstring>
#include <windows.h>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

#define ll long long
#define lb long double

// ��Ϣ�б�[ 0"Student_number",1"Name",2"Gender",3"Address",4"Contact_number",5"Chinese",6"Math",7"English",8"Test_average_score",9"Test_ranking",10"Students_rate_each_other",11"Moral_score",12"Subject_teacher_scores",13"Comprehensive_assessment_total_score",14"Comprehensive_assessment_ranking"]
extern string Data_list[15];
extern string Data_list_chinese[15];
extern HANDLE hConsole;									// ��ȡ��׼��ɫ������

extern string in_filename;
extern string out_filename;
extern string intermediate_filename;

void red_print();										// ��ɫ��ʾ����
void green_print();										// ��ɫ��ʾ����
void yellow_print();									// ��ɫ��ʾ����
void blue_print();										// ��ɫ��ʾ����
void white_print();										// ԭɫ����ɫ����ʾ����

void printError(const string& a = " ", bool flag = true);		// ����������
bool string_judge_number(const string a);				// �ж��ַ����Ƿ�ȫΪ����
lb score_round(lb score);								// ��������������ֵ
//bool turn_lb(const string& str);							// �ַ���ת��long double

// ѧ����Ϣ���븨������
bool inputScore(const string& subject, lb& score, bool flag = true);	

// �ɼ������ɫ��������
void score_print(const string& sub, lb &score);

	
// ѧ����Ϣ��
class Student
{
public:
	// ���캯�������ó�ʼֵ
	Student(ll student_number = -2,
		string name = "δ֪",
		string gender = "δ֪",
		string address = "δ֪",
		string contact_number = "δ֪",
		lb chinese = 0,
		lb math = 0,
		lb english = 0,
		lb students_rate_each_other = 0,
		lb moral_score = 0,
		lb subject_teacher_scores = 0);
	Student(const Student& obj);
	
	// ����ѧ����Ϣ����(������true���쳣(-1�˳�)��false)
	bool Set_Student();
	
	// ���㿼��ƽ���ɼ�
	void Calculate_Test_average_score();
	
	// �����ۺϲ����ܷ�
	void Calculate_Comprehensive_assessment_total_score();
	
	// ѧ����Ϣ���
	void Message_print();
	
	//<<���������
	friend ostream& operator<<(ostream& out, const Student& stu);

	// �޸�����
	friend bool Change_Data(Student &stu);

protected:

	ll Student_number = -2;							// ѧ�� (��ֵ���ʼΪ -1 )
	string Name = "δ֪";							// ���� (��ֵ���ʼΪ δ֪ )
	string Gender = "δ֪";							// �Ա� (��ֵ���ʼΪ δ֪ )
	string Address = "δ֪";						// ��ͥסַ (��ֵ���ʼΪ δ֪ )
	string Contact_number = "δ֪";					// ��ϵ�绰 (��ֵ���ʼΪ δ֪ )

	lb Chinese = 0;									// ���ĳɼ� (��ֵ���ʼΪ 0 )
	lb Math = 0;									// ��ѧ�ɼ� (��ֵ���ʼΪ 0 )
	lb English = 0;									// ����ɼ� (��ֵ���ʼΪ 0 )

	lb Test_average_score = 0;						// ����ƽ���ɼ� (��ֵ���ʼΪ 0 )
	ll Test_ranking = 0;							// �������� (��ֵ���ʼΪ 0 )

	lb Students_rate_each_other = 0;				// ͬѧ������ (��ֵ���ʼΪ 0 )
	lb Moral_score = 0;								// Ʒ�³ɼ� (��ֵ���ʼΪ 0 )
	lb Subject_teacher_scores = 0;					// �ον�ʦ���� (��ֵ���ʼΪ 0 )

	lb Comprehensive_assessment_total_score = 0;	// �ۺϲ����ܷ� (��ֵ���ʼΪ 0 )
	ll Comprehensive_assessment_ranking = 0;		// �ۺϲ������� (��ֵ���ʼΪ 0 )

	friend class StudentList;
private:
};

#endif