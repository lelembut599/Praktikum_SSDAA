#include <iostream>

using namespace std;

void Hanoi(int jumlahLapisan, char MenaraAsal, char MenaraTujuan, char MenaraSementara) {
    if (jumlahLapisan == 1) {
        cout << "Pindahkan Lapisan " << jumlahLapisan << " dari " << MenaraAsal << " ke " << MenaraTujuan << endl;
    } else {
        Hanoi(jumlahLapisan - 1, MenaraAsal, MenaraSementara, MenaraTujuan);
        cout << "Pindahkan Lapisan " << jumlahLapisan << " dari " << MenaraAsal << " ke " << MenaraTujuan << endl;
        Hanoi(jumlahLapisan - 1, MenaraSementara, MenaraTujuan, MenaraAsal);
    }
}

int main() {
    int jumlahLapisan;
    cout << "Masukkan Jumlah Lapisan Yang Anda Inginkan: ";
    cin >> jumlahLapisan;

    cout << "\nLangkah-Langkah: ";
    Hanoi(jumlahLapisan, 'A', 'C', 'B');
    cout << "\nKeterangan : \n A = Menara Asal \n B = Menara Sementara \n C = Menara Tujuan";
    return 0;
}
