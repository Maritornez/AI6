#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

const int MaxClients = 10;         // число покупателей // число решений
const int MaxItems = 10*10;        // число элементов   // число элементов в решении
const int MaxClusters = 3;         // предельное число кластеров

typedef int TVector[MaxItems];
typedef TVector TClusters[MaxClusters];
typedef int TMembers[MaxClusters];
typedef int TGroup[MaxClients];

class ART1 {
private:
    double Beta = 1.0;                 // параметр разрушения связей
    double Rho = 0.9;                  // внимательность


    std::string ItemName[MaxItems] = { "Молоток", "Бумага", "Шоколадка",
        "Отвертка", "Ручка", "Кофе", "Гвоздодер", "Карандаш",
        "Конфеты", "Дрель", "Дырокол" };

    TVector Data[MaxClients]; //=
    //{ {0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0},
    //    {0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    //    {0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0},
    //    {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1},
    //    {1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
    //    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    //    {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    //    {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
    //    {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0},
    //    {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0} };

    TClusters Clusters;  // прототипы кластеров
    TClusters Sum;       // векторы суммирования
    TMembers Members;    // число членов в кластерах
    TGroup Group;        // принадлежность к кластеру
    int N = 0;           // число кластеров


    void Initialize();  // инициализация
    

    void AndVectors(TVector  R, TVector V, TVector W);  // И векторов


    void UpdateVectors(int K);  // обновление прототипа K


    int CreateVector(TVector V);  // новый кластер


    int OnesVector(TVector V);  // число 1 в векторе


    void ExecuteART1();  // применение алгоритма ART1


    void ShowClusters();  // показ кластеров


    void MakeAdvise(int p);  // рекомендации

public:
    ART1(std::vector<std::vector<int>> vector);

    int main();
};
