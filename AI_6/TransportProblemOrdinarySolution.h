#pragma once

#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <string>

class TransportProblemOrdinarySolution {
private:
    const int N = 10;             // число складов (y)
    const int K = 11;          // число магазинов (x)
    const int cost_min = 1;       // минимальная цена перевозки
    const int cost_max = 10;      // максимальная цена перевозки
    const int plan_min = 2;       // минимальное значение плана перевозки из какого-то склада в какой-то магазин
    const int plan_max = 10;      // максимальное значение плана перевозки из какого-то склада в какой-то магазин
    const int transfer_size = 1;  // размер изменения величины перевоза товара в функции Swap()

    const double Tn = 1000.0;      // начальная температура
    const double Tk = 0.01;       // конечная температура
    const double Alfa = 0.98;     // скорость охлаждения
    const int ST = 1000;          // число итераций при смене T

    struct TSolution {            // решение
        std::vector<std::vector<int>> plan; // матрица плана перевозок - кодировка решения
        int Energy;               // энергия решения    
    };

    std::vector<std::vector<int>> cost;     // матрица стоимости перевозок

    TSolution Current;            // текущее решение
    TSolution Working;            // рабочее решение
    TSolution Best;               // лучшее решение

    double Random_double(double min, double max);  // случайное число от min до max

    int random_int(int min, int max); // случайное целочисленное число от min до max 

    std::vector<std::vector<int>> generate_cost_matrix(int N, int K);

    void show_cost_matrix(std::vector<std::vector<int>> matrix);

    void Swap(TSolution* M);

    void New(TSolution* M);

    void CalcEnergy(TSolution* M);

    void Copy(TSolution* MD, TSolution* MS);

    void Show(TSolution M);

public:
    TransportProblemOrdinarySolution(); // конструктор

    TransportProblemOrdinarySolution(int N, int K, int cost_min, int cost_max, int plan_min, int plan_max, int transfer_size, double Tn, double Tk, double Alfa, int ST); // конструктор с параметрами

	~TransportProblemOrdinarySolution(); // деструктор

    int get_plan_max();
    int get_N();
	int get_K();

    std::vector<std::vector<int>> Get_SolutionInTheEnd();
};
