#include <iostream>
#include <stdio.h>
#include <iomanip>
using namespace std;

struct User {
    string username;
    string password;
    string role;
};

struct Reservasi {
    string nama;
    int nomorKamar;
    int lamaInap;
    Reservasi* next;
};

struct ReservasiDLL {
    string nama;
    int nomorKamar;
    int lamaInap;
    ReservasiDLL* next;
    ReservasiDLL* prev;
};


Reservasi* head = NULL;
Reservasi* tail = NULL;

ReservasiDLL* headDLL = NULL;
ReservasiDLL* tailDLL = NULL;

string loginUser = "";
string loginRole = "";

void tambahKeDLL(string nama, int kamar, int lama) {
    ReservasiDLL* baru = new ReservasiDLL;
    baru->nama = nama;
    baru->nomorKamar = kamar;
    baru->lamaInap = lama;
    baru->next = NULL;
    baru->prev = NULL;

    if (headDLL == NULL) {
        headDLL = tailDLL = baru;
    } else {
        tailDLL->next = baru;
        baru->prev = tailDLL;
        tailDLL = baru;
    }
}

void simpanFile(){
    FILE *file = fopen("reservasi.txt", "w");

    ReservasiDLL* temp = headDLL;

    while(temp != NULL){
        fprintf(file, "%s, %d, %d \n",
                    temp->nama.c_str(),
                    temp->nomorKamar,
                    temp->lamaInap);
        
        temp = temp->next;
    }
    fclose(file);
}

void bacaFile(){
    FILE *file = fopen("reservasi.txt", "r");

    if(file == NULL){
        return;
    }

    char nama[100];
    int kamar, lama;

    while(fscanf(file, "%s, %d, %d", nama, &kamar, &lama) != EOF){
        Reservasi* baru = new Reservasi;

        baru->nama = nama;
        baru->nomorKamar = kamar;
        baru->lamaInap = lama;
        baru->next = NULL;
    
        if(head == NULL){
            head = tail = baru;
        }else{
            tail->next = baru;
            tail = baru;
        }
        tambahKeDLL(nama, kamar, lama);
    }
    fclose(file);
}

void registerUser(){
    string usn, pw, role;

    cout << "\nREGISTER\n";
    cout << "Username          : "; cin >> usn;
    cout << "Password          : "; cin >> pw;
    cout << "Role (admin/user) : "; cin >> role;

    FILE *file = fopen("users.txt", "a");

    fprintf(file, "%s, %s, %s\n",
            usn.c_str(), pw.c_str(), role.c_str());
    
    fclose(file);
    cout << "Register berhasil!\n";
}

bool login() {
    string usn, pw;
    cout << "\nLOGIN\n";

    cout << "Username : "; cin >> usn;
    cout << "Password : "; cin >> pw;

    FILE *file = fopen("users.txt", "r");
    if (!file) return false;

    char user[100], pass[100], role[100];

    while (fscanf(file, "%s, %s, %s", user, pass, role) != EOF) {

        User usr;
        usr.username = user;
        usr.password = pass;
        usr.role = role;

        if (usn == usr.username && pw == usr.password) {
            loginUser = usr.username;
            loginRole = usr.role;
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

void buatReservasi() {
    string nama;
    int kamar, lama;

    cout << "\n=== Buat Reservasi ===\n";
    cout << "Nama: ";
    cin >> nama;
    cout << "Nomor Kamar: ";
    cin >> kamar;
    cout << "Lama Inap (hari): ";
    cin >> lama;

    Reservasi* baru = new Reservasi;
    baru->nama = nama;
    baru->nomorKamar = kamar;
    baru->lamaInap = lama;
    baru->next = NULL;

    if (head == NULL) {
        head = tail = baru;
    } else {
        tail->next = baru;
        tail = baru;
    }

    tambahKeDLL(nama, kamar, lama);

    cout << "Data berhasil ditambahkan!\n";
}

void tampilkan() {
    cout << "\n=====================================\n";
    cout << "        DATA RESERVASI HOTEL        \n";
    cout << "=====================================\n";

    if (headDLL == NULL) { 
        cout << "Data masih kosong!\n";
        return;
    }

    cout << left
         << setw(5)  << "No"
         << setw(15) << "Nama"
         << setw(15) << "Kamar"
         << setw(15) << "Lama"
         << endl;

    cout << "-------------------------------------\n";

    ReservasiDLL* temp = headDLL;
    int no = 1;

    while (temp != NULL) {
        cout << left
             << setw(5)  << no++
             << setw(15) << temp->nama
             << setw(15) << temp->nomorKamar
             << setw(15) << temp->lamaInap
             << endl;

        temp = temp->next;
    }
    cout << "-------------------------------------\n";
}

void cari() {
    string nama;
    cout << "\nMasukkan nama yang dicari: ";
    cin >> nama;

    Reservasi* temp = head; 
    bool ditemukan = false;

    while (temp != NULL) {
        if (temp->nama == nama) {
            cout << "\n=====================================\n";
            cout << "         DATA DITEMUKAN             \n";
            cout << "=====================================\n";
            cout << "Nama        : " << temp->nama << endl;
            cout << "Kamar       : " << temp->nomorKamar << endl;
            cout << "Lama Inap   : " << temp->lamaInap << " hari\n";
            cout << "=====================================\n";

            ditemukan = true;
        }
        
        temp = temp->next;
    }

    if (!ditemukan) {
        cout << "Data tidak ditemukan!\n";
    }
}

void hapusReservasi() {
    string nama;
    cout << "\nMasukkan nama yang ingin dihapus: ";
    cin >> nama;

    Reservasi* temp = head;
    Reservasi* prev = NULL;
    bool ada = false;

    while (temp != NULL) {
        if (temp->nama == nama) {
            ada = true;
            if (prev == NULL) {
                head = temp->next;
                if (head == NULL) {
                    tail = NULL;
                }
            } else {
                prev->next = temp->next;
                if (temp == tail) {
                    tail = prev;
                }
            }
            delete temp;
            break; 
        }
        prev = temp;
        temp = temp->next;
    }

    if (ada) {
        ReservasiDLL* tempDLL = headDLL;
        while (tempDLL != NULL) {
            if (tempDLL->nama == nama) {
                if (tempDLL->prev != NULL) tempDLL->prev->next = tempDLL->next;
                else headDLL = tempDLL->next;

                if (tempDLL->next != NULL) tempDLL->next->prev = tempDLL->prev;
                else tailDLL = tempDLL->prev;

                delete tempDLL;
                break;
            }
            tempDLL = tempDLL->next;
        }
        cout << "Data berhasil dihapus!\n";
    } else {
        cout << "Data tidak ditemukan!\n";
    }
}

void sortingNama(){
    if (headDLL == NULL) {
        cout << "Data kosong!\n";
        return;
    }
    bool tukar;
    do {
        tukar = false;
        ReservasiDLL* current = headDLL;

        while (current->next != NULL) {
            if (current->nama > current->next->nama) {
                swap(current->nama, current->next->nama);
                swap(current->nomorKamar, current->next->nomorKamar);
                swap(current->lamaInap, current->next->lamaInap);
                tukar = true;
            }
            current = current->next;
        }
    } while (tukar);
    simpanFile();
    cout << "\nData berhasil diurutkan!\n";
}

void menuAdmin() {
    int pilih;
    do{
        cout << "\n=====================================\n";
        cout << "             MENU ADMIN             \n";
        cout << "=====================================\n";
        cout << "1. Tambah Reservasi\n";
        cout << "2. Tampilkan Data\n";
        cout << "3. Cari Data\n";
        cout << "4. Hapus Reservasi\n";
        cout << "5. Sorting Nama\n";
        cout << "6. Logout\n";

        cout << "Pilih : "; cin >> pilih;
        switch (pilih) {
            case 1: buatReservasi(); break;
            case 2: tampilkan(); break;
            case 3: cari(); break;
            case 4: hapusReservasi(); break;
            case 5: sortingNama(); break;
        }
    } while (pilih != 6);
}

void menuUser() {
    int pilih;
    do{
        cout << "\n=====================================\n";
        cout << "              MENU USER             \n";
        cout << "=====================================\n";
        cout << "1. Buat Reservasi\n";
        cout << "2. Cari Reservasi\n";
        // cout << "3. Check In\n";
        // cout << "4. Check Out\n";
        cout << "5. Logout\n";
        cout << "Pilih : ";
        cin >> pilih;

        switch(pilih){
            case 1:
                buatReservasi();
                break;
            case 2:
                cari();
                break;
            case 3:
                ;
                break;
            case 4:
                ;
                break;
            case 5:
                cout << "Logout berhasil!\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    }while(pilih != 5);
}

void menuLogin() {
    int pilih;
    do{
        cout << "\n=====================================\n";
        cout << "             MENU LOGIN             \n";
        cout << "=====================================\n";

        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Keluar\n";
        cout << "Pilih : ";
        cin >> pilih;

        switch(pilih){
            case 1:
                registerUser();
                break;
            case 2:
                if(login()){
                    cout << "Login berhasil!\n";
                    if(loginRole == "admin"){
                        menuAdmin();
                    }else{
                        menuUser();
                    }
                }else{
                    cout << "Login gagal!\n";
                }
                break;
            case 3:
                cout << "Program selesai!\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    }while(pilih != 3);
}

int main() {
    bacaFile();
    menuLogin();
    return 0;
}