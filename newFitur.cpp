#include <iostream>
#include <iomanip> // untuk menggunakan manipulasi setw dan setfill
#include <string> // untuk kebutuhan registrasi & login
#include <fstream> // untuk kebutuhan registrasi & login
#include <cstdlib> // untuk fungsi exit
#include <conio.h> // untuk getch password
#include <ctime> // untuk waktu
#include <limits> // try catch
#include <windows.h>
using namespace std;

// PENGGUNAAN STRUCT
struct produk
{
    string nama;
    string deskripsi;
    long long int harga;
    int stok;
    int id;
    string kategori;
    string vAccount;
};

struct tree
{
    produk data;
    tree *left, *right;
};
tree *pohon, *root;

struct transaksi
{
    string noTransaksi;
    string namaProduk;
    int Qty;
    long long int totalHarga;
    string statusPembayaran;
    string VAccount;
};

struct node
{
    transaksi Transaksi;
    node *next;
};

struct linkedlist
{
    node *head;
    node *tail;
};
linkedlist keranjang;

produk listProduk[] = {
    {"HOODIE AHHA", "HOODIE DENGAN BERBAGAI UKURAN DARI MINIMAL HINGGA MAKSIMAL", 455000, 50, 101, "Pakaian", "733199926"},
    {"KAOS IBU HAMIL", "KAOS DENGAN UKURAN S SAJA", 95000, 3, 102, "Pakaian", "874924108"},
    {"JAKET ZIPPER", "JAKET BISA DI PAKAI FORMAL MAUPUN CASUAL (SANTAI ABIS)", 300500, 36, 103, "Pakaian", "585987722"},
    {"ASUS TUF GAMING", "LAPTOP BISA DIPAKAI UNTUK NGODING C++", 15222000, 11, 201, "Elektronik", "761725523"},
    {"GALAXY Z FOLD4", "HP SAMSUNG LIPAT CANGGIH UNTUK ANDA", 7999000, 5, 202, "Elektronik", "526377389"},
    {"LG SMART TV 32", "TV CERDAS LEBIH CERDAS DARI ANDA", 1250000, 7, 203, "Elektronik", "640773823"},
    {"BASRENG PEDAS", "BASRENG SEUHAH DENGAN DAUN JERUK", 25000, 15, 301, "Makanan", "388138333"},
    {"EAT SAMBEL", "SAMBEL TIKTOKERS YANG ENAK", 35500, 100, 302, "Makanan", "457290336"},
    {"ROTI AOKA", "ROTI BUKAN SEKEDAR ROTI, TAPI ROTI ENAK", 2500, 29, 303, "Makanan", "982288709"}};

// GLOBAL VARIABEL
int length = sizeof(listProduk) / sizeof(listProduk[0]);

int menuUtama();

int tryCatch(string input)
{
    int nama;
    try
    {
        nama = stoi(input);
    }
    catch (const std::exception &e)
    {
        cout << "Inputan tidak valid" << endl;
        system("pause");
        menuUtama();
    }
    return nama;
}

void deklarasi()
{
    pohon = NULL;
};

void inputTree(tree **root, string nama, string deskripsi, double harga, int stok, int id, string kategori, string vAccount)
{
    tree *newnode;
    if ((*root) == NULL)
    {
        newnode = new tree;
        newnode->data.nama = nama;
        newnode->data.deskripsi = deskripsi;
        newnode->data.harga = harga;
        newnode->data.stok = stok;
        newnode->data.id = id;
        newnode->data.kategori = kategori;
        newnode->data.vAccount = vAccount;
        newnode->left = newnode->right = NULL;

        (*root) = newnode;
        (*root)->data.id = id;
        (*root)->left = (*root)->right = NULL;
    }
    else if (id < (*root)->data.id)
    {
        inputTree(&(*root)->left, nama, deskripsi, harga, stok, id, kategori, vAccount);
    }
    else
    {
        inputTree(&(*root)->right, nama, deskripsi, harga, stok, id, kategori, vAccount);
    }
};

void listingProduk()
{
    deklarasi();
    inputTree(&pohon, "", "", 0, 0, 270, "Main", "");
    inputTree(&pohon, "", "", 0, 0, 150, "Group 1", "");
    inputTree(&pohon, "", "", 0, 0, 100, "Pakaian", "");
    inputTree(&pohon, "HOODIE AHHA", "HOODIE DENGAN BERBAGAI UKURAN DARI MINIMAL HINGGA MAKSIMAL", 455000, 50, 101, "Pakaian", "733199926");
    inputTree(&pohon, "KAOS IBU HAMIL", "KAOS DENGAN UKURAN S SAJA", 95000, 3, 102, "Pakaian", "874924108");
    inputTree(&pohon, "JAKET ZIPPER", "JAKET BISA DI PAKAI FORMAL MAUPUN CASUAL (SANTAI ABIS)", 300500, 36, 103, "Pakaian", "585987722");
    inputTree(&pohon, "", "", 0, 0, 200, "Elektronik", "");
    inputTree(&pohon, "ASUS TUF GAMING", "LAPTOP BISA DIPAKAI UNTUK NGODING C++", 15222000, 11, 201, "Elektronik", "761725523");
    inputTree(&pohon, "GALAXY Z FOLD4", "HP SAMSUNG LIPAT CANGGIH UNTUK ANDA", 7999000, 5, 202, "Elektronik", "526377389");
    inputTree(&pohon, "LG SMART TV 32", "TV CERDAS LEBIH CERDAS DARI ANDA", 1250000, 7, 203, "Elektronik", "640773823");
    inputTree(&pohon, "", "", 0, 0, 350, "Group 2", "");
    inputTree(&pohon, "", "", 0, 0, 300, "Makanan", "");
    inputTree(&pohon, "BASRENG PEDAS", "BASRENG SEUHAH DENGAN DAUN JERUK", 25000, 15, 301, "Makanan", "388138333");
    inputTree(&pohon, "EAT SAMBEL", "SAMBEL TIKTOKERS YANG ENAK", 35500, 100, 302, "Makanan", "457290336");
    inputTree(&pohon, "ROTI AOKA", "ROTI BUKAN SEKEDAR ROTI, TAPI ROTI ENAK", 2500, 29, 303, "Makanan", "982288709");
};

void printDaftar (tree *root, int parentId, int rekursiCount, int counter)
{
    rekursiCount++;
    if (rekursiCount == 1)
    {
        if (root != NULL)
        {
            int colWidths[] = {3, 15, 70, 15, 5, 9};

            cout << setfill('-');
            for (int i = 0; i < 6; i++)
            {
                cout << "+" << setw(colWidths[i]) << "-";
            }
            cout << "+" << endl;

            cout << setfill(' ');
            cout << "| " << setw(colWidths[0]) << "No"
                << " | "
                << setw(colWidths[1]) << "Nama"
                << " | "
                << setw(colWidths[2]) << "Deskripsi"
                << " | "
                << setw(colWidths[3]) << "Harga"
                << " | "
                << setw(colWidths[4]) << "Stok"
                << " |" << endl;

            cout << setfill('-');
            for (int i = 0; i < 6; i++)
            {
                cout << "+" << setw(colWidths[i]) << "-";
            }
            cout << "+" << endl;
        }
    }
    if (root != NULL)
    {
        if (root->data.id >= parentId && root->data.id < (parentId + 5))
        {
            if (root->left != NULL)
            {
                int colWidths[] = {3, 15, 70, 15, 5, 9};
                cout << setfill(' ');
                cout << "| " << setw(colWidths[0]) << counter << " | "
                << setw(colWidths[1]) << root->left->data.nama << " | "
                << setw(colWidths[2]) << root->left->data.deskripsi << " | "
                << setw(colWidths[3]) << root->left->data.harga << " | "
                << setw(colWidths[4]) << root->left->data.stok << " |" << endl;

                counter++;
            }
            else if (root->right != NULL)
            {
                int colWidths[] = {3, 15, 70, 15, 5, 9};
                cout << setfill(' ');
                cout << "| " << setw(colWidths[0]) << counter << " | "
                << setw(colWidths[1]) << root->right->data.nama << " | "
                << setw(colWidths[2]) << root->right->data.deskripsi << " | "
                << setw(colWidths[3]) << root->right->data.harga << " | "
                << setw(colWidths[4]) << root->right->data.stok << " |" << endl;

                counter++;
            }

            printDaftar(root->left, parentId, rekursiCount, counter);
            printDaftar(root->right, parentId, rekursiCount, counter);
        }
        else
        {
            printDaftar(root->left, parentId, rekursiCount, counter);
            printDaftar(root->right, parentId, rekursiCount, counter);
        }
    }
};

void printKategori(tree *root)
{
    int pil;
    string temp;
    system("cls");
    cout << "\t\t\t\t===============================" <<
    endl << "\t\t\t\t         Menu Kategori" <<
    endl << "\t\t\t\t===============================" <<
    endl << endl << "================" <<
    endl << " [1] Pakaian" <<
    endl << " [2] Elektronik" <<
    endl << " [3] Makanan" <<
    endl << " [0] Menu Utama" <<
    endl << "================" <<
    endl << endl << "Pilih Kategori : ";
    cin >> temp;
    try
    {
        pil = stoi(temp);
    }
    catch(const std::exception& e)
    {
        cout << "Masukan inputan yang benar" << endl;
        system("pause");
        printKategori(root);
    }

    if (pil > 0 && pil < 4)
    {
        pil = pil * 100;
        system("cls");
        cout << endl;
        printDaftar(root, pil, 0, 1);
        int colWidths[] = {3, 15, 70, 15, 5, 9};
        cout << setfill('-');
        for (int i = 0; i < 6; i++)
        {
            cout << "+" << setw(colWidths[i]) << "-";
        }
        cout << "+" << endl;
        cout << endl;
        system("pause");
        printKategori(root);
    }
    else if (pil == 0)
    {
        menuUtama();
    }
    else
    {
        printKategori(root);
    }

};

void minusStok(tree *root, int pil, int minStok, bool done)
{
    if (pil >= 1 && pil < 4)
    {
        pil = pil + 100;
        minusStok(root, pil, minStok, done);
        return;
    }
    else if (pil >= 4 && pil < 7)
    {
        pil = (pil - 3) + 200;
        minusStok(root, pil, minStok, done);
        return;
    }
    else if (pil >= 7 && pil < 10)
    {
        pil = (pil - 6) + 300;
        minusStok(root, pil, minStok, done);
        return;
    }
    if (root != NULL)
    {
        if (root->data.id == pil)
        {
            root->data.stok = root->data.stok - minStok;
            done = true;
        }

        if (root->left != NULL)
            minusStok(root->left, pil, minStok, done);
        if (root->right != NULL)
            minusStok(root->right, pil, minStok, done);
    }
}
void plusStok(tree *root, int pil, int minStok, bool done)
{
    if (pil >= 1 && pil < 4)
    {
        pil = pil + 100;
        plusStok(root, pil, minStok, done);
        return;
    }
    else if (pil >= 4 && pil < 7)
    {
        pil = (pil - 3) + 200;
        plusStok(root, pil, minStok, done);
        return;
    }
    else if (pil >= 7 && pil < 10)
    {
        pil = (pil - 6) + 300;
        plusStok(root, pil, minStok, done);
        return;
    }
    if (root != NULL)
    {
        if (root->data.id == pil)
        {
            root->data.stok = root->data.stok + minStok;
            done = true;
        }

        if (root->left != NULL)
            plusStok(root->left, pil, minStok, done);
        if (root->right != NULL)
            plusStok(root->right, pil, minStok, done);
    }
}

const int ukuranQueue = 99;
struct Queue
{
    int top;
    string noTransaksi[ukuranQueue];
    string namaBarang[ukuranQueue];
    int waktuTransaksi[ukuranQueue];

};Queue queue;



void createQueue()
{
    queue.top = 0;
}

bool isEmpty()
{
    if (queue.top == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isFull()
{
    if (queue.top >= ukuranQueue)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void inQueue(string data, string barang)
{
        queue.noTransaksi[queue.top] = data;
        queue.namaBarang[queue.top] = barang;
        time_t waktuTemp = time(nullptr);
        queue.waktuTransaksi[queue.top] = waktuTemp;
        queue.top++;
}

string deQueue()
{
    string temp = queue.noTransaksi[0];
    for (int i = 1; i < queue.top; i++)
    {
        queue.noTransaksi[i - 1] = queue.noTransaksi[i];
        queue.namaBarang[i - 1] = queue.namaBarang[i];
        queue.waktuTransaksi[i - 1] = queue.waktuTransaksi[i];
    }
    queue.top--;
    return temp;
}

void checkPembayaran()
{
    if (!isEmpty())
    {
        time_t waktuTemp = time(nullptr);
        int saatIni = waktuTemp;
        if (saatIni - queue.waktuTransaksi[0] >= 15)
        {
            node *current = keranjang.head;
            string checking = deQueue();
            while (current != NULL && current->Transaksi.noTransaksi != checking)
            {
                current = current->next;
            }
            int i = 0;
            while (queue.namaBarang[0] != listProduk[i].nama)
            {
                i++;
            }
            listProduk[i].stok = listProduk[i].stok - current->Transaksi.Qty;
            i++;
            minusStok(pohon, i, current->Transaksi.Qty, false);
            current->Transaksi.statusPembayaran = "Transaksi Selesai";
            cout << "\033[32m";
            cout << "Transaksi dengan nomor " << current->Transaksi.noTransaksi << " Sudah Selesai" << endl << endl;
            cout << "\033[0m";
        }
    }
    else
    {
        cout << endl;
    }
}

// MEMBUAT LIST KOSONG
void createEmpty(linkedlist *list)
{
    list->head = NULL;
    list->tail = NULL;
}

// CEK STATUS LIST
bool isEmpty(linkedlist list)
{
    if (list.head == NULL)
    {
        return true;
    }
    return false;
}

// GENERATE NOMOR TRANSAKSI
string noTransaksiAcak(){
    static int counter = 1;
    string transaksiNomer = "OLS-" + to_string(counter);
    counter++;
    return transaksiNomer;
}

int pembelian();
// MENAMBAHKAN TRANSAKSI
void insertLast(linkedlist *list, produk listProduk[], int x)
{
    int tempQty;
    string tempNoTrans, choice, tempStr;
    cout << "[2] Jumlah\t\t\t\t\t: ";
    cin >> tempStr;
    try
    {
        tempQty = stoi(tempStr);
    }
    catch(const std::exception& e)
    {
        tempQty = -1;
    }


    if (tempQty < 0)
    {
        cout << "Input tidak valid." << endl;
        system("pause");
        pembelian();
    }

    if ((listProduk[x-1].stok - tempQty) < 0)
    {
        cout << "Maaf Jumlah melebihi stok" << endl;
        system("pause");
        menuUtama();
    }
    cout << "[3] Nomor Transaksi \t\t\t\t: ";
    cout << noTransaksiAcak() << endl << endl;
    system("pause");
    tempNoTrans = noTransaksiAcak();


    node *new_node, *current;
    new_node = new node;
    new_node->Transaksi.noTransaksi = tempNoTrans;
    new_node->Transaksi.namaProduk = listProduk[x-1].nama;
    new_node->Transaksi.Qty = tempQty;
    new_node->Transaksi.totalHarga = tempQty * listProduk[x-1].harga;
    new_node->Transaksi.VAccount = listProduk[x-1].vAccount;
    new_node->next = NULL;

    if (isEmpty(keranjang))
    {
        list->head = new_node;
        list->head->next = NULL;
    }
    else
    {
        current = list->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }
}

// MENGHAPUS TRANSAKSI TERAKHIR
void removeLast(linkedlist *list)
{
    if (list->head == NULL)
    {
        cout << "List kosong" << endl;
        system("pause");
        return;
    }
    else if (list->head->next == NULL)
    {
        delete list->head;
        list->head = NULL;
    }
    else {
        node *temp = NULL;
        node *current = list->head;
        while (current->next != NULL)
        {
            temp = current;
            current = current->next;
        }
        temp->next = NULL;
        delete current;
    }
}

// MENAMPILKAN HISTORY TRANSAKSI
void displayHistory(linkedlist list)
{
    system("CLS");
    if (isEmpty(list))
        cout << "List kosong" << endl;
    else{
        node *current = list.head;
        while (current != NULL){
            cout << "Nomor Transaksi\t  : " << current->Transaksi.noTransaksi << endl
            << "Produk\t\t  : " << current->Transaksi.namaProduk << endl
            << "Jumlah\t\t  : " << current->Transaksi.Qty << "\t" << endl
            << "Total Harga\t  : " << current->Transaksi.totalHarga << endl;
            if (current->Transaksi.statusPembayaran == "Sudah Selesai")
            {
                cout << "\033[32m";
            }
            else if (current->Transaksi.statusPembayaran == "Transaksi Pending")
            {
                cout << "\033[33m";
            }
            else if (current->Transaksi.statusPembayaran == "Belum Selesai")
            {
                cout << "\033[31m";
            }
            cout << "Status Pembayaran : " << current->Transaksi.statusPembayaran << endl;
            cout << "\033[0m";
            current = current->next;
            cout << "======================================" << endl << endl;
        }
        cout << endl;
    }
}

// PENGGUNAAN VOID UNTUK REGISTER
void registrasi() {
    string username, pass;

    cout << "                                    ==============================" << endl;
    cout << "                                    |         REGISTER           |" << endl;
    cout << "                                    ==============================" << endl << endl;
    cout << "Username: " << setw(5); cin >> username;
    cout << "Password: " << setw(5); cin >> pass;
    cout << endl << endl;

    ofstream userFile("dataUser.txt", ios::app);
    if (userFile.is_open()){
        userFile << "username : " << username << " | "
                 << "password = " << pass << endl;
        userFile.close();
        cout << "\033[32m";
        cout << "=====================" << endl;
        cout << " Registrasi Berhasil "<< endl;
        cout << "=====================" << endl << endl;
        cout << "\033[0m";
    }
    else{
        cout << "Something Went Wrong!" << endl;
    }
}

// PENGGUNAAN VOID UNTUK LOGIN
bool login() {
    string username, pass, line;
    bool check = false;
    char input;

    cout << "                                   ==============================" << endl;
    cout << "                                   |           LOGIN            |" << endl;
    cout << "                                   ==============================" << endl << endl;
    cout << "Username: " << setw(5); cin >> username;
    // cout << "Password: " << setw(5);
    cout << "Password: ";
    pass = "";
    while (true) {
        input = getch();
        if (input == 13) {
            break;
        } else if (input == 8) {
            if (pass.length() > 0) {
                pass.pop_back();
                cout << "\b \b";
            }
        } else if (input >= 32 && input <= 126) {
            pass += input;
            cout << "*";
        }
    }


    cout << endl << endl;

    ifstream userFile("dataUser.txt");
    if (userFile.is_open()){
        while (getline(userFile, line))
        {
            size_t pos = line.find(" | ");
            size_t pos2 = line.find("=");
            string u = line.substr(11, pos - 11);
            string p = line.substr(pos2 + 2);
            if (u == username && p == pass)
            {
                check = true;
                break;
            }
        }
        userFile.close();
        if (check){
            cout << "\033[32m";
            cout << "=====================" << endl;
            cout << "   Login Berhasil    " << endl;
            cout << "=====================" << endl << endl;
            cout << "\033[0m";
        }
        else{
            cout << "\033[31m";
            cout << "==========================" << endl;
            cout << "    Username / Password   " << endl;
            cout << "          Salah           " << endl;
            cout << "==========================" << endl << endl;
            cout << "\033[0m";
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
    cout << "\033[38;5;202m";
    cout << "                                     ===============================================" << endl;
    cout << "                                     |            ONLINE SALES PROGRAM             |" << endl;
    cout << "                                     ===============================================" << endl << endl << endl;
    cout << "\033[0m";
    // cout << "================== DAFTAR PRODUK ==================" << endl << endl;
    cout << setfill('=') << setw(63) << " DAFTAR PRODUK " << setfill('=') << setw(62) << " " << endl << endl;
    // for (int i = 0; i < length; i++)
    // {
    //     produk *pProduk = &listProduk[i]; // pointer untuk mengakses struct produk
    //     cout << i + 1 << ". " << pProduk->nama << endl
    //          << "   Deskripsi \t\t: " << pProduk->deskripsi << endl
    //          << "   Harga \t\t: " << pProduk->harga << endl
    //          << "   Stok \t\t: " << pProduk->stok << endl
    //          << endl;
    // }

    // TAMPILAN TABEL
    int colWidths[] = {3, 15, 70, 15, 5, 16};

    cout << setfill('-');
    for (int i = 0; i < 6; i++)
    {
        cout << setw(colWidths[i]) << "+";
    }
    cout << endl;

    cout << setfill(' ');
    cout << "| " << setw(colWidths[0]) << "No"
         << " | "
         << setw(colWidths[1]) << left << "Nama"
         << " | "
         << setw(colWidths[2]) << "Deskripsi"
         << " | "
         << setw(colWidths[3]) << "Harga"
         << " | "
         << setw(colWidths[4]) << "Stok"
         << " |" << endl;

    cout << setfill('-');
    for (int i = 0; i < 6; i++)
    {
        cout << setw(colWidths[i]) << "+";
    }
    cout << endl;

    cout << setfill(' ');
    for (int i = 0; i < length; i++)
    {
        produk *pProduk = &listProduk[i];
        cout << "| " << setw(colWidths[0]) << i + 1 << " | "
             << setw(colWidths[1]) << pProduk->nama << " | "
             << setw(colWidths[2]) << pProduk->deskripsi << " | "
             << setw(colWidths[3]) << pProduk->harga << " | "
             << setw(colWidths[4]) << pProduk->stok << " |" << endl;
    }

    cout << setfill('-');
    for (int i = 0; i < 6; i++)
    {
        cout << setw(colWidths[i]) << "+";
    }
    cout << endl;
}

// FITUR PEMBELIAN/PENAMBAHAN TRANSAKSI
int pembelian(){
    int pilihB;
    string temp;
    while (1 == 1)
    {
        displayDaftar();
        cout << "\n\n";
        cout << "[1] Masukkan Nomor Produk Yang Akan Dibeli\t: ";
        cin >> temp;
        try
        {
            pilihB = stoi(temp);
        }
        catch(const std::exception& e)
        {
            pilihB = 0;
        }

        if (pilihB > length || pilihB < 1)
        {
            cout << "Masukan inputan yang benar" << endl;
            system("pause");
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
            system("CLS");
            cout << "\t\t\t\t===========" << endl;
            cout << "\t\t\t\t  INVOICE" << endl;
            cout << "\t\t\t\t===========" << endl << endl;
            while (current != NULL){
                cout
                << "Nomor Transaksi\t  : " << current->Transaksi.noTransaksi << endl
                << "Produk\t\t  : " << current->Transaksi.namaProduk << endl
                << "Jumlah\t\t  : " << current->Transaksi.Qty << "\t" << endl
                << "Total Harga\t  : " << current->Transaksi.totalHarga << endl
                << endl;
                break;
            }
            cout << endl;
            while (1 == 1)
            {
                cout << "Pesanan Sudah Sesuai [Y] Ya / [N] Tidak\t\t\t\t: ";
                cin >> choice;
                if (choice == "y" || choice == "Y")
                {
                    cout << "Generate Virtual Account Untuk Pembayaran [Y] Ya / [N] Tidak\t: ";
                    cin >> choice;
                    if (choice == "y" || choice == "Y")
                    {
                        current2->Transaksi.statusPembayaran = "Transaksi Pending";
                        inQueue(current2->Transaksi.noTransaksi, current2->Transaksi.namaProduk);
                        cout << endl << "Nomor Virtual Account : " << listProduk[pilihB-1].vAccount << endl;
                        cout << "Silahkan bayar dengan metode pembayaran anda !" << endl << endl;
                        cout << "\033[32m";
                        cout << "Produk berhasil ditambahkan ke keranjang" << endl;
                        cout << "\033[0m \n\n";
                        system("pause");
                        return menuUtama();
                    }
                    else if (choice == "n" || choice == "N")
                    {
                        current2->Transaksi.statusPembayaran = "Belum Selesai";
                        cout << "\n\n";
                        cout << "\033[32m";
                        cout << "Produk berhasil ditambahkan ke keranjang" << endl;
                        cout << "\033[0m \n\n";
                        system("pause");
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
    return 0;
}

int Pembayaran(){
    while (1 == 1)
    {
        system("CLS");
        string subMenu;
        cout << "\033[38;5;202m";
        cout << "                                     ===============================================" << endl;
        cout << "                                     |            ONLINE SALES PROGRAM             |" << endl;
        cout << "                                     ===============================================" << endl << endl << endl;
        cout << "\033[0m";
        cout << "====== MENU PEMBAYARAN ======" << endl;
        cout << "[1] Histori Pembayaran" << endl;
        cout << "[2] Bayar" << endl;
        cout << "[3] Kembali" << endl << endl;
        cout << "Pilihan Menu: ";
        cin >> subMenu;
        int temp = tryCatch(subMenu);
        switch (temp)
        {
        case 1:
            displayHistory(keranjang);
            system("pause");
            break;
        case 2:
            system("cls");
            displayHistory(keranjang);
            cout << endl
                 << endl;
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
                while (current != NULL && current->Transaksi.noTransaksi != search)
                {
                    current = current->next;
                }
                if (current == NULL)
                {
                    cout << "No. Transaksi tidak terdaftar" << endl;
                    system("pause");
                    break;
                }
                current2 = current;
                // while (current != NULL){
                //     cout << endl
                //     << "Nomor Transaksi\t  : " << current2->Transaksi.noTransaksi << endl
                //     << "Produk\t\t  : " << current2->Transaksi.namaProduk << endl
                //     << "Jumlah\t\t  : " << current2->Transaksi.Qty << endl
                //     << "Total Harga\t  : " << current2->Transaksi.totalHarga << endl
                //     << "Status Pembayaran : " << current2->Transaksi.statusPembayaran << endl
                //     << endl;
                //     break;
                // }
                cout << endl;

                if (current2->Transaksi.statusPembayaran == "Sudah Selesai")
                {
                    cout << "\033[32m";
                    cout << "Transaksi dengan nomor " << current2->Transaksi.noTransaksi << " Sudah Selesai, Tidak Perlu Dibayar" << endl
                         << endl;
                    cout << "\033[0m";
                }
                else if (current2->Transaksi.statusPembayaran == "Transaksi Pending")
                {
                    cout << "\033[33m";
                    cout << "Transaksi sedang dalam proses pembayaran melalui Virtual Account oleh pengguna, harap menunggu!" << endl
                         << endl;
                    cout << "\033[0m";
                }
                else if (current2->Transaksi.statusPembayaran == "Belum Selesai")
                {
                    current2->Transaksi.statusPembayaran = "Transaksi Pending";
                    inQueue(current2->Transaksi.noTransaksi, current2->Transaksi.namaProduk);
                    cout << endl
                         << "Nomor Virtual Account : " << current2->Transaksi.VAccount << endl;
                    cout << "Silahkan bayar dengan metode pilihan anda !" << endl
                         << endl;
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

void pengembalian(){
    system("cls");
    string pengembalianStr;
    int input;
    cout << "No. Transaksi yang Ingin dikembalikan: ";
    cin >> pengembalianStr;
    cout << "Jumlah barang yang akan dikembalikan: ";
    cin >> input;
    node *current = keranjang.head;
    while (current != NULL && current->Transaksi.noTransaksi != pengembalianStr)
    {
        current = current->next;
    }
    if (current == NULL)
    {
        cout << "No. Transaksi tidak ada" << endl;
        system("pause");
        pengembalian();
    }
    if (current->Transaksi.statusPembayaran == "Transaksi Selesai")
    {
        if (current->Transaksi.Qty - input < 0)
        {
            cout << "Jumlah barang yang dikembalikan melebihi jumlah barang Transaksi" << endl;
            system("pause");
            pengembalian();
        }
        int i = 0;
        while ( current->Transaksi.namaProduk != listProduk[i].nama)
        {
            i++;
        }
        current->Transaksi.Qty = current->Transaksi.Qty - input;
        current->Transaksi.totalHarga = current->Transaksi.Qty * listProduk[i].harga;
        listProduk[i].stok = listProduk[i].stok + input;
        i++;
        plusStok(pohon, i, input, false);
    }
    else{
        cout << "Transaksi belum dilakukan" << endl;
        system("pause");
        menuUtama();
    }

}

// MENAMPILKAN MENU UTAMA
int menuUtama(){
    bool exitloop = false;
    while (!exitloop)
    {
        int pilihM;
        string temp;
        system("cls");
        cout << "\033[38;5;202m";
        cout << "                                     ===============================================" << endl;
        cout << "                                     |            ONLINE SALES PROGRAM             |" << endl;
        cout << "                                     ===============================================" << endl << endl << endl;
        cout << "\033[0m";
        cout << "Notifikasi:" << endl;
        checkPembayaran();
        cout << "========= MENU UTAMA =========" << endl;
        cout << "[1] Melihat Daftar Produk     " << endl
             << "[2] Pembelian                 " << endl
             << "[3] Melihat Histori Transaksi " << endl
             << "[4] Pembayaran                " << endl
             << "[5] Pengembalian Barang" << endl
             << "[6] Keluar Program            " << endl << endl;
        cout << "Pilih menu: ";
        cin >> temp;
        pilihM = tryCatch(temp);
        /* while (true) {
            try {
                cin >> pilihM;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    throw std::runtime_error("Input tidak valid");
                }

                // Cek batasan pilihan menu yang diperbolehkan
                if (pilihM < 1 || pilihM > 5) {
                    throw std::runtime_error("Masukkan pilihan yang benar");
                }

                break; // Keluar dari loop jika input valid
            }
            catch (const std::exception& e) {
                std::cerr << "Terjadi kesalahan: " << e.what() << std::endl;
                cout << "Pilih menu: ";
            }
        } */
        switch (pilihM)
        {
        case 1:
            printKategori(pohon);
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
            system("cls");
            pengembalian();
            break;
        case 6:
            system("CLS");
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
    string temp;
    bool valid;
    listingProduk();

    while (1 == 1)
    {
        system("cls");
        cout << "\033[38;5;202m";
        cout << "                                     ===============================================" << endl;
        cout << "                                     |                  WELCOME                    |" << endl;
        cout << "                                     |            ONLINE SALES PROGRAM             |" << endl;
        cout << "                                     ===============================================" << endl << endl << endl;
        cout << "\033[0m";
        cout << "[1] LOGIN" << endl;
        cout << "[2] REGISTRASI" << endl << endl;
        cout << "Silahkan Pilih\t: ";
        cin >> temp;
        try
        {
            pilih = stoi(temp);
        }
        catch (const std::exception &e)
        {
            cout << "Masukan inputan yang benar" << endl;
            system("pause");
            continue;
        }

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
