#include "cell.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <cstdlib>


std::chrono::milliseconds duration(100);
inline void sleep() {
    std::this_thread::sleep_for(duration);
}


int main(int argc, char** argv) {
    if(argc != 7) {
        std::cout << "Invalid parameters" << std::endl;
        exit(1);
    }
    const int W = std::stoi(argv[1]);
    const int H = std::stoi(argv[2]);
    const int R = std::stoi(argv[3]);
    const int T = std::stoi(argv[4]);
    const int C = std::stoi(argv[5]);
    const int N = std::stoi(argv[6]);
    Cell cell(W, H, R, T, C, N);
    cell.init();

    while(true) {
        cell.draw();
        cell.update();
        sleep();
    };
}
