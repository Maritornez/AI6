#include "ART1.h"

void ART1::Initialize()  // инициализация
{
    //setlocale(LC_ALL, "Russian");
    for (int i = 0; i < MaxClusters; i++) {
        for (int j = 0; j < MaxItems; j++) {
            Clusters[i][j] = 0;  Sum[i][j] = 0;
        }
        Members[i] = 0;
    }
    for (int j = 0; j < MaxClients; j++) Group[j] = -1;
}

void  ART1::AndVectors(TVector  R, TVector V, TVector W)  // И векторов
{
    for (int i = 0; i < MaxItems; i++) R[i] = V[i] & W[i];
}

void  ART1::UpdateVectors(int K)  // обновление прототипа K
{
    int i, j;
    bool f;
    if ((K < 0) || (K >= MaxClusters)) return;
    f = true;
    for (i = 0; i < MaxItems; i++) {
        Clusters[K][i] = 0;  Sum[K][i] = 0;
    }
    for (j = 0; j < MaxClients; j++) {
        if (Group[j] == K) {
            if (f) {
                memcpy(Clusters[K], Data[j], sizeof Data[j]);
                memcpy(Sum[K], Data[j], sizeof Data[j]);
                f = false;
            } else {
                AndVectors(Clusters[K], Clusters[K], Data[j]);
                for (i = 0; i < MaxItems; i++) Sum[K][i] += Data[j][i];
            }
        }
    }
}

int  ART1::CreateVector(TVector V)  // новый кластер
{
    int i = -1;   // индекс кластера
    do {
        i++;  if (i >= MaxClusters) return -1;
    } while (Members[i] != 0);
    N++;
    Members[i] = 1;
    memcpy(Clusters[i], V, sizeof TVector);
    return i;
}

int  ART1::OnesVector(TVector V)  // число 1 в векторе
{
    int k = 0;  // счетчик
    for (int j = 0; j < MaxItems; j++) if (V[j] == 1) k++;
    return k;
}

void  ART1::ExecuteART1()  // применение алгоритма ART1
{
    TVector R;          // вектор "И" результата
    int PE;             // значимость нового вектора
    int P;              // значимость вектора-прототипа
    int E;              // значимость вектора покупателя
    bool Test;          // флаг прохождения тестов
    int i, j;           // индексы клиента, прототипа
    int count = 50;     // счетчик предельных итераций
    bool exit = false;  // флаг выхода из цикла
    int s;              // старый номер кластера
    do {
        exit = true;
        for (i = 0; i < MaxClients; i++) {
            for (j = 0; j < MaxClusters; j++) {
                if (Members[j] > 0) {
                    AndVectors(R, Data[i], Clusters[j]);
                    PE = OnesVector(R);
                    P = OnesVector(Clusters[j]);
                    E = OnesVector(Data[i]);
                    Test = ((PE / (Beta + P)) > (E / (Beta + MaxItems)));
                    if (Test) Test = (((double)PE / E) < Rho);
                    if (Test) Test = (Group[i] != j);
                    if (Test) {
                        s = Group[i];  Group[i] = j;
                        if (s >= 0) {
                            Members[s]--;
                            if (Members[s] == 0) N--;
                        }
                        Members[j]++;
                        UpdateVectors(s);  UpdateVectors(j);
                        exit = false;  break;
                    }
                }
            }
            if (Group[i] == -1) {
                Group[i] = CreateVector(Data[i]);
                exit = false;
            }
        }
        count--;
    } while ((!exit) && (count > 0));
}

void  ART1::ShowClusters()  // показ кластеров
{
    for (int i = 0; i < N; i++) {
        std::cout << "Вектор-прототип " << std::setw(2) << i + 1 << " : ";
        for (int j = 0; j < MaxItems; j++) std::cout << Clusters[i][j] << " ";
        std::cout << std::endl;
        for (int k = 0; k < MaxClients; k++)
            if (Group[k] == i) {
                std::cout << "Решение  " << std::setw(2) << k + 1 << "     : ";
                for (int j = 0; j < MaxItems; j++) std::cout << Data[k][j] << " ";
                std::cout << std::endl;
            }
    }
    std::cout << std::endl << std::endl;
}

void  ART1::MakeAdvise(int p)  // рекомендации
{
    int best = -1;
    int max = 0;
    for (int i = 0; i < MaxItems; i++) {
        if ((Data[p][i] == 0) && (Sum[Group[p]][i] > max)) {
            best = i;  max = Sum[Group[p]][i];
        }
    }
    std::cout << "Для покупателя " << p + 1 << " ";
    if (best >= 0) std::cout << "рекомендация - " << ItemName[best] << std::endl;
    else std::cout << "нет рекомендаций" << std::endl;
    std::cout << "Уже выбраны: ";
    for (int i = 0; i < MaxItems; i++)
        if (Data[p][i] != 0) std::cout << ItemName[i] << " ";
    std::cout << std::endl;
}

ART1::ART1(std::vector<std::vector<int>> vector) {
    for (size_t i = 0; i < MaxClients; i++) {
	    for (int j = 0; j < MaxItems; j++) {
			    Data[i][j] = vector[i][j];
	    }
    }
}

int  ART1::main() {
    Initialize();
    ExecuteART1();
    ShowClusters();
    //for (int p = 0; p < MaxClients; p++) MakeAdvise(p);
    //system("pause");
    return 0;
}
