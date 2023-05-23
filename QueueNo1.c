#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 10 // Jumlah karakter maksimal

// Mendefinisikan Struktur data Queue
typedef struct {
    // Memiliki array data untuk menyimpan elemen-elemen dalam antrian
    int data[MAX_SIZE];
    // Memiliki dua indeks front dan rear untuk melacak elemen terdepan dan terbelakang dalam antrian
    int front;
    int rear;
} Queue;

// Menginisialisasi antrian dengan mengatur indeks front dan rear menjadi -1 
// Nilai awal dari indeks front dan rear
void init(Queue *queue){
    queue->front = -1;
    queue->rear = -1;
}

// Memeriksa apakah antrian kosong
bool jikaKosong(Queue *queue){
    // Jika kedua nilai tersebut sama dengan -1, maka antrian dianggap kosong dan fungsi akan mengembalikan nilai true
    // Jika salah satu atau kedua nilai tersebut bukan -1, maka antrian dianggap tidak kosong dan fungsi akan mengembalikan nilai false
    return queue->front == -1 && queue->rear == -1;
}

// Memeriksa apakah antrian penuh
bool jikaPenuh(Queue *queue){
    // Jika nilai rear sama dengan MAX_SIZE - 1, maka antrian dianggap penuh dan fungsi akan mengembalikan nilai true
    // Jika nilai rear bukan MAX_SIZE - 1, maka antrian dianggap belum penuh dan fungsi akan mengembalikan nilai false
    return queue->rear == MAX_SIZE - 1;
}

// Menghitung jumlah elemen dalam antrian yang valid dan bukan -1
int size(Queue *queue) {
    int count = 0;
    if (!jikaKosong(queue)) { // Jika queue tidak kosong
        for (int i = queue->front; i <= queue->rear; i++) {
            if (queue->data[i] != -1) {  // Dengan asumsi -1 mewakili elemen yang tidak valid/tidak digunakan
                count++;
            }
        }
    }
    return count; // mengembalikan nilai count
}

// Mengembalikan elemen terdepan dalam antrian
int front(Queue *queue){
    return !jikaKosong(queue) ? queue->data[queue->front] : -1;
}

// Menambahkan elemen baru ke dalam antrian
void enqueue(Queue *queue, int newValue) {
    // Jika antrian kosong, perbarui front menjadi 0
    if (!jikaPenuh(queue)) {
        // Jika antrian tidak penuh, periksa apakah antrian kosong 
        if (jikaKosong(queue)) {
            queue->front++;
        }
        queue->data[++queue->rear] = newValue; // Tambahkan elemen baru ke antrian
    } else {
        printf("Queue penuh!\n"); // Jika antrian penuh, cetak pesan "Queue penuh!"
    }
}

// Menghapus dan mengembalikan elemen terdepan dari antrian
int dequeue(Queue *queue) {
    // Jika antrian tidak kosong, ambil nilai elemen terdepan dequeNilai
    if (!jikaKosong(queue)) {
        // Periksa apakah elemen terdepan merupakan elemen tunggal dalam antrian
        int dequeNilai = queue->data[queue->front];
        // Jika elemen tunggal, atur queue->front dan queue->rear menjadi -1
        if (queue->front == queue->rear) {
            queue->front = -1;
            queue->rear = -1;
        } else {
            // Jika bukan elemen tunggal, increment queue->front untuk majukan elemen terdepan
            queue->front++;
        }
        return dequeNilai; // Kembalikan nilai dequeNilai sebagai hasil fungsi
    } else {
        printf("Queue kosong!\n"); // Jika antrian kosong, cetak pesan "Queue kosong!" dan kembalikan -1
        return -1;
    }
}

// Mencetak elemen-elemen dalam antrian
void cetakQueue(Queue *queue){
    // Jika antrian tidak kosong, lakukan perulangan dari queue->front hingga queue->rear untuk mencetak seluruh elemen dalam antrian
    if(!jikaKosong(queue)){
        for(int i = queue->front; i < queue->rear + 1; i++){
            // Cetak setiap elemen
            printf("%d ", queue->data[i]);
        }
        return;
    }
    printf("Queue kosong!"); // Jika antrian kosong, cetak pesan "Queue kosong!"
}

int main(){
    Queue mahasiswaQ,buburQ; // mahasiswaQueue untuk mahasiswa, buburQueue untuk bubur
    init(&mahasiswaQ); // Menginisialisasi antrian menggunakan fungsi init()
    init(&buburQ); // Menginisialisasi antrian menggunakan fungsi init()
    int jumlahMahasiswa, jumlahBubur, mahasiswa, bubur; // Menginisialisasi setiap variabel

    // Memasukkan jumlah mahasiswa
    printf("Masukkan Jumlah Mahasiswa : ");
    scanf("%d",&jumlahMahasiswa);
    printf("Mahasiswa : \n");
    // jika jumlah mahasiswa lebih dari 0
    for (int i = 0; i < jumlahMahasiswa; i++)
    {
        // Masukkan inputan untuk kubu Mahasiswa
        scanf("%d",&mahasiswa);
        // Tambahkan kedalam queue
        enqueue(&mahasiswaQ, mahasiswa);
    }

    // Memasukkan jumlah bubur
    printf("Masukkan Jumlah bubur : ");
    scanf("%d",&jumlahBubur);
    printf("Bubur : \n");
    // jika jumlah bubur lebih dari 0
    for (int i = 0; i < jumlahBubur; i++)
    {
        // Masukkan inputan untuk kubu Bubur
        scanf("%d",&bubur);
        // Tambahkan kedalam queue
        enqueue(&buburQ, bubur);
    }
    // Cocokan mahasiswa dengan bubur agar sesuai
    // Jika kedua antrian tidak kosong, bandingkan elemen terdepan dari mahasiswaQ dengan elemen terdepan dari buburQ
    while (!jikaKosong(&mahasiswaQ) && !jikaKosong(&buburQ)) {
        // Jika mereka sesuai, hapus elemen tersebut dari kedua antrian
        if (front(&mahasiswaQ) == front(&buburQ)) {
            dequeue(&mahasiswaQ);
            dequeue(&buburQ);
        } else {
            // Jika tidak sesuai, 
            int student = dequeue(&mahasiswaQ);
            enqueue(&mahasiswaQ, student);
            int frontStudent = front(&mahasiswaQ);
            bool semuaSama = true;
            // Geser mahasiswa terdepan ke belakang antrian mahasiswaQ dan memeriksa apakah ada kemungkinan cocok yang lain
            for (int i = mahasiswaQ.front; i <= mahasiswaQ.rear; i++) {
                if (mahasiswaQ.data[i] != frontStudent) {
                    semuaSama = false;
                    break;
                }
            }
            if (semuaSama) {
                // Jika tidak ada lagi kemungkinan cocok lagi (semua mahasiswa dalam antrian memiliki nilai yang sama), keluar dari loop
                break;
            }
        }
    }
    // Cetak jumlah mahasiswa yang tidak dapat mengambil bubur sesuai dengan varian yang diinginkan
    printf("Output : %d\n", size(&mahasiswaQ));
}