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

void tambahReservasi() {
    string nama;
    int kamar, lama;

    cout << "\n=== Tambah Reservasi ===\n";
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
    return 0;
}
