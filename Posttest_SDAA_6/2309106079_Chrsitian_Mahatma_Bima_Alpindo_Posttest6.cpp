#include <iostream>
#include <vector>
#include <string>
#include <cmath> 
using namespace std;

struct alatPendakian {
    string idAlat;
    string nama;
    string harga;
    alatPendakian* next;
};

void tambahAlatProses(alatPendakian*& head, string idAlat, string namaAlat, string harga);
void tambahAlat(alatPendakian*& head);
void tampilkanAlat(alatPendakian*& head);
void hapusAlat(alatPendakian*& head);
void editAlat(alatPendakian*& head);
alatPendakian* getMiddle(alatPendakian* head);
alatPendakian* merge(alatPendakian* left, alatPendakian* right);
alatPendakian* mergeSortAlat(alatPendakian* head);
void mergeSort(alatPendakian*& head);
alatPendakian* getTail(alatPendakian* cur);
alatPendakian* partition(alatPendakian* head, alatPendakian* end, alatPendakian*& newHead, alatPendakian*& newEnd);
alatPendakian* quickSortRecur(alatPendakian* head, alatPendakian* end);
void quickSort(alatPendakian*& head);
void menu(alatPendakian*& head);

vector<int> buildBadCharTable(const string& pattern) {
    const int ALPHABET_SIZE = 256; // Extended ASCII
    vector<int> badCharTable(ALPHABET_SIZE, -1);

    for (int i = 0; i < pattern.size(); ++i) {
        badCharTable[static_cast<unsigned char>(pattern[i])] = i;
    }

    return badCharTable;
}

void boyerMooreSearch(alatPendakian* head, const string& pattern) {
    vector<int> badCharTable = buildBadCharTable(pattern);
    int patternLength = pattern.size();
    alatPendakian* current = head;

    while (current != nullptr) {
        int textLength = current->nama.size();
        int s = 0;

        while (s <= textLength - patternLength) {
            int j = patternLength - 1;

            while (j >= 0 && pattern[j] == current->nama[s + j]) {
                j--;
            }

            if (j < 0) {
                cout << "Nama alat yang ditemukan: " << current->nama << endl;
                cout << "ID alat: " << current->idAlat << endl;
                cout << "Harga: " << current->harga << endl << endl;
                s += (s + patternLength < textLength) ? patternLength - badCharTable[static_cast<unsigned char>(current->nama[s + patternLength])] : 1;
            } else {
                s += max(1, j - badCharTable[static_cast<unsigned char>(current->nama[s + j])]);
            }
        }
        current = current->next;
    }
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
    head = quickSortRecur(head, getTail(head));
    tampilkanAlat(head);
}

void jumpSearchHarga(alatPendakian* head, string hargaDicari) {
    if (head == nullptr) {
        cout << "Tidak ada data." << endl;
        return;
    }

    int n = 0;
    alatPendakian* temp = head;

    while (temp != nullptr) {
        n++;
        temp = temp->next;
    }

    int step = sqrt(n);  
    int prev = 0;
    temp = head;

    alatPendakian* jumpNode = head;
    for (int i = 0; i < step && jumpNode != nullptr; i++) {
        jumpNode = jumpNode->next;
    }

    while (jumpNode != nullptr && jumpNode->harga <= hargaDicari) {
        prev += step;
        temp = jumpNode;
        for (int i = 0; i < step && jumpNode != nullptr; i++) {
            jumpNode = jumpNode->next;
        }
    }

    while (temp != nullptr && prev < n && temp->harga < hargaDicari) {
        temp = temp->next;
        prev++;
    }

    if (temp != nullptr && temp->harga == hargaDicari) {
        cout << "Alat dengan harga " << hargaDicari << " ditemukan." << endl;
        cout << "ID alat: " << temp->idAlat << endl;
        cout << "Nama alat: " << temp->nama << endl;
        cout << "Harga: " << temp->harga << endl;
    } else {
        cout << "Alat dengan harga " << hargaDicari << " tidak ditemukan." << endl;
    }
}

int min(int x, int y) {
    return (x <= y) ? x : y;
}

void fibonacciSearchID(alatPendakian* head, string idDicari) {
    if (head == nullptr) {
        cout << "Tidak ada data." << endl;
        return;
    }

    vector<alatPendakian*> alatArray;
    alatPendakian* temp = head;
    while (temp != nullptr) {
        alatArray.push_back(temp);
        temp = temp->next;
    }

    int n = alatArray.size();

    int fibMMm2 = 0;  
    int fibMMm1 = 1;  
    int fibM = fibMMm2 + fibMMm1;   


    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;

    while (fibM > 1) {
        int i = min(offset + fibMMm2, n - 1);

        if (alatArray[i]->idAlat < idDicari) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        } else if (alatArray[i]->idAlat > idDicari) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        } else {
            cout << "Alat dengan ID " << idDicari << " ditemukan." << endl;
            cout << "ID alat: " << alatArray[i]->idAlat << endl;
            cout << "Nama alat: " << alatArray[i]->nama << endl;
            cout << "Harga: " << alatArray[i]->harga << endl;
            return;
        }
    }

    if (fibMMm1 && alatArray[offset + 1]->idAlat == idDicari) {
        cout << "Alat dengan ID " << idDicari << " ditemukan." << endl;
        cout << "ID alat: " << alatArray[offset + 1]->idAlat << endl;
        cout << "Nama alat: " << alatArray[offset + 1]->nama << endl;
        cout << "Harga: " << alatArray[offset + 1]->harga << endl;
    } else {
        cout << "Alat dengan ID " << idDicari << " tidak ditemukan." << endl;
    }
}

void menu(alatPendakian*& head) {
    string pilih, ulang = "y";
    while (ulang == "y") {
        cout << 
        "======================\n"
        "|    Menu Alat       |\n"
        "======================\n"
        "[1] Tambah alat pendakian \n"
             "[2] Hapus alat pendakian\n"
             "[3] Edit alat pendakian\n"
             "[4] Tampilkan secara descending\n"
             "[5] Tampilkan secara ascending\n"
             "[6] Cari alat pendakian (Boyer-Moore)\n"
             "[7] Cari harga menggunakan (Jump Search)\n"
             "[8] Cari ID menggunakan (Fibonacci Search)\n"
             "[9] Keluar\n";
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
            string pattern;
            cin.ignore();
            cout << "Masukkan nama alat yang dicari >> ";
            getline(cin, pattern);
            boyerMooreSearch(head, pattern);
        } else if (pilih == "7") {
            string hargaDicari;
            cin.ignore();
            cout << "Masukkan harga yang dicari >> ";
            getline(cin, hargaDicari);
            jumpSearchHarga(head, hargaDicari);
        } else if (pilih == "8") {
            string idDicari;
            cin.ignore();
            cout << "Masukkan ID yang dicari >> ";
            getline(cin, idDicari);
            fibonacciSearchID(head, idDicari);
        } else if (pilih == "9") {
            ulang = "t";
        } else {
            cout << "Pilihan tidak ada" << endl;
        }
    }
}

int main() {
    alatPendakian* head = nullptr;
    menu(head);
    return 0;
}
