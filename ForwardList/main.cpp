#include <iostream>
using namespace std;

#define tab "\t"
#define delimiter "\n----------------------------------\n"

class Element
{
	int Data; //�������� ��������
	Element* pNext; //����� ���������� ��������
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "E_Constructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "E_Destructor:\t" << this << endl;
	}
	friend class ForwardList;
};

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
		cout << "LD_Destructor:\t" << this << endl;
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
	void pop_front()
	{
		Element* Temp = Head->pNext;
		delete Head;
		Head = Temp;
	} 
	void push_back(int Data)
	{
		Element* New = new Element(Data);

	}


	//                  METHODS:
	void print()const
	{
		Element* Temp = Head; //Temp - �������� (���������, ��� ������ ��������
		                      //����� �������� ������ � ��������� ��������� ������
		while (Temp!=nullptr)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext; //������� �� ��������� �������
		}
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
	list.pop_front();
	list.print();
}