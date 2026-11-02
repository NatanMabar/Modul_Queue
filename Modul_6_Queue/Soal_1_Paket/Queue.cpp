#include "Queue.h"
#include <iostream>
#include <new>
using namespace std;

void createQueue(Queue& Q) {
    Q.head = nullptr;
    Q.tail = nullptr;
}

bool isEmptyQueue(const Queue& Q) {
    return Q.head == nullptr;
}

Paket* alokasi(const string& kode, int berat) {
    Paket* P = new (nothrow) Paket;
    if (P == nullptr) return nullptr;
    P->kode = kode;
    P->berat = berat;
    P->next = nullptr;
    return P;
}

void dealokasi(Paket*& P) {
    delete P;
    P = nullptr;
}

void enqueue(Queue& Q, Paket* P) {
    if (P == nullptr) return;
    P->next = nullptr;
    if (isEmptyQueue(Q)) Q.head = Q.tail = P;
    else {
        Q.tail->next = P;
        Q.tail = P;
    }
}

Paket* dequeue(Queue& Q) {
    if (isEmptyQueue(Q)) return nullptr;
    Paket* P = Q.head;
    Q.head = Q.head->next;
    if (Q.head == nullptr) Q.tail = nullptr;
    P->next = nullptr;
    return P;
}

Paket* findElm(const Queue& Q, const string& kode) {
    for (Paket* p = Q.head; p != nullptr; p = p->next)
        if (p->kode == kode) return p;
    return nullptr;
}

int fFindElm(const Queue& Q, const string& kode) {
    int posisi = 1;
    for (Paket* p = Q.head; p != nullptr; p = p->next, ++posisi)
        if (p->kode == kode) return posisi;
    return -1;
}

int nbList(const Queue& Q) {
    int jumlah = 0;
    for (Paket* p = Q.head; p != nullptr; p = p->next) ++jumlah;
    return jumlah;
}

void printInfo(const Queue& Q) {
    if (isEmptyQueue(Q)) {
        cout << "Kosong";
        return;
    }
    for (Paket* p = Q.head; p != nullptr; p = p->next) {
        cout << p->kode << "(" << p->berat << " gram)";
        if (p->next) cout << " -> ";
    }
}

void delAll(Queue& Q) {
    while (!isEmptyQueue(Q)) {
        Paket* P = dequeue(Q);
        dealokasi(P);
    }
}
