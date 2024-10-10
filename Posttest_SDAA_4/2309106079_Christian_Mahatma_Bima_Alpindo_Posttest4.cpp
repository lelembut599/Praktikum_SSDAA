#include <iostream>

using namespace std;

struct alatPendakian {
    string idAlat;
    string nama;
    string harga;
    alatPendakian* next;
};

void enqueue(alatPendakian*& head, alatPendakian*& tail, string idAlat, string namaAlat, string harga);
void tampilkanAlat(alatPendakian*& head);
void editAlat(alatPendakian*& head);

void tambahAlatQueue(alatPendakian*& head, alatPendakian*& tail) {
    string idAlat, namaAlat, harga;
    cin.ignore();
    cout << "Masukkan ID alat pendakian >> ";
    getline(cin, idAlat);
    cout << "Masukkan nama alat pendakian >> ";
    getline(cin, namaAlat);
    cout << "Masukkan harga alat pendakian >> ";
    getline(cin, harga);

    enqueue(head, tail, idAlat, namaAlat, harga);
}

void enqueue(alatPendakian*& head, alatPendakian*& tail, string idAlat, string namaAlat, string harga) {
    alatPendakian* tambahAlat = new alatPendakian();
    tambahAlat->nama = namaAlat;
    tambahAlat->harga = harga;
    tambahAlat->idAlat = idAlat;
    tambahAlat->next = nullptr;

    if (head == nullptr) {
        head = tambahAlat;
        tail = tambahAlat; 
    } else {
        tail->next = tambahAlat;
        tail = tambahAlat; 
    }
}

void dequeue(alatPendakian*& head, alatPendakian*& tail) {
    if (head == nullptr) {
        cout << "Belum ada data" << endl;
        return;
    }
    alatPendakian* temp = head;
    head = head->next;
    if (head == nullptr) {
        tail = nullptr; 
    }
    delete temp;
    cout << "Alat pendakian pertama berhasil dihapus dari queue" << endl;
}

void menuQueue(alatPendakian*& head, alatPendakian*& tail) {
    string pilih, ulang = "y";
    while (ulang == "y") {
        cout << "[1] Tambah alat pendakian\n"
             << "[2] Lihat alat pendakian \n"
             << "[3] Hapus alat pendakian\n"
             << "[4] Edit alat pendakian\n"
             << "[5] Keluar\n";
        cout << "Masukkan pilihan >> ";
        cin >> pilih;
        if (pilih == "1") {
            tambahAlatQueue(head, tail);
        } else if(pilih == "2") {
            tampilkanAlat(head);
        } else if(pilih == "3") {
            dequeue(head, tail);
        } else if (pilih == "4") {
            editAlat(head);
        } else if (pilih == "5") {
            ulang = "t";
        } else {
            cout << "Pilihan tidak ada" << endl;
        }
    }
}

// Stack
void push(alatPendakian*& head, string idAlat, string namaAlat, string harga) {
    alatPendakian* newAlat = new alatPendakian();
    newAlat->idAlat = idAlat;
    newAlat->nama = namaAlat;
    newAlat->harga = harga;
    newAlat->next = head; 
    head = newAlat; 
}

void tampilkanAlat(alatPendakian*& head) {
    if (head == nullptr) {
        cout << "Stack kosong!" << endl;
        return;
    }
    alatPendakian* temp = head;
    while (temp != nullptr) {
        cout << "Id alat: " << temp->idAlat << endl;
        cout << "Nama alat: " << temp->nama << endl;
        cout << "Harga (Rp): " << temp->harga << endl;
        cout << endl;
        temp = temp->next;
    }
}

void pop(alatPendakian*& head) {
    if (head == nullptr) {
        cout << "Stack kosong, tidak ada yang bisa di-pop!" << endl;
        return;
    }
    alatPendakian* temp = head;
    head = head->next; 
    delete temp; 
    cout << "Alat pendakian paling atas telah dihapus" << endl;
}

void tambahAlat(alatPendakian*& head) {
    string idAlat, namaAlat, harga;
    cin.ignore();
    cout << "Masukkan ID alat pendakian >> ";
    getline(cin, idAlat);
    cout << "Masukkan nama alat pendakian >> ";
    getline(cin, namaAlat);
    cout << "Masukkan harga alat pendakian >> ";
    getline(cin, harga);
    push(head, idAlat, namaAlat, harga);
}

void editAlat(alatPendakian*& head) {
    if (head == nullptr) {
        cout << "Belum ada data alat pendakian" << endl;
        return;
    }
    string idAlat;
    tampilkanAlat(head);
    cin.ignore();
    cout << "Masukkan id alat pendakian yang akan diubah >> ";
    getline(cin, idAlat);

    alatPendakian* temp = head;
    while(temp != nullptr) {
        if (temp->idAlat == idAlat) {
            cout << "Masukkan nama alat pendakian baru >> ";
            getline(cin, temp->nama);
            cout << "Masukkan harga alat pendakian baru >> ";
            getline(cin, temp->harga);
            cout << "Berhasil melakukan perubahan data" << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Id alat pendakian tidak ditemukan" << endl;
}

void menu(alatPendakian*& head) {
    string pilih, ulang = "y";
    while (ulang == "y") {
        cout << "[1] Tambah alat pendakian \n"
        "[2] Lihat alat pendakian\n"
        "[3] Hapus alat pendakian\n"
        "[4] Edit alat pendakian\n"
        "[5] Keluar\n";
        cout << "Masukkan pilihan >> ";
        cin >> pilih;
        if (pilih == "1") {
            tambahAlat(head);
        } else if(pilih == "2") {
            tampilkanAlat(head);
        } else if(pilih == "3") {
            pop(head);
        } else if (pilih == "4") {
            editAlat(head);
        } else if (pilih == "5") {
            ulang = "t";
        } else {
            cout << "Pilihan tidak ada" << endl;
        }  
    }
}

int main(int argc, char const* argv[]) {
    string pilih;

    cout << "1. Stack\n"
    "2. Queue\n";
    cout << "Masukkan pilihan >>";
    cin >> pilih;
    if(pilih == "1") {
        alatPendakian* head = nullptr;
        menu(head);
    } else if(pilih == "2") {
        alatPendakian* head = nullptr;
        alatPendakian* tail = nullptr;
        menuQueue(head, tail);
    } else {
        cout << "Pilihan tidak ada" << endl;
    }

    return 0;
}
