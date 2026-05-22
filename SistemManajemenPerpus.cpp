#include <iostream>
#include <iomanip>
using namespace std;

struct Buku {
    string Judul;
    string Pengarang;
    string status;
    int Id;
    Buku *next;
    Buku *prev;
};

Buku *head = NULL;
Buku *tail = NULL;

void swapData(Buku *a, Buku *b) {
    int  tmpId  = a->Id;        a->Id        = b->Id;        b->Id        = tmpId;
    string tmpJ = a->Judul;     a->Judul     = b->Judul;     b->Judul     = tmpJ;
    string tmpP = a->Pengarang; a->Pengarang = b->Pengarang; b->Pengarang = tmpP;
    string tmpS = a->status;    a->status    = b->status;    b->status    = tmpS;
}

string toLowerManual(string s) {
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] = s[i] + ('a' - 'A');
    }
    return s;
}

bool mengandung(string haystack, string needle) {
    haystack = toLowerManual(haystack);
    needle   = toLowerManual(needle);
    int hLen = (int)haystack.size();
    int nLen = (int)needle.size();
    if (nLen > hLen) return false;
    for (int i = 0; i <= hLen - nLen; i++) {
        bool cocok = true;
        for (int j = 0; j < nLen; j++) {
            if (haystack[i + j] != needle[j]) { cocok = false; break; }
        }
        if (cocok) return true;
    }
    return false;
}

Buku *bukuBaru(string Judul, string Pengarang, string status, int Id) {
    Buku *buku = new Buku();
    buku->Judul     = Judul;
    buku->Pengarang = Pengarang;
    buku->status    = status;
    buku->Id        = Id;
    buku->next      = NULL;
    buku->prev      = NULL;
    return buku;
}

void simpanSemuaBuku() {
    FILE *file = fopen("data_buku.txt", "w");
    if (!file) { cout << "Gagal menyimpan data buku!\n"; return; }
    Buku *curr = head;
    while (curr != NULL) {
        fprintf(file, "%d|%s|%s|%s\n",
            curr->Id,
            curr->Judul.c_str(),
            curr->Pengarang.c_str(),
            curr->status.c_str());
        curr = curr->next;
    }
    fclose(file);
}

Buku* cariBukuById(int id) {
    Buku *curr = head;
    while (curr != NULL) {
        if (curr->Id == id) return curr;
        curr = curr->next;
    }
    return NULL;
}

void menuCari() {
    if (head == NULL) { cout << "\nData buku kosong!\n"; return; }

    string keyword;
    cout << "\n========================================\n";
    cout << "          Cari Buku Berdasarkan Judul   \n";
    cout << "========================================\n";
    cout << "Masukkan Kata Kunci Judul : "; getline(cin, keyword);

    cout << "\n============ HASIL PENCARIAN ============\n";
    cout << left << setw(8)  << "ID"
                 << setw(30) << "Judul"
                 << setw(25) << "Pengarang"
                 << setw(12) << "Status" << "\n";
    cout << "=========================================\n";

    bool ada = false;
    Buku *curr = head;
    while (curr != NULL) {
        if (mengandung(curr->Judul, keyword)) {
            cout << left << setw(8)  << curr->Id
                         << setw(30) << curr->Judul
                         << setw(25) << curr->Pengarang
                         << setw(12) << curr->status << "\n";
            ada = true;
        }
        curr = curr->next;
    }
    if (!ada) cout << "  Tidak ditemukan buku dengan judul \"" << keyword << "\"\n";
    cout << "=========================================\n";
}

void sortById(bool ascending) {
    if (head == NULL || head->next == NULL) return;
    bool swapped;
    do {
        swapped = false;
        Buku *curr = head;
        while (curr->next != NULL) {
            bool perluSwap = ascending
                ? (curr->Id > curr->next->Id)
                : (curr->Id < curr->next->Id);
            if (perluSwap) {
                swapData(curr, curr->next);
                swapped = true;
            }
            curr = curr->next;
        }
    } while (swapped);
    simpanSemuaBuku();
}

void sortByJudul(bool ascending) {
    if (head == NULL || head->next == NULL) return;
    bool swapped;
    do {
        swapped = false;
        Buku *curr = head;
        while (curr->next != NULL) {
            bool perluSwap = ascending
                ? (toLowerManual(curr->Judul) > toLowerManual(curr->next->Judul))
                : (toLowerManual(curr->Judul) < toLowerManual(curr->next->Judul));
            if (perluSwap) {
                swapData(curr, curr->next);
                swapped = true;
            }
            curr = curr->next;
        }
    } while (swapped);
    simpanSemuaBuku();
}

void tampilHasilSort() {
    cout << "\n========= DAFTAR BUKU SETELAH PENGURUTAN =========\n";
    cout << left << setw(8)  << "ID"
                 << setw(30) << "Judul"
                 << setw(25) << "Pengarang"
                 << setw(12) << "Status" << "\n";
    cout << "===================================================\n";
    Buku *curr = head;
    while (curr != NULL) {
        cout << left << setw(8)  << curr->Id
                     << setw(30) << curr->Judul
                     << setw(25) << curr->Pengarang
                     << setw(12) << curr->status << "\n";
        curr = curr->next;
    }
    cout << "===================================================\n";
}

void menuSort() {
    if (head == NULL) { cout << "\nData buku kosong!\n"; return; }

    int pilKriteria, pilArah;

    cout << "\n==============================\n";
    cout << "        Urutkan Buku          \n";
    cout << "==============================\n";
    cout << "  Urutkan berdasarkan:\n";
    cout << "  | 1 | ID Buku              |\n";
    cout << "  | 2 | Judul Buku           |\n";
    cout << "==============================\n";
    cout << "  Pilihan : "; cin >> pilKriteria; cin.ignore();

    if (pilKriteria != 1 && pilKriteria != 2) {
        cout << "Pilihan tidak valid!\n"; return;
    }

    cout << "\n  Urutan:\n";
    cout << "  | 1 | Ascending  (A-Z / ID terkecil ke terbesar) |\n";
    cout << "  | 2 | Descending (Z-A / ID terbesar ke terkecil) |\n";
    cout << "  Pilihan : "; cin >> pilArah; cin.ignore();

    if (pilArah != 1 && pilArah != 2) {
        cout << "Pilihan tidak valid!\n"; return;
    }

    bool ascending = (pilArah == 1);
    string keterangan = ascending ? "Ascending" : "Descending";

    if (pilKriteria == 1) {
        sortById(ascending);
        cout << "\nBuku berhasil diurutkan berdasarkan ID (" << keterangan << ")!\n";
    } else {
        sortByJudul(ascending);
        cout << "\nBuku berhasil diurutkan berdasarkan Judul (" << keterangan << ")!\n";
    }

    tampilHasilSort();
}

void BukuTersedia() {
    Buku *hasil = head;
    cout << "\n==================== BUKU TERSEDIA ===================================\n";
    cout << left << setw(8)  << "ID"
                 << setw(30) << "Judul"
                 << setw(25) << "Pengarang"
                 << setw(12) << "Status" << "\n";
    cout << "=======================================================================\n";
    bool ada = false;
    while (hasil != NULL) {
        if (hasil->status == "Tersedia") {
            cout << left << setw(8)  << hasil->Id
                         << setw(30) << hasil->Judul
                         << setw(25) << hasil->Pengarang
                         << setw(12) << hasil->status << "\n";
            ada = true;
        }
        hasil = hasil->next;
    }
    if (!ada) cout << "  (Tidak ada buku yang tersedia)\n";
    cout << "=======================================================================\n";
}

void BukuDipinjam() {
    Buku *hasil = head;
    cout << "\n==================== BUKU DIPINJAM ===================================\n";
    cout << left << setw(8)  << "ID"
                 << setw(30) << "Judul"
                 << setw(25) << "Pengarang"
                 << setw(12) << "Status" << "\n";
    cout << "========================================================================\n";
    bool ada = false;
    while (hasil != NULL) {
        if (hasil->status == "Dipinjam") {
            cout << left << setw(8)  << hasil->Id
                         << setw(30) << hasil->Judul
                         << setw(25) << hasil->Pengarang
                         << setw(12) << hasil->status << "\n";
            ada = true;
        }
        hasil = hasil->next;
    }
    if (!ada) cout << "  (Tidak ada buku yang sedang dipinjam)\n";
    cout << "========================================================================\n";
}

void SemuaBuku() {
    if (head == NULL) { cout << "Data buku kosong!\n"; return; }
    cout << "\n==================== SEMUA BUKU  =====================================\n";
    cout << left << setw(8)  << "ID"
                 << setw(30) << "Judul"
                 << setw(25) << "Pengarang"
                 << setw(12) << "Status" << "\n";
    cout << "=======================================================================\n";
    Buku *curr = head;
    while (curr != NULL) {
        cout << left << setw(8)  << curr->Id
                     << setw(30) << curr->Judul
                     << setw(25) << curr->Pengarang
                     << setw(12) << curr->status << "\n";
        curr = curr->next;
    }
    cout << "=======================================================================\n";
}

void TampilkanBuku() {
    if (head == NULL) { cout << "Belum Ada Data Buku Yang Tersimpan\n"; return; }

    while (true) {
        int pilihan;
        cout << "\n===================================\n";
        cout << "          / List Buku /            \n";
        cout << "===================================\n";
        cout << "| 1 | Buku yang Tersedia          |\n";
        cout << "| 2 | Buku yang Dipinjam          |\n";
        cout << "| 3 | Semua Buku                  |\n";
        cout << "| 4 | Cari Buku (Judul)           |\n";
        cout << "| 5 | Urutkan Buku                |\n";
        cout << "| 6 | Kembali                     |\n";
        cout << "===================================\n";
        cout << "Masukan Pilihan : "; cin >> pilihan; cin.ignore();

        if      (pilihan == 1) BukuTersedia();
        else if (pilihan == 2) BukuDipinjam();
        else if (pilihan == 3) SemuaBuku();
        else if (pilihan == 4) menuCari();
        else if (pilihan == 5) menuSort();
        else if (pilihan == 6) { break; }
        else cout << "Pilih (1-6)\n";
    }
}

void TambahBuku() {
    string judul, pengarang, status;
    int id;

    cout << " =========================== \n";
    cout << " |       Tambah Buku       |  \n";
    cout << " =========================== \n";
    cout << " Masukan Data Buku Baru!\n";
    cout << " --------------------------- \n";
    cout << "Masukan ID Buku       : "; cin >> id;           cin.ignore();
    cout << "Masukan Judul Buku    : "; getline(cin, judul);
    cout << "Masukan Nama Pengarang: "; getline(cin, pengarang);
    cout << "Masukan Status Buku   : "; getline(cin, status);

    Buku *buku = bukuBaru(judul, pengarang, status, id);
    if (head == NULL) {
        head = tail = buku;
    } else {
        tail->next = buku;
        buku->prev = tail;
        tail = buku;
    }

    FILE *file = fopen("data_buku.txt", "a");
    if (!file) { cout << "File tidak dapat dibuka!\n"; return; }
    fprintf(file, "%d|%s|%s|%s\n",
        id, judul.c_str(), pengarang.c_str(), status.c_str());
    fclose(file);
    cout << "\nBuku berhasil ditambahkan!\n";
}

void HapusBuku() {
    if (head == NULL) { cout << "\nData buku kosong!\n"; return; }
    int cariId;
    cout << "\nMasukkan ID Buku yang ingin dihapus : "; cin >> cariId; cin.ignore();

    Buku *temp = head;
    bool ditemukan = false;

    while (temp != NULL) {
        if (temp->Id == cariId) {
            ditemukan = true;
            if (temp == head) {
                head = head->next;
                if (head != NULL) head->prev = NULL;
            } else if (temp == tail) {
                tail = tail->prev;
                if (tail != NULL) tail->next = NULL;
            } else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            delete temp;
            break;
        }
        temp = temp->next;
    }

    if (!ditemukan) { cout << "\nID Buku tidak ditemukan!\n"; return; }
    simpanSemuaBuku();
    cout << "\nBuku berhasil dihapus!\n";
}

void registerUser() {
    string usernameUser, passwordUser;
    cout << "\n====================\n";
    cout << "    Registrasi      \n";
    cout << "====================\n";
    cout << "Masukan Username : "; getline(cin, usernameUser);
    cout << "Masukan Password : "; getline(cin, passwordUser);

    FILE *file = fopen("data_user.txt", "a");
    if (!file) { cout << "File tidak dapat dibuka!\n"; return; }
    fprintf(file, "%s|%s\n", usernameUser.c_str(), passwordUser.c_str());
    fclose(file);
    cout << "\nRegistrasi berhasil! Silakan login.\n";
}

string loginUser() {
    string usernameUser, passwordUser;
    char userFile[100], passFile[100];

    cout << "\n====================\n";
    cout << "       LOGIN        \n";
    cout << "====================\n";
    cout << "Masukan Username : "; getline(cin, usernameUser);
    cout << "Masukan Password : "; getline(cin, passwordUser);

    FILE *file = fopen("data_user.txt", "r");
    if (!file) { cout << "Mohon Registrasi Terlebih Dahulu!\n"; return ""; }

    bool ditemukan = false;
    while (fscanf(file, "%99[^|]|%99[^\n]\n", userFile, passFile) == 2) {
        if (usernameUser == userFile && passwordUser == passFile) {
            ditemukan = true; break;
        }
    }
    fclose(file);

    if (ditemukan) {
        cout << "\nLogin berhasil! Selamat datang, " << usernameUser << "!\n";
        return usernameUser;
    }
    cout << "\nUsername atau password salah. Mohon Coba Lagi.\n";
    return "";
}

void simpanPinjaman(string username, int bookId) {
    FILE *file = fopen("data_pinjam.txt", "a");
    if (!file) { cout << "Gagal menyimpan data pinjaman!\n"; return; }
    fprintf(file, "%s|%d\n", username.c_str(), bookId);
    fclose(file);
}

void pinjamBukuSetelahLogin(string username) {
    BukuTersedia();
    int id;
    cout << "\nMasukkan ID Buku yang ingin dipinjam : "; cin >> id; cin.ignore();

    Buku *buku = cariBukuById(id);
    if (buku == NULL) { cout << "Buku dengan ID " << id << " tidak ditemukan!\n"; return; }
    if (buku->status != "Tersedia") {
        cout << "Buku \"" << buku->Judul << "\" sedang tidak tersedia!\n"; return;
    }
    buku->status = "Dipinjam";
    simpanSemuaBuku();
    simpanPinjaman(username, id);
    cout << "\nBuku \"" << buku->Judul << "\" berhasil dipinjam oleh " << username << "!\n";
}

void pinjamBuku() {
    int pilihanPinjam;
    cout << "\nNotes : Peminjaman buku hanya untuk user yang sudah terdaftar.\n";
    cout << "\n============================\n";
    cout << "         Pinjam Buku        \n";
    cout << "============================\n";
    cout << "| 1 |  Login               |\n";
    cout << "| 2 |  Registrasi          |\n";
    cout << "============================\n";
    cout << "\nMasukan Pilihan Anda : "; cin >> pilihanPinjam; cin.ignore();
    system("cls");

    string username = "";
    if (pilihanPinjam == 1) {
        username = loginUser();
    } else if (pilihanPinjam == 2) {
        registerUser();
        cout << "\nSilakan login untuk melanjutkan peminjaman.\n";
        username = loginUser();
    } else {
        cout << "Pilihan tidak valid!\n"; return;
    }
    if (username != "") pinjamBukuSetelahLogin(username);
}

void kembalikanBukuSetelahLogin(string username) {
    FILE *filePinjam = fopen("data_pinjam.txt", "r");
    if (!filePinjam) { cout << "Tidak ada data peminjaman sama sekali!\n"; return; }

    char userFile[100];
    int bookId;
    bool adaPinjaman = false;

    cout << "\n====== Daftar Buku yang Anda Pinjam ======\n";
    cout << left << setw(8)  << "ID"
                 << setw(30) << "Judul"
                 << setw(25) << "Pengarang" << "\n";
    cout << "===========================================\n";
    while (fscanf(filePinjam, "%99[^|]|%d\n", userFile, &bookId) == 2) {
        if (username == userFile) {
            Buku *b = cariBukuById(bookId);
            if (b) {
                cout << left << setw(8)  << b->Id
                             << setw(30) << b->Judul
                             << setw(25) << b->Pengarang << "\n";
                adaPinjaman = true;
            }
        }
    }
    fclose(filePinjam);
    cout << "===========================================\n";

    if (!adaPinjaman) { cout << "Anda tidak memiliki pinjaman buku!\n"; return; }

    int id;
    cout << "\nMasukkan ID Buku yang ingin dikembalikan : "; cin >> id; cin.ignore();

    filePinjam = fopen("data_pinjam.txt", "r");
    bool valid = false;
    while (fscanf(filePinjam, "%99[^|]|%d\n", userFile, &bookId) == 2) {
        if (username == userFile && bookId == id) { valid = true; break; }
    }
    fclose(filePinjam);

    if (!valid) { cout << "Anda tidak meminjam buku dengan ID " << id << "!\n"; return; }

    Buku *buku = cariBukuById(id);
    if (!buku) { cout << "Data buku tidak ditemukan di sistem!\n"; return; }

    buku->status = "Tersedia";
    simpanSemuaBuku();

    filePinjam         = fopen("data_pinjam.txt", "r");
    FILE *fileTemp     = fopen("data_pinjam_temp.txt", "w");
    bool sudahHapus    = false;
    while (fscanf(filePinjam, "%99[^|]|%d\n", userFile, &bookId) == 2) {
        if (!sudahHapus && username == userFile && bookId == id) {
            sudahHapus = true;
        } else {
            fprintf(fileTemp, "%s|%d\n", userFile, bookId);
        }
    }
    fclose(filePinjam);
    fclose(fileTemp);
    remove("data_pinjam.txt");
    rename("data_pinjam_temp.txt", "data_pinjam.txt");

    cout << "\nBuku \"" << buku->Judul << "\" berhasil dikembalikan. Terima kasih, " << username << "!\n";
}

void kembalikanBuku() {
    int pilihanKembali;
    cout << "\nNotes : Pengembalian buku hanya untuk user yang sudah terdaftar.\n";
    cout << "\n============================\n";
    cout << "      Kembalikan Buku       \n";
    cout << "============================\n";
    cout << "| 1 |  Login               |\n";
    cout << "| 2 |  Registrasi          |\n";
    cout << "============================\n";
    cout << "\nMasukan Pilihan Anda : "; cin >> pilihanKembali; cin.ignore();
    system("cls");

    string username = "";
    if (pilihanKembali == 1) {
        username = loginUser();
    } else if (pilihanKembali == 2) {
        registerUser();
        cout << "\nSilakan login untuk melanjutkan pengembalian.\n";
        username = loginUser();
    } else {
        cout << "Pilihan tidak valid!\n"; return;
    }
    if (username != "") kembalikanBukuSetelahLogin(username);
}

void loginAdmin() {
    string username, password;
    const string adminUser = "ADMIN";
    const string adminPass = "123";

    cout << "\n== Login Sebagai Admin ==\n";
    cout << "Masukkan Username : "; getline(cin, username);
    cout << "Masukkan Password : "; getline(cin, password);

    if (username != adminUser || password != adminPass) {
        cout << "\nUsername atau password salah. Mohon Coba Lagi.\n"; return;
    }
    cout << "\nLogin berhasil!\n";

    while (true) {
        int pilihanAdmin;
        cout << "\n============================\n";
        cout << "        MENU ADMIN          \n";
        cout << "============================\n";
        cout << "| 1 |  Tambah Buku         |\n";
        cout << "| 2 |  List Buku           |\n";
        cout << "| 3 |  Hapus Buku          |\n";
        cout << "| 4 |  Logout              |\n";
        cout << "============================\n";
        cout << "\nMasukan Pilihan Anda : "; cin >> pilihanAdmin; cin.ignore();
        system("cls");

        if      (pilihanAdmin == 1) TambahBuku();
        else if (pilihanAdmin == 2) TampilkanBuku();
        else if (pilihanAdmin == 3) HapusBuku();
        else if (pilihanAdmin == 4) { cout << "Logout Admin berhasil.\n"; break; }
        else cout << "Pilih (1-4)\n";
    }
}

void user() {
    while (true) {
        int pilihanUser;
        cout << "\n============================\n";
        cout << "         MENU USER          \n";
        cout << "============================\n";
        cout << "| 1 |  List Buku           |\n";
        cout << "| 2 |  Pinjam Buku         |\n";
        cout << "| 3 |  Kembalikan Buku     |\n";
        cout << "| 4 |  Logout              |\n";
        cout << "============================\n";
        cout << "\nMasukan Pilihan Anda : "; cin >> pilihanUser; cin.ignore();
        system("cls");

        if      (pilihanUser == 1) TampilkanBuku();
        else if (pilihanUser == 2) pinjamBuku();
        else if (pilihanUser == 3) kembalikanBuku();
        else if (pilihanUser == 4) { cout << "Logout berhasil.\n"; return; }
        else cout << "Pilih (1-4)\n";
    }
}

int main() {
    FILE *file = fopen("data_buku.txt", "r");
    if (file != NULL) {
        char judul[100], pengarang[100], status[50];
        int id;
        while (fscanf(file, "%d|%99[^|]|%99[^|]|%49[^\n]\n",
                      &id, judul, pengarang, status) == 4) {
            Buku *buku = bukuBaru(judul, pengarang, status, id);
            if (head == NULL) { head = tail = buku; }
            else { tail->next = buku; buku->prev = tail; tail = buku; }
        }
        fclose(file);
    }

    int pilihPeran;
    do {
        cout << "\n=== SELAMAT DATANG DI PROGRAM SI-BOOK ===\n";
        cout << "==============================\n";
        cout << "| NO |       PILIHAN         |\n";
        cout << "==============================\n";
        cout << "|  1 |       Admin           |\n";
        cout << "==============================\n";
        cout << "|  2 |       User            |\n";
        cout << "==============================\n";
        cout << "|  3 |       Exit            |\n";
        cout << "==============================\n";
        cout << "Masukkan Pilihan Anda : "; cin >> pilihPeran; cin.ignore();
        system("cls");

        if      (pilihPeran == 1) loginAdmin();
        else if (pilihPeran == 2) user();
        else if (pilihPeran == 3) {
            cout << "Terima Kasih Telah Menggunakan Program SI-BOOK.\n";
            return 0;
        }
    } while (true);

    return 0;
}
