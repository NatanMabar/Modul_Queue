#include "Queue.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
using namespace std;

int nomorBerikutnya = 1;

int main() {
    Queue Q; createQueue(Q);
    cout << "BUFFER PENCATATAN HASIL UKUR - 2 " << 2 << "\n";
    cout << "Perintah: TULIS k nilai... | AMBIL k | LIHAT | RINGKAS | KOSONGKAN | SELESAI\n";
    string line, cmd;
    while (true) {
        cout << "> ";
        if (!getline(cin,line)) break;
        stringstream ss(line); ss >> cmd;
        if (cmd == "SELESAI") { cout << "Program selesai.\n"; break; }
        else if (cmd == "TULIS") {
            int k; if (!(ss >> k) || k < 1 || k > 6) { cout << "Ditolak: k harus 1-6.\n"; continue; }
            int vals[6]; bool valid = true;
            for (int i=0;i<k;i++) if (!(ss >> vals[i]) || vals[i] < -1000 || vals[i] > 1000) valid=false;
            string extra; if (ss >> extra) valid=false;
            if (!valid) { cout << "Ditolak: format atau nilai di luar -1000 sampai 1000.\n"; continue; }
            if (KAPASITAS-jumlah(Q) < k) { cout << "Ditolak: ruang kosong kurang dari " << k << ".\n"; continue; }
            for (int i=0;i<k;i++) {
                Rekaman r{nomorBerikutnya++, vals[i]};
                enqueue(Q,r);
            }
            cout << "Berhasil menambahkan " << k << " rekaman.\n";
        } else if (cmd == "AMBIL") {
            int k; string extra;
            if (!(ss >> k) || (ss >> extra) || k <= 0) { cout << "Ditolak: k harus positif.\n"; continue; }
            if (k > jumlah(Q)) { cout << "Ditolak: data hanya " << jumlah(Q) << " rekaman.\n"; continue; }
            for (int i=0;i<k;i++) {
                Rekaman r; dequeue(Q,r);
                cout << "Keluar " << r.nomor << ":" << r.nilai << "\n";
            }
        } else if (cmd == "LIHAT") printInfo(Q);
        else if (cmd == "RINGKAS") ringkas(Q);
        else if (cmd == "KOSONGKAN") { kosongkan(Q); cout << "Buffer dikosongkan.\n"; }
        else if (!cmd.empty()) cout << "Perintah tidak dikenal.\n";
    }
}
