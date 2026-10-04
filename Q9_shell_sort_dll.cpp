#include <iostream>
#include <vector>
#include <utility>
using namespace std;

struct DNode {
    int id;
    int severity;
    DNode* prev;
    DNode* next;
    DNode(int i, int s) : id(i), severity(s), prev(nullptr), next(nullptr) {}
};

DNode* buildList(const vector<pair<int, int>>& records) {
    DNode* head = nullptr;
    DNode* tail = nullptr;
    for (const auto& r : records) {
        DNode* n = new DNode(r.first, r.second);
        if (!head) head = tail = n;
        else { tail->next = n; n->prev = tail; tail = n; }
    }
    return head;
}

void printForward(DNode* head) {
    cout << "NULL";
    for (DNode* cur = head; cur; cur = cur->next) {
        cout << "[ID:" << cur->id << ", Sev:" << cur->severity << "]";
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

int listLength(DNode* head) {
    int n = 0;
    for (; head; head = head->next) n++;
    return n;
}

DNode* stepBack(DNode* p, int steps) {
    for (int k = 0; k < steps; k++) {
        if (!p) return nullptr;
        p = p->prev;
    }
    return p;
}

void unlinkNode(DNode*& head, DNode* x) {
    if (x->prev) x->prev->next = x->next;
    else head = x->next;
    if (x->next) x->next->prev = x->prev;
    x->prev = nullptr;
    x->next = nullptr;
}

void insertBefore(DNode*& head, DNode* pos, DNode* x) {
    x->next = pos;
    x->prev = pos->prev;
    if (pos->prev) pos->prev->next = x;
    else head = x;
    pos->prev = x;
}

DNode* shellSort(DNode* head) {
    int n = listLength(head);

    for (int gap = n / 2; gap > 0; gap /= 2) {
        DNode* cur = head;
        int index = 0;

        while (cur) {
            DNode* nxt = cur->next;

            if (index >= gap) {
                DNode* pos = cur;
                DNode* back = stepBack(pos, gap);
                while (back && back->severity > cur->severity) {
                    pos = back;
                    back = stepBack(pos, gap);
                }
                if (pos != cur) {
                    unlinkNode(head, cur);
                    insertBefore(head, pos, cur);
                }
            }

            cur = nxt;
            index++;
        }

        cout << "After gap " << gap << ": ";
        printForward(head);
    }
    return head;
}

int main() {
    DNode* head = buildList({{101, 50}, {102, 20}, {103, 80}, {104, 10}, {105, 60}, {106, 30}});

    cout << "Input:  ";
    printForward(head);
    cout << endl;

    head = shellSort(head);

    cout << "\nOutput: ";
    printForward(head);

    freeList(head);
    return 0;
}
