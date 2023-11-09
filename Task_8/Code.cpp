#include <iostream>
#include <vector>

using namespace std;

int findMinWeightPath(vector<vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    // Создаем двумерный массив для хранения минимальных весов
    vector<vector<int>> dp(rows, vector<int>(cols, 0));

    // Инициализируем первую клетку
    dp[0][0] = grid[0][0];

    // Инициализируем первый столбец
    for (int i = 1; i < rows; ++i) {
        dp[i][0] = dp[i - 1][0] + grid[i][0];
    }

    // Инициализируем первую строку
    for (int j = 1; j < cols; ++j) {
        dp[0][j] = dp[0][j - 1] + grid[0][j];
    }

    // Заполняем остальные ячейки
    for (int i = 1; i < rows; ++i) {
        for (int j = 1; j < cols; ++j) {
            // Выбираем минимальный вес из трех возможных направлений
            dp[i][j] = grid[i][j] + min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1]));
        }
    }

    // Возвращаем минимальный вес маршрута до правой нижней клетки
    return dp[rows - 1][cols - 1];
}

int main() {
    setlocale(LC_ALL, "ru");

    // Пример входных данных
    vector<vector<int>> grid = {
        {1, 3, 1},
        {2, 2, 4},
        {5, 6, 1}
    };

    // Вызываем функцию и выводим результат
    int minWeight = findMinWeightPath(grid);
    cout << "Минимальный вес маршрута: " << minWeight << endl;

    return 0;
}