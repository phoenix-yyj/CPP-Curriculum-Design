#include<cstdio>
#include <iostream> 
#include <fstream>
#include <string>

using namespace std;

const string file_name = "data.txt";	//�洢�����ݵ��ļ���

//�ṹ�壺ѧ������
struct Student {
	string name;		//���ѵ�����
	string address;		//ѧ���ĵ�ַ
	string phone_num;	//ѧ���ĵ绰����
	Student* next;		//��һ�����
};

//�ࣺ������
class Control {
private:
	Student* head;  //ͷ�ڵ�
	Student* last;	//β�ڵ�

	//�������������һ��ѧ����������Ϣ
	void print_student(Student* student);
	//��������������һ��ѧ����������Ϣ
	void input_student(Student* student);
	//��������������һ��ѧ����������Ϣ
	void save_student(Student* student, fstream& fs);
	//������������ȡһ��ѧ����������Ϣ
	void load_student(Student* student, fstream& fs);
public:
	Student* index;//��������
	static int count;		//ͨѶ¼��������  

	Control() {
		head = new Student;
		index = new Student;
		last = new Student;
		head->next = NULL;
		last->next = NULL;
		index->next = NULL;
	}
	//���ܣ�����ѧ����Ϣ
	bool insert_student();
	//���ܣ�����ѧ����Ϣ
	bool search_student();
	//���ܣ�ɾ��ѧ����Ϣ
	bool delete_student();
	//���ܣ��޸�ѧ����Ϣ
	bool modify_student();
	//���ܣ���ʾ����ѧ����Ϣ
	bool show_all();

	//��������ѧ����Ϣ
	void load();
	//�洢����ѧ����Ϣ
	void save();

	//�˳�
	void exit_info();
};
int Control::count = 0;

//�ࣺ��ʾ��
class View {
public:
	void interface();		//������
	void choose();			//ѡ���֧����
};


void Control::print_student(Student* student) {
	cout << "\t���ѵ�������" << student->name << endl;
	cout << "\t���ѵĵ�ַ��" << student->address << endl;
	cout << "\t���ѵ���ϵ��ʽ��" << student->phone_num << endl;
}
void Control::input_student(Student* student) {
	cout << "�����룺" << endl;
	cout << "\t���ѵ�������"; cin >> student->name;
	cout << "\t���ѵĵ�ַ��"; cin >> student->address;
	cout << "\t���ѵ���ϵ��ʽ��"; cin >> student->phone_num;
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

	Student* node;		//Ҫ����Ľڵ�
	node = new Student;
	//�������������
	input_student(node);
	//����ڵ�����
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
	return true;		//�Ѳ���
}

bool Control::search_student() {
	

	//�ǿռ��
	if (count == 0) {
		cout << "���ͨѶ¼Ϊ�գ�" << endl;
		return false;
	}
	cout << "������Ҫ�����ĺ��ѵ����֣�";
	string input_name;	//Ҫ���������
	cin >> input_name;

	index = head->next;		//��λ���׽ڵ����
	while (index != NULL) {
		if (input_name == index->name) {
			print_student(index);	//���һ��ѧ������������
			return true;		//�Ѳ��ҵ�
		}
		index = index->next;
	}
	return false; //���Ҳ���
}

bool Control::delete_student() {
	

	//�ǿռ��
	if (count == 0) {
		cout << "���ͨѶ¼Ϊ�գ�" << endl;
		return false;
	}
	cout << "������Ҫɾ���ĺ��ѵ����֣�";
	string input_name;	//Ҫ���������
	cin >> input_name;

	index = head;		//��λ��ͷ�ڵ�
	while (index->next != NULL) {
		if (input_name == index->next->name) {
			index->next = index->next->next;	//������
			count--;
			return true;		//��ɾ��
		}
		index = index->next;
	}
	return false; //���Ҳ���
}

bool Control::modify_student() {
	
	//�ǿռ��
	if (count == 0) {
		cout << "���ͨѶ¼Ϊ�գ�" << endl;
		return false;
	}
	cout << "������Ҫ�޸���Ϣ�ĺ��ѵ����֣�";
	string input_name;	//Ҫ���������
	cin >> input_name;

	index = head->next;		//��λ���׽ڵ����һ���ڵ�
	while (index != NULL) {
		if (input_name == index->name) {
			//�������������
			input_student(index);
			return true;		//���޸����
		}
		index = index->next;
	}
	return false;		//���Ҳ���
}

bool Control::show_all() {
	
	//�ǿռ��
	if (count == 0) {
		cout << "���ͨѶ¼Ϊ�գ�" << endl;
		return false;
	}
	cout << "���ͨѶ¼�еĺ�������Ϊ��" << count << endl;

	index = head->next;			//ͷ�ڵ�ָ�����һ���ڵ�
	while (index != NULL) {
		print_student(index);   //������нڵ�������Ϣ
		index = index->next;	//��һ���ڵ�
	}
	return true;		//��ʾ���
}

void Control::load() {
	Student* node;
	fstream fs;
	fs.open(file_name, ios::in);
	//����ļ�û�дﵽ��β
	//��ȡ
	if (fs.is_open()) {
		while (!fs.eof()) {
			node = new Student;
			load_student(node, fs);

			//����ȡ���һ��
			if (node->name == "" || node->name == "\n") {
				break;
			}
			//����ָ��
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
	//д��
	if (fs.is_open()) {
		while (index != NULL) {
			//������Ϣ
			save_student(index, fs);
			index = index->next;
		}
		fs.close();
	}
}

void Control::exit_info() {
	cout << "��ȷ���˳���ͨѶ¼��(yes:1) ";
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
		cout << "��������Ҫ���еĲ���(1-6)" << endl;
		char action; cin >> action;		//Ҫ�����ָ��

		switch (action) {
		case '1':
			cout << "����ѡ��Ĳ������鿴������Ϣ�����еģ�" << endl;
			flag = control.show_all();
			break;
		case '2':
			cout << "����ѡ��Ĳ�������Ӻ�����Ϣ" << endl;
			flag = control.insert_student();
			break;
		case '3':
			cout << "����ѡ��Ĳ�����ɾ��������Ϣ" << endl;
			flag = control.delete_student();
			break;
		case '4':
			cout << "����ѡ��Ĳ���������������Ϣ" << endl;
			flag = control.search_student();
			break;
		case '5':
			cout << "����ѡ��Ĳ������޸ĺ�����Ϣ" << endl;
			flag = control.modify_student();
			break;
		case '6':
			cout << "����ѡ��Ĳ������˳�ͨѶ¼����ϵͳ" << endl;
			control.save();
			control.exit_info();
		default:
			cout << "���������ָ���������������룡" << endl;
			break;
		}

		if (flag) {
			cout << "�����ɹ���" << endl;
		}
		else {
			cout << "����ʧ�ܣ�" << endl;
		}
	}
}

void View::interface() {
	cout << endl
		<< "|*********************************************" << endl
		<< "|*  ѧ��ͨѶ¼	                              " << endl
		<< "|*********************************************" << endl
		<< "|*  ����ѡ��:	                              " << endl
		<< "|*  1. �鿴������Ϣ�����еģ�                   " << endl
		<< "|*  2. ��Ӻ�����Ϣ                            " << endl
		<< "|*  3. ɾ��������Ϣ                            " << endl
		<< "|*  4. ����������Ϣ                            " << endl
		<< "|*  5. �޸ĺ�����Ϣ                            " << endl
		<< "|*  6. �˳�����ϵͳ                            " << endl
		<< "|*********************************************" << endl
		<< endl;
}

int main() {
	View v;
	v.interface();
	v.choose();
	return 0;
}
