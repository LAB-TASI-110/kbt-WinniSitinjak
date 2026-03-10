#include <stdio.h>    // Untuk fungsi input/output seperti printf, scanf, fgets
#include <string.h>   // Untuk fungsi manipulasi string seperti strcmp, strcspn
#include <ctype.h>    // Untuk fungsi konversi karakter seperti tolower

// Fungsi pembantu untuk mengkonversi string menjadi huruf kecil
// Berguna untuk perbandingan input yang tidak case-sensitive
void toLowerStr(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int main() {
    char customerName[100], customerAddress[100], customerPhone[20];
    char departureTime[20], destination[50], serviceType[20];
    char hasChildInput[5], hasMemberCardInput[5];
    int luggageWeight, numPreviousBookings;
    double basePrice = 0.0;
    double totalPrice = 0.0;
    double totalDiscountPercentage = 0.0; // Akumulasi persentase diskon
    char continueBooking = 'y'; // Variabel untuk mengontrol perulangan booking

    // Menggunakan perulangan 'for' untuk memungkinkan banyak pemesanan tiket dalam satu sesi
    // Perulangan akan berlanjut selama pengguna memilih 'y' (ya)
    for (int bookingCount = 1; tolower(continueBooking) == 'y'; bookingCount++) {
        printf("\n--- Pemesanan Tiket Koperasi Bintang Tapanuli (KBT) #%d ---\n", bookingCount);

        // Input Detail Customer
        printf("Nama Customer: ");
        // fgets digunakan untuk membaca input string termasuk spasi, lebih aman dari scanf
        fgets(customerName, sizeof(customerName), stdin);
        customerName[strcspn(customerName, "\n")] = 0; // Menghapus karakter newline '\n'

        printf("Alamat: ");
        fgets(customerAddress, sizeof(customerAddress), stdin);
        customerAddress[strcspn(customerAddress, "\n")] = 0;

        printf("No. Telp: ");
        fgets(customerPhone, sizeof(customerPhone), stdin);
        customerPhone[strcspn(customerPhone, "\n")] = 0;

        printf("Jam Keberangkatan (Contoh: 08:00): ");
        fgets(departureTime, sizeof(departureTime), stdin);
        departureTime[strcspn(departureTime, "\n")] = 0;

        // Input Tujuan dan menentukan harga dasar tiket
        printf("Tempat Tujuan (Sibolga-Medan, Sibolga-Siantar, Balige-Medan, Balige-Siantar, Tarutung-Medan, Tarutung-Siantar): ");
        fgets(destination, sizeof(destination), stdin);
        destination[strcspn(destination, "\n")] = 0;
        toLowerStr(destination); // Konversi ke huruf kecil untuk perbandingan tidak sensitif huruf

        if (strcmp(destination, "sibolga-medan") == 0) {
            basePrice = 170000.0;
        } else if (strcmp(destination, "sibolga-siantar") == 0) {
            basePrice = 120000.0;
        } else if (strcmp(destination, "balige-medan") == 0) {
            basePrice = 110000.0;
        } else if (strcmp(destination, "balige-siantar") == 0) {
            basePrice = 80000.0;
        } else if (strcmp(destination, "tarutung-medan") == 0) {
            basePrice = 140000.0;
        } else if (strcmp(destination, "tarutung-siantar") == 0) {
            basePrice = 100000.0;
        } else {
            printf("Error: Tujuan yang dimasukkan tidak valid. Mohon coba lagi.\n");
            // Jika tujuan tidak valid, lewati iterasi ini dan mulai pemesanan baru
            continue; 
        }
        
        totalPrice = basePrice; // Inisialisasi total harga dengan harga dasar

        // Input Jenis Layanan (Reguler/Eksklusif)
        printf("Jenis Layanan (Reguler/Eksklusif): ");
        fgets(serviceType, sizeof(serviceType), stdin);
        serviceType[strcspn(serviceType, "\n")] = 0;
        toLowerStr(serviceType);

        if (strcmp(serviceType, "eksklusif") == 0) {
            totalPrice += 30000.0; // Tambah biaya layanan eksklusif
        }

        // Pertanyaan tentang membawa anak usia 0-5 tahun
        printf("Apakah penumpang membawa anak usia 0-5 tahun? (ya/tidak): ");
        fgets(hasChildInput, sizeof(hasChildInput), stdin);
        hasChildInput[strcspn(hasChildInput, "\n")] = 0;
        toLowerStr(hasChildInput);

        if (strcmp(hasChildInput, "ya") == 0) {
            totalPrice += 50000.0; // Tambah biaya kursi anak
        }

        // Pertanyaan tentang berat barang bawaan
        printf("Berat barang yang dibawa (dalam kg): ");
        scanf("%d", &luggageWeight);
        // Membersihkan buffer input setelah scanf untuk mencegah masalah dengan fgets berikutnya
        while (getchar() != '\n'); 

        if (luggageWeight > 15) {
            totalPrice += (luggageWeight - 15) * 15000.0; // Tambah biaya kelebihan bagasi
        }
        
        // --- Penambahan jarak sesuai permintaan ---
        printf("\n"); // Menambahkan baris kosong di sini
        // --- Akhir penambahan ---

        // Perhitungan Diskon
        totalDiscountPercentage = 0.0; // Reset diskon untuk setiap pemesanan

        // Diskon untuk pelanggan dengan > 3 pemesanan sebelumnya
        printf("Berapa kali Anda telah memesan layanan KBT sebelumnya? ");
        scanf("%d", &numPreviousBookings);
        while (getchar() != '\n'); 

        if (numPreviousBookings > 3) {
            totalDiscountPercentage += 0.05; // Tambah diskon 5%
        }

        // Diskon untuk pemilik kartu member KBT
        printf("Apakah Anda memiliki kartu member KBT? (ya/tidak): ");
        fgets(hasMemberCardInput, sizeof(hasMemberCardInput), stdin);
        hasMemberCardInput[strcspn(hasMemberCardInput, "\n")] = 0;
        toLowerStr(hasMemberCardInput);

        if (strcmp(hasMemberCardInput, "ya") == 0) {
            totalDiscountPercentage += 0.10; // Tambah diskon 10%
        }

        // Menerapkan diskon ke total harga
        char discountInfo[100]; // Buffer untuk menyimpan keterangan diskon
        if (totalDiscountPercentage > 0) {
            double finalDiscountAmount = totalPrice * totalDiscountPercentage;
            totalPrice -= finalDiscountAmount;
            // Menggunakan snprintf untuk format string keterangan diskon
            snprintf(discountInfo, sizeof(discountInfo), "Diskon %.0f%% (Rp %.2f).", totalDiscountPercentage * 100, finalDiscountAmount);
        } else {
            strcpy(discountInfo, "Tidak ada diskon.");
        }

        // Output Rincian Pemesanan
        printf("\n--- Rincian Pemesanan Tiket KBT ---\n");
        printf("Nama Pemesan     : %s\n", customerName);
        printf("No. Telp         : %s\n", customerPhone);
        printf("Jenis Layanan    : %s\n", serviceType);
        printf("Alamat Tujuan    : %s\n", destination);
        printf("Total Pembayaran : Rp %.2f\n", totalPrice);
        printf("Keterangan Diskon: %s\n", discountInfo);
        printf("----------------------------------\n");

        // Pertanyaan untuk melanjutkan pemesanan
        printf("\nApakah Anda ingin melakukan pemesanan lain? (Ya/Tidak): ");
        // Spasi sebelum %c di scanf penting untuk mengabaikan karakter newline yang tersisa di buffer
        scanf(" %c", &continueBooking); 
        // Membersihkan buffer input setelah scanf untuk iterasi berikutnya
        while (getchar() != '\n'); 
    }

    printf("\nTerima kasih telah menggunakan layanan Koperasi Bintang Tapanuli.\n");
    return 0; // Mengakhiri program dengan sukses
}
