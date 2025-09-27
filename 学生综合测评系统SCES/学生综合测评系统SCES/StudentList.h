// StudentList.h

#ifndef STUDENTLIST_H
#define STUDENTLIST_H

#include<vector>
#include "Student.h"


// �ڵ��࣬�̳��� Student
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

	// ģ�����ҹ��ܺ���
	// ģ�������ж�����
	template<typename T>
	bool is_search(const string &data, const T &source);
	
	// ģ�����������������
	template<typename T>
	void fuzzy_search_display(const string &field_name, const T &value, const string &search_data);
	
	// ģ�������������
	void fuzzy_search_display(const string &search_data);
};



// ������
class StudentList
{
private:
	Node* head;
	ll num = 0;
	
	// �������
	void clear();
	
	// ���㿼��ƽ���ɼ�����
	void Calculate_Test_ranking();
	
	// �����ۺϲ����ܷ�����
	void Calculate_Comprehensive_assessment_total_score();
	
	// ����ͳһ����
	void Calculate_Score_Ranking();

public:
	// ���캯������ʼ�� head Ϊ nullptr
	StudentList();

	// ��������(false:�ֶ����룻true:�Զ��ļ���ȡ)
	StudentList(bool flag);		

	~StudentList();

	// operator=����
	StudentList& operator=(const StudentList& right);				


	//�ж������Ƿ�Ϊ��(false:�����������ʾ��true:�������ݵ�����)
	bool List_is_none();

	// ��ѧ�Ų��루��������(1:����ɹ���-1:ѧ���ظ����µĲ���ʧ��)(CZ��Ĭ��false���������룻����true���ʹ�������ݵĹ���)
	int insert(Student s, bool CZ = false);
	
	// ������ѧ�Ų��ҽڵ�
	Node* find_id(ll id);
	
	// �޸�ѧ����Ϣ
	void change_informaton(ll id);
	
	// ɾ��ѧ��
	void remove(ll id);
	
	// ���浽�ļ�
	void saveToFile(const string& filename = out_filename);	
	
	// ���ļ���������
	void loadFromFile();
	
	// �������ѧ����Ϣ
	void displayAll();

	// ������ſ�����ѧ���ĳɼ�
	void print_subject_all_scores(const int &sub);

	// ��ȷ����
	Node** precise_search();
	
	// ģ������
	Node** fuzzy_search();

	// ������ true���������У�Ĭ�ϣ���false����������
	bool id_sort(bool sx = true);
	bool test_average_score_sort(bool sx = true);
	bool comprehensive_assessment_total_score_sort(bool sx = true);

	bool Get_is_head();
};

#endif