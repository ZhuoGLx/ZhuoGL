//Student.cpp

#include"Student.h"

// 信息列表[ 0"Student_number",1"Name",2"Gender",3"Address",4"Contact_number",5"Chinese",6"Math",7"English",8"Test_average_score",9"Test_ranking",10"Students_rate_each_other",11"Moral_score",12"Subject_teacher_scores",13"Comprehensive_assessment_total_score",14"Comprehensive_assessment_ranking"]
string Data_list[15] = { "Student_number","Name","Gender","Address","Contact_number","Chinese","Math","English","Test_average_score","Test_ranking","Students_rate_each_other","Moral_score","Subject_teacher_scores","Comprehensive_assessment_total_score","Comprehensive_assessment_ranking" };
string Data_list_chinese[15] = { "学号","姓名","性别","家庭住址","联系电话","语文成绩","数学成绩","外语成绩","考试平均成绩","考试名次","同学互评分","品德成绩","任课教师评分","综合测评总分","综合测评名次" };

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

string in_filename = "学生数据.txt";
string out_filename = "学生数据处理结果.txt";
string intermediate_filename = "学生数据处理中间文件.txt";

// 红色显示函数
void red_print()
{
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
}

// 绿色显示函数
void green_print()
{
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

// 黄色显示函数
void yellow_print()
{
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

// 蓝色显示函数
void blue_print()
{
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

// 原色（白色）显示函数
void white_print()
{
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

// 报错辅助函数
void printError(const string& a, bool flag)
{
	red_print();
	if (a != " ")
	{
		cout << "ERROR：输入错误(错误原因：" << a << ")，请重新输入！\n";
	}
	else
	{
		cout << "ERROR：输入错误，请重新输入！\n";
	}
	if (flag == true)
	{
		cout << '\n';
	}
	white_print();
}

// 判断字符串是否全为数字
bool string_judge_number(const string a)
{
	for (int i = 0; i < (int)a.size(); i++)
	{
		if (a[i]<'0' || a[i]>'9')
		{
			return false;
		}
	}
	return true;
}

// 返回四舍五入后的值
lb score_round(lb score)
{
	return (roundl(score * 100.0L) / 100.0L);
}


// 构造函数，头文件设置初始值
Student::Student(ll student_number,
	string name,
	string gender,
	string address,
	string contact_number,
	lb chinese,
	lb math,
	lb english,
	lb students_rate_each_other,
	lb moral_score,
	lb subject_teacher_scores) :

	Student_number(student_number),				//赋值
	Name(name),
	Gender(gender),
	Address(address),
	Contact_number(contact_number),
	Chinese(chinese),
	Math(math),
	English(english),
	Students_rate_each_other(students_rate_each_other),
	Moral_score(moral_score),
	Subject_teacher_scores(subject_teacher_scores)
{
	Calculate_Test_average_score();
	Calculate_Comprehensive_assessment_total_score();
}

// 拷贝构造函数
Student::Student(const Student& obj):
	Student_number(obj.Student_number),
	Name(obj.Name),
	Gender(obj.Gender),
	Address(obj.Address),
	Contact_number(obj.Contact_number),
	Chinese(obj.Chinese),
	Math(obj.Math),
	English(obj.English),
	Students_rate_each_other(obj.Students_rate_each_other),
	Moral_score(obj.Moral_score),
	Subject_teacher_scores(obj.Subject_teacher_scores),
	Test_average_score(obj.Test_average_score),
	Test_ranking(obj.Test_ranking),
	Comprehensive_assessment_total_score(obj.Comprehensive_assessment_total_score),
	Comprehensive_assessment_ranking(obj.Comprehensive_assessment_ranking){}

//// 学生信息输入辅助函数
//bool inputScore(const string& subject, lb& score, bool flag)	// flag默认true
//{
//	lb new_score;
//	if (flag == true)
//	{
//			if (subject == "同学互评" || subject == "任课教师评分")
//				cout << "请输入" << subject << "成绩(100分制)\t";
//			else
//				cout << "请输入" << subject << "成绩(100分制)\t\t";
//			cin >> new_score;
//			while (new_score < 0 || new_score > 100)
//			{
//				if (new_score == -1)
//				{
//					return false;
//				}
//				printError("成绩超出100分制范围", false);
//				if (subject == "同学互评" || subject == "任课教师评分")
//					cout << "请输入" << subject << "成绩(100分制)\t";
//				else
//					cout << "请输入" << subject << "成绩(100分制)\t\t";
//				cin >> new_score;
//			}
//			score = new_score;
//	}
//	else
//	{
//		cout << "请输入" << subject << "成绩(100分制)：";
//		cin >> new_score;
//
//		while (new_score < 0 || new_score > 100)
//		{
//			if (new_score == -1)
//			{
//				return false;
//			}
//			printError("成绩超出100分制范围", false);
//			cout << "请输入" << subject << "成绩(100分制)：";
//			cin >> new_score;
//		}
//		score = new_score;
//	}
//	return true;
//}

// 添加浮点数格式检查函数（允许一个小数点，不能以小数点开头/结尾）
bool is_valid_float(const string& str) {
	bool has_decimal = false;
	bool has_digit = false;
	for (size_t i = 0; i < str.size(); ++i) {
		char c = str[i];
		if (c == '.') {
			// 不允许重复小数点，或小数点在首尾位置
			if (has_decimal || i == 0 || i == str.size() - 1) return false;
			has_decimal = true;
		}
		else if (c == '+'&&i == 0)
		{
			continue;
		}
		else if (!isdigit(c)) {
			// 包含非数字字符（除小数点外）
			return false;
		}
		has_digit = true; // 至少有一个数字
	}
	return has_digit; // 必须包含至少一个数字
}

// 修改后的成绩输入函数（增加字符串数字检查）
bool inputScore(const string& subject, lb& score, bool flag) {
	string str_score; // 使用字符串接收输入

	while (true) {
		// 输出提示信息
		if (flag) {
			if (subject == "同学互评" || subject == "任课教师评分")
				cout << "请输入" << subject << "成绩(100分制)\t";
			else
				cout << "请输入" << subject << "成绩(100分制)\t\t";
		}
		else {
			cout << "请输入" << subject << "成绩(100分制)：";
		}

		cin >> str_score;

		// 处理退出指令
		if (str_score == "-1") return false;

		// 第一步：检查是否为合法数字字符串
		if (!is_valid_float(str_score)) {
			printError("成绩必须为大于等于0的有效数字(格式示例：100、99.5)", false);
			continue;
		}

		// 第二步：转换为数值并检查范围
		try {
			lb new_score = std::stold(str_score); // 使用stold进行转换

			// 检查数值范围
			if (new_score < 0 || new_score > 100) {
				printError("成绩必须在0-100分之间", false);
				continue;
			}

			score = new_score;
			return true;

		}
		catch (const std::invalid_argument&) {
			printError("无效的数字格式(不支持科学计数法)", false);
		}
		catch (const std::out_of_range&) {
			printError("数字超出长双精度范围", false);
		}
	}
}

// 具体学生信息输入(正常：true；异常(-1退出)：false)
bool Student::Set_Student()
{
	// 输入学号
	string number;
	do
	{
		cout << "请输入数字学号\t\t\t";
		cin >> number;
		if (number == "-1")
		{
			return false;
		}
		else if (string_judge_number(number) == false)
		{
			printError("学号不能包含字符(\"-\",\"/\")", false);
		}
	} while (string_judge_number(number) == false);
	Student_number = 0;
	for (int i = 0; i < (int)number.size(); i++)
	{
		Student_number = Student_number * 10 + (number[i] - '0');
	}

	// 输入姓名
	cout << "请输入姓名\t\t\t";
	cin >> Name;
	if (Name == "-1")
	{
		return false;
	}

	// 输入性别	
	do
	{
		cout << "请输入性别(\"男\"或\"女\")\t\t";
		cin >> Gender;
		if (Gender == "-1")
		{
			return false;
		}
		if (!(Gender == "男" || Gender == "女"))
		{
			printError("性别仅包含\"男\"或\"女\"", false);
		}
	} while (!(Gender == "男" || Gender == "女"));

	// 输入家庭住址
	cout << "请输入家庭住址\t\t\t";
	cin >> Address;
	if (Address == "-1")
	{
		return false;
	}

	// 输入联系电话
	do
	{
		cout << "请输入联系电话\t\t\t";
		cin >> Contact_number;
		if (Contact_number == "-1")
		{
			return false;
		}
		if (string_judge_number(Contact_number) == false)
		{
			printError("联系电话不能包含字符(\"-\",\"/\")", false);
		}
	} while (string_judge_number(Contact_number) == false);


	bool result = true;

	// 输入语文成绩
	result = inputScore("语文", Chinese);
	if (result == false)
	{
		return false;
	}

	// 输入数学成绩
	result = inputScore("数学", Math);
	if (result == false)
	{
		return false;
	}

	// 输入外语成绩
	result = inputScore("外语", English);
	if (result == false)
	{
		return false;
	}

	// 输入同学互评分
	result = inputScore("同学互评", Students_rate_each_other);
	if (result == false)
	{
		return false;
	}

	// 输入品德成绩
	result = inputScore("品德", Moral_score);
	if (result == false)
	{
		return false;
	}

	// 输入任课教师评分
	result = inputScore("任课教师评分", Subject_teacher_scores);
	if (result == false)
	{
		return false;
	}

	cout << '\n';
	
	Calculate_Comprehensive_assessment_total_score();
	Calculate_Test_average_score();

	return true;
}

// 计算考试平均成绩
void Student::Calculate_Test_average_score()
{
	Test_average_score = (Chinese + Math + English) / 3;
}

// 计算综合测评总分
void Student::Calculate_Comprehensive_assessment_total_score()
{
	Calculate_Test_average_score();
	Comprehensive_assessment_total_score = Test_average_score * 0.6 + Students_rate_each_other * 0.1 + Moral_score * 0.1 + Subject_teacher_scores * 0.2;
}

// 成绩输出颜色辅助函数
void score_print(const string& sub,lb &score)
{
	cout << sub << "\t";
	if (score < 60)
	{
		red_print();
		cout << setprecision(2) << fixed << score << '\n';
		white_print();
	}
	else if (score >= 90)
	{
		green_print();
		cout << setprecision(2) << fixed << score << '\n';
		white_print();
	}
	else
	{
		cout << setprecision(2) << fixed << score << '\n';
	}
}

// 学生信息输出
void Student::Message_print()
{
	cout << "学号\t\t" << Student_number << "\n";
	cout << "姓名\t\t" << Name << "\n";
	cout << "性别\t\t" << Gender << "\n";
	cout << "家庭住址\t" << Address << "\n";
	cout << "联系电话\t" << Contact_number << "\n";

	//cout << "语文成绩\t" << setprecision(2) << fixed << Chinese << "\n";
	//cout << "数学成绩\t" << setprecision(2) << fixed << Math << "\n";
	//cout << "外语成绩\t" << setprecision(2) << fixed << English << "\n";

	score_print("语文成绩", Chinese);
	score_print("数学成绩", Math);
	score_print("外语成绩", English);


	//cout << "考试平均成绩\t" << setprecision(2) << fixed << Test_average_score << "\n";

	score_print("考试平均成绩", Test_average_score);
	cout << "考试名次\t" << Test_ranking << "\n";

	//cout << "同学互评分\t" << setprecision(2) << fixed << Students_rate_each_other << "\n";
	//cout << "品德成绩\t" << setprecision(2) << fixed << Moral_score << "\n";
	//cout << "任课教师评分\t" << setprecision(2) << fixed << Subject_teacher_scores << "\n";

	score_print("同学互评分", Students_rate_each_other);
	score_print("品德成绩", Moral_score);
	score_print("任课教师评分", Subject_teacher_scores);

	//cout << "综合测评总分\t" << setprecision(2) << fixed << Comprehensive_assessment_total_score << "\n";

	score_print("综合测评总分", Comprehensive_assessment_total_score);
	cout << "综合测评名次\t" << Comprehensive_assessment_ranking << "\n\n";


}

// <<重载输出颜色辅助函数
void score_print_out(ostream& out, const string& subject, double score)
{
	out << subject << "\t";

	if (score < 60) {
		red_print();
		out << setprecision(2) << fixed << score << "\n";
		white_print();
	}
	else if (score >= 90) {
		green_print();
		out << setprecision(2) << fixed << score << "\n";
		white_print();
	}
	else {
		out << setprecision(2) << fixed << score << "\n";
	}
}

// <<重载输出
ostream& operator<<(ostream& out, const Student& stu) {
	out << "学号\t\t" << stu.Student_number << "\n";
	out << "姓名\t\t" << stu.Name << "\n";
	out << "性别\t\t" << stu.Gender << "\n";
	out << "家庭住址\t" << stu.Address << "\n";
	out << "联系电话\t" << stu.Contact_number << "\n";

	score_print_out(out, "语文成绩", stu.Chinese);
	score_print_out(out, "数学成绩", stu.Math);
	score_print_out(out, "外语成绩", stu.English);

	score_print_out(out, "考试平均成绩", stu.Test_average_score);
	out << "考试名次\t" << stu.Test_ranking << "\n";

	score_print_out(out, "同学互评分", stu.Students_rate_each_other);
	score_print_out(out, "品德成绩", stu.Moral_score);
	score_print_out(out, "任课教师评分", stu.Subject_teacher_scores);

	score_print_out(out, "综合测评总分", stu.Comprehensive_assessment_total_score);
	out << "综合测评名次\t" << stu.Comprehensive_assessment_ranking << "\n\n";

	return out;
}

// 修改数据
bool Change_Data(Student& stu)
{
	int position;
	bool is_change = false;
re:
	cout << "请输入你想修改的信息选项：\n";
	for (int i = 1; i < 8; i++)
	{
		cout << setw(2) << setfill('0') << i;
		cout << ". " << Data_list_chinese[i] << '\n';
	}
	for (int i = 10; i <= 12; ++i)
	{
		cout << setw(2) << setfill('0') << i - 2;
		cout << ". " << Data_list_chinese[i] << '\n';
	}
	cout << "00. 终止修改信息操作\n请输入序号：";
	cin >> position;
	while (position > 10 || position < 0)
	{
		printError("超出序号范围", false);
		cout << "请输入你想修改的信息选项序号：";
		cin >> position;
	}
	if (position == 0)
	{
		yellow_print();
		cout << "修改操作已终止！\n\n";
		white_print();
		return is_change;
	}
	if (position >= 1 && position <= 4)
	{
		string data;
		cout << "请输入新的" << Data_list_chinese[position] << "数据：";
		cin >> data;
		switch (position)
		{
		case 1:
			stu.Name = data;
			is_change = true;
			break;
		case 2:
			while(!(data == "男" || data == "女"))
			{
				printError("性别仅包含\"男\"或\"女\"", false);
				cout << "请输入新的" << Data_list_chinese[position] << "数据：";
				cin >> data;
			}
			stu.Gender = data;
			is_change = true;
			break;
		case 3:
			stu.Address = data;
			is_change = true;
			break;
		default:
			while (string_judge_number(data) == false)
			{
				printError("联系电话不能包含字符(\"-\",\"/\")", false);
				cout << "请输入新的" << Data_list_chinese[position] << "数据：";
				cin >> data;
			}
			stu.Contact_number = data;
			is_change = true;
			break;
		}
	}
	else
	{
		switch (position)
		{
		case 5:
			inputScore("新的语文", stu.Chinese, false);
			stu.Calculate_Test_average_score();
			stu.Calculate_Comprehensive_assessment_total_score();
			is_change = true;
			break;
		case 6:
			inputScore("新的数学", stu.Math, false);
			stu.Calculate_Test_average_score();
			stu.Calculate_Comprehensive_assessment_total_score();
			is_change = true;
			break;
		case 7:
			inputScore("新的外语", stu.English, false);
			stu.Calculate_Test_average_score();
			stu.Calculate_Comprehensive_assessment_total_score();
			is_change = true;
			break;
		case 8:
			inputScore("新的同学互评分", stu.Students_rate_each_other, false);
			stu.Calculate_Comprehensive_assessment_total_score();
			is_change = true;
			break;
		case 9:
			inputScore("新的品德", stu.Moral_score, false);
			stu.Calculate_Comprehensive_assessment_total_score();
			is_change = true;
			break;
		default:
			inputScore("新的任课教师评分", stu.Subject_teacher_scores, false);
			stu.Calculate_Comprehensive_assessment_total_score();
			is_change = true;
			break;
		}
	}
	if (is_change == true)
	{
		green_print();
		cout << "数据已修改！";
		yellow_print();
		cout << "是否继续修改该学生数据？\nY：是\tN：否\n请输入：";
		white_print();

		char flag;
		cin >> flag;
		while (!(flag == 'Y' || flag == 'y' || flag == 'N' || flag == 'n'))
		{
			printError("操作序号超出范围", false);
			yellow_print();
			cout << "是否继续修改该学生数据？\nY：是\tN：否\n";
			white_print();
			cin >> flag;
		}
		if (flag == 'Y' || flag == 'y')
		{
			goto re;
		}
		else
		{
			yellow_print();
			cout << "修改操作已结束！\n\n";
			white_print();
			return is_change;
		}
	}
	return is_change;
}
