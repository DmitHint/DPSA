#include <iostream>

using namespace std;

struct Specialization {
	string code;       // Код специальности (пример: "09.03.01")
	string university; // Название вуза
};

class SpecializationHashTable {
private:
	static const int TABLE_SIZE = 100; // Размер хеш-таблицы

	struct Record {
		Specialization data;
		bool isOccupied;
	};

	Record table[TABLE_SIZE];

public:

	int hash1(const string& key) {
		int hash = 0;
		for (char c : key) {
			hash += c;
		}
		return hash % TABLE_SIZE;
	}

	int hash2(const string& key) {
		int hash = 0;
		for (char c : key) {
			hash += c * 11;
		}
		return (hash % (TABLE_SIZE - 1)) + 1; // Для избежания коллизий с нулевой функцией
	}

	SpecializationHashTable() {
		for (int i = 0; i < TABLE_SIZE; ++i) {
			table[i].isOccupied = false;
		}

	}

	// Метод для вставки элемента
	void insert(const Specialization& specialization) {
		string key = specialization.code;
		int index = hash1(key);
		int step = hash2(key);

		while (table[index].isOccupied) {
			index = (index + step) % TABLE_SIZE;
		}

		table[index].data = specialization;
		table[index].isOccupied = true;
	}

	// Метод для поиска элемента по ключу
	Specialization* find(const string& code) {
		int index = hash1(code);
		int step = hash2(code);

		while (table[index].isOccupied) {
			if (table[index].data.code == code) {
				return &(table[index].data);
			}
			index = (index + step) % TABLE_SIZE;
		}

		return nullptr; // Элемент не найден
	}

	// Метод для удаления элемента по ключу
	void remove(const string& code) {
		int index = hash1(code);
		int step = hash2(code);

		while (table[index].isOccupied) {
			if (table[index].data.code == code) {
				table[index].isOccupied = false;
				return; // Элемент найден и удален
			}
			index = (index + step) % TABLE_SIZE;
		}
	}

	// Метод для вывода всех элементов
	void display() {
		for (int i = 0; i < TABLE_SIZE; ++i) {
			if (table[i].isOccupied) {
				cout << "Специализация: " << table[i].data.code << ", Название: " << table[i].data.university << endl;
			}
		}
	}
};

void checkSpec(Specialization* spec, string searchKey) {
	if (spec != nullptr) {
		cout << "Найдена специализация с кодом " << searchKey << ": " << spec->university << endl;
	}
	else {
		cout << "Специализация с кодом " << searchKey << " не найдена" << endl;
	}
}

int main()
{
	setlocale(LC_ALL, "ru");

	SpecializationHashTable hashTable;

	// Заполняем хеш-таблицу несколькими записями
	hashTable.insert(Specialization{ "09.03.01", "Вуз 1" });
	hashTable.insert(Specialization{ "09.03.02", "Вуз 2" });
	hashTable.insert(Specialization{ "09.03.03", "Вуз 3" });
	hashTable.insert(Specialization{ "09.03.04", "Вуз 4" });
	hashTable.insert(Specialization{ "09.03.05", "Вуз 5" });

	// Выводим все элементы
	cout << "Все элементы в хеш-таблице:" << std::endl;
	hashTable.display();
	cout << endl;

	// Поиск элемента по ключу
	string searchKey = "09.03.03";
	Specialization* spec = hashTable.find(searchKey);
	checkSpec(spec, searchKey);

	searchKey = "08.01.01";
	spec = hashTable.find(searchKey);
	checkSpec(spec, searchKey);

	// Удаление элемента
	string deleteKey = "09.03.02";
	hashTable.remove(deleteKey);
	cout << "Специализация с кодом " << deleteKey << " удалена" << endl;

	// Выводим все элементы после удаления
	cout << endl;
	cout << "Все элементы в хеш-таблице после удаления:" << endl;
	hashTable.display();
}
