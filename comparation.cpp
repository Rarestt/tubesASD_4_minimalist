#include <iostream>
#include <vector>
using namespace std;

const int MAX_SIZE = 100;

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

//deklarasi data meja beserta kapasitasnya
const int jumlahMeja = 11;
int jumlahKursi;
string meja[] ={"1", "2", "3", "4", "5", "6", "7", "8", "9", "Bar", "Bar Tengah"};
int kursi[] ={6, 6, 4, 4, 4, 2, 2, 2, 2, 6, 6};
bool statusMeja[11];

// Struktur untuk menyimpan informasi pelanggan
struct Customer{
    int membershipLevel;
    TableCombination combination;
};

struct PriorityQueue{
    Customer data[MAX_SIZE];
    int front, rear;
};

//kumpulan prototype
void initQueue(PriorityQueue& q);
bool isEmpty(PriorityQueue q);
bool isFull(PriorityQueue q);
void enqueue(PriorityQueue& q, int membershipLevel, TableCombination combination);
void dequeue(PriorityQueue& q);
void displayQueue(PriorityQueue q);
TableCombination findBestCombination(int people);
void input_kebutuhan_kursi(int level, PriorityQueue& q);
void ask_member_and_chair_needle(PriorityQueue& q);
void customerQueueHandler(int level, TableCombination combination);
void input_all(Node *root), filterKat_Subkat(Node *root), filterHarga(Node *root), filterEvent(Node *root), traverseTree(Node *root, int level),
     display_menu(Node *root), traverseFilter(Node *root, int level), pencarianKat_subkat(Node *root, string filter, int level),
     filterByMaxPrice(Node *root, int budget), traverseEvent(Node *root, int level), modifyCategory(Node* root, const string& oldCategory, const string& newCategory),
     modifySubcategory(Node* root, const string& category, const string& oldSubcategory, const string& newSubcategory),
     modifyMenuItem(Node* root, const string& category, const string& subcategory, const string& oldItem, const string& newItem),
     deleteCategory(Node* root, string category), deleteSubcategory(Node* root, const string& subcategory), deleteMenuItem(Node* root, const string& item),
     bought_1by1(Node *root, string tujuan), modifyStock(Node *root, string tujuan, int newStock),
     modifyPrice(Node *root, string tujuan, int newPrice), cari_item(Node *root, string tujuan);

Node* newNode(string data, int stok, int harga);
Node* addSibling(Node *n, string data, int stok, int harga);
Node* addChild(Node * n, string data, int stok, int harga);
Node* insertCategory(Node* root, const string& category);
Node* insertSubcategory(Node* root, const string& category, const string& subcategory);
Node* insertMenuItem(Node* root, const string& category, const string& subcategory, const string& item, int newStock, int newPrice);

int main(){
    cout << "UpperEast - ";
    int p;
    //deklarasi root menu
    Node *root = newNode("MENU DAN HARGA", not_item, not_item);

    input_all(root);
    PriorityQueue queue;
    initQueue(queue);
    
    /*  Admin action(fitur admin) start dari sini ========

        command2/subprogram di bawah ini khusus merupakan fitur admin,
        bisa digunakan dengan cara menghilangkan comment pada masing2 line
        SELAMAT MENCOBA!
    */

    //INSERT NEW

    //kategori
    root = insertCategory(root, "Snack");

    //subkategori
    insertSubcategory(root, "Snack", "Martabak");

    //item beserta stok dan harga
    insertMenuItem(root, "Snack", "Martabak", "Martabak Manis", 7, 18000);

    //MODIFY

    //modify kategori
    //Old kategori -> New kategori
    modifyCategory(root, "Roti dan Kue", "Bakery");

    //modify subkategori
    //Kategori -> Old Subkategori -> New Subkategori
    modifySubcategory(root, "Bakery", "Bread", "Roti");

    //modify nama item
    //Kategori -> Subkategori -> Old item -> New item
    modifyMenuItem(root, "Snack", "Martabak", "Martabak Manis", "Martabak Telor");

    //modify harga
    //nama item -> harga terbaru
    modifyPrice(root, "Apple Juice", 99000);

    //modify stok
    //nama item -> stok terbaru
    modifyStock(root, "Apple Juice", 9);

    //mengurangi stok satu per satu ketika ada pembelian
    bought_1by1(root, "Apple Juice");

    // DELETE/MENGHAPUS
    deleteCategory(root, "Minuman");
    deleteSubcategory(root, "Pasta");
    deleteMenuItem(root, "Croissant");
    
    //menampilkan nama dan kapasitas kursi tiap meja(opsional)
    // for(int i=0; i<11; i++){
    //     cout << "Meja '" << meja[i] << "', kapasitas kursi : " << kursi[i] << endl;
    // }

    //Customer action(fitur customer) start dari sini ===========
    begin:
    system("pause");
    system("cls");
    cout << "=== SELAMAT DATANG DI UpperEast CAFFE ===\n";
    cout << "1. Masuk Antrian\n";
    cout << "2. Tampilkan Antrian Tersortir\n";
    cout << "3. Tampilkan Semua Menu\n";
    cout << "4. Filter Berdasarkan Kategori/Subkategori\n";
    cout << "5. Filter Berdasarkan Event\n";
    cout << "6. Filter Berdasarkan Harga(maximal budget)\n";
    cout << "7. Cari Item Berdasarkan Nama\n";
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
    }else{
        cout << "Pilihan tidak tersedia! Silakan pilih ulang.\n";
        goto begin;
    }


    return 0;
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
    } else{
        if(isEmpty(q)){
            q.front = 0;
            q.rear = 0;
            q.data[q.rear].membershipLevel = membershipLevel;
            q.data[q.rear].combination = combination;
        } else{
            q.rear =(q.rear + 1) % MAX_SIZE;
            q.data[q.rear].membershipLevel = membershipLevel;
            q.data[q.rear].combination = combination;
        }
    }
}


void dequeue(PriorityQueue& q){
    if(isEmpty(q)){
        cout << "Antrian Kosong." << endl;
    } else if(q.front == q.rear){
        initQueue(q);
    } else{
        // dequeue customer
        q.front =(q.front + 1) % MAX_SIZE;
        // cari meja yang tersedia berikutnya
        int nextTable = -1;
        for(int i = 0; i < jumlahMeja; ++i){
            if(!statusMeja[i]){
                nextTable = i;
                break;
            }
        }
        if(nextTable != -1){
            // perbarui status meja
            statusMeja[nextTable] = true;
            // memindahkan customer ke meja selanjutnya yang tersedia
            q.data[q.front].combination.tables.clear();
            q.data[q.front].combination.tables.push_back(nextTable + 1);
        } else{
            cout << "Meja penuh." << endl;
        }
    }
}

void displayQueue(PriorityQueue q){
    if(isEmpty(q)){
        cout << "Antrian kosong." << endl;
    } else{
        for(int level = 1; level <= 4; ++level){
            int i = q.front;
            do{
                if(q.data[i].membershipLevel == level){
                    cout << "Customer: Membership Level " << q.data[i].membershipLevel << ", Kombinasi meja yang didapat: ";
                    for(int table : q.data[i].combination.tables){
                        cout << "Meja " << table << " ";
                    }
                    cout << "(Total kursi yang dibutuhkan: " << q.data[i].combination.totalSeats << ")\n";
                }
                i =(i + 1) % MAX_SIZE;
            } while(i !=(q.rear + 1) % MAX_SIZE);
        }
    }
}


TableCombination findBestCombination(int people){
    int minSeats = 100;
    TableCombination bestCombination;

    for(int i = 0; i <(1 << jumlahMeja); ++i){
        int seats = 0;
        vector<int> currentCombination;

        for(int k = 0; k < jumlahMeja; ++k){
            statusMeja[k] = false;
        }

        for(int j = 0; j < jumlahMeja; ++j){
            if(i &(1 << j)){
                seats += kursi[j];
                currentCombination.push_back(j + 1);
                statusMeja[j] = true;
            }
        }

        if(seats >= people && seats < minSeats){
            minSeats = seats;
            bestCombination.tables = currentCombination;
            bestCombination.totalSeats = seats;
        }
    }

    return bestCombination;
}

void input_kebutuhan_kursi(int level, PriorityQueue& q){
    int people;
    if(level <= 0 || level >= 5){
        cout << "Level membership tidak tersedia, silakan piih ulang\n";
        ask_member_and_chair_needle(q);
    }
    cout << "kapasitas kursi yang dibutuhkan : ";
    cin >> people;

    TableCombination combination = findBestCombination(people);

    if(!combination.tables.empty()){
        cout << "Meja terbaik untuk " << people << " orang: ";
        for(int table : combination.tables){
            cout << "Meja " << meja[table - 1] << " ";
        }
        cout << "(Total kapasitas: " << combination.totalSeats << ")\n";

        enqueue(q, level, combination);
        customerQueueHandler(level, combination);  // Add the declaration
    } else{
        cout << "Tidak ada kombinasi meja yang mencukupi.\n";
    }
}

void ask_member_and_chair_needle(PriorityQueue& q){
    int level;
    cout << "\nPilih level membership\n1. Platinum\n2. Gold\n3. Silver\n4. Non-Membership\nlevel anda : ";
    cin >> level;
    input_kebutuhan_kursi(level, q);
}

void customerQueueHandler(int level, TableCombination combination){
    switch(level){
        case 1:
            cout << "Platinum customer, mohon tunggu.\n";
            break;
        case 2:
            cout << "Gold customer, mohon tunggu.\n";
            break;
        case 3:
            cout << "Silver customer, mohon tunggu.\n";
            break;
        case 4:
            cout << "Non-Membership customer, mohon tunggu.\n";
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
        cout << "|-" << root->data << "\n";
    } else{
    cout << "|-" << root->data;
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
        cout << "|-" << root->data << "\n";
    } else{
    cout << "|-" << root->data;
    cout << ", stok : " << root->stok;
    cout << ", harga : Rp" << root->harga << ",-\n";
    }

    if(root->child)
        traverseFilter(root->child, level + 1);

    if(root->next)
        traverseFilter(root->next, level);
    }

void pencarianKat_subkat(Node *root, string filter, int level){
    if(root == NULL)
        return;

    if(root->data == filter)
   {
		cout << "|-" << root->data << endl;
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
    if(root == nullptr){
        return;
    }

    if(root->harga != -1 && root->harga <= budget){
        cout << "Item: " << root->data;
        cout << ", Harga: Rp" << root->harga << ",-" << endl;
    }

    filterByMaxPrice(root->child, budget);

    filterByMaxPrice(root->next, budget);

}

//filterEvent
void traverseEvent(Node *root, int level){

    for(int i = 0; i < level; ++i)
        cout << "    ";

    if(root -> harga == not_item){
        cout << "|-" << root->data << "\n";
    } else{
    cout << "|-" << root->data;
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

    if(root->data == event)
   {
		cout << "|-" << root->data << endl;
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
    if(root == nullptr){
        root = new Node;
        root->data = category;
        root->child = nullptr;
        root->next = nullptr;
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
    } else{
        Node* temp = root->child;
        while(temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = newNode;
    }

    return root;
}

//Menginsert Subkategori
Node* insertSubcategory(Node* root, const string& category, const string& subcategory){
    Node* categoryNode = root->child;

    while(categoryNode != nullptr && categoryNode->data != category){
        categoryNode = categoryNode->next;
    }

    if(categoryNode != nullptr){
        if(categoryNode->child == nullptr){
            categoryNode->child = newNode(subcategory, not_item, not_item);
        } else{
            Node* temp = categoryNode->child;
            while(temp->next != nullptr){
                temp = temp->next;
            }
            temp->next = newNode(subcategory, not_item, not_item);
        }
    }

    return root;
}

//Menginsert Menu Item
Node* insertMenuItem(Node* root, const string& category, const string& subcategory, const string& item, int newStock, int newPrice){
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
            } else{
                Node* temp = subcategoryNode->child;
                while(temp->next != nullptr){
                    temp = temp->next;
                }
                temp->next = newNode(item, not_item, not_item);
            }
        }
    }

    return root;
}

//Modify Kategori
void modifyCategory(Node* root, const string& oldCategory, const string& newCategory){
    Node* categoryNode = root->child;

    while(categoryNode != nullptr && categoryNode->data != oldCategory){
        categoryNode = categoryNode->next;
    }

    if(categoryNode != nullptr){
        categoryNode->data = newCategory;
    }
}

//Modify Subkategori
void modifySubcategory(Node* root, const string& category, const string& oldSubcategory, const string& newSubcategory){
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
        }
    }
}


//Modify menu item
void modifyMenuItem(Node* root, const string& category, const string& subcategory, const string& oldItem, const string& newItem){
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
            }
        }
    }
}

//Menghapus Kategori
void deleteCategory(Node* root, string category){
    if(root == nullptr || root->child == nullptr){
        return;
    }

    Node* prevCategory = nullptr;
    Node* Category = root->child;

    while(Category != nullptr && Category->data != category){
        prevCategory = Category;
        Category = Category->next;
    }

    if(Category != nullptr){
        if(prevCategory != nullptr){
            prevCategory->next = Category->next;
            delete Category;
        } else{
            root->child = Category->next;
            delete Category;
        }
    }
}

//Menghapus subkategori
void deleteSubcategory(Node* root, const string& subcategory){
    if(root == nullptr){
        return;
    }

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
                } else{
                    category->child = sub->next;
                    delete sub;
                    sub = category->child;
                }
            } else{
                prevSub = sub;
                sub = sub->next;
            }
        }
        category = category->next;
    }
}

//Menghapus Menu Item
void deleteMenuItem(Node* root, const string& item){
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
                    } else{
                        sub->child = currentItem->next;
                        delete currentItem;
                        currentItem = sub->child;
                    }
                } else{
                    prevItem = currentItem;
                    currentItem = currentItem->next;
                }
            }
            sub = sub->next;
        }
        category = category->next;
    }
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
}

void filterKat_Subkat(Node *root){
	string filter;
	cout << "Kategori/subkategori yang ingin anda cari: "; cin.ignore(); getline(cin, filter);
    pencarianKat_subkat(root, filter, 0);
}

void filterHarga(Node *root){
	int budget;
	cout << "\nMasukkan budget Anda : Rp";
	cin >> budget;
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
    if(root == NULL)
        return;

    if(root->data == tujuan){
        root->stok -= 1;
        return;
    }

    if(root->child)
        bought_1by1(root->child, tujuan);

    if(root->next)
        bought_1by1(root->next, tujuan);
}

void modifyStock(Node *root, string tujuan, int newStock){
    if(root == NULL)
        return;

    if(root->data == tujuan){
        root->stok = newStock;
        return;
    }

    if(root->child)
        modifyStock(root->child, tujuan, newStock);

    if(root->next)
        modifyStock(root->next, tujuan, newStock);
}

void modifyPrice(Node *root, string tujuan, int newPrice){
    if(root == NULL)
        return;

    if(root->data == tujuan){
        root->harga = newPrice;
        return;
    }

    if(root->child)
        modifyPrice(root->child, tujuan, newPrice);

    if(root->next)
        modifyPrice(root->next, tujuan, newPrice);
}

void cari_item(Node *root, string tujuan){
    if(root == NULL)
        return;

    if(root->data == tujuan){
        cout << "Item ditemukan!\n";
        if(root->harga >= not_item && root->stok >= not_item)
        cout << root->data << ", dengan stok : " << root->stok << " dan harga : Rp" << root->harga << ",-\n";
        return;
    }

    if(root->child)
        cari_item(root->child, tujuan);

    if(root->next)
        cari_item(root->next, tujuan);
}