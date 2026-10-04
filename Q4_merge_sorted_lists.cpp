#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int d) : data(d), next(nullptr) {}
};

Node* buildList(const vector<int>& values) {
    Node* head = nullptr;
    Node* tail = nullptr;
    for (int v : values) {
        Node* n = new Node(v);
        if (!head) head = tail = n;
        else { tail->next = n; tail = n; }
    }
    return head;
}

void printList(Node* head) {
    for (Node* cur = head; cur; cur = cur->next) {
        cout << "[" << cur->data << "]";
    }
    cout << "NULL" << endl;
}

void freeList(Node* head) {
    while (head) {
        Node* nxt = head->next;
        delete head;
        head = nxt;
    }
}

Node* mergeSorted(Node* a, Node* b) {
    Node dummy(0);
    Node* tail = &dummy;

    while (a && b) {
        if (a->data <= b->data) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }
    tail->next = a ? a : b;
    return dummy.next;
}

int main() {
    Node* headA = buildList({1, 3, 5, 7});
    Node* headB = buildList({2, 4, 6, 8});

    cout << "Chain A: HEAD1";
    printList(headA);
    cout << "Chain B: HEAD2";
    printList(headB);

    Node* merged = mergeSorted(headA, headB);

    cout << "\nMerged:  ";
    printList(merged);

    freeList(merged);
    return 0;
}
