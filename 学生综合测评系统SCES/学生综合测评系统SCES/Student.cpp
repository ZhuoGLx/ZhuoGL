//Student.cpp

#include"Student.h"

// ��Ϣ�б�[ 0"Student_number",1"Name",2"Gender",3"Address",4"Contact_number",5"Chinese",6"Math",7"English",8"Test_average_score",9"Test_ranking",10"Students_rate_each_other",11"Moral_score",12"Subject_teacher_scores",13"Comprehensive_assessment_total_score",14"Comprehensive_assessment_ranking"]
string Data_list[15] = { "Student_number","Name","Gender","Address","Contact_number","Chinese","Math","English","Test_average_score","Test_ranking","Students_rate_each_other","Moral_score","Subject_teacher_scores","Comprehensive_assessment_total_score","Comprehensive_assessment_ranking" };
string Data_list_chinese[15] = { "ѧ��","����","�Ա�","��ͥסַ","��ϵ�绰","���ĳɼ�","��ѧ�ɼ�","����ɼ�","����ƽ���ɼ�","��������","ͬѧ������","Ʒ�³ɼ�","�ον�ʦ����","�ۺϲ����ܷ�","�ۺϲ�������" };

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

string in_filename = "ѧ������.txt";
string out_filename = "ѧ�����ݴ�����.txt";
string intermediate_filename = "ѧ�����ݴ����м��ļ�.txt";

// ��ɫ��ʾ����
void red_print()
{
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
}

// ��ɫ��ʾ����
void green_print()
{
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

// ��ɫ��ʾ����
void yellow_print()
{
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

// ��ɫ��ʾ����
void blue_print()
{
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

// ԭɫ����ɫ����ʾ����
void white_print()
{
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

// ����������
void printError(const string& a, bool flag)
{
	red_print();
	if (a != " ")
	{
		cout << "ERROR���������(����ԭ��" << a << ")�����������룡\n";
	}
	else
	{
		cout << "ERROR������������������룡\n";
	}
	if (flag == true)
	{
		cout << '\n';
	}
	white_print();
}

// �ж��ַ����Ƿ�ȫΪ����
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

// ��������������ֵ
lb score_round(lb score)
{
	return (roundl(score * 100.0L) / 100.0L);
}


// ���캯����ͷ�ļ����ó�ʼֵ
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

	Student_number(student_number),				//��ֵ
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

// �������캯��
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

//// ѧ����Ϣ���븨������
//bool inputScore(const string& subject, lb& score, bool flag)	// flagĬ��true
//{
//	lb new_score;
//	if (flag == true)
//	{
//			if (subject == "ͬѧ����" || subject == "�ον�ʦ����")
//				cout << "������" << subject << "�ɼ�(100����)\t";
//			else
//				cout << "������" << subject << "�ɼ�(100����)\t\t";
//			cin >> new_score;
//			while (new_score < 0 || new_score > 100)
//			{
//				if (new_score == -1)
//				{
//					return false;
//				}
//				printError("�ɼ�����100���Ʒ�Χ", false);
//				if (subject == "ͬѧ����" || subject == "�ον�ʦ����")
//					cout << "������" << subject << "�ɼ�(100����)\t";
//				else
//					cout << "������" << subject << "�ɼ�(100����)\t\t";
//				cin >> new_score;
//			}
//			score = new_score;
//	}
//	else
//	{
//		cout << "������" << subject << "�ɼ�(100����)��";
//		cin >> new_score;
//
//		while (new_score < 0 || new_score > 100)
//		{
//			if (new_score == -1)
//			{
//				return false;
//			}
//			printError("�ɼ�����100���Ʒ�Χ", false);
//			cout << "������" << subject << "�ɼ�(100����)��";
//			cin >> new_score;
//		}
//		score = new_score;
//	}
//	return true;
//}

// ��Ӹ�������ʽ��麯��������һ��С���㣬������С���㿪ͷ/��β��
bool is_valid_float(const string& str) {
	bool has_decimal = false;
	bool has_digit = false;
	for (size_t i = 0; i < str.size(); ++i) {
		char c = str[i];
		if (c == '.') {
			// �������ظ�С���㣬��С��������βλ��
			if (has_decimal || i == 0 || i == str.size() - 1) return false;
			has_decimal = true;
		}
		else if (c == '+'&&i == 0)
		{
			continue;
		}
		else if (!isdigit(c)) {
			// �����������ַ�����С�����⣩
			return false;
		}
		has_digit = true; // ������һ������
	}
	return has_digit; // �����������һ������
}

// �޸ĺ�ĳɼ����뺯���������ַ������ּ�飩
bool inputScore(const string& subject, lb& score, bool flag) {
	string str_score; // ʹ���ַ�����������

	while (true) {
		// �����ʾ��Ϣ
		if (flag) {
			if (subject == "ͬѧ����" || subject == "�ον�ʦ����")
				cout << "������" << subject << "�ɼ�(100����)\t";
			else
				cout << "������" << subject << "�ɼ�(100����)\t\t";
		}
		else {
			cout << "������" << subject << "�ɼ�(100����)��";
		}

		cin >> str_score;

		// �����˳�ָ��
		if (str_score == "-1") return false;

		// ��һ��������Ƿ�Ϊ�Ϸ������ַ���
		if (!is_valid_float(str_score)) {
			printError("�ɼ�����Ϊ���ڵ���0����Ч����(��ʽʾ����100��99.5)", false);
			continue;
		}

		// �ڶ�����ת��Ϊ��ֵ����鷶Χ
		try {
			lb new_score = std::stold(str_score); // ʹ��stold����ת��

			// �����ֵ��Χ
			if (new_score < 0 || new_score > 100) {
				printError("�ɼ�������0-100��֮��", false);
				continue;
			}

			score = new_score;
			return true;

		}
		catch (const std::invalid_argument&) {
			printError("��Ч�����ָ�ʽ(��֧�ֿ�ѧ������)", false);
		}
		catch (const std::out_of_range&) {
			printError("���ֳ�����˫���ȷ�Χ", false);
		}
	}
}

// ����ѧ����Ϣ����(������true���쳣(-1�˳�)��false)
bool Student::Set_Student()
{
	// ����ѧ��
	string number;
	do
	{
		cout << "����������ѧ��\t\t\t";
		cin >> number;
		if (number == "-1")
		{
			return false;
		}
		else if (string_judge_number(number) == false)
		{
			printError("ѧ�Ų��ܰ����ַ�(\"-\",\"/\")", false);
		}
	} while (string_judge_number(number) == false);
	Student_number = 0;
	for (int i = 0; i < (int)number.size(); i++)
	{
		Student_number = Student_number * 10 + (number[i] - '0');
	}

	// ��������
	cout << "����������\t\t\t";
	cin >> Name;
	if (Name == "-1")
	{
		return false;
	}

	// �����Ա�	
	do
	{
		cout << "�������Ա�(\"��\"��\"Ů\")\t\t";
		cin >> Gender;
		if (Gender == "-1")
		{
			return false;
		}
		if (!(Gender == "��" || Gender == "Ů"))
		{
			printError("�Ա������\"��\"��\"Ů\"", false);
		}
	} while (!(Gender == "��" || Gender == "Ů"));

	// �����ͥסַ
	cout << "�������ͥסַ\t\t\t";
	cin >> Address;
	if (Address == "-1")
	{
		return false;
	}

	// ������ϵ�绰
	do
	{
		cout << "��������ϵ�绰\t\t\t";
		cin >> Contact_number;
		if (Contact_number == "-1")
		{
			return false;
		}
		if (string_judge_number(Contact_number) == false)
		{
			printError("��ϵ�绰���ܰ����ַ�(\"-\",\"/\")", false);
		}
	} while (string_judge_number(Contact_number) == false);


	bool result = true;

	// �������ĳɼ�
	result = inputScore("����", Chinese);
	if (result == false)
	{
		return false;
	}

	// ������ѧ�ɼ�
	result = inputScore("��ѧ", Math);
	if (result == false)
	{
		return false;
	}

	// ��������ɼ�
	result = inputScore("����", English);
	if (result == false)
	{
		return false;
	}

	// ����ͬѧ������
	result = inputScore("ͬѧ����", Students_rate_each_other);
	if (result == false)
	{
		return false;
	}

	// ����Ʒ�³ɼ�
	result = inputScore("Ʒ��", Moral_score);
	if (result == false)
	{
		return false;
	}

	// �����ον�ʦ����
	result = inputScore("�ον�ʦ����", Subject_teacher_scores);
	if (result == false)
	{
		return false;
	}

	cout << '\n';
	
	Calculate_Comprehensive_assessment_total_score();
	Calculate_Test_average_score();

	return true;
}

// ���㿼��ƽ���ɼ�
void Student::Calculate_Test_average_score()
{
	Test_average_score = (Chinese + Math + English) / 3;
}

// �����ۺϲ����ܷ�
void Student::Calculate_Comprehensive_assessment_total_score()
{
	Calculate_Test_average_score();
	Comprehensive_assessment_total_score = Test_average_score * 0.6 + Students_rate_each_other * 0.1 + Moral_score * 0.1 + Subject_teacher_scores * 0.2;
}

// �ɼ������ɫ��������
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

// ѧ����Ϣ���
void Student::Message_print()
{
	cout << "ѧ��\t\t" << Student_number << "\n";
	cout << "����\t\t" << Name << "\n";
	cout << "�Ա�\t\t" << Gender << "\n";
	cout << "��ͥסַ\t" << Address << "\n";
	cout << "��ϵ�绰\t" << Contact_number << "\n";

	//cout << "���ĳɼ�\t" << setprecision(2) << fixed << Chinese << "\n";
	//cout << "��ѧ�ɼ�\t" << setprecision(2) << fixed << Math << "\n";
	//cout << "����ɼ�\t" << setprecision(2) << fixed << English << "\n";

	score_print("���ĳɼ�", Chinese);
	score_print("��ѧ�ɼ�", Math);
	score_print("����ɼ�", English);


	//cout << "����ƽ���ɼ�\t" << setprecision(2) << fixed << Test_average_score << "\n";

	score_print("����ƽ���ɼ�", Test_average_score);
	cout << "��������\t" << Test_ranking << "\n";

	//cout << "ͬѧ������\t" << setprecision(2) << fixed << Students_rate_each_other << "\n";
	//cout << "Ʒ�³ɼ�\t" << setprecision(2) << fixed << Moral_score << "\n";
	//cout << "�ον�ʦ����\t" << setprecision(2) << fixed << Subject_teacher_scores << "\n";

	score_print("ͬѧ������", Students_rate_each_other);
	score_print("Ʒ�³ɼ�", Moral_score);
	score_print("�ον�ʦ����", Subject_teacher_scores);

	//cout << "�ۺϲ����ܷ�\t" << setprecision(2) << fixed << Comprehensive_assessment_total_score << "\n";

	score_print("�ۺϲ����ܷ�", Comprehensive_assessment_total_score);
	cout << "�ۺϲ�������\t" << Comprehensive_assessment_ranking << "\n\n";


}

// <<���������ɫ��������
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

// <<�������
ostream& operator<<(ostream& out, const Student& stu) {
	out << "ѧ��\t\t" << stu.Student_number << "\n";
	out << "����\t\t" << stu.Name << "\n";
	out << "�Ա�\t\t" << stu.Gender << "\n";
	out << "��ͥסַ\t" << stu.Address << "\n";
	out << "��ϵ�绰\t" << stu.Contact_number << "\n";

	score_print_out(out, "���ĳɼ�", stu.Chinese);
	score_print_out(out, "��ѧ�ɼ�", stu.Math);
	score_print_out(out, "����ɼ�", stu.English);

	score_print_out(out, "����ƽ���ɼ�", stu.Test_average_score);
	out << "��������\t" << stu.Test_ranking << "\n";

	score_print_out(out, "ͬѧ������", stu.Students_rate_each_other);
	score_print_out(out, "Ʒ�³ɼ�", stu.Moral_score);
	score_print_out(out, "�ον�ʦ����", stu.Subject_teacher_scores);

	score_print_out(out, "�ۺϲ����ܷ�", stu.Comprehensive_assessment_total_score);
	out << "�ۺϲ�������\t" << stu.Comprehensive_assessment_ranking << "\n\n";

	return out;
}

// �޸�����
bool Change_Data(Student& stu)
{
	int position;
	bool is_change = false;
re:
	cout << "�����������޸ĵ���Ϣѡ�\n";
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
	cout << "00. ��ֹ�޸���Ϣ����\n��������ţ�";
	cin >> position;
	while (position > 10 || position < 0)
	{
		printError("������ŷ�Χ", false);
		cout << "�����������޸ĵ���Ϣѡ����ţ�";
		cin >> position;
	}
	if (position == 0)
	{
		yellow_print();
		cout << "�޸Ĳ�������ֹ��\n\n";
		white_print();
		return is_change;
	}
	if (position >= 1 && position <= 4)
	{
		string data;
		cout << "�������µ�" << Data_list_chinese[position] << "���ݣ�";
		cin >> data;
		switch (position)
		{
		case 1:
			stu.Name = data;
			is_change = true;
			break;
		case 2:
			while(!(data == "��" || data == "Ů"))
			{
				printError("�Ա������\"��\"��\"Ů\"", false);
				cout << "�������µ�" << Data_list_chinese[position] << "���ݣ�";
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
				printError("��ϵ�绰���ܰ����ַ�(\"-\",\"/\")", false);
				cout << "�������µ�" << Data_list_chinese[position] << "���ݣ�";
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
			inputScore("�µ�����", stu.Chinese, false);
			stu.Calculate_Test_average_score();
			stu.Calculate_Comprehensive_assessment_total_score();
			is_change = true;
			break;
		case 6:
			inputScore("�µ���ѧ", stu.Math, false);
			stu.Calculate_Test_average_score();
			stu.Calculate_Comprehensive_assessment_total_score();
			is_change = true;
			break;
		case 7:
			inputScore("�µ�����", stu.English, false);
			stu.Calculate_Test_average_score();
			stu.Calculate_Comprehensive_assessment_total_score();
			is_change = true;
			break;
		case 8:
			inputScore("�µ�ͬѧ������", stu.Students_rate_each_other, false);
			stu.Calculate_Comprehensive_assessment_total_score();
			is_change = true;
			break;
		case 9:
			inputScore("�µ�Ʒ��", stu.Moral_score, false);
			stu.Calculate_Comprehensive_assessment_total_score();
			is_change = true;
			break;
		default:
			inputScore("�µ��ον�ʦ����", stu.Subject_teacher_scores, false);
			stu.Calculate_Comprehensive_assessment_total_score();
			is_change = true;
			break;
		}
	}
	if (is_change == true)
	{
		green_print();
		cout << "�������޸ģ�";
		yellow_print();
		cout << "�Ƿ�����޸ĸ�ѧ�����ݣ�\nY����\tN����\n�����룺";
		white_print();

		char flag;
		cin >> flag;
		while (!(flag == 'Y' || flag == 'y' || flag == 'N' || flag == 'n'))
		{
			printError("������ų�����Χ", false);
			yellow_print();
			cout << "�Ƿ�����޸ĸ�ѧ�����ݣ�\nY����\tN����\n";
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
			cout << "�޸Ĳ����ѽ�����\n\n";
			white_print();
			return is_change;
		}
	}
	return is_change;
}
