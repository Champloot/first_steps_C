#include <stdio.h>
#include <windows.h>
#define HEIGHT 25
#define WIDTH 25
#define LYES 1
#define LNO 0


typedef int Tab[HEIGHT][WIDTH];
//Создание и вывод игрового поля. Там где жизнь 'Q', где нет '.'
void printTab(Tab table) {
    int height, width;

    for (height = 0; height < HEIGHT; height++) {
        for (width = 0; width < WIDTH; width++) {
            if (table[height][width] == LYES) {
                printf("Q");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
    printf("\n");
}

//Очищаем игровое поле от всех живых
void clearTable(Tab table) {
    int height, width;
    for (height = 0; height < HEIGHT; height++) {
        for (width = 0; width < WIDTH; width++) {
            table[height][width] = LNO;
        }
    }
}

//Если вышли за пределы игровой зоны или клетка мертва возвращаем 0, иначе 1
int getNeighborValue(Tab table, int row, int col) {
    if (row < 0 || row >= HEIGHT
        || col < 0 || col >= WIDTH
        || table[row][col] != LYES )
    {
        return 0;
    } else {
        return 1;
    }
}

//Функция чекает все соседние координаты на наличие соседей
int getNeighborCount(Tab table, int row, int col) {
    int neighbor = 0;

    neighbor += getNeighborValue(table, row - 1, col - 1);
    neighbor += getNeighborValue(table, row - 1, col);
    neighbor += getNeighborValue(table, row - 1, col + 1);
    neighbor += getNeighborValue(table, row, col - 1);
    neighbor += getNeighborValue(table, row, col + 1);
    neighbor += getNeighborValue(table, row + 1, col - 1);
    neighbor += getNeighborValue(table, row + 1, col);
    neighbor += getNeighborValue(table, row + 1, col + 1);

    return neighbor;
}
//Проверка выполнения правил
void calc(Tab tableA) {
    Tab tableB;
    int neighbor, height, width;

    for (height = 0; height < HEIGHT; height++) {
        for (width = 0; width < WIDTH; width++) {
            neighbor = getNeighborCount(tableA, height, width);
            if (neighbor==3) {
                tableB[height][width] = LYES;
            } else if (neighbor == 2 && tableA[height][width] == LYES) {
                tableB[height][width] = LYES;
            } else {
                tableB[height][width] = LNO;
            }
        }
    }
    for (height = 0; height < HEIGHT; height++) {
        for (width = 0; width < WIDTH; width++) {
            tableA[height][width] = tableB[height][width];
        }
    }
}
//Начальные данные(можно и свапнуть)
void loaddata(Tab table) {

    table[10][4] = LYES;
    table[11][5] = LYES;
    table[12][5] = LYES;
    table[12][4] = LYES;
    table[12][3] = LYES;
}
//Главная функция
int main(int argc, char *argv[])
{
    Tab table;
    int gen = 0;
    int i;
    clearTable(table);
    loaddata(table);
    printTab(table);
    for(gen=0;gen<100000;gen++)
    {
        system("cls");
        calc(table);
        printTab(table);
        printf("Update# %d\n", gen);
        Sleep(500);
    }
    return 0;
}


