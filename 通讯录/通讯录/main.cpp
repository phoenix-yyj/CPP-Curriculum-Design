#include<cstdio>
#include <iostream> 
#include <fstream>
#include <string>

using namespace std;

const string file_name = "data.txt";	//存储的数据的文件名

//结构体：学生链表
struct Student {
	string name;		//好友的姓名
	string address;		//学生的地址
	string phone_num;	//学生的电话号码
	Student* next;		//下一个结点
};

//类：控制类
class Control {
private:
	Student* head;  //头节点
	Student* last;	//尾节点

	//基础方法：输出一个学生的所有信息
	void print_student(Student* student);
	//基础方法：输入一个学生的所有信息
	void input_student(Student* student);
	//基础方法：保存一个学生的所有信息
	void save_student(Student* student, fstream& fs);
	//基础方法：读取一个学生的所有信息
	void load_student(Student* student, fstream& fs);
public:
	Student* index;//结点的索引
	static int count;		//通讯录的总人数  

	Control() {
		head = new Student;
		index = new Student;
		last = new Student;
		head->next = NULL;
		last->next = NULL;
		index->next = NULL;
	}
	//功能：插入学生信息
	bool insert_student();
	//功能：查找学生信息
	bool search_student();
	//功能：删除学生信息
	bool delete_student();
	//功能：修改学生信息
	bool modify_student();
	//功能：显示所有学生信息
	bool show_all();

	//加载所有学生信息
	void load();
	//存储所有学生信息
	void save();

	//退出
	void exit_info();
};
int Control::count = 0;

//类：显示类
class View {
public:
	void interface();		//主界面
	void choose();			//选择分支控制
};


void Control::print_student(Student* student) {
	cout << "\t好友的姓名：" << student->name << endl;
	cout << "\t好友的地址：" << student->address << endl;
	cout << "\t好友的联系方式：" << student->phone_num << endl;
}
void Control::input_student(Student* student) {
	cout << "请输入：" << endl;
	cout << "\t好友的姓名："; cin >> student->name;
	cout << "\t好友的地址："; cin >> student->address;
	cout << "\t好友的联系方式："; cin >> student->phone_num;
}
void Control::save_student(Student* student, fstream& fs) {
	fs << student->name << endl;
	fs << student->address << endl;
	fs << student->phone_num << endl;
}
void Control::load_student(Student* student, fstream& fs) {
	char buffer[100];
	fs.getline(buffer, 100);
	student->name = buffer;
	fs.getline(buffer, 100);
	student->address = buffer;
	fs.getline(buffer, 100);
	student->phone_num = buffer;
}


bool Control::insert_student() {

	Student* node;		//要插入的节点
	node = new Student;
	//处理输入的数据
	input_student(node);
	//处理节点连接
	if (head->next == NULL) {
		last = node;
		head->next = last;
		last->next = NULL;
	}
	else {
		last->next = node;
		last = node;
		last->next = NULL;
	}
	count++;
	return true;		//已插入
}

bool Control::search_student() {
	

	//非空检查
	if (count == 0) {
		cout << "你的通讯录为空！" << endl;
		return false;
	}
	cout << "请输入要搜索的好友的名字：";
	string input_name;	//要输入的姓名
	cin >> input_name;

	index = head->next;		//定位到首节点后面
	while (index != NULL) {
		if (input_name == index->name) {
			print_student(index);	//输出一个学生的所有属性
			return true;		//已查找到
		}
		index = index->next;
	}
	return false; //查找不到
}

bool Control::delete_student() {
	

	//非空检查
	if (count == 0) {
		cout << "你的通讯录为空！" << endl;
		return false;
	}
	cout << "请输入要删除的好友的名字：";
	string input_name;	//要输入的姓名
	cin >> input_name;

	index = head;		//定位到头节点
	while (index->next != NULL) {
		if (input_name == index->next->name) {
			index->next = index->next->next;	//处理结点
			count--;
			return true;		//已删除
		}
		index = index->next;
	}
	return false; //查找不到
}

bool Control::modify_student() {
	
	//非空检查
	if (count == 0) {
		cout << "你的通讯录为空！" << endl;
		return false;
	}
	cout << "请输入要修改信息的好友的名字：";
	string input_name;	//要输入的姓名
	cin >> input_name;

	index = head->next;		//定位到首节点的下一个节点
	while (index != NULL) {
		if (input_name == index->name) {
			//处理输入的数据
			input_student(index);
			return true;		//已修改完毕
		}
		index = index->next;
	}
	return false;		//查找不到
}

bool Control::show_all() {
	
	//非空检查
	if (count == 0) {
		cout << "你的通讯录为空！" << endl;
		return false;
	}
	cout << "你的通讯录中的好友数量为：" << count << endl;

	index = head->next;			//头节点指向的下一个节点
	while (index != NULL) {
		print_student(index);   //输出所有节点属性信息
		index = index->next;	//下一个节点
	}
	return true;		//显示完毕
}

void Control::load() {
	Student* node;
	fstream fs;
	fs.open(file_name, ios::in);
	//如果文件没有达到结尾
	//读取
	if (fs.is_open()) {
		while (!fs.eof()) {
			node = new Student;
			load_student(node, fs);

			//不读取最后一行
			if (node->name == "" || node->name == "\n") {
				break;
			}
			//设置指针
			if (head->next == NULL) {
				last = node;
				head->next = last;
				last->next = NULL;
			}
			else {
				last->next = node;
				last = node;
				last->next = NULL;
			}
			count++;
		}
		fs.close();
	}
}

void Control::save() {
	fstream fs;
	index = head->next;
	fs.open(file_name, ios::out);
	//写入
	if (fs.is_open()) {
		while (index != NULL) {
			//保存信息
			save_student(index, fs);
			index = index->next;
		}
		fs.close();
	}
}

void Control::exit_info() {
	cout << "你确定退出此通讯录吗？(yes:1) ";
	char ch; cin >> ch;
	if (ch == '1') {
		exit(1);
	}
}

void View::choose() {

	Control control;
	View view;
	bool flag;
	control.load();

	while (true) {
		cout << "请输入你要进行的操作(1-6)" << endl;
		char action; cin >> action;		//要输入的指令

		switch (action) {
		case '1':
			cout << "你所选择的操作：查看好友信息（所有的）" << endl;
			flag = control.show_all();
			break;
		case '2':
			cout << "你所选择的操作：添加好友信息" << endl;
			flag = control.insert_student();
			break;
		case '3':
			cout << "你所选择的操作：删除好友信息" << endl;
			flag = control.delete_student();
			break;
		case '4':
			cout << "你所选择的操作：搜索好友信息" << endl;
			flag = control.search_student();
			break;
		case '5':
			cout << "你所选择的操作：修改好友信息" << endl;
			flag = control.modify_student();
			break;
		case '6':
			cout << "你所选择的操作：退出通讯录管理系统" << endl;
			control.save();
			control.exit_info();
		default:
			cout << "你所输入的指令有误，请重新输入！" << endl;
			break;
		}

		if (flag) {
			cout << "操作成功！" << endl;
		}
		else {
			cout << "操作失败！" << endl;
		}
	}
}

void View::interface() {
	cout << endl
		<< "|*********************************************" << endl
		<< "|*  学生通讯录	                              " << endl
		<< "|*********************************************" << endl
		<< "|*  功能选择:	                              " << endl
		<< "|*  1. 查看好友信息（所有的）                   " << endl
		<< "|*  2. 添加好友信息                            " << endl
		<< "|*  3. 删除好友信息                            " << endl
		<< "|*  4. 搜索好友信息                            " << endl
		<< "|*  5. 修改好友信息                            " << endl
		<< "|*  6. 退出管理系统                            " << endl
		<< "|*********************************************" << endl
		<< endl;
}

int main() {
	View v;
	v.interface();
	v.choose();
	return 0;
}
