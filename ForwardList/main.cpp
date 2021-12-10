#include <iostream>
using namespace std;

#define tab "\t"
#define delimiter "\n----------------------------------\n"

class Element
{
	int Data; //�������� ��������
	Element* pNext; //����� ���������� ��������
	static int count; // ���������� ���������
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "E_Constructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "E_Destructor:\t" << this << endl;
	}
	friend class ForwardList;
};
int Element::count = 0; //����������� ���������� ����� ���� ������������������� ������
                        //�� �������

class ForwardList
{
	Element* Head; //��������� �� ��������� ������� ������. �������� ������ ����� � ������
public:
	ForwardList()
	{
		this->Head = nullptr;// ���� ������ ��������� �� 0, ������ ������ ����
		cout << "L_Constructor:\t" << this << endl;
	}
	~ForwardList()
	{
		//for ()
		{
			Element* Temp = Head;
			Head = Head->pNext;
			delete Temp;
		}
		
		cout << "FL_Destructor:\t" << this << endl;
	}

	//                        ADDING ELEMENTS:
	void push_front(int Data)
	{
		//1) ������� �������:
		Element* New = new Element(Data);
		//2) ������������ ����� ������� � ������:
		New->pNext = Head;
		//3) ��������� ������ �� ����� �������:
		Head = New;
	}
	void push_back(int Data)
	{
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
	}

	//                     Erasing elements:
	void pop_front()
	{
		// 1) ���������� ����� ���������� ��������
		Element* Erased = Head;
		// 2) ��������� ������� �� ������
		Head = Head->pNext;
		// 3) ������� ������� �� ������
		delete Erased;
	}
	void pop_back()
	{
		// 1) ������� �� �������������� ��������
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;//��������� � ������������� ��������
		// 2) ������� ��������� ������� �� ������
		delete Temp->pNext;
		// 3) "��������" �� ��������� ��������,�� ���� �������� ��� ����� �����
		Temp->pNext = nullptr;
		//������ Temp �������� ��������� ��������� ������
	}
	void insert(int Data, int Index)
	{
		if (Index > Head->count)
		{
			cout << "Error: ����� �� ������� ������." << endl;
			return;
		}
		if (Index == 0 || Head == nullptr)return push_front(Data);
		// 0) ������� ����� �������
		Element* New = new Element(Data);
		// 1) ������� �� ������� ��������
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		// ������������ ������� ������ ��������
		// 2) ����������� ����� ������� � ������ 
		New->pNext = Temp->pNext;
		// 3) �������� ������� � ������
		Temp->pNext = New;
	}
	void erase(int Index)
	{
		if (Index > Head->count)
		{
			cout << "Error: ����� �� ������� ������." << endl;
			return;
		}
		Element* Temp = Head; //������� �� ������� ��������
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		Element* New = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete New;
	}


	//                  METHODS:
	void print()const
	{
		Element* Temp = Head; //Temp - �������� (���������, ��� ������ ��������
							  //����� �������� ������ � ��������� ��������� ������
		while (Temp != nullptr)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext; //������� �� ��������� �������
		}
		cout << "���������� ��������� ������: " << Head->count << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "Rus");
	int n; //������ ������
	cout << "������� ������ ������: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	cout << delimiter << endl;
	list.push_back(123);
	list.print();
	cout << delimiter << endl;
	list.pop_front();
	list.print();
	cout << delimiter << endl;
	list.pop_back();
	list.print();
	cout << delimiter << endl;
	int index;
	int value;
	cout << "������� ������ ������������ ��������: ";cin >> index;
	cout << "������� �������� ������������ ��������: ";cin >> value;
	list.insert(value, index);
	list.print();
	cout << delimiter << endl;
	cout << "������� ������ ���������� ��������: ";cin >> index;
	list.erase(index);
	list.print();
}