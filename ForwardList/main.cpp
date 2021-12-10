#include <iostream>
using namespace std;

#define tab "\t"
#define delimiter "\n----------------------------------\n"

class Element
{
	int Data; //значение элемента
	Element* pNext; //адрес следующего элемента
	static int count; // количество элементов
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
int Element::count = 0; //статические переменные могут быть проинициализированы только
                        //за классом

class ForwardList
{
	Element* Head; //указывает на начальный элемент списка. Является точкой входа в список
public:
	ForwardList()
	{
		this->Head = nullptr;// если голова указывает на 0, значит список пуст
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
		//1) Создаем элемент:
		Element* New = new Element(Data);
		//2) присоединяем новый элемент к списку:
		New->pNext = Head;
		//3) Переносим голову на новый элемент:
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
		// 1) запоминаем адрес удаляемого элемента
		Element* Erased = Head;
		// 2) исключаем элемент из списка
		Head = Head->pNext;
		// 3) удаляем элемент из списка
		delete Erased;
	}
	void pop_back()
	{
		// 1) доходим до предпоследнего элемента
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;//оказались в предпоследнем элементе
		// 2) удаляем последний элемент из памяти
		delete Temp->pNext;
		// 3) "забываем" об удаленном элементе,то есть затираем его адрес нулем
		Temp->pNext = nullptr;
		//Теперь Temp является последним элементом списка
	}
	void insert(int Data, int Index)
	{
		if (Index > Head->count)
		{
			cout << "Error: Выход за пределы списка." << endl;
			return;
		}
		if (Index == 0 || Head == nullptr)return push_front(Data);
		// 0) создаем новый элемент
		Element* New = new Element(Data);
		// 1) доходим до нужного элемента
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		// осуществялем вставку нового элемента
		// 2) привязываем новый элемень к списку 
		New->pNext = Temp->pNext;
		// 3) включаем элемент в список
		Temp->pNext = New;
	}
	void erase(int Index)
	{
		if (Index > Head->count)
		{
			cout << "Error: Выход за пределы списка." << endl;
			return;
		}
		Element* Temp = Head; //доходим до нужного элемента
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		Element* New = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete New;
	}


	//                  METHODS:
	void print()const
	{
		Element* Temp = Head; //Temp - ИТЕРАТОР (УКАЗАТЕЛЬ, ПРИ ПОМОЩИ КОТОРОГО
							  //МОЖНО ПОЛУЧИТЬ ДОСТУП К ЭЛЕМЕНТАМ СТРУКТУРЫ ДАННЫХ
		while (Temp != nullptr)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext; //Переход на следующий элемент
		}
		cout << "Количество элементов списка: " << Head->count << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "Rus");
	int n; //размер списка
	cout << "Введите размер списка: "; cin >> n;
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
	cout << "Введите индекс добавляемого элемента: ";cin >> index;
	cout << "Введите значение добавляемого элемента: ";cin >> value;
	list.insert(value, index);
	list.print();
	cout << delimiter << endl;
	cout << "Введите индекс удаляемого элемента: ";cin >> index;
	list.erase(index);
	list.print();
}