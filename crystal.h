#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <random>
#include <mutex>
#include <cassert>

class Crystal {
public:
    Crystal(int countOfCells, int countOfAtoms);
    void start(double probability);
    void stop();
    int getCell(int i);
private:
    std::vector<int> cells;
    int totalAtoms;
    std::vector<std::thread> threads;
    bool running = false;
    std::mutex mtx;
    int snapshotNumber = 1;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> dist;
    void move(int& position, double probability);
    void moveAtom(int position, double probability);
    void printSnapshot();
};