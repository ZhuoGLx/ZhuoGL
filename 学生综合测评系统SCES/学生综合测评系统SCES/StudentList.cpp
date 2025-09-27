// StudentList.cpp
#include "StudentList.h"


// �ڵ��� - ���캯������ʼ�� next ָ��Ϊ nullptr
Node::Node() : Student(), next(nullptr) {}


// �ڵ��� - �� Student ������ Node �Ĺ��캯����ͬʱ��ʼ�� next Ϊ nullptr
Node::Node(const Student& s) : Student(s), next(nullptr) {}

Node& Node::operator=(const Node& right)
{
	if (this == &right)
	{
		return *this;
	}
	Student_number = right.Student_number;
	Name = right.Name;
	Gender = right.Gender;
	Address = right.Address;
	Contact_number = right.Contact_number;
	Chinese = right.Chinese;
	Math = right.Math;
	English = right.English;
	Test_average_score = right.Test_average_score;
	Test_ranking = right.Test_ranking;
	Students_rate_each_other = right.Students_rate_each_other;
	Moral_score = right.Moral_score;
	Subject_teacher_scores = right.Subject_teacher_scores;
	Comprehensive_assessment_total_score = right.Comprehensive_assessment_total_score;
	Comprehensive_assessment_ranking = right.Comprehensive_assessment_ranking;
	next = nullptr;
	return *this;
}


// ���캯������ʼ�� head Ϊ nullptr
StudentList::StudentList() : head(nullptr), num(0) {}

// ��������(false:�ֶ����룻true:�Զ��ļ���ȡ)
StudentList::StudentList(bool flag) :head(nullptr), num(0)
{
	if (flag == false)
	{
		clear();
		Node* current = nullptr;
		Student new_student;
		cout << "�������[ " << num + 1 << " ]λѧ������Ϣ";
		yellow_print();
		cout << "����ֹ��������<����>��Ϣ�������� -1����\n";
		white_print();
		while (new_student.Set_Student() != false)
		{
			if (find_id(new_student.Student_number) != nullptr)
			{
				printError("ѧ���ظ�");
				cout << "�����������[ " << num + 1 << " ]λѧ������Ϣ����ֹ��������<����>��Ϣ�������� -1����\n";
				continue;
			}
			if (num == 0)
			{
				head = new Node(new_student);
				current = head;
			}
			else
			{
				current->next = new Node(new_student);
				current = current->next;
			}
			++num;
			cout << "�������[ " << num + 1 << " ]λѧ������Ϣ����ֹ��������<����>��Ϣ�������� -1����\n";
		}
		green_print();
		cout << "[ " << num << " ]��ѧ�������ֶ�������ϣ�\n\n";
		white_print();
		if (num == 0)
		{
			head = nullptr;
		}
		else
		{
			current->next = nullptr;
		}
	}
	else
	{
		loadFromFile();
	}
	Calculate_Score_Ranking();
	saveToFile(intermediate_filename);
}

// �������������� clear �����ͷ��������нڵ��ڴ�
StudentList::~StudentList()
{
	saveToFile();
	clear();
}

// operator=����
StudentList& StudentList::operator=(const StudentList& right)
{
	if (this == &right)
	{
		return *this;
	}
	clear();
	num = right.num;
	Node* right_current = right.head;
	Node* prev = nullptr;							// ��¼ǰ���ڵ�

	while (right_current != nullptr)
	{				
		Node* new_node = new Node(*right_current);	// �����½ڵ㲢��������
		if (prev == nullptr)
		{
			head = new_node;						// ͷ�ڵ��ʼ��
		}
		else
		{
			prev->next = new_node;					// ���ӵ�ǰ���ڵ�
		}
		prev = new_node;							// ����ǰ���ڵ�
		right_current = right_current->next;		// �ƶ�����������һ���ڵ�
	}
	return *this;
}

// ������������������ɾ���ڵ㣬�ͷ��ڴ�
void StudentList::clear()
{
	while (head != nullptr)
	{
		Node* temp = head;
		head = head->next;
		delete temp;
	}
	num = 0;
}

// ��ѧ�Ų��루��������(1:����ɹ���-1:ѧ���ظ����µĲ���ʧ��)(CZ��Ĭ��false���������룻����true���ʹ�������ݵĹ���)
int StudentList::insert(Student s, bool CZ)
{
	int result = 0;
	Node* newNode = new Node(s);								// �����½ڵ㣬�洢�����ѧ������ s

	if (head == nullptr)
	{
		head = newNode;
		result = 1;
	}
	else if (newNode->Student_number < head->Student_number)	// ��ѧ��ѧ��С��ͷ�ڵ�ѧ��
	{
		newNode->next = head;									// �½ڵ����һ���ڵ�ָ��ԭͷ�ڵ�
		head = newNode;											// �½ڵ��Ϊͷ�ڵ�
		result = 1;
	}
	else if (newNode->Student_number == head->Student_number)	// ��ѧ��ѧ�ŵ���ͷ�ڵ�ѧ��
	{
		red_print();
		cout << "ERROR������ѧ����ѧ��������ѧ����ѧ���ظ������������ֹ��(����Ϊ�ظ���ѧ�ŵ�����ѧ����)\n";			// ���������Ϣ
		white_print();
		cout << *head;
		result = -1;
		return -1;
	}
	else
	{
		Node* current = head;									// ������ͷ����ʼ����
		while (current->next != nullptr && current->next->Student_number < newNode->Student_number)		// Ѱ�Ҳ���λ�ã�ֱ����ǰ�ڵ����һ���ڵ�Ϊ�ջ���һ���ڵ�ѧ�Ŵ��ڵ����½ڵ�ѧ��
		{
			current = current->next;
		}

		// ����Ƿ����ѧ���ظ�
		if (current->next != nullptr && current->next->Student_number == newNode->Student_number)
		{
			red_print();
			cout << "ERROR������ѧ����ѧ��������ѧ����ѧ���ظ�������Ϊ�ظ���ѧ��<" << newNode->Student_number << ">������ѧ�����ݣ�\n\n";
			white_print();
			cout << *(current->next);
			result = -1;
			return -1;
		}

		newNode->next = current->next;							// �½ڵ���� current �ڵ�֮��
		current->next = newNode;								// current �ڵ����һ���ڵ�ָ���½ڵ�
		result = 1;
	}

	if (result == 1)
	{
		if (CZ == false)
		{
			green_print();
			cout << "ѧ��Ϊ<" << newNode->Student_number << ">��ѧ���Ѳ��룡\n\n";
			white_print();
			Calculate_Score_Ranking();
			saveToFile(intermediate_filename);
		}
		++num;
	}
	else if (result == 0)
	{
		red_print();
		cout << "ERROR������ʧ�ܣ�ʧ��ԭ��δ֪\n\n";
		white_print();
	}
	return result;
}

// ������ѧ�Ų��ҽڵ�
Node* StudentList::find_id(ll id)
{
	Node* current = head;
	while (current)
	{
		if (current->Student_number == id)
		{
			return current;									// �ҵ�ƥ��ѧ�ŵĽڵ㣬���ظýڵ�
		}
		current = current->next;							// �ƶ�����һ���ڵ�
	}
	return nullptr;											// δ�ҵ����ؿ�ָ��
}

//�ж������Ƿ�Ϊ��(false:�����������ʾ��true:�������ݵ�����)
bool StudentList::List_is_none()
{
	if (head == nullptr)
	{
		red_print();
		cout << "ERROR������Ϊ�գ�\n\n";
		white_print();
		return false;
	}
	return true;
}


// �޸�ѧ����Ϣ
void StudentList::change_informaton(ll id)
{
	if (List_is_none() == false)
	{
		return ;
	}
	Node* node = find_id(id);						// ����ָ��ѧ�ŵ�ѧ���ڵ�
	if (node != nullptr)							// �ҵ��ڵ�
	{
		cout << "��ѧ����ǰ����Ϊ��\n" << *node;
		if (Change_Data(*node))						// ���� Change_Data �����޸���Ϣ���ɹ������
		{
			node->Calculate_Test_average_score();	// ���¼��㿼��ƽ���ɼ�
			node->Calculate_Comprehensive_assessment_total_score();	// ���¼����ۺϲ����ܷ�
			Calculate_Score_Ranking();
			saveToFile(intermediate_filename);							// �����޸ĺ�����ݵ��ļ�
		}
	}
	else
	{
		red_print();
		cout << "ERROR��δ�ҵ���ѧ��ѧ����\n\n";	// δ�ҵ���ʾ
		white_print();
	}
}

// ɾ��ѧ��
void StudentList::remove(ll id)
{
	Node* current = head;
	Node* prev = nullptr;												// ���ڼ�¼��ǰ�ڵ��ǰһ���ڵ�
	if (current == nullptr)
	{
		red_print();
		cout << "ERROR������Ϊ�գ�\n\n";
		white_print();
		return;
	}
	bool is_change = false;
	while (current != nullptr)											// ��������
	{
		if (current->Student_number == id)								// ����ѧ��
		{
			yellow_print();
			cout << "��ȷ���Ƿ�ɾ������ѧ����\n";
			white_print();
			cout << *current;
			yellow_print();
			cout << "Y: ��\tN����\n�����룺";	// ��ʾ��ѧ����Ϣ��ȷ���Ƿ�ɾ��
			white_print();

			char confirm;
			cin >> confirm;
			while (true)
			{
				if (confirm == 'y' || confirm == 'Y')					// ȷ��ɾ��
				{
					if (prev != nullptr)
					{
						prev->next = current->next;						// ǰһ���ڵ�������ǰ�ڵ�
					}
					else
					{
						head = current->next;							// �����ͷ�ڵ㣬ͷָ�����
					}
					delete current;										// ɾ����ǰ�ڵ�
					green_print();
					cout << "��ɾ��ѧ��Ϊ" << id << "��ѧ����\n\n";
					white_print();
					--num;
					Calculate_Score_Ranking();
					is_change = true;
					saveToFile(intermediate_filename);										// ����ɾ����������������ݵ��ļ�
					return;
				}
				else if(confirm == 'n' || confirm == 'N')
				{
					yellow_print();
					cout << "ɾ����������ֹ��\n\n";
					white_print();
					return;
				}
				printError("������ų�����Χ", false);
				yellow_print();
				cout << "��ȷ���Ƿ�ɾ����ѧ����\nY: ��\tN����\n�����룺";
				white_print();
				cin >> confirm;
			}
			break;
		}
		prev = current;													// ��¼��ǰ�ڵ�Ϊǰһ���ڵ�
		current = current->next;										// �ƶ�����һ���ڵ�
	}
	if (is_change != true)												// ɾ�������ʾ
	{
		red_print();
		cout << "ERROR��δ�ҵ���ѧ��ѧ����\n\n";
		white_print();
	}
}

// ���浽�ļ�
void StudentList::saveToFile(const string& filename)
{
	ofstream fout(filename);						// �����ģʽ���ļ�
	if (fout)
	{	// �ļ��򿪳ɹ�
		Node* current = head;						// ������ͷ����ʼ
		while (current != nullptr)					// ��������
		{
			fout << "ѧ��\t\t\t" << current->Student_number << "\n"
				<< "����\t\t\t" << current->Name << "\n"
				<< "�Ա�\t\t\t" << current->Gender << "\n"
				<< "��ͥסַ\t\t" << current->Address << "\n"
				<< "��ϵ�绰\t\t" << current->Contact_number << "\n"
				<< "���ĳɼ�\t\t" << setprecision(2) << fixed << current->Chinese << "\n"
				<< "��ѧ�ɼ�\t\t" << setprecision(2) << fixed << current->Math << "\n"
				<< "����ɼ�\t\t" << setprecision(2) << fixed << current->English << "\n"
				<< "����ƽ���ɼ�\t" << setprecision(2) << fixed << current->Test_average_score << "\n"
				<< "��������\t\t" << current->Test_ranking << "\n"
				<< "ͬѧ������\t" << setprecision(2) << fixed << current->Students_rate_each_other << "\n"
				<< "Ʒ�³ɼ�\t\t" << setprecision(2) << fixed << current->Moral_score << "\n"
				<< "�ον�ʦ����\t" << setprecision(2) << fixed << current->Subject_teacher_scores << "\n"
				<< "�ۺϲ����ܷ�\t" << setprecision(2) << fixed << current->Comprehensive_assessment_total_score << "\n"
				<< "�ۺϲ�������\t" << current->Comprehensive_assessment_ranking << "\n\n";
			current = current->next;				// �ƶ�����һ���ڵ�
		}
		fout.close();								// �ر��ļ�
	}
	else
	{
		red_print();
		cout << "ERROR��<" << filename << ">�ļ�����ʧ�ܣ�\n";	// �ļ���ʧ����ʾ
		white_print();
	}
}


//// ���ļ���������
//void StudentList::loadFromFile()
//{
//	clear();							// �����������������
//	ifstream fin(in_filename);			// ������ģʽ���ļ�
//	if (fin)
//	{	// �ļ��򿪳ɹ�
//		ll student_number, fail_num = 0;
//		string name, gender, address, contact_number;
//		lb chinese, math, english, students_rate, moral, teacher;
//		// ���ļ��洢��ʽ��ȡ����
//		while (fin >> student_number >> name >> gender >> address >> contact_number >> chinese >> math >> english >> students_rate >> moral >> teacher)
//		{
//			Student s(student_number, name, gender, address, contact_number, chinese, math, english, students_rate, moral, teacher);	// ����ѧ������
//			if (insert(s, true) == -1)				// ��ѧ����������
//			{
//				++fail_num;
//			}
//		}
//		green_print();
//		cout << "<" << in_filename << ">�ļ���ȡ��ϣ���[ " << num << " ]��ѧ�����ݶ�ȡ�ɹ���";
//		red_print();
//		cout << "��[ " << fail_num << " ]��ѧ�����ݶ�ȡʧ��\n\n";
//		white_print();
//		fin.close();	// �ر��ļ�
//	}
//	else
//	{
//		red_print();
//		cout << "ERROR��<" << in_filename << ">�ļ������ڣ����½��ļ���\n";	// �ļ���������ʾ
//		white_print();
//	}
//}

// ���ļ��������ݣ�ʹ��string�����ֻ������ԣ�
void StudentList::loadFromFile()
{
	clear(); // �����������
	ifstream fin(in_filename);
	if (!fin)
	{
		red_print();
		cout << "ERROR��<" << in_filename << ">�ļ������ڣ����½��ļ���\n";
		white_print();
		return;
	}

	string line;
	int line_num = 0;
	int fail_num = 0;

	while (getline(fin, line))
	{
		line_num++;
		vector<string> parts;
		stringstream ss(line);
		string field;

		// ���ո�ָ��ֶ�
		while (ss >> field)
		{
			parts.push_back(field);
		}

		if (parts.size() != 11)
		{
			red_print();
			cout << "��[" << line_num<< "]��ʽ���󣺱������11���ֶ���Ϣ��ʵ����" << parts.size() << "��\n";
			white_print();
			fail_num++;
			continue;
		}

		Student new_student;
		bool valid = true;

		// 1. ѧ�ţ�����Ϊ���֣�
		if (string_judge_number(parts[0]) == false)
		{
			red_print();
			cout << "��[" << line_num << "]ѧ�ŷǷ�(���ڳ�����֮����ַ�)��" << parts[0] << "\n";
			white_print();
			valid = false;
			++fail_num;
			continue;
		}
		else
		{
			new_student.Student_number = atoll(parts[0].c_str());
		}

		// 2. �Ա𣨽�����/Ů��
		if (parts[2] != "��" && parts[2] != "Ů")
		{
			red_print();
			cout << "��[" << line_num << "]�Ա�Ƿ�(���ڳ�\"��\"��\"Ů\"֮����ַ�)��" << parts[2] << "\n";
			white_print();
			valid = false;
			++fail_num;
			continue;
		}
		else
		{
			new_student.Gender = parts[2];
		}

		// 3. �ɼ��ֶΣ�ת��Ϊ���ֲ���鷶Χ��
		for (int i = 5; i <= 10; i++)
		{
			char* endptr;
			double score = strtod(parts[i].c_str(), &endptr);			// �ַ���ת��long double

			if (*endptr != '\0' || score < 0 || score > 100)
			{
				red_print();
				cout << "��[" << line_num << "]�ɼ��Ƿ�(���ڳ�����֮����ַ�����ֵ������100����)��" << parts[i] << "\n";
				white_print();
				valid = false;
				++fail_num;
				break;
			}

			switch (i)
			{
			case 5: new_student.Chinese = score; break;
			case 6: new_student.Math = score; break;
			case 7: new_student.English = score; break;
			case 8: new_student.Students_rate_each_other = score; break;
			case 9: new_student.Moral_score = score; break;
			case 10: new_student.Subject_teacher_scores = score; break;
			}
		}
		if (valid == false)
		{
			continue;
		}

		// �����ֶ�
		new_student.Name = parts[1];
		new_student.Address = parts[3];
		if (string_judge_number(parts[4]) == false)
		{
			red_print();
			cout << "��[" << line_num << "]��ϵ�绰�Ƿ�(���ڳ�����֮����ַ�)��" << parts[4] << "\n";
			white_print();
			valid = false;
			++fail_num;
			continue;
		}
		else
		{
			new_student.Contact_number = parts[4];
		}

		// ����Ϸ�����
		if (valid == true)
		{
			new_student.Calculate_Comprehensive_assessment_total_score();
			if (insert(new_student, true) == -1)
			{
				++fail_num;
				red_print();
				cout << "��[" << line_num<< "]ѧ���ظ���������\n";
				white_print();
			}
		}
	}

	fin.close();
	green_print();
	cout << "<" << in_filename << ">�ļ���ȡ��ϣ���[ " << num << " ]����Ч�����У�";
	red_print();
	cout << "��[ " << fail_num << " ]����Ч������\n\n";
	white_print();
	Calculate_Score_Ranking();
	saveToFile(intermediate_filename);
}

// �������ѧ����Ϣ
void StudentList::displayAll()
{
	Node* current = head;	// ������ͷ����ʼ
	if (current == nullptr)
	{
		red_print();
		cout << "ERROR������Ϊ�գ�\n\n";
		white_print();
		return;
	}
	else
	{
		green_print();
		cout << "����Ϊ��ǰ����ѧ�����ݣ�\n\n";
		white_print();
	}
	while (current)
	{	// ��������
		current->Message_print();	// ����ѧ���������Ϣ��ʾ����
		current = current->next;	// �ƶ�����һ���ڵ�
	}
	green_print();
	cout << "��[ " << num << " ]��ѧ������\n\n";
	white_print();
	saveToFile(intermediate_filename);
}

// ѧ������true���������У�Ĭ�ϣ���false����������
bool StudentList::id_sort(bool sx)
{
	// ����߽�������������Ϊ�ջ�ֻ��һ���ڵ㣬��������
	if (head == nullptr || num <= 1)
	{
		return true;
	}

	bool swapped;				// ��Ǳ����Ƿ�������
	bool is_need;
	Node* current;				// ��ǰ�Ƚϵĵ�һ���ڵ�
	Node* current_next;			// ��ǰ�Ƚϵĵڶ����ڵ㣨current����һ���ڵ㣩
	Node* prev1 = nullptr;		// current��ǰ���ڵ�


	for (int i = 0; i < num - 1; i++)	// ð������
	{
		swapped = false;		// ���ý������
		current = head;			// ÿ�ִ�ͷ��ʼ����
		prev1 = nullptr;		// ��ʼ��ǰ���ڵ�

		// ȷ����ǰ�ڵ����һ���ڵ㶼��Ϊ��
		while (current != nullptr && current->next != nullptr)
		{
			current_next = current->next; // ��ǰ�Ƚϵĵڶ����ڵ�

			if (sx == true)
			{
				is_need = current->Student_number > current_next->Student_number;
			}
			else
			{
				is_need = current->Student_number < current_next->Student_number;
			}
			if (is_need == true)
			{
				// �����ڵ㣺����ǰ���ڵ��ָ��
				if (prev1 != nullptr)
				{
					prev1->next = current_next; // ǰ���ڵ�ָ��current_next
				}
				else
				{
					// ���prevΪ�գ�˵����ǰ��������ͷ�ڵ㣬��Ҫ����head
					head = current_next;
				}

				Node* temp = current_next->next;	// ����current_next����һ���ڵ㣬��ֹ����

				// ��ɽڵ㽻����
				// 1. current_next��nextָ��current
				// 2. current��nextָ��ԭcurrent_next��next
				current_next->next = current;
				current->next = temp;

				prev1 = current_next;	// ����prev������current_next���Ƶ�current��λ�ã�prevӦָ��current_next

				swapped = true; // ��Ƿ����˽���

				// ע�⣺���ﲻ��ֱ���ƶ�current����Ϊcurrent�Ѿ�������������ȥ��
				// ����ͨ��continue����ѭ��ĩβ��current�ƶ�����
				continue;
			}

			// ���û�н����������ƶ�prev��currentָ��
			prev1 = current;
			current = current->next;
		}

		// �������û�з���������˵�������Ѿ�������ǰ��������
		if (swapped == false)
		{
			break;
		}
	}
	return true; // ����ɹ����
}

// ����ƽ���ɼ�����true���������У�Ĭ�ϣ���false����������
bool StudentList::test_average_score_sort(bool sx)
{
	// ����߽�������������Ϊ�ջ�ֻ��һ���ڵ㣬��������
	if (head == nullptr || num <= 1)
	{
		return true;
	}

	bool swapped;				// ��Ǳ����Ƿ�������
	bool is_need;
	Node* current;				// ��ǰ�Ƚϵĵ�һ���ڵ�
	Node* current_next;			// ��ǰ�Ƚϵĵڶ����ڵ㣨current����һ���ڵ㣩
	Node* prev = nullptr;		// current��ǰ���ڵ�

	for (int i = 0; i < num - 1; i++)	// ð������
	{
		swapped = false;		// ���ý������
		current = head;			// ÿ�ִ�ͷ��ʼ����
		prev = nullptr;			// ��ʼ��ǰ���ڵ�

		// ȷ����ǰ�ڵ����һ���ڵ㶼��Ϊ��
		while (current != nullptr && current->next != nullptr)
		{
			current_next = current->next; // ��ǰ�Ƚϵĵڶ����ڵ�

			if (sx == true)
			{
				is_need = current->Test_average_score > current_next->Test_average_score;
			}
			else
			{
				is_need = current->Test_average_score < current_next->Test_average_score;
			}
			if (is_need == true)
			{
				// �����ڵ㣺����ǰ���ڵ��ָ��
				if (prev != nullptr)
				{
					prev->next = current_next; // ǰ���ڵ�ָ��current_next
				}
				else
				{
					head = current_next;		// ���prevΪ�գ�˵����ǰ��������ͷ�ڵ㣬��Ҫ����head
				}

				Node* temp = current_next->next;// ����current_next����һ���ڵ㣬��ֹ����

				// ��ɽڵ㽻����
				current_next->next = current;	// 1. current_next��nextָ��current
				current->next = temp;			// 2. current��nextָ��ԭcurrent_next��next
				prev = current_next;			// 3. ����prev������current_next���Ƶ�current��λ�ã����prevӦָ��current_next
				swapped = true;					// ��Ƿ����˽���

				// ע�⣺���ﲻ��ֱ���ƶ�current����Ϊcurrent�Ѿ�������������ȥ�ˣ�����ͨ��continue����ѭ��ĩβ��current�ƶ�����
				continue;
			}

			// ���û�н����������ƶ�prev��currentָ��
			prev = current;
			current = current->next;
		}

		// �������û�з���������˵�������Ѿ�������ǰ��������
		if (swapped == false)
		{
			break;
		}
	}
	return true; // ����ɹ����
}

// �ۺϲ����ܷ�����true���������У�Ĭ�ϣ���false����������
bool StudentList::comprehensive_assessment_total_score_sort(bool sx)
{
	// ����߽�������������Ϊ�ջ�ֻ��һ���ڵ㣬��������
	if (head == nullptr || num <= 1)
	{
		return true;
	}

	bool swapped;				// ��Ǳ����Ƿ�������
	bool is_need;
	Node* current;				// ��ǰ�Ƚϵĵ�һ���ڵ�
	Node* current_next;			// ��ǰ�Ƚϵĵڶ����ڵ㣨current����һ���ڵ㣩
	Node* prev = nullptr;		// current��ǰ���ڵ�
	
	for (int i = 0; i < num - 1; i++)		// ð������
	{
		swapped = false;					// ���ý������
		current = head;						// ÿ�ִ�ͷ��ʼ����
		prev = nullptr;						// ��ʼ��ǰ���ڵ�

		// ȷ����ǰ�ڵ����һ���ڵ㶼��Ϊ��
		while (current != nullptr && current->next != nullptr)
		{
			current_next = current->next; // ��ǰ�Ƚϵĵڶ����ڵ�

			if (sx == true)
			{
				is_need = current->Comprehensive_assessment_total_score > current_next->Comprehensive_assessment_total_score;
			}
			else
			{
				is_need = current->Comprehensive_assessment_total_score < current_next->Comprehensive_assessment_total_score;
			}
			if (is_need == true)
			{
				// �����ڵ㣺����ǰ���ڵ��ָ��
				if (prev != nullptr)
				{
					prev->next = current_next; // ǰ���ڵ�ָ��current_next
				}
				else
				{
					// ���prevΪ�գ�˵����ǰ��������ͷ�ڵ㣬��Ҫ����head
					head = current_next;
				}

				Node* temp = current_next->next;	// ����current_next����һ���ڵ㣬��ֹ����

				// ��ɽڵ㽻����
				// 1. current_next��nextָ��current
				// 2. current��nextָ��ԭcurrent_next��next
				current_next->next = current;
				current->next = temp;

				// ����prev������current_next���Ƶ�current��λ�ã�prevӦָ��current_next
				prev = current_next;

				swapped = true; // ��Ƿ����˽���

				// ע�⣺���ﲻ��ֱ���ƶ�current����Ϊcurrent�Ѿ�������������ȥ��
				// ����ͨ��continue����ѭ��ĩβ��current�ƶ�����
				continue;
			}

			// ���û�н����������ƶ�prev��currentָ��
			prev = current;
			current = current->next;
		}

		// �������û�з���������˵�������Ѿ�������ǰ��������
		if (swapped == false)
		{
			break;
		}
	}
	return true; // ����ɹ����
}

// ���㿼��ƽ���ɼ�����
void StudentList::Calculate_Test_ranking()
{
	if (head == nullptr)
	{
		return;
	}
	test_average_score_sort(false);
	ll ranking = 0;
	ll same_score_num = 0;
	lb same_score = -1;
	Node* current = head;
	while (current != nullptr)
	{
		if (current->Test_average_score == same_score)
		{
			++same_score_num;
		}
		else
		{
			ranking += (same_score_num + 1);
			same_score = current->Test_average_score;
			same_score_num = 0;
		}
		current->Test_ranking = ranking;
		current = current->next;
	}
}

// �����ۺϲ����ܷ�����
void StudentList::Calculate_Comprehensive_assessment_total_score()
{
	if (head == nullptr)
	{
		return;
	}
	comprehensive_assessment_total_score_sort(false);
	ll ranking = 0;
	ll same_score_num = 0;
	lb same_score = -1;
	Node* current = head;
	while (current != nullptr)
	{
		if (current->Comprehensive_assessment_total_score == same_score)
		{
			++same_score_num;
		}
		else
		{
			ranking += (same_score_num + 1);
			same_score = current->Comprehensive_assessment_total_score;
			same_score_num = 0;
		}
		current->Comprehensive_assessment_ranking = ranking;
		current = current->next;
	}
}

// ����ͳһ����
void StudentList::Calculate_Score_Ranking()
{
	Calculate_Test_ranking();
	Calculate_Comprehensive_assessment_total_score();
	id_sort();
}

// ������ſ�����ѧ���ĳɼ�
void StudentList::print_subject_all_scores(const int &sub)
{
	if (List_is_none() == false)
	{
		return ;
	}

	Node* current = head;
	Node** result = new Node*[num];

	ofstream fout(intermediate_filename);
	bool fout_flag = false;
	if (fout)
	{
		fout_flag = true;
	}

	while (current != nullptr)
	{
		std::cout << "ѧ��\t\t" << current->Student_number << "\n";
		std::cout << "����\t\t" << current->Name << "\n";

		fout << "ѧ��\t\t\t" << current->Student_number << "\n"
			<< "����\t\t\t" << current->Name << "\n"
			<< Data_list_chinese[sub] << '\t';

		switch (sub)
		{
		case 6:

			score_print("���ĳɼ�", current->Chinese);
			if (fout_flag == true)
			{
				fout << current->Chinese;
			}
			break;
		case 7:
			score_print("��ѧ�ɼ�", current->Math);
			if (fout_flag == true)
			{
				fout << current->Math;
			}
			break;
		case 8:
			score_print("����ɼ�", current->English);
			if (fout_flag == true)
			{
				fout << current->English;
			}
			break;
		case 9:
			score_print("����ƽ���ɼ�", current->Test_average_score);
			if (fout_flag == true)
			{
				fout << current->Test_average_score;
			}
			break;
		case 11:
			score_print("ͬѧ������", current->Students_rate_each_other);
			if (fout_flag == true)
			{
				fout << current->Students_rate_each_other;
			}
			break;
		case 12:
			score_print("Ʒ�³ɼ�", current->Moral_score);
			if (fout_flag == true)
			{
				fout << current->Moral_score;
			}
			break;
		case 13:
			score_print("�ον�ʦ����", current->Subject_teacher_scores);
			if (fout_flag == true)
			{
				fout << current->Subject_teacher_scores;
			}
			break;
		case 14:
			score_print("�ۺϲ����ܷ�", current->Comprehensive_assessment_total_score);
			if (fout_flag == true)
			{
				fout << current->Comprehensive_assessment_total_score;
			}
			break;
		default:
			break;
		}
		std::cout << '\n';
		fout << "\n\n";
		current = current->next;
	}
	
	if (fout_flag == true)
	{
		green_print();
		cout << "����ѧ����" << Data_list_chinese[sub] << "�ɼ���д��<" << intermediate_filename << ">�ļ�\n\n";
		white_print();
		fout.close();
	}
}

// ��ȷ����
Node** StudentList::precise_search()
{
	if (List_is_none() == false)
	{
		return nullptr;
	}

	int position;
	cout << "���������뾫ȷ���ҵ���Ϣѡ�\n";
	for (int i = 0; i < 15; i++)
	{
		cout << setw(2) << setfill('0') << i+1;
		cout << ". " << Data_list_chinese[i] << '\n';
	}
	cout << "00. ��ֹ��ȷ��Ϣ���Ҳ���\n������ѡ����ţ�";
	cin >> position;
	while (position > 15 || position < 0)
	{
		printError("ѡ����ų�����Χ", false);
		cout << "���ٴ��������뾫ȷ���ҵ���Ϣѡ����ţ�";
		cin >> position;
	}
	if (position == 0)
	{
		return nullptr;
	}
	
	Node* current = head;
	Node** result = new Node*[num]();
	int find_num = 0;

	if (position >= 1 && position <= 5)
	{
		string data;
		cout << "�������뾫ȷ���ҵ�" << Data_list_chinese[position-1] << "���ݣ�";
		cin >> data;
		switch (position)
		{
		case 1:
		{
			while (string_judge_number(data) == false)
			{
				printError("ѧ�Ų��ܰ����ַ�(\"-\",\"/\")", false);
				cout << "�������뾫ȷ���ҵ�����ѧ�ţ�";
				cin >> data;
			}
			ll student_number = 0;
			for (int i = 0; i < (int)data.size(); i++)
			{
				student_number = student_number * 10 + (data[i] - '0');
			}

			while (current != nullptr)
			{
				if (current->Student_number == student_number)
				{
					if (find_num == 0)
					{
						green_print();
						cout << "�Ѹ��ݸ�ѧ����Ϣ�ҵ�����ѧ����\n";
						white_print();
					}
					cout << *current;
					result[find_num] = current;
					find_num++;
				}
				current = current->next;
			}
			break;
		}
		case 2:
			while (current != nullptr)
			{
				if (current->Name == data)
				{
					if (find_num == 0)
					{
						green_print();
						cout << "�Ѹ��ݸ�������Ϣ�ҵ�����ѧ����\n";
						white_print();
					}
					cout << *current;
					result[find_num] = current;
					find_num++;
				}
				current = current->next;
			}
			break;
		case 3:
			while (!(data == "��" || data == "Ů"))
			{
				printError("�Ա������\"��\"��\"Ů\"", false);
				cout << "�������뾫ȷ���ҵ�" << Data_list_chinese[position] << "���ݣ�";
				cin >> data;
			}
			while (current != nullptr)
			{
				if (current->Gender == data)
				{
					if (find_num == 0)
					{
						green_print();
						cout << "�Ѹ��ݸ��Ա���Ϣ�ҵ�����ѧ����\n";
						white_print();
					}
					cout << *current;
					result[find_num] = current;
					find_num++;
				}
				current = current->next;
			}
			break;
		case 4:
			while (current != nullptr)
			{
				if (current->Address == data)
				{
					if (find_num == 0)
					{
						green_print();
						cout << "�Ѹ��ݸü�ͥסַ��Ϣ�ҵ�����ѧ����\n";
						white_print();
					}
					cout << *current;
					result[find_num] = current;
					find_num++;
				}
				current = current->next;
			}
			break;
		case 5:
			while (string_judge_number(data) == false)
			{
				printError("��ϵ�绰���ܰ����ַ�(\"-\",\"/\")", false);
				cout << "�������뾫ȷ���ҵ�" << Data_list_chinese[position] << "���ݣ�";
				cin >> data;
			}
			while (current != nullptr)
			{
				if (current->Contact_number == data)
				{
					if (find_num == 0)
					{
						green_print();
						cout << "�Ѹ��ݸ���ϵ�绰��Ϣ�ҵ�����ѧ����\n";
						white_print();
					}
					cout << *current;
					result[find_num] = current;
					find_num++;
				}
				current = current->next;
			}
			break;
		default:
			break;
		}
	}
	else
	{
		if (position != 10 && position != 15)
		{
			cout << "��ѡ�����ѡ�\n1.����ѧ����" << Data_list_chinese[position - 1] << "\n2.����" << Data_list_chinese[position - 1] << "�Բ��Ҷ�Ӧѧ��\n�����룺";
			int numb;
			cin >> numb;
			while (numb < 1 || numb>2)
			{
				printError("ѡ����ų�����Χ", false);
				cout << "���ٴ�����������еĲ���ѡ����ţ�";
				cin >> numb;
			}
			if (numb == 1)
			{
				print_subject_all_scores(position);
				delete[] result;
				result = new Node*[2]{ head, head };
				return result;
			}
		}
		lb score;
		switch (position)
		{
		case 6:
			inputScore("�뾫ȷ���ҵ�����", score, false);
			while (current != nullptr)
			{
				if (current->Chinese == score)
				{
					if (find_num == 0)
					{
						green_print();
						cout << "�Ѹ��ݸ����ĳɼ���Ϣ�ҵ�����ѧ����\n";
						white_print();
					}
					cout << *current;
					result[find_num] = current;
					find_num++;
				}
				current = current->next;
			}
			break;
		case 7:
			inputScore("�뾫ȷ���ҵ���ѧ", score, false);
			while (current != nullptr)
			{
				if (current->Math == score)
				{
					if (find_num == 0)
					{
						green_print();
						cout << "�Ѹ��ݸ���ѧ�ɼ���Ϣ�ҵ�����ѧ����\n";
						white_print();
					}
					cout << *current;
					result[find_num] = current;
					find_num++;
				}
				current = current->next;
			}
			break;
		case 8:
			inputScore("�뾫ȷ���ҵ�����", score, false);
			while (current != nullptr)
			{
				if (current->English == score)
				{
					if (find_num == 0)
					{
						green_print();
						cout << "�Ѹ��ݸ�����ɼ���Ϣ�ҵ�����ѧ����\n";
						white_print();
					}
					cout << *current;
					result[find_num] = current;
					find_num++;
				}
				current = current->next;
			}
			break;
		case 9:
			inputScore("�뾫ȷ���ҵĿ���ƽ��", score, false);
			while (current != nullptr)
			{
				if (score_round(current->Test_average_score) == score)
				{
					if (find_num == 0)
					{
						green_print();
						cout << "�Ѹ��ݸÿ���ƽ���ɼ���Ϣ�ҵ�����ѧ����\n";
						white_print();
					}
					cout << *current;
					result[find_num] = current;
					find_num++;
				}
				current = current->next;
			}
			break;
		case 10:
		{
			ll ranking;
			cout << "�������뾫ȷ���ҵĿ����������ݣ�";
			cin >> ranking;
			while (ranking <= 0)
			{
				printError("���β���ΪС�ڵ���0����", false);
				cout << "�������뾫ȷ���ҵĿ����������ݣ�";
				cin >> ranking;
			}
			while (current != nullptr)
			{
				if (current->Test_ranking == ranking)
				{
					if (find_num == 0)
					{
						green_print();
						cout << "�Ѹ��ݸÿ���������Ϣ�ҵ�����ѧ����\n";
						white_print();
					}
					cout << *current;
					result[find_num] = current;
					find_num++;
				}
				current = current->next;
			}
		}
			break;
		case 11:
			inputScore("�뾫ȷ���ҵ�ͬѧ������", score, false);
			while (current != nullptr)
			{
				if (current->Students_rate_each_other == score)
				{
					if (find_num == 0)
					{
						green_print();
						cout << "�Ѹ��ݸ�ͬѧ��������Ϣ�ҵ�����ѧ����\n";
						white_print();
					}
					cout << *current;
					result[find_num] = current;
					find_num++;
				}
				current = current->next;
			}
			break;
		case 12:
			inputScore("�뾫ȷ���ҵ�Ʒ��", score, false);
			while (current != nullptr)
			{
				if (current->Moral_score == score)
				{
					if (find_num == 0)
					{
						green_print();
						cout << "�Ѹ��ݸ�Ʒ����Ϣ�ҵ�����ѧ����\n";
						white_print();
					}
					cout << *current;
					result[find_num] = current;
					find_num++;
				}
				current = current->next;
			}
			break;
		case 13:
			inputScore("�뾫ȷ���ҵ��ον�ʦ����", score, false);
			while (current != nullptr)
			{
				if (current->Subject_teacher_scores == score)
				{
					if (find_num == 0)
					{
						green_print();
						cout << "�Ѹ��ݸ��ον�ʦ������Ϣ�ҵ�����ѧ����\n";
						white_print();
					}
					cout << *current;
					result[find_num] = current;
					find_num++;
				}
				current = current->next;
			}
			break;
		case 14:
			inputScore("�뾫ȷ���ҵ��ۺϲ����ܷ�", score, false);
			while (current != nullptr)
			{
				if (score_round(current->Comprehensive_assessment_total_score) == score)
				{
					if (find_num == 0)
					{
						green_print();
						cout << "�Ѹ��ݸ��ۺϲ����ܷ���Ϣ�ҵ�����ѧ����\n";
						white_print();
					}
					cout << *current;
					result[find_num] = current;
					find_num++;
				}
				current = current->next;
			}
			break;
		case 15:
		{
			ll ranking;
			cout << "�������뾫ȷ���ҵ��ۺϲ����������ݣ�";
			cin >> ranking;
			while (ranking <= 0)
			{
				printError("���β���ΪС�ڵ���0����", false);
				cout << "�������뾫ȷ���ҵ��ۺϲ����������ݣ�";
				cin >> ranking;
			}
			while (current != nullptr)
			{
				if (current->Comprehensive_assessment_ranking == ranking)
				{
					if (find_num == 0)
					{
						green_print();
						cout << "�Ѹ��ݸ��ۺϲ���������Ϣ�ҵ�����ѧ����\n";
						white_print();
					}
					cout << *current;
					result[find_num] = current;
					find_num++;
				}
				current = current->next;
			}
		}
			break;
		default:
			break;
		}
	}

	if (find_num == 0)
	{
		red_print();
		cout << "δ�ҵ����<" << Data_list_chinese[position - 1] << ">��Ϣ��ƥ���ѧ����\n\n";
		white_print();
		return nullptr;
	}
	else
	{
		green_print();
		cout << "���ݸ�<" << Data_list_chinese[position - 1] << ">��Ϣ�����ҵ�[ " << find_num << " ]��ѧ����Ϣ\n\n";
		white_print();
		if (find_num < num)
		{
			Node** final_result = new Node*[find_num];
			memcpy(final_result, result, find_num * sizeof(Node*));
			delete[] result;
			result = final_result;
		}

		ofstream fout(intermediate_filename, ios::trunc);
		if (fout)
		{
			fout << "���������<" << Data_list_chinese[position - 1] << ">��Ϣ����ȷ���ҵ���ѧ�����ݣ�\n\n";
			for (int i = 0; i < find_num; i++)
			{
				if (result[i] != nullptr)
				{
					fout << "ѧ��\t\t\t" << result[i]->Student_number << "\n"
						<< "����\t\t\t" << result[i]->Name << "\n"
						<< "�Ա�\t\t\t" << result[i]->Gender << "\n"
						<< "��ͥסַ\t\t" << result[i]->Address << "\n"
						<< "��ϵ�绰\t\t" << result[i]->Contact_number << "\n"
						<< "���ĳɼ�\t\t" << setprecision(2) << fixed << result[i]->Chinese << "\n"
						<< "��ѧ�ɼ�\t\t" << setprecision(2) << fixed << result[i]->Math << "\n"
						<< "����ɼ�\t\t" << setprecision(2) << fixed << result[i]->English << "\n"
						<< "����ƽ���ɼ�\t" << setprecision(2) << fixed << result[i]->Test_average_score << "\n"
						<< "��������\t\t" << result[i]->Test_ranking << "\n"
						<< "ͬѧ������\t" << setprecision(2) << fixed << result[i]->Students_rate_each_other << "\n"
						<< "Ʒ�³ɼ�\t\t" << setprecision(2) << fixed << result[i]->Moral_score << "\n"
						<< "�ον�ʦ����\t" << setprecision(2) << fixed << result[i]->Subject_teacher_scores << "\n"
						<< "�ۺϲ����ܷ�\t" << setprecision(2) << fixed << result[i]->Comprehensive_assessment_total_score << "\n"
						<< "�ۺϲ�������\t" << result[i]->Comprehensive_assessment_ranking << "\n\n";
				}
				else
				{
					fout << "result[i] == nullptr\n";
				}
			}
			fout << "���ݸ�<" << Data_list_chinese[position - 1] << ">��Ϣ�����ҵ�[ " << find_num << " ]��ѧ����Ϣ\n\n";
			fout.close();
		}
		else
		{
			red_print();
			cout << "ERROR��<" << intermediate_filename << ">�ļ�����ʧ�ܣ�\n\n";	// �ļ���ʧ����ʾ
			white_print();
		}

		return result;
	}
}


// �ַ���ת������
template<typename T>
string turn_string(const T &data, int set = 2)
{
	stringstream data1;
	data1 << setprecision(set) << fixed << data;
	string data2 = data1.str();
	return data2;
}

// ģ�������ж�����
template<typename T>
bool Node::is_search(const string &data, const T &source)
{
	string source_data = turn_string(source);
	return (source_data.find(data) != string::npos);
}

// �����ֵ���͵��ػ��汾��ȷ��ת������
template<>
bool Node::is_search<long double>(const string &data, const long double &source)
{
	stringstream ss;
	ss << setprecision(2) << fixed << source;									// ȷ������ʾ����һ��
	string source_data = ss.str();
	return (source_data.find(data) != string::npos);
}

// ģ�����������������
template<typename T>
void Node::fuzzy_search_display(const string &field_name, const T &value, const string &search_data)
{
	cout << field_name << "\t";
	if (field_name=="ѧ��"|| field_name == "����"|| field_name == "�Ա�")
	{
		cout << "\t";
	}
	bool is_match = is_search(search_data, value);
	if (is_match)
	{
		blue_print();
	}
	cout << setprecision(2) << fixed << value << "\n";
	if (is_match)
	{
		white_print();
	}
}

// ģ�������������
void Node::fuzzy_search_display(const string &search_data)
{
	fuzzy_search_display("ѧ��", Student_number, search_data);
	fuzzy_search_display("����", Name, search_data);
	fuzzy_search_display("�Ա�", Gender, search_data);
	fuzzy_search_display("��ͥסַ", Address, search_data);
	fuzzy_search_display("��ϵ�绰", Contact_number, search_data);
	fuzzy_search_display("���ĳɼ�", Chinese, search_data);
	fuzzy_search_display("��ѧ�ɼ�", Math, search_data);
	fuzzy_search_display("����ɼ�", English, search_data);
	fuzzy_search_display("����ƽ���ɼ�", Test_average_score, search_data);
	fuzzy_search_display("��������", Test_ranking, search_data);
	fuzzy_search_display("ͬѧ������", Students_rate_each_other, search_data);
	fuzzy_search_display("Ʒ�³ɼ�", Moral_score, search_data);
	fuzzy_search_display("�ον�ʦ����", Subject_teacher_scores, search_data);
	fuzzy_search_display("�ۺϲ����ܷ�", Comprehensive_assessment_total_score, search_data);
	fuzzy_search_display("�ۺϲ�������", Comprehensive_assessment_ranking, search_data);
	cout << "\n";
}

// ģ������
Node** StudentList::fuzzy_search()
{
	if (List_is_none() == false)
	{
		return nullptr;
	}

	cout << "��������Ҫģ�����ҵ���Ϣ��";
	string data;
	cin >> data;

	Node* current = head;
	Node** result = new Node*[num]();
	ll find_num = 0;
	bool is_match = false;

	while (current != nullptr)
	{
		is_match = false;
		is_match =
			// ѧ�ţ�����
			current->is_search(data, current->Student_number) == true || current->is_search(data, current->Name) == true
			// �Ա𣬼�ͥסַ
			|| current->is_search(data, current->Gender) == true || current->is_search(data, current->Address) == true
			// ��ϵ�绰
			|| current->is_search(data, current->Contact_number) == true
			// ���ĳɼ�����ѧ�ɼ�������ɼ�
			|| current->is_search(data, current->Chinese) == true || current->is_search(data, current->Math) == true || current->is_search(data, current->English) == true
			// ����ƽ���ɼ�����������
			|| current->is_search(data, current->Test_average_score) == true || current->is_search(data, current->Test_ranking) == true
			// ͬѧ�����֣�Ʒ�³ɼ����ον�ʦ����
			|| current->is_search(data, current->Students_rate_each_other) == true || current->is_search(data, current->Moral_score) == true || current->is_search(data, current->Subject_teacher_scores) == true
			// �ۺϲ����ܷ֣��ۺϲ�������
			|| current->is_search(data, current->Comprehensive_assessment_total_score) == true || current->is_search(data, current->Comprehensive_assessment_ranking) == true;
		if (is_match == true)
		{
			if (find_num == 0)
			{
				green_print();
				cout << "�Ѹ��ݸ�<" << data << ">��Ϣ�ҵ�����ѧ����\n";
				white_print();
			}
			current->fuzzy_search_display(data);
			result[find_num] = current;
			find_num++;
		}
		current = current->next;
	}

	if (find_num == 0)
	{
		red_print();
		cout << "δ�ҵ����<" << data << ">������ص�ѧ����\n\n";
		white_print();
		return nullptr;
	}
	else
	{
		green_print();
		cout << "���ݸ�<" << data << ">���ݣ����ҵ�[ " << find_num << " ]�����ѧ����Ϣ\n\n";
		white_print();
	}

	if (find_num < num)
	{
		Node** final_result = new Node*[find_num];
		memcpy(final_result, result, find_num * sizeof(Node*));
		delete[] result;
		result = final_result;
	}

	ofstream fout(intermediate_filename);
	if (fout)
	{
		fout << "���������<" << data << ">������ģ�����ҵ������ѧ�����ݣ�\n\n";
		for (int i = 0; i < find_num; i++)
		{
			if (result[i] != nullptr)
			{
				fout << "ѧ��\t\t\t" << result[i]->Student_number << "\n"
					<< "����\t\t\t" << result[i]->Name << "\n"
					<< "�Ա�\t\t\t" << result[i]->Gender << "\n"
					<< "��ͥסַ\t\t" << result[i]->Address << "\n"
					<< "��ϵ�绰\t\t" << result[i]->Contact_number << "\n"
					<< "���ĳɼ�\t\t" << setprecision(2) << fixed << result[i]->Chinese << "\n"
					<< "��ѧ�ɼ�\t\t" << setprecision(2) << fixed << result[i]->Math << "\n"
					<< "����ɼ�\t\t" << setprecision(2) << fixed << result[i]->English << "\n"
					<< "����ƽ���ɼ�\t" << setprecision(2) << fixed << result[i]->Test_average_score << "\n"
					<< "��������\t\t" << result[i]->Test_ranking << "\n"
					<< "ͬѧ������\t" << setprecision(2) << fixed << result[i]->Students_rate_each_other << "\n"
					<< "Ʒ�³ɼ�\t\t" << setprecision(2) << fixed << result[i]->Moral_score << "\n"
					<< "�ον�ʦ����\t" << setprecision(2) << fixed << result[i]->Subject_teacher_scores << "\n"
					<< "�ۺϲ����ܷ�\t" << setprecision(2) << fixed << result[i]->Comprehensive_assessment_total_score << "\n"
					<< "�ۺϲ�������\t" << result[i]->Comprehensive_assessment_ranking << "\n\n";
			}
			else
			{
				fout << "result[i] == nullptr\n";
			}
		}
		fout << "���ݸ�<" << data << ">���ݣ����ҵ�[ " << find_num << " ]�����ѧ����Ϣ\n\n";
		fout.close();
	}
	else
	{
		red_print();
		cout << "ERROR��<" << intermediate_filename << ">�ļ�����ʧ�ܣ�\n\n";	// �ļ���ʧ����ʾ
		white_print();
	}

	return result;
}

bool StudentList::Get_is_head()
{
	if (head == nullptr)
	{
		return false;
	}
	return true;
}