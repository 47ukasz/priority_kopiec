#include <iostream>
#include <vector>

using namespace std;

class PriorityQueue {
private:
    vector<int> heap;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    void heapify_down(int i) {
        int l = left(i);
        int r = right(i);
        int largest = i;
        if (l < heap.size() && heap[l] > heap[largest]) {
            largest = l;
        }
        if (r < heap.size() && heap[r] > heap[largest]) {
            largest = r;
        }
        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapify_down(largest);
        }
    }

    void heapify_up(int i) {
        if (i && heap[parent(i)] < heap[i]) {
            swap(heap[i], heap[parent(i)]);
            heapify_up(parent(i));
        }
    }

public:
    void insert(int key) {
        heap.push_back(key);
        int index = heap.size() - 1;
        heapify_up(index);
    }

    int getMin() {
        if (heap.empty()) {
            cout << "Kopiec jest pusty!" << endl;
            return -1;
        }

        int min = heap[0];

        for (int i = 0; i < heap.size(); i++) {
            if (heap[i] < min) {
                min = heap[i];
            }
        }
        return min;
    }

    void deleteMin() {
        if (heap.empty()) {
            cout << "Kopiec jest pusty!" << endl;
            return;
        }

        int minIndex = -1;
        int min = heap[0];
        for (int i = 0; i < heap.size(); i++) {
            if (heap[i] < min) {
                min = heap[i];
                minIndex = i;
            }
        }

        if (minIndex != -1) {
            heap[minIndex] = heap.back();
            heap.pop_back();
            heapify_down(minIndex);
        }
    }

    void increaseKey(int old_val, int new_val) {

        if (heap.size() == 0) {
            cout << "Kolejka jest pusta." << endl;
            return;
        }

        int index = -1;

        for (int i = 0; i < heap.size(); i++) {
            if (heap[i] == old_val) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Podana wartosc nie znajduje sie w kolejce!" << endl;
            return;
        }

        if (heap[index] <= new_val) {
            cout << "Nowy klucz musi byc wiekszy niz stary klucz.\n";
            return;
        }

        heap[index] = new_val;
        heapify_up(index);
    }

    void display() {

        if (heap.size() == 0) {
            cout << "Kolejka jest pusta!" << endl;
            return;
        }

        for (int i = 0; i < heap.size(); i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};

void menu() {
    PriorityQueue pq;
    int choice, value_1, value_2;

    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Wstaw" << endl;
        cout << "2. Znajdz wartosc minimalna" << endl;
        cout << "3. Usun wartosc minimalna" << endl;
        cout << "4. Zamien klucz na wiekszy" << endl;
        cout << "5. Wyswietl kolejke" << endl;
        cout << "6. Wyjdz" << endl;
        cout << "Wybierz opcje: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Wprowadź wartosc do wstawienia: ";
                cin >> value_1;
                pq.insert(value_1);
                break;
            case 2:
                value_1 = pq.getMin();
                if (value_1 != -1) {
                    cout << "Minimalna wartosc to: " << value_1 << endl;
                }
                break;
            case 3:
                pq.deleteMin();
                cout << "Minimalna wartosc zostala usunieta" << endl;
                break;
            case 4:
                cout << "Wprowadz stary klucz: ";
                cin >> value_1;
                cout << "Wprowadz nowy klucz: ";
                cin >> value_2;
                pq.increaseKey(value_1, value_2);
                break;
            case 5:
                pq.display();
                break;
            case 6:
                return;
            default:
                cout << "Nieprawidlowa opcja..." << endl;
        }
    }
}

int main() {
    menu();
    return 0;
}
