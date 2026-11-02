#ifndef QUEUE_H
#define QUEUE_H

#include <string>
using namespace std;

struct Paket {
    string kode;
    int berat;
    Paket* next;
};

struct Queue {
    Paket* head;
    Paket* tail;
};

void createQueue(Queue& Q);
bool isEmptyQueue(const Queue& Q);
Paket* alokasi(const string& kode, int berat);
void dealokasi(Paket*& P);
void enqueue(Queue& Q, Paket* P);
Paket* dequeue(Queue& Q);
Paket* findElm(const Queue& Q, const string& kode);
int fFindElm(const Queue& Q, const string& kode);
int nbList(const Queue& Q);
void printInfo(const Queue& Q);
void delAll(Queue& Q);

#endif
