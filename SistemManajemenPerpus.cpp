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

Buku DaftarBuku[100];
int jumlah = 0;

Buku *head = NULL;
Buku *tail = NULL;

Buku *bukuBaru(string Judul, string Pengarang, string status, int Id){
    Buku *buku = new Buku();
    buku -> Judul = Judul;
    buku -> Pengarang = Pengarang;
    buku -> status = status;
    buku -> Id = Id;
    buku -> next = NULL;
    buku -> prev = NULL;
    return buku;

}

void TambahBuku() {
    string judul, pengarang, status;
    int id;

cout << " ================= " << endl;
cout << " |  Tambah Buku  |  " <<endl;
cout << " ================= " << endl;
cout << " Masukan Data Buku Baru!" << endl;
cout << "Masukan ID Buku : "; 
cin >> id; cin.ignore();
cout << "Masukan Judul Buku :";
getline(cin, judul);
cout << "Masukan Nama Pengarang Buku : ";
getline(cin, pengarang);
cout << "Masukan Status Buku : ";
getline (cin, status);

Buku *buku = bukuBaru(judul, pengarang, status, id);

if(head == NULL){
    head = tail = buku;
}

else{
    tail->next = buku;
    buku->prev = tail;
    tail = buku;
}

FILE *file = fopen("data_buku.txt", "a");

if(file == NULL){
    cout << "File tidak dapat dibuka!";
    return;
}
fprintf(file, "%d|%s|%s|%s\n",
    id,
    judul.c_str(),
    pengarang.c_str(),
    status.c_str());

    fclose(file);
}

void BukuTersedia(){

    Buku *hasil = head;

    cout << "\n==================== BUKU TERSEDIA ====================\n";

    cout << left
         << setw(10) << "ID"
         << setw(25) << "Judul"
         << setw(25) << "Pengarang"
         << setw(15) << "Status" << endl;

    cout << "=======================================================\n";

    while (hasil != NULL){

        if (hasil->status == "Tersedia"){

            cout << left
                 << setw(10) << hasil->Id
                 << setw(25) << hasil->Judul
                 << setw(25) << hasil->Pengarang
                 << setw(15) << hasil->status
                 << endl;
        }

        hasil = hasil->next;
    }

    cout << "=======================================================\n";
}

void BukuDipinjam(){
 
    Buku *hasil = head;

    cout << "\n==================== BUKU DIPINJAM ====================\n";

    cout << left
         << setw(10) << "ID"
         << setw(25) << "Judul"
         << setw(25) << "Pengarang"
         << setw(15) << "Status" << endl;

    cout << "=======================================================\n";

    while (hasil != NULL){

        if (hasil->status == "Dipinjam"){

            cout << left
                 << setw(10) << hasil->Id
                 << setw(25) << hasil->Judul
                 << setw(25) << hasil->Pengarang
                 << setw(15) << hasil->status
                 << endl;
        }

        hasil = hasil->next;
    }

    cout << "=======================================================\n";
}

void SemuaBuku(){
 
    Buku *hasil = head;

    cout << "\n=================== SEMUA BUKU ===================\n";
    cout << left
         << setw(10) << "ID"
         << setw(25) << "Judul"
         << setw(25) << "Pengarang"
         << setw(15) << "Status" << endl;

    cout << "===============================================================\n";

    while (hasil != NULL){

        cout << left
             << setw(10) << hasil->Id
             << setw(25) << hasil->Judul
             << setw(25) << hasil->Pengarang
             << setw(15) << hasil->status
             << endl;

        hasil = hasil->next;
    }

    cout << "===============================================================\n";
}
void TampilkanBuku(){
    FILE *files = fopen("data_buku.txt", "r");
    if (!files){
        cout << "Belum Ada Data Buku Yang Tersimpan" << endl;
        return;
    }
    int pilihan;
    cout << " ================= " << endl;
    cout << " / Daftar Buku / " << endl;
    cout << " ================= " << endl;
    cout << "1. Buku yang Tersedia" << endl;
    cout << "2. Buku yang Dipinjam" << endl;
    cout << "3. Semua Buku" << endl;
    cout << "Masukan Pilihan : "; cin >> pilihan; cin.ignore();
    cout << " ================= " << endl;
    if(pilihan == 1){
        BukuTersedia();
    }
    else if(pilihan == 2){
        BukuDipinjam();
    }
    else{
        SemuaBuku();
    }
}

void HapusBuku(){
    
    if(head == NULL){

        cout << "\nData buku kosong!\n";
        return;
    }

    int cariId;

    cout << "\nMasukkan ID Buku yang ingin dihapus : ";
    cin >> cariId;

    Buku *temp = head;

    while(temp != NULL){

        if(temp->Id == cariId){

            if(temp == head){

                head = head->next;

                if(head != NULL){
                    head->prev = NULL;
                }
            }
            else if(temp == tail){

                tail = tail->prev;
                tail->next = NULL;
            }
            else{

                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }

            delete temp;

            cout << "\nBuku berhasil dihapus!\n";

            return;
        }

        temp = temp->next;
    }

    cout << "\nID Buku tidak ditemukan!\n";
}


int main(){
FILE *file = fopen("data_buku.txt", "r");

if(file != NULL){

    char judul[100];
    char pengarang[100];
    char status[50];
    int id;

    while(fscanf(file,
    "%d|%99[^|]|%99[^|]|%49[^\n]\n",
    &id,
    judul,
    pengarang,
    status) == 4){

        Buku *buku = bukuBaru(
            judul,
            pengarang,
            status,
            id
        );

        if(head == NULL){
            head = tail = buku;
        }
        else{
            tail->next = buku;
            buku->prev = tail;
            tail = buku;
        }
    }

    fclose(file);
}


int pilihPeran;

string username, password;
string adminUser = "ADMIN";
string adminPass = "123";
char kembali;

do{
    cout << "\n=== SELAMAT DATANG DI PROGRAM SI-BOOK ===" << endl;
    cout << "==============================" << endl;
    cout << "| NO |       PILIHAN         |" << endl;
    cout << "==============================" << endl;
    cout << "|  1 |       Admin           |" << endl;
    cout << "==============================" << endl;
    cout << "|  2 |       User            |" << endl;
    cout << "==============================" << endl;
    cout << "|  3 |       Exit            |" << endl;
    cout << "==============================" << endl;
    cout << "+----------------------------+" << endl;
    cout << "Masukkan Pilihan Anda : "; cin >> pilihPeran; cin.ignore();
    cout << "+----------------------------+" << endl;
    system("cls");

    if(pilihPeran == 1){
        while(true){
            cout << "\n== Login Sebagai Admin ==" << endl;
            cout << "Masukkan Username\t : "; getline(cin, username);
            cout << "Masukkan Password\t: "; getline(cin, password);

                if (username == adminUser && password == adminPass){
                    cout << "Login berhasil!\n";
                    
                    int pilihanAdmin;
                    cout << "======================"<< endl;
                    cout << "      MENU ADMIN      "<< endl;
                    cout << "======================"<< endl;
                    cout << "| 1 |  Tambah Buku   |"<< endl;
                    cout << "======================"<< endl;
                    cout << "| 2 |  List Buku     |"<< endl;
                    cout << "======================"<< endl;
                    cout << "| 3 |  Hapus Buku    |"<< endl;
                    cout << "======================"<< endl;
                    cout << "+---------------------+" << endl;
                    cout << "Masukan Pilihan Anda : "; cin >> pilihanAdmin; cin.ignore();
                    cout << "+---------------------+" << endl;
                    system("cls");
                    char pilihLagi;
                    if(pilihanAdmin == 1){
                        TambahBuku();
                        
                    }else if(pilihanAdmin == 2){
                        TampilkanBuku();
                        
                    }else if(pilihanAdmin == 3){
                        HapusBuku();
                        
                    }
                     break;
                } else{
                    cout << "Username atau password salah. Mohon Coba Lagi.\n";
                }
    }
        
    } else if(pilihPeran == 2){
        
    }

    else if(pilihPeran == 3){
        cout << "Terima Kasih Telah Menggunakan Program SI-BOOK."<< endl;
        return 0;
    }

} while(true);
return 0;
}
