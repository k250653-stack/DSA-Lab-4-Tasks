#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int d) : data(d), next(nullptr) {}
};

Node* detectLoopStart(Node* head) {
    Node* slow = head;
    Node* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            Node* ptr1 = head;
            Node* ptr2 = slow;
            while (ptr1 != ptr2) {
                ptr1 = ptr1->next;
                ptr2 = ptr2->next;
            }
            return ptr1;
        }
    }
    return nullptr;
}

void removeLoop(Node* loopStart) {
    Node* cur = loopStart;
    while (cur->next != loopStart) {
        cur = cur->next;
    }
    cur->next = nullptr;
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

int main() {
    Node* nodes[6];
    for (int i = 0; i < 6; i++) {
        nodes[i] = new Node(i + 1);
    }
    for (int i = 0; i < 5; i++) {
        nodes[i]->next = nodes[i + 1];
    }
    nodes[5]->next = nodes[2];

    cout << "Input: [1] [2] [3] [4] [5] [6]  (back to [3])" << endl;

    Node* start = detectLoopStart(nodes[0]);
    if (!start) {
        cout << "No loop detected." << endl;
        printList(nodes[0]);
        freeList(nodes[0]);
        return 0;
    }

    cout << "Loop starts at: [" << start->data << "]" << endl;
    removeLoop(start);

    cout << "Output: ";
    printList(nodes[0]);

    freeList(nodes[0]);
    return 0;
}
