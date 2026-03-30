# 🏦 Sistem Perbankan Indonesia (Ngawi Jaya Bank)

![C++](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)
![Topic](https://img.shields.io/badge/Topic-Sorting%20%26%20Searching-green.svg)
![IDE](https://img.shields.io/badge/IDE-VSCode%20%7C%20Dev--C%2B%2B-orange.svg)

Program simulasi perbankan berbasis CLI (*Command Line Interface*) yang dirancang untuk mendemonstrasikan implementasi lengkap berbagai algoritma **Sorting** (Pengurutan) dan **Searching** (Pencarian) menggunakan bahasa C++.

---

## 📋 Deskripsi Proyek
Program ini merupakan proyek edukasi untuk memahami struktur data dan algoritma. Menggunakan studi kasus data nasabah bank, program ini mengelola informasi seperti:
* **ID Nasabah**
* **Nama Nasabah**
* **Nomor Rekening**
* **Saldo (IDR)**
* **Jenis Akun** (Tabungan, Giro, Deposito)

## 🚀 Fitur & Algoritma

### 📊 10 Metode Sorting (Ascending by Saldo)
Program ini mengimplementasikan hampir semua algoritma pengurutan populer:
1.  **Simple Sort**: Bubble, Selection, Insertion.
2.  **Efficient Sort**: Shell, Quick, Merge, Heap.
3.  **Distribution Sort**: Radix Sort.
4.  **Specialized**: Tree Sort (menggunakan Binary Search Tree/BST) dan Exchange Sort.

### 🔍 10 Metode Searching
Pencarian data dilakukan dengan berbagai teknik:
* **By Saldo**: Binary Search, Interpolation Search, Fibonacci Search.
* **By ID**: Sequential Search, Linear Search (via Fungsi & Prosedur).
* **Advanced**: Search via Pointer, Search via Struct, serta pencarian pada Array 1D dan 2D (Matriks Transaksi).

### 💡 Konsep C++ Lainnya
* **Array 2D**: Digunakan untuk menyimpan matriks riwayat transaksi bulanan.
* **Pointer**: Demonstrasi aritmatika pointer dan alokasi memori dinamis (`new` & `delete`).
* **Struct**: Pengorganisasian data nasabah yang kompleks.
* **Header & Formatting**: Penggunaan `iomanip` untuk tampilan tabel yang rapi.

---

## 🛠️ Cara Menjalankan

1.  Pastikan Anda memiliki compiler C++ (seperti MinGW untuk Windows).
2.  Clone repositori ini:
    ```bash
    git clone https://github.com/nugrahreswara/UTS_Algoritma-Pemrograman-Lanjut.git
    ```
3.  Lakukan kompilasi:
    ```bash
    g++ program.cpp -o program_bank
    ```
4.  Jalankan program:
    ```bash
    ./program_bank
    ```

---

## 🖥️ Tampilan Menu Utama
```text
  ========== MENU UTAMA ==========
  1. Tampilkan Semua Data Nasabah
  2. Menu Sorting
  3. Menu Searching
  4. Demo Array 2 Dimensi
  5. Demo Pointer
  6. Demo Semua Metode Sorting
  7. Demo Semua Metode Searching
  0. Keluar
  =================================
