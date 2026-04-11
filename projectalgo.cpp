#include <iostream>
using namespace std;

struct Reservasi {
    string nama;
    int nomorKamar;
    int lamaInap;
    Reservasi* next;
};

Reservasi* head = NULL;
Reservasi* tail = NULL;

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

    cout << "Data berhasil ditambahkan!\n";
}

void tampilkan() {
    cout << "\n=== Data Reservasi ===\n";

    if (head == NULL) {
        cout << "Data masih kosong!\n";
        return;
    }

    Reservasi* temp = head;
    int no = 1;

    while (temp != NULL) {
        cout << no++ << ". "
             << temp->nama << " | Kamar: "
             << temp->nomorKamar << " | Lama: "
             << temp->lamaInap << " hari\n";
        temp = temp->next;
    }
}

void cari() {
    string nama;
    cout << "\nMasukkan nama yang dicari: ";
    cin >> nama;

    Reservasi* temp = head;
    bool ditemukan = false;

    while (temp != NULL) {
        if (temp->nama == nama) {
            cout << "Ditemukan: "
                 << temp->nama << " | Kamar: "
                 << temp->nomorKamar << " | Lama: "
                 << temp->lamaInap << " hari\n";
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

    while (temp != NULL) {
        if (temp->nama == nama) {

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
            cout << "Data berhasil dihapus!\n";
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    cout << "Data tidak ditemukan!\n";
}


int main() {
    int opsi;

    do {
        cout << "\n=== MENU RESERVASI HOTEL ===\n";
        cout << "1. Buat Reservasi\n";
        cout << "2. Tampilkan Reservasi\n";
        cout << "3. Cari Reservasi\n";
        cout << "4. Hapus Reservasi\n";
        cout << "Pilih opsi: ";
        cin >> opsi;

        switch (opsi) {
            case 1: 
                buatReservasi(); 
                break;
            case 2: 
                tampilkan(); 
                break;
            case 3: 
                cari(); 
                break;
            case 4: 
                hapusReservasi(); 
                break;
            case 5: 
            default: 
                cout << "Pilihan tidak valid!\n";
        }

    } while (opsi != 0);

    return 0;
}
