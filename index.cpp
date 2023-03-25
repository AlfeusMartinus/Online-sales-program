#include <iostream>
#include <string> // untuk kebutuhan registrasi & login
#include <fstream> // untuk kebutuhan registrasi & login
using namespace std;

// PENGGUNAAN STRUCT
struct produk
{
    string nama;
    string deskripsi;
    double harga;
    int stok;
};

produk listProduk[] = {
    {"Hoodie Naruto", "xxxxxxxxxxxxxx", 50000, 32}, {"Kaos Mixue", "xxxxxxxxxxxxxx", 72340, 20}};

struct transaksi
{
    int no_transaksi;
    int jumlah;
    double total_harga;
    bool status_pembayaran;
};


// PENGGUNAAN VOID UNTUK REGISTER
void registrasi() {
    string username, pass;
    cout << "Username\t:"; cin >> username;
    cout << "Password\t:"; cin >> pass;

    ofstream userFile("dataUser.txt", ios::app);
    if (userFile.is_open())
    {
        userFile << username << " " << pass << endl;
        userFile.close();
        cout << "Registrasi Berhasil" << endl;
    }
    else 
    {
        cout << "Something Went Wrong!" << endl;
    }
}

// PENGGUNAAN VOID UNTUK LOGIN 
void login() {
    string username, pass, line;
    bool check = false;
    cout << "Username\t:"; cin >> username;
    cout << "Password\t;"; cin >> pass;

    ifstream userFile("dataUser.txt");
    if (userFile.is_open())
    {
        while (getline(userFile, line))
        {
            size_t pos = line.find(" ");
            string u = line.substr(0, pos);
            string p = line.substr(pos+1);
            if (u == username && p == pass)
            {
                check = true;
                break;
            }
            
        }
        userFile.close();
        if (check)
        {
            cout << "Login Berhasil" << endl;
        }
        else 
        {
            cout << "Username / Password salah" << endl;
        }
        
    }
    else
    {
        cout << "Something Went Wrong!" << endl;
    }
    
}

int main(){ 
    int size = sizeof(listProduk) / sizeof(listProduk[0]);
    int pilih;

    cout << "Silahkan Login / Register Terlebih dulu\n" << "1. Login\n" << "2. Register\n" ; cin >> pilih; 
    if (pilih == 1)
    {
        login();
    }
    else if (pilih == 2)
    {
        registrasi();
    }
    else {
        cout << "Masukan inputan yang benar" << endl;
    }

    cout << "Daftar Produk" << endl;

    for (int i = 0; i < size; i++)
    {
        produk *pProduk = &listProduk[i]; // pointer untuk mengakses struct produk
        cout << i + 1 << ". " << pProduk->nama << endl
             << "   Deskripsi \t\t:" << pProduk->deskripsi << endl
             << "   Harga \t\t:" << pProduk->harga << endl
             << "   Stok \t\t:" << pProduk->stok << endl
             << endl;
    }

}