#include "TransportProblemOrdinarySolution.h"








double TransportProblemOrdinarySolution::Random_double(double min, double max) { // случайное число от min до max
    return (double)(rand()) * (max - min) / RAND_MAX + min;
}

int TransportProblemOrdinarySolution::random_int(int min, int max) { // случайное целочисленное число от min до max 
    return (rand() % (max - min + 1)) + min;
}

std::vector<std::vector<int>> TransportProblemOrdinarySolution::generate_cost_matrix(int N, int K) {
    std::vector<std::vector<int>> matrix;
    for (int y = 0; y < N; y++) {
        std::vector<int> v;
        for (int x = 0; x < K; x++) {
            v.push_back(random_int(cost_min, cost_max));
        }
        matrix.push_back(v);
    }
    return matrix;
}

void TransportProblemOrdinarySolution::show_cost_matrix(std::vector<std::vector<int>> matrix) {
    std::cout << "Матрица стоимостей перевозок:" << std::endl;
    for (auto row : matrix) {
        for (auto val : row) {
            std::cout << std::setw(std::to_string(cost_max).length()) << val << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

}

void TransportProblemOrdinarySolution::Swap(TSolution* M) { // модификация решения
    int timeoutSeconds = 0.00001;
    std::chrono::steady_clock::time_point startTime;
    int timeoutSecondsOuterLoop1 = 0.001;
    std::chrono::steady_clock::time_point startTime_for_outer_loop1;
    int timeoutSecondsOuterLoop2 = 0.001;
    std::chrono::steady_clock::time_point startTime_for_outer_loop2;

    if (random_int(0, 1)) {
        // Нахождение двух случайных элементов в плане, чтобы они образовали прямоугольник
        //
        // - ----→ +
        // |       ↑
        // |       |
        // ↓       |
        // + ←---- -
        //

        int x1 = -1, y1 = -1;
        int x2 = -1, y2 = -1;
        while (true) {
            startTime_for_outer_loop1 = std::chrono::high_resolution_clock::now();

            startTime = std::chrono::high_resolution_clock::now();
            do {
                x1 = random_int(0, K - 2);
                y1 = random_int(0, N - 2);

                auto currentTime = std::chrono::high_resolution_clock::now();
                auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
                if (elapsedTime >= timeoutSeconds) break;
            } while (M->plan[y1][x1] == 0);

            startTime = std::chrono::high_resolution_clock::now();
            do {
                x2 = random_int(x1 + 1, K - 1);
                y2 = random_int(y1 + 1, N - 1);

                auto currentTime = std::chrono::high_resolution_clock::now();
                auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
                if (elapsedTime >= timeoutSeconds) break;
            } while (M->plan[y1][x1] == 0);

            if ((M->plan[y1][x1] == 0) || (M->plan[y2][x2] == 0) || (x1 == -1) || (y1 == -1) || (x2 == -1) || (y2 == -1)) {
                continue;
            } else {
                break;
            }

            auto currentTime = std::chrono::high_resolution_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
            if (elapsedTime >= timeoutSecondsOuterLoop1) break;
        }
        // Изменение четырех элементов в плане
        M->plan[y1][x1] -= transfer_size;
        M->plan[y1][x2] += transfer_size;
        M->plan[y2][x1] += transfer_size;
        M->plan[y2][x2] -= transfer_size;
    } else {
        // Нахождение двух случайных элементов в плане, чтобы они образовали прямоугольник
        //
        // + ←---- -
        // ↑       |
        // |       |
        // |       ↓
        // - ----→ +
        //
        int x1 = -1, y1 = -1;
        int x2 = -1, y2 = -1;
        while (true) {
            startTime_for_outer_loop2 = std::chrono::high_resolution_clock::now();

            startTime = std::chrono::high_resolution_clock::now();
            do {
                x1 = random_int(1, K - 1);
                y1 = random_int(0, N - 2);

                auto currentTime = std::chrono::high_resolution_clock::now();
                auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
                if (elapsedTime >= timeoutSeconds) break;
            } while (M->plan[y1][x1] == 0);

            startTime = std::chrono::high_resolution_clock::now();
            do {
                x2 = random_int(0, x1 - 1);
                y2 = random_int(y1 + 1, N - 1);

                auto currentTime = std::chrono::high_resolution_clock::now();
                auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
                if (elapsedTime >= timeoutSeconds) break;
            } while (M->plan[y1][x1] == 0);

            if ((M->plan[y1][x1] == 0) || (M->plan[y2][x2] == 0) || (x1 == -1) || (y1 == -1) || (x2 == -1) || (y2 == -1)) {
                continue;
            } else {
                break;
            }

            auto currentTime = std::chrono::high_resolution_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
            if (elapsedTime >= timeoutSecondsOuterLoop2) break;

        }
        // Изменение четырех элементов в плане
        M->plan[y1][x1] -= transfer_size;
        M->plan[y1][x2] += transfer_size;
        M->plan[y2][x1] += transfer_size;
        M->plan[y2][x2] -= transfer_size;
    }

}


void TransportProblemOrdinarySolution::New(TSolution* M) { // инициализация решения (плана перевозок)
    // Заполнение плана случайными числами
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < K; x++) {
            M->plan[y][x] = random_int(plan_min, plan_max);
        }
    }
}


void TransportProblemOrdinarySolution::CalcEnergy(TSolution* M) { // расчет энергии
    // Сложение всех произведений соответствующих элементов матриц cost и plan
    int sum = 0;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < K; x++) {
            sum += cost[y][x] * M->plan[y][x];
        }
    }
    M->Energy = sum;
}


void TransportProblemOrdinarySolution::Copy(TSolution * MD, TSolution * MS) { // копирование решения
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < K; x++) {
            MD->plan[y][x] = MS->plan[y][x];
        }
    }
    MD->Energy = MS->Energy;
}


void TransportProblemOrdinarySolution::Show(TSolution M) { // отображение на экране матрицы
    std::cout << "Решение:" << std::endl;
    for (auto row : M.plan) {
        for (auto val : row) {
            std::cout << std::setw(std::to_string(plan_max).length() + 1) << val << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}



TransportProblemOrdinarySolution::TransportProblemOrdinarySolution() {
    cost = generate_cost_matrix(N, K);
}

TransportProblemOrdinarySolution::TransportProblemOrdinarySolution(int N, int K, int cost_min, int cost_max, int plan_min, int plan_max, int transfer_size, double Tn, double Tk, double Alfa, int ST)
    : N(N), K(K), cost_min(cost_min), cost_max(cost_max), plan_min(plan_min), plan_max(plan_max), transfer_size(transfer_size), Tn(Tn), Tk(Tk), Alfa(Alfa), ST(ST) {
    cost = generate_cost_matrix(N, K);
}

TransportProblemOrdinarySolution::~TransportProblemOrdinarySolution() {}


int TransportProblemOrdinarySolution::get_plan_max() {
    return plan_max;
}

int TransportProblemOrdinarySolution::get_N() {
    return N;
}

int TransportProblemOrdinarySolution::get_K() {
    return K;
}



std::vector<std::vector<int>> TransportProblemOrdinarySolution::Get_SolutionInTheEnd() {
    //std::srand(std::time(nullptr));

    // Инициализация матрицы стоимостей перевозок
    //cost = generate_cost_matrix(N, K);
    show_cost_matrix(cost);

    double  T = Tn;           // температура
    bool    fBest = false;    // флаг лучшего решения
    bool    fNew;             // флаг нового решения
    int     Time = 0;         // этап поиска
    // Инициализация векторов (нулями)
    Current.plan.resize(N, std::vector<int>(K));
    Working.plan.resize(N, std::vector<int>(K));
    Best.plan.resize(N, std::vector<int>(K));

    New(&Current);
    Show(Current);

    CalcEnergy(&Current);

    Copy(&Best, &Current);
    Copy(&Working, &Current);

    while ((T > Tk) && (Best.Energy > 0)) {
        for (int Step = 0; Step < ST; Step++) {
            fNew = false;
            Swap(&Working);
            CalcEnergy(&Working);
            if (Working.Energy <= Current.Energy) {
                fNew = true;
            } else {
                double Delta = Working.Energy - Current.Energy;  // разница энергий
                double P = exp(-Delta / T);                      // вероятность допуска
                if (P > Random_double(0, 1)) fNew = true;
            }
            if (fNew) {
                fNew = false;
                Copy(&Current, &Working);
                if (Current.Energy < Best.Energy) {
                    Copy(&Best, &Current);
                    fBest = true;
                }
            } else Copy(&Working, &Current);
        }
        std::cout << "Temp=" << T << " Energy=" << Best.Energy << std::endl;
        T *= Alfa;
        Time++;
    }
    if ((fBest) && (N < 80)) Show(Best);
    return Best.plan;
}
