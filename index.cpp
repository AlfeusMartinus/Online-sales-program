#include <iostream>
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
    {"Hoodie Naruto", "xxxxxxxxxxxxxx", 50000, 32}, {"Kaos Mixue", "xxxxxxxxxxxxxx", 72340, 20}
};

struct transaksi
{
    int no_transaksi;
    int jumlah;
    double total_harga;
    bool status_pembayaran;
};


int main (){
    int size = sizeof(listProduk)/sizeof(listProduk[0]);

    cout << "Daftar Produk" << endl;

    for (int i = 0; i < size; i++)
    {
        cout << i+1 << ". " << listProduk[i].nama << endl << "   Deskripsi \t\t:" << listProduk[i].deskripsi << endl << "   Harga \t\t:" << listProduk[i].harga << endl << "   Stok \t\t:" << listProduk[i].stok << endl << endl; 
    }

    

}