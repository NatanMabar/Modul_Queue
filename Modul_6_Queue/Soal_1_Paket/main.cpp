#include "Queue.h"
#include <iostream>
#include <sstream>
#include <cctype>
using namespace std;

Queue A, B;
long long totalTerkirim = 0;
long long jumlahTerkirim = 0;

bool kodeValid(const string& kode) {
    if (kode.empty() || kode.size() > 10) return false;
    for (unsigned char c : kode)
        if (isspace(c)) return false;
    return true;
}

bool kodeAktif(const string& kode) {
    return findElm(A, kode) != nullptr || findElm(B, kode) != nullptr;
}

void rekap() {
    long long beratA = 0, beratB = 0;
    for (Paket* p=A.head; p; p=p->next) beratA += p->berat;
    for (Paket* p=B.head; p; p=p->next) beratB += p->berat;
    cout << "A: " << nbList(A) << " paket, " << beratA << " gram\n";
    cout << "B: " << nbList(B) << " paket, " << beratB << " gram\n";
    cout << "Terkirim: " << jumlahTerkirim << " paket, " << totalTerkirim << " gram\n";
}

void lihat() {
    cout << "A: "; printInfo(A); cout << "\n";
    cout << "B: "; printInfo(B); cout << "\n";
}

int main() {
    createQueue(A); createQueue(B);
    cout << "SISTEM SORTIR DAN PENGIRIMAN PAKET\n";
    cout << "Perintah: MASUK kode berat | PINDAH n | KIRIM n | CARI kode | LIHAT | REKAP | BERSIHKAN | SELESAI\n";
    string baris, perintah;
    while (true) {
        cout << "> ";
        if (!getline(cin, baris)) break;
        stringstream ss(baris);
        ss >> perintah;
        if (perintah == "SELESAI") {
            delAll(A); delAll(B);
            cout << "Program selesai.\n";
            break;
        } else if (perintah == "MASUK") {
            string kode, sisa; int berat;
            if (!(ss >> kode >> berat) || (ss >> sisa)) {
                cout << "Ditolak: format MASUK kode berat.\n"; continue;
            }
            if (!kodeValid(kode)) { cout << "Ditolak: kode harus 1-10 karakter tanpa spasi.\n"; continue; }
            if (berat < 1 || berat > 5000) { cout << "Ditolak: berat harus 1-5000 gram.\n"; continue; }
            if (kodeAktif(kode)) { cout << "Ditolak: kode sedang aktif.\n"; continue; }
            Paket* P = alokasi(kode, berat);
            if (!P) { cout << "Ditolak: alokasi memori gagal.\n"; continue; }
            enqueue(A, P); cout << "Berhasil masuk ke A.\n";
        } else if (perintah == "PINDAH" || perintah == "KIRIM") {
            int n; string sisa;
            if (!(ss >> n) || (ss >> sisa) || n <= 0) {
                cout << "Ditolak: n harus bilangan positif.\n"; continue;
            }
            Queue& sumber = (perintah == "PINDAH") ? A : B;
            if (n > nbList(sumber)) {
                cout << "Ditolak: antrean sumber hanya berisi " << nbList(sumber) << " paket.\n";
                continue;
            }
            if (perintah == "PINDAH") {
                for (int i=0; i<n; ++i) {
                    Paket* P = dequeue(A);
                    enqueue(B, P); // alamat node tetap, tidak ada alokasi/dealokasi
                }
                cout << n << " paket dipindahkan ke B.\n";
            } else {
                for (int i=0; i<n; ++i) {
                    Paket* P = dequeue(B);
                    cout << "Terkirim: " << P->kode << " (" << P->berat << " gram)\n";
                    ++jumlahTerkirim; totalTerkirim += P->berat;
                    dealokasi(P);
                }
            }
        } else if (perintah == "CARI") {
            string kode, sisa;
            if (!(ss >> kode) || (ss >> sisa)) { cout << "Format: CARI kode.\n"; continue; }
            int pos = fFindElm(A, kode);
            if (pos != -1) cout << kode << " berada di A, posisi " << pos << ", berat " << findElm(A,kode)->berat << " gram.\n";
            else {
                pos = fFindElm(B, kode);
                if (pos != -1) cout << kode << " berada di B, posisi " << pos << ", berat " << findElm(B,kode)->berat << " gram.\n";
                else cout << "TIDAK DITEMUKAN\n";
            }
        } else if (perintah == "LIHAT") lihat();
        else if (perintah == "REKAP") rekap();
        else if (perintah == "BERSIHKAN") {
            delAll(A); delAll(B);
            cout << "Kedua antrean dibersihkan; statistik terkirim tetap.\n";
        } else if (!perintah.empty()) cout << "Perintah tidak dikenal.\n";
    }
    return 0;
}
