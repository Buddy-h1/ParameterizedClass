#include <sstream>
#include <iostream>
#include <iomanip>
#include <ctime>

template<class T>
class Plenty {
private:
	int size;
	int capacity;
	T* plentyPtr;

	bool Peek(T obj) {
		for (int i = 0; i < this->size; i++) {
			if (plentyPtr[i] == obj) return true;
		}
		return false;
	}

	T operator[] (int index) {
		return plentyPtr[index];
	}

public:
	Plenty() {
		this->size = 0;
		this->capacity = 0;
		plentyPtr = nullptr;
	}

	Plenty(int size) {
		plentyPtr = new T [size];
		this->size = size;
		this->capacity = size;
	}

	~Plenty() {
		delete[] plentyPtr;
		this->size = 0;
		this->capacity = 0;
	}

	Plenty(const Plenty& plenty) {
		this->size = plenty.size;
		this->capacity = plenty.capacity;
		this->plentyPtr = new T[this->size];
		for (int i = 0; i < plenty.size; i++) {
			this->plentyPtr[i] = plenty.plentyPtr[i];
		}
	}

	void RandomFillInt() {
		for (int i = 0; i < this->size; i++) {
			int random = 0 + rand() % (100 - 0);
			while (this->Peek(random)) {
				random = 0 + rand() % (100 - 0);
			}
			this->plentyPtr[i] = random;
		}
		this->Sort();
	}

	void PushBack(T obj) {
		if (!Peek(obj)) {
			if (capacity == size) {
				this->capacity *= 2;
				T* newPlentyPtr = new T[this->capacity];
				for (int i = 0; i < this->size; i++) {
					newPlentyPtr[i] = this->plentyPtr[i];
				}
				delete[] plentyPtr;
				this->plentyPtr = newPlentyPtr;
			}
			this->plentyPtr[this->size] = obj;
			this->size++;
			Sort();
		}
		else return;
	}

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

	void Change(int index, T obj) {
		if (!this->Peek(obj) && index < size) {
			plentyPtr[index] = obj;
		}
		else throw "error: going beyond the plenty";
	}

	template <typename T>
	friend std::istream& operator>> (std::istream& in, Plenty<T>& plenty) {
		for (int i = 0; i < plenty.size; i++) {
			T temp;
			in >> temp;
			if (!plenty.Peek(temp)) {
				plenty.plentyPtr[i] = temp;
			}
			else throw "error: you entered the same items";
		}
		plenty.Sort();
		return in;
	}

	template <typename T>
	friend std::ostream& operator<< (std::ostream& out, const Plenty<T>& plenty) {
		out << "{ ";
		for (int i = 0; i < plenty.size; i++) {
			i < plenty.size - 1 ? out << plenty.plentyPtr[i] << ", " : out << plenty.plentyPtr[i];
		}
		out << " }";
		return out;
	}

	template <typename T>
	Plenty<T> operator+ (Plenty<T>& plenty) {
		Plenty<T> result(this->size + plenty.size);
		for (int i = 0; i < this->size; i++) {
			result.plentyPtr[i] = this->plentyPtr[i];
		}
		int j = this->size;
		for (int i = 0; i < plenty.size; i++) {
			if (!result.Peek(plenty.plentyPtr[i])) {
				result.plentyPtr[j] = plenty.plentyPtr[i];
				j++;
			}
			else {
				result.size--;
			}
		}
		result.Sort();
		return result;
	}
};

class Line {
private:
	int length;
	//int capacity;
	char* linePtr;

	int LineLenght(const char* line) {
		int count = 0;
		for (int i = 0; line[i] != '\0'; i++) { count++; }
		return count;
	}
public:
	Line() {
		length = 0;
		linePtr = new char;
		linePtr[0] = '\0';
	}

	Line(const char* line) {
		this->length = LineLenght(line);
		this->linePtr = new char[this->length + 1];
		for (int i = 0; i < this->length; i++) {
			this->linePtr[i] = line[i];
		}
		this->linePtr[this->length] = '\0';
	}

	Line(const Line& line) {
		this->length = line.length;
		this->linePtr = new char[this->length + 1];
		for (int i = 0; i < this->length; i++) {
			this->linePtr[i] = line.linePtr[i];
		}
		this->linePtr[this->length] = '\0';
	}

	~Line() {
		delete[] this->linePtr;
	}

	Line operator+(const Line& line) {
		Line result;
		result.length = this->length + line.length;
		result.linePtr = new char[result.length + 1];

		int i;
		for (i = 0; i < this->length; i++) {
			result.linePtr[i] = this->linePtr[i];
		}
		for (int j = 0; j < line.length; j++) {
			result.linePtr[i] = line.linePtr[j];
			i++;
		}
		result.linePtr[result.length] = '\0';

		return result;
	}

	friend std::ostream& operator<< (std::ostream& out, const Line& line) {
		for (int i = 0; i < line.length; i++) {
			out << line.linePtr[i];
		}
		return out;
	}

};

template<class T>
class Matrix {
private:
	int count_line;
	int count_column;
	T** matrix;

public:
	Matrix() {
		count_line = 1;
		count_column = 1;
		matrix = new T* [1];
		matrix[0] = new T[1];
		matrix[0][0] = 0;
	}
	Matrix(int value_line, int value_column) : count_line(value_line), count_column(value_column) {
		matrix = new T* [count_line];
		for (int i = 0; i < count_line; i++) {
			matrix[i] = new T[count_column];
		}
	}
	~Matrix() {
		for (int i = 0; i < count_line; i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
		count_line = 0;
		count_column = 0;
	}

	int* operator[](int index) {
		return matrix[index];
	}
	Matrix(const Matrix& other) {
		this->count_line = other.count_line;
		this->count_column = other.count_column;
		this->matrix = new T* [this->count_line];
		for (int i = 0; i < this->count_column; i++) {
			this->matrix[i] = new T[this->count_column];
		}
		for (int i = 0; i < this->count_line; i++) {
			for (int j = 0; j < this->count_column; j++) {
				this->matrix[i][j] = other.matrix[i][j];
			}
		}
	}
	void operator=(const Matrix& other) {
		if (this->matrix != nullptr) {
			for (int i = 0; i < this->count_column; i++) {
				delete[] this->matrix[i];
			}
			delete[] this->matrix;
			this->count_line = 0;
			this->count_column = 0;
		}
		this->count_line = other.count_line;
		this->count_column = other.count_column;
		this->matrix = new int* [this->count_line];
		for (int i = 0; i < this->count_column; i++) {
			this->matrix[i] = new int[this->count_column];
		}
		for (int i = 0; i < this->count_line; i++) {
			for (int j = 0; j < this->count_column; j++) {
				this->matrix[i][j] = other.matrix[i][j];
			}
		}
	}

	template<class T>
	friend Matrix<T> operator+(Matrix<T> matrix) {
		if ((this->count_line != matrix.count_line) || (this->count_column != matrix.count_column)) {
			std::string ex = "matrix sizes do not match";
			throw ex;
		}
		Matrix result(this->count_line, this->count_column);
		for (int i = 0; i < this->count_line; i++) {
			for (int j = 0; j < this->count_column; j++) {
				result[i][j] = this->matrix[i][j] + this->matrix[i][j];
			}
		}
		return result;
	}

	void Change(T element, int i, int j) {
		this->matrix[i][j] = element;
	}

	void Print(std::string name) {
		std::cout << "Matrix " + name << std::endl;
		for (int i = 0; i < count_line; i++) {
			for (int j = 0; j < count_column; j++) {
				std::cout << std::setw(3) << matrix[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

};

int main() {
	srand(time(0));
	/*Plenty<int> A(5);
	Plenty<int> B(7);
	A.RandomFillInt();
	B.RandomFillInt();
	std::cout << A << std::endl;
	std::cout << B << std::endl;
	Plenty<int> C = A + B;
	std::cout << C;*/

	Line line_1("Dog");
	Line line_2("Xytor");
	Line line_3("Memory");
	Line line_4("Cat");

	Matrix<Line> matrix(2, 2);
	matrix.Change(line_1, 0, 0);
	matrix.Change(line_2, 0, 1);
	matrix.Change(line_3, 1, 0);
	matrix.Change(line_4, 1, 1);
	matrix.Print("LINE");

	return 0;
}