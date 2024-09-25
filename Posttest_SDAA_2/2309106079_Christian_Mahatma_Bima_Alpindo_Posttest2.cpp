#include <iostream>
#include <string>

using namespace std;

const int MAX_ALAT = 100; // Batas maksimum jumlah alat

struct AlatPendakian {
    string nama;
    string jenis;
    int jumlah;
};

// Fungsi untuk menambah alat
void tambahAlat(AlatPendakian* alatList, int& count) {
    if (count >= MAX_ALAT) {
        cout << "Tidak dapat menambah alat, kapasitas penuh!\n";
        return;
    }

    AlatPendakian* alat = new AlatPendakian; // Menggunakan pointer
    cout << "Masukkan nama alat: ";
    cin.ignore(); // Mengabaikan newline yang tersisa
    getline(cin, alat->nama); // Menggunakan getline
    cout << "Masukkan jenis alat: ";
    getline(cin, alat->jenis); // Menggunakan getline
    cout << "Masukkan jumlah alat: ";
    cin >> alat->jumlah;

    alatList[count++] = *alat; // Dereference untuk menyimpan ke dalam array
    delete alat; // Menghapus objek dari heap
    cout << "Alat berhasil ditambahkan!\n";
}

// Fungsi untuk menampilkan alat
void tampilkanAlat(AlatPendakian* alatList, int count) {
    if (count == 0) {
        cout << "Tidak ada alat yang tersedia.\n";
        return;
    }

    cout << "Daftar Alat Pendakian:\n";
    for (int i = 0; i < count; i++) {
        AlatPendakian& alat = alatList[i]; // Menggunakan referensi
        cout << "Nama: " << alat.nama 
             << ", Jenis: " << alat.jenis 
             << ", Jumlah: " << alat.jumlah << endl;
    }
}

// Fungsi untuk mengubah alat
void ubahAlat(AlatPendakian* alatList, int count) {
    string nama;
    cout << "Masukkan nama alat yang ingin diubah: ";
    cin.ignore(); // Mengabaikan newline yang tersisa
    getline(cin, nama); // Menggunakan getline

    for (int i = 0; i < count; i++) {
        if (alatList[i].nama == nama) {
            AlatPendakian& alat = alatList[i]; // Menggunakan referensi
            cout << "Masukkan jenis alat baru: ";
            getline(cin, alat.jenis); // Menggunakan getline
            cout << "Masukkan jumlah alat baru: ";
            cin >> alat.jumlah;
            cout << "Alat berhasil diubah!\n";
            return;
        }
    }
    cout << "Alat tidak ditemukan.\n";
}

// Fungsi untuk menghapus alat
void hapusAlat(AlatPendakian* alatList, int& count) {
    string nama;
    cout << "Masukkan nama alat yang ingin dihapus: ";
    cin.ignore(); // Mengabaikan newline yang tersisa
    getline(cin, nama); // Menggunakan getline

    for (int i = 0; i < count; i++) {
        if (alatList[i].nama == nama) {
            alatList[i] = alatList[count - 1]; // Pindahkan alat terakhir
            count--;
            cout << "Alat berhasil dihapus!\n";
            return;
        }
    }
    cout << "Alat tidak ditemukan.\n";
}

int main() {
    AlatPendakian alatList[MAX_ALAT];
    int count = 0;
    int pilihan;

    do {
        cout << "\nMenu:\n";
        cout << "1. Tambah Alat\n";
        cout << "2. Tampilkan Alat\n";
        cout << "3. Ubah Alat\n";
        cout << "4. Hapus Alat\n";
        cout << "5. Keluar\n";
        cout << "Pilih pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahAlat(alatList, count);
                break;
            case 2:
                tampilkanAlat(alatList, count);
                break;
            case 3:
                ubahAlat(alatList, count);
                break;
            case 4:
                hapusAlat(alatList, count);
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
