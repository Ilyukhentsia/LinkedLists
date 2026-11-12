#include "../include/connectlist.h"

// ЗАДАНИЕ 1
// ---------- Вставка в конец ----------
void AddAtEndSingle(SingleList& list, int value) {
    Cell* new_cell = new Cell{value};
    if (list.top == nullptr) {
        list.top = new_cell;
        list.bottom = new_cell;
    } else {
        list.bottom->next = new_cell;   // старый хвост знает, кто после
        list.bottom = new_cell;         // сдвигаем хвост
    }
}

// ---------- Удаление ячейки по значению ----------
bool deleteValue(SingleList& list, int value) {
    if (list.top == nullptr) return false;    // список пуст -> удалять нечего
    Cell* prev = nullptr;
    Cell* target = list.top;
    while (target!=nullptr && target->value != value){  // Пока значение не найдено
        prev = target;
        target = target->next;
    }
    if (target==nullptr) return false;
    if (prev!=nullptr){prev->next = target->next;}  // Если не первый, то указатель предыдущего передаем следующему
    else {list.top = target->next;}                 // Иначе, сдвигаем вершину на следующий элемент
    if (list.bottom == target){list.bottom = prev;} // Если последний, то переносим указатель хвоста на предыдущий
    delete target;  // освобождаем память
    return true;
}


// ЗАДАНИЕ 2
// ---------- Максмиальный элемент ----------
int maxValue(const SingleList& list) {
    if (list.top == nullptr) throw std::runtime_error("maxValue: список пуст...");
    int mx = list.top->value;
    for (Cell* i = list.top->next; i!=nullptr; i = i->next)
        if (i->value > mx) mx = i->value;
    return mx;
}


// ЗАДАНИЕ 3-5
// ---------- Добавление в начало ----------
void addAtBeginDouble(DoubleList& list, int value) {
    DCell* new_cell = new DCell{value};
    new_cell->next = list.top;
    if (list.top!=nullptr) {list.top->prev = new_cell;}
    else {list.bottom = new_cell;}
    list.top = new_cell;
}
// ---------- Добавление в конец ----------
void addAtEndDouble(DoubleList& list, int value) {
    DCell* new_cell = new DCell{value};
    new_cell->prev = list.bottom;
    if (list.bottom!=nullptr) {list.bottom->next = new_cell;}
    else {list.top = new_cell;}
    list.bottom = new_cell;
}
// ---------- Добавление с помощью Insert ----------
void insertDouble(DoubleList& list, DCell* pos, DCell* new_cell) {
    if (pos==nullptr){
        new_cell->prev = nullptr;
        new_cell->next = list.top;
        if (list.top) list.top->prev = new_cell;
        else list.bottom = new_cell;
    } else {
        new_cell->prev = pos;
        new_cell->next = pos->next;
        if (pos->next!=nullptr) pos->next->prev = new_cell;
        else list.bottom = new_cell;
        pos->next = new_cell;
    }
}
// Начало
void addAtBeginInsert(DoubleList& list, int value) {insertDouble(list, nullptr, new DCell{value});}
// Конец
void addAtEndInsert(DoubleList& list, int value) {insertDouble(list, list.bottom, new DCell{value});}


// ЗАДАНИЕ 6
// ---------- Удаление ячейки в двунаправленном списке ----------
bool deleteValueDouble(DoubleList& list, int value) {
    DCell* target = list.top;
    while (target!=nullptr && target->value != value) target = target->next;
    if (target == nullptr) return false;
    if (target->prev!=nullptr) target->prev->next = target->next;
    else list.top = target->next;
    if (target->next) target->next->prev = target->prev;
    else list.bottom = target->prev;
    delete target;
    return true;
}


// ЗАДАНИЕ 8
// ---------- Вставка в двунаправленный сортированный список ----------
void AddAtDoubleSorted(DoubleList& list, int value) {
    if (value == INT_MAX || value == INT_MIN) throw std::invalid_argument("Недопустимое значение");
    DCell* new_cell = list.top;
    while (new_cell->next != list.bottom && new_cell->next->value < value) new_cell = new_cell->next;
    DCell* target = new DCell{value};
    target->next = new_cell->next;
    target->prev = new_cell;
    new_cell->next->prev = target;
    new_cell->next = target;
}


// ЗАДАНИЕ 9
// ---------- Проверка сортировки ----------
bool istSorted(const SingleList& list) {
    for (Cell* new_cell = list.top; new_cell!=nullptr && new_cell->next!=nullptr; new_cell = new_cell->next) {
        if (new_cell->value > new_cell->next->value) return false;
    } return true;
}


// ЗАДАНИЕ 10
void addPlanet(PlanetList& list, const std::string name, double distance, double mass, double diameter) {
    Planet* new_cell = new Planet{name, distance, mass, diameter};
    list.owned.push_back(new_cell);
    auto insert = [new_cell](Planet*& head, auto next, auto get) {
        Planet** cur = &head;
        while (*cur && get(*cur) <= get(new_cell)) cur = &((*cur)->*next);
        new_cell->*next = *cur;
        *cur = new_cell;
    };
    insert(list.byDistance, &Planet::nextDistance,
        [](Planet* q) {return q->distance;});
    insert(list.byMass, &Planet::nextMass,
        [](Planet* q) {return q->mass;});
    insert(list.byDiameter, &Planet::nextDiameter,
        [](Planet* q) {return q->diameter;});
}


// ЗАДАНИЕ 11
// ---------- Черепеха и кролик ----------
Cell* istCicle(Cell* top) {
    Cell* slow = top;
    Cell* fast = top;
    while (fast!=nullptr && fast->next!=nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            fast = top;
            while (fast != slow) {
                fast = fast->next;
                slow = slow->next;
            } return fast;
        }
    } return nullptr;
}


// // ============================================================
// //  ЗАДАНИЕ 10. Многопотоковый список планет
// // ============================================================
// struct Planet {
//     std::string name;
//     double distance;
//     double mass;
//     int    diameter;
//     Planet* nextDistance = nullptr;
//     Planet* nextMass     = nullptr;
//     Planet* nextDiameter = nullptr;

//     Planet(std::string n, double d, double m, int dia)
//         : name(std::move(n)), distance(d), mass(m), diameter(dia) {}
// };

// class MultiLinkedList {
// public:
//     ~MultiLinkedList() {
//         Planet* cur = headDistance;
//         while (cur) { Planet* n = cur->nextDistance; delete cur; cur = n; }
//     }
//     void addPlanet(Planet* p) {
//         headDistance = ins(headDistance, p,
//             [](Planet* a){ return a->distance; }, &Planet::nextDistance);
//         headMass = ins(headMass, p,
//             [](Planet* a){ return a->mass; }, &Planet::nextMass);
//         headDiameter = ins(headDiameter, p,
//             [](Planet* a){ return (double)a->diameter; }, &Planet::nextDiameter);
//     }
//     void printByDistance() const { std::cout << "\n=== По расстоянию ===\n"; pr(headDistance, &Planet::nextDistance); }
//     void printByMass()     const { std::cout << "\n=== По массе ===\n";       pr(headMass,     &Planet::nextMass); }
//     void printByDiameter() const { std::cout << "\n=== По диаметру ===\n";    pr(headDiameter, &Planet::nextDiameter); }

// private:
//     Planet *headDistance = nullptr, *headMass = nullptr, *headDiameter = nullptr;

//     template <typename K>
//     static Planet* ins(Planet* h, Planet* p, K key, Planet* Planet::*nf) {
//         if (!h || key(p) < key(h)) { p->*nf = h; return p; }
//         Planet* c = h;
//         while (c->*nf && key(c->*nf) < key(p)) c = c->*nf;
//         p->*nf = c->*nf;
//         c->*nf = p;
//         return h;
//     }
//     static void pr(Planet* h, Planet* Planet::*nf) {
//         std::cout << std::string(64, '-') << "\n";
//         std::cout << "Имя\t\tРасст.\t\tМасса\t\tДиаметр\n";
//         std::cout << std::string(64, '-') << "\n";
//         for (Planet* p = h; p; p = p->*nf)
//             std::cout << p->name << "\t\t" << p->distance << "\t\t"
//                       << p->mass << "\t\t" << p->diameter << "\n";
//     }
// };

// void planetsDemo() {
//     MultiLinkedList list;
//     list.addPlanet(new Planet("Меркурий",  57.9,   0.33,   4879));
//     list.addPlanet(new Planet("Венера",   108.2,   4.87,  12104));
//     list.addPlanet(new Planet("Земля",    149.6,   5.97,  12742));
//     list.addPlanet(new Planet("Марс",     227.9,   0.642,  6779));
//     list.addPlanet(new Planet("Юпитер",   778.6, 1898.0, 139820));
//     list.addPlanet(new Planet("Сатурн",  1433.5,  568.0, 116460));
//     list.addPlanet(new Planet("Уран",    2872.5,   86.8,  50724));
//     list.addPlanet(new Planet("Нептун",  4495.1,  102.0,  49244));

//     int c = -1;
//     while (true) {
//         std::cout << "\n1 — расстояние, 2 — масса, 3 — диаметр, 0 — выход\n> ";
//         if (!(std::cin >> c)) {
//             std::cin.clear();
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//             continue;
//         }
//         if (c == 0) return;
//         if (c == 1) list.printByDistance();
//         else if (c == 2) list.printByMass();
//         else if (c == 3) list.printByDiameter();
//         else std::cout << "Нет такого пункта.\n";
//     }
// }

// // ============================================================
// //  ЗАДАНИЕ 11. Черепаха и кролик
// // ============================================================
// struct Node {
//     int value = 0;
//     Node* next = nullptr;
//     explicit Node(int v = 0) : value(v) {}
// };

// bool hasCycle(Node* head) {
//     Node *s = head, *f = head;
//     while (f && f->next) {
//         s = s->next; f = f->next->next;
//         if (s == f) return true;
//     }
//     return false;
// }

// Node* findCycleStart(Node* head) {
//     Node *s = head, *f = head;
//     while (f && f->next) {
//         s = s->next; f = f->next->next;
//         if (s == f) {
//             Node* r = head;
//             while (r != s) { r = r->next; s = s->next; }
//             return s;
//         }
//     }
//     return nullptr;
// }

// bool breakCycle(Node* head) {
//     Node* start = findCycleStart(head);
//     if (!start) return false;
//     Node *rabbit = start, *turtle = start;
//     while (turtle->next != rabbit) turtle = turtle->next;
//     turtle->next = nullptr;
//     return true;
// }