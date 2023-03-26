#include <iostream>
#include <string> // untuk kebutuhan registrasi & login
#include <fstream> // untuk kebutuhan registrasi & login
#include <cstdlib> // untuk fungsi exit
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

// GLOBAL VARIABEL
int length = sizeof(listProduk) / sizeof(listProduk[0]);


struct transaksi
{
    string noTransaksi;
    string namaProduk;
    int Qty;
    double totalHarga;
    string statusPembayaran;
};

struct node
{
    transaksi Transaksi;
    node *next;
    node *prev;
};

struct linkedlist
{
    node *head;
    node *tail;
};
linkedlist keranjang;

// MEMBUAT LIST KOSONG
void createEmpty(linkedlist *l){
    l->head = NULL;
    l->tail = NULL;
}

// CEK STATUS LIST
bool isEmpty(linkedlist l)
{
    if (l.head == NULL)
    {
        return true;
    }
    return false;
}

// MENAMBAHKAN TRANSAKSI
void insertLast(linkedlist *l, produk listProduk[], int x){
    int tempQty;
    string tempNoTrans, choice;
    cout << "Berapa banyak produk\t\t: ";
    cin >> tempQty;
    cout << "Masukan nomor transaksi\t\t: ";
    cin >> tempNoTrans;


    node *new_node, *current;
    new_node = new node;
    new_node->Transaksi.noTransaksi = tempNoTrans;
    new_node->Transaksi.namaProduk = listProduk[x-1].nama;
    new_node->Transaksi.Qty = tempQty;
    new_node->Transaksi.totalHarga = tempQty * listProduk[x-1].harga;
    new_node->next = NULL;

    if (isEmpty(keranjang))
    {
        l->head = new_node;
        l->head->next = NULL;
    }
    else
    {
        current = l->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }
}

// MENGHAPUS TRANSAKSI TERAKHIR
void removeLast(linkedlist *l) {
    if (l->head == nullptr) {
        cout << "List kosong" << endl;
        system("pause");
        return;
    }
    else if (l->head->next == nullptr) {
        delete l->head;
        l->head = nullptr;
    }
    else {
        node *temp = nullptr;
        node *current = l->head;
        while (current->next != nullptr) {
            temp = current;
            current = current->next;
        }
        temp->next = nullptr;
        delete current;
    }
}

// MENAMPILKAN HISTORY TRANSAKSI
void displayHistory(linkedlist l){
    system("CLS");
    if(isEmpty(l))
        cout << "List kosong" << endl;
    else{
        node *current = l.head;
        while (current != NULL){
            cout << "Nomor Transaksi\t  : " << current->Transaksi.noTransaksi << endl
            << "Produk\t\t  : " << current->Transaksi.namaProduk << endl
            << "Jumlah\t\t  : " << current->Transaksi.Qty << "\t" << endl
            << "Total Harga\t  : " << current->Transaksi.totalHarga << endl
            << "Status Pembayaran : " << current->Transaksi.statusPembayaran << endl
            << endl;
            current = current->next;
        }
        cout << endl;
    }
}

// PENGGUNAAN VOID UNTUK REGISTER
void registrasi() {
    string username, pass;
    cout << "Username\t: "; cin >> username;
    cout << "Password\t: "; cin >> pass;

    ofstream userFile("dataUser.txt", ios::app);
    if (userFile.is_open()){
        userFile << username << " " << pass << endl;
        userFile.close();
        cout << "Registrasi Berhasil" << endl;
    }
    else{
        cout << "Something Went Wrong!" << endl;
    }
}

// PENGGUNAAN VOID UNTUK LOGIN 
bool login() {
    string username, pass, line;
    bool check = false;
    cout << "Username\t: "; cin >> username;
    cout << "Password\t: "; cin >> pass;

    ifstream userFile("dataUser.txt");
    if (userFile.is_open()){
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
        if (check){
            cout << "Login Berhasil" << endl;
        }
        else{
            cout << "Username / Password salah" << endl;
        }
        return check;
    }
    else{
        cout << "Something Went Wrong!" << endl;
    }
    return 0;
}

// MENAMPILKAN DAFTAR BARANG
void displayDaftar(){
    system("cls");
    cout << "------------------- Daftar Produk -------------------" << endl << endl;
    for (int i = 0; i < length; i++)
    {
        produk *pProduk = &listProduk[i]; // pointer untuk mengakses struct produk
        cout << i + 1 << ". " << pProduk->nama << endl
             << "   Deskripsi \t\t:" << pProduk->deskripsi << endl
             << "   Harga \t\t:" << pProduk->harga << endl
             << "   Stok \t\t:" << pProduk->stok << endl
             << endl;
    }
}

int menuUtama();

// FITUR PEMBELIAN/PENAMBAHAN TRANSAKSI
int pembelian(){
    int pilihB;
    while (1 == 1)
    {
        displayDaftar();
        cout << "No. Barang yang akan dibeli\t: ";
        cin >> pilihB;
        if (pilihB > length)
        {
            cout << "Masukan inputan yang benar" << endl;
            continue;
        }
        else
        {
            string choice;
            node *current, *current2;
            insertLast(&keranjang, listProduk, pilihB);
            current = keranjang.head;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current2 = current;
            while (current != NULL){
                cout << endl 
                << "Nomor Transaksi\t  : " << current->Transaksi.noTransaksi << endl
                << "Produk\t\t  : " << current->Transaksi.namaProduk << endl
                << "Jumlah\t\t  : " << current->Transaksi.Qty << "\t" << endl
                << "Total Harga\t  : " << current->Transaksi.totalHarga << endl
                << "Status Pembayaran : " << current->Transaksi.statusPembayaran << endl
                << endl;
                break;
            }
            cout << endl;
            while (1 == 1)
            {
                cout << "Apakah pesanan sudah tepat ? (y) Ya  (n) Tidak : ";
                cin >> choice;
                if (choice == "y" || choice == "Y")
                {
                    cout << "Apakah sudah dibayar? (Y/N) ";
                    cin >> choice;
                    if (choice == "y" || choice == "Y")
                    {
                        current2->Transaksi.statusPembayaran = "Sudah Selesai";
                        return menuUtama();
                    }
                    else if (choice == "n" || choice == "N")
                    {
                        current2->Transaksi.statusPembayaran = "Belum Selesai";
                        return menuUtama();
                    }
                    else
                    {
                       cout << "Masukan inputan yang benar" << endl;
                        continue; 
                    }
                }
                else if (choice == "n" || choice == "N")
                {
                    removeLast(&keranjang);
                    cout << "Kembali ke Menu Utama " << endl;
                    return menuUtama();
                    
                }
                else
                {
                    cout << "Masukan inputan yang benar" << endl;
                    continue;
                }
            }
            break;
        }
    } 
}

int Pembayaran()
{
    while (1 == 1)
    {
        system("CLS");
        int subMenu;
        cout << "------- MENU PEMBAYARAN -------" << endl << endl;
        cout << "1. Tampilkan History Pembayaran" << endl;
        cout << "2. Bayar Transaksi" << endl;
        cout << "3. Kembali ke Menu Utama" << endl;
        cout << "Pilihan Anda: ";
        cin >> subMenu;
        switch (subMenu) {
            case 1:
                displayHistory(keranjang);
                system("pause");
                break;
            case 2:
                if (isEmpty(keranjang)) 
                {
                    cout << "Tidak ada transaksi yang harus dibayar." << endl;
                }
                else if (!isEmpty(keranjang))
                {
                    string search;
                    node *current, *current2;
                    cout << "Masukan No. Transaksi  : ";
                    cin >> search;
                    
                    current = keranjang.head;
                    while (current->Transaksi.noTransaksi != search)
                    {
                        if (current == keranjang.tail)
                        {
                            break;
                        }
                        else
                        {
                            current = current->next;
                        }
                    }
                    current2 = current;
                    while (current->next != NULL){
                        cout << endl 
                        << "Nomor Transaksi\t  : " << current->Transaksi.noTransaksi << endl
                        << "Produk\t\t  : " << current->Transaksi.namaProduk << endl
                        << "Jumlah\t\t  : " << current->Transaksi.Qty << endl
                        << "Total Harga\t  : " << current->Transaksi.totalHarga << endl
                        << "Status Pembayaran : " << current->Transaksi.statusPembayaran << endl
                        << endl;
                        break;
                    }
                    cout << endl;
                    if (current2 == keranjang.tail && current2->Transaksi.noTransaksi != search)
                    {
                        cout << "No. Transaksi tidak terdaftar" << endl;
                    }
                    else if (current2->Transaksi.statusPembayaran == "Sudah Selesai")
                    {
                        cout << "Transaksi dengan nomor " << current2->Transaksi.noTransaksi << " Sudah Selesai, Tidak Perlu Dibayar" << endl;
                    }
                    else if (current2->Transaksi.statusPembayaran == "Belum Selesai")
                    {
                        current2->Transaksi.statusPembayaran = "Sudah Selesai";    
                        cout << "Transaksi dengan nomor " << current2->Transaksi.noTransaksi << " telah dibayar." << endl;
                    }
                }
                system("pause");
                break;
            case 3:
                menuUtama();
                break;
            default:
                cout << "Masukan inputan yang benar" << endl;
                system("pause");
                break;
        }
    }
}

// MENAMPILKAN MENU UTAMA
int menuUtama(){
    bool exitloop = false;
    while (!exitloop)
    {
        int pilihM;
        system("cls");
        cout << "-------- Menu Utama --------  " << endl << endl;
        cout << "[1] Melihat Daftar Produk     " << endl
             << "[2] Pembelian                 " << endl
             << "[3] Melihat Histori Transaksi " << endl
             << "[4] Pembayaran                " << endl
             << "[5] Keluar Program            " << endl
             << "----------------------------  " << endl << endl;
        cout << "Pilih menu: ";
        cin >> pilihM;

        switch (pilihM)
        {
        case 1:
            displayDaftar();
            system("pause");
            break;
        case 2:
            pembelian();
            system("pause");
            break;
        case 3:
            displayHistory(keranjang);
            system("pause");
            break;
        case 4:
            Pembayaran();
            system("pause");
            break;
        case 5: 
            exitloop = true;
            cout << "Menutup Program . . . ." << endl;
            exit(0);
        default:
            cout << "Masukan inputan yang benar" << endl;
            system("pause");
            break;
        }
    } 
    return 0;
}

int main(){ 
    int pilih;
    bool valid;

    while (1 == 1)
    {
        system("cls");
        cout << "LOGIN / REGISTER" << endl << endl;
        cout << "[1] LOGIN" << endl;
        cout << "[2] REGISTRASI" << endl << endl;
        cout << "Masukkan angka\t: "; cin >> pilih; 
        system ("CLS");
        if (pilih == 1)
        {
            valid = login();
            if (valid)
            {
                break;
            }
            else
            {   
                system("pause");
                continue;
            }
        }
        else if (pilih == 2)
        {
            registrasi();
            system("pause");
            continue;;
        }
        else {
            cout << "Masukan inputan yang benar" << endl;
            system("pause");
            continue;
        }
    }

    system("pause");

    // MEMBUAT KERANJANG KOSONG
    createEmpty(&keranjang);
    menuUtama();
    return 0;
}   