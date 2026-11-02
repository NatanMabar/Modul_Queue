# Modul 6 - Struktur Data: Queue

## Cara kompilasi
Gunakan compiler C++17.

### Soal 1
Masuk ke folder `Soal_1_Paket`, lalu:
```bash
g++ -std=c++17 main.cpp Queue.cpp -o paket
./paket
```

### Soal 2
Pilih salah satu folder versi, lalu:
```bash
g++ -std=c++17 main.cpp Queue.cpp -o buffer
./buffer
```
Setiap versi menggunakan antarmuka `Queue.h` dan `main.cpp` yang sama.

## Uji utama Soal 1
```text
MASUK P17 450
MASUK P28 700
MASUK P36 550
PINDAH 2
MASUK P42 600
PINDAH 3
PINDAH 1
KIRIM 2
CARI P36
KIRIM 2
PINDAH 1
KIRIM 2
REKAP
BERSIHKAN
SELESAI
```
Hasil akhir statistik terkirim: 4 paket, 2300 gram. Penolakan PINDAH 3 terjadi karena A hanya berisi 2 paket; penolakan KIRIM 2 terjadi karena B hanya berisi 1 paket.

## Uji utama Soal 2 (jalankan pada setiap versi)
```text
TULIS 6 12 -4 7 0 15 6
AMBIL 2
TULIS 3 9 11 -2
TULIS 2 9 -2
RINGKAS
LIHAT
SELESAI
```
Hasil RINGKAS: jumlah 6, total 35, minimum -2, maksimum 15, rata-rata 5.83.
Posisi akhir dan total pergeseran yang diharapkan:
- Versi 1: head=0, tail=5, 9 pergeseran.
- Versi 2: head=0, tail=5, 4 pergeseran.
- Versi 3: head=2, count=6, 0 pergeseran.

## Analisis kompleksitas
### Soal 1 (n = jumlah node pada antrean)
- `enqueue`: O(1), karena menggunakan pointer tail.
- `dequeue`: O(1), hanya melepas head.
- `PINDAH k`: O(k), setiap node dipindahkan satu kali; alamat node tetap.
- `KIRIM k`: O(k), setiap node dilepas dan dibebaskan.
- `CARI`: O(n), pencarian linear pada antrean A dan B.
- `LIHAT`, `REKAP`, `nbList`: O(n).

Pengelolaan memori: setiap `MASUK` melakukan satu `new`; `KIRIM`, `BERSIHKAN`, dan `SELESAI` membebaskan node dengan `delete`. `PINDAH` tidak melakukan alokasi atau dealokasi. `dequeue` memutus `next` node yang dilepas sehingga node tidak menjadi anggota dua queue. Setiap node hanya dihapus satu kali.

### Soal 2
- Array geser: enqueue O(1), dequeue O(n) karena semua elemen aktif setelah head digeser; batch k dequeue dapat O(k*n) dan total perpindahan untuk skenario uji adalah 9.
- Array pemadatan: dequeue O(1); enqueue umumnya O(1), tetapi O(n) saat pemadatan; batch dapat O(k+n) bila pemadatan terjadi; skenario uji memindahkan 4 rekaman.
- Circular queue: enqueue O(1), dequeue O(1), batch k operasi O(k); tidak ada perpindahan elemen, sehingga total pergeseran 0.

FIFO dipertahankan dengan selalu menambah di belakang dan mengambil dari depan. Kapasitas dibatasi 6. Validasi batch dilakukan sebelum queue berubah; nomor hanya bertambah setelah setiap rekaman berhasil ditambahkan. KOSONGKAN tidak mereset nomor urut atau penghitung pergeseran.
