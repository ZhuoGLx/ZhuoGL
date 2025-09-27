#include"StudentList.h"

// 菜单栏
int menu()
{
	cout << "┏--------- 学生综合测评系统 ---------┓\n";
	cout << "┃=============== MEMU ===============┃\n";
	cout << "┃    操作序号            操作功能    ┃\n";
	cout << "┃        1             输入学生信息  ┃\n";
	cout << "┃        2             查找学生信息  ┃\n";
	cout << "┃        3             添加学生信息  ┃\n";
	cout << "┃        4             修改学生信息  ┃\n";
	cout << "┃        5             删除学生信息  ┃\n";
	cout << "┃        6           输出全部学生信息┃\n";
	cout << "┃        ";
	red_print();
	cout << "0               结束程序";
	white_print();
	cout<<"    ┃\n";
	cout << "┗------------------------------------┛\n";
	cout << "请输入你想进行的操作序号：";
	int serial_number;
	cin >> serial_number;
	while (serial_number < 0 || serial_number > 6)
	{
		printError("操作序号超出范围", false);
		cout << "请输入你想进行的操作序号：";
		cin >> serial_number;
	}
	return serial_number;
}


int main()
{
	int cz;
	cz = menu();
	StudentList List;
	while (cz != 0)
	{
		switch (cz)
		{
		case 1:
		{
			if (List.Get_is_head() == true)
			{
				yellow_print();
				cout << "链表已有数据，";
				red_print();
					cout << "继续进行输入操作将会清空这些数据！";
				yellow_print();
				cout << "请选择是否继续进行输入操作？\nY:是（将会清空原数据以继续进行输入操作）\nP:是（将会跳转至添加学生信息数据操作以进行添加数据）\nN:否（终止输入操作）\n请输入：";
				white_print();
				char confirm;
				cin >> confirm;
				while (!(confirm == 'n' || confirm == 'N'|| confirm == 'y' || confirm == 'Y'|| confirm == 'p' || confirm == 'P'))
				{
					printError("选项序号超出范围", false);
					cout << "请再次输入选项序号：";
					cin >> confirm;
				}
				if (confirm == 'n' || confirm == 'N')
				{
					yellow_print();
					cout << "输入操作已终止！\n\n";
					white_print();
					break;
				}
				else if(confirm == 'p' || confirm == 'P')
				{
					goto insert_;
					break;
				}
			}

			cout << "请选择输入方式：\n1.自动读取文件\n2.手动输入\n";
			red_print();
			cout << "0.终止输入\n";
			white_print();
			cout<<"请输入选项序号：";
			int number;
			cin >> number;
			while (!(number >= 0 || number <= 2))
			{
				printError("选项序号超出范围", false);
				cout << "请再次输入选项序号：";
				cin >> number;
			}
			if (number == 0)
			{
				yellow_print();
				cout << "输入操作已终止！\n\n";
				white_print();
				break;
			}

			if (number == 1)
			{
				List = StudentList(true);
			}
			else
			{
				List = StudentList(false);
			}
			break;
		}
		case 2:
		{
			if (List.Get_is_head() == false)
			{
				red_print();
				cout << "ERROR：链表为空！\n\n";
				white_print();
				break;
			}
			cout << "请选择查找方式(输入序号)：\n1.精确查找\n2.模糊查找\n";
			red_print();
			cout << "0.终止查找\n";
			white_print();
			cout << "请输入选项序号：";
			int number;
			cin >> number;
			while (!(number >= 0 || number <= 2))
			{
				printError("选项序号超出范围", false);
				cout << "请再次输入选项序号：";
				cin >> number;
			}
			if (number == 0)
			{
				yellow_print();
				cout << "查找操作已终止！\n\n";
				white_print();
				break;
			}
			if (number == 1)
			{
				Node** result = List.precise_search();
				delete[] result;
			}
			else
			{
				Node** result = List.fuzzy_search();
				delete[] result;
			}
			break;
		}
		case 3:
		{
insert_:
			cout << "请输入要添加的学生的信息";
			red_print();
			cout << "(终止添加请在<任意>信息栏内输入 -1)";
			white_print();
			cout<<"：\n";
			Student new_student;
			if (new_student.Set_Student() == false)
			{
				yellow_print();
				cout << "添加操作已终止！\n\n";
				white_print();
				break;
			}
			int flag = List.insert(new_student);
			while (flag != 1)
			{
				yellow_print();
				cout << "是否重新输入学生数据以再次尝试添加学生？\nY：是\tN：否\n请输入：";
				white_print();
				string confirm;
				cin >> confirm;
				while (!(confirm == "Y" || confirm == "y" || confirm == "N" || confirm == "n"))
				{
					printError("操作序号超出范围", false);
					yellow_print();
					cout << "是否重新输入学生数据以再次尝试添加学生？\nY：是\tN：否\n请输入：";
					white_print();
					cin >> confirm;
				}
				if (confirm == "y" || confirm == "Y")
				{
					cout << "请再次输入要添加的学生的信息";
					red_print();
					cout << "(终止添加请在<任意>信息栏内输入 -1)";
					white_print();
					cout << "：\n";
					if (new_student.Set_Student() == false)
					{
						yellow_print();
						cout << "添加操作已取消！\n\n";
						white_print();
						break;
					}
					flag = List.insert(new_student);
				}
				else
				{
					yellow_print();
					cout << "添加操作已取消！\n\n";
					white_print();
					break;
				}
			}

			if (flag == 1)
			{
				yellow_print();
				cout << "是否继续进行添加操作?\nY：是\tN：否\n请输入：";
				white_print();
				string confirm;
				cin >> confirm;
				while (!(confirm == "Y" || confirm == "y" || confirm == "N" || confirm == "n"))
				{
					printError("选项序号超出范围", false);
					yellow_print();
					cout << "是否继续进行添加操作?\nY：是\tN：否\n请输入：";
					white_print();
					cin >> confirm;
				}
				if (confirm == "Y" || confirm == "y")
				{
					goto insert_;
				}
				else
				{
					yellow_print();
					cout << "添加操作已结束！\n\n";
					white_print();
					break;
				}
			}
			break;
		}
		case 4:
		{
			if (List.Get_is_head() == false)
			{
				red_print();
				cout << "ERROR：链表为空！\n\n";
				white_print();
				break;
			}
			cout << "请输入要修改信息的学生的学号";
			red_print();
			cout << "(终止修改请输入 -1)";
			white_print();
			cout << "：";
			string number;
			cin >> number;
			if (number == "-1")
			{
				yellow_print();
				cout << "修改操作已终止！\n\n";
				white_print();
				break;
			}
			while (string_judge_number(number) == false)
			{
				printError("学号不能包含字符(\"-\",\"/\")", false);
				cout << "请输入要修改信息的学生的学号";
				red_print();
				cout << "(终止修改请输入 -1)";
				white_print();
				cout << "：";
				cin >> number;
				if (number == "-1")
				{
					break;
				}
			}
			if (number == "-1")
			{
				yellow_print();
				cout << "修改操作已终止！\n\n";
				white_print();
				break;
			}
			ll student_number = 0;
			for (int i = 0; i < (int)number.size(); i++)
			{
				student_number = student_number * 10 + (number[i] - '0');
			}
			List.change_informaton(student_number);
			break;
		}
		case 5:
		{
			if (List.Get_is_head() == false)
			{
				red_print();
				cout << "ERROR：链表为空！\n\n";
				white_print();
				break;
			}
			cout << "请输入要删除信息的学生的学号";
			red_print();
			cout << "(终止删除请输入 -1)";
			white_print();
			cout << "：";
			string number;
			cin >> number;
			if (number == "-1")
			{
				yellow_print();
				cout << "删除操作已终止！\n\n";
				white_print();
				break;
			}
			while (string_judge_number(number) == false)
			{
				printError("学号不能包含字符(\"-\",\"/\")", false);
				cout << "请输入要删除信息的学生的学号";
				red_print();
				cout << "(终止删除请输入 -1)";
				white_print();
				cout << "：";
				cin >> number;
				if (number == "-1")
				{
					break;
				}
			}
			if (number == "-1")
			{
				yellow_print();
				cout << "删除操作已终止！\n\n";
				white_print();
				break;
			}
			ll student_number = 0;
			for (int i = 0; i < (int)number.size(); i++)
			{
				student_number = student_number * 10 + (number[i] - '0');
			}
			List.remove(student_number);
			break;
		}
		case 6:
		{
			if (List.List_is_none() == false)
			{
				break;
			}
			cout << "请输入输出的排序方式：\n1.按学号大小升序输出\n2.按学号大小降序输出\n3.按考试平均成绩升序（成绩分数由低到高）输出\n4.按考试平均成绩降序（成绩分数由高到低）输出\n5.按综合测评总分升序（成绩分数由低到高）输出\n6.按综合测评总分降序（成绩分数由高到低）输出\n请输入输出选项：";
			int number;
			cin >> number;
			while (!(number >= 1 && number <= 6))
			{
				printError("选项序号超出范围", false);
				cout << "请再次输入选项序号：";
				cin >> number;
			}
			switch (number)
			{
			case 1:
				List.id_sort(true);
				break;			
			case 2:
				List.id_sort(false);
				break; 
			case 3:
				List.test_average_score_sort(true);
				break; 
			case 4:
				List.test_average_score_sort(false);
				break; 
			case 5:
				List.comprehensive_assessment_total_score_sort(true);
				break; 
			case 6:
				List.comprehensive_assessment_total_score_sort(false);
				break;
			default:
				break;
			}
			List.displayAll(); 
			List.id_sort(true);
			break;
		}
		default:
			break;
		}
		cz = menu();
	}
	green_print();
	cout << "最终的学生信息处理结果已写入<" << out_filename << ">文件，程序已结束！\n";
	white_print();
}