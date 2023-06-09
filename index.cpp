#include <iostream>
#include <iomanip> // untuk menggunakan manipulasi setw dan setfill
#include <string> // untuk kebutuhan registrasi & login
#include <fstream> // untuk kebutuhan registrasi & login
#include <cstdlib> // untuk fungsi exit
#include <conio.h> // untuk getch password
using namespace std;

// PENGGUNAAN STRUCT
struct produk
{
    string nama;
    string deskripsi;
    double harga;
    int stok;
    int id;
    string kategori;
};

struct tree
{
    produk data;
    tree *left, *right;
};
tree *pohon, *root;

void deklarasi()
{
    pohon = NULL;
};

void inputTree(tree **root, string nama, string deskripsi, double harga, int stok, int id, string kategori)
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
        newnode->left = newnode->right = NULL;

        (*root) = newnode;
        (*root)->data.id = id;
        (*root)->left = (*root)->right = NULL;
    }
    else if (id < (*root)->data.id)
    {
        inputTree(&(*root)->left, nama, deskripsi, harga, stok, id, kategori);
    }
    else
    {
        inputTree(&(*root)->right, nama, deskripsi, harga, stok, id, kategori);
    }
};

void listingProduk()
{
    deklarasi();
    inputTree(&pohon, "", "", 0, 0, 270, "Main");
    inputTree(&pohon, "", "", 0, 0, 150, "Group 1");
    inputTree(&pohon, "", "", 0, 0, 100, "Pakaian");
    inputTree(&pohon, "HOODIE AHHA", "HOODIE DENGAN BERBAGAI UKURAN DARI MINIMAL HINGGA MAKSIMAL", 455000, 50, 101, "Pakaian");
    inputTree(&pohon, "KAOS IBU HAMIL", "KAOS DENGAN UKURAN S SAJA", 95000, 3, 102, "Pakaian");
    inputTree(&pohon, "JAKET ZIPPER", "JAKET BISA DI PAKAI FORMAL MAUPUN CASUAL (SANTAI ABIS)", 300500, 36, 103, "Pakaian");
    inputTree(&pohon, "", "", 0, 0, 200, "Elektronik");
    inputTree(&pohon, "ASUS TUF GAMING", "LAPTOP BISA DIPAKAI UNTUK NGODING C++", 15222000, 11, 201, "Elektronik");
    inputTree(&pohon, "GALAXY Z FOLD4", "HP SAMSUNG LIPAT CANGGIH UNTUK ANDA", 7999000, 5, 202, "Elektronik");
    inputTree(&pohon, "LG SMART TV 32", "TV CERDAS LEBIH CERDAS DARI ANDA", 1250000, 7, 203, "Elektronik");
    inputTree(&pohon, "", "", 0, 0, 350, "Group 2");
    inputTree(&pohon, "", "", 0, 0, 300, "Makanan");
    inputTree(&pohon, "BASRENG PEDAS", "BASRENG SEUHAH DENGAN DAUN JERUK", 25000, 15, 301, "Makanan");
    inputTree(&pohon, "EAT SAMBEL", "SAMBEL TIKTOKERS YANG ENAK", 35500, 100, 302, "Makanan");
    inputTree(&pohon, "ROTI AOKA", "ROTI BUKAN SEKEDAR ROTI, TAPI ROTI ENAK", 2500, 29, 303, "Makanan");
};

// void printDaftar (tree *root, int parentId)
// {
//     if (root != NULL)
//     {
//         if (root->data.id >= parentId && root->data.id < (parentId + 5))
//         {
//             if (root->left != NULL)
//                 cout << root->left->data.id << endl;
//             else if (root->right != NULL)
//                 cout << root->right->data.id << endl;

//             printDaftar(root->left, parentId);
//             printDaftar(root->right, parentId);
//         }
//         else
//         {
//             printDaftar(root->left, parentId);
//             printDaftar(root->right, parentId);
//         }
//     }
// };

void printProduk(tree* root, int& counter);

void printDaftar (tree *root, int parentId)
{
    int counter = 1;
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

        printProduk(root, counter);

        cout << setfill('-');
        for (int i = 0; i < 6; i++)
        {
            cout << "+" << setw(colWidths[i]) << "-";
        }
        cout << "+" << endl;
    }
};

void printProduk(tree* root, int& counter)
{
    if (root != NULL)
    {
        int colWidths[] = {3, 15, 70, 15, 5, 9};
        printProduk(root->left, counter);

        cout << setfill(' ');
        cout << "| " << setw(colWidths[0]) << counter << " | "
             << setw(colWidths[1]) << root->data.nama << " | "
             << setw(colWidths[2]) << root->data.deskripsi << " | "
             << setw(colWidths[3]) << root->data.harga << " | "
             << setw(colWidths[4]) << root->data.stok << " |" << endl;
        counter++;
        printProduk(root->right, counter);
    }
}

void printKategori(tree *root)
{
    int pil;
    system("cls");
    cout << "===============================" <<
    endl << "         Menu Kategori" <<
    endl << "===============================" <<
    endl << "1. Pakaian" <<
    endl << "2. Elektronik" <<
    endl << "3. Makanan" <<
    endl << "0. Menu Utama" <<
    endl << "===============================" <<
    endl << "Pilih menu kategori : ";
    cin >> pil;
    if (pil > 0 && pil < 4)
    {
        pil = pil * 100;
        system("cls");
        printDaftar(root, pil);
    }
    else if (pil == 0)
    {
        return;
    }
    else
    {
        printKategori(root);
    }
    
};

void minusStok(tree *root, int pil, int minStok)
{
    if (pil >= 1 && pil < 4)
    {
        pil = pil + 100;
        minusStok(root, pil, minStok);
    }
    else if (pil >= 4 && pil < 7)
    {
        pil = (pil - 3) + 200;
        minusStok(root, pil, minStok);
    }
    else if (pil >= 7 && pil < 10)
    {
        pil = (pil - 6) + 300;
        minusStok(root, pil, minStok);
    }
    
     if (root != NULL)
    {
        if (root->data.id == pil)
        {
            root->data.stok = root->data.stok - minStok;
        }
        else
        {
            minusStok(root->left, pil, minStok);
            minusStok(root->right, pil, minStok);
        }
    }
}

produk listProduk[] = {
    {"HOODIE AHHA", "HOODIE DENGAN BERBAGAI UKURAN DARI MINIMAL HINGGA MAKSIMAL", 455000, 50, 101},
    {"KAOS IBU HAMIL", "KAOS DENGAN UKURAN S SAJA", 95000, 3, 102},
    {"JAKET ZIPPER", "JAKET BISA DI PAKAI FORMAL MAUPUN CASUAL (SANTAI ABIS)", 300500, 36, 103},
    {"ASUS TUF GAMING", "LAPTOP BISA DIPAKAI UNTUK NGODING C++", 15222000, 11, 201},
    {"GALAXY Z FOLD4", "HP SAMSUNG LIPAT CANGGIH UNTUK ANDA", 7999000, 5, 202},
    {"LG SMART TV 32", "TV CERDAS LEBIH CERDAS DARI ANDA", 1250000, 7, 203},
    {"BASRENG PEDAS", "BASRENG SEUHAH DENGAN DAUN JERUK", 25000, 15, 401},
    {"EAT SAMBEL", "SAMBEL TIKTOKERS YANG ENAK", 35500, 100, 402},
    {"ROTI AOKA", "ROTI BUKAN SEKEDAR ROTI, TAPI ROTI ENAK", 2500, 29, 403}};

// GLOBAL VARIABEL
int length = sizeof(listProduk) / sizeof(listProduk[0]);

int menuUtama();

struct transaksi
{
    string noTransaksi;
    string namaProduk;
    int Qty;
    int totalHarga;
    string statusPembayaran;
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

// MENAMBAHKAN TRANSAKSI
void insertLast(linkedlist *list, produk listProduk[], int x)
{
    int tempQty;
    string tempNoTrans, choice;
    cout << "2. Jumlah\t\t\t\t\t: ";
    cin >> tempQty;
    if ((listProduk[x-1].stok - tempQty) < 0)
    {
        cout << "Maaf Jumlah melebihi stok" << endl;
        system("pause");
        menuUtama();
    }
    cout << "3. Nomor Transaksi \t\t\t\t: ";
    cout << noTransaksiAcak() << endl;
    system("pause");
    tempNoTrans = noTransaksiAcak();


    node *new_node, *current;
    new_node = new node;
    new_node->Transaksi.noTransaksi = tempNoTrans;
    new_node->Transaksi.namaProduk = listProduk[x-1].nama;
    new_node->Transaksi.Qty = tempQty;
    new_node->Transaksi.totalHarga = tempQty * listProduk[x-1].harga;
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
    cout << "================== DAFTAR PRODUK ==================" << endl << endl;
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
    while (1 == 1)
    {
        displayDaftar();
        cout << "\n\n";
        cout << "=================================" << endl;
        cout << "1. Masukkan Nomor Produk Yang Akan Dibeli\t: ";
        cin >> pilihB;
        
        if (pilihB > length || pilihB < 1)
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
            system("CLS");
            while (current != NULL){
                cout  
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
                cout << "Pesanan ini sudah sesuai?" << endl;
                cout << "[y]Ya / [n]Tidak\t: ";
                cin >> choice;
                if (choice == "y" || choice == "Y")
                {
                    cout << "Sudahkah pembayaran dilakukan?" << endl;
                    cout << "[y]Ya / [n]Tidak\t: ";
                    cin >> choice;
                    if (choice == "y" || choice == "Y")
                    {
                        current2->Transaksi.statusPembayaran = "Sudah Selesai";
                        cout << "\033[32m";
                        cout << "Produk berhasil ditambahkan ke keranjang" << endl;
                        cout << "\033[0m \n\n";
                        system("pause");
                        listProduk[pilihB-1].stok = (listProduk[pilihB-1].stok) - (current->Transaksi.Qty);
                        minusStok(pohon, pilihB, current->Transaksi.Qty);
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
        int subMenu;
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
        switch (subMenu) {
            case 1:
                displayHistory(keranjang);
                system("pause");
                break;
            case 2:
                system("cls");
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
                        cout << "Transaksi dengan nomor " << current2->Transaksi.noTransaksi << " Sudah Selesai, Tidak Perlu Dibayar" << endl << endl;
                        cout << "\033[0m";
                    }
                    else if (current2->Transaksi.statusPembayaran == "Belum Selesai")
                    {
                        cout << "\033[32m";
                        current2->Transaksi.statusPembayaran = "Sudah Selesai";    
                        cout << "Transaksi dengan nomor " << current2->Transaksi.noTransaksi << " telah dibayar." << endl << endl;
                        cout << "\033[0m";
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
        cout << "\033[38;5;202m";
        cout << "                                     ===============================================" << endl;
        cout << "                                     |            ONLINE SALES PROGRAM             |" << endl;
        cout << "                                     ===============================================" << endl << endl << endl;
        cout << "\033[0m";
        cout << "========= MENU UTAMA =========" << endl;
        cout << "[1] Melihat Daftar Produk     " << endl
             << "[2] Pembelian                 " << endl
             << "[3] Melihat Histori Transaksi " << endl
             << "[4] Pembayaran                " << endl
             << "[5] Keluar Program            " << endl << endl;
        cout << "Pilih menu: ";
        cin >> pilihM;

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
        cout << "Silahkan Pilih\t: "; cin >> pilih; 

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
