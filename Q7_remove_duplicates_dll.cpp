#include <iostream>
#include <vector>
using namespace std;

struct DNode {
    int data;
    DNode* prev;
    DNode* next;
    DNode(int d) : data(d), prev(nullptr), next(nullptr) {}
};

DNode* buildList(const vector<int>& values) {
    DNode* head = nullptr;
    DNode* tail = nullptr;
    for (int v : values) {
        DNode* n = new DNode(v);
        if (!head) head = tail = n;
        else { tail->next = n; n->prev = tail; tail = n; }
    }
    return head;
}

void printForward(DNode* head) {
    cout << " NULL";
    for (DNode* cur = head; cur; cur = cur->next) {
        cout << "[" << cur->data << "]";
        if (cur->next) cout << " ";
    }
    cout << " NULL" << endl;
}

void printBackward(DNode* head) {
    if (!head) {
        cout << "(empty)" << endl;
        return;
    }
    DNode* tail = head;
    while (tail->next) tail = tail->next;
    cout << " NULL";
    for (DNode* cur = tail; cur; cur = cur->prev) {
        cout << "[" << cur->data << "]";
        if (cur->prev) cout << " ";
    }
    cout << " NULL" << endl;
}

void freeList(DNode* head) {
    while (head) {
        DNode* nxt = head->next;
        delete head;
        head = nxt;
    }
}

DNode* removeDuplicates(DNode* head) {
    DNode* curr = head;
    while (curr && curr->next) {
        if (curr->data == curr->next->data) {
            DNode* dup = curr->next;
            curr->next = dup->next;
            if (dup->next) dup->next->prev = curr;
            delete dup;
        } else {
            curr = curr->next;
        }
    }
    return head;
}

int main() {
    DNode* head = buildList({1, 1, 2, 3, 3, 3, 4});

    cout << "Input:  ";
    printForward(head);

    head = removeDuplicates(head);

    cout << "Output: ";
    printForward(head);
    cout << "Backward check: ";
    printBackward(head);

    freeList(head);
    return 0;
}
