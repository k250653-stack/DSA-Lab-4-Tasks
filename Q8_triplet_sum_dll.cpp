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
    cout << "NULL";
    for (DNode* cur = head; cur; cur = cur->next) {
        cout << "[" << cur->data << "]";
        if (cur->next) cout << " ";
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

int countTriplets(DNode* head, int x) {
    int count = 0;
    cout << "All triplets checked:" << endl;
    for (DNode* a = head; a; a = a->next) {
        for (DNode* b = a->next; b; b = b->next) {
            for (DNode* c = b->next; c; c = c->next) {
                int sum = a->data + b->data + c->data;
                cout << "(" << a->data << "," << b->data << "," << c->data << ") = " << sum;
                if (sum == x) {
                    cout << " " << endl;
                    count++;
                } else {
                    cout << " " << endl;
                }
            }
        }
    }
    return count;
}

int main() {
    DNode* head = buildList({1, 2, 3, 4, 5});
    int x = 6;

    cout << "Input: ";
    printForward(head);
    cout << "X = " << x << "\n" << endl;

    int matches = countTriplets(head, x);
    cout << "Matching: " << matches << endl;

    freeList(head);
    return 0;
}
