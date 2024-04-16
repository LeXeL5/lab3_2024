#include <iostream>
using namespace std;

void menu() {
    cout << "(0) shutdown program" << endl;
    cout << "(1) add(int value)" << endl;
    cout << "(2) insert(int index, int value)" << endl;
    cout << "(3) removeAt(int index)" << endl;
    cout << "(4) elementAt(int index)" << endl;
    cout << "(5) count()" << endl;
    cout << "(6) insertBeforeNegative()" << endl;
    cout << "(7) removeNegative()" << endl;
    cout << "(8) count(int value)" << endl;
    cout << "(9) clear()" << endl;
}
struct Node {
    int value = 0;
    Node* next = nullptr;
};
struct List {
    Node* head = nullptr;
    Node* tail = nullptr;
    Node* prev = nullptr;
    Node* current = nullptr;
    int size = 0;
    int currentIndex = 0;
    bool isEmpty() {
        return !size;
    }
    void toFirst() {
        if (isEmpty()) return;
        current = head;
        prev = tail;
        currentIndex = 0;
    }
    void toNext() {
        if (isEmpty()) return;
        prev = current;
        current = current->next;
        currentIndex++;
        currentIndex = currentIndex % size;
    }
    void removeCurrent() {
        if (isEmpty()) return;
        if (current == head) head = current->next;
        if (current == tail) tail = prev;
        prev->next = current->next;
        delete current;
        size--;
        if (isEmpty()) return;
        current = prev->next;
        currentIndex = currentIndex % size;
    }
    void insertBeforeCurrent(int value) {
        if (isEmpty()) return;
        Node* newNode = new Node;
        size++;
        currentIndex++;
        newNode->value = value;
        newNode->next = current;
        prev->next = newNode;
        prev = newNode;
        if (current == head) { head = newNode; }
    }

    void add(int value) {
        Node* newNode = new Node;
        newNode->value = value;
        if (isEmpty()) {
            head = newNode;
            prev = newNode;
            current = newNode;
            size = 1;
            currentIndex = 0;
        }
        else {
            prev = tail;
            tail->next = newNode;
            size++;
        }
        newNode->next = head;
        tail = newNode;
        elementAt(size-1);
    }
    void insert(int index, int value) {
        index = index % (size + 1);
        if ((isEmpty()) or (index == size)) {
            add(value);
        }
        else {
            elementAt(index);
            insertBeforeCurrent(value);
        }
    }
    void removeAt(int index) {
        elementAt(index);
        removeCurrent();
    }
    int elementAt(int index) {
        if (isEmpty()) return 0;
        index = index % size;
        while (index != currentIndex) {
            toNext();
        }
        return current->value;
    }
    int count() {
        return size;
    }
    void insertBeforeNegative() {
        if (isEmpty()) return;
        toFirst();
        for (int i = size; i > 0; i--) {
            if (current->value < 0) {
                insertBeforeCurrent(1);
            }
            toNext();
        }
    }
    void removeNegative() {
        toFirst();
        for (int i = size; i > 0; i--) {
            if (isEmpty()) return;
            if (current->value < 0) {
                removeCurrent();
            }
            else {
                toNext();
            }
        }
    }
    int count(int countWhat) {
        if (isEmpty()) return 0;
        toFirst();
        int count = 0;
        for (int i = size; i > 0; i--) {
            if (current->value == countWhat) count++;
            toNext();
        }
        return count;
    }
    void clear() {
        if (isEmpty()) return;
        toFirst();
        for (int i = size; i > 0; i--) {
            removeCurrent();
        }
    }
};

void main() {
    List list;
    int value = 0;
    int index = 0;
    int countWhat = 0;
    int switch_on = 0;
    while (true) {
        system("cls");
        menu();
        cout << endl;
        cout << "Choice: ";
        cin >> switch_on;
        switch (switch_on) {
        case (0): {
            return;
            break;
        }
        case (1): {
            cout << "Value: ";
            cin >> value;
            cout << endl;
            list.add(value);
            break;
        }
        case (2): {
            cout << "Index and value: ";
            cin >> index >> value;
            cout << endl;
            list.insert(index, value);
            break;
        }
        case (3): {
            cout << "Index: ";
            cin >> index;
            cout << endl;
            list.removeAt(index);
            break;
        }
        case (4): {
            if (!list.isEmpty()) {
                cout << "Index: ";
                cin >> index;
                cout << endl;
                cout << "Value: " << list.elementAt(index) << endl;
            }
            else {
                cout << "List is empty " << endl;
            }
            break;
        }
        case (5): {
            cout << "List size: " << list.count() << endl;
            break;
        }
        case (6): {
            list.insertBeforeNegative();
            cout << "Elements are inserted" << endl;
            break;
        }
        case (7): {
            list.removeNegative();
            cout << "Negative elements are removed" << endl;
            break;
        }
        case (8): {
            cout << "CountWhat: ";
            cin >> countWhat;
            cout << endl;
            cout << "Number of occurrences: " << list.count(countWhat) << endl;
            break;
        }
        case (9): {
            list.clear();
            cout << "List is cleared" << endl;
            break;
        }
        default: {
            cout << "Unknown command, try again" << endl;
            break;
        }
        }
        system("pause");
    }
}
