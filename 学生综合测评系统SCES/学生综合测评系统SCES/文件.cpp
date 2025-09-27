#include <iostream>  // ��������������⣬���ڱ�׼�����������
#include <fstream>   // �����ļ����⣬�����ļ��Ķ�д����
#include <random>    // ������������ɿ⣬�������������
#include <string>    // �����ַ����⣬���ڴ����ַ���
#include <vector>

using namespace std;

// ���ɹ̶�λ���������
long long generateFixedDigitNumber(int digits)
{
	random_device rd;  // ��������������ӣ���֤�����
	mt19937 gen(rd()); // ʹ�� Mersenne Twister ����������������� rd ��Ϊ����
	uniform_int_distribution<> dis(0, 9); // ����һ�����ȷֲ�����Χ�� 0 �� 9

	long long n = 0;
	while (n == 0)
	{
		n= dis(gen);
	}
	for (int i = 1; i < digits; ++i)
	{
		n = n * 10 + dis(gen);
	}
	return n;
}

string generateChineseAddress()
{
	std::vector<std::string> addresses = {
		// �㽭ʡ�����У�6����
		"�㽭ʡ�����������������ֵ�",
		"�㽭ʡ�������ຼ���峣�ֵ�",
		"�㽭ʡ�����б��������˽ֵ�",
		"�㽭ʡ�������ϳ���СӪ�ֵ�",
		"�㽭ʡ�����й�����������ֵ�",
		"�㽭ʡ��������ƽ����Է�ֵ�",

		// �㽭ʡ����������6����
		"�㽭ʡ������۴�����ӹ���ֵ�",
		"�㽭ʡ������¹��������ֵ�",
		"�㽭ʡ������Խ������ɽ�ֵ�",
		"�㽭ʡ�������Ϻ�������ֵ�",
		"�㽭ʡ��������������Ȫ�ֵ�",
		"�㽭ʡ�����ĳ������нֵ�",

		// ����ʡ�ݣ�18����
		"�����к������йش�ֵ�",
		"�Ϻ����ֶ�����½����ֵ�",
		"�㶫ʡ���������������ֵ�",
		"����ʡ�Ͼ���������÷԰�´�ֵ�",
		"�Ĵ�ʡ�ɶ��н���������·�ֵ�",
		"����ʡ�人�н�����һԪ�ֵ�",
		"ɽ��ʡ��������������ͻȪ�ֵ�",
		"����ʡ�����й�¥�����ֵֽ�",
		"����ʡ�Ϸ���®������ң��ֵ�",
		"����ʡ��ɳ����´����´�ֵ�",
		"����ʡ֣������ԭ������·�ֵ�",
		"�ӱ�ʡʯ��ׯ�г����������ֵ�",
		"ɽ��ʡ̫ԭ��ӭ��������ֵ�",
		"����ʡ�����б�������Ժ�Žֵ�",
		"����ʡ�������廪����ɽ�ֵ�",
		"����ʡ�������������»�·�ֵ�",
		"����ʡ�����к�ƽ���Ϻ��ֵ�",
		"����ʡ�����г������Ϻ��ֵ�"
	};

	// �����������
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> streetDis(0, addresses.size() - 1);
	std::string address = addresses[streetDis(gen)];

	// ����������ƺţ�1 - 1000��
	std::uniform_int_distribution<> houseNumberDis(1, 1000);
	int houseNumber = houseNumberDis(gen);

	// ��ϵ�ַ��Ϣ
	return address + std::to_string(houseNumber) + "��";
}

string generatePhoneNumber() {
	// �����ֻ�����Ŷ�
	std::vector<std::string> prefixes = { "130", "131", "132", "133", "134", "135", "136", "137", "138", "139",
										 "145", "147", "150", "151", "152", "153", "155", "156", "157", "158",
										 "159", "166", "170", "171", "172", "173", "175", "176", "177", "178",
										 "180", "181", "182", "183", "184", "185", "186", "187", "188", "189",
										 "198", "199" };

	// �����������
	std::random_device rd;
	std::mt19937 gen(rd());

	// ���ѡ��һ���Ŷ�
	std::uniform_int_distribution<> prefixDis(0, prefixes.size() - 1);
	std::string prefix = prefixes[prefixDis(gen)];

	std::string phoneNumber = prefix;
	std::uniform_int_distribution<> digitDis(0, 9);
	for (int i = 0; i < 8; ++i) {
		phoneNumber += std::to_string(digitDis(gen));
	}

	return phoneNumber;
}

double generateGrade() {
	std::random_device rd;
	std::mt19937 gen(rd());
	// ��������Ƿ�Ϊ����
	std::uniform_int_distribution<> isIntegerDis(0, 1);
	bool isInteger = isIntegerDis(gen);

	if (isInteger) {
		// ���� 0 �� 100 �������ɼ�
		std::uniform_int_distribution<> intDis(0, 100);
		return static_cast<double>(intDis(gen));
	}
	else {
		// ���� 0 �� 100 �Ĵ�С���ɼ���������λС��
		std::uniform_real_distribution<> realDis(0.0, 100.0);
		double grade = realDis(gen);
		return std::round(grade * 100) / 100;
	}
}

int main()
{
	int numCount = 10; // Ҫ���ɵ������������
	//int digits = 5;    // �������λ��
	string filename = "ѧ������.txt"; // �洢��������ļ���

	string name[53] = { "��","��","��","֣","��","��","��","��","��","��","��","��","��","��","��","ʩ","��","��","��","��","��","��","κ","��","��","��","ˮ","�","��","��","л","��","��","��","��","��","��","��","��","��","��","ۺ","��","ʷ","��","��","��","Ԭ","��","³","Τ","��","��" };
	string name2[16] = { "ΰ", "��", "��", "��", "��", "ǿ", "��", "��", "��", "��", "��", "��", "��", "��", "ϼ", "��" };

	ofstream outFile(filename); // ���ļ�����д��
	if (!outFile.is_open())
	{  // ����ļ��Ƿ�ɹ���
		cerr << "�޷����ļ���" << endl;  // ��δ�ɹ��򿪣����������Ϣ
		return 1;  // �����쳣�˳������ش����� 1
	}

	for (int i = 0; i < numCount; ++i) {  // ѭ�� numCount �Σ�����ָ�������������
		//long long randomNumber = generateFixedDigitNumber(digits); // ���ú������������
		outFile << generateFixedDigitNumber(12) << ' ';  // �������д���ļ�
		string Name;
		long long randomNumber1= generateFixedDigitNumber(1) % 3;
		while (randomNumber1 == 0)
		{
			randomNumber1 = generateFixedDigitNumber(1) % 3;
		}
		long long randomNumber2 = generateFixedDigitNumber(1) % 3;
		while (randomNumber2 == 0)
		{
			randomNumber2 = generateFixedDigitNumber(1) % 3;
		}
		for (int i = 0; i < randomNumber1; i++)
		{
			Name += name[generateFixedDigitNumber(2) % 53];
		}
		for (int i = 0; i < randomNumber2; i++)
		{
			Name += name2[generateFixedDigitNumber(2) % 16];
		}
		outFile << Name << ' ';
		outFile << (generateFixedDigitNumber(1) % 2 == 1 ? "��" : "Ů") << ' ';
		outFile << (generateChineseAddress()) << ' ';
		outFile << (generatePhoneNumber());
		for (int j = 0; j < 6; ++j)
		{
			outFile << ' ' << (generateGrade());
		}
		outFile << endl;
	}

	outFile.close();  // �ر��ļ�
	cout << "[ " << numCount << " ]�����ѧ�������ѳɹ�д�� " << filename << endl;  // ����ɹ���Ϣ

	return 0;  // ���������˳������� 0
}