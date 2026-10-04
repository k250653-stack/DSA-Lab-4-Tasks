#include <iostream>
#include <string>
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

string val(Node* n) {
    return n ? to_string(n->data) : "NULL";
}

void freeList(Node* head) {
    while (head) {
        Node* nxt = head->next;
        delete head;
        head = nxt;
    }
}

Node* reverseList(Node* head) {
    Node* prev = nullptr;
    Node* curr = head;
    int step = 1;

    while (curr) {
        Node* nxt = curr->next;
        cout << "Step " << step << ": prev=" << val(prev) << ", curr=" << val(curr) << ", next=" << val(nxt) << endl;
        curr->next = prev;
        cout << "        [" << curr->data << "].next -> " << val(prev) << endl;
        prev = curr;
        curr = nxt;
        cout << "        Reversed so far: ";
        printList(prev);
        step++;
    }
    return prev;
}

int main() {
    Node* head = buildList({10, 20, 30, 40, 50});
    cout << "Input:  ";
    printList(head);
    cout << endl;

    head = reverseList(head);

    cout << "\nOutput: ";
    printList(head);

    freeList(head);
    return 0;
}
