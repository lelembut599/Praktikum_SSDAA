#include <iostream>
#include <string>

using namespace std;

struct AlatPendakian {
    int id; 
    string nama;
    string jenis;
    int jumlah;
    AlatPendakian* next;
};

class LinkedList {
private:
    AlatPendakian* head;

public:
    LinkedList() : head(nullptr) {}

    void tambahAlat() {
        AlatPendakian* alat_baru = new AlatPendakian;
        cout << "Masukkan ID alat: ";
        cin >> alat_baru->id; 
        cin.ignore();
        cout << "Masukkan nama alat: ";
        getline(cin, alat_baru->nama);
        cout << "Masukkan jenis alat: ";
        getline(cin, alat_baru->jenis);
        cout << "Masukkan jumlah alat: ";
        cin >> alat_baru->jumlah;
        alat_baru->next = nullptr;

        if (head == nullptr) {
            head = alat_baru;
        } else {
            AlatPendakian* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = alat_baru;
        }
        cout << "Alat berhasil ditambahkan!\n";
    }

    void tampilkanAlat() {
        if (head == nullptr) {
            cout << "Tidak ada alat yang tersedia.\n";
            return;
        }

        cout << "Daftar Alat Pendakian:\n";
        AlatPendakian* current = head;
        while (current != nullptr) {
            cout << "ID: " << current->id 
                 << ", Nama: " << current->nama 
                 << ", Jenis: " << current->jenis 
                 << ", Jumlah: " << current->jumlah << endl;
            current = current->next;
        }
    }

    void ubahAlat() {
        int id;
        cout << "Masukkan ID alat yang ingin diubah: ";
        cin >> id;
        cin.ignore();

        AlatPendakian* current = head;
        while (current != nullptr) {
            if (current->id == id) {
                cout << "Masukkan nama alat baru: ";
                getline(cin, current->nama);
                cout << "Masukkan jenis alat baru: ";
                getline(cin, current->jenis);
                cout << "Masukkan jumlah alat baru: ";
                cin >> current->jumlah;
                cout << "Alat berhasil diubah!\n";
                return;
            }
            current = current->next;
        }
        cout << "Alat tidak ditemukan.\n";
    }

    void hapusAlat() {
        int id;
        cout << "Masukkan ID alat yang ingin dihapus: ";
        cin >> id;

        if (head == nullptr) {
            cout << "Tidak ada alat yang tersedia!\n";
            return;
        }

        if (head->id == id) { 
            AlatPendakian* temp = head;
            head = head->next;
            delete temp;
            cout << "Alat berhasil dihapus!\n";
            return;
        }

        AlatPendakian* current = head;
        while (current->next != nullptr && current->next->id != id) { 
            current = current->next;
        }

        if (current->next == nullptr) {
            cout << "ID tidak valid!\n";
            return;
        }

        AlatPendakian* temp = current->next;
        current->next = current->next->next; 
        delete temp;
        cout << "Alat berhasil dihapus!\n";
    }

    ~LinkedList() {
        AlatPendakian* current = head;
        while (current != nullptr) {
            AlatPendakian* next_node = current->next;
            delete current;
            current = next_node;
        }
    }
};

int main() {
    LinkedList daftar_alat;
    int pilihan;

    do {
        cout << "\nMenu:\n";
        cout << "[ 1.] Tambah Alat\n";
        cout << "[ 2.] Tampilkan Alat\n";
        cout << "[ 3.] Ubah Alat\n";
        cout << "[ 4.] Hapus Alat\n";
        cout << "[ 5.] Keluar\n";
        cout << "Pilih pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                daftar_alat.tambahAlat();
                break;
            case 2:
                daftar_alat.tampilkanAlat();
                break;
            case 3:
                daftar_alat.ubahAlat();
                break;
            case 4:
                daftar_alat.hapusAlat();
                break;
            case 5:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    } while (pilihan != 5);

    return 0;
}
