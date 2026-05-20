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

cout << " =========================== " << endl;
cout << " |       Tambah Buku       |  " <<endl;
cout << " =========================== " << endl;
cout << " Masukan Data Buku Baru!"      << endl;
cout << " --------------------------- " << endl;
cout << "Masukan ID Buku : "; cin >> id; cin.ignore();
cout << "Masukan Judul Buku :"; getline(cin, judul);
cout << "Masukan Nama Pengarang Buku : "; getline(cin, pengarang);
cout << "Masukan Status Buku : "; getline (cin, status);

Buku *buku = bukuBaru(judul, pengarang, status, id);

if(head == NULL){
    head = tail = buku;
} else{
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
    cout << "\n==================== BUKU TERSEDIA ===================================\n";
    cout << left
         << setw(10) << "ID"
         << setw(25) << "Judul"
         << setw(25) << "Pengarang"
         << setw(15) << "Status" << endl;
    cout << "=======================================================================\n";
    while (hasil != NULL){
        if (hasil->status == "Tersedia"){
            cout << left
                 << setw(10) << hasil->Id
                 << setw(25) << hasil->Judul
                 << setw(25) << hasil->Pengarang
                 << setw(15) << hasil->status
                 << endl;
        } hasil = hasil->next;
    }
    cout << "=======================================================================\n";
}

void BukuDipinjam(){
    Buku *hasil = head;
    cout << "\n==================== BUKU DIPINJAM ===================================\n";
    cout << left
         << setw(10) << "ID"
         << setw(25) << "Judul"
         << setw(25) << "Pengarang"
         << setw(15) << "Status" << endl;
    cout << "========================================================================\n";
    while (hasil != NULL){
        if (hasil->status == "Dipinjam"){
            cout << left
                 << setw(10) << hasil->Id
                 << setw(25) << hasil->Judul
                 << setw(25) << hasil->Pengarang
                 << setw(15) << hasil->status
                 << endl;
        } hasil = hasil->next;
    }
    cout << "========================================================================\n";
}

void SemuaBuku(){
    FILE *file = fopen("data_buku.txt", "r");
    if(file == NULL){
        cout << "Data buku kosong!\n";
        return;
    }
    char judul[100];
    char pengarang[100];
    char status[50];
    int id;
    cout << "\n==================== SEMUA BUKU  =====================================\n";
    cout << left
         << setw(10) << "ID"
         << setw(25) << "Judul"
         << setw(25) << "Pengarang"
         << setw(15) << "Status" << endl;
    cout << "=======================================================================\n";
    while(fscanf(file,"%d|%99[^|]|%99[^|]|%49[^\n]\n", &id, judul, pengarang, status) == 4){
        cout << left
             << setw(10) << id
             << setw(25) << judul
             << setw(25) << pengarang
             << setw(15) << status
             << endl;
    }
    cout << "=======================================================================\n";
    fclose(file);
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
    } else if(pilihan == 2){
        BukuDipinjam();
    } else{
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
    bool ditemukan = false;
    
    while(temp != NULL){
        if(temp->Id == cariId){
            ditemukan = true;
            if(temp == head){
                head = head->next;
                if(head != NULL){
                    head->prev = NULL;
                }
            }else if(temp == tail){
                tail = tail->prev;
                if(tail != NULL){
                    tail->next = NULL;
                }
            }else{
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            delete temp;
            break;
        }
        temp = temp->next;
    }
    if(!ditemukan){
        cout << "\nID Buku tidak ditemukan!\n";
        return;
    }
    FILE *file = fopen("data_buku.txt", "w");
    Buku *simpan = head;

    while(simpan != NULL){
        fprintf(file, "%d|%s|%s|%s\n",
            simpan->Id,
            simpan->Judul.c_str(),
            simpan->Pengarang.c_str(),
            simpan->status.c_str());
        simpan = simpan->next;
    }
    fclose(file);
    cout << "\nBuku berhasil dihapus!\n";
}

void registerUser(){
	string usernameUser, passwordUser;
	cout << "\n===================="<< endl;
	cout << "    Registrasi      "<< endl;
	cout << "===================="<< endl;
	cout << "Masukan Username : "; getline(cin, usernameUser);
	cout << "Masukan Password : "; getline(cin, passwordUser);
	
	FILE *file = fopen("data_user.txt", "a");
	
	if(file == NULL){
		cout << "File tidak dapat dibuka!"<< endl;
		return;
		}
	fprintf(file, "%s|%s\n", usernameUser.c_str(), passwordUser.c_str());
	
	fclose(file);
	cout << "\nRegistrasi berhasil!"<< endl;	 
	}

void loginAdmin(){
	string username, password;
	string adminUser = "ADMIN";
	string adminPass = "123";

	cout << "\n== Login Sebagai Admin ==" << endl;
    cout << "Masukkan Username\t : "; getline(cin, username);
    cout << "Masukkan Password\t: "; getline(cin, password);

    if (username == adminUser && password == adminPass){
        cout << "\nLogin berhasil!\n";

        while(true){
            int pilihanAdmin;
            cout << "\n======================"<< endl;
            cout << "      MENU ADMIN      "<< endl;
            cout << "======================"<< endl;
            cout << "| 1 |  Tambah Buku   |"<< endl;
            cout << "======================"<< endl;
            cout << "| 2 |  List Buku     |"<< endl;
            cout << "======================"<< endl;
            cout << "| 3 |  Hapus Buku    |"<< endl;
            cout << "======================"<< endl;
            cout << "| 4 |  Logout        |"<< endl;
            cout << "======================"<< endl;
            cout << "\nMasukan Pilihan Anda : "; cin >> pilihanAdmin; cin.ignore();
            system("cls");

            if(pilihanAdmin == 1){
                TambahBuku();

            }else if(pilihanAdmin == 2){
                TampilkanBuku();

            }else if(pilihanAdmin == 3){
                HapusBuku();

            }else if(pilihanAdmin == 4){
                break;
            }
        }
    }else{
        cout << "Username atau password salah. Mohon Coba Lagi.\n";
    }
	}


	
void loginUser(){
	string usernameUser, passwordUser;
	//buat nyimpen username, password dari file
	char userFile[100], passFile[100];
	
	cout << "\n===================="<< endl;
	cout << "       LOGIN        "<< endl;
	cout << "===================="<< endl;
	cout << "Masukan Username : "; getline(cin,usernameUser);
	cout << "Masukan Password : "; getline(cin,passwordUser);
	
	FILE *file = fopen("data_user.txt", "r");
	if(file == NULL){
		cout << "Mohon Registrasi Terlebih Dahulu!\n"<< endl;
		return;
		}
	bool ditemukan = false;
	
	while(fscanf(file, "%99[^|]|%99[^\n]\n", userFile, passFile)==2){
	//buat baca data user dri file satu persatu
	
	if(usernameUser == userFile && passwordUser == passFile){
		ditemukan = true;
		break;
		}
	}
	fclose(file);
		
	if(ditemukan){
		cout << "Login berhasil!" << endl;
		}else{
			cout << "Password atau username salah. Mohon Coba Lagi.\n"<< endl;
			}
	}

void pinjamBuku(){
			int pilihanPinjam;
			cout << "Notes : Peminjaman buku hanya dapat dilakukan oleh user yang sudah terdaftar";
			cout << "\n============================"<< endl;
			cout << "         Pinjam Buku        "<< endl;
			cout << "============================"<< endl;
			cout << "| 1 |   Login              |"<< endl;
			cout << "============================"<< endl;
			cout << "| 2 |  Registrasi          |"<< endl;
			cout << "============================"<< endl;
			cout << "\nMasukan Pilihan Anda : ";cin >> pilihanPinjam; cin.ignore();
			system("cls");
			
			if(pilihanPinjam == 1){
				loginUser();

			}else if(pilihanPinjam == 2){
				registerUser();
			}
			
			}

void user(){
	
	while(true){
	int pilihanUser;
            cout << "\n==========================="<< endl;
            cout << "          MENU USER      "<< endl;
            cout << "==========================="<< endl;
            cout << "| 1 |   List Buku         |"<< endl;
            cout << "==========================="<< endl;
            cout << "| 2 |   Pinjam Buku       |"<< endl;
            cout << "==========================="<< endl;
            cout << "| 3 |   Kembalikan Buku   |"<< endl;
            cout << "==========================="<< endl;
            cout << "| 4 |   Logout            |"<< endl;
            cout << "==========================="<< endl;
            cout << "\nMasukan Pilihan Anda : "; cin >> pilihanUser; cin.ignore();
            system("cls");
        
        if(pilihanUser == 1){
			TampilkanBuku();
			
		}else if(pilihanUser == 2){
			pinjamBuku();
			
		}else if(pilihanUser == 3){
			cout << "blm"<< endl;
			
		}else if(pilihanUser == 4){
			cout << "Logout Berhasil."<< endl;
			return;
		}else{
			cout << "Pilih (1-4)" << endl;
			}
}
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
    system("cls");


if(pilihPeran == 1){
	loginAdmin();  
	   
} else if(pilihPeran == 2){
		user();
    }else if(pilihPeran == 3){
        cout << "Terima Kasih Telah Menggunakan Program SI-BOOK."<< endl;
        return 0;
    }

} while(true);
return 0;
}
