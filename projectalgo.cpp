#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <string>

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
};

struct NodeReservasi {
    Reservasi data;
    NodeReservasi* prev;
    NodeReservasi* next;
};

NodeReservasi* head = NULL;
NodeReservasi* tail = NULL;

string loginUser = "";
string loginRole = "";

void infoKamar() {
    cout << "\n--- INFORMASI TIPE KAMAR ---\n";
    cout << "1. Standard : Rp 200.000 / malam (Kasur Single, AC, TV)\n";
    cout << "2. Deluxe   : Rp 350.000 / malam (Kasur Queen, AC, TV, Kulkas)\n";
    cout << "3. Suite    : Rp 500.000 / malam (Kasur King, AC, Smart TV, Bathup)\n";
    cout << "----------------------------\n";
}

int hargaKamar(string tipe) {
    if(tipe == "Standard") {
        return 200000;
    } else if(tipe == "Deluxe") {
        return 350000;
    } else if(tipe == "Suite") {
        return 500000;
    }
    return 0;
}

bool cekKamar(int kamar) {
    NodeReservasi* temp = head;
    while(temp != NULL) {
        if(temp->data.nomorKamar == kamar && temp->data.status != "checkout") {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void simpanReservasi() {
    FILE *file = fopen("reservasi.txt", "w");
    NodeReservasi* temp = head;
    
    while(temp != NULL) {
        fprintf(file, "%s %s %s %d %d %d %d\n",
                temp->data.nama.c_str(), 
                temp->data.tipeKamar.c_str(), 
                temp->data.status.c_str(),
                temp->data.nomorKamar, 
                temp->data.lamaInap, 
                temp->data.harga, 
                temp->data.total);
        temp = temp->next;
    }
    fclose(file);
}

void tambahKeLinkedList(Reservasi baru) {
    NodeReservasi* nodeBaru = new NodeReservasi;
    nodeBaru->data = baru;
    nodeBaru->prev = NULL;
    nodeBaru->next = NULL;

    if (head == NULL) {
        head = tail = nodeBaru;
    } else {
        tail->next = nodeBaru;
        nodeBaru->prev = tail;
        tail = nodeBaru;
    }
}

void loadReservasi() {
    FILE *file = fopen("reservasi.txt", "r");
    if(file == NULL) {
        return;
    }
    
    char nama[100], tipe[100], status[100];
    int kamar, lama, harga, total;
    
    while(fscanf(file, "%s %s %s %d %d %d %d", nama, tipe, status, &kamar, &lama, &harga, &total) != EOF) {
        Reservasi baru;
        baru.nama = nama; 
        baru.tipeKamar = tipe; 
        baru.status = status;
        baru.nomorKamar = kamar; 
        baru.lamaInap = lama; 
        baru.harga = harga; 
        baru.total = total;
        
        tambahKeLinkedList(baru);
    }
    fclose(file);
}

void sinkronisasi(Reservasi arr[], int &jumlah) {
    jumlah = 0;
    NodeReservasi* temp = head;
    while(temp != NULL && jumlah < 100) {
        arr[jumlah] = temp->data;
        jumlah++;
        temp = temp->next;
    }
}

void urutkanNama(Reservasi arr[], int jumlah, bool asc) {
    for(int i = 0; i < jumlah - 1; i++) {
        for(int j = i + 1; j < jumlah; j++) {
            if (asc) {
                if(arr[i].nama > arr[j].nama) swap(arr[i], arr[j]);
            } else {
                if(arr[i].nama < arr[j].nama) swap(arr[i], arr[j]);
            }
        }
    }
}

void urutkanLamaInap(Reservasi arr[], int jumlah, bool asc) {
    for(int i = 0; i < jumlah - 1; i++) {
        for(int j = i + 1; j < jumlah; j++) {
            if (asc) {
                if(arr[i].lamaInap > arr[j].lamaInap) swap(arr[i], arr[j]);
            } else {
                if(arr[i].lamaInap < arr[j].lamaInap) swap(arr[i], arr[j]);
            }
        }
    }
}

void urutkanNomorKamar(Reservasi arr[], int jumlah, bool asc) {
    for(int i = 0; i < jumlah - 1; i++) {
        for(int j = i + 1; j < jumlah; j++) {
            if (asc) {
                if(arr[i].nomorKamar > arr[j].nomorKamar) swap(arr[i], arr[j]);
            } else {
                if(arr[i].nomorKamar < arr[j].nomorKamar) swap(arr[i], arr[j]);
            }
        }
    }
}

void tampilkanSorting() {
    Reservasi arr[100];
    int jumlah;
    sinkronisasi(arr, jumlah);
    
    if (jumlah == 0) { 
        cout << "Data hotel masih kosong!\n"; 
        return; 
    }

    int sortTipe, urutan;
    cout << "\n--- Urutkan Berdasarkan ---\n";
    cout << "1. Nama Pemesan\n";
    cout << "2. Lama Inap (Hari)\n";
    cout << "3. Nomor Kamar\n";
    cout << "Pilih: "; 
    cin >> sortTipe;
    
    cout << "\n--- Urutan ---\n";
    cout << "1. Ascending (Terkecil - Terbesar / A-Z)\n";
    cout << "2. Descending (Terbesar - Terkecil / Z-A)\n";
    cout << "Pilih: "; 
    cin >> urutan;

    bool asc = (urutan == 1);

    if(sortTipe == 1) urutkanNama(arr, jumlah, asc);
    else if(sortTipe == 2) urutkanLamaInap(arr, jumlah, asc);
    else if(sortTipe == 3) urutkanNomorKamar(arr, jumlah, asc);
    else cout << "Pilihan tidak valid, menampilkan data secara acak.\n";

    cout << "\n==========================================================================\n";
    cout << left << setw(5) << "No" << setw(15) << "Nama" << setw(15) << "Tipe" << setw(15) << "Status" 
         << setw(10) << "Kamar" << setw(10) << "Hari" << setw(15) << "Total" << endl;
    cout << "--------------------------------------------------------------------------\n";
    
    for(int i = 0; i < jumlah; i++) {
        cout << left << setw(5) << i+1 
             << setw(15) << arr[i].nama 
             << setw(15) << arr[i].tipeKamar 
             << setw(15) << arr[i].status 
             << setw(10) << arr[i].nomorKamar 
             << setw(10) << arr[i].lamaInap 
             << setw(15) << arr[i].total << endl;
    }
    cout << "--------------------------------------------------------------------------\n";
}

void cariBinary() {
    Reservasi arr[100];
    int jumlah;
    sinkronisasi(arr, jumlah);
    
    if (jumlah == 0) { 
        cout << "Data hotel kosong!\n"; 
        return; 
    }

    urutkanNama(arr, jumlah, true);

    string cari;
    cout << "\nMasukkan nama pemesan yang ingin dicari: "; 
    cin >> cari;

    int awal = 0, akhir = jumlah - 1, mid;
    bool ketemu = false;

    while(awal <= akhir) {
        mid = (awal + akhir) / 2;
        
        if(arr[mid].nama == cari) {
            cout << "\n===== DATA DITEMUKAN =====\n";
            cout << "Nama Pemesan : " << arr[mid].nama << endl;
            cout << "Nomor Kamar  : " << arr[mid].nomorKamar << endl;
            cout << "Tipe Kamar   : " << arr[mid].tipeKamar << endl;
            cout << "Status       : " << arr[mid].status << endl;
            cout << "Lama Inap    : " << arr[mid].lamaInap << " Hari" << endl;
            cout << "Total Bayar  : Rp " << arr[mid].total << endl;
            ketemu = true;
            break;
        } else if (cari < arr[mid].nama) {
            akhir = mid - 1;
        } else {
            awal = mid + 1;
        }
    }
    
    if(!ketemu) {
        cout << "Data reservasi atas nama '" << cari << "' tidak ditemukan!\n";
    }
}

void buatReservasi() {
    string nama, tipe;
    int kamar, lama, pilih;
    
    cout << "\n===== BUAT RESERVASI KAMAR =====\n";
    cout << "Masukkan Nama Pemesan (Tanpa Spasi) : "; 
    cin >> nama;
    
    cout << "Masukkan Nomor Kamar yang Diinginkan: "; 
    cin >> kamar;
    
    if(cekKamar(kamar)) { 
        cout << "Maaf, Kamar " << kamar << " sudah dipakai! Silakan pilih kamar lain.\n"; 
        return; 
    }

    infoKamar();
    cout << "Pilih Tipe Kamar (1-3): "; 
    cin >> pilih;
    
    if (pilih == 1) {
        tipe = "Standard";
    } else if (pilih == 2) {
        tipe = "Deluxe";
    } else {
        tipe = "Suite";
    }
    
    cout << "Masukkan Rencana Lama Inap (Hari)   : "; 
    cin >> lama;

    Reservasi baru;
    baru.nama = nama; 
    baru.status = "Booking"; 
    baru.nomorKamar = kamar;
    baru.tipeKamar = tipe; 
    baru.lamaInap = lama; 
    baru.harga = hargaKamar(tipe); 
    baru.total = baru.harga * lama;

    tambahKeLinkedList(baru);
    simpanReservasi();
    
    cout << "\nReservasi sukses! Kamar " << kamar << " telah dikunci untuk Bapak/Ibu " << nama << ".\n";
}

void editReservasi() {
    string nama;
    cout << "\n===== EDIT DATA RESERVASI =====\n";
    cout << "Masukkan nama pemesan yang ingin diedit : "; 
    cin >> nama;
    
    NodeReservasi* temp = head;
    
    while(temp != NULL) {
        if(temp->data.nama == nama) {
            cout << "Data Ditemukan! Tipe: " << temp->data.tipeKamar << ", Lama Sebelumnya: " << temp->data.lamaInap << " Hari.\n";
            cout << "Masukkan Lama Inap Baru (Hari) : "; 
            cin >> temp->data.lamaInap;

            temp->data.total = temp->data.lamaInap * temp->data.harga;
            simpanReservasi();
            
            cout << "Data berhasil diubah! Total tagihan baru: Rp " << temp->data.total << "\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Data tidak ditemukan dalam sistem!\n";
}

void hapusReservasi() {
    string nama;
    cout << "\n===== HAPUS DATA RESERVASI =====\n";
    cout << "Masukkan nama pemesan yang ingin dihapus : "; 
    cin >> nama;
    
    NodeReservasi* temp = head;
    
    while(temp != NULL) {
        if(temp->data.nama == nama) {
            if(temp->prev != NULL) {
                temp->prev->next = temp->next;
            } else {
                head = temp->next;
            }

            if(temp->next != NULL) {
                temp->next->prev = temp->prev;
            } else {
                tail = temp->prev;
            }

            delete temp;
            simpanReservasi();
            
            cout << "Data reservasi atas nama " << nama << " berhasil dihapus permanen!\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Data pemesan tidak ditemukan!\n";
}

void checkIn() {
    string nama;
    cout << "\n===== PROSES CHECK IN =====\n";
    cout << "Masukkan nama pemesan: "; 
    cin >> nama;

    NodeReservasi* temp = head;
    while (temp != NULL) {
        if (temp->data.nama == nama) {
            if (temp->data.status == "Booking") {
                temp->data.status = "checkin";
                simpanReservasi();
                cout << "Check-in berhasil untuk kamar " << temp->data.nomorKamar << "!\n";
                cout << "Selamat menikmati fasilitas hotel kami.\n";
            } else if (temp->data.status == "checkin") {
                cout << "Peringatan: Pemesan ini sudah berada di dalam kamar (Sudah Check-In).\n";
            } else {
                cout << "Peringatan: Pemesan ini sudah menyelesaikan reservasi (Sudah Check-Out).\n";
            }
            return;
        }
        temp = temp->next;
    }
    cout << "Data reservasi tidak ditemukan!\n";
}

void checkOut() {
    string nama;
    cout << "\n===== PROSES CHECK OUT =====\n";
    cout << "Masukkan nama pemesan: "; 
    cin >> nama;

    NodeReservasi* temp = head;
    while (temp != NULL) {
        if (temp->data.nama == nama) {
            if (temp->data.status == "checkin") {
                temp->data.status = "checkout";
                simpanReservasi();

                cout << "\n============================================\n";
                cout << "             HOTEL RECEIPT BILL             \n";
                cout << "============================================\n";
                cout << "Nama Pelanggan  : " << temp->data.nama << endl;
                cout << "Nomor Kamar     : " << temp->data.nomorKamar << endl;
                cout << "Tipe Kamar      : " << temp->data.tipeKamar << endl;
                cout << "Lama Menginap   : " << temp->data.lamaInap << " Hari" << endl;
                cout << "Harga Per Malam : Rp " << temp->data.harga << endl;
                cout << "--------------------------------------------\n";
                cout << "TOTAL KESELURUHAN : Rp " << temp->data.total << endl;
                cout << "============================================\n";
                cout << "       Terima Kasih Telah Berkunjung!       \n";
                cout << "============================================\n";
            } else if (temp->data.status == "Booking") {
                cout << "Gagal: Pelanggan belum melakukan Check-In sama sekali!\n";
            } else {
                cout << "Gagal: Pelanggan ini sudah Checkout sebelumnya.\n";
            }
            return;
        }
        temp = temp->next;
    }
    cout << "Data reservasi tidak ditemukan!\n";
}

void laporanPendapatan() {
    int totalPendapatan = 0;
    int kamarTerjual = 0;
    
    NodeReservasi* temp = head;
    while (temp != NULL) {
        if (temp->data.status == "checkout") {
            totalPendapatan += temp->data.total;
            kamarTerjual++;
        }
        temp = temp->next;
    }
    
    cout << "\n============================================\n";
    cout << "       LAPORAN PENDAPATAN HOTEL (FINAL)     \n";
    cout << "============================================\n";
    cout << "Total Kamar Selesai (Checkout) : " << kamarTerjual << " Kamar\n";
    cout << "Total Pendapatan Bersih        : Rp " << totalPendapatan << "\n";
    cout << "============================================\n";
}

void registerUser() {
    string usn, pw, role;
    cout << "\n===== REGISTRASI AKUN BARU =====\n";
    cout << "Masukkan Username          : "; 
    cin >> usn;
    cout << "Masukkan Password          : "; 
    cin >> pw;
    cout << "Pilih Role (admin / user)  : "; 
    cin >> role;
    
    FILE *file = fopen("users.txt", "a");
    fprintf(file, "%s %s %s\n", usn.c_str(), pw.c_str(), role.c_str());
    fclose(file);
    
    cout << "Registrasi berhasil! Silakan login menggunakan akun tersebut.\n";
}

bool login() {
    string usn, pw;
    cout << "\n===== LOGIN SISTEM =====\n";
    cout << "Username : "; 
    cin >> usn;
    cout << "Password : "; 
    cin >> pw;

    FILE *file = fopen("users.txt", "r");
    if (!file) {
        return false;
    }

    char user[100], pass[100], role[100];
    while (fscanf(file, "%s %s %s", user, pass, role) != EOF) {
        if (usn == string(user) && pw == string(pass)) {
            loginUser = string(user);
            loginRole = string(role);
            fclose(file);
            return true;
        }
    }
    fclose(file);
    return false;
}

void menuAdmin() {
    int pilih;
    do {
        cout << "\n============================================\n";
        cout << "               DASHBOARD ADMIN              \n";
        cout << "============================================\n";
        cout << "1. Buat Reservasi Kamar\n";
        cout << "2. Tampilkan Data (Multi-Sorting)\n";
        cout << "3. Cari Data Pelanggan (Binary Search)\n";
        cout << "4. Edit Durasi Menginap\n";
        cout << "5. Batalkan / Hapus Reservasi\n";
        cout << "6. Lihat Laporan Pendapatan Hotel\n";
        cout << "7. Logout\n";
        cout << "--------------------------------------------\n";
        cout << "Pilih Menu : "; 
        cin >> pilih;
        
        switch (pilih) {
            case 1: buatReservasi(); break;
            case 2: tampilkanSorting(); break;
            case 3: cariBinary(); break;
            case 4: editReservasi(); break;
            case 5: hapusReservasi(); break;
            case 6: laporanPendapatan(); break;
            case 7: cout << "Keluar dari mode Admin...\n"; break;
            default: cout << "Pilihan tidak tersedia!\n";
        }
    } while (pilih != 7);
}

void menuUser() {
    int pilih;
    do {
        cout << "\n============================================\n";
        cout << "          MENU PELANGGAN (RESEPSIONIS)      \n";
        cout << "============================================\n";
        cout << "1. Booking Kamar Baru\n";
        cout << "2. Cek Status Reservasi Saya\n";
        cout << "3. Lakukan Check-In\n";
        cout << "4. Lakukan Check-Out (Cetak Tagihan)\n";
        cout << "5. Logout\n";
        cout << "--------------------------------------------\n";
        cout << "Pilih Menu : "; 
        cin >> pilih;
        
        switch(pilih) {
            case 1: buatReservasi(); break;
            case 2: cariBinary(); break;
            case 3: checkIn(); break;
            case 4: checkOut(); break;
            case 5: cout << "Keluar dari mode Pelanggan...\n"; break;
            default: cout << "Pilihan tidak tersedia!\n";
        }
    } while(pilih != 5);
}

int main() {
    loadReservasi();
    
    int pilih;
    do {
        cout << "\n===== MENU OTENTIKASI =====\n";
        cout << "1. Buat Akun Baru (Register)\n";
        cout << "2. Masuk ke Sistem (Login)\n";
        cout << "3. Matikan Program\n";
        cout << "Pilih : "; 
        cin >> pilih;
        
        switch(pilih) {
            case 1: 
                registerUser(); 
                break;
            case 2:
                if(login()) {
                    cout << "Autentikasi Sukses! Selamat datang kembali, " << loginUser << ".\n";
                    if(loginRole == "admin") {
                        menuAdmin();
                    } else {
                        menuUser();
                    }
                } else {
                    cout << "Gagal Masuk! Username atau Password salah.\n";
                }
                break;
            case 3: 
                cout << "Menyimpan data & mematikan program...\nSampai Jumpa!\n"; 
                break;
            default: 
                cout << "Pilihan input tidak valid, silakan coba lagi!\n";
        }
    } while(pilih != 3);
    
    return 0;
}
