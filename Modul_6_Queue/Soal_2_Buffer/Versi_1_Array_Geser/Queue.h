#ifndef VERSION
#define VERSION 1
#endif
#ifndef BUFFER_H
#define BUFFER_H
const int KAPASITAS = 6;
struct Rekaman { int nomor; int nilai; };
struct Queue {
    Rekaman data[KAPASITAS];
    int head;
    int tail;   // dipakai versi 1 dan 2
    int count;  // dipakai versi 3
    int geser;
};
void createQueue(Queue& Q);
int jumlah(const Queue& Q);
bool enqueue(Queue& Q, Rekaman r);
bool dequeue(Queue& Q, Rekaman& hasil);
void printInfo(const Queue& Q);
void ringkas(const Queue& Q);
void kosongkan(Queue& Q);
#endif
