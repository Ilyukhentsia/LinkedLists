#include <iostream>
#include <string>
#include <string>
#include <vector>
#include <stdexcept>   // для std::runtime_error
#include <climits>      // для INT_MAX и INT_MIN

// Ячейка хранит next
struct Cell {
    int value;
    Cell* next;     // следующий
};
// Список хранит оба указателя: top (голова) и bottom (хвост)
struct SingleList {
    Cell* top = nullptr;
    Cell* bottom = nullptr;
};
// Ячейка хранит next и prev
struct DCell {
    int value;
    DCell* next;     // следующий
    DCell* prev;     // предыдущий
};
// Список хранит оба указателя: top (голова) и bottom (хвост)
struct DoubleList {
    DCell* top = nullptr;
    DCell* bottom = nullptr;
};

void AddAtEndSingle(SingleList& list, int value);
bool deleteValue(SingleList& list, int value);
int maxValue(const SingleList& list);
void addAtBeginDouble(DoubleList& list, int value);
void addAtEndDouble(DoubleList& list, int value);
void insertDouble(DoubleList& list, DCell* pos, DCell* new_cell);
void addAtBeginInsert(DoubleList& list, int value);
void addAtEndInsert(DoubleList& list, int value);
bool deleteValueDouble(DoubleList& list, int value);
void AddAtDoubleSorted(DoubleList& list, int value);
bool istSorted(const SingleList& list);

// ---------- Многопотоковый список планет ----------
struct Planet {
    std::string name;
    double distance, mass, diameter;
    Planet* nextDistance = nullptr;
    Planet* nextMass = nullptr;
    Planet* nextDiameter = nullptr;
};
struct PlanetList {
    std::vector<Planet*> owned;
    Planet* byDistance = nullptr;
    Planet* byMass = nullptr;
    Planet* byDiameter = nullptr;
};
void addPlanet(PlanetList& list, const std::string name, double distance, double mass, double diameter);

Cell* istCicle(Cell* top);