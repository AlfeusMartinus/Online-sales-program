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
int size = sizeof(listProduk) / sizeof(listProduk[0]);

struct transaksi
{
    int noTransaksi;
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
    int tempQty, tempNoTrans;
    cout << "Berapa banyak produk:\t\t";
    cin >> tempQty;
    cout << "Masukan nomor transaksi:\t";
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
void deleteLast(linkedlist *l){
    if(isEmpty(*l))
        cout << "List kosong" << endl;
    else{
        node *tmpNode = l->tail;
        l->tail->prev->next = NULL;
        l->tail = l->tail->prev;
        free(tmpNode);
    }
}

// MENAMPILKAN HISTORY TRANSAKSI
void displayHistory(linkedlist l){
    system("cls");
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

// MENAMPILKAN DAFTAR BARANG
void displayDaftar(){
    system("cls");
    cout << "-------- Daftar Produk --------" << endl;

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

int menuUtama();
// FITUR PEMBELIAN/PENAMBAHAN TRANSAKSI
int pembelian(linkedlist *l){
    int pilih;
    while (1 == 1)
    {
        displayDaftar();
        cout << "No. Barang yang akan dibeli:\t";
        cin >> pilih;
        if (pilih > size)
        {
            cout << "Masukan inputan yang benar" << endl;
            continue;
        }
        else
        {
            char choice;
            insertLast(&keranjang, listProduk, pilih);// Masih ambigu
            // node *current = l->tail->prev;
            // cout << "Nomor Transaksi:" << "\t" << current->Transaksi.noTransaksi << endl
            //     << "Produk:" << "\t\t" << current->Transaksi.namaProduk << endl
            //     << "Jumlah:" << "\t\t" << current->Transaksi.Qty << "\t" << endl
            //     << "Total Harga:" << "\t" << current->Transaksi.totalHarga << endl
            //     << endl;
            while (1 == 1)
            {
                cout << "Apakah pesanan sudah tepat ? (y) Ya  (n) Tidak : ";
                cin >> choice;
                if (choice == 'y' || choice == 'Y')
                {
                    cout << "Bayar Sekarang atau Nanti ? (y) Sekarang (n) Nanti : ";
                    cin >> choice;
                    if (choice == 'y' || choice == 'Y')
                    {
                        //ini belum
                    }
                }
                else if (choice == 'n' || choice == 'N')
                {
                    //deleteLast(&keranjang); //Masih Error disini outputnya
                    cout << "Kembali ke Menu Utama " << endl;
                    return menuUtama();
                    
                }
            }
            break;
        }
    } 
}

// MENAMPILKAN MENU UTAMA
int menuUtama(){
    while (1 == 1)
    {
        int pilih;
        system("cls");
        cout << "-------- Menu Utama --------" << endl;
        cout << "1. Melihat Daftar Produk" <<endl
             << "2. Pembelian" << endl
             << "3. Melihat Histori Transaksi" << endl
             << "4. Keluar Program " << endl
             << "----------------------------" << endl;
        cout << "Pilih menu: ";
        cin >> pilih;

        switch (pilih)
        {
        case 1:
            displayDaftar();
            system("pause");
            break;
        case 2:
            pembelian(&keranjang);
            system("pause");
            break;
        case 3:
            displayHistory(keranjang);
            system("pause");
            break;
        case 4:
            return 0;
            break;
        default:
            cout << "Masukan inputan yang benar" << endl;
            system("pause");
            break;
        }
    } 
}

int main(){ 
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

    //membuat keranjang kosong
    createEmpty(&keranjang);

    menuUtama();
}   