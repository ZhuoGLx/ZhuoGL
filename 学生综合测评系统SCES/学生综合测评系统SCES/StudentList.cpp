// StudentList.cpp
#include "StudentList.h"


// 节点类 - 构造函数：初始化 next 指针为 nullptr
Node::Node() : Student(), next(nullptr) {}


// 节点类 - 用 Student 对象构造 Node 的构造函数，同时初始化 next 为 nullptr
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


// 构造函数：初始化 head 为 nullptr
StudentList::StudentList() : head(nullptr), num(0) {}

// 输入数据(false:手动输入；true:自动文件读取)
StudentList::StudentList(bool flag) :head(nullptr), num(0)
{
	if (flag == false)
	{
		clear();
		Node* current = nullptr;
		Student new_student;
		cout << "请输入第[ " << num + 1 << " ]位学生的信息";
		yellow_print();
		cout << "（终止输入请在<任意>信息栏内输入 -1）：\n";
		white_print();
		while (new_student.Set_Student() != false)
		{
			if (find_id(new_student.Student_number) != nullptr)
			{
				printError("学号重复");
				cout << "请重新输入第[ " << num + 1 << " ]位学生的信息（终止输入请在<任意>信息栏内输入 -1）：\n";
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
			cout << "请输入第[ " << num + 1 << " ]位学生的信息（终止输入请在<任意>信息栏内输入 -1）：\n";
		}
		green_print();
		cout << "[ " << num << " ]个学生数据手动输入完毕！\n\n";
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

// 析构函数：调用 clear 函数释放链表所有节点内存
StudentList::~StudentList()
{
	saveToFile();
	clear();
}

// operator=重载
StudentList& StudentList::operator=(const StudentList& right)
{
	if (this == &right)
	{
		return *this;
	}
	clear();
	num = right.num;
	Node* right_current = right.head;
	Node* prev = nullptr;							// 记录前驱节点

	while (right_current != nullptr)
	{				
		Node* new_node = new Node(*right_current);	// 创建新节点并复制数据
		if (prev == nullptr)
		{
			head = new_node;						// 头节点初始化
		}
		else
		{
			prev->next = new_node;					// 连接到前驱节点
		}
		prev = new_node;							// 更新前驱节点
		right_current = right_current->next;		// 移动到右链表下一个节点
	}
	return *this;
}

// 清空链表：遍历链表，逐个删除节点，释放内存
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

// 按学号插入（保持有序）(1:插入成功，-1:学号重复导致的插入失败)(CZ：默认false，正常插入；特殊true：客串添加数据的功能)
int StudentList::insert(Student s, bool CZ)
{
	int result = 0;
	Node* newNode = new Node(s);								// 创建新节点，存储传入的学生对象 s

	if (head == nullptr)
	{
		head = newNode;
		result = 1;
	}
	else if (newNode->Student_number < head->Student_number)	// 新学生学号小于头节点学号
	{
		newNode->next = head;									// 新节点的下一个节点指向原头节点
		head = newNode;											// 新节点成为头节点
		result = 1;
	}
	else if (newNode->Student_number == head->Student_number)	// 新学生学号等于头节点学号
	{
		red_print();
		cout << "ERROR：插入学生的学号与已有学生的学号重复，插入操作终止！(以下为重复该学号的已有学生：)\n";			// 输出报错信息
		white_print();
		cout << *head;
		result = -1;
		return -1;
	}
	else
	{
		Node* current = head;									// 从链表头部开始遍历
		while (current->next != nullptr && current->next->Student_number < newNode->Student_number)		// 寻找插入位置，直到当前节点的下一个节点为空或下一个节点学号大于等于新节点学号
		{
			current = current->next;
		}

		// 检查是否存在学号重复
		if (current->next != nullptr && current->next->Student_number == newNode->Student_number)
		{
			red_print();
			cout << "ERROR：插入学生的学号与已有学生的学号重复！以下为重复该学号<" << newNode->Student_number << ">的已有学生数据：\n\n";
			white_print();
			cout << *(current->next);
			result = -1;
			return -1;
		}

		newNode->next = current->next;							// 新节点接在 current 节点之后
		current->next = newNode;								// current 节点的下一个节点指向新节点
		result = 1;
	}

	if (result == 1)
	{
		if (CZ == false)
		{
			green_print();
			cout << "学号为<" << newNode->Student_number << ">的学生已插入！\n\n";
			white_print();
			Calculate_Score_Ranking();
			saveToFile(intermediate_filename);
		}
		++num;
	}
	else if (result == 0)
	{
		red_print();
		cout << "ERROR：操作失败，失败原因：未知\n\n";
		white_print();
	}
	return result;
}

// 仅依据学号查找节点
Node* StudentList::find_id(ll id)
{
	Node* current = head;
	while (current)
	{
		if (current->Student_number == id)
		{
			return current;									// 找到匹配学号的节点，返回该节点
		}
		current = current->next;							// 移动到下一个节点
	}
	return nullptr;											// 未找到返回空指针
}

//判断链表是否为空(false:空链表并输出提示；true:含有数据的链表)
bool StudentList::List_is_none()
{
	if (head == nullptr)
	{
		red_print();
		cout << "ERROR：链表为空！\n\n";
		white_print();
		return false;
	}
	return true;
}


// 修改学生信息
void StudentList::change_informaton(ll id)
{
	if (List_is_none() == false)
	{
		return ;
	}
	Node* node = find_id(id);						// 查找指定学号的学生节点
	if (node != nullptr)							// 找到节点
	{
		cout << "该学生当前数据为：\n" << *node;
		if (Change_Data(*node))						// 调用 Change_Data 函数修改信息，成功则继续
		{
			node->Calculate_Test_average_score();	// 重新计算考试平均成绩
			node->Calculate_Comprehensive_assessment_total_score();	// 重新计算综合测评总分
			Calculate_Score_Ranking();
			saveToFile(intermediate_filename);							// 保存修改后的数据到文件
		}
	}
	else
	{
		red_print();
		cout << "ERROR：未找到该学号学生！\n\n";	// 未找到提示
		white_print();
	}
}

// 删除学生
void StudentList::remove(ll id)
{
	Node* current = head;
	Node* prev = nullptr;												// 用于记录当前节点的前一个节点
	if (current == nullptr)
	{
		red_print();
		cout << "ERROR：链表为空！\n\n";
		white_print();
		return;
	}
	bool is_change = false;
	while (current != nullptr)											// 遍历链表
	{
		if (current->Student_number == id)								// 查找学号
		{
			yellow_print();
			cout << "请确认是否删除以下学生？\n";
			white_print();
			cout << *current;
			yellow_print();
			cout << "Y: 是\tN：否\n请输入：";	// 显示该学生信息，确认是否删除
			white_print();

			char confirm;
			cin >> confirm;
			while (true)
			{
				if (confirm == 'y' || confirm == 'Y')					// 确认删除
				{
					if (prev != nullptr)
					{
						prev->next = current->next;						// 前一个节点跳过当前节点
					}
					else
					{
						head = current->next;							// 如果是头节点，头指针后移
					}
					delete current;										// 删除当前节点
					green_print();
					cout << "已删除学号为" << id << "的学生！\n\n";
					white_print();
					--num;
					Calculate_Score_Ranking();
					is_change = true;
					saveToFile(intermediate_filename);										// 保存删除操作后的链表数据到文件
					return;
				}
				else if(confirm == 'n' || confirm == 'N')
				{
					yellow_print();
					cout << "删除操作已终止！\n\n";
					white_print();
					return;
				}
				printError("操作序号超出范围", false);
				yellow_print();
				cout << "请确认是否删除该学生？\nY: 是\tN：否\n请输入：";
				white_print();
				cin >> confirm;
			}
			break;
		}
		prev = current;													// 记录当前节点为前一个节点
		current = current->next;										// 移动到下一个节点
	}
	if (is_change != true)												// 删除结果提示
	{
		red_print();
		cout << "ERROR：未找到该学号学生！\n\n";
		white_print();
	}
}

// 保存到文件
void StudentList::saveToFile(const string& filename)
{
	ofstream fout(filename);						// 以输出模式打开文件
	if (fout)
	{	// 文件打开成功
		Node* current = head;						// 从链表头部开始
		while (current != nullptr)					// 遍历链表
		{
			fout << "学号\t\t\t" << current->Student_number << "\n"
				<< "姓名\t\t\t" << current->Name << "\n"
				<< "性别\t\t\t" << current->Gender << "\n"
				<< "家庭住址\t\t" << current->Address << "\n"
				<< "联系电话\t\t" << current->Contact_number << "\n"
				<< "语文成绩\t\t" << setprecision(2) << fixed << current->Chinese << "\n"
				<< "数学成绩\t\t" << setprecision(2) << fixed << current->Math << "\n"
				<< "外语成绩\t\t" << setprecision(2) << fixed << current->English << "\n"
				<< "考试平均成绩\t" << setprecision(2) << fixed << current->Test_average_score << "\n"
				<< "考试名次\t\t" << current->Test_ranking << "\n"
				<< "同学互评分\t" << setprecision(2) << fixed << current->Students_rate_each_other << "\n"
				<< "品德成绩\t\t" << setprecision(2) << fixed << current->Moral_score << "\n"
				<< "任课教师评分\t" << setprecision(2) << fixed << current->Subject_teacher_scores << "\n"
				<< "综合测评总分\t" << setprecision(2) << fixed << current->Comprehensive_assessment_total_score << "\n"
				<< "综合测评名次\t" << current->Comprehensive_assessment_ranking << "\n\n";
			current = current->next;				// 移动到下一个节点
		}
		fout.close();								// 关闭文件
	}
	else
	{
		red_print();
		cout << "ERROR：<" << filename << ">文件保存失败！\n";	// 文件打开失败提示
		white_print();
	}
}


//// 从文件加载数据
//void StudentList::loadFromFile()
//{
//	clear();							// 先清空现有链表数据
//	ifstream fin(in_filename);			// 以输入模式打开文件
//	if (fin)
//	{	// 文件打开成功
//		ll student_number, fail_num = 0;
//		string name, gender, address, contact_number;
//		lb chinese, math, english, students_rate, moral, teacher;
//		// 按文件存储格式读取数据
//		while (fin >> student_number >> name >> gender >> address >> contact_number >> chinese >> math >> english >> students_rate >> moral >> teacher)
//		{
//			Student s(student_number, name, gender, address, contact_number, chinese, math, english, students_rate, moral, teacher);	// 创建学生对象
//			if (insert(s, true) == -1)				// 将学生插入链表
//			{
//				++fail_num;
//			}
//		}
//		green_print();
//		cout << "<" << in_filename << ">文件读取完毕，共[ " << num << " ]个学生数据读取成功，";
//		red_print();
//		cout << "共[ " << fail_num << " ]个学生数据读取失败\n\n";
//		white_print();
//		fin.close();	// 关闭文件
//	}
//	else
//	{
//		red_print();
//		cout << "ERROR：<" << in_filename << ">文件不存在，请新建文件！\n";	// 文件不存在提示
//		white_print();
//	}
//}

// 从文件加载数据（使用string但保持基础特性）
void StudentList::loadFromFile()
{
	clear(); // 清空现有数据
	ifstream fin(in_filename);
	if (!fin)
	{
		red_print();
		cout << "ERROR：<" << in_filename << ">文件不存在，请新建文件！\n";
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

		// 按空格分割字段
		while (ss >> field)
		{
			parts.push_back(field);
		}

		if (parts.size() != 11)
		{
			red_print();
			cout << "行[" << line_num<< "]格式错误：必须包含11个字段信息，实际有" << parts.size() << "个\n";
			white_print();
			fail_num++;
			continue;
		}

		Student new_student;
		bool valid = true;

		// 1. 学号（必须为数字）
		if (string_judge_number(parts[0]) == false)
		{
			red_print();
			cout << "行[" << line_num << "]学号非法(存在除数字之外的字符)：" << parts[0] << "\n";
			white_print();
			valid = false;
			++fail_num;
			continue;
		}
		else
		{
			new_student.Student_number = atoll(parts[0].c_str());
		}

		// 2. 性别（仅限男/女）
		if (parts[2] != "男" && parts[2] != "女")
		{
			red_print();
			cout << "行[" << line_num << "]性别非法(存在除\"男\"和\"女\"之外的字符)：" << parts[2] << "\n";
			white_print();
			valid = false;
			++fail_num;
			continue;
		}
		else
		{
			new_student.Gender = parts[2];
		}

		// 3. 成绩字段（转换为数字并检查范围）
		for (int i = 5; i <= 10; i++)
		{
			char* endptr;
			double score = strtod(parts[i].c_str(), &endptr);			// 字符串转换long double

			if (*endptr != '\0' || score < 0 || score > 100)
			{
				red_print();
				cout << "行[" << line_num << "]成绩非法(存在除数字之外的字符或数值不符合100分制)：" << parts[i] << "\n";
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

		// 其他字段
		new_student.Name = parts[1];
		new_student.Address = parts[3];
		if (string_judge_number(parts[4]) == false)
		{
			red_print();
			cout << "行[" << line_num << "]联系电话非法(存在除数字之外的字符)：" << parts[4] << "\n";
			white_print();
			valid = false;
			++fail_num;
			continue;
		}
		else
		{
			new_student.Contact_number = parts[4];
		}

		// 插入合法数据
		if (valid == true)
		{
			new_student.Calculate_Comprehensive_assessment_total_score();
			if (insert(new_student, true) == -1)
			{
				++fail_num;
				red_print();
				cout << "行[" << line_num<< "]学号重复，已跳过\n";
				white_print();
			}
		}
	}

	fin.close();
	green_print();
	cout << "<" << in_filename << ">文件读取完毕，共[ " << num << " ]个有效数据行，";
	red_print();
	cout << "共[ " << fail_num << " ]个无效数据行\n\n";
	white_print();
	Calculate_Score_Ranking();
	saveToFile(intermediate_filename);
}

// 输出所有学生信息
void StudentList::displayAll()
{
	Node* current = head;	// 从链表头部开始
	if (current == nullptr)
	{
		red_print();
		cout << "ERROR：链表为空！\n\n";
		white_print();
		return;
	}
	else
	{
		green_print();
		cout << "以下为当前所有学生数据：\n\n";
		white_print();
	}
	while (current)
	{	// 遍历链表
		current->Message_print();	// 调用学生对象的信息显示函数
		current = current->next;	// 移动到下一个节点
	}
	green_print();
	cout << "共[ " << num << " ]个学生数据\n\n";
	white_print();
	saveToFile(intermediate_filename);
}

// 学号排序，true：升序排列（默认）；false：降序排列
bool StudentList::id_sort(bool sx)
{
	// 处理边界情况：如果链表为空或只有一个节点，无需排序
	if (head == nullptr || num <= 1)
	{
		return true;
	}

	bool swapped;				// 标记本轮是否发生交换
	bool is_need;
	Node* current;				// 当前比较的第一个节点
	Node* current_next;			// 当前比较的第二个节点（current的下一个节点）
	Node* prev1 = nullptr;		// current的前驱节点


	for (int i = 0; i < num - 1; i++)	// 冒泡排序
	{
		swapped = false;		// 重置交换标记
		current = head;			// 每轮从头开始遍历
		prev1 = nullptr;		// 初始化前驱节点

		// 确保当前节点和下一个节点都不为空
		while (current != nullptr && current->next != nullptr)
		{
			current_next = current->next; // 当前比较的第二个节点

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
				// 交换节点：调整前驱节点的指针
				if (prev1 != nullptr)
				{
					prev1->next = current_next; // 前驱节点指向current_next
				}
				else
				{
					// 如果prev为空，说明当前交换的是头节点，需要更新head
					head = current_next;
				}

				Node* temp = current_next->next;	// 保存current_next的下一个节点，防止断链

				// 完成节点交换：
				// 1. current_next的next指向current
				// 2. current的next指向原current_next的next
				current_next->next = current;
				current->next = temp;

				prev1 = current_next;	// 更新prev：由于current_next已移到current的位置，prev应指向current_next

				swapped = true; // 标记发生了交换

				// 注意：这里不能直接移动current，因为current已经被交换到后面去了
				// 所以通过continue跳过循环末尾的current移动操作
				continue;
			}

			// 如果没有交换，正常移动prev和current指针
			prev1 = current;
			current = current->next;
		}

		// 如果本轮没有发生交换，说明链表已经有序，提前结束排序
		if (swapped == false)
		{
			break;
		}
	}
	return true; // 排序成功完成
}

// 考试平均成绩排序，true：升序排列（默认）；false：降序排列
bool StudentList::test_average_score_sort(bool sx)
{
	// 处理边界情况：如果链表为空或只有一个节点，无需排序
	if (head == nullptr || num <= 1)
	{
		return true;
	}

	bool swapped;				// 标记本轮是否发生交换
	bool is_need;
	Node* current;				// 当前比较的第一个节点
	Node* current_next;			// 当前比较的第二个节点（current的下一个节点）
	Node* prev = nullptr;		// current的前驱节点

	for (int i = 0; i < num - 1; i++)	// 冒泡排序
	{
		swapped = false;		// 重置交换标记
		current = head;			// 每轮从头开始遍历
		prev = nullptr;			// 初始化前驱节点

		// 确保当前节点和下一个节点都不为空
		while (current != nullptr && current->next != nullptr)
		{
			current_next = current->next; // 当前比较的第二个节点

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
				// 交换节点：调整前驱节点的指针
				if (prev != nullptr)
				{
					prev->next = current_next; // 前驱节点指向current_next
				}
				else
				{
					head = current_next;		// 如果prev为空，说明当前交换的是头节点，需要更新head
				}

				Node* temp = current_next->next;// 保存current_next的下一个节点，防止断链

				// 完成节点交换：
				current_next->next = current;	// 1. current_next的next指向current
				current->next = temp;			// 2. current的next指向原current_next的next
				prev = current_next;			// 3. 更新prev：由于current_next已移到current的位置，因此prev应指向current_next
				swapped = true;					// 标记发生了交换

				// 注意：这里不能直接移动current，因为current已经被交换到后面去了，所以通过continue跳过循环末尾的current移动操作
				continue;
			}

			// 如果没有交换，正常移动prev和current指针
			prev = current;
			current = current->next;
		}

		// 如果本轮没有发生交换，说明链表已经有序，提前结束排序
		if (swapped == false)
		{
			break;
		}
	}
	return true; // 排序成功完成
}

// 综合测评总分排序，true：升序排列（默认）；false：降序排列
bool StudentList::comprehensive_assessment_total_score_sort(bool sx)
{
	// 处理边界情况：如果链表为空或只有一个节点，无需排序
	if (head == nullptr || num <= 1)
	{
		return true;
	}

	bool swapped;				// 标记本轮是否发生交换
	bool is_need;
	Node* current;				// 当前比较的第一个节点
	Node* current_next;			// 当前比较的第二个节点（current的下一个节点）
	Node* prev = nullptr;		// current的前驱节点
	
	for (int i = 0; i < num - 1; i++)		// 冒泡排序
	{
		swapped = false;					// 重置交换标记
		current = head;						// 每轮从头开始遍历
		prev = nullptr;						// 初始化前驱节点

		// 确保当前节点和下一个节点都不为空
		while (current != nullptr && current->next != nullptr)
		{
			current_next = current->next; // 当前比较的第二个节点

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
				// 交换节点：调整前驱节点的指针
				if (prev != nullptr)
				{
					prev->next = current_next; // 前驱节点指向current_next
				}
				else
				{
					// 如果prev为空，说明当前交换的是头节点，需要更新head
					head = current_next;
				}

				Node* temp = current_next->next;	// 保存current_next的下一个节点，防止断链

				// 完成节点交换：
				// 1. current_next的next指向current
				// 2. current的next指向原current_next的next
				current_next->next = current;
				current->next = temp;

				// 更新prev：由于current_next已移到current的位置，prev应指向current_next
				prev = current_next;

				swapped = true; // 标记发生了交换

				// 注意：这里不能直接移动current，因为current已经被交换到后面去了
				// 所以通过continue跳过循环末尾的current移动操作
				continue;
			}

			// 如果没有交换，正常移动prev和current指针
			prev = current;
			current = current->next;
		}

		// 如果本轮没有发生交换，说明链表已经有序，提前结束排序
		if (swapped == false)
		{
			break;
		}
	}
	return true; // 排序成功完成
}

// 计算考试平均成绩排名
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

// 计算综合测评总分排名
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

// 排名统一计算
void StudentList::Calculate_Score_Ranking()
{
	Calculate_Test_ranking();
	Calculate_Comprehensive_assessment_total_score();
	id_sort();
}

// 输出该门课所有学生的成绩
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
		std::cout << "学号\t\t" << current->Student_number << "\n";
		std::cout << "姓名\t\t" << current->Name << "\n";

		fout << "学号\t\t\t" << current->Student_number << "\n"
			<< "姓名\t\t\t" << current->Name << "\n"
			<< Data_list_chinese[sub] << '\t';

		switch (sub)
		{
		case 6:

			score_print("语文成绩", current->Chinese);
			if (fout_flag == true)
			{
				fout << current->Chinese;
			}
			break;
		case 7:
			score_print("数学成绩", current->Math);
			if (fout_flag == true)
			{
				fout << current->Math;
			}
			break;
		case 8:
			score_print("外语成绩", current->English);
			if (fout_flag == true)
			{
				fout << current->English;
			}
			break;
		case 9:
			score_print("考试平均成绩", current->Test_average_score);
			if (fout_flag == true)
			{
				fout << current->Test_average_score;
			}
			break;
		case 11:
			score_print("同学互评分", current->Students_rate_each_other);
			if (fout_flag == true)
			{
				fout << current->Students_rate_each_other;
			}
			break;
		case 12:
			score_print("品德成绩", current->Moral_score);
			if (fout_flag == true)
			{
				fout << current->Moral_score;
			}
			break;
		case 13:
			score_print("任课教师评分", current->Subject_teacher_scores);
			if (fout_flag == true)
			{
				fout << current->Subject_teacher_scores;
			}
			break;
		case 14:
			score_print("综合测评总分", current->Comprehensive_assessment_total_score);
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
		cout << "所有学生的" << Data_list_chinese[sub] << "成绩已写入<" << intermediate_filename << ">文件\n\n";
		white_print();
		fout.close();
	}
}

// 精确查找
Node** StudentList::precise_search()
{
	if (List_is_none() == false)
	{
		return nullptr;
	}

	int position;
	cout << "请输入你想精确查找的信息选项：\n";
	for (int i = 0; i < 15; i++)
	{
		cout << setw(2) << setfill('0') << i+1;
		cout << ". " << Data_list_chinese[i] << '\n';
	}
	cout << "00. 终止精确信息查找操作\n请输入选项序号：";
	cin >> position;
	while (position > 15 || position < 0)
	{
		printError("选项序号超出范围", false);
		cout << "请再次输入你想精确查找的信息选项序号：";
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
		cout << "请输入想精确查找的" << Data_list_chinese[position-1] << "数据：";
		cin >> data;
		switch (position)
		{
		case 1:
		{
			while (string_judge_number(data) == false)
			{
				printError("学号不能包含字符(\"-\",\"/\")", false);
				cout << "请输入想精确查找的数字学号：";
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
						cout << "已根据该学号信息找到以下学生：\n";
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
						cout << "已根据该姓名信息找到以下学生：\n";
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
			while (!(data == "男" || data == "女"))
			{
				printError("性别仅包含\"男\"或\"女\"", false);
				cout << "请输入想精确查找的" << Data_list_chinese[position] << "数据：";
				cin >> data;
			}
			while (current != nullptr)
			{
				if (current->Gender == data)
				{
					if (find_num == 0)
					{
						green_print();
						cout << "已根据该性别信息找到以下学生：\n";
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
						cout << "已根据该家庭住址信息找到以下学生：\n";
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
				printError("联系电话不能包含字符(\"-\",\"/\")", false);
				cout << "请输入想精确查找的" << Data_list_chinese[position] << "数据：";
				cin >> data;
			}
			while (current != nullptr)
			{
				if (current->Contact_number == data)
				{
					if (find_num == 0)
					{
						green_print();
						cout << "已根据该联系电话信息找到以下学生：\n";
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
			cout << "请选择查找选项：\n1.所有学生的" << Data_list_chinese[position - 1] << "\n2.输入" << Data_list_chinese[position - 1] << "以查找对应学生\n请输入：";
			int numb;
			cin >> numb;
			while (numb < 1 || numb>2)
			{
				printError("选项序号超出范围", false);
				cout << "请再次输入你想进行的查找选项序号：";
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
			inputScore("想精确查找的语文", score, false);
			while (current != nullptr)
			{
				if (current->Chinese == score)
				{
					if (find_num == 0)
					{
						green_print();
						cout << "已根据该语文成绩信息找到以下学生：\n";
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
			inputScore("想精确查找的数学", score, false);
			while (current != nullptr)
			{
				if (current->Math == score)
				{
					if (find_num == 0)
					{
						green_print();
						cout << "已根据该数学成绩信息找到以下学生：\n";
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
			inputScore("想精确查找的外语", score, false);
			while (current != nullptr)
			{
				if (current->English == score)
				{
					if (find_num == 0)
					{
						green_print();
						cout << "已根据该外语成绩信息找到以下学生：\n";
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
			inputScore("想精确查找的考试平均", score, false);
			while (current != nullptr)
			{
				if (score_round(current->Test_average_score) == score)
				{
					if (find_num == 0)
					{
						green_print();
						cout << "已根据该考试平均成绩信息找到以下学生：\n";
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
			cout << "请输入想精确查找的考试名次数据：";
			cin >> ranking;
			while (ranking <= 0)
			{
				printError("名次不能为小于等于0的数", false);
				cout << "请输入想精确查找的考试名次数据：";
				cin >> ranking;
			}
			while (current != nullptr)
			{
				if (current->Test_ranking == ranking)
				{
					if (find_num == 0)
					{
						green_print();
						cout << "已根据该考试名次信息找到以下学生：\n";
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
			inputScore("想精确查找的同学互评分", score, false);
			while (current != nullptr)
			{
				if (current->Students_rate_each_other == score)
				{
					if (find_num == 0)
					{
						green_print();
						cout << "已根据该同学互评分信息找到以下学生：\n";
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
			inputScore("想精确查找的品德", score, false);
			while (current != nullptr)
			{
				if (current->Moral_score == score)
				{
					if (find_num == 0)
					{
						green_print();
						cout << "已根据该品德信息找到以下学生：\n";
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
			inputScore("想精确查找的任课教师评分", score, false);
			while (current != nullptr)
			{
				if (current->Subject_teacher_scores == score)
				{
					if (find_num == 0)
					{
						green_print();
						cout << "已根据该任课教师评分信息找到以下学生：\n";
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
			inputScore("想精确查找的综合测评总分", score, false);
			while (current != nullptr)
			{
				if (score_round(current->Comprehensive_assessment_total_score) == score)
				{
					if (find_num == 0)
					{
						green_print();
						cout << "已根据该综合测评总分信息找到以下学生：\n";
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
			cout << "请输入想精确查找的综合测评名次数据：";
			cin >> ranking;
			while (ranking <= 0)
			{
				printError("名次不能为小于等于0的数", false);
				cout << "请输入想精确查找的综合测评名次数据：";
				cin >> ranking;
			}
			while (current != nullptr)
			{
				if (current->Comprehensive_assessment_ranking == ranking)
				{
					if (find_num == 0)
					{
						green_print();
						cout << "已根据该综合测评名次信息找到以下学生：\n";
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
		cout << "未找到与该<" << Data_list_chinese[position - 1] << ">信息相匹配的学生！\n\n";
		white_print();
		return nullptr;
	}
	else
	{
		green_print();
		cout << "根据该<" << Data_list_chinese[position - 1] << ">信息，共找到[ " << find_num << " ]个学生信息\n\n";
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
			fout << "根据输入的<" << Data_list_chinese[position - 1] << ">信息所精确查找到的学生数据：\n\n";
			for (int i = 0; i < find_num; i++)
			{
				if (result[i] != nullptr)
				{
					fout << "学号\t\t\t" << result[i]->Student_number << "\n"
						<< "姓名\t\t\t" << result[i]->Name << "\n"
						<< "性别\t\t\t" << result[i]->Gender << "\n"
						<< "家庭住址\t\t" << result[i]->Address << "\n"
						<< "联系电话\t\t" << result[i]->Contact_number << "\n"
						<< "语文成绩\t\t" << setprecision(2) << fixed << result[i]->Chinese << "\n"
						<< "数学成绩\t\t" << setprecision(2) << fixed << result[i]->Math << "\n"
						<< "外语成绩\t\t" << setprecision(2) << fixed << result[i]->English << "\n"
						<< "考试平均成绩\t" << setprecision(2) << fixed << result[i]->Test_average_score << "\n"
						<< "考试名次\t\t" << result[i]->Test_ranking << "\n"
						<< "同学互评分\t" << setprecision(2) << fixed << result[i]->Students_rate_each_other << "\n"
						<< "品德成绩\t\t" << setprecision(2) << fixed << result[i]->Moral_score << "\n"
						<< "任课教师评分\t" << setprecision(2) << fixed << result[i]->Subject_teacher_scores << "\n"
						<< "综合测评总分\t" << setprecision(2) << fixed << result[i]->Comprehensive_assessment_total_score << "\n"
						<< "综合测评名次\t" << result[i]->Comprehensive_assessment_ranking << "\n\n";
				}
				else
				{
					fout << "result[i] == nullptr\n";
				}
			}
			fout << "根据该<" << Data_list_chinese[position - 1] << ">信息，共找到[ " << find_num << " ]个学生信息\n\n";
			fout.close();
		}
		else
		{
			red_print();
			cout << "ERROR：<" << intermediate_filename << ">文件保存失败！\n\n";	// 文件打开失败提示
			white_print();
		}

		return result;
	}
}


// 字符串转换函数
template<typename T>
string turn_string(const T &data, int set = 2)
{
	stringstream data1;
	data1 << setprecision(set) << fixed << data;
	string data2 = data1.str();
	return data2;
}

// 模糊查找判定函数
template<typename T>
bool Node::is_search(const string &data, const T &source)
{
	string source_data = turn_string(source);
	return (source_data.find(data) != string::npos);
}

// 针对数值类型的特化版本，确保转换精度
template<>
bool Node::is_search<long double>(const string &data, const long double &source)
{
	stringstream ss;
	ss << setprecision(2) << fixed << source;									// 确保与显示精度一致
	string source_data = ss.str();
	return (source_data.find(data) != string::npos);
}

// 模糊查找输出辅助函数
template<typename T>
void Node::fuzzy_search_display(const string &field_name, const T &value, const string &search_data)
{
	cout << field_name << "\t";
	if (field_name=="学号"|| field_name == "姓名"|| field_name == "性别")
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

// 模糊查找输出函数
void Node::fuzzy_search_display(const string &search_data)
{
	fuzzy_search_display("学号", Student_number, search_data);
	fuzzy_search_display("姓名", Name, search_data);
	fuzzy_search_display("性别", Gender, search_data);
	fuzzy_search_display("家庭住址", Address, search_data);
	fuzzy_search_display("联系电话", Contact_number, search_data);
	fuzzy_search_display("语文成绩", Chinese, search_data);
	fuzzy_search_display("数学成绩", Math, search_data);
	fuzzy_search_display("外语成绩", English, search_data);
	fuzzy_search_display("考试平均成绩", Test_average_score, search_data);
	fuzzy_search_display("考试名次", Test_ranking, search_data);
	fuzzy_search_display("同学互评分", Students_rate_each_other, search_data);
	fuzzy_search_display("品德成绩", Moral_score, search_data);
	fuzzy_search_display("任课教师评分", Subject_teacher_scores, search_data);
	fuzzy_search_display("综合测评总分", Comprehensive_assessment_total_score, search_data);
	fuzzy_search_display("综合测评名次", Comprehensive_assessment_ranking, search_data);
	cout << "\n";
}

// 模糊查找
Node** StudentList::fuzzy_search()
{
	if (List_is_none() == false)
	{
		return nullptr;
	}

	cout << "请输入想要模糊查找的信息：";
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
			// 学号，姓名
			current->is_search(data, current->Student_number) == true || current->is_search(data, current->Name) == true
			// 性别，家庭住址
			|| current->is_search(data, current->Gender) == true || current->is_search(data, current->Address) == true
			// 联系电话
			|| current->is_search(data, current->Contact_number) == true
			// 语文成绩，数学成绩，外语成绩
			|| current->is_search(data, current->Chinese) == true || current->is_search(data, current->Math) == true || current->is_search(data, current->English) == true
			// 考试平均成绩，考试名次
			|| current->is_search(data, current->Test_average_score) == true || current->is_search(data, current->Test_ranking) == true
			// 同学互评分，品德成绩，任课教师评分
			|| current->is_search(data, current->Students_rate_each_other) == true || current->is_search(data, current->Moral_score) == true || current->is_search(data, current->Subject_teacher_scores) == true
			// 综合测评总分，综合测评名次
			|| current->is_search(data, current->Comprehensive_assessment_total_score) == true || current->is_search(data, current->Comprehensive_assessment_ranking) == true;
		if (is_match == true)
		{
			if (find_num == 0)
			{
				green_print();
				cout << "已根据该<" << data << ">信息找到以下学生：\n";
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
		cout << "未找到与该<" << data << ">数据相关的学生！\n\n";
		white_print();
		return nullptr;
	}
	else
	{
		green_print();
		cout << "根据该<" << data << ">数据，共找到[ " << find_num << " ]个相关学生信息\n\n";
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
		fout << "根据输入的<" << data << ">数据所模糊查找到的相关学生数据：\n\n";
		for (int i = 0; i < find_num; i++)
		{
			if (result[i] != nullptr)
			{
				fout << "学号\t\t\t" << result[i]->Student_number << "\n"
					<< "姓名\t\t\t" << result[i]->Name << "\n"
					<< "性别\t\t\t" << result[i]->Gender << "\n"
					<< "家庭住址\t\t" << result[i]->Address << "\n"
					<< "联系电话\t\t" << result[i]->Contact_number << "\n"
					<< "语文成绩\t\t" << setprecision(2) << fixed << result[i]->Chinese << "\n"
					<< "数学成绩\t\t" << setprecision(2) << fixed << result[i]->Math << "\n"
					<< "外语成绩\t\t" << setprecision(2) << fixed << result[i]->English << "\n"
					<< "考试平均成绩\t" << setprecision(2) << fixed << result[i]->Test_average_score << "\n"
					<< "考试名次\t\t" << result[i]->Test_ranking << "\n"
					<< "同学互评分\t" << setprecision(2) << fixed << result[i]->Students_rate_each_other << "\n"
					<< "品德成绩\t\t" << setprecision(2) << fixed << result[i]->Moral_score << "\n"
					<< "任课教师评分\t" << setprecision(2) << fixed << result[i]->Subject_teacher_scores << "\n"
					<< "综合测评总分\t" << setprecision(2) << fixed << result[i]->Comprehensive_assessment_total_score << "\n"
					<< "综合测评名次\t" << result[i]->Comprehensive_assessment_ranking << "\n\n";
			}
			else
			{
				fout << "result[i] == nullptr\n";
			}
		}
		fout << "根据该<" << data << ">数据，共找到[ " << find_num << " ]个相关学生信息\n\n";
		fout.close();
	}
	else
	{
		red_print();
		cout << "ERROR：<" << intermediate_filename << ">文件保存失败！\n\n";	// 文件打开失败提示
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