#ifndef CELL_H
#define CELL_H
#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <random>
#include <cmath>


std::random_device rndDev;
std::mt19937 mt(rndDev());
std::uniform_real_distribution<double> randDist(0, 1);
inline double rnd() {
    return randDist(mt);
}


inline std::string color(int i) {
    return "\e[48;5;" + std::to_string(i) + "m" + " \e[0m";
}


inline int mDist(int x1, int y1, int x2, int y2) {
    return std::abs(x2 - x1) + std::abs(y2 - y1);
}


class Cell {
    public:
        int width;
        int height;
        int R;
        int T;
        int C;
        int N;
        int* data;
        int* data_p;
        Cell() {};
        Cell(int _width, int _height, int _R, int _T, int _C, int _N) {
            width = _width;
            height = _height;
            R = _R;
            T = _T;
            C = _C;
            N = _N;
            data = new int[width*height];
            data_p = new int[width*height];
        };
        ~Cell() {
            delete[] data;
            delete[] data_p;
        };


        int get(int i, int j) {
            if(i < 0 || i >= width || j < 0 || j >= height) {
                return 0;
            }
            return data[i + width*j];
        };
        int getP(int i, int j) {
            if(i < 0 || i >= width || j < 0 || j >= height) {
                return 0;
            }
            return data_p[i + width*j];
        };
        void set(int i, int j, int val) {
            if(i < 0 || i >= width || j < 0 || j >= height) {
                std::cout << "Invalid access at (" << i << ", " << j << ")" << std::endl;
                exit(1);
            }
            data[i + width*j] = val;
        };


        void init() {
            for(int i = 0; i < width; i++) {
                for(int j = 0; j < height; j++) {
                    int val = (int)(rnd()*C);
                    this->set(i, j, val);
                }
            }
        }
        void draw() {
            for(int j = 0; j < height; j++) {
                for(int i = 0; i < width; i++) {
                    int val = this->get(i, j);
                    std::cout << color(val);
                }
                std::cout << "\n";
            }
            std::cout << "\r\e[" + std::to_string(height) + "A" << std::flush;
        }
        void saveCell() {
            for(int i = 0; i < width; i++) {
                for(int j = 0; j < height; j++) {
                    data_p[i + width*j] = this->get(i, j);
                }
            }
        };
        void update() {
            this->saveCell();

            for(int i = 0; i < width; i++) {
                for(int j = 0; j < height; j++) {
                    int val = this->get(i, j);
                    int count = 0;
                    for(int idx = i - R; idx <= i + R; idx++) {
                        for(int idx2 = j - R; idx2 <= j + R; idx2++) {
                            if(idx == idx2)
                                continue;
                            if(N == 1)
                                if(mDist(i, j, idx, idx2) > R)
                                    continue;
                            int val2 = this->getP(idx, idx2);
                            if((val + 1)%C == val2)
                                count++;
                        }
                    }

                    if(count >= T) {
                        this->set(i, j, (val + 1)%C);
                    }
                }
            }
        };
};
#endif
