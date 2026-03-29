/*
==============================================================
   SISTEM PERBANKAN INDONESIA
   Program C++ dengan Tema Perbankan
   Materi: Sorting & Searching (LENGKAP)
==============================================================
   SORTING  : Shell, Tree, Exchange, Quick, Merge,
              Insertion, Radix, Heap, Selection, Bubble
   SEARCHING: Interpolation, Fibonacci, Sequential, Binary
   Juga mencakup: Prosedur, Fungsi, Prototipe Fungsi,
                  Array 1D, Array 2D, Pointer, Struct
==============================================================
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

// ============================================================
//                     STRUCT NASABAH
// ============================================================
struct Nasabah {
    int    id;
    string nama;
    string noRekening;
    double saldo;
    string jenisAkun; // Tabungan | Giro | Deposito
};

// ============================================================
//                  KONSTANTA & VARIABEL GLOBAL
// ============================================================
const int MAX_NASABAH = 100;
const int MAX_ROWS    = 5;   // baris matriks transaksi
const int MAX_COLS    = 4;   // kolom matriks transaksi (bulan)

// Array 1 Dimensi nasabah (global)
Nasabah daftarNasabah[MAX_NASABAH];
int     jumlahNasabah = 0;

// Array 2 Dimensi – riwayat transaksi bulanan
double matriks[MAX_ROWS][MAX_COLS];

// ============================================================
//              PROTOTIPE FUNGSI (Fungsi Prototype)
// ============================================================
// Utility
void clearScreen();
void tampilkanHeader();
void tampilkanNasabah(Nasabah* arr, int n);
void copyArray(Nasabah* src, Nasabah* dst, int n);
void tungguEnter();
void inisialisasiData();
void tampilkanMatriks();
void demoPointer();

// Sorting Algorithms
void insertionSort(Nasabah* arr, int n);
void shellSort(Nasabah* arr, int n);
void exchangeSort(Nasabah* arr, int n);     // Exchange Sort (Bubble style)
void bubbleSort(Nasabah* arr, int n);       // Bubble Sort (explicit)
void selectionSort(Nasabah* arr, int n);    // Selection Sort
void quickSort(Nasabah* arr, int low, int high);
int partisi(Nasabah* arr, int low, int high);
void mergeSort(Nasabah* arr, int l, int r);
void gabung(Nasabah* arr, int l, int m, int r);
void radixSort(Nasabah* arr, int n);
void countingSortDigit(Nasabah* arr, int n, long long exp);
void heapSort(Nasabah* arr, int n);
void heapify(Nasabah* arr, int n, int i);
void treeSort(Nasabah* arr, int n);
struct TreeNode;
TreeNode* sisipBST(TreeNode* root, Nasabah d);
void inorder(TreeNode* root, Nasabah* arr, int& idx);
void hapusPohon(TreeNode* root);

// Searching Algorithms
int interpolationSearch(Nasabah* arr, int n, double target);
int fibonacciSearch(Nasabah* arr, int n, double target);
int sequentialSearch(Nasabah* arr, int n, int targetID);   // Sequential Search by ID
int binarySearch(Nasabah* arr, int n, double target);      // Binary Search by saldo
void searchProsedur(Nasabah* arr, int n, int targetID);    // Prosedur
int searchFungsi(Nasabah* arr, int n, int targetID);       // Fungsi
void searchArray1D(double* saldoArr, int n, double target);
void searchArray2D(double mat[][MAX_COLS], int baris, int kolom);
void searchPointer(Nasabah* ptr, int n, const string& targetNama);
void searchStruct(Nasabah* arr, int n, const string& noRek);

// Menu & Demo
void menuSorting();
void menuSearching();
void demoSemuaSorting();
void demoSemuaSearching();

// ============================================================
//              IMPLEMENTASI FUNGSI UTILITAS
// ============================================================

// Bersihkan layar
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Header program
void tampilkanHeader() {
    cout << "\n";
    cout << "  ==========================================================\n";
    cout << "  ||          SISTEM PERBANKAN INDONESIA                  ||\n";
    cout << "  ||               Ngawi Jaya Bank                        ||\n";
    cout << "  ==========================================================\n";
}

// Tampilkan daftar nasabah (via pointer ke array)
void tampilkanNasabah(Nasabah* arr, int n) {
    if (n == 0) { cout << "  (Tidak ada data)\n"; return; }
    cout << "\n  " << string(78, '-') << "\n";
    cout << "  " << left
         << setw(4)  << "No"
         << setw(5)  << "ID"
         << setw(22) << "Nama"
         << setw(14) << "No.Rekening"
         << setw(18) << "Saldo (Rp)"
         << setw(12) << "Jenis" << "\n";
    cout << "  " << string(78, '-') << "\n";
    for (int i = 0; i < n; i++) {
        cout << "  " << left
             << setw(4)  << (i + 1)
             << setw(5)  << arr[i].id
             << setw(22) << arr[i].nama
             << setw(14) << arr[i].noRekening
             << setw(18) << fixed << setprecision(2) << arr[i].saldo
             << setw(12) << arr[i].jenisAkun << "\n";
    }
    cout << "  " << string(78, '-') << "\n";
}

// Salin array nasabah
void copyArray(Nasabah* src, Nasabah* dst, int n) {
    for (int i = 0; i < n; i++) dst[i] = src[i];
}

// Tunggu Enter
void tungguEnter() {
    cout << "\n  Tekan [Enter] untuk melanjutkan...";
    cin.ignore();
    cin.get();
}

// ============================================================
//                   ALGORITMA SORTING
// ============================================================

// ─── 1. INSERTION SORT (by saldo ascending) ────────────────
void insertionSort(Nasabah* arr, int n) {
    for (int i = 1; i < n; i++) {
        Nasabah key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].saldo > key.saldo) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// ─── 2. SHELL SORT (by saldo ascending) ────────────────────
void shellSort(Nasabah* arr, int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Nasabah temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap].saldo > temp.saldo) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

// ─── 3. EXCHANGE SORT (Bubble sort style) ──────────────────
void exchangeSort(Nasabah* arr, int n) {
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].saldo > arr[j + 1].saldo) {
                Nasabah tmp = arr[j];
                arr[j]     = arr[j + 1];
                arr[j + 1] = tmp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// ─── 4. BUBBLE SORT (explicit, similar but kept for requirement) ──
void bubbleSort(Nasabah* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].saldo > arr[j + 1].saldo) {
                Nasabah temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// ─── 5. SELECTION SORT (by saldo ascending) ────────────────
void selectionSort(Nasabah* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].saldo < arr[minIdx].saldo)
                minIdx = j;
        }
        if (minIdx != i) {
            Nasabah temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
        }
    }
}

// ─── 6. QUICK SORT (by saldo) ──────────────────────────────
int partisi(Nasabah* arr, int low, int high) {
    double pivot = arr[high].saldo;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].saldo <= pivot) {
            i++;
            Nasabah tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
        }
    }
    Nasabah tmp = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = tmp;
    return i + 1;
}

void quickSort(Nasabah* arr, int low, int high) {
    if (low < high) {
        int pi = partisi(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ─── 7. MERGE SORT (by saldo) ──────────────────────────────
void gabung(Nasabah* arr, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    Nasabah* L = new Nasabah[n1];
    Nasabah* R = new Nasabah[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i].saldo <= R[j].saldo) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    delete[] L;
    delete[] R;
}

void mergeSort(Nasabah* arr, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        gabung(arr, l, m, r);
    }
}

// ─── 8. RADIX SORT (by saldo, dikonversi ke long long) ─────
void countingSortDigit(Nasabah* arr, int n, long long exp) {
    Nasabah* output = new Nasabah[n];
    int count[10] = {0};
    for (int i = 0; i < n; i++) {
        long long digit = ((long long)(arr[i].saldo * 100) / exp) % 10;
        count[digit]++;
    }
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) {
        long long digit = ((long long)(arr[i].saldo * 100) / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }
    for (int i = 0; i < n; i++) arr[i] = output[i];
    delete[] output;
}

void radixSort(Nasabah* arr, int n) {
    long long maxVal = 0;
    for (int i = 0; i < n; i++) {
        long long v = (long long)(arr[i].saldo * 100);
        if (v > maxVal) maxVal = v;
    }
    for (long long exp = 1; maxVal / exp > 0; exp *= 10)
        countingSortDigit(arr, n, exp);
}

// ─── 9. HEAP SORT (by saldo) ───────────────────────────────
void heapify(Nasabah* arr, int n, int i) {
    int largest = i;
    int left    = 2 * i + 1;
    int right   = 2 * i + 2;
    if (left  < n && arr[left].saldo  > arr[largest].saldo) largest = left;
    if (right < n && arr[right].saldo > arr[largest].saldo) largest = right;
    if (largest != i) {
        Nasabah tmp = arr[i]; arr[i] = arr[largest]; arr[largest] = tmp;
        heapify(arr, n, largest);
    }
}

void heapSort(Nasabah* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        Nasabah tmp = arr[0]; arr[0] = arr[i]; arr[i] = tmp;
        heapify(arr, i, 0);
    }
}

// ─── 10. TREE SORT (BST in-order by saldo) ─────────────────
struct TreeNode {
    Nasabah  data;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* sisipBST(TreeNode* root, Nasabah d) {
    if (!root) {
        TreeNode* node = new TreeNode;
        node->data  = d;
        node->left  = node->right = nullptr;
        return node;
    }
    if (d.saldo < root->data.saldo)
        root->left  = sisipBST(root->left,  d);
    else
        root->right = sisipBST(root->right, d);
    return root;
}

void inorder(TreeNode* root, Nasabah* arr, int& idx) {
    if (!root) return;
    inorder(root->left,  arr, idx);
    arr[idx++] = root->data;
    inorder(root->right, arr, idx);
}

void hapusPohon(TreeNode* root) {
    if (!root) return;
    hapusPohon(root->left);
    hapusPohon(root->right);
    delete root;
}

void treeSort(Nasabah* arr, int n) {
    TreeNode* root = nullptr;
    for (int i = 0; i < n; i++) root = sisipBST(root, arr[i]);
    int idx = 0;
    inorder(root, arr, idx);
    hapusPohon(root);
}

// ============================================================
//                  ALGORITMA SEARCHING
// ============================================================

// ─── 1. INTERPOLATION SEARCH (array terurut by saldo) ──────
int interpolationSearch(Nasabah* arr, int n, double target) {
    int low = 0, high = n - 1;
    while (low <= high && target >= arr[low].saldo && target <= arr[high].saldo) {
        if (arr[high].saldo == arr[low].saldo) {
            return (arr[low].saldo == target) ? low : -1;
        }
        int pos = (int)(low + ((target - arr[low].saldo) /
                  (arr[high].saldo - arr[low].saldo)) * (high - low));
        if (pos < low || pos > high) return -1;
        if (arr[pos].saldo == target) return pos;
        if (arr[pos].saldo < target)  low  = pos + 1;
        else                          high = pos - 1;
    }
    return -1;
}

// ─── 2. FIBONACCI SEARCH (array terurut by saldo) ──────────
int fibonacciSearch(Nasabah* arr, int n, double target) {
    int fibM2 = 0, fibM1 = 1, fibM = 1;
    while (fibM < n) {
        fibM2 = fibM1;
        fibM1 = fibM;
        fibM  = fibM2 + fibM1;
    }
    int offset = -1;
    while (fibM > 1) {
        int i = min(offset + fibM2, n - 1);
        if (arr[i].saldo < target) {
            fibM  = fibM1; fibM1 = fibM2; fibM2 = fibM - fibM1;
            offset = i;
        } else if (arr[i].saldo > target) {
            fibM  = fibM2; fibM1 = fibM1 - fibM2; fibM2 = fibM - fibM1;
        } else return i;
    }
    if (fibM1 && (offset + 1) < n && arr[offset + 1].saldo == target)
        return offset + 1;
    return -1;
}

// ─── 3. SEQUENTIAL SEARCH (by ID, array tidak perlu urut) ───
int sequentialSearch(Nasabah* arr, int n, int targetID) {
    for (int i = 0; i < n; i++)
        if (arr[i].id == targetID) return i;
    return -1;
}

// ─── 4. BINARY SEARCH (array harus terurut by saldo) ───────
int binarySearch(Nasabah* arr, int n, double target) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].saldo == target) return mid;
        else if (arr[mid].saldo < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// ─── 5. PROSEDUR – Linear Search by ID ─────────────────────
void searchProsedur(Nasabah* arr, int n, int targetID) {
    cout << "\n  [PROSEDUR] Linear Search by ID = " << targetID << "\n";
    bool ditemukan = false;
    for (int i = 0; i < n; i++) {
        if (arr[i].id == targetID) {
            cout << "  >> Ditemukan di index [" << i << "]\n";
            cout << "     ID          : " << arr[i].id << "\n";
            cout << "     Nama        : " << arr[i].nama << "\n";
            cout << "     No. Rekening: " << arr[i].noRekening << "\n";
            cout << "     Saldo       : Rp " << fixed << setprecision(2) << arr[i].saldo << "\n";
            cout << "     Jenis Akun  : " << arr[i].jenisAkun << "\n";
            ditemukan = true;
            break;
        }
    }
    if (!ditemukan)
        cout << "  >> Nasabah dengan ID " << targetID << " TIDAK ditemukan.\n";
}

// ─── 6. FUNGSI – Linear Search by ID ───────────────────────
int searchFungsi(Nasabah* arr, int n, int targetID) {
    for (int i = 0; i < n; i++)
        if (arr[i].id == targetID) return i;
    return -1;
}

// ─── 7. SEARCH via ARRAY 1 DIMENSI (by saldo exact) ────────
void searchArray1D(double* saldoArr, int n, double target) {
    cout << "\n  [ARRAY 1D] Mencari saldo = Rp "
         << fixed << setprecision(2) << target << "\n";
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (saldoArr[i] == target) {
            cout << "  >> Ditemukan di index [" << i << "] -> "
                 << daftarNasabah[i].nama << "\n";
            found = true;
        }
    }
    if (!found) cout << "  >> Saldo tersebut TIDAK ditemukan.\n";
}

// ─── 8. SEARCH via ARRAY 2 DIMENSI (by posisi) ─────────────
void searchArray2D(double mat[][MAX_COLS], int baris, int kolom) {
    if (baris < 0 || baris >= MAX_ROWS || kolom < 0 || kolom >= MAX_COLS) {
        cout << "  [ARRAY 2D] Indeks di luar batas!\n";
        return;
    }
    cout << "\n  [ARRAY 2D] Transaksi Bulan-" << (kolom + 1)
         << " untuk Nasabah ke-" << (baris + 1) << ":\n";
    cout << "  >> Nasabah   : " << daftarNasabah[baris].nama << "\n";
    cout << "  >> Jumlah Tx : Rp "
         << fixed << setprecision(2) << mat[baris][kolom] << "\n";
}

// ─── 9. SEARCH via POINTER (by nama) ───────────────────────
void searchPointer(Nasabah* ptr, int n, const string& targetNama) {
    cout << "\n  [POINTER] Mencari nasabah bernama \"" << targetNama << "\"\n";
    bool found = false;
    for (int i = 0; i < n; i++) {
        if ((ptr + i)->nama == targetNama) {
            cout << "  >> Ditemukan di alamat memori : " << (ptr + i) << "\n";
            cout << "     ID          : " << (ptr + i)->id << "\n";
            cout << "     Nama        : " << (ptr + i)->nama << "\n";
            cout << "     Saldo       : Rp "
                 << fixed << setprecision(2) << (ptr + i)->saldo << "\n";
            found = true;
            break;
        }
    }
    if (!found) cout << "  >> Nama \"" << targetNama << "\" TIDAK ditemukan.\n";
}

// ─── 10. SEARCH via STRUCT (by No. Rekening) ────────────────
void searchStruct(Nasabah* arr, int n, const string& noRek) {
    cout << "\n  [STRUCT] Mencari No. Rekening \"" << noRek << "\"\n";
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (arr[i].noRekening == noRek) {
            Nasabah& ns = arr[i];
            cout << "  >> Ditemukan!\n";
            cout << "     ID          : " << ns.id << "\n";
            cout << "     Nama        : " << ns.nama << "\n";
            cout << "     No. Rekening: " << ns.noRekening << "\n";
            cout << "     Saldo       : Rp "
                 << fixed << setprecision(2) << ns.saldo << "\n";
            cout << "     Jenis Akun  : " << ns.jenisAkun << "\n";
            found = true;
            break;
        }
    }
    if (!found)
        cout << "  >> No. Rekening \"" << noRek << "\" TIDAK ditemukan.\n";
}

// ============================================================
//               INISIALISASI DATA PERBANKAN
// ============================================================
void inisialisasiData() {
    string names[] = {
        "Budi Santoso",    "Siti Rahayu",    "Ahmad Fauzi",
        "Dewi Lestari",    "Eko Prasetyo",   "Fitri Handayani",
        "Gunawan Wibowo",  "Hesti Kurniawan","Irfan Malik",
        "Joko Widodo"
    };
    string jenis[] = {
        "Tabungan","Giro","Deposito","Tabungan","Giro",
        "Deposito","Tabungan","Giro","Deposito","Tabungan"
    };
    double saldos[] = {
        5000000.00, 15000000.00,  8500000.00,  3200000.00, 22000000.00,
       11500000.00,  7800000.00, 19000000.00,  4300000.00, 33000000.00
    };

    jumlahNasabah = 10;
    for (int i = 0; i < jumlahNasabah; i++) {
        daftarNasabah[i].id          = i + 1;
        daftarNasabah[i].nama        = names[i];
        daftarNasabah[i].noRekening  = "BNK" + to_string(100000 + i);
        daftarNasabah[i].saldo       = saldos[i];
        daftarNasabah[i].jenisAkun   = jenis[i];
    }

    // Inisialisasi Array 2D transaksi bulanan (simulasi acak)
    srand((unsigned)time(nullptr));
    for (int i = 0; i < MAX_ROWS; i++)
        for (int j = 0; j < MAX_COLS; j++)
            matriks[i][j] = (double)(rand() % 9000000 + 1000000);
}

// ============================================================
//             TAMPILKAN ARRAY 2 DIMENSI
// ============================================================
void tampilkanMatriks() {
    cout << "\n  ===== RIWAYAT TRANSAKSI BULANAN (Array 2 Dimensi) =====\n";
    cout << "  " << left << setw(22) << "Nasabah";
    for (int j = 0; j < MAX_COLS; j++)
        cout << setw(17) << ("Bulan-" + to_string(j + 1));
    cout << "\n  " << string(90, '-') << "\n";
    for (int i = 0; i < MAX_ROWS; i++) {
        cout << "  " << setw(22) << daftarNasabah[i].nama;
        for (int j = 0; j < MAX_COLS; j++)
            cout << setw(17) << fixed << setprecision(0) << matriks[i][j];
        cout << "\n";
    }
    cout << "  " << string(90, '-') << "\n";
}

// ============================================================
//              DEMO POINTER
// ============================================================
void demoPointer() {
    cout << "\n  ===== DEMO PENGGUNAAN POINTER =====\n";
    Nasabah* ptr = daftarNasabah;

    cout << "  Pointer menunjuk ke data nasabah pertama:\n";
    cout << "  Alamat (ptr)      : " << ptr << "\n";
    cout << "  Nama  (*ptr).nama : " << ptr->nama << "\n";
    cout << "  Saldo (*ptr).saldo: Rp "
         << fixed << setprecision(2) << ptr->saldo << "\n";

    cout << "\n  Menelusuri 3 nasabah dengan pointer arithmetic:\n";
    for (int i = 0; i < 3; i++) {
        cout << "  [" << i << "] Alamat=" << (ptr + i)
             << "  Nama=" << left << setw(20) << (ptr + i)->nama
             << "  Saldo=Rp " << fixed << setprecision(2) << (ptr + i)->saldo << "\n";
    }

    cout << "\n  Contoh pointer dinamis (new / delete):\n";
    Nasabah* pDin = new Nasabah;
    pDin->id         = 99;
    pDin->nama       = "Nasabah Dinamis";
    pDin->noRekening = "BNK999999";
    pDin->saldo      = 9999999.00;
    pDin->jenisAkun  = "Tabungan";
    cout << "  >> Nama : " << pDin->nama
         << "  Saldo : Rp " << fixed << setprecision(2) << pDin->saldo << "\n";
    delete pDin;
    cout << "  >> Memori dibebaskan (delete).\n";
}

// ============================================================
//              MENU SORTING (LENGKAP 10 SORT)
// ============================================================
void menuSorting() {
    Nasabah temp[MAX_NASABAH];
    int pil;
    do {
        tampilkanHeader();
        cout << "\n  ========== MENU SORTING ==========\n";
        cout << "  1. Insertion Sort\n";
        cout << "  2. Shell Sort\n";
        cout << "  3. Exchange Sort\n";
        cout << "  4. Bubble Sort\n";
        cout << "  5. Selection Sort\n";
        cout << "  6. Quick Sort\n";
        cout << "  7. Merge Sort\n";
        cout << "  8. Radix Sort\n";
        cout << "  9. Heap Sort\n";
        cout << " 10. Tree Sort (BST)\n";
        cout << " 11. Tampilkan Data Asli\n";
        cout << "  0. Kembali\n";
        cout << "  Pilihan: ";
        cin >> pil;

        string label[] = {"", "INSERTION SORT", "SHELL SORT", "EXCHANGE SORT",
                          "BUBBLE SORT", "SELECTION SORT", "QUICK SORT",
                          "MERGE SORT", "RADIX SORT", "HEAP SORT", "TREE SORT"};

        if (pil >= 1 && pil <= 10) {
            copyArray(daftarNasabah, temp, jumlahNasabah);
            cout << "\n  Data SEBELUM sorting:\n";
            tampilkanNasabah(temp, jumlahNasabah);

            switch (pil) {
                case 1: insertionSort(temp, jumlahNasabah); break;
                case 2: shellSort(temp, jumlahNasabah); break;
                case 3: exchangeSort(temp, jumlahNasabah); break;
                case 4: bubbleSort(temp, jumlahNasabah); break;
                case 5: selectionSort(temp, jumlahNasabah); break;
                case 6: quickSort(temp, 0, jumlahNasabah - 1); break;
                case 7: mergeSort(temp, 0, jumlahNasabah - 1); break;
                case 8: radixSort(temp, jumlahNasabah); break;
                case 9: heapSort(temp, jumlahNasabah); break;
                case 10: treeSort(temp, jumlahNasabah); break;
            }
            cout << "\n  Data SESUDAH sorting [" << label[pil] << "] (ascending by saldo):\n";
            tampilkanNasabah(temp, jumlahNasabah);
            tungguEnter();
        } else if (pil == 11) {
            cout << "\n  Data Asli Nasabah:\n";
            tampilkanNasabah(daftarNasabah, jumlahNasabah);
            tungguEnter();
        }
    } while (pil != 0);
}

// ============================================================
//              MENU SEARCHING (LENGKAP)
// ============================================================
void menuSearching() {
    int pil;
    do {
        tampilkanHeader();
        cout << "\n  ========== MENU SEARCHING ==========\n";
        cout << "  1. Interpolation Search  (by Saldo)\n";
        cout << "  2. Fibonacci Search      (by Saldo)\n";
        cout << "  3. Sequential Search     (by ID)\n";
        cout << "  4. Binary Search         (by Saldo)\n";
        cout << "  5. Linear Search - Prosedur (by ID)\n";
        cout << "  6. Linear Search - Fungsi   (by ID)\n";
        cout << "  7. Search via Array 1 Dimensi (by Saldo)\n";
        cout << "  8. Search via Array 2 Dimensi (by Posisi)\n";
        cout << "  9. Search via Pointer    (by Nama)\n";
        cout << " 10. Search via Struct     (by No. Rekening)\n";
        cout << "  0. Kembali\n";
        cout << "  Pilihan: ";
        cin >> pil;

        if (pil == 1 || pil == 2 || pil == 4) {
            // Untuk Interpolation, Fibonacci, Binary: butuh array terurut
            Nasabah sorted[MAX_NASABAH];
            copyArray(daftarNasabah, sorted, jumlahNasabah);
            quickSort(sorted, 0, jumlahNasabah - 1);

            cout << "\n  Data (urut saldo):\n";
            tampilkanNasabah(sorted, jumlahNasabah);

            double target;
            cout << "\n  Masukkan saldo yang dicari: Rp ";
            cin >> target;

            int idx = -1;
            string metode;
            if (pil == 1) { idx = interpolationSearch(sorted, jumlahNasabah, target); metode = "INTERPOLATION"; }
            else if (pil == 2) { idx = fibonacciSearch(sorted, jumlahNasabah, target); metode = "FIBONACCI"; }
            else if (pil == 4) { idx = binarySearch(sorted, jumlahNasabah, target); metode = "BINARY"; }

            if (idx != -1) {
                cout << "\n  [" << metode << " SEARCH] Ditemukan di index [" << idx << "]:\n";
                cout << "  >> Nama  : " << sorted[idx].nama << "\n";
                cout << "  >> Saldo : Rp " << fixed << setprecision(2) << sorted[idx].saldo << "\n";
            } else {
                cout << "\n  [" << metode << " SEARCH] Data saldo Rp "
                     << fixed << setprecision(2) << target << " TIDAK ditemukan.\n";
            }
            tungguEnter();

        } else if (pil == 3) {
            // Sequential Search by ID
            cout << "\n  Daftar ID Nasabah:\n";
            for (int i = 0; i < jumlahNasabah; i++)
                cout << "  ID " << daftarNasabah[i].id << " -> " << daftarNasabah[i].nama << "\n";
            int id;
            cout << "  Masukkan ID yang dicari: ";
            cin >> id;
            int idx = sequentialSearch(daftarNasabah, jumlahNasabah, id);
            if (idx != -1) {
                cout << "\n  [SEQUENTIAL SEARCH] Ditemukan di index [" << idx << "]:\n";
                cout << "  >> Nama  : " << daftarNasabah[idx].nama << "\n";
                cout << "  >> Saldo : Rp " << fixed << setprecision(2) << daftarNasabah[idx].saldo << "\n";
            } else {
                cout << "\n  [SEQUENTIAL SEARCH] ID " << id << " TIDAK ditemukan.\n";
            }
            tungguEnter();

        } else if (pil == 5) {
            cout << "\n  Daftar ID Nasabah:\n";
            for (int i = 0; i < jumlahNasabah; i++)
                cout << "  ID " << daftarNasabah[i].id << " -> " << daftarNasabah[i].nama << "\n";
            int id;
            cout << "  Masukkan ID yang dicari: ";
            cin >> id;
            searchProsedur(daftarNasabah, jumlahNasabah, id);
            tungguEnter();

        } else if (pil == 6) {
            cout << "\n  Daftar ID Nasabah:\n";
            for (int i = 0; i < jumlahNasabah; i++)
                cout << "  ID " << daftarNasabah[i].id << " -> " << daftarNasabah[i].nama << "\n";
            int id;
            cout << "  Masukkan ID yang dicari: ";
            cin >> id;
            int idx = searchFungsi(daftarNasabah, jumlahNasabah, id);
            cout << "\n  [FUNGSI] ";
            if (idx != -1) {
                cout << "Ditemukan di index [" << idx << "]:\n";
                cout << "  >> Nama  : " << daftarNasabah[idx].nama << "\n";
                cout << "  >> Saldo : Rp " << fixed << setprecision(2) << daftarNasabah[idx].saldo << "\n";
            } else {
                cout << "ID " << id << " TIDAK ditemukan. (return -1)\n";
            }
            tungguEnter();

        } else if (pil == 7) {
            double saldoArr[MAX_NASABAH];
            cout << "\n  Array 1 Dimensi Saldo Nasabah:\n  [ ";
            for (int i = 0; i < jumlahNasabah; i++) {
                saldoArr[i] = daftarNasabah[i].saldo;
                cout << fixed << setprecision(0) << saldoArr[i];
                if (i < jumlahNasabah - 1) cout << ", ";
            }
            cout << " ]\n";
            double target;
            cout << "  Masukkan saldo yang dicari: Rp ";
            cin >> target;
            searchArray1D(saldoArr, jumlahNasabah, target);
            tungguEnter();

        } else if (pil == 8) {
            tampilkanMatriks();
            int baris, kolom;
            cout << "  Masukkan indeks baris  (0-" << MAX_ROWS - 1 << "): ";
            cin >> baris;
            cout << "  Masukkan indeks kolom  (0-" << MAX_COLS - 1 << "): ";
            cin >> kolom;
            searchArray2D(matriks, baris, kolom);
            tungguEnter();

        } else if (pil == 9) {
            cout << "\n  Daftar Nama Nasabah:\n";
            for (int i = 0; i < jumlahNasabah; i++)
                cout << "  - " << daftarNasabah[i].nama << "\n";
            string nama;
            cin.ignore();
            cout << "  Masukkan nama yang dicari: ";
            getline(cin, nama);
            searchPointer(daftarNasabah, jumlahNasabah, nama);
            tungguEnter();

        } else if (pil == 10) {
            cout << "\n  Daftar No. Rekening:\n";
            for (int i = 0; i < jumlahNasabah; i++)
                cout << "  " << daftarNasabah[i].noRekening
                     << " -> " << daftarNasabah[i].nama << "\n";
            string noRek;
            cin.ignore();
            cout << "  Masukkan No. Rekening: ";
            getline(cin, noRek);
            searchStruct(daftarNasabah, jumlahNasabah, noRek);
            tungguEnter();
        }
    } while (pil != 0);
}

// ============================================================
//         DEMO SEMUA METODE SORTING (10 SORT)
// ============================================================
void demoSemuaSorting() {
    tampilkanHeader();
    cout << "\n  ===== DEMO SEMUA METODE SORTING =====\n";
    cout << "  Data asli (sebelum sorting):\n";
    tampilkanNasabah(daftarNasabah, jumlahNasabah);

    const int JMLH_METODE = 10;
    string namaMetode[JMLH_METODE] = {
        "INSERTION SORT", "SHELL SORT", "EXCHANGE SORT", "BUBBLE SORT",
        "SELECTION SORT", "QUICK SORT", "MERGE SORT", "RADIX SORT",
        "HEAP SORT", "TREE SORT"
    };
    Nasabah temp[MAX_NASABAH];

    for (int m = 0; m < JMLH_METODE; m++) {
        copyArray(daftarNasabah, temp, jumlahNasabah);
        switch (m) {
            case 0: insertionSort(temp, jumlahNasabah); break;
            case 1: shellSort(temp, jumlahNasabah); break;
            case 2: exchangeSort(temp, jumlahNasabah); break;
            case 3: bubbleSort(temp, jumlahNasabah); break;
            case 4: selectionSort(temp, jumlahNasabah); break;
            case 5: quickSort(temp, 0, jumlahNasabah - 1); break;
            case 6: mergeSort(temp, 0, jumlahNasabah - 1); break;
            case 7: radixSort(temp, jumlahNasabah); break;
            case 8: heapSort(temp, jumlahNasabah); break;
            case 9: treeSort(temp, jumlahNasabah); break;
        }
        cout << "\n  [" << (m + 1) << "] " << namaMetode[m] << " (ascending saldo):\n";
        cout << "  ";
        for (int i = 0; i < jumlahNasabah; i++) {
            cout << setw(2) << (i + 1) << ". "
                 << left << setw(20) << temp[i].nama
                 << "Rp " << fixed << setprecision(2) << temp[i].saldo;
            if (i % 2 == 1) cout << "\n  ";
            else            cout << "   |   ";
        }
        cout << "\n";
    }
    tungguEnter();
}

// ============================================================
//         DEMO SEMUA METODE SEARCHING (LENGKAP)
// ============================================================
void demoSemuaSearching() {
    tampilkanHeader();
    cout << "\n  ===== DEMO SEMUA METODE SEARCHING =====\n";

    Nasabah sorted[MAX_NASABAH];
    copyArray(daftarNasabah, sorted, jumlahNasabah);
    quickSort(sorted, 0, jumlahNasabah - 1);

    double targetSaldo = sorted[jumlahNasabah / 2].saldo;
    int    targetID    = daftarNasabah[3].id;
    string targetNama  = daftarNasabah[3].nama;
    string targetRek   = daftarNasabah[3].noRekening;

    cout << "  Target saldo (searching 1,2,4) : Rp " << fixed << setprecision(2) << targetSaldo << "\n";
    cout << "  Target ID    (searching 3,5,6) : " << targetID << "\n";
    cout << "  Target nama  (searching 9)     : " << targetNama << "\n";
    cout << "  Target NoRek (searching 10)    : " << targetRek << "\n";
    cout << "\n  " << string(60, '-') << "\n";

    // 1. Interpolation
    { int idx = interpolationSearch(sorted, jumlahNasabah, targetSaldo);
      cout << "  1. INTERPOLATION SEARCH : " << (idx != -1 ? "DITEMUKAN -> " + sorted[idx].nama : "Tidak ditemukan") << "\n"; }
    // 2. Fibonacci
    { int idx = fibonacciSearch(sorted, jumlahNasabah, targetSaldo);
      cout << "  2. FIBONACCI SEARCH     : " << (idx != -1 ? "DITEMUKAN -> " + sorted[idx].nama : "Tidak ditemukan") << "\n"; }
    // 3. Sequential
    { int idx = sequentialSearch(daftarNasabah, jumlahNasabah, targetID);
      cout << "  3. SEQUENTIAL SEARCH    : " << (idx != -1 ? "DITEMUKAN index[" + to_string(idx) + "] -> " + daftarNasabah[idx].nama : "Tidak ditemukan") << "\n"; }
    // 4. Binary
    { int idx = binarySearch(sorted, jumlahNasabah, targetSaldo);
      cout << "  4. BINARY SEARCH        : " << (idx != -1 ? "DITEMUKAN -> " + sorted[idx].nama : "Tidak ditemukan") << "\n"; }
    // 5. Prosedur
    cout << "  5. PROSEDUR (Linear/ID) :\n";
    searchProsedur(daftarNasabah, jumlahNasabah, targetID);
    // 6. Fungsi
    { int idx = searchFungsi(daftarNasabah, jumlahNasabah, targetID);
      cout << "  6. FUNGSI   (Linear/ID) : " << (idx != -1 ? "DITEMUKAN index[" + to_string(idx) + "] -> " + daftarNasabah[idx].nama : "Tidak ditemukan") << "\n"; }
    // 7. Array 1D
    { double saldoArr[MAX_NASABAH];
      for (int i = 0; i < jumlahNasabah; i++) saldoArr[i] = daftarNasabah[i].saldo;
      bool found = false;
      for (int i = 0; i < jumlahNasabah; i++) if (saldoArr[i] == targetSaldo) { found = true; break; }
      cout << "  7. ARRAY 1 DIMENSI      : " << (found ? "DITEMUKAN di array saldo" : "Tidak ditemukan") << "\n"; }
    // 8. Array 2D
    { double val = matriks[0][0];
      cout << "  8. ARRAY 2 DIMENSI      : Nilai matriks[0][0] = Rp " << fixed << setprecision(0) << val << " (Ditemukan)\n"; }
    // 9. Pointer
    { Nasabah* ptr = daftarNasabah; bool found = false;
      for (int i = 0; i < jumlahNasabah; i++) if ((ptr + i)->nama == targetNama) {
          cout << "  9. POINTER (by Nama)    : DITEMUKAN di " << (ptr + i) << " -> " << (ptr + i)->nama << "\n";
          found = true; break; }
      if (!found) cout << "  9. POINTER (by Nama)    : Tidak ditemukan\n"; }
    // 10. Struct
    { bool found = false;
      for (int i = 0; i < jumlahNasabah; i++) if (daftarNasabah[i].noRekening == targetRek) {
          cout << " 10. STRUCT (by NoRek)    : DITEMUKAN -> " << daftarNasabah[i].nama << " | " << daftarNasabah[i].noRekening << "\n";
          found = true; break; }
      if (!found) cout << " 10. STRUCT (by NoRek)    : Tidak ditemukan\n"; }

    cout << "  " << string(60, '-') << "\n";
    tungguEnter();
}

// ============================================================
//                     MENU UTAMA
// ============================================================
int main() {
    inisialisasiData();
    int pil;

    do {
        clearScreen();
        tampilkanHeader();
        cout << "\n  ========== MENU UTAMA ==========\n";
        cout << "  1. Tampilkan Semua Data Nasabah\n";
        cout << "  2. Menu Sorting\n";
        cout << "  3. Menu Searching\n";
        cout << "  4. Demo Array 2 Dimensi (Riwayat Transaksi)\n";
        cout << "  5. Demo Pointer\n";
        cout << "  6. Demo Semua Metode Sorting\n";
        cout << "  7. Demo Semua Metode Searching\n";
        cout << "  0. Keluar\n";
        cout << "  =================================\n";
        cout << "  Pilihan: ";
        cin >> pil;

        switch (pil) {
            case 1:
                cout << "\n  ===== DATA NASABAH =====\n";
                tampilkanNasabah(daftarNasabah, jumlahNasabah);
                tungguEnter();
                break;
            case 2: menuSorting(); break;
            case 3: menuSearching(); break;
            case 4:
                tampilkanMatriks();
                tungguEnter();
                break;
            case 5:
                demoPointer();
                tungguEnter();
                break;
            case 6: demoSemuaSorting(); break;
            case 7: demoSemuaSearching(); break;
            case 0:
                cout << "\n  Terima kasih telah menggunakan Sistem Perbankan!\n\n";
                break;
            default:
                cout << "  Pilihan tidak valid! Silakan coba lagi.\n";
                tungguEnter();
        }
    } while (pil != 0);

    return 0;
}