#include <iostream>

using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimiter "\n----------------------------------\n"
//#define DEBUG



class Element
{
	int Data; //значение элемента
	Element* pNext; //адрес следующего элемента
	static int count; // количество элементов
public:
	int getData()const
	{
		return Data;
	}
	Element* get_pNext()const
	{
		return pNext;
	}
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
	friend class Iterator;
};
int Element::count = 0; //статические переменные могут быть проинициализированы только
                        //за классом
class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
	{
#ifdef DEBUG
		cout << "It_Constructor:\t" << this << endl;
#endif // DEBUG

	}
	~Iterator()
	{
#ifdef DEBUG
		cout << "It_Destructor:\t" << this << endl;
#endif // DEBUG

	}

	//                     OPERATORS:
	Iterator& operator++() //Prefix increment
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator operator++(int) //Suffix increment
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}
	const int& operator*()const
	{
		return Temp->Data;
	}
	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	operator bool()const
	{
		return Temp;
	}
};

class ForwardList
{
	Element* Head; //указывает на начальный элемент списка. Является точкой входа в список
	size_t size;
public:
	Element* getHead()const
	{
		return Head;
	}

	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}

	//                       CONSTRUCTORS:
	ForwardList()
	{
		this->Head = nullptr;// если голова указывает на 0, значит список пуст
		size = 0;
		cout << "L_Constructor:\t" << this << endl;
	}
	ForwardList(const std::initializer_list<int>& il):ForwardList()
	{
		for (const int* it = il.begin(); it != il.end(); it++)
		{
			//it - итератор для прохождения по il
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other)
	{
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "L_Copy_Constructor: " << this << endl;
	}
	~ForwardList()
	{
		/*for (;Head;)
		{
			Element* Temp = Head;
			Head = Head->pNext;
			delete Temp;
		}*/
		while (Head)pop_front();
		cout << "FL_Destructor:\t" << this << endl;
		cout << "\n---------------------------------------------\n";
	}

	//                         OPERATORS:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "L_Copy_Assignment: " << this << endl;
		return *this;
	}
	

	//                        ADDING ELEMENTS:
	void push_front(int Data)
	{
		//1) Создаем элемент:
		//Element* New = new Element(Data, Head);
		//2) присоединяем новый элемент к списку:
		//New->pNext = Head;
		//3) Переносим голову на новый элемент:
		//Head = New;
		Head = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
		size++;
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
		size--;
	}
	void pop_back()
	{
		if (Head->pNext == nullptr)return pop_front();
		// 1) доходим до предпоследнего элемента
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;//оказались в предпоследнем элементе
		// 2) удаляем последний элемент из памяти
		delete Temp->pNext;
		// 3) "забываем" об удаленном элементе,то есть затираем его адрес нулем
		Temp->pNext = nullptr;
		//Теперь Temp является последним элементом списка
		size--;
	}
	void insert(int Data, int Index)
	{
		if (Index > Head->count)
		{
			cout << "Error: Выход за пределы списка." << endl;
			return;
		}
		if (Index == 0 || Head == nullptr)return push_front(Data);
		// 0) доходим до нужного элемента
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		// 1) создаем новый элемент
		//Element* New = new Element(Data);
		// осуществялем вставку нового элемента
		// 2) привязываем новый элемень к списку 
		//New->pNext = Temp->pNext;
		// 3) включаем элемент в список
		//Temp->pNext = New;
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
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
		size--;
	}


	//                  METHODS:
	void print()const
	{
		/*Element* Temp = Head; //Temp - ИТЕРАТОР (УКАЗАТЕЛЬ, ПРИ ПОМОЩИ КОТОРОГО
							  //МОЖНО ПОЛУЧИТЬ ДОСТУП К ЭЛЕМЕНТАМ СТРУКТУРЫ ДАННЫХ
		while (Temp != nullptr)
		{
			Temp = Temp->pNext; //Переход на следующий элемент
		}*/
		//for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		for (Iterator Temp = Head; Temp!=nullptr; Temp++)
			cout <<*Temp<< tab;
		cout << endl;
		cout << "Количество элемнтов в списке: " << size << endl;
		cout << "Общее количество элементов списка: " << Head->count << endl;
	}
	
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList result = left;
	//for (Element* Temp = right.getHead(); Temp; Temp = Temp->get_pNext())//проходим по правому списку
		//result.push_back(Temp->getData());//и добавляем все его элементы в конец результата
	for (Iterator Temp = right.getHead(); Temp; Temp++)
	{
		result.push_back(*Temp);
	}
	return result;
}

//#define BASE_CHECK
//#define COUNT_CHECK
//#define COPY_METHODS_CHECK
//#define OPERATOR_PLUS_CHECK
//#define RANGE_BASED_FOR_ARR

void main()
{
	setlocale(LC_ALL, "Rus");
#ifdef BASE_CHECK
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
#endif // BASE_CHECK

#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);

	list1.print();
	list2.print();

#endif // COUNT_CHECK

#ifdef COPY_METHODS_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1 = list1;
	list1.print();

	//ForwardList list2 = list1; //CopyConstructor
	ForwardList list2;
	list2 = list1; //CopyAssignment
	list2.print();
#endif // COPY_METHODS_CHECK

#ifdef OPERATOR_PLUS_CHECK
	ForwardList list1 = { 3, 5,8,13,21 };
	list1.print();
	ForwardList list2 = { 34,55,89 };
	list2.print();
	ForwardList list3 = list1 + list2;
	list3.print();
#endif // OPERATOR_PLUS_CHECK

#ifdef RANGE_BASED_FOR_ARR
	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
		cout << arr[i] << tab;
	cout << endl;

	//                           RANGE-BASED FOR:
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_ARR

	ForwardList list = { 3,5,8,13,21 };
	cout << "\n----------------------------------\n";
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
	cout << "\n----------------------------------\n";
}