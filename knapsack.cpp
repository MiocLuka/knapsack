#include <iostream>
#include <vector>
#include <fstream>

int solve(int num, int weight, int maxWeight, const std::vector< int >& vecW, const std::vector< int >& vecVal,
          std::vector< bool > used, std::vector< bool >& bestUsed, int& bestVal) {
    
    if (num == vecW.size()) {
        int currVal = 0;
        for (int i = 0; i < used.size(); i++) {
            if (used.at(i)) {
                currVal += vecVal.at(i);
            }
        }

        if (currVal > bestVal) {
            bestVal = currVal;
            bestUsed = used;
        }

        return 0;
    }
    //item will not be taken
    int a = solve(num + 1, weight, maxWeight, vecW, vecVal, used, bestUsed, bestVal);

    //item will be taken IF it fits
    int b = 0;
    if (weight + vecW.at(num) <= maxWeight) {
        used.at(num) = true;
        b = vecVal.at(num) + solve(num + 1, weight + vecW.at(num), maxWeight, vecW, vecVal, used, bestUsed, bestVal);
    }

    int ret = a;
    if (b > ret) ret = b;

    return ret;
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "No input filename given" << std::endl;
        return -1;
    }
    
    std::ifstream in(argv[1]);
    if (!in.is_open()) {
        std::cout << "Could not open file" << argv[1] << std::endl;
        return -2;
    }

    std::vector< int > vecW, vecVal;
    std::vector< bool > used, bestUsed;
    int w, v;
    int bestVal = 0;

    int maxW;
    in >> maxW;
    while (in >> w >> v) {
        vecW.push_back(w);
        vecVal.push_back(v);
        used.push_back(false);
    }

    solve(0, 0, maxW, vecW, vecVal, used, bestUsed, bestVal);
    int totalW = 0;
    for (int i = 0; i < bestUsed.size(); i++) {
        if (bestUsed.at(i)) {
            totalW+= vecW.at(i);
        }
    }
    
    std::cout <<  "With a capacity of " << maxW << " kg, the total value is " 
    << bestVal << " Eur, leading to a total weight of " << totalW << " kg \n"
    << "The following items are included: ";
    for (int i = 0; i < bestUsed.size(); i++) {
        if (bestUsed.at(i)) {
            std::cout << "[" << vecW.at(i) << "," << vecVal.at(i) << "] ";
        }
    }
    std::cout << std::endl;

    return 0;
}
