#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

struct Makanan {
    string nama;
    int harga;
};

struct Pesanan {
    string nama;
    int harga;
    int jumlah;
    int subtotal;
};

Makanan menu[] = {
    {"Nasi Goreng", 12000},
    {"Mie Ayam", 13000},
    {"Bakso", 15000},
    {"Sate Ayam", 17000},
    {"Ayam Goreng", 18000}
};

int jumlahMenu = 5;

// ===== UTIL =====
void border() {
    cout << "========================================\n";
}

string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// ===== LOGIN =====
bool login() {
    string user, pass;

    cout << "\n=== LOGIN ===\n";
    cout << "Username : "; cin >> user;
    cout << "Password : "; cin >> pass;

    // Multi user sederhana
    if ((user == "Ali" && pass == "123") ||
        (user == "Afzal" && pass == "111")) {
        return true;
    }
    return false;
}

// ===== MENU =====
void tampilMenu() {
    border();
    cout << "          MENU MAKANAN\n";
    border();
    for (int i = 0; i < jumlahMenu; i++) {
        cout << i + 1 << ". " << menu[i].nama
             << " - Rp" << menu[i].harga << endl;
    }
    border();
}

// ===== SEARCH =====
int cariMenu(string nama) {
    string input = toLower(nama);

    for (int i = 0; i < jumlahMenu; i++) {
        string data = toLower(menu[i].nama);
        if (data.find(input) != string::npos) {
            return i;
        }
    }
    return -1;
}

// ===== MAIN =====
int main() {
    border();
    cout << "          APLIKASI PESAN MAKANAN\n";
    border();

    if (!login()) {
        cout << "Login gagal!\n";
        return 0;
    }

    cout << "Login berhasil!\n";

    Pesanan keranjang[100];
    int jumlahPesanan = 0;
    int pilihan;

    do {
        tampilMenu();

        cout << "\n1. Cari Menu";
        cout << "\n2. Tambah Pesanan";
        cout << "\n3. Lihat Keranjang";
        cout << "\n4. Bayar";
        cout << "\n5. Keluar";
        cout << "\nPilih : ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            string cari;
            cout << "Cari makanan: ";
            getline(cin, cari);

            int hasil = cariMenu(cari);
            if (hasil != -1) {
                cout << "Ditemukan: " << menu[hasil].nama
                     << " - Rp" << menu[hasil].harga << endl;
            } else {
                cout << "Tidak ditemukan!\n";
            }

        } else if (pilihan == 2) {
            int nomor, jumlah;
            cout << "Pilih nomor: ";
            cin >> nomor;

            if (nomor > 0 && nomor <= jumlahMenu) {
                cout << "Jumlah: ";
                cin >> jumlah;

                keranjang[jumlahPesanan].nama = menu[nomor - 1].nama;
                keranjang[jumlahPesanan].harga = menu[nomor - 1].harga;
                keranjang[jumlahPesanan].jumlah = jumlah;
                keranjang[jumlahPesanan].subtotal =
                    menu[nomor - 1].harga * jumlah;

                jumlahPesanan++;

                cout << "Ditambahkan!\n";
            } else {
                cout << "Menu tidak valid!\n";
            }

        } else if (pilihan == 3) {
            border();
            cout << "        KERANJANG\n";
            border();

            int total = 0;

            for (int i = 0; i < jumlahPesanan; i++) {
                cout << keranjang[i].nama << " x"
                     << keranjang[i].jumlah
                     << " = Rp" << keranjang[i].subtotal << endl;
                total += keranjang[i].subtotal;
            }

            cout << "Total: Rp" << total << endl;
            border();

        } else if (pilihan == 4) {
            ofstream file("struk.txt");

            int total = 0;

            border();
            cout << "         STRUK BELANJA\n";
            border();

            file << "STRUK BELANJA\n";

            for (int i = 0; i < jumlahPesanan; i++) {
                cout << keranjang[i].nama << " x"
                     << keranjang[i].jumlah
                     << " = Rp" << keranjang[i].subtotal << endl;

                file << keranjang[i].nama << " x"
                     << keranjang[i].jumlah
                     << " = Rp" << keranjang[i].subtotal << endl;

                total += keranjang[i].subtotal;
            }

            cout << "Total: Rp" << total << endl;
            file << "Total: Rp" << total << endl;

            int bayar;
            cout << "Bayar: ";
            cin >> bayar;

            if (bayar >= total) {
                cout << "Kembalian: Rp" << bayar - total << endl;
                cout << "Pembayaran sukses!\n";
                file << "Kembalian: Rp" << bayar - total << endl;
            } else {
                cout << "Uang kurang!\n";
            }

            file.close();
            border();
        }

    } while (pilihan != 5);

    cout << "Terima kasih sudah berbelanja!\n";
    return 0;
}