#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int d, Node* n = nullptr) : data(d), next(n) {}
};

void printList(Node* head) {
    for (Node* cur = head; cur; cur = cur->next) {
        cout << "[" << cur->data << "]";
    }
    cout << "NULL" << endl;
}

void freeUntil(Node* head, Node* stop) {
    while (head && head != stop) {
        Node* nxt = head->next;
        delete head;
        head = nxt;
    }
}

Node* getIntersection(Node* headA, Node* headB) {
    if (!headA || !headB) return nullptr;

    Node* pa = headA;
    Node* pb = headB;
    while (pa != pb) {
        pa = pa ? pa->next : headB;
        pb = pb ? pb->next : headA;
    }
    return pa;
}

int main() {
    Node* common = new Node(8, new Node(4, new Node(5)));
    Node* headA = new Node(4, new Node(1, common));
    Node* headB = new Node(5, new Node(6, new Node(1, common)));

    cout << "Chain A: ";
    printList(headA);
    cout << "Chain B: ";
    printList(headB);

    Node* hit = getIntersection(headA, headB);
    if (hit) cout << "Intersection point = [" << hit->data << "]" << endl;
    else cout << "Intersection point = NULL" << endl;

    freeUntil(headA, nullptr);
    freeUntil(headB, common);

    Node* x = new Node(1, new Node(2));
    Node* y = new Node(3, new Node(4));
    cout << "\nNon-intersecting test:" << endl;
    Node* none = getIntersection(x, y);
    if (none) cout << "Intersection point = [" << none->data << "]" << endl;
    else cout << "Intersection point = NULL" << endl;
    freeUntil(x, nullptr);
    freeUntil(y, nullptr);

    return 0;
}
