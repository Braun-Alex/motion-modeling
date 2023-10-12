#include "crystal.h"

int main() {
    int countOfCells, countOfAtoms;
    double probability;

    std::cout << "Введіть значення кількості комірок кристала:\n";
    std::cin >> countOfCells;
    assert(countOfCells > 0);

    std::cout << "Введіть значення кількості атомів:\n";
    std::cin >> countOfAtoms;
    assert(countOfAtoms > 0);

    std::cout << "Введіть значення ймовірності переходу:\n";
    std::cin >> probability;
    assert(probability >= 0.0);
    assert(probability <= 1.0);

    std::cout << "Імітація броунівського руху..." << "\n";

    Crystal crystal(countOfCells, countOfAtoms);

    crystal.start(probability);

    crystal.stop();

    int sumOfAtoms = 0;
    for (int i = 0; i < countOfCells; i++) {
        sumOfAtoms += crystal.getCell(i);
    }

    std::cout << "Значення кількості атомів після проведення експерименту: " << sumOfAtoms;

    return 0;
}