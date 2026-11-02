#ifndef VERSION
#define VERSION 3
#endif
#include "Queue.h"
#include <iostream>
#include <iomanip>
using namespace std;
void createQueue(Queue& Q) {
    Q.head=0; Q.tail=-1; Q.count=0; Q.geser=0;
#if VERSION == 3
    Q.head=0; Q.count=0;
#endif
}
int jumlah(const Queue& Q) {
#if VERSION == 3
    return Q.count;
#else
    return Q.tail == -1 ? 0 : Q.tail-Q.head+1;
#endif
}
bool enqueue(Queue& Q, Rekaman r) {
    if (jumlah(Q)>=KAPASITAS) return false;
#if VERSION == 1
    Q.data[++Q.tail]=r;
#elif VERSION == 2
    if (Q.tail==KAPASITAS-1) {
        int n=jumlah(Q);
        for(int i=0;i<n;i++) { Q.data[i]=Q.data[Q.head+i]; ++Q.geser; }
        Q.head=0; Q.tail=n-1;
    }
    Q.data[++Q.tail]=r;
#else
    int pos=(Q.head+Q.count)%KAPASITAS;
    Q.data[pos]=r; ++Q.count;
#endif
    return true;
}
bool dequeue(Queue& Q, Rekaman& hasil) {
    if (jumlah(Q)==0) return false;
#if VERSION == 1
    hasil=Q.data[Q.head];
    int n=jumlah(Q);
    for(int i=1;i<n;i++) { Q.data[i-1]=Q.data[i]; ++Q.geser; }
    --Q.tail; Q.head=0;
    if(Q.tail<0) { Q.head=0; Q.tail=-1; }
#elif VERSION == 2
    hasil=Q.data[Q.head++];
    if(Q.head>Q.tail) { Q.head=0; Q.tail=-1; }
#else
    hasil=Q.data[Q.head];
    Q.head=(Q.head+1)%KAPASITAS; --Q.count;
    if(Q.count==0) Q.head=0;
#endif
    return true;
}
void printInfo(const Queue& Q) {
    cout << "FIFO: ";
    for(int i=0;i<jumlah(Q);i++) {
#if VERSION == 3
        int idx=(Q.head+i)%KAPASITAS;
#else
        int idx=Q.head+i;
#endif
        cout << Q.data[idx].nomor << ":" << Q.data[idx].nilai << (i+1<jumlah(Q)?", ":"");
    }
    if(jumlah(Q)==0) cout << "Kosong";
    cout << "\nIndeks fisik: ";
    for(int i=0;i<KAPASITAS;i++) {
        bool aktif=false;
        for(int j=0;j<jumlah(Q);j++) {
#if VERSION == 3
            int idx=(Q.head+j)%KAPASITAS;
#else
            int idx=Q.head+j;
#endif
            if(idx==i) aktif=true;
        }
        if(aktif) cout << "[" << i << "]=" << Q.data[i].nomor << ":" << Q.data[i].nilai;
        else cout << "[" << i << "]=-";
        if(i<KAPASITAS-1) cout << " ";
    }
#if VERSION == 3
    cout << "\nhead=" << Q.head << ", count=" << Q.count;
#else
    cout << "\nhead=" << (jumlah(Q)?Q.head:-1) << ", tail=" << Q.tail;
#endif
    cout << ", total pergeseran=" << Q.geser << "\n";
}
void ringkas(const Queue& Q) {
    int n=jumlah(Q); long long total=0; int mn=0,mx=0;
    for(int i=0;i<n;i++) {
#if VERSION == 3
        int idx=(Q.head+i)%KAPASITAS;
#else
        int idx=Q.head+i;
#endif
        int v=Q.data[idx].nilai;
        total+=v; if(i==0||v<mn) mn=v; if(i==0||v>mx) mx=v;
    }
    cout << "Jumlah: " << n << "\nTotal: " << total << "\n";
    if(n==0) cout << "Minimum: TIDAK ADA\nMaksimum: TIDAK ADA\nRata-rata: TIDAK ADA\n";
    else cout << "Minimum: " << mn << "\nMaksimum: " << mx << "\nRata-rata: " << fixed << setprecision(2) << (double)total/n << "\n";
}
void kosongkan(Queue& Q) {
#if VERSION == 3
    Q.head=0; Q.count=0;
#else
    Q.head=0; Q.tail=-1;
#endif
    // Nomor urut dan penghitung pergeseran sengaja tidak direset.
}
