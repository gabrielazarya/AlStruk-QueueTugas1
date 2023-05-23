#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 26 // Jumlah huruf dalam alfabet

// Struktur data untuk elemen dalam queue
struct Index {
    int index; // Buat variabel indexnya
    struct Index* next;
};

// Struktur data untuk queue itu sendiri
struct Queue {
    struct Index* front; // Buat front terhadap struct Index
    struct Index* rear;  // Buat rear terhadap struct Index
};

// Fungsi untuk membuat queue baru
struct Queue* buatQueue() {
    // Mengalokasikan memori untuk antrian baru 
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = NULL; // menandakan bahwa antrian kosong
    queue->rear = NULL; // menandakan bahwa antrian kosong
    return queue; // Mengembalikan nilai queue
}

// Fungsi untuk menambahkan elemen ke dalam queue
void enqueue(struct Queue* queue, int index) {
    // Mengalokasikan memori untuk antrian baru 
    struct Index* elemenBaru = (struct Index*)malloc(sizeof(struct Index));
    elemenBaru->index = index; // nilai indeks yang diberikan dalam parameter fungsi
    elemenBaru->next = NULL; // karena elemen baru akan menjadi elemen terakhir dalam antrian

    if (queue->rear == NULL) { // Jika antrian masih kosong
        // maka mengatur queue front dan rear untuk menunjuk ke elemen baru
        queue->front = elemenBaru;
        queue->rear = elemenBaru;
    } else { // Jika antrian tidak kosong
        // Maka mengatur queue front dan rear
        // Memperbarui rear untuk menunjuk ke elemen baru
        queue->rear->next = elemenBaru;
        queue->rear = elemenBaru;
    }
}

// Fungsi untuk menghapus elemen dari queue
void dequeue(struct Queue* queue) {
    // program memeriksa apakah front bernilai kosong
    // Jika iya, maka antrian kosong
    if (queue->front == NULL) {
        return;
    }
    // untuk menyimpan alamat elemen pertama sebelum dihapus
    struct Index* temp = queue->front;
    // untuk menunjuk ke elemen berikutnya dalam antrian
    queue->front = queue->front->next;

    // dilakukan pengecekan apakah antrian sekarang kosong
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    //  Jika iya, maka antrian saat ini kosong karena tidak ada elemen lagi
    free(temp);
}

// Fungsi untuk mengecek apakah queue kosong atau tidak
int jikaKosong(struct Queue* queue) {
    return queue->front == NULL; // Nilai front kosong
}

// Fungsi untuk mencari dan menampilkan indeks karakter pertama yang merupakan karakter tunggal
void IndeksUnikPertama(const char* str) {
    int jumlahHuruf[MAX_SIZE] = {0}; // untuk mendefinisikan 26 jumlah hurud
    int besarHuruf = strlen(str); // untuk mendefinisikan besar hurufnya
    struct Queue* queue = buatQueue(); // Untuk membuat queue baru

    // Menghitung frekuensi kemunculan setiap karakter dalam string
    for (int i = 0; i < besarHuruf; i++) {
        jumlahHuruf[str[i] - 'a']++;
    }

    // Menambahkan indeks karakter pertama yang merupakan karakter tunggal ke dalam queue
    for (int i = 0; i < besarHuruf; i++) {
        if (jumlahHuruf[str[i] - 'a'] == 1) {
            enqueue(queue, i);
        }
    }

    // Menampilkan indeks karakter pertama yang merupakan karakter tunggal
    if (!jikaKosong(queue)) {
        printf("%d\n", queue->front->index);
    } else {
        printf("-1\n");
    }

    // Menghapus semua elemen dalam queue
    while (!jikaKosong(queue)) {
        dequeue(queue);
    }

    // Membebaskan memori yang dialokasikan untuk queue
    free(queue);
}

int main() {
    char karakter[100]; // mendefinisikan inputan berupa karakter
    printf("Masukkan Karakter : \n");
    scanf("%s", karakter);

    // Mencari Indeks unik pertama dalam variabel karakter
    IndeksUnikPertama(karakter);

    return 0; // Program selesai
}
