#include<iostream>
using namespace std;

const int not_item = -1;

struct Node{
	string data;
    int harga;
    int stok;
	struct Node *next;
	struct Node *child;
};
struct Node *head;

struct Event{
    string event;
    string item;
    struct Event *next;
    struct Event *child;
};
void input_all(Node *root), FilterKategori(Node *root), FilterHarga(Node *root), FilterEvent(Node *root);
//menyimpan data menu dan harga
Node* newNode(string data, int stok, int harga){
	Node *newNode = new Node;
	newNode->next = newNode->child = NULL;
	newNode->data = data;
	newNode->stok = stok;
	newNode->harga = harga;
	return newNode;
}

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

// menampilkan data menu
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

//Pencarian Kategori Filter
void traverseFilter(Node *root, int level){

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
        traverseFilter(root->child, level + 1);

    if (root->next)
        traverseFilter(root->next, level);
}

void PencarianFilter(Node *root, string filter, int level){
    if (root == NULL)
        return;

    if (root->data == filter)
    {
		cout << "|-" << root->data << endl;
        traverseFilter(root->child, level);
        return;
    }

    if (root->child)
        PencarianFilter(root->child, filter, level + 1);

    if (root->next)
        PencarianFilter(root->next, filter, level);
}

//Filter Subkategori
void findSubcategory(Node* root, const string& subcategory, Node*& subcategoryNode) {
    if (root == nullptr) {
        return;
    }

    if (root->data == subcategory) {
        traverseTree(root->child, 1);
        subcategoryNode = root;
        return;
    }

    findSubcategory(root->next, subcategory, subcategoryNode);
    findSubcategory(root->child, subcategory, subcategoryNode);
}

void filterBySubcategory(Node* root) {
    cout << "Masukkan subkategori yang ingin anda cari: ";
    string subcategory;
    cin >> subcategory;

    Node* subcategoryNode = nullptr;
    findSubcategory(root, subcategory, subcategoryNode);

    if (subcategoryNode) {
        cout << "Subkategori tidak ditemukan.\n";
    } else {
        cout << "Subkategori tidak ditemukan.\n";
    }
}

//Filter harga
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

//FilterEvent
void traverseEvent(Node *root, int level){

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
        traverseEvent(root->child, level + 1);

    if (root->next)
        traverseEvent(root->next, level);
}

void PencarianEvent(Node *root, string event, int level){
    if (root == NULL)
        return;

    if (root->data == event)
    {
		cout << "|-" << root->data << endl;
        traverseEvent(root->child, level);
        return;
    }

    if (root->child)
        PencarianEvent(root->child, event, level + 1);

    if (root->next)
        PencarianEvent(root->next, event, level);
}

int main(){
    Node *root = newNode("MENU DAN HARGA", not_item, not_item);
    
    //Admin action
    input_all(root);
    menu_header(root);
	FilterKategori(root);
	//filterBySubcategory(root);
	//FilterHarga(root);
	//FilterEvent(root);
    return 0;
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
	Node *n15 = addChild(n4, "Croissant", 7, 15000);
	Node *n16 = addChild(n4, "Pain au Chocolate", 7, 15000);
	Node *n17 = addChild(n4, "Brioche", 7, 15000);
	Node *n18 = addChild(n5, "Eclair", 7, 15000);
	Node *n19 = addChild(n5, "Mille-feuille", 7, 15000);
	Node *n20 = addChild(n5, "Tarte Tatin", 7, 15000);
	Node *n21 = addChild(n5, "Tarlet", 7, 15000);
	Node *n22 = addChild(n6, "Baguette", 7, 15000);
	Node *n23 = addChild(n6, "Sourdough", 7, 15000);
	Node *n24 = addChild(n6, "Brioche Long", 7, 15000);
	Node *n25 = addChild(n7, "Bagel", 7, 15000);
	Node *n26 = addChild(n7, "Burger", 7, 15000);
	Node *n27 = addChild(n7, "Hotdog", 7, 15000);
	Node *n28 = addChild(n8, "Apple Juice", 7, 15000);
	Node *n29 = addChild(n8, "Orange Juice", 7, 15000);
	Node *n30 = addChild(n8, "Strawberry Juice", 7, 15000);
	Node *n31 = addChild(n9, "Earl Grey", 7, 15000);
	Node *n32 = addChild(n9, "Chamomile", 7, 15000);
	Node *n33 = addChild(n9, "English Breakfast", 7, 15000);
	Node *n34 = addChild(n9, "Darjeeling", 7, 15000);
	Node *n35 = addChild(n9, "Oolong", 7, 15000);
	Node *n36 = addChild(n9, "Matcha", 7, 15000);
	Node *n37 = addChild(n9, "Jasmine", 7, 15000);
    Node *n38 = addChild(n10, "Long Black", 7, 15000);
    Node *n39 = addChild(n10, "Cappucino", 7, 15000);
    Node *n40 = addChild(n10, "Latte", 7, 15000);
    Node *n41 = addChild(n10, "Espresso", 7, 15000);
    Node *n42 = addChild(n10, "Machiato", 7, 15000);
    Node *n43 = addChild(n10, "Piccolo", 7, 15000);
    Node *n44 = addChild(n11, " Caesar Salad", 7, 15000);
    Node *n45 = addChild(n11, " Caprese Salad", 7, 15000);
    Node *n46 = addChild(n11, " Waldorf Salad", 7, 15000);
    Node *n48 = addChild(n11, " Nicoise Salad", 7, 15000);
    Node *n49 = addChild(n12, " Pumpkin Soup", 7, 15000);
    Node *n50 = addChild(n12, " Mushroon Soup", 7, 15000);
    Node *n51 = addChild(n12, " Corn Soup ", 7, 15000);
    Node *n52 = addChild(n13, " Club Sandwich", 7, 15000);
    Node *n53 = addChild(n13, " Tuna Sandwich", 7, 15000);
    Node *n54 = addChild(n14, " Gnocchi", 7, 15000);
    Node *n55 = addChild(n14, " Aglio Olio", 7, 15000);
    Node *n56 = addChild(n14, " Lasagna", 7, 15000);
    Node *n57 = addChild(n14, " Fettucine", 7, 15000);
    Node *n58 = addChild(n14, " Carbonara", 7, 15000);
}

void FilterKategori(Node *root){
	string filter;
	cout << "Kategori yang ingin anda cari: ";
    getline(cin, filter);
    PencarianFilter(root, filter, 0);
}

void FilterHarga(Node *root){
	int budget;
	cout << "Masukkan budget Anda: ";
	cin >> budget;
	filterByMaxPrice(root, budget);
}

void FilterEvent(Node *root){
	int pilihan;
	string event;
    cout << "1. Breakfast \n2. Brunch \n3. Lunch \n4. Morning Coffe/Tea Time/Afternoon Coffe \n5. Dinner \n";
    cout << "pilih Event yang anda inginkan: "; 
	cin >> pilihan;

    //enum option {Breakfast = 1, Brunch, Lunch, Morning_Coffe, Dinner};

    switch (pilihan) {
        case 1: {
            string item1[4] = {"Bread", "Bun", "Minuman", "Sandwich"};
            for (int i = 0; i < 4; i++) {
                event = item1[i];
                PencarianEvent(root, event, 0);
            }
            break;
        }

        case 2: {
            string item2[] = {"Bread", "Bun", "Minuman", "Salad", "Sup", "Sandwich"};
            for (int i = 0; i < 7; i++) {
                event = item2[i];
                PencarianEvent(root, event, 0);
            }
            break;
        }

        case 3: {
            string item3[] = {"Pastry", "Minuman", "Makanan Utama"};
            for (int i = 0; i < 4; i++) {
                event = item3[i];
                PencarianEvent(root, event, 0);
            }
            break;
        }

        case 4: {
            string item4[] = {"Viennoiseries", "Pastry", "Minuman"};
            for (int i = 0; i < 4; i++) {
                event = item4[i];
                PencarianEvent(root, event, 0);
            }
            break;
        }

        case 5: {
            string item5[] = {"Pastry", "Minuman", "Makanan Utama"};
            for (int i = 0; i < 4; i++) {
                event = item5[i];
                PencarianEvent(root, event, 0);
            }
            break;
        }

        default:
            cout << "event tidak ditemukan.\n";
            break;
    }
}