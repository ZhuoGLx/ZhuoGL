#include <iostream>  // 包含输入输出流库，用于标准输入输出操作
#include <fstream>   // 包含文件流库，用于文件的读写操作
#include <random>    // 包含随机数生成库，用于生成随机数
#include <string>    // 包含字符串库，用于处理字符串
#include <vector>

using namespace std;

// 生成固定位数的随机数
long long generateFixedDigitNumber(int digits)
{
	random_device rd;  // 用于生成随机种子，保证随机性
	mt19937 gen(rd()); // 使用 Mersenne Twister 引擎生成随机数，用 rd 作为种子
	uniform_int_distribution<> dis(0, 9); // 定义一个均匀分布，范围是 0 到 9

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
		// 浙江省杭州市（6个）
		"浙江省杭州市西湖区灵隐街道",
		"浙江省杭州市余杭区五常街道",
		"浙江省杭州市滨江区西兴街道",
		"浙江省杭州市上城区小营街道",
		"浙江省杭州市拱墅区米市巷街道",
		"浙江省杭州市临平区南苑街道",

		// 浙江省其他地区（6个）
		"浙江省宁波市鄞州区钟公庙街道",
		"浙江省温州市鹿城区五马街道",
		"浙江省绍兴市越城区府山街道",
		"浙江省嘉兴市南湖区建设街道",
		"浙江省湖州市吴兴区龙泉街道",
		"浙江省金华市婺城区城中街道",

		// 其他省份（18个）
		"北京市海淀区中关村街道",
		"上海市浦东新区陆家嘴街道",
		"广东省广州市天河区冼村街道",
		"江苏省南京市玄武区梅园新村街道",
		"四川省成都市锦江区春熙路街道",
		"湖北省武汉市江岸区一元街道",
		"山东省济南市历下区趵突泉街道",
		"福建省福州市鼓楼区东街街道",
		"安徽省合肥市庐阳区逍遥津街道",
		"湖南省长沙市岳麓区岳麓街道",
		"河南省郑州市中原区建设路街道",
		"河北省石家庄市长安区建北街道",
		"山西省太原市迎泽区柳巷街道",
		"陕西省西安市碑林区南院门街道",
		"云南省昆明市五华区华山街道",
		"贵州省贵阳市南明区新华路街道",
		"辽宁省沈阳市和平区南湖街道",
		"吉林省长春市朝阳区南湖街道"
	};

	// 随机数生成器
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> streetDis(0, addresses.size() - 1);
	std::string address = addresses[streetDis(gen)];

	// 随机生成门牌号（1 - 1000）
	std::uniform_int_distribution<> houseNumberDis(1, 1000);
	int houseNumber = houseNumberDis(gen);

	// 组合地址信息
	return address + std::to_string(houseNumber) + "号";
}

string generatePhoneNumber() {
	// 常见手机号码号段
	std::vector<std::string> prefixes = { "130", "131", "132", "133", "134", "135", "136", "137", "138", "139",
										 "145", "147", "150", "151", "152", "153", "155", "156", "157", "158",
										 "159", "166", "170", "171", "172", "173", "175", "176", "177", "178",
										 "180", "181", "182", "183", "184", "185", "186", "187", "188", "189",
										 "198", "199" };

	// 随机数生成器
	std::random_device rd;
	std::mt19937 gen(rd());

	// 随机选择一个号段
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
	// 随机决定是否为整数
	std::uniform_int_distribution<> isIntegerDis(0, 1);
	bool isInteger = isIntegerDis(gen);

	if (isInteger) {
		// 生成 0 到 100 的整数成绩
		std::uniform_int_distribution<> intDis(0, 100);
		return static_cast<double>(intDis(gen));
	}
	else {
		// 生成 0 到 100 的带小数成绩，保留两位小数
		std::uniform_real_distribution<> realDis(0.0, 100.0);
		double grade = realDis(gen);
		return std::round(grade * 100) / 100;
	}
}

int main()
{
	int numCount = 10; // 要生成的随机数的数量
	//int digits = 5;    // 随机数的位数
	string filename = "学生数据.txt"; // 存储随机数的文件名

	string name[53] = { "李","周","吴","郑","王","冯","陈","褚","卫","蒋","沈","韩","杨","何","吕","施","张","朱","秦","尤","许","金","魏","陶","姜","柏","水","窦","章","戚","谢","邹","喻","孔","曹","严","华","苗","凤","花","方","酆","鲍","史","唐","俞","任","袁","柳","鲁","韦","昌","马" };
	string name2[16] = { "伟", "芳", "娜", "敏", "静", "强", "磊", "军", "洋", "勇", "艳", "杰", "娟", "秀", "霞", "婷" };

	ofstream outFile(filename); // 打开文件用于写入
	if (!outFile.is_open())
	{  // 检查文件是否成功打开
		cerr << "无法打开文件！" << endl;  // 若未成功打开，输出错误信息
		return 1;  // 程序异常退出，返回错误码 1
	}

	for (int i = 0; i < numCount; ++i) {  // 循环 numCount 次，生成指定数量的随机数
		//long long randomNumber = generateFixedDigitNumber(digits); // 调用函数生成随机数
		outFile << generateFixedDigitNumber(12) << ' ';  // 将随机数写入文件
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
		outFile << (generateFixedDigitNumber(1) % 2 == 1 ? "男" : "女") << ' ';
		outFile << (generateChineseAddress()) << ' ';
		outFile << (generatePhoneNumber());
		for (int j = 0; j < 6; ++j)
		{
			outFile << ' ' << (generateGrade());
		}
		outFile << endl;
	}

	outFile.close();  // 关闭文件
	cout << "[ " << numCount << " ]个随机学生数据已成功写入 " << filename << endl;  // 输出成功信息

	return 0;  // 程序正常退出，返回 0
}