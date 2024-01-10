#include<iostream>
using namespace std;

const int not_item = -1;

struct Node{
	string data;
    int harga;
    int stok;
	struct Node *next;
	struct Node *child;
 //   struct node (int val) : data(val), leftChild(nullptr), rightSibling(nullptr) {}

};
//aku ngantuk
struct customer{

};

//deklarasi meja
const int jumlahMeja = 11;
int jumlahKursi;
string meja[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "Bar", "Bar Tengah"};
int kursi[] = {6, 6, 4, 4, 4, 2, 2, 2, 2, 6, 6};
//meja dengan nomor [indeks] memiliki kapasitas kursi pada [indkes] yang sama

bool statusMeja[11];

struct table{
    string meja;
    int kursi;
    table *next;
};

Node* newNode(string data, int stok, int harga){
	Node *newNode = new Node;
	newNode->next = newNode->child = NULL;
	newNode->data = data;
	newNode->stok = stok;
	newNode->harga = harga;
	return newNode;
}
// test change
Node *addSibling(Node *n, string data, int stok, int harga){
	if (n == NULL)
		return NULL;

	while (n->next)
		n = n->next;

	return (n->next = newNode(data, stok, harga));
}

Node *addChild(Node * n, string data, int stok, int harga){
	if (n == NULL)
		return NULL;

	if (n->child)
		return addSibling(n->child, data, stok, harga);
	else
		return (n->child = newNode(data, stok, harga));
}

void traverseTree(Node *root, int level){
    if (root == NULL)
        return;

    for (int i = 0; i < level; ++i)
        cout << "    ";

    if (root -> harga == not_item){
        cout << "|-" << root->data << "\n";
    } else {
    cout << "|-" << root->data;
    cout << ", stok : " << root->stok;
    cout << ", harga : " << root->harga << "\n";
    }
    if (root->child)
        traverseTree(root->child, level + 1);

    if (root->next)
        traverseTree(root->next, level);
    
}

void menu_header(Node *root){
    cout <<"\n==================\n| ";
    cout << root->data << " |\n==================\n";
	root= root -> child;
    traverseTree(root, 1);
}

void PencarianFilter(Node *root, const string &filter, int level){
    if (root == NULL)
        return;

    if (root->data == filter)
    {
        traverseTree(root, level);
        return;
    }

    if (root->child)
        PencarianFilter(root->child, filter, level + 1);

    if (root->next)
        PencarianFilter(root->next, filter, level);
}

void PageFilter(Node *root){
	int pilihan;
	string filter;
	cout<<"1.filter kategori \n2.filter sub kategori \npilihan: ";
	cin>>pilihan;

	switch (pilihan){
		case 1:
			cout<<"kategori apa yang anda inginkan: ";
			cin>>filter;
			PencarianFilter(root, filter, 0);
			break;
		case 2:
			break;
	}
}

void PagePelangan(Node *root){
	int pilihan;

	cout<<"1.tampilkan menu \n2.filter pencarian \npilihan: ";
	cin>>pilihan;
	system("cls");

	switch (pilihan){
		case 1:
			menu_header(root);
			
			break;
		case 2:
			PageFilter(root);
			
			break;
	}
}

void findMenu(Node *current, const string &searchItem, Node *&result) {
    while (current != nullptr) {
        if (current->data == searchItem) {
            result = current;
            break; 
        }

        if (current->child != nullptr) {
            findMenu(current->child, searchItem, result);
            if (result != nullptr) {
                break;
            }
        }

        current = current->next;
    }
}

void searchMenu(Node *root) {
    string searchItem;
    cout << "Masukkan menu yang ingin dicari: ";
    cin.ignore();
    getline(cin, searchItem);

    Node *result = nullptr;

    findMenu(root, searchItem, result);

    if (result) {
        cout << "Item ditemukan: " << result->data;
        cout << ", Stok: " << result->stok;
        cout << ", harga: " << result->harga<< endl;
    } else {
        cout << "Item tidak ditemukan.\n";
    }

    system("pause");
    customer_more_action(root);
}

void filterByMaxPrice(Node *root, int budget) {
    if (root == nullptr) {
        return;
    }

    if (root->harga != -1 && root->harga <= budget) {
        cout << "Item: " << root->data;
        cout << ", Harga: " << root->harga << endl;
    }

    filterByMaxPrice(root->child, budget);

    filterByMaxPrice(root->next, budget);
}


void findSubcategory(Node *root, const string &subcategory) {
    if (root == nullptr) {
        return;
    }

    if (root->data == subcategory) {
        traverseTree(root->child, 1);
        return;
    }

    findSubcategory(root->next, subcategory);
    findSubcategory(root->child, subcategory);
}

void filterBySubcategory(Node *root) {
    cout << "Masukkan subkategori yang ingin anda cari: ";
    string subcategory;
    cin >> subcategory;

    findSubcategory(root, subcategory);
}

void get_role(Node *root), admin_action(Node *root), admin_more_action(Node *root), customer_table_picker(), customer_action(Node *root), customer_more_action(Node *root);

int main(){
    //input kategori
    Node *root = newNode("MENU DAN HARGA", not_item, not_item);
	Node *n1 = addChild(root, "Roti dan Kue", not_item, not_item);
	Node *n2 = addChild(root, "Minuman", not_item, not_item);
	Node *n3 = addChild(root, "Makanan Utama", not_item, not_item);
    //input subkategori
	Node *n4 = addChild(n1, "Viennoiseries", not_item, not_item);
	Node *n5 = addChild(n1, "Pastry", not_item, not_item);
	Node *n6 = addChild(n1, "Bread", not_item, not_item);
	Node *n7 = addChild(n1, "Bun", not_item, not_item);
	Node *n8 = addChild(n2, "Juice", not_item, not_item);
	Node *n9 = addChild(n2, "Teh", not_item, not_item);
	Node *n10 = addChild(n2, "Kopi", not_item, not_item);
	Node *n11 = addChild(n3, "Salad", not_item, not_item);
	Node *n12 = addChild(n3, "Sup", not_item, not_item);
	Node *n13 = addChild(n3, "Sandwich", not_item, not_item);
	Node *n14 = addChild(n3, "Pasta", not_item, not_item);
    //input item
	Node *n15 = addChild(n4, "Croissant", 7, 24500);
	Node *n16 = addChild(n4, "Pain au Chocolate", 7, 26000);
	Node *n17 = addChild(n4, "Brioche", 7, 10000);
	Node *n18 = addChild(n5, "Eclair", 7, 7000);
	Node *n19 = addChild(n5, "Mille-feuille", 7, 11000);
	Node *n20 = addChild(n5, "Tarte Tatin", 7, 90000);
	Node *n21 = addChild(n5, "Tarlet", 7, 12000);
	Node *n22 = addChild(n6, "Baguette", 7, 13000);
	Node *n23 = addChild(n6, "Sourdough", 7, 30000);
	Node *n24 = addChild(n6, "Brioche Long", 7, 20000);
	Node *n25 = addChild(n7, "Bagel", 7, 9500);
	Node *n26 = addChild(n7, "Burger", 7, 18000);
	Node *n27 = addChild(n7, "Hotdog", 7, 16500);
	Node *n28 = addChild(n8, "Apple Juice", 7, 12000);
	Node *n29 = addChild(n8, "Orange Juice", 7, 10000);
	Node *n30 = addChild(n8, "Strawberry Juice", 7, 12000);
	Node *n31 = addChild(n9, "Earl Grey", 7, 11000);
	Node *n32 = addChild(n9, "Chamomile", 7, 7000);
	Node *n33 = addChild(n9, "English Breakfast", 7, 14000);
	Node *n34 = addChild(n9, "Darjeeling", 7, 13000);
	Node *n35 = addChild(n9, "Oolong", 7, 9000);
	Node *n36 = addChild(n9, "Matcha", 7, 15000);
	Node *n37 = addChild(n9, "Jasmine", 7, 12500);
    Node *n38 = addChild(n10, "Long Black", 7, 25000);
    Node *n39 = addChild(n10, "Cappucino", 7, 18000);
    Node *n40 = addChild(n10, "Latte", 7, 24000);
    Node *n41 = addChild(n10, "Espresso", 7, 24000);
    Node *n42 = addChild(n10, "Machiato", 7, 16000);
    Node *n43 = addChild(n10, "Piccolo", 7, 30000);
    Node *n44 = addChild(n11, " Caesar Salad", 7, 34000);
    Node *n45 = addChild(n11, " Caprese Salad", 7, 32000);
    Node *n46 = addChild(n11, " Waldorf Salad", 7, 28000);
    Node *n48 = addChild(n11, " Nicoise Salad", 7, 23000);
    Node *n49 = addChild(n12, " Pumpkin Soup", 7, 30000);
    Node *n50 = addChild(n12, " Mushroon Soup", 7, 22000);
    Node *n51 = addChild(n12, " Corn Soup ", 7, 18000);
    Node *n52 = addChild(n13, " Club Sandwich", 7, 38000);
    Node *n53 = addChild(n13, " Tuna Sandwich", 7, 33000);
    Node *n54 = addChild(n14, " Gnocchi", 7, 31000);
    Node *n55 = addChild(n14, " Aglio Olio", 7, 23000);
    Node *n56 = addChild(n14, " Lasagna", 7, 21500);
    Node *n57 = addChild(n14, " Fettucine", 7, 24000);
    Node *n58 = addChild(n14, " Carbonara", 7, 19000);

	
     //int budgetValue = 200000;
    //filterByMaxPrice(root, budgetValue);
	
     //searchMenu(root, "Latte");
	
    //synchronize meja
    for(int i=0; i<11; i++){
        cout << "Meja '" << meja[i] << "', kapasitas kursi : " << kursi[i] << endl;
    }

    //masuk alur user

    get_role(root);

    return 0;
}

void get_role(Node *root){
    int pilihan;
    // system("cls");

    cout << "===== PROGRAM KELOLA HeavenTerrace =====" << endl;
    cout << "1. Admin" << endl;
    cout << "2. Customer" << endl;
    cout << "Masuk sebagai\t: "; cin >> pilihan;

    enum option{ADMIN = 1, CUSTOMER};

    switch(pilihan){
        case ADMIN:
            int pilihan;

            cout << "Selamat datang kembali worker, ada perlu apa?" << endl;
            cout << "1. Tambah Menu" << endl;
            cout << "2. Pengurangan Menu" << endl;
            cout << "3. Edit Menu" << endl;
            cout << "4. Edit Harga" << endl;
            cout << "5. Kembali" << endl;
            cout << "pilihan : "; cin >> pilihan;

            enum option{TAMBAH = 1, KURANG, EDIT_MENU, EDIT_HARGA, BACK};

            switch (pilihan){
                case TAMBAH:
                //fungsi tambah disini
                    cout << "mau tambah apa?" << endl;
                    system("pause");
                    // admin_more_action(root);
                    break;

                case KURANG:
                //fungsi kurang disini
                    cout << "mau kurang apa?" << endl;
                    system("pause");
                    // admin_more_action(root);
                    break;

                case EDIT_MENU:
                //fungsi edit disini
                    cout << "mau edit menu apa?" << endl;
                    system("pause");
                    // admin_more_action(root);
                    break;

                case EDIT_HARGA:
                //fungsi edit disini
                    cout << "mau edit harga apa?" << endl;
                    system("pause");
                    // admin_more_action(root);
                    break;

                case BACK:
                    system ("cls");
                    get_role(root);
                    break;
                        
                default:
                    cout << "pilihan anda tidak tersedia, silakan pilih ulang.\n";
                    // admin_action(root);
                    break;
            }
                    break;

                case CUSTOMER:
                    customer_table_picker();
                    customer_action(root);
                    break;

                default:
                    cout << "Pilihan anda tidak tersedia, pilih yang sesuai.\n" << endl;
                    get_role(root);
            }
}

void admin_action(Node *root){
    
}

void admin_more_action(Node *root){
    char pil[1];
    int pilihan;
    cout << "masih ada perlu? (y/n)"; cin >> pil[0];
    if(pil[0] == 'y' || pil[0] == 'Y'){
        system("cls");
        admin_action(root);
    }else if(pil[0] == 'n' || pil[0] == 'N'){
        system ("cls");
        get_role(root);
    }else{
        cout << "pilihan tidak sesuai, silakan pilih ulang\n";
        admin_more_action(root);
    }
}

// void customer_table_picker(int jumlahKursi){
//     cout << "Welcome to HeavenTerrace!\n";
//     cout << "Kapasitas kursi yang anda butuhkan\t: "; cin >> jumlahKursi;
// }

void customer_action(Node *root){
    int pilihan;

    cout << "======= Selamat datang di HeavenTerrace =======" << endl;
    cout << "1. Tampilkan Menu" << endl;
    cout << "2. Cari Menu" << endl;
    cout << "3. Filter Kategori" << endl;
    cout << "4. Filter Subkategori" << endl;
    cout << "5. Filter Event" << endl;
    cout << "6. Filter Harga" << endl;
    cout << "7. Kembali" << endl;
    cout << "pilihan : "; cin >> pilihan;

    enum option{VIEW = 1, SEARCH, FILTER_KATEGORI, FILTER_SUBKATEGORI, FILTER_EVENT, FILTER_HARGA, BACK};

    switch (pilihan){
        case VIEW:
        //fungsi view disini

            menu_header(root);
            customer_more_action(root);
            break;

        case SEARCH:
            searchMenu(root);
            break;

        case FILTER_KATEGORI:
        //fungsi filter kategori disini
            cout << "(hasil filter)" << endl;
            system("pause");
            customer_more_action(root);
            break;

        case FILTER_SUBKATEGORI:
        filterBySubcategory(root);
            break;

        case FILTER_EVENT:
        //fungsi filter event disini
            cout << "(hasil filter)" << endl;
            system("pause");
            customer_more_action(root);
            break;

        case FILTER_HARGA:
	    int budget;
	    cout << "Masukkan budget Anda: ";
	    cin >> budget;
	    filterByMaxPrice(root, budget);
	    break;

        case BACK:
            system ("cls");
            get_role(root);
            break;
                
        default:
            cout << "pilihan anda tidak tersedia, silakan pilih ulang.\n";
            customer_action(root);
            break;
    }
}

void customer_more_action(Node *root){
    char pil[1];
    int pilihan;
    cout << "masih ada keperluan lain? (y/n)"; cin >> pil[0];
    if(pil[0] == 'y' || pil[0] == 'Y'){
        system("cls");
        customer_action(root);
    }else if(pil[0] == 'n' || pil[0] == 'N'){
        system ("cls");
        get_role(root);
    }else{
        cout << "pilihan tidak sesuai, silakan pilih ulang\n";
        customer_more_action(root);
    }
}

void assignTable(const int* kursi, const string* meja, int jumlahMeja, int jumlahKursi) {
    bool found = false;
    string mejaDipilih = ""; // Variabel untuk menyimpan nama meja yang dipilih

    // Mencari meja tunggal yang memenuhi jumlah kursi
    for (int i = 0; i < jumlahMeja; ++i) {
        if (kursi[i] >= jumlahKursi && isTableAvailable(i)) {
            mejaDipilih = meja[i];
            cout << "Meja yang diberikan: " << mejaDipilih << " dengan " << kursi[i] << " kursi.\n";
            found = true;
            break;
        }
    }

    // Mencoba menggabungkan meja jika tidak ada meja tunggal yang memenuhi
    if (!found) {
        for (int i = 0; i < jumlahMeja; ++i) {
            for (int j = i + 1; j < jumlahMeja; ++j) {
                if (kursi[i] + kursi[j] >= jumlahKursi && isTableAvailable(i) && isTableAvailable(j)) {
                    mejaDipilih = meja[i] + " dan " + meja[j];
                    cout << "Meja yang diberikan: " << mejaDipilih << " dengan total " << (kursi[i] + kursi[j]) << " kursi.\n";
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
    }

    // Update status meja yang dipilih
    if (found) {
        for (int i = 0; i < jumlahMeja; ++i) {
            if (meja[i] == mejaDipilih) {
                statusMeja[i] = true; // Menandai meja sebagai dipakai
                break;
            }
        }
    } else {
        cout << "Tidak ada kombinasi meja yang memenuhi jumlah kursi yang dibutuhkan.\n";
    }
}

// Fungsi untuk menandakan meja kembali tersedia
void releaseTable(string mejaDipilih) {
    for (int i = 0; i < 11; ++i) {
        if (meja[i] == mejaDipilih) {
            statusMeja[i] = false;
            break;
        }
    }

}

void customer_table_picker(){
    int person;
    cout << "Welcome to HeavenTerrace!\n";
    cout << "Kapasitas kursi yang anda butuhkan: "; 
    cin >> person;

    assignTable(kursi, meja, 11, person);
}

void initializeTableStatus() {
    for (int i = 0; i < 11; ++i) {
        statusMeja[i] = false; // Semua meja tersedia pada awalnya
    }
}

// Saat mengecek meja, tambahkan pemeriksaan status
bool isTableAvailable(int index) {
    return !statusMeja[index];
}
