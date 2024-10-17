#include <iostream>
using namespace std;

struct alatPendakian {
    string idAlat;
    string nama;
    string harga;
    alatPendakian* next;
};

void tambahAlatProses(alatPendakian*& head, string idAlat, string namaAlat, string harga);

void tambahAlat(alatPendakian*& head) {
    string idAlat, namaAlat, harga;
    cin.ignore();
    cout << "Masukkan ID alat pendakian >> ";
    getline(cin, idAlat);
    cout << "Masukkan nama alat pendakian >> ";
    getline(cin, namaAlat);
    cout << "Masukkan harga alat pendakian >> ";
    getline(cin, harga);

    tambahAlatProses(head, idAlat, namaAlat, harga);
}

void tambahAlatProses(alatPendakian*& head, string idAlat, string namaAlat, string harga) {
    alatPendakian* tambahAlat = new alatPendakian();
    tambahAlat->nama = namaAlat;
    tambahAlat->harga = harga;
    tambahAlat->idAlat = idAlat;
    tambahAlat->next = nullptr;

    if (head == nullptr) {
        head = tambahAlat;
    } else {
        alatPendakian* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = tambahAlat;
    }
}

void tampilkanAlat(alatPendakian*& head) {
    if (head == nullptr) {
        cout << "Belum ada data" << endl;
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

void hapusAlat(alatPendakian*& head) {
    if (head == nullptr) {
        cout << "Belum ada data" << endl;
        return;
    }
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }
    alatPendakian* temp = head;
    while (temp->next->next != nullptr) {
        temp = temp->next;
    }
    delete temp->next;
    temp->next = nullptr;
}

void editAlat(alatPendakian*& head) {
    if (head == nullptr) {
        cout << "Belum ada data alat pendakian" << endl;
        return;
    }
    string idAlat;
    tampilkanAlat(head);
    cin.ignore();
    cout << "Masukkan id alat yang akan diubah >> ";
    getline(cin, idAlat);

    alatPendakian* temp = head;
    while (temp != nullptr) {
        if (temp->idAlat == idAlat) {
            cout << "Masukkan nama alat baru >> ";
            getline(cin, temp->nama);
            cout << "Masukkan harga alat baru >> ";
            getline(cin, temp->harga);
            cout << "Berhasil melakukan perubahan data" << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Id alat tidak ditemukan" << endl;
}

alatPendakian* getMiddle(alatPendakian* head) {
    if (head == nullptr) return head;
    alatPendakian* slow = head;
    alatPendakian* fast = head->next;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

alatPendakian* merge(alatPendakian* left, alatPendakian* right) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;

    alatPendakian* result = nullptr;

    if (left->nama <= right->nama) {
        result = left;
        result->next = merge(left->next, right);
    } else {
        result = right;
        result->next = merge(left, right->next);
    }
    return result;
}

alatPendakian* mergeSortAlat(alatPendakian* head) {
    if (head == nullptr || head->next == nullptr) return head;

    alatPendakian* middle = getMiddle(head);
    alatPendakian* nextOfMiddle = middle->next;
    middle->next = nullptr;

    alatPendakian* left = mergeSortAlat(head);
    alatPendakian* right = mergeSortAlat(nextOfMiddle);

    alatPendakian* sortedList = merge(left, right);

    return sortedList;
}

void mergeSort(alatPendakian*& head) {
    if (head == nullptr) {
        cout << "Belum ada data untuk diurutkan" << endl;
        return;
    }
    head = mergeSortAlat(head);
    tampilkanAlat(head);
}

alatPendakian* getTail(alatPendakian* cur) {
    while (cur != nullptr && cur->next != nullptr) {
        cur = cur->next;
    }
    return cur;
}

alatPendakian* partition(alatPendakian* head, alatPendakian* end, alatPendakian*& newHead, alatPendakian*& newEnd) {
    alatPendakian* pivot = end;
    alatPendakian* prev = nullptr, * cur = head, * tail = pivot;

    while (cur != pivot) {
        // Compare nama secara descending
        if (cur->nama > pivot->nama) {
            if (newHead == nullptr) {
                newHead = cur;
            }
            prev = cur;
            cur = cur->next;
        } else {
            if (prev != nullptr) {
                prev->next = cur->next;
            }
            alatPendakian* temp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = temp;
        }
    }

    if (newHead == nullptr) {
        newHead = pivot;
    }
    newEnd = tail;

    return pivot;
}

alatPendakian* quickSortRecur(alatPendakian* head, alatPendakian* end) {
    if (!head || head == end) {
        return head;
    }

    alatPendakian* newHead = nullptr, * newEnd = nullptr;

    alatPendakian* pivot = partition(head, end, newHead, newEnd);

    if (newHead != pivot) {
        alatPendakian* temp = newHead;
        while (temp->next != pivot) {
            temp = temp->next;
        }
        temp->next = nullptr;

        newHead = quickSortRecur(newHead, temp);
        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);

    return newHead;
}

void quickSort(alatPendakian*& head) {
    if (head == nullptr) {
        cout << "Belum ada data untuk diurutkan" << endl;
        return;
    }
    head = quickSortRecur(head, getTail(head));
    tampilkanAlat(head);
}

void menu(alatPendakian*& head) {
    string pilih, ulang = "y";
    while (ulang == "y") {
        cout << "[1] Tambah alat pendakian \n"
            "[2] Hapus alat pendakian\n"
            "[3] Edit alat pendakian\n"
            "[4] Tampilkan secara descending\n"
            "[5] Tampilkan secara ascending\n"
            "[6] Keluar\n";
        cout << "Masukkan pilihan >> ";
        cin >> pilih;
        if (pilih == "1") {
            tambahAlat(head);
        } else if (pilih == "2") {
            hapusAlat(head);
        } else if (pilih == "3") {
            editAlat(head);
        } else if (pilih == "4") {
            quickSort(head);
        } else if (pilih == "5") {
            mergeSort(head);
        } else if (pilih == "6") {
            ulang = "t";
        } else {
            cout << "Pilihan tidak ada" << endl;
        }
    }
}

int main(int argc, char const* argv[]) {
    alatPendakian* head = nullptr;

    menu(head);

    return 0;
}
