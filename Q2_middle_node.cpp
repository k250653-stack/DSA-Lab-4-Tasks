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

Node* findMiddle(Node* head) {
    Node* slow = head;
    Node* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

int main() {
    Node* odd = buildList({1, 2, 3, 4, 5});
    cout << "Input (Odd):  ";
    printList(odd);
    Node* mid = findMiddle(odd);
    cout << "Middle = [" << mid->data << "]" << endl;
    freeList(odd);

    Node* even = buildList({1, 2, 3, 4, 5, 6});
    cout << "\nInput (Even): ";
    printList(even);
    mid = findMiddle(even);
    cout << "Middle Box = [" << mid->data << "] (second middle)" << endl;
    freeList(even);

    return 0;
}
