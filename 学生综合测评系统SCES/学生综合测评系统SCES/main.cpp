#include"StudentList.h"

// �˵���
int menu()
{
	cout << "��--------- ѧ���ۺϲ���ϵͳ ---------��\n";
	cout << "��=============== MEMU ===============��\n";
	cout << "��    �������            ��������    ��\n";
	cout << "��        1             ����ѧ����Ϣ  ��\n";
	cout << "��        2             ����ѧ����Ϣ  ��\n";
	cout << "��        3             ���ѧ����Ϣ  ��\n";
	cout << "��        4             �޸�ѧ����Ϣ  ��\n";
	cout << "��        5             ɾ��ѧ����Ϣ  ��\n";
	cout << "��        6           ���ȫ��ѧ����Ϣ��\n";
	cout << "��        ";
	red_print();
	cout << "0               ��������";
	white_print();
	cout<<"    ��\n";
	cout << "��------------------------------------��\n";
	cout << "������������еĲ�����ţ�";
	int serial_number;
	cin >> serial_number;
	while (serial_number < 0 || serial_number > 6)
	{
		printError("������ų�����Χ", false);
		cout << "������������еĲ�����ţ�";
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
				cout << "�����������ݣ�";
				red_print();
					cout << "������������������������Щ���ݣ�";
				yellow_print();
				cout << "��ѡ���Ƿ�����������������\nY:�ǣ��������ԭ�����Լ����������������\nP:�ǣ�������ת�����ѧ����Ϣ���ݲ����Խ���������ݣ�\nN:����ֹ���������\n�����룺";
				white_print();
				char confirm;
				cin >> confirm;
				while (!(confirm == 'n' || confirm == 'N'|| confirm == 'y' || confirm == 'Y'|| confirm == 'p' || confirm == 'P'))
				{
					printError("ѡ����ų�����Χ", false);
					cout << "���ٴ�����ѡ����ţ�";
					cin >> confirm;
				}
				if (confirm == 'n' || confirm == 'N')
				{
					yellow_print();
					cout << "�����������ֹ��\n\n";
					white_print();
					break;
				}
				else if(confirm == 'p' || confirm == 'P')
				{
					goto insert_;
					break;
				}
			}

			cout << "��ѡ�����뷽ʽ��\n1.�Զ���ȡ�ļ�\n2.�ֶ�����\n";
			red_print();
			cout << "0.��ֹ����\n";
			white_print();
			cout<<"������ѡ����ţ�";
			int number;
			cin >> number;
			while (!(number >= 0 || number <= 2))
			{
				printError("ѡ����ų�����Χ", false);
				cout << "���ٴ�����ѡ����ţ�";
				cin >> number;
			}
			if (number == 0)
			{
				yellow_print();
				cout << "�����������ֹ��\n\n";
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
				cout << "ERROR������Ϊ�գ�\n\n";
				white_print();
				break;
			}
			cout << "��ѡ����ҷ�ʽ(�������)��\n1.��ȷ����\n2.ģ������\n";
			red_print();
			cout << "0.��ֹ����\n";
			white_print();
			cout << "������ѡ����ţ�";
			int number;
			cin >> number;
			while (!(number >= 0 || number <= 2))
			{
				printError("ѡ����ų�����Χ", false);
				cout << "���ٴ�����ѡ����ţ�";
				cin >> number;
			}
			if (number == 0)
			{
				yellow_print();
				cout << "���Ҳ�������ֹ��\n\n";
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
			cout << "������Ҫ��ӵ�ѧ������Ϣ";
			red_print();
			cout << "(��ֹ�������<����>��Ϣ�������� -1)";
			white_print();
			cout<<"��\n";
			Student new_student;
			if (new_student.Set_Student() == false)
			{
				yellow_print();
				cout << "��Ӳ�������ֹ��\n\n";
				white_print();
				break;
			}
			int flag = List.insert(new_student);
			while (flag != 1)
			{
				yellow_print();
				cout << "�Ƿ���������ѧ���������ٴγ������ѧ����\nY����\tN����\n�����룺";
				white_print();
				string confirm;
				cin >> confirm;
				while (!(confirm == "Y" || confirm == "y" || confirm == "N" || confirm == "n"))
				{
					printError("������ų�����Χ", false);
					yellow_print();
					cout << "�Ƿ���������ѧ���������ٴγ������ѧ����\nY����\tN����\n�����룺";
					white_print();
					cin >> confirm;
				}
				if (confirm == "y" || confirm == "Y")
				{
					cout << "���ٴ�����Ҫ��ӵ�ѧ������Ϣ";
					red_print();
					cout << "(��ֹ�������<����>��Ϣ�������� -1)";
					white_print();
					cout << "��\n";
					if (new_student.Set_Student() == false)
					{
						yellow_print();
						cout << "��Ӳ�����ȡ����\n\n";
						white_print();
						break;
					}
					flag = List.insert(new_student);
				}
				else
				{
					yellow_print();
					cout << "��Ӳ�����ȡ����\n\n";
					white_print();
					break;
				}
			}

			if (flag == 1)
			{
				yellow_print();
				cout << "�Ƿ����������Ӳ���?\nY����\tN����\n�����룺";
				white_print();
				string confirm;
				cin >> confirm;
				while (!(confirm == "Y" || confirm == "y" || confirm == "N" || confirm == "n"))
				{
					printError("ѡ����ų�����Χ", false);
					yellow_print();
					cout << "�Ƿ����������Ӳ���?\nY����\tN����\n�����룺";
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
					cout << "��Ӳ����ѽ�����\n\n";
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
				cout << "ERROR������Ϊ�գ�\n\n";
				white_print();
				break;
			}
			cout << "������Ҫ�޸���Ϣ��ѧ����ѧ��";
			red_print();
			cout << "(��ֹ�޸������� -1)";
			white_print();
			cout << "��";
			string number;
			cin >> number;
			if (number == "-1")
			{
				yellow_print();
				cout << "�޸Ĳ�������ֹ��\n\n";
				white_print();
				break;
			}
			while (string_judge_number(number) == false)
			{
				printError("ѧ�Ų��ܰ����ַ�(\"-\",\"/\")", false);
				cout << "������Ҫ�޸���Ϣ��ѧ����ѧ��";
				red_print();
				cout << "(��ֹ�޸������� -1)";
				white_print();
				cout << "��";
				cin >> number;
				if (number == "-1")
				{
					break;
				}
			}
			if (number == "-1")
			{
				yellow_print();
				cout << "�޸Ĳ�������ֹ��\n\n";
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
				cout << "ERROR������Ϊ�գ�\n\n";
				white_print();
				break;
			}
			cout << "������Ҫɾ����Ϣ��ѧ����ѧ��";
			red_print();
			cout << "(��ֹɾ�������� -1)";
			white_print();
			cout << "��";
			string number;
			cin >> number;
			if (number == "-1")
			{
				yellow_print();
				cout << "ɾ����������ֹ��\n\n";
				white_print();
				break;
			}
			while (string_judge_number(number) == false)
			{
				printError("ѧ�Ų��ܰ����ַ�(\"-\",\"/\")", false);
				cout << "������Ҫɾ����Ϣ��ѧ����ѧ��";
				red_print();
				cout << "(��ֹɾ�������� -1)";
				white_print();
				cout << "��";
				cin >> number;
				if (number == "-1")
				{
					break;
				}
			}
			if (number == "-1")
			{
				yellow_print();
				cout << "ɾ����������ֹ��\n\n";
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
			cout << "���������������ʽ��\n1.��ѧ�Ŵ�С�������\n2.��ѧ�Ŵ�С�������\n3.������ƽ���ɼ����򣨳ɼ������ɵ͵��ߣ����\n4.������ƽ���ɼ����򣨳ɼ������ɸߵ��ͣ����\n5.���ۺϲ����ܷ����򣨳ɼ������ɵ͵��ߣ����\n6.���ۺϲ����ֽܷ��򣨳ɼ������ɸߵ��ͣ����\n���������ѡ�";
			int number;
			cin >> number;
			while (!(number >= 1 && number <= 6))
			{
				printError("ѡ����ų�����Χ", false);
				cout << "���ٴ�����ѡ����ţ�";
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
	cout << "���յ�ѧ����Ϣ��������д��<" << out_filename << ">�ļ��������ѽ�����\n";
	white_print();
}