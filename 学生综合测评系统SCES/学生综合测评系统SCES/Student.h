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

// 信息列表[ 0"Student_number",1"Name",2"Gender",3"Address",4"Contact_number",5"Chinese",6"Math",7"English",8"Test_average_score",9"Test_ranking",10"Students_rate_each_other",11"Moral_score",12"Subject_teacher_scores",13"Comprehensive_assessment_total_score",14"Comprehensive_assessment_ranking"]
extern string Data_list[15];
extern string Data_list_chinese[15];
extern HANDLE hConsole;									// 获取标准颜色输出句柄

extern string in_filename;
extern string out_filename;
extern string intermediate_filename;

void red_print();										// 红色显示函数
void green_print();										// 绿色显示函数
void yellow_print();									// 黄色显示函数
void blue_print();										// 蓝色显示函数
void white_print();										// 原色（白色）显示函数

void printError(const string& a = " ", bool flag = true);		// 报错辅助函数
bool string_judge_number(const string a);				// 判断字符串是否全为数字
lb score_round(lb score);								// 返回四舍五入后的值
//bool turn_lb(const string& str);							// 字符串转换long double

// 学生信息输入辅助函数
bool inputScore(const string& subject, lb& score, bool flag = true);	

// 成绩输出颜色辅助函数
void score_print(const string& sub, lb &score);

	
// 学生信息类
class Student
{
public:
	// 构造函数，设置初始值
	Student(ll student_number = -2,
		string name = "未知",
		string gender = "未知",
		string address = "未知",
		string contact_number = "未知",
		lb chinese = 0,
		lb math = 0,
		lb english = 0,
		lb students_rate_each_other = 0,
		lb moral_score = 0,
		lb subject_teacher_scores = 0);
	Student(const Student& obj);
	
	// 具体学生信息输入(正常：true；异常(-1退出)：false)
	bool Set_Student();
	
	// 计算考试平均成绩
	void Calculate_Test_average_score();
	
	// 计算综合测评总分
	void Calculate_Comprehensive_assessment_total_score();
	
	// 学生信息输出
	void Message_print();
	
	//<<运算符重载
	friend ostream& operator<<(ostream& out, const Student& stu);

	// 修改数据
	friend bool Change_Data(Student &stu);

protected:

	ll Student_number = -2;							// 学号 (无值则初始为 -1 )
	string Name = "未知";							// 姓名 (无值则初始为 未知 )
	string Gender = "未知";							// 性别 (无值则初始为 未知 )
	string Address = "未知";						// 家庭住址 (无值则初始为 未知 )
	string Contact_number = "未知";					// 联系电话 (无值则初始为 未知 )

	lb Chinese = 0;									// 语文成绩 (无值则初始为 0 )
	lb Math = 0;									// 数学成绩 (无值则初始为 0 )
	lb English = 0;									// 外语成绩 (无值则初始为 0 )

	lb Test_average_score = 0;						// 考试平均成绩 (无值则初始为 0 )
	ll Test_ranking = 0;							// 考试名次 (无值则初始为 0 )

	lb Students_rate_each_other = 0;				// 同学互评分 (无值则初始为 0 )
	lb Moral_score = 0;								// 品德成绩 (无值则初始为 0 )
	lb Subject_teacher_scores = 0;					// 任课教师评分 (无值则初始为 0 )

	lb Comprehensive_assessment_total_score = 0;	// 综合测评总分 (无值则初始为 0 )
	ll Comprehensive_assessment_ranking = 0;		// 综合测评名次 (无值则初始为 0 )

	friend class StudentList;
private:
};

#endif