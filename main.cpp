#include <iostream>
#include <vector>

using namespace std;

class PriorityQueue {
private:
    vector<int> heap;

    void heapifyUp(int index) {
        while (index > 0 && heap[(index - 1) / 2] < heap[index]) {
            swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    void heapifyDown(int index) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < heap.size() && heap[left] > heap[largest]) {
            largest = left;
        }

        if (right < heap.size() && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest != index) {
            swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

    int findMinIndex() {
        int minIndex = 0;
        for (int i = 1; i < heap.size(); ++i) {
            if (heap[i] < heap[minIndex]) {
                minIndex = i;
            }
        }
        return minIndex;
    }

public:
    void insert(int element) {
        heap.push_back(element);
        heapifyUp(heap.size() - 1);
    }

    int getMin() {
        if (heap.empty()) {
            cout << "Kolejka jest pusta" << endl;
            return -1;
        }

        return heap[findMinIndex()];
    }

    void removeMin() {
        if (heap.empty()) {
            cout << "Kolejka jest pusta" << endl;
            return;
        }

        int minIndex = findMinIndex();
        heap[minIndex] = heap.back();
        heap.pop_back();
        heapifyDown(minIndex);
    }

    void increaseKey(int oldKey, int newKey) {
        int index = -1;

        if (heap.empty()) {
            cout << "Kolejka jest pusta" << endl;
            return;
        } else if (newKey <= oldKey) {
            cout << "Nowa wartosc musi byc wieksza od poprzedniej" << endl;
            return;
        }

        for (int i = 0; i < heap.size(); ++i) {
            if (heap[i] == oldKey) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            heap[index] = newKey;
            heapifyUp(index);
        } else {
            cout << "Element nie zostal znaleziony" << endl;
        }
    }

    void display() {
        for (int i : heap) {
            cout << i << " ";
        }
        cout << endl;
    }
};

int main() {
    PriorityQueue pq;
    int choice, value, oldKey, newKey;

    while(true) {
        cout << "Menu:" << endl;
        cout << "1. Dodaj" << endl;
        cout << "2. Minimum" << endl;
        cout << "3. Usun element (minimum)" << endl;
        cout << "4. Zwieksz klucz" << endl;
        cout << "5. Wyswietl" << endl;
        cout << "6. Wyjdz" << endl;
        cout << "Opcja: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Wprowadz wartosc: ";
                cin >> value;
                pq.insert(value);
                break;
            case 2:
                value = pq.getMin();
                if (value != -1) {
                    cout << "Wartosc minimalna: " << value << endl;
                }
                break;
            case 3:
                pq.removeMin();
                break;
            case 4:
                cout << "Wprowadz stary klucz: ";
                cin >> oldKey;
                cout << "Wprowadz nowy klucz: ";
                cin >> newKey;
                pq.increaseKey(oldKey, newKey);
                break;
            case 5:
                pq.display();
                break;
            case 6:
                cout << "Wychodzenie..." << endl;
                return 0;
            default:
                cout << "Niepoprawna opcja..." << endl;
        }
    }

    return 0;
}
