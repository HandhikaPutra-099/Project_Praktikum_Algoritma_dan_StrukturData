#include <iostream>
#include <iomanip>
using namespace std;

struct Buku {
    string Judul;
    string Pengarang;
    int Id;
};

// array untuk menyimpan buku
Buku DaftarBuku[100];
int jumlah = 0;

// fungsi menambahkan buku
void TambahBuku() {

}

int main(){

int pilihPeran;

string username, password;
string adminUser = "ADMIN";
string adminPass = "123";
string memberUser = "MEMBER";
string memberPass = "124";
char kembali;

do{
    cout << "\n=== SELAMAT DATANG DI PROGRAM SI-BOOK ===" << endl;
    cout << "==============================" << endl;
    cout << "| NO |       PILIHAN         |" << endl;
    cout << "==============================" << endl;
    cout << "|  1 |       Admin           |" << endl;
    cout << "==============================" << endl;
    cout << "|  2 |       Member          |" << endl;
    cout << "==============================" << endl;
    cout << "|  3 |       Register        |" << endl;
    cout << "==============================" << endl;
    cout << "|  4 |       Exit            |" << endl;
    cout << "==============================" << endl;
    cout << "+----------------------------+" << endl;
    cout << "Masukkan Pilihan Anda : "; cin >> pilihPeran; cin.ignore();
    cout << "+----------------------------+" << endl;
    system("cls");

    if(pilihPeran == 1){
        while(true){
            cout << "/n== Login Sebagai Admin ==" << endl;
            cout << "Masukkan Username\t : "; getline(cin, username);
            cout << "Masukkan Password\t: "; getline(cin, password);

                if (username == adminUser && password == adminPass)
                {
                    cout << "Login berhasil!\n";
                    break;
                }
                else
                {
                    cout << "Username atau password salah. Mohon Coba Lagi.\n";
                }

        }
    }

    else if(pilihPeran == 2){
        while(true){
            cout << "/n== Login Sebagai Member ==" << endl;
            cout << "Masukkan Username\t : "; getline(cin, username);
            cout << "Masukkan Password\t: "; getline(cin, password);

                if (username == memberUser && password == memberPass)
                {
                    cout << "Login berhasil!\n";
                    break;
                }
                else
                {
                    cout << "Username atau password salah. Mohon Coba lagi.\n";
                    cout << "Belum punya akun? Register dulu di menu 3.\n";
                    break;
                }

        }
    }

    else if(pilihPeran == 3){
        cout << "\n== Pendaftaran Member Baru ==" << endl;
        cout << "Buat Username\t: "; getline(cin, memberUser);
        cout << "Buat Password\t: "; getline(cin, memberPass);
        cout << "Registrasi Berhasil!\n";
    }

    else if(pilihPeran == 4){
        cout << "Terima Kasih Telah Menggunakan Program SI-BOOK."<< endl;
        return;
    }

} while(kembali == 'Y' || kembali == 'y');

cout << "Terima Kasih Telah Menggunakan Program SI-BOOK."<< endl;

}