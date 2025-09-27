// StudentList.h

#ifndef STUDENTLIST_H
#define STUDENTLIST_H

#include<vector>
#include "Student.h"


// 节点类，继承自 Student
class Node : public Student
{
protected:
private:
	Node* next;
public:
	Node();
	Node(const Student& s);
	Node& operator=(const Node& right);

	friend class StudentList;

	// 模糊查找功能函数
	// 模糊查找判定函数
	template<typename T>
	bool is_search(const string &data, const T &source);
	
	// 模糊查找输出辅助函数
	template<typename T>
	void fuzzy_search_display(const string &field_name, const T &value, const string &search_data);
	
	// 模糊查找输出函数
	void fuzzy_search_display(const string &search_data);
};



// 链表类
class StudentList
{
private:
	Node* head;
	ll num = 0;
	
	// 清空链表
	void clear();
	
	// 计算考试平均成绩排名
	void Calculate_Test_ranking();
	
	// 计算综合测评总分排名
	void Calculate_Comprehensive_assessment_total_score();
	
	// 排名统一计算
	void Calculate_Score_Ranking();

public:
	// 构造函数：初始化 head 为 nullptr
	StudentList();

	// 输入数据(false:手动输入；true:自动文件读取)
	StudentList(bool flag);		

	~StudentList();

	// operator=重载
	StudentList& operator=(const StudentList& right);				


	//判断链表是否为空(false:空链表并输出提示；true:含有数据的链表)
	bool List_is_none();

	// 按学号插入（保持有序）(1:插入成功，-1:学号重复导致的插入失败)(CZ：默认false，正常插入；特殊true：客串添加数据的功能)
	int insert(Student s, bool CZ = false);
	
	// 仅依据学号查找节点
	Node* find_id(ll id);
	
	// 修改学生信息
	void change_informaton(ll id);
	
	// 删除学生
	void remove(ll id);
	
	// 保存到文件
	void saveToFile(const string& filename = out_filename);	
	
	// 从文件加载数据
	void loadFromFile();
	
	// 输出所有学生信息
	void displayAll();

	// 输出该门课所有学生的成绩
	void print_subject_all_scores(const int &sub);

	// 精确查找
	Node** precise_search();
	
	// 模糊查找
	Node** fuzzy_search();

	// 排序函数 true：升序排列（默认）；false：降序排列
	bool id_sort(bool sx = true);
	bool test_average_score_sort(bool sx = true);
	bool comprehensive_assessment_total_score_sort(bool sx = true);

	bool Get_is_head();
};

#endif