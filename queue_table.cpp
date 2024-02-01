#include <iostream>
#include <vector>
using namespace std;

const int MAX_SIZE = 100;

struct TableCombination{
    vector<int> tables;
    int totalSeats;
};

struct Table {
    string id;
    int seats;
    bool status; // Status meja, true jika sedang digunakan
};

// Array of struct meja
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

struct PriorityQueue{
    Customer data[MAX_SIZE];
    int front, rear;
};

//kumpulan prototype
void initQueue(PriorityQueue& q);
bool isEmpty(PriorityQueue q);
bool isFull(PriorityQueue q);
void allocateOrEnqueue(int level, PriorityQueue& q, int people);
void freeTable(PriorityQueue& q, string tableId);
void enqueue(PriorityQueue& q, int membershipLevel, TableCombination combination);
void dequeue(PriorityQueue& q);
void displayQueue(PriorityQueue q);
TableCombination findBestCombination(int people);
void input_kebutuhan_kursi(int level, PriorityQueue& q);
void ask_member_and_chair_needle(PriorityQueue& q);
void customerQueueHandler(int level, TableCombination combination);

int main(){
    cout << "UpperEast - ";
    int p;

    PriorityQueue queue;
    initQueue(queue);

    //Customer action(fitur customer) start dari sini ===========
    begin:
    system("pause");
    system("cls");
    cout << "=== SELAMAT DATANG DI UpperEast CAFFE ===\n";
    cout << "1. Masuk Antrian\n";
    cout << "2. Tampilkan Antrian Tersortir\n";
    cout << "3. Kosongkan Meja\n";
    cout << "pilihan : "; cin >> p;

    if(p == 1){
        ask_member_and_chair_needle(queue);
        goto begin;
    }else if(p == 2){
        displayQueue(queue);
        goto begin;
    }else if(p == 3){
        string tableId;
        cout << "Masukkan ID Meja yang ingin dibebaskan: ";
        cin >> tableId;
        freeTable(queue, tableId);
        goto begin;
    }else{
        cout << "Pilihan tidak tersedia! Silakan pilih ulang.\n";
        goto begin;
    }

    return 0;
}

void allocateOrEnqueue(PriorityQueue& q, int level, int people) {
    TableCombination combination = findBestCombination(people);
    if (!combination.tables.empty()) { // kalau ada meja yang tersedia
        cout << "Alokasi meja untuk " << people << " orang: ";
        for (int table : combination.tables) {
            cout << "Meja " << tables[table - 1].id << ", ";
            tables[table - 1].status = true; // update status meja menjadi terpakai (true)
        }
        cout << "(Total kapasitas: " << combination.totalSeats << ")\n";
        customerQueueHandler(level, combination); // langsung aja tangani pelanggan tanpa menambahkan ke queue
    // gada meja? masukkin ke queue
    } else {
        cout << "Tidak ada meja yang tersedia untuk " << people << " orang saat ini. Anda akan dimasukkan ke dalam queue.\n";
        if (isFull(q)) {
            cout << "Maaf, antrian penuh.\n";
        } else {
            // perbarui combination untuk mencerminkan kebutuhan kursi aktual sebelum masuk ke queue
            combination.totalSeats = people; // update totalSeats dengan jumlah orang karena tidak ada kombinasi meja yang tersedia
            enqueue(q, level, combination);
        }
    }
}

void freeTable(PriorityQueue& q, string tableId) {
    for (int i = 0; i < jumlahMeja; ++i) {
        if (tables[i].id == tableId) {
            tables[i].status = false;
            cout << "Meja " << tables[i].id << " telah dikosongkan.\n";
            break;
        }
    }

    // cek apakah ada pelanggan dalam queue yang bisa dialokasikan meja
    if (!isEmpty(q)) {
        Customer frontCustomer = q.data[q.front]; // Ambil pelanggan di depan queue
        TableCombination combination = findBestCombination(frontCustomer.combination.totalSeats);
        if (!combination.tables.empty()) { // Jika ada kombinasi meja yang tersedia
            cout << "Mengalokasikan meja kepada pelanggan: Membership Level " << frontCustomer.membershipLevel << ", Kursi yang dibutuhkan: " << frontCustomer.combination.totalSeats << "\n";
            for (int tableIndex : combination.tables) {
                tables[tableIndex - 1].status = true; // update status meja menjadi terpakai
                cout << "Meja " << tables[tableIndex - 1].id << " dialokasikan.\n";
            }
            dequeue(q); // mengeluarkan pelanggan dari queue setelah meja dialokasikan
        } else {
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

void enqueue(PriorityQueue& q, int membershipLevel, TableCombination combination) {
    if (isFull(q)) {
        cout << "Antrian Penuh." << endl;
        return;
    }

    if (isEmpty(q)) {
        q.front = 0;
        q.rear = 0;
    } else {
        //naikkan rear terlebih dahulu untuk menyiapkan tempat bagi elemen baru
        q.rear = (q.rear + 1) % MAX_SIZE;
    }

    // tempatkan elemen baru di rear antrian
    q.data[q.rear].membershipLevel = membershipLevel;
    q.data[q.rear].combination = combination;

    // cari posisi yang tepat untuk elemen berdasarkan prioritas, jika ini bukan elemen pertama
    if (q.rear != q.front) {
        int i = q.rear;
        int prev = (i - 1 + MAX_SIZE) % MAX_SIZE;
        while (i != q.front && q.data[prev].membershipLevel > membershipLevel) {
            //tukar elemen untuk mengurutkan berdasarkan prioritas
            swap(q.data[i], q.data[prev]);
            i = prev;
            prev = (i - 1 + MAX_SIZE) % MAX_SIZE;
        }
    }
}

void dequeue(PriorityQueue& q) {
    if (isEmpty(q)) {
        cout << "Antrian Kosong." << endl;
        return;
    }

    if (q.front == q.rear) { //kalau antrian hanya memiliki satu elemen
        initQueue(q);
    } else {
        q.front = (q.front + 1) % MAX_SIZE;
    }
}

void displayQueue(PriorityQueue q) {
    if (isEmpty(q)) {
        cout << "Antrian kosong." << endl;
    } else {
        for (int level = 1; level <= 4; ++level) {
            int i = q.front;
            do {
                if (q.data[i].membershipLevel == level) {
                    cout << "Customer: Membership Level " << q.data[i].membershipLevel << ", Kombinasi meja yang didapat: ";
                    for (int tableIndex : q.data[i].combination.tables) {
                        cout << "Meja " << tables[tableIndex - 1].id << " ";
                    }
                    cout << "(Total kursi yang dibutuhkan: " << q.data[i].combination.totalSeats << ")\n";
                }
                i = (i + 1) % MAX_SIZE;
            } while (i != (q.rear + 1) % MAX_SIZE);
        }
    }
}

TableCombination findBestCombination(int people) {
    int minSeats = 100;
    TableCombination bestCombination;

    for (int i = 0; i < (1 << jumlahMeja); ++i) {
        int seats = 0;
        vector<int> currentCombination;
        bool isValidCombination = true;

        for (int j = 0; j < jumlahMeja; ++j) {
            if ((i & (1 << j)) && !tables[j].status) { // Hanya memilih meja yang belum terpakai
                seats += tables[j].seats;
                currentCombination.push_back(j + 1); // Simpan indeks meja + 1
            } else if ((i & (1 << j)) && tables[j].status) {
                isValidCombination = false; // Jika salah satu meja dalam kombinasi sudah terpakai, tandai kombinasi ini tidak valid
                break; // Keluar dari loop karena kombinasi ini tidak valid
            }
        }

        if (isValidCombination && seats >= people && seats < minSeats) {
            minSeats = seats;
            bestCombination.tables = currentCombination;
            bestCombination.totalSeats = seats;
        }
    }

    return bestCombination;
}

void input_kebutuhan_kursi(int level, PriorityQueue& q) {
    int people;
    cout << "Kapasitas kursi yang dibutuhkan: ";
    cin >> people;

    TableCombination combination = findBestCombination(people);

    if (!combination.tables.empty()) {
        cout << "Meja terbaik untuk " << people << " orang: ";
        for (int table : combination.tables) {
            cout << "Meja " << tables[table - 1].id << " ";
        }
        cout << "(Total kapasitas: " << combination.totalSeats << ")\n";

        enqueue(q, level, combination);
        customerQueueHandler(level, combination);
    } else {
        cout << "Tidak ada kombinasi meja yang mencukupi.\n";
    }
}

void ask_member_and_chair_needle(PriorityQueue& q) {
    int level, people;
    cout << "\nPilih level membership\n1. Platinum\n2. Gold\n3. Silver\n4. Non-Membership\nLevel Anda: ";
    cin >> level;

    if (level <= 0 || level > 4) {
        cout << "Level membership tidak valid, silakan pilih ulang\n";
        return;
    }

    cout << "Kapasitas kursi yang dibutuhkan: ";
    cin >> people;

    allocateOrEnqueue(q, level, people);
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