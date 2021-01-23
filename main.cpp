#include <cstdlib>
#include <iostream>
#include <ctime>
#include <stack>

#define N 1000000

using namespace std;

template<typename T>
void swap(T *Arr, const int a, const int b, int &chgCount)
{
	T temp = Arr[a]; // меняем их местами
	Arr[a] = Arr[b];
	Arr[b] = temp;
	
	++chgCount;
}

#pragma region HeapSort

// Функция "просеивания" через кучу - формирование кучи
template<typename T>
void siftDown(T *numbers, int root, int bottom, int &chgCount, int &cmpCount)
{
	int maxChild; // индекс максимального потомка
	bool done = false; // флаг того, что куча сформирована
	// Пока не дошли до последнего ряда
	while ((root * 2 <= bottom) && (!done))
	{
		if (root * 2 == bottom)   // если мы в последнем ряду,
		{
			maxChild = root * 2;    // запоминаем левый потомок
		}
			// иначе запоминаем больший потомок из двух
		else if (numbers[root * 2] > numbers[root * 2 + 1])
		{
			maxChild = root * 2;
			cmpCount++;
		}
		else
		{
			maxChild = root * 2 + 1;
			cmpCount++;
		}
		// если элемент вершины меньше максимального потомка
		if (numbers[root] < numbers[maxChild])
		{
			swap(numbers, root, maxChild, chgCount);
			root = maxChild;
			cmpCount++;
		}
		else // иначе
		{
			done = true; // пирамида сформирована
			cmpCount++;
		}
	}
}

// Функция сортировки на куче
template<typename T>
void heapSort(T *numbers, int array_size, int &chgCount, int &cmpCount)
{
	// Формируем нижний ряд пирамиды
	chgCount = 0;
	cmpCount = 0;
	
	for (int i = (array_size / 2) - 1; i >= 0; i--)
	{
		siftDown(numbers, i, array_size - 1, chgCount, cmpCount);
	}
	// Просеиваем через пирамиду остальные элементы
	for (int i = array_size - 1; i >= 1; i--)
	{
		swap(numbers, 0, i, chgCount);
		siftDown(numbers, 0, i - 1, chgCount, cmpCount);
	}
}

#pragma endregion HeapSort

#pragma region QSort

template<typename T>
void QSort(T *arr, int n, int &chgCount, int &cmpCount)
{
	T base;
	int left, right, i, j;
	
	chgCount = 0;
	cmpCount = 0;
	
	i = j = 0;
	stack <int> st;
	st.push(n - 1);
	st.push(0);
	do {                  // while (!st.empty())
		left = st.top();
		st.pop();
		right = st.top();
		st.pop();
		if (((right - left) == 1) && (arr[left] > arr[right]))
		{
			swap(arr, left, right, chgCount);
			cmpCount++;
		}
		else
		{
			base = arr[right];
			i = left;
			j = right;
			// цикл продолжается, пока индексы i и j не сойдутся
			do {         // while (i > j)
				// пока i-ый элемент не превысит опорный
				while ((base > arr[i]))
				{
					++i;
					cmpCount++;
				}
				// пока j-ый элемент не окажется меньше опорного
				while (arr[j] > base)
				{
					--j;
					cmpCount++;
				}
				if (i <= j)
				{
					swap(arr, i, j, chgCount);
					i++;
					j--;
				}
			} while (i <= j);
		}
		if (left < j)
		{
			st.push(j);
			st.push(left);
		}
		if (i < right)
		{
			st.push(right);
			st.push(i);
		}
	} while (!st.empty());
}

#pragma endregion QSort

#pragma region ArrayFunctions

template<typename T>
void fillArray (T *Arr, int size)
{
	srand(time(nullptr));
	// Заполнение массива случайными числами
	for (int i = 0; i < size; ++i)
	{
		Arr[i] = rand() % N;
	}
}

template<typename T>
void printArray (T *Arr, int size, std::ostream &out=std::cout)
{
	for (int i = 0; i<size; ++i)
	{
		out << Arr[i] << ' ';
	}
	endl(out);
}

#pragma endregion ArrayFunctions


#pragma region DecoratedFunctions

template<typename T>
void DecSort(bool ind, T *Arr, int size, void sort(T *arr, int n, int &chgCount, int &cmpCount), char *sortName, std::ostream &out=std::cout)
{
	int cmpCount, chgCount;
	clock_t start, end;
	
	start = clock();
	sort(Arr, size, chgCount, cmpCount);
	end = clock();
	
	out << "Сортировка: " << sortName << endl;
	out << "Отсортированный массив: ";
	if (ind)
	{
		printArray(Arr, size, out);
	}
	else
	{
		out << "<Слишком длинный для отображения на экране>" << endl;
	}
	out << "Время: " << (double)(end-start)/CLOCKS_PER_SEC << " sec." << endl;
	
	out << "Количество сравнений: " << cmpCount << endl;
	out << "Количество обменов: " << chgCount << endl;
}

#pragma endregion DecoratedFunctions


int main()
{
	int a[N];
	// Заполнение массива
	fillArray(a, N);
	
	bool ind;
	if (N > 1000)
	{
		ind = false;
	}
	else
	{
		ind = true;
	}
	
	// Вывод элементов массива до сортировки
	printArray(a, N);
	
	
	
	cout << "------------------------------------------";
	endl(cout);
	
	DecSort(ind, a, N, QSort, "Быстрая");
	
	cout << "------------------------------------------";
	endl(cout);
	
	DecSort(ind, a, N, heapSort, "Пирамидальная");
	
	
	return 0;
}
