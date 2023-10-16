#include "crystal.h"

Crystal::Crystal(int countOfCells, int countOfAtoms): cells(countOfCells, 0), totalAtoms(countOfAtoms), gen(rd()), dist(0.0, 1.0) {
    assert(countOfCells > 0);
    assert(countOfAtoms > 0);
    cells[0] = countOfAtoms;
}

void Crystal::move(int& position, double probability) {
    assert(position >= 0);
    assert(probability >= 0.0);
    assert(probability <= 1.0);

    double randValue = dist(gen);

    if (randValue > probability) {
        position += 1;
        if (position >= cells.size())
            position = cells.size() - 1;
    } else {
        position -= 1;
        if (position < 0)
            position = 0;
    }
}

void Crystal::moveAtom(int position, double probability) {
    assert(position >= 0);
    assert(probability >= 0.0);
    assert(probability <= 1.0);
    while (running) {
        int previousPosition = position;
        move(position, probability);

        std::unique_lock<std::mutex> lock(mtx);
        --cells[previousPosition];
        ++cells[position];
    }
}

int Crystal::getCell(int i) {
    assert(i >= 0);
    assert(i <= cells.size() - 1);
    std::unique_lock<std::mutex> lock(mtx);
    return cells[i];
}

void Crystal::start(double probability) {
    assert(probability >= 0.0);
    assert(probability <= 1.0);
    running = true;

    for (int i = 0; i < totalAtoms; i++) {
        threads.emplace_back(&Crystal::moveAtom, this, 0, probability);
    }

    for (int i = 0; i < 10; i++) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        printSnapshot();
    }
}

void Crystal::stop() {
    running = false;
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    threads.clear();
}

void Crystal::printSnapshot() {
    std::vector<int> snapshot;
    {
        std::unique_lock<std::mutex> lock(mtx);
        snapshot = cells;
    }
    std::cout << "Знімок " << snapshotNumber << ": ";
    for (const auto& cell : snapshot) {
        std::cout << cell << " ";
    }
    std::cout << "\n";
    ++snapshotNumber;
}