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
    cout << "pilihan : "; cin >> p;

    if(p == 1){
        ask_member_and_chair_needle(queue);
        goto begin;
    }else if(p == 2){
        displayQueue(queue);
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

void enqueue(PriorityQueue& q, int membershipLevel, TableCombination combination) {
    if (isFull(q)) {
        cout << "Antrian Penuh." << endl;
    } else {
        if (isEmpty(q)) {
            q.front = 0;
            q.rear = 0;
        } else {
            q.rear = (q.rear + 1) % MAX_SIZE;
        }
        q.data[q.rear].membershipLevel = membershipLevel;
        q.data[q.rear].combination = combination;

        // Update status meja menjadi true setelah diberikan kepada pelanggan
        for (int tableIndex : combination.tables) {
            tables[tableIndex - 1].status = true; // Meja sekarang terpakai
        }
    }
}

void dequeue(PriorityQueue& q) {
    if (isEmpty(q)) {
        cout << "Antrian Kosong." << endl;
    } else {
        // Ambil data pelanggan di depan
        Customer customer = q.data[q.front];

        // Perbarui status meja yang dipesan pelanggan
        for (int tableIndex : customer.combination.tables) {
            tables[tableIndex - 1].status = false; // Meja kembali tersedia
        }

        // Update indeks front
        if (q.front == q.rear) {
            initQueue(q); // Jika hanya ada satu elemen
        } else {
            q.front = (q.front + 1) % MAX_SIZE;
        }
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
    int level;
    cout << "\nPilih level membership\n1. Platinum\n2. Gold\n3. Silver\n4. Non-Membership\nLevel Anda: ";
    cin >> level;

    if (level <= 0 || level > 4) {
        cout << "Level membership tidak valid, silakan pilih ulang\n";
    } else {
        input_kebutuhan_kursi(level, q);
    }
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
