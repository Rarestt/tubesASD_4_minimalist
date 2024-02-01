#include <iostream>
#include <vector>
using namespace std;

const int MAX_SIZE = 100;

struct TableCombination{
    vector<int> tables;
    int totalSeats;
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