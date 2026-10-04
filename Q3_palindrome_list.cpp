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

Node* reverseList(Node* head) {
    Node* prev = nullptr;
    while (head) {
        Node* nxt = head->next;
        head->next = prev;
        prev = head;
        head = nxt;
    }
    return prev;
}

bool isPalindrome(Node* head) {
    if (!head || !head->next) return true;

    Node* slow = head;
    Node* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* secondHalf = reverseList(slow);
    Node* left = head;
    Node* right = secondHalf;
    bool result = true;

    while (right) {
        if (left->data != right->data) {
            result = false;
            break;
        }
        left = left->next;
        right = right->next;
    }

    reverseList(secondHalf);
    return result;
}

void test(const vector<int>& values) {
    Node* head = buildList(values);
    cout << "Input : ";
    printList(head);
    cout << "Output: " << (isPalindrome(head) ? "TRUE" : "FALSE") << endl;
    cout << "List after check (restored): ";
    printList(head);
    cout << endl;
    freeList(head);
}

int main() {
    test({1, 2, 3, 2, 1});
    test({1, 2, 2, 1});
    test({1, 2, 3, 4, 1});
    test({7});
    return 0;
}
