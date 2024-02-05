#include <iostream>
#include <vector>
using namespace std;

const int MAX_SIZE = 100;

//kombinasi meja
struct TableCombination{
    vector<int> tables;
    int totalSeats;
};

//untuk mengisi slot data dengan keterangan bukan item
const int not_item = -1;

//node untuk item beserta datanya
struct Node{
    string data;
    int harga;
    int stok;
    Node* next;
    Node* child;
};

//define meja
struct Table{
    string id;
    int seats;
    bool status; // Status meja, true jika sedang digunakan
};

//deklarasi data meja beserta kapasitasnya
const int jumlahMeja = 11;
Table tables[jumlahMeja] = {
 {"1", 6, false}, {"2", 6, false}, {"3", 4, false}, {"4", 4, false},
 {"5", 4, false}, {"6", 2, false}, {"7", 2, false}, {"8", 2, false},
 {"9", 2, false}, {"Bar", 6, false}, {"Bar Tengah", 6, false}
};

// Struktur untuk menyimpan informasi pelanggan
struct Customer{
    int membershipLevel;
    TableCombination combination;
};

//antrian
struct PriorityQueue{
    Customer data[MAX_SIZE];
    int front, rear;
};

//kumpulan prototype
void initQueue(PriorityQueue& q) ,enqueue(PriorityQueue& q, int membershipLevel, TableCombination combination) ,dequeue(PriorityQueue& q),
     displayQueue(PriorityQueue q), ask_member_and_chair_needle(PriorityQueue& q), freeTable(PriorityQueue& q, string tableId),
     customerQueueHandler(int level, TableCombination combination), allocateOrEnqueue(PriorityQueue& q, int level, int people),
     input_all(Node *root), filterKat_Subkat(Node *root), filterHarga(Node *root), filterEvent(Node *root), traverseTree(Node *root, int level),
     display_menu(Node *root), traverseFilter(Node *root, int level), pencarianKat_subkat(Node *root, string filter, int level),
     filterByMaxPrice(Node *root, int budget), traverseEvent(Node *root, int level), modifyCategory(Node* root, const string& oldCategory, const string& newCategory),
     modifySubcategory(Node* root, const string& category, const string& oldSubcategory, const string& newSubcategory),
     modifyMenuItem(Node* root, const string& category, const string& subcategory, const string& oldItem, const string& newItem),
     deleteCategory(Node* root, string category), deleteSubcategory(Node* root, const string& subcategory), deleteMenuItem(Node* root, const string& item),
     bought_1by1(Node *root, string tujuan), modifyStock(Node *root, string tujuan, int newStock),
     modifyPrice(Node *root, string tujuan, int newPrice), cari_item(Node *root, string tujuan);

bool isEmpty(PriorityQueue q), isFull(PriorityQueue q), found;
     
TableCombination findBestCombination(int people);

Node* newNode(string data, int stok, int harga);
Node* addSibling(Node *n, string data, int stok, int harga);
Node* addChild(Node * n, string data, int stok, int harga);
Node* insertCategory(Node* root, const string& category);
Node* insertSubcategory(Node* root, const string& category, const string& subcategory);
Node* insertMenuItem(Node* root, const string& category, const string& subcategory, const string& item, int newStock, int newPrice);

int main(){
    cout << "UpperEast -\n";
    //deklarasi root menu
    Node *root = newNode("MENU DAN HARGA", not_item, not_item);

    //input semua data awal
    // input_all(root);

    //deklarasi antrian
    PriorityQueue queue;
    initQueue(queue);
    
    /*  Admin action (fitur admin) start dari sini ========

        command2/subprogram di bawah ini khusus merupakan fitur admin,
        bisa digunakan dengan cara menghilangkan comment pada masing-masing line
        SELAMAT MENCOBA!
        *status berhasil atau tidaknya aksi admin akan terlihat di terminal setelah program berjalan
        *admin juga memiliki 2 aksi pada terminal, yakni perubahan status pada meja dan tampilan status meja
    */

    //INSERT NEW

    //kategori
    // root = insertCategory(root, "Snack");

    //subkategori
    // insertSubcategory(root, "Snack", "Martabak");
    // insertSubcategory(root, "Snackz", "Martabak");

    //item beserta stok dan harga
    // insertMenuItem(root, "Snack", "Martabak", "Martabak Manis", 7, 18000);
    // insertMenuItem(root, "Minuman", "Juice", "Jus Terong Belanda", 7, 18000);

    //MODIFY

    //modify kategori
    //Old kategori -> New kategori
    // modifyCategory(root, "Roti dan Kue", "Bakery");
    // modifyCategory(root, "Minumanz", "Drinks");

    //modify subkategori
    //Kategori -> Old Subkategori -> New Subkategori
    // modifySubcategory(root, "Bakery", "Bread", "Roti");
    // modifySubcategory(root, "Bakery", "Breadz", "Roti");
    // modifySubcategory(root, "Bakeryz", "Bread", "Roti");

    //modify nama item
    //Kategori -> Subkategori -> Old item -> New item
    // modifyMenuItem(root, "Snack", "Martabak", "Martabak Manis", "Martabak Telor");
    // modifyMenuItem(root, "Snackz", "Martabak", "Martabak Manis", "Martabak Telor");
    // modifyMenuItem(root, "Snack", "Martabakz", "Martabak Manis", "Martabak Telor");
    // modifyMenuItem(root, "Snack", "Martabak", "Martabak Manisz", "Martabak Telor");

    //modify harga
    //nama item -> harga terbaru
    // modifyPrice(root, "Apple Juice", 99000);
    // modifyPrice(root, "Applez Juice", 99000);

    //modify stok
    //nama item -> stok terbaru
    // modifyStock(root, "Apple Juice", 9);
    // modifyStock(root, "Applez Juice", 9);

    //mengurangi stok satu per satu ketika ada pembelian
    // bought_1by1(root, "Apple Juice");
    // bought_1by1(root, "Applez Juice");

    // DELETE/MENGHAPUS

    //delete kategori
    // deleteCategory(root, "Minuman");
    // deleteCategory(root, "Minumanz");

    //delete subkategori
    // deleteSubcategory(root, "Pasta");
    // deleteSubcategory(root, "Pastaz");

    //delete item
    // deleteMenuItem(root, "Croissant");
    // deleteMenuItem(root, "Croissantz");
    
    //Customer action(fitur customer) start dari sini ===========
    // *kini fitur customer memiliki pemberitahuan juga jika ada aksi yang gagal (tujuan tidak ditemukan).
    
    int p;
    begin:
    system("pause");
    system("cls");
    cout << "=== SELAMAT DATANG DI UpperEast CAFFE ===\n";
    cout << "1. Masuk Meja (antri jika penuh)\n";
    cout << "2. Tampilkan Antrian Terurut\n";
    cout << "3. Tampilkan Semua Menu\t\n";
    cout << "4. Filter Berdasarkan Kategori/Subkategori\n";
    cout << "5. Filter Berdasarkan Event\n";
    cout << "6. Filter Berdasarkan budget\n";
    cout << "7. Cari Item Berdasarkan Nama\n";
    cout << "8. Menampilkan Status Meja berdasarkan ID [admin]\n";
    cout << "9. Kosongkan Meja berdasarkan ID [admin]\n";
    cout << "pilihan : "; cin >> p;

    if(p == 1){
        ask_member_and_chair_needle(queue);
        goto begin;
    }else if(p == 2){
        displayQueue(queue);
        goto begin;
    }else if(p == 3){
        display_menu(root);
        goto begin;
    }else if(p == 4){
        filterKat_Subkat(root);
        goto begin;
    }else if(p == 5){
        filterEvent(root);
        goto begin;
    }else if(p == 6){
        filterHarga(root);
        goto begin;
    }else if(p == 7){
        string tujuan;
        cout << "Item yang ingin dicari : "; cin.ignore(); getline(cin, tujuan);
        cari_item(root, tujuan);
        goto begin;
    }else if(p == 8){
        for(int i=0; i<11; i++){
            cout << "Meja '" << tables[i].id << "' : ";
            if(tables[i].status == true) cout << "terisi" << endl;
            else cout << "kosong" << endl;
        }
        goto begin;
    }else if(p == 9){
        string tableId;
        cout << "Masukkan ID Meja yang ingin dibebaskan: "; cin >> tableId;
        freeTable(queue, tableId);
        goto begin;
    }else{
        cout << "Pilihan tidak tersedia! Silakan pilih ulang.\n";
        goto begin;
    }
    return 0;
}

void allocateOrEnqueue(PriorityQueue& q, int level, int people){
    TableCombination combination = findBestCombination(people);
    if(!combination.tables.empty()){ // kalau ada meja yang tersedia
        cout << "Alokasi meja untuk " << people << " orang: ";
        for(int table : combination.tables){
            cout << "Meja " << tables[table - 1].id << ", ";
            tables[table - 1].status = true; // update status meja menjadi terpakai (true)
        }
        cout << "(Total kapasitas: " << combination.totalSeats << ")\n";
        customerQueueHandler(level, combination); // customer langsung masuk meja tanpa menambahkan ke queue
                                                  // saat meja terisi penuh, baru customer dimasukkan dalam queue
    }else{
        cout << "Tidak ada meja yang tersedia untuk " << people << " orang saat ini. Anda akan dimasukkan ke dalam queue.\n";
        if(isFull(q)){
            cout << "Maaf, antrian penuh.\n";
        }else{
            // perbarui combination untuk mencerminkan kebutuhan kursi aktual sebelum masuk ke queue
            combination.totalSeats = people; // update totalSeats dengan jumlah orang karena tidak ada kombinasi meja yang tersedia
            enqueue(q, level, combination);
        }
    }
}

void freeTable(PriorityQueue& q, string tableId){
    for(int i = 0; i < jumlahMeja; ++i){
        if(tables[i].id == tableId){
            tables[i].status = false;
            cout << "Meja " << tables[i].id << " telah dikosongkan.\n";
            break;
        }
    }

    // cek apakah ada pelanggan dalam queue yang bisa dialokasikan meja
    if(!isEmpty(q)){
        Customer frontCustomer = q.data[q.front]; // Ambil pelanggan di depan queue
        TableCombination combination = findBestCombination(frontCustomer.combination.totalSeats);
        if(!combination.tables.empty()){ // Jika ada kombinasi meja yang tersedia
            cout << "Mengalokasikan meja kepada pelanggan: Membership Level " << frontCustomer.membershipLevel << ", Kursi yang dibutuhkan: " << frontCustomer.combination.totalSeats << "\n";
            for(int tableIndex : combination.tables){
                tables[tableIndex - 1].status = true; // update status meja menjadi terpakai
                cout << "Meja " << tables[tableIndex - 1].id << " dialokasikan.\n";
            }
            dequeue(q); // mengeluarkan pelanggan dari queue setelah meja dialokasikan
        }else{
            cout << "Tidak ada kombinasi meja yang tersedia untuk pelanggan di depan queue.\n";
        }
    }
}

void initQueue(PriorityQueue& q){
    q.front = -1;
    q.rear = -1;
}

bool isEmpty(PriorityQueue q){
    return q.front == -1;
}

bool isFull(PriorityQueue q){
    return(q.rear + 1) % MAX_SIZE == q.front;
}

void enqueue(PriorityQueue& q, int membershipLevel, TableCombination combination){
    if(isFull(q)){
        cout << "Antrian Penuh." << endl;
        return;
    }

    if(isEmpty(q)){
        q.front = 0;
        q.rear = 0;
    }else{
        //naikkan rear terlebih dahulu untuk menyiapkan tempat bagi elemen baru
        q.rear = (q.rear + 1) % MAX_SIZE;
    }

    // tempatkan elemen baru di rear antrian
    q.data[q.rear].membershipLevel = membershipLevel;
    q.data[q.rear].combination = combination;

    // cari posisi yang tepat untuk elemen berdasarkan prioritas, jika ini bukan elemen pertama
    if(q.rear != q.front){
        int i = q.rear;
        int prev = (i - 1 + MAX_SIZE) % MAX_SIZE;
        while(i != q.front && q.data[prev].membershipLevel > membershipLevel){
            //tukar elemen untuk mengurutkan berdasarkan prioritas
            swap(q.data[i], q.data[prev]);
            i = prev;
            prev = (i - 1 + MAX_SIZE) % MAX_SIZE;
        }
    }
}

void dequeue(PriorityQueue& q){
    if(isEmpty(q)){
        cout << "Antrian Kosong." << endl;
        return;
    }

    if(q.front == q.rear){ //kalau antrian hanya memiliki satu elemen
        initQueue(q);
    }else{
        q.front = (q.front + 1) % MAX_SIZE;
    }
}

void displayQueue(PriorityQueue q){
    if(isEmpty(q)){
        cout << "Antrian kosong." << endl;
    }else{
        for(int level = 1; level <= 4; ++level){
            int i = q.front;
            do{
                if(q.data[i].membershipLevel == level){
                    cout << "Customer: Membership Level " << q.data[i].membershipLevel;
                    cout << " (Total kursi yang dibutuhkan: " << q.data[i].combination.totalSeats << ")\n";
                }
                i = (i + 1) % MAX_SIZE;
            } while(i != (q.rear + 1) % MAX_SIZE);
        }
    }
}

TableCombination findBestCombination(int people){
    int minSeats = 100;
    TableCombination bestCombination;

    for(int i = 0; i < (1 << jumlahMeja); ++i){
        int seats = 0;
        vector<int>currentCombination;
        bool isValidCombination = true;

        for(int j = 0; j < jumlahMeja; ++j){
            if((i & (1 << j)) && !tables[j].status){ // Hanya memilih meja yang belum terpakai
                seats += tables[j].seats;
                currentCombination.push_back(j + 1); // Simpan indeks meja + 1
            }else if((i & (1 << j)) && tables[j].status){
                isValidCombination = false; // Jika salah satu meja dalam kombinasi sudah terpakai, tandai kombinasi ini tidak valid
                break; // Keluar dari loop karena kombinasi ini tidak valid
            }
        }

        if(isValidCombination && seats >= people && seats < minSeats){
            minSeats = seats;
            bestCombination.tables = currentCombination;
            bestCombination.totalSeats = seats;
        }
    }

    return bestCombination;
}

void ask_member_and_chair_needle(PriorityQueue& q){
    int level, people;
    cout << "\nPilih level membership\n1. Platinum\n2. Gold\n3. Silver\n4. Non-Membership\nLevel Anda: ";
    cin >> level;

    if(level <= 0 || level > 4){
        cout << "Level membership tidak tersedia.\n";
        return;
    }

    cout << "Kapasitas kursi yang dibutuhkan: "; cin >> people;
    if(people > 44){
        cout << "Kapasitas kami tidak mencukupi kebutuhan kursi anda.\n";
        return;
    }
    if(people <=0){
        cout << "Jumlah kursi yang anda butuhkan tidak valid.\n";
        return;
    }

    allocateOrEnqueue(q, level, people);
}

void customerQueueHandler(int level, TableCombination combination){
    switch(level){
        case 1:
            cout << "Platinum customer. Meja tersedia, silakan masuk.\n";
            break;
        case 2:
            cout << "Gold customer. Meja tersedia, silakan masuk.\n";
            break;
        case 3:
            cout << "Silver customer. Meja tersedia, silakan masuk.\n";
            break;
        case 4:
            cout << "Non-Membership customer. Meja tersedia, silakan masuk.\n";
            break;
    }
}


//menyimpan data menu dan harga
Node* newNode(string data, int stok, int harga){
	Node *newNode = new Node;
	newNode->next = newNode->child = NULL;
	newNode->data = data;
	newNode->stok = stok;
	newNode->harga = harga;
	return newNode;
}

Node* addSibling(Node *n, string data, int stok, int harga){
	if(n == NULL)
		return NULL;

	while(n->next)
		n = n->next;

	return(n->next = newNode(data, stok, harga));
}

Node* addChild(Node * n, string data, int stok, int harga){
	if(n == NULL)
		return NULL;

	if(n->child)
		return addSibling(n->child, data, stok, harga);
	else
		return(n->child = newNode(data, stok, harga));
}

// menampilkan data menu
void traverseTree(Node *root, int level){
    if(root == NULL)
        return;

    for(int i = 0; i < level; ++i)
        cout << "    ";

    if(root -> harga <= not_item || root->stok <= not_item){
        cout << "|- " << root->data << "\n";
    }else{
    cout << "|- " << root->data;
    cout << ", stok : " << root->stok;
    cout << ", harga : Rp" << root->harga << ",-\n";
    }

    if(root->child)
        traverseTree(root->child, level + 1);

    if(root->next)
        traverseTree(root->next, level);
}

void display_menu(Node *root){
    cout <<"\n==================\n| ";
    cout << root->data << " |\n==================\n";
	root= root -> child;
    traverseTree(root, 1);
}

//Pencarian Kategori Filter
void traverseFilter(Node *root, int level){

    for(int i = 0; i < level; ++i)
        cout << "    ";

    if(root -> harga <= not_item || root->stok <= not_item){
        cout << "|- " << root->data << "\n";
    }else{
    cout << "|- " << root->data;
    cout << ", stok : " << root->stok;
    cout << ", harga : Rp" << root->harga << ",-\n";
    }

    if(root->child)
        traverseFilter(root->child, level + 1);

    if(root->next)
        traverseFilter(root->next, level);
    }

void pencarianKat_subkat(Node *root, string filter, int level){
    if(root == NULL){
        cout << "Menu kosong.\n";
        return;
    }

    if(root->data == filter){
		cout << "|- " << root->data << endl;
        found = false;
        traverseFilter(root->child, level);
        return;
    }

    if(root->child)
        pencarianKat_subkat(root->child, filter, level + 1);

    if(root->next)
        pencarianKat_subkat(root->next, filter, level);
}

//Filter harga
void filterByMaxPrice(Node *root, int budget){
    bool nothing = true;
    Node* category = root->child;

    while (category != nullptr){
         Node* sub = category->child;
         while (sub != nullptr){
             Node* currentItem = sub->child;
             while (currentItem != nullptr){
                 if(currentItem->harga >= -1 && currentItem->harga <= budget){
                     cout << "==> " << currentItem->data;
                     cout << ", Harga: Rp" << currentItem->harga << ",-" << endl;
                     nothing = false;
                 }
                 currentItem = currentItem->next;
             }
             sub = sub->next;
         }
         category = category->next;
    }
    if(nothing == true)
        cout << "Item dengan harga (dibawah) Rp" << budget << ",- tidak ditemukan.\n";
}

//filterEvent
void traverseEvent(Node *root, int level){

    for(int i = 0; i < level; ++i)
        cout << "    ";

    if(root -> harga == not_item){
        cout << "|- " << root->data << "\n";
    }else{
        cout << "|- " << root->data;
        cout << ", stok : " << root->stok;
        cout << ", harga : Rp" << root->harga << ",-\n";
    }

    if(root->child)
        traverseEvent(root->child, level + 1);

    if(root->next)
        traverseEvent(root->next, level);
}

void PencarianEvent(Node *root, string event, int level){
    if(root == NULL)
        return;

    if(root->data == event){
		cout << "|- " << root->data << endl;
        traverseEvent(root->child, level);
        return;
    }

    if(root->child)
        PencarianEvent(root->child, event, level + 1);

    if(root->next)
        PencarianEvent(root->next, event, level);
}

//Menginsert Kategori
Node* insertCategory(Node* root, const string& category){
    bool fail = true;
    if(root == nullptr){
        root = new Node;
        root->data = category;
        root->child = nullptr;
        root->next = nullptr;
        fail = false;
        cout << "Kategori '" << category << "' berhasil ditambahkan.\n";
        return root;
    }

    Node* newNode = new Node;
    newNode->data = category;
    newNode->child = nullptr;
    newNode->next = nullptr;
    newNode->harga = not_item;
    newNode->stok = not_item;

    if(root->child == nullptr){
        root->child = newNode;
        fail = false;
        cout << "Kategori '" << category << "' berhasil ditambahkan.\n";
    }else{
        Node* temp = root->child;
        while(temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = newNode;
        fail = false;
        cout << "Kategori '" << category << "' berhasil ditambahkan.\n";
    }
    if(fail == true)
    cout << "Gagal menambahkan kategori '" << category << "'.\n";
    return root;
}

//Menginsert Subkategori
Node* insertSubcategory(Node* root, const string& category, const string& subcategory){
    bool fail = true;    
    Node* categoryNode = root->child;

    while(categoryNode != nullptr && categoryNode->data != category){
        categoryNode = categoryNode->next;
    }

    if(categoryNode != nullptr){
        if(categoryNode->child == nullptr){
            categoryNode->child = newNode(subcategory, not_item, not_item);
            fail = false;
            cout << "Subkategori '" << subcategory << "' berhasil ditambahkan.\n";
        }else{
            Node* temp = categoryNode->child;
            while(temp->next != nullptr){
                temp = temp->next;
            }
            temp->next = newNode(subcategory, not_item, not_item);
            fail = false;
            cout << "Subkategori '" << subcategory << "' berhasil ditambahkan.\n";
        }
    }
    if(fail == true)
    cout << "Gagal menambahkan subkategori '" << subcategory << "'.\n";
    return root;
}

//Menginsert Menu Item
Node* insertMenuItem(Node* root, const string& category, const string& subcategory, const string& item, int newStock, int newPrice){
    bool fail = true;
    Node* categoryNode = root->child;

    while(categoryNode != nullptr && categoryNode->data != category){
        categoryNode = categoryNode->next;
    }

    if(categoryNode != nullptr){
        Node* subcategoryNode = categoryNode->child;

        while(subcategoryNode != nullptr && subcategoryNode->data != subcategory){
            subcategoryNode = subcategoryNode->next;
        }

        if(subcategoryNode != nullptr){
            if(subcategoryNode->child == nullptr){
                subcategoryNode->child = newNode(item, newStock, newPrice);
                fail = false;
                cout << "Item baru '" << item << "' berhasil ditambahkan.\n";
            }else{
                Node* temp = subcategoryNode->child;
                while(temp->next != nullptr){
                    temp = temp->next;
                }
                temp->next = newNode(item, newStock, newPrice);
                fail = false;
                cout << "Item '" << item << "' berhasil ditambahkan.\n";
            }
        }
    }
    if(fail == true)
    cout << "Gagal menambahkan item '" << item << "'.\n";
    return root;
}

//Modify Kategori
void modifyCategory(Node* root, const string& oldCategory, const string& newCategory){
    bool fail = true;
    Node* categoryNode = root->child;

    while(categoryNode != nullptr && categoryNode->data != oldCategory){
        categoryNode = categoryNode->next;
    }

    if(categoryNode != nullptr){
        categoryNode->data = newCategory;
        fail = false;
        cout << "Nama kategori '" << oldCategory << "' berhasil diperbarui menjadi '" << newCategory << "'.\n";
    }
    if(fail == true)
    cout << "Gagal memperbarui nama kategori '" << oldCategory << "'.\n";
}

//Modify Subkategori
void modifySubcategory(Node* root, const string& category, const string& oldSubcategory, const string& newSubcategory){
    bool fail = true;
    Node* categoryNode = root->child;

    while(categoryNode != nullptr && categoryNode->data != category){
        categoryNode = categoryNode->next;
    }

    if(categoryNode != nullptr){
        Node* subcategoryNode = categoryNode->child;

        while(subcategoryNode != nullptr && subcategoryNode->data != oldSubcategory){
            subcategoryNode = subcategoryNode->next;
        }

        if(subcategoryNode != nullptr){
            subcategoryNode->data = newSubcategory;
            fail = false;
            cout << "Nama subkategori '" << oldSubcategory << "' berhasil diperbarui menjadi '" << newSubcategory << "'.\n";
        }
    }
    if(fail == true)
    cout << "Gagal memperbarui nama subkategori '" << oldSubcategory << "'.\n";
}


//Modify menu item
void modifyMenuItem(Node* root, const string& category, const string& subcategory, const string& oldItem, const string& newItem){
    bool fail = true;
    Node* categoryNode = root->child;

    while(categoryNode != nullptr && categoryNode->data != category){
        categoryNode = categoryNode->next;
    }

    if(categoryNode != nullptr){
        Node* subcategoryNode = categoryNode->child;

        while(subcategoryNode != nullptr && subcategoryNode->data != subcategory){
            subcategoryNode = subcategoryNode->next;
        }

        if(subcategoryNode != nullptr){
            Node* menuItemNode = subcategoryNode->child;

            while(menuItemNode != nullptr && menuItemNode->data != oldItem){
                menuItemNode = menuItemNode->next;
            }

            if(menuItemNode != nullptr){
                menuItemNode->data = newItem;
                fail = false;
                cout << "Nama item '" << oldItem << "' berhasil diperbarui menjadi '" << newItem << "'.\n";
            }
        }
    }
    if(fail == true)
    cout << "Gagal memperbarui nama item '" << oldItem << "'.\n";
}

//Menghapus Kategori
void deleteCategory(Node* root, string category){
    bool fail = true;
    if(root == nullptr || root->child == nullptr){
        if(fail == true)
        cout << "Gagal menghapus kategori '" << category << "'.\n";
        return;
    }

    Node* prevCategory = nullptr;
    Node* Category = root->child;

    while(Category != nullptr && Category->data != category){
        if(Category != nullptr){
                if(prevCategory != nullptr){
                    prevCategory->next = Category->next;
                    delete Category;
                    fail = false;
                    cout << "Kategori '" << category << "' berhasil dihapus.\n";
                }else{
                    root->child = Category->next;
                    delete Category;
                    fail = false;
                    cout << "Kategori '" << category << "' berhasil dihapus.\n";
                }
        }
        prevCategory = Category;
        Category = Category->next;
    }

    if(fail == true)
    cout << "Gagal menghapus kategori '" << category << "'.\n";
}

//Menghapus subkategori
void deleteSubcategory(Node* root, const string& subcategory){
    bool fail = true;
    if(root == nullptr)
        return;

    Node* category = root->child;
    while(category != nullptr){
        Node* sub = category->child;
        Node* prevSub = nullptr;
        while(sub != nullptr){
            if(sub->data == subcategory){

                if(prevSub != nullptr){
                    prevSub->next = sub->next;
                    delete sub;
                    sub = prevSub->next;
                    fail = false;
                    cout << "Subkategori '" << subcategory << "' berhasil dihapus.\n";
                }else{
                    category->child = sub->next;
                    delete sub;
                    sub = category->child;
                    fail = false;
                    cout << "Subkategori '" << subcategory << "' berhasil dihapus.\n";
                }
            }else{
                prevSub = sub;
                sub = sub->next;
            }
        }
        category = category->next;
    }
    if(fail == true)
    cout << "Gagal menghapus Subkategori '" << subcategory << "'.\n";
}

//Menghapus Menu Item
void deleteMenuItem(Node* root, const string& item){
    bool fail = true;
    if(root == nullptr){
        return;
    }

    Node* category = root->child;
    while(category != nullptr){
        Node* sub = category->child;
        while(sub != nullptr){
            Node* prevItem = nullptr;
            Node* currentItem = sub->child;
            while(currentItem != nullptr){
                if(currentItem->data == item){
                    if(prevItem != nullptr){
                        prevItem->next = currentItem->next;
                        delete currentItem;
                        currentItem = prevItem->next;
                        fail = false;
                        cout << "'" << item << "' berhasil dihapus.\n";
                    }else{
                        sub->child = currentItem->next;
                        delete currentItem;
                        currentItem = sub->child;
                        fail = false;
                        cout << "'" << item << "' berhasil dihapus.\n";
                    }
                }else{
                    prevItem = currentItem;
                    currentItem = currentItem->next;
                }
            }
            sub = sub->next;
        }
        category = category->next;
    }
    if(fail == true)
    cout << "Gagal menghapus '" << item << "'.\n";
}


//data menu
 void input_all(Node *root){
    //input kategori
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
    Node *n44 = addChild(n11, "Caesar Salad", 7, 34000);
    Node *n45 = addChild(n11, "Caprese Salad", 7, 32000);
    Node *n46 = addChild(n11, "Waldorf Salad", 7, 28000);
    Node *n48 = addChild(n11, "Nicoise Salad", 7, 23000);
    Node *n49 = addChild(n12, "Pumpkin Soup", 7, 30000);
    Node *n50 = addChild(n12, "Mushroon Soup", 7, 22000);
    Node *n51 = addChild(n12, "Corn Soup ", 7, 18000);
    Node *n52 = addChild(n13, "Club Sandwich", 7, 38000);
    Node *n53 = addChild(n13, "Tuna Sandwich", 7, 33000);
    Node *n54 = addChild(n14, "Gnocchi", 7, 31000);
    Node *n55 = addChild(n14, "Aglio Olio", 7, 23000);
    Node *n56 = addChild(n14, "Lasagna", 7, 21500);
    Node *n57 = addChild(n14, "Fettucine", 7, 24000);
    Node *n58 = addChild(n14, "Carbonara", 7, 19000);
}

void filterKat_Subkat(Node *root){
    found = true;
	string filter;
	cout << "Kategori/subkategori yang ingin anda cari: "; cin.ignore(); getline(cin, filter);
    pencarianKat_subkat(root, filter, 0);
    if(found == true)
    cout << "Kategori/Subkategori '" << filter << "' tidak ditemukan.\n";
}

void filterHarga(Node *root){
	int budget;
	cout << "\nMasukkan budget Anda : Rp"; cin >> budget;
	filterByMaxPrice(root, budget);
}

void filterEvent(Node *root){
	int pilihan;
	string event;
    cout << "\n=== Event (rekomendasi waktu) pembelian ===\n";
    cout << "1. Breakfast \n2. Brunch \n3. Lunch \n4. Morning Coffe/Tea Time/Afternoon Coffe \n5. Dinner \n";
    cout << "pilih Event yang anda inginkan: "; cin >> pilihan;

    enum option{Breakfast = 1, Brunch, Lunch, Morning_Coffe, Dinner};

    switch(pilihan){
        case Breakfast:{
            string item1[4] ={"Bread", "Bun", "Minuman", "Sandwich"};
            for(int i = 0; i < 4; i++){
                event = item1[i];
                PencarianEvent(root, event, 0);
            }
            break;
        }

        case Brunch:{
            string item2[] ={"Bread", "Bun", "Minuman", "Salad", "Sup", "Sandwich"};
            for(int i = 0; i < 6; i++){
                event = item2[i];
                PencarianEvent(root, event, 0);
            }
            break;
        }

        case Lunch:{
            string item3[] ={"Pastry", "Minuman", "Makanan Utama"};
            for(int i = 0; i < 3; i++){
                event = item3[i];
                PencarianEvent(root, event, 0);
            }
            break;
        }

        case Morning_Coffe:{
            string item4[] ={"Viennoiseries", "Pastry", "Minuman"};
            for(int i = 0; i < 3; i++){
                event = item4[i];
                PencarianEvent(root, event, 0);
            }
            break;
        }

        case Dinner:{
            string item5[] ={"Pastry", "Minuman", "Makanan Utama"};
            for(int i = 0; i < 3; i++){
                event = item5[i];
                PencarianEvent(root, event, 0);
            }
            break;
        }

        default:{
            cout << "pilihan tidak sesuai! ";
            cout << "Silakan pilih ulang.\n";
            filterEvent(root);
            break;
        }
    }
}

void bought_1by1(Node *root, string tujuan){
    Node* category = root->child;
    while (category != nullptr){
        Node* sub = category->child;
        while (sub != nullptr){
            Node* currentItem = sub->child;
            while (currentItem != nullptr){
                if(currentItem->data == tujuan){
                    currentItem->stok -= 1;
                    cout << "Stok item '" << tujuan << "' telah berkurang satu.\n";
                    return;
                }
                currentItem = currentItem->next;
            }
            sub = sub->next;
        }
        category = category->next;
    }
    cout << "Item '" << tujuan << "' tidak ditemukan.\n";
}

void modifyStock(Node *root, string tujuan, int newStock){
    Node* category = root->child;
    while (category != nullptr){
        Node* sub = category->child;
        while (sub != nullptr){
            Node* currentItem = sub->child;
            while (currentItem != nullptr){
                if(currentItem->data == tujuan){
                    currentItem->stok = newStock;
                    cout << "Stok item '" << tujuan << "' telah diupdate menjadi " << newStock << ".\n";
                    return;
                }
                currentItem = currentItem->next;
            }
            sub = sub->next;
        }
        category = category->next;
    }
    cout << "Gagal memperbarui jumlah stok '" << tujuan << "'.\n";
}

void modifyPrice(Node *root, string tujuan, int newPrice){
    Node* category = root->child;
    while (category != nullptr){
        Node* sub = category->child;
        while (sub != nullptr){
            Node* currentItem = sub->child;
            while (currentItem != nullptr){
                if(currentItem->data == tujuan){
                    currentItem->harga = newPrice;
                    cout << "Harga item '" << tujuan << "' telah diupdate menjadi Rp" << newPrice << ",-.\n";
                    return;
                }
                currentItem = currentItem->next;
            }
            sub = sub->next;
        }
        category = category->next;
    }
    cout << "Gagal memperbarui nominal harga '" << tujuan << "'.\n";
}

void cari_item(Node *root, string tujuan){
    if(root == NULL)
        return;

    Node* category = root->child;
    while (category != nullptr){
        Node* sub = category->child;
        while (sub != nullptr){
            Node* currentItem = sub->child;
            while (currentItem != nullptr){
                if(currentItem->data == tujuan){
                    cout << "Item ditemukan!\n";
                    cout << "Nama: " << currentItem->data;
                    cout << ", Stok: " << currentItem->stok;
                    cout << ", Harga: Rp" << currentItem->harga << ",-\n";
                    return;
                }
                currentItem = currentItem->next;
            }
            sub = sub->next;
        }
        category = category->next;
    }
    cout << "Item '" << tujuan << "' tidak ditemukan.\n";
}