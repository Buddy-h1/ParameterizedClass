#include <iostream>
#include <iomanip>

template<class T>
class Plenty {
private:
	int size;
	int capacity;
	T* plentyPtr;

public:
	//Стандартный конструктор для создания объекта
	Plenty() {
		this->size = 0;
		this->capacity = 0;
		this->plentyPtr = nullptr;
	}

	//Конструктор принимающий список инициализации
	Plenty(const std::initializer_list<T>& data) {
		this->plentyPtr = new T[data.size()];
		this->capacity = data.size();
		this->size = 0;
		for (auto i : data) {
			if (!Peek(i)) {
				this->plentyPtr[this->size] = i;
				this->size++;
			}
		}
		Sort();
	}

	//Конструктор копирования
	Plenty(const Plenty& plenty) {
		this->size = plenty.size;
		this->capacity = plenty.capacity;
		this->plentyPtr = new T[plenty.capacity];
		for (int i = 0; i < plenty.size; i++) {
			this->plentyPtr[i] = plenty.plentyPtr[i];
		}
	}

	//Деструктор
	~Plenty() {
		delete[] this->plentyPtr;
		this->size = 0;
		this->capacity = 0;
	}

	//Добавление элемента
	void PushBack(T obj) {
		if (!Peek(obj)) {
			if (capacity == size) {
				this->capacity *= 2;
				T* newPlentyPtr = new T[this->capacity];
				for (int i = 0; i < this->size; i++) {
					newPlentyPtr[i] = this->plentyPtr[i];
				}
				delete[] this->plentyPtr;
				this->plentyPtr = newPlentyPtr;
			}
			this->plentyPtr[this->size] = obj;
			this->size++;
			Sort();
		}
		else return;
	}

	//Сортировка множества
	void Sort() {
		for (int i = 0; i < this->size; i++) {
			for (int j = 0; j < this->size - 1; j++) {
				if (plentyPtr[j] > plentyPtr[j + 1]) {
					T tmp = plentyPtr[j];
					plentyPtr[j] = plentyPtr[j + 1];
					plentyPtr[j + 1] = tmp;
				}
			}
		}
	}

	//Проверить элемент в множестве
	bool Peek(T obj) {
		for (int i = 0; i < this->size; i++) {
			if (plentyPtr[i] == obj) return true;
		}
		return false;
	}

	Plenty& operator= (const Plenty& plenty) {
		this->size = plenty.size;
		this->capacity = plenty.capacity;
		if (this->plentyPtr != nullptr) delete[] this->plentyPtr;
		this->plentyPtr = new T[plenty.capacity];
		for (int i = 0; i < plenty.size; i++) {
			this->plentyPtr[i] = plenty.plentyPtr[i];
		}
		return *this;
	}

	template <typename T>
	friend Plenty<T> operator+ (const Plenty<T>& lhs, const Plenty<T>& rhs);

	template <typename T>
	friend std::ostream& operator<< (std::ostream& out, const Plenty<T>& plenty);
};

template <typename T>
Plenty<T> operator+ (const Plenty<T>& lhs, const Plenty<T>& rhs) {
	Plenty<T> result;
	result.plentyPtr = new T[lhs.size + rhs.size];
	result.size = result.capacity = lhs.size + rhs.size;
	for (int i = 0; i < lhs.size; i++) {
		result.plentyPtr[i] = lhs.plentyPtr[i];
	}
	int j = lhs.size;
	for (int i = 0; i < rhs.size; i++) {
		if (!result.Peek(rhs.plentyPtr[i])) {
			result.plentyPtr[j] = rhs.plentyPtr[i];
			j++;
		}
		else {
			result.size--;
		}
	}
	result.Sort();
	return result;
}

template <typename T>
std::ostream& operator<< (std::ostream& out, const Plenty<T>& plenty) {
	out << "{ ";
	for (int i = 0; i < plenty.size; i++) {
		i < plenty.size - 1 ? out << plenty.plentyPtr[i] << ", " : out << plenty.plentyPtr[i];
	}
	out << " }";
	return out;
}





class Line {
private:
	int length;
	char* linePtr;

	//Узнать длину строки
	int LineLenght(const char* line) {
		int count = 0;
		for (int i = 0; line[i] != '\0'; i++) { count++; }
		return count;
	}
public:
	//Стандартный конструктор для создания объекта
	Line() {
		length = 0;
		linePtr = new char;
		linePtr[0] = '\0';
	}

	//Конструктор принимающий строку
	Line(const char* line) {
		this->length = LineLenght(line);
		this->linePtr = new char[this->length + 1];
		for (int i = 0; i < this->length; i++) {
			this->linePtr[i] = line[i];
		}
		this->linePtr[this->length] = '\0';
	}

	//Конструктор копирования
	Line(const Line& line) {
		this->linePtr = new char[line.length + 1];
		for (int i = 0; i < line.length; i++) {
			this->linePtr[i] = line.linePtr[i];
		}
		this->linePtr[line.length] = '\0';
		this->length = line.length;
	}

	//Деструктор
	~Line() {
		delete[] this->linePtr;
		length = 0;
	}

	Line& operator= (const Line& line) {
		if (this->linePtr) delete[] this->linePtr;
		this->length = line.length;

		this->linePtr = new char[line.length];
		for (int i = 0; i < line.length; i++) {
			this->linePtr[i] = line.linePtr[i];
		}
		return *this;
	}

	friend Line operator+(const Line& lhs, const Line& rhs);

	friend std::ostream& operator<< (std::ostream& out, const Line& line);
};

Line operator+(const Line& lhs, const Line& rhs) {
	Line result;
	result.length = lhs.length + rhs.length;
	result.linePtr = new char[result.length + 1];

	int i;
	for (i = 0; i < lhs.length; i++) {
		result.linePtr[i] = lhs.linePtr[i];
	}
	for (int j = 0; j < rhs.length; j++) {
		result.linePtr[i] = rhs.linePtr[j];
		i++;
	}
	result.linePtr[result.length] = '\0';

	return result;
}

std::ostream& operator<< (std::ostream& out, const Line& line) {
	for (int i = 0; i < line.length; i++) {
		out << line.linePtr[i];
	}
	return out;
}




template<class T>
class Matrix {
private:
	int count_line;
	int count_column;
	T** matrix;

	void MemoryAllocation(int value_line, int value_column) {
		this->matrix = new T * [value_line];
		for (int i = 0; i < value_line; i++) {
			this->matrix[i] = new T[value_column];
		}
	}

public:
	//Стандартный конструктор для создания объекта
	Matrix() {
		matrix = nullptr;
	}

	//Конструктор принимающий размеры матрицы
	Matrix(int value_line, int value_column) : count_line(value_line), count_column(value_column) {
		matrix = new T* [value_line];
		for (int i = 0; i < value_line; i++) {
			matrix[i] = new T[value_column];
		}
	}

	//Конструктор принимающий размеры матрицы и значения
	Matrix(int value_line, int value_column, const std::initializer_list<T>& params) {
		if (value_line * value_column < (int)params.size()) {
			std::string ex = "you tried to initialize too much data";
			throw ex;
		}
		MemoryAllocation(value_line, value_column);
		this->count_line = value_line;
		this->count_column = value_column;
		int line = 0;
		int column = 0;
		for (auto i : params) {
			this->matrix[line][column] = i;
			column++;
			if (column == value_column) {
				column = 0;
				line++;
			}
		}
	}

	//Деструктор
	~Matrix() {
		for (int i = 0; i < this->count_line; i++) {
			delete[] matrix[i];
		}
		delete this->matrix;
		count_line = 0;
		count_column = 0;
	}

	//Конструктор копирования
	Matrix(const Matrix& other) {
		this->count_line = other.count_line;
		this->count_column = other.count_column;
		MemoryAllocation(other.count_line, other.count_column);
		for (int i = 0; i < this->count_line; i++) {
			for (int j = 0; j < this->count_column; j++) {
				this->matrix[i][j] = other.matrix[i][j];
			}
		}
	}

	Matrix& operator= (const Matrix& matrix) {
		this->count_line = matrix.count_line;
		this->count_column = matrix.count_column;
		if (this->matrix != nullptr) {
			for (int i = 0; i < this->count_line; i++) {
				delete[] this->matrix[i];
			}
			delete this->matrix;
		}
		MemoryAllocation(matrix.count_line, matrix.count_column);
		for (int i = 0; i < matrix.count_line; i++) {
			for (int j = 0; j < matrix.count_column; j++) {
				this->matrix[i][j] = matrix.matrix[i][j];
			}
		}
		return *this;
	}

	template <typename T>
	friend Matrix<T> operator+ (const Matrix<T>& lhs, const Matrix<T>& rhs);

	template <typename T>
	friend std::ostream& operator<< (std::ostream& out, const Matrix<T>& matrix);

};

template <typename T>
Matrix<T> operator+ (const Matrix<T>& lhs, const Matrix<T>& rhs) {
	if ((lhs.count_line != rhs.count_line) || (lhs.count_column != rhs.count_column)) {
		std::string ex = "matrix sizes do not match";
		throw ex;
	}
	Matrix<T> result(lhs.count_line, lhs.count_column);
	for (int i = 0; i < lhs.count_line; i++) {
		for (int j = 0; j < lhs.count_column; j++) {
			result.matrix[i][j] = lhs.matrix[i][j] + rhs.matrix[i][j];
		}
	}
	return result;
}

template <typename T>
std::ostream& operator<< (std::ostream& out, const Matrix<T>& matrix) {
	for (int i = 0; i < matrix.count_line; i++) {
		for (int j = 0; j < matrix.count_column; j++) {
			std::cout << std::setw(5) << matrix.matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	return out;
}





int main() {
	{
		Plenty<int> plenty_1 = { 8, 4, 23, 8, 9 };
		std::cout << "plenty_1:   " << plenty_1 << std::endl;
		Plenty<int> plenty_2 = { 9, 11, 54, 23, 98, 3 };
		std::cout << "plenty_2:   " << plenty_2 << std::endl;
		Plenty<int> plenty_3 = plenty_1 + plenty_2;
		std::cout << "plenty_1 + plenty_2 = " << plenty_3 << std::endl;
		plenty_1 = plenty_2;
		std::cout << "plenty_1 = plenty_2; plenty_1:   " << plenty_1 << std::endl;
	}

	std::cout << "-------------------" << std::endl;

	{
		Line line_1("Hello");
		std::cout << "line_1: " << line_1 << std::endl;
		Line line_2(" world!");
		std::cout << "line_2:" << line_2 << std::endl;
		Line line_3 = line_1 + line_2;
		std::cout << "line_1 + line_2 = " << line_3 << std::endl;
		line_1 = line_2;
		std::cout << "line_2 = line_1; line_1: " << line_1 << std::endl;
	}

	std::cout << "-------------------" << std::endl;

	{
		Matrix<Plenty<int>> matrix_1(3, 2, { {8, 9, 12}, { 7, 3, 7 }, { 15, 8, 2 }, { 13, 1, 7 }, { 15, 8, 2 }, { 15, 8, 2 } });
		Matrix<Plenty<int>> matrix_2(3, 2, { {1, 5, 6}, { 1, 3, 4 }, { 3, 2, 5 }, { 9, 2, 1 } , { 8, 4, 1, 5, 3 } , { 2, 21, 14 } });
		std::cout << "matrix_1" << std::endl << matrix_1 << std::endl;
		std::cout << "matrix_2" << std::endl << matrix_2 << std::endl;
		Matrix<Plenty<int>> matrix_3 = matrix_1 + matrix_2;
		std::cout << "matrix_1 + matrix_2" << std::endl << matrix_3 << std::endl;
		matrix_1 = matrix_2;
		std::cout << "matrix_1 = matrix_2; matrix_1: " << std::endl << matrix_1 << std::endl;
	}

	std::cout << "-------------------" << std::endl;

	{
		Matrix<Line> matrix_1s(3, 2, { "cat", "dog", "bird", "wolf", "goose", "frog" });
		Matrix<Line> matrix_2s(3, 2, { "cow", "rat", "fox", "bear", "pig", "duck" });
		std::cout << "matrix_1s" << std::endl << matrix_1s << std::endl;
		std::cout << "matrix_2s" << std::endl << matrix_2s << std::endl;
		Matrix<Line> matrix_3s = matrix_1s + matrix_2s;
		std::cout << "matrix_1s + matrix_2s" << std::endl << matrix_3s << std::endl;
		matrix_1s = matrix_2s;
		std::cout << "matrix_1s = matrix_2s; matrix_1s: " << std::endl << matrix_1s << std::endl;
	}

	return 0;
}