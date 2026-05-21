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
    string tipeKamar;
    string status;
    int nomorKamar;
    int lamaInap;
    int harga;
    int total;

    Reservasi* next;
};

Reservasi* head = NULL;
Reservasi* tail = NULL;

string loginUser = "";
string loginRole = "";

int hargaKamar(string tipe){
    if(tipe == "Standard"){
        return 200000;
    }else if(tipe == "Deluxe"){
        return 350000;
    }else if(tipe == "Suite"){
        return 500000;
    } 
    return 0;
}

bool cekKamar(int kamar){
    Reservasi* temp = head;
    
    while(temp != NULL){
        if(temp->nomorKamar == kamar && temp->status != "checkout"){
            return true;
           }
           temp = temp->next;
    }
    return false;
}

void simpanFile(){
    FILE *file = fopen("reservasi.txt", "w");

    Reservasi* temp = head;

    while(temp != NULL){
        fprintf(file, "%s %s %s %d %d %d %d \n",
                    temp->nama.c_str(),
                    temp->tipeKamar.c_str(),
                    temp->status.c_str(),
                    temp->nomorKamar,
                    temp->lamaInap,
                    temp->harga,
                    temp->total);
        
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
    char tipe[100];
    char status[100];
    int kamar, lama, harga, total;

    while(fscanf(file, "%s %s %s %d %d %d %d",
                        nama, tipe, status,
                        &kamar, &lama, &harga, &total) != EOF){
        Reservasi* baru = new Reservasi;

        baru->nama = nama;
        baru->tipeKamar = tipe;
        baru->status = status;
        baru->nomorKamar = kamar;
        baru->lamaInap = lama;
        baru->harga = harga;
        baru->total = total;
        baru->next = NULL;
    
        if(head == NULL){
            head = tail = baru;
        }else{
            tail->next = baru;
            tail = baru;
        }
    }
    fclose(file);
}

void tambahReservasi() {
    string nama, tipe;
    int kamar, lama;
    int pilih;

    cout << "\n===== TAMBAH RESERVASI =====\n";
    cout << "Nama        : "; cin >> nama;
    cout << "Nomor kamar : "; cin >> kamar;

    if(cekKamar(kamar)){

        cout << "Kamar sudah dipakai!\n";
        return;
    }

    cout << "\n1. Standard\n";
    cout << "2. Deluxe\n";
    cout << "3. Suite\n";
    cout << "Pilih : "; cin >> pilih;

    if (pilih == 1) {
        tipe = "Standard";
    } else if (pilih == 2){
        tipe = "Deluxe";
    } else {
        tipe = "Suite";
    }
    cout << "Lama inap : "; cin >> lama;

    int harga = hargaKamar(tipe);
    int total = harga * lama;

    Reservasi* baru = new Reservasi;

    baru->nama = nama;
    baru->status = "Booking";
    baru->nomorKamar = kamar;
    baru->tipeKamar = tipe;
    baru->lamaInap = lama;
    baru->harga = harga;
    baru->total = total;
    baru->next = NULL;

    if (head == NULL) head = tail = baru;
    else {
        tail->next = baru;
        tail = baru;
    }
    simpanFile();
    cout << "Berhasil ditambahkan!\n";
}

void registerUser(){
    string usn, pw, role;

    cout << "\nREGISTER\n";
    cout << "Username          : "; cin >> usn;
    cout << "Password          : "; cin >> pw;
    cout << "Role (admin/user) : "; cin >> role;

    FILE *file = fopen("users.txt", "a");

    fprintf(file, "%s %s %s\n",
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

    while (fscanf(file, "%s %s %s", user, pass, role) != EOF) {

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

void tampilkan() {
    cout << "\n=================================================================\n";
    cout << "                     DATA RESERVASI HOTEL                        \n";
    cout << "=================================================================\n";

    if (head == NULL) { 
        cout << "Data masih kosong!\n";
        return;
    }

    cout << left
         << setw(5)  << "No"
         << setw(15) << "Nama"
         << setw(15) << "Tipe"
         << setw(15) << "Status"
         << setw(10) << "Kamar"
         << setw(10) << "Hari"
         << setw(15) << "Total"
         << endl;

    cout << "-------------------------------------\n";

    Reservasi* temp = head;
    int no = 1;

    while (temp != NULL) {
        cout << left
             << setw(5)  << no++
             << setw(15) << temp->nama
             << setw(15) << temp->tipeKamar
             << setw(15) << temp->status
             << setw(10) << temp->nomorKamar
             << setw(10) << temp->lamaInap
             << setw(15) << temp->total
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
            cout << "\n===== DATA DITEMUKAN =====\n";

            cout << "Nama        : " << temp->nama << endl;
            cout << "Kamar       : " << temp->nomorKamar << endl;
            cout << "Tipe        : " << temp->tipeKamar << endl;
            cout << "Status      : " << temp->status << endl;
            cout << "Lama Inap   : " << temp->lamaInap << endl;
            cout << "Total Bayar : " << temp->total << endl;

            ditemukan = true;
        }
        temp = temp->next;
    }

    if (!ditemukan) {
        cout << "Data tidak ditemukan!\n";
    }
}

void editReservasi(){

    string nama;

    cout << "\nMasukkan nama yang ingin diedit : ";
    cin >> nama;

    Reservasi* temp = head;

    while(temp != NULL){

        if(temp->nama == nama){

            cout << "Nama Baru : ";
            cin >> temp->nama;

            cout << "Lama Inap Baru : ";
            cin >> temp->lamaInap;

            temp->total = temp->lamaInap * temp->harga;

            simpanFile();

            cout << "Data berhasil diedit!\n";
            return;
        }

        temp = temp->next;
    }

    cout << "Data tidak ditemukan!\n";
}

void hapusReservasi(){

    string nama;

    cout << "\nMasukkan nama yang ingin dihapus : ";
    cin >> nama;

    Reservasi* temp = head;
    Reservasi* prev = NULL;

    while(temp != NULL){

        if(temp->nama == nama){

            if(prev == NULL){

                head = temp->next;

            }else{

                prev->next = temp->next;
            }

            if(temp == tail){

                tail = prev;
            }

            delete temp;

            simpanFile();

            cout << "Data berhasil dihapus!\n";
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    cout << "Data tidak ditemukan!\n";
}

void sortingNama(){
    if (head == NULL) {
        cout << "Data kosong!\n";
        return;
    }
    bool tukar;
    do {
        tukar = false;
        Reservasi* current = head;

        while (current->next != NULL) {
            if (current->nama > current->next->nama) {
                swap(current->nama, 
                    current->next->nama);

                swap(current->tipeKamar,
                     current->next->tipeKamar);

                swap(current->status,
                     current->next->status);

                swap(current->nomorKamar,
                     current->next->nomorKamar);

                swap(current->lamaInap,
                     current->next->lamaInap);

                swap(current->harga,
                     current->next->harga);

                swap(current->total,
                     current->next->total);
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
        cout << "4. Edit Reservasi\n";
        cout << "5. Hapus Reservasi\n";
        cout << "6. Sorting Nama\n";
        cout << "7. Logout\n";

        cout << "Pilih : "; cin >> pilih;
        switch (pilih) {
            case 1: tambahReservasi(); break;
            case 2: tampilkan(); break;
            case 3: cari(); break;
            case 4: editReservasi(); break;
            case 5: hapusReservasi(); break;
            case 6: sortingNama(); break;
        }
    } while (pilih != 7);
}

void menuUser() {
    int pilih;
    do{
        cout << "\n=====================================\n";
        cout << "              MENU USER             \n";
        cout << "=====================================\n";
        cout << "1. Buat Reservasi\n";
        cout << "2. Cari Reservasi\n";
        cout << "3. Check In\n";
        cout << "4. Check Out\n";
        cout << "5. Logout\n";
        cout << "Pilih : ";
        cin >> pilih;

        switch(pilih){
            case 1:
                tambahReservasi();
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