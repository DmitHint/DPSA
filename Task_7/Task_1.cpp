#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    char symbol;
    double probability;
    string code;
};

void shannonFano(vector<Node>& nodes, int start, int end) {
    if (start == end - 1) {
        return; // Одна вершина - ничего не делаем
    }

    // Находим разделитель
    double totalProbability = 0.0;
    for (int i = start; i < end; ++i) {
        totalProbability += nodes[i].probability;
    }

    double currentProbability = 0.0;
    int splitIndex = start;
    double minDifference = totalProbability;

    while (currentProbability <= totalProbability / 2 && splitIndex < end) {
        currentProbability += nodes[splitIndex].probability;
        double difference = abs(totalProbability - 2 * currentProbability);
        if (difference < minDifference) {
            minDifference = difference;
            splitIndex++;
        }
        else {
            break;
        }
    }

    // Присваиваем коды
    for (int i = start; i < splitIndex; ++i) {
        nodes[i].code += '0';
    }
    for (int i = splitIndex; i < end; ++i) {
        nodes[i].code += '1';
    }

    // Рекурсивно вызываем для обеих частей
    shannonFano(nodes, start, splitIndex);
    shannonFano(nodes, splitIndex, end);
}

int main() {
    setlocale(LC_ALL, "ru");

    string phrase = "По-турецки говорили. Чяби, чяряби Чяряби, чяби-чяби. Мы набрали в рот воды.";

    // Подсчет вероятностей символов
    vector<Node> nodes;
    for (char ch : phrase) {
        auto it = find_if(nodes.begin(), nodes.end(), [ch](const Node& node) {
            return node.symbol == ch;
            });

        if (it == nodes.end()) {
            nodes.push_back({ ch, 1, "" });
        }
        else {
            it->probability += 1;
        }
    }

    for (auto& node : nodes) {
        node.probability /= phrase.length();
    }

    // Сортировка узлов по вероятностям
    sort(nodes.begin(), nodes.end(), [](const Node& a, const Node& b) {
        return a.probability > b.probability;
        });

    // Применение метода Шеннона–Фано
    shannonFano(nodes, 0, nodes.size());

    // Вывод кодов для каждого символа
    for (const auto& node : nodes) {
        cout << "Символ: '" << node.symbol << "' , Код: " << node.code << std::endl;
    }

    return 0;
}