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

Node* groupByPosition(Node* head) {
    if (!head || !head->next) return head;

    Node* odd = head;
    Node* even = head->next;
    Node* evenHead = even;

    while (even && even->next) {
        odd->next = even->next;
        odd = odd->next;
        even->next = odd->next;
        even = even->next;
    }
    odd->next = evenHead;
    return head;
}

Node* groupByValueParity(Node* head) {
    Node oddDummy(0);
    Node evenDummy(0);
    Node* oddTail = &oddDummy;
    Node* evenTail = &evenDummy;

    while (head) {
        Node* nxt = head->next;
        head->next = nullptr;
        if (head->data % 2 != 0) {
            oddTail->next = head;
            oddTail = head;
        } else {
            evenTail->next = head;
            evenTail = head;
        }
        head = nxt;
    }
    oddTail->next = evenDummy.next;
    return oddDummy.next;
}

int main() {
    vector<int> values = {2, 1, 3, 5, 6, 4, 7};

    Node* byPosition = buildList(values);
    cout << "Input: ";
    printList(byPosition);

    byPosition = groupByPosition(byPosition);
    cout << "Odd positions first, then even positions : ";
    printList(byPosition);
    freeList(byPosition);

    Node* byValue = buildList(values);
    byValue = groupByValueParity(byValue);
    cout << "Odd values first, then even values       : ";
    printList(byValue);
    freeList(byValue);

    return 0;
}
