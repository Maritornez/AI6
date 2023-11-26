#include <iostream>
#include <iomanip>
#include <string>
#include "TransportProblemOrdinarySolution.h"
#include "ART1.h"

void ShowMatrix(std::vector<std::vector<int>> matrix, int margin) {
	for (auto row : matrix) {
		for (auto val : row) {
			std::cout << std::setw(margin + 1) << val << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int main() {
    std::srand(std::time(nullptr));

	const int solutions_amount = 10;
	const int N = 10;
	const int K = 10;

	std::vector<std::vector<std::vector<int>>> solutions_at_the_beginning;
	std::vector<std::vector<std::vector<int>>> solutions_in_the_middle;
	std::vector<std::vector<std::vector<int>>> solutions_in_the_end;



	TransportProblemOrdinarySolution transportProblemOrdinarySolution_AtTheBeginning(N, K, 1, 10, 2, 10, 1, 100.0, 30, 0.98, 100);
	for (size_t i = 0; i < solutions_amount; i++) {
		solutions_at_the_beginning.push_back(transportProblemOrdinarySolution_AtTheBeginning.Get_SolutionInTheEnd());
	}

	TransportProblemOrdinarySolution transportProblemOrdinarySolution_InTheMiddle(N, K, 1, 10, 2, 10, 1, 100.0, 60, 0.98, 100);
	for (size_t i = 0; i < solutions_amount; i++) {
		solutions_in_the_middle.push_back(transportProblemOrdinarySolution_InTheMiddle.Get_SolutionInTheEnd());
	}

    TransportProblemOrdinarySolution transportProblemOrdinarySolution_InTheEnd(N, K, 1, 10, 2, 10, 1, 100.0, 60/*0.01*/, 0.98, 100);
    for (size_t i = 0; i < solutions_amount; i++) {
		solutions_in_the_end.push_back(transportProblemOrdinarySolution_InTheEnd.Get_SolutionInTheEnd());
    }


	std::cout << "Матрицы планов перевозок:" << std::endl;
	std::cout << "Алгоритм проработал недолго" << std::endl;
	for (auto the_solution : solutions_at_the_beginning) {
		ShowMatrix(the_solution, std::to_string(transportProblemOrdinarySolution_AtTheBeginning.get_plan_max()).length());
	}
	std::cout << "Алгоритм проработал до середины" << std::endl;
	for (auto the_solution : solutions_in_the_middle) {
		ShowMatrix(the_solution, std::to_string(transportProblemOrdinarySolution_InTheMiddle.get_plan_max()).length());
	}
	std::cout << "Алгоритм проработал до конца" << std::endl;
	for (auto the_solution : solutions_in_the_end) {
		ShowMatrix(the_solution, std::to_string(transportProblemOrdinarySolution_InTheEnd.get_plan_max()).length());
	}





	// Переработка матриц в векторах solutions в одни большие векторы
	
	//std::vector<std::vector<std::vector<int>>> solutions_at_the_beginning;
	std::vector<std::vector<int>> solutions_at_the_beginning_flattened;
	for (int k = 0; k < solutions_at_the_beginning.size(); k++) {
		solutions_at_the_beginning_flattened.push_back(std::vector<int>());
		for (int i = 0; i < solutions_at_the_beginning[0].size(); i++) {
			for (int j = 0; j < solutions_at_the_beginning[0][0].size(); j++) {
				solutions_at_the_beginning_flattened[k].push_back(solutions_at_the_beginning[k][i][j]);
			}
		}
	}
	//std::vector<std::vector<std::vector<int>>> solutions_in_the_middle;
	std::vector<std::vector<int>> solutions_in_the_middle_flattened;
	for (int k = 0; k < solutions_in_the_middle.size(); k++) {
		solutions_in_the_middle_flattened.push_back(std::vector<int>());
		for (int i = 0; i < solutions_in_the_middle[0].size(); i++) {
			for (int j = 0; j < solutions_in_the_middle[0][0].size(); j++) {
				solutions_in_the_middle_flattened[k].push_back(solutions_in_the_middle[k][i][j]);
			}
		}
	}
	//std::vector<std::vector<std::vector<int>>> solutions_in_the_end;
	std::vector<std::vector<int>> solutions_in_the_end_flattened;
	for (int k = 0; k < solutions_in_the_end.size(); k++) {
		solutions_in_the_end_flattened.push_back(std::vector<int>());
		for (int i = 0; i < solutions_in_the_end[0].size(); i++) {
			for (int j = 0; j < solutions_in_the_end[0][0].size(); j++) {
				solutions_in_the_end_flattened[k].push_back(solutions_in_the_end[k][i][j]);
			}
		}
	}


	std::cout << "Матрицы планов перевозок в виде строки:" << std::endl;
	std::cout << "Алгоритм проработал недолго" << std::endl;
	for (auto the_matrix : solutions_at_the_beginning_flattened) {
		for (auto val : the_matrix) {
			std::cout << std::setw(std::to_string(transportProblemOrdinarySolution_AtTheBeginning.get_plan_max()).length()) << val << ' ';
		}
		std::cout << std::endl << std::endl;
	}
	std::cout << "Алгоритм проработал до середины" << std::endl;
	for (auto the_matrix : solutions_in_the_middle_flattened) {
		for (auto val : the_matrix) {
			std::cout << std::setw(std::to_string(transportProblemOrdinarySolution_InTheMiddle.get_plan_max()).length()) << val << ' ';
		}
		std::cout << std::endl << std::endl;
	}
	std::cout << "Алгоритм проработал до конца" << std::endl;
	for (auto the_matrix : solutions_in_the_end_flattened) {
		for (auto val : the_matrix) {
			std::cout << std::setw(std::to_string(transportProblemOrdinarySolution_InTheEnd.get_plan_max()).length()) << val << ' ';
		}
		std::cout << std::endl << std::endl;
	}


	// Переработка векторов в бинарные векторы

	//std::vector<std::vector<int>> solutions_at_the_beginning_flattened;
	for (size_t i = 0; i < solutions_at_the_beginning_flattened.size(); i++) {
		for (size_t j = 0; j < solutions_at_the_beginning_flattened[0].size(); j++) {
			if (solutions_at_the_beginning_flattened[i][j] > 0) {
				solutions_at_the_beginning_flattened[i][j] = 1;
			}
		}
	}
	//std::vector<std::vector<int>> solutions_in_the_middle_flattened;
	for (size_t i = 0; i < solutions_in_the_middle_flattened.size(); i++) {
		for (size_t j = 0; j < solutions_in_the_middle_flattened[0].size(); j++) {
			if (solutions_in_the_middle_flattened[i][j] > 0) {
				solutions_in_the_middle_flattened[i][j] = 1;
			}
		}
	}
	//std::vector<std::vector<int>> solutions_in_the_end_flattened;
	for (size_t i = 0; i < solutions_in_the_end_flattened.size(); i++) {
		for (size_t j = 0; j < solutions_in_the_end_flattened[0].size(); j++) {
			if (solutions_in_the_end_flattened[i][j] > 0) {
				solutions_in_the_end_flattened[i][j] = 1;
			}
		}
	}

	std::cout << "Матрицы планов перевозок в виде строки:" << std::endl;
	std::cout << "Алгоритм проработал недолго" << std::endl;
	for (auto the_matrix : solutions_at_the_beginning_flattened) {
		for (auto val : the_matrix) {
			std::cout << std::setw(std::to_string(transportProblemOrdinarySolution_AtTheBeginning.get_plan_max()).length()) << val << ' ';
		}
		std::cout << std::endl << std::endl;
	}
	std::cout << "Алгоритм проработал до середины" << std::endl;
	for (auto the_matrix : solutions_in_the_middle_flattened) {
		for (auto val : the_matrix) {
			std::cout << std::setw(std::to_string(transportProblemOrdinarySolution_InTheMiddle.get_plan_max()).length()) << val << ' ';
		}
		std::cout << std::endl << std::endl;
	}
	std::cout << "Алгоритм проработал до конца" << std::endl;
	for (auto the_matrix : solutions_in_the_end_flattened) {
		for (auto val : the_matrix) {
			std::cout << std::setw(std::to_string(transportProblemOrdinarySolution_InTheEnd.get_plan_max()).length()) << val << ' ';
		}
		std::cout << std::endl << std::endl;
	}



	// Где-то здесь переполнение

	
	// Начинает работу алгоритм ART1
	ART1 art1_begin(solutions_at_the_beginning_flattened);
	ART1 art1_middle(solutions_in_the_middle_flattened);
	ART1 art1_end(solutions_in_the_end_flattened);

	std::cout << "Алгоритм проработал недолго" << std::endl;
	art1_begin.main();
	std::cout << "Алгоритм проработал до середины" << std::endl;
	art1_middle.main();
	std::cout << "Алгоритм проработал до конца" << std::endl;
	art1_end.main();

	


    //system("pause");
    return 0;
}
