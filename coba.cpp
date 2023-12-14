#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>


using namespace std;

const string dataAccount = "account_data.txt";
const string dataServisHistory = "account_servisHistory.txt";
const string dataBelanja = "account_belanja.txt";
const string dataBelanjaHistory = "account_belanjaHistory.txt";
const string dataMekanik = "account_mekanik.txt";

string email;

bool accountFound = false;

void akun();
void registrasi();
void login();
void menu();
void konsultasi();
void servis();
void belanja();
void admin();

void mekanikAdmin();
void belanjaAdmin();
void addMekanik();
void editMekanik();
void deleteMekanik();
void loadMekanik();
void addBelanja();
void editBelanja();
void deleteBelanja();
void loadBelanja();
string getLastBelanjaID();
string getLastMekanikID();
string generateNextID(const string& lastID);
void displayBelanjaData();
void displayMekanikData();
void displayMekanikJadwal(string jadwalMekanik);
void displayJenisBelanja(string jenisBelanja);
bool isValidMekanikID(int pilihMekanik, const string& jadwal);
bool isValidBelanjaID(int pilihBelanja, const string& barang);


void saveAccountToFile(const string& email, const string& nama, const string& username, const string& password);
void saveServisHistoryToFile(const string& email, const string& jenis, const string& merek, const string& tipe, const string& tahun, const string& datang, const string& pickup, const string& jarak, const string& jadwal, const string& servis, const string& mekanik, const string& sparepart, const int& harga);
void saveBelanjaToFile(const string& id, const string& jenis, const string& barang, const string& harga);
void saveBelanjaHistoryToFile(const string& email, const string& jenis, const string& barang, const string& harga, const string& jumlah);
void saveMekanikToFile(const string& id, const string& nama, const string& jadwal, const string& harga);
void loadAccountsFromFile();
void loadServisHistoryFromFile();
void loadBelanjaFromFile();
void loadBelanjaHistoryFromFile();
void loadMekanikFromFile();

int main()
{

    cout << "------ ==Selamat Datang di ByBeng== ------" << endl;
    akun();
    menu(); 
}

void registrasi()
{
    cout << "--Registrasi Akun--" << endl;

    string email, nama, username, password;

    // Ensure unique email
    do
    {
        cout << "Masukkan email: ";
        getline(cin, email);

        ifstream inFile(dataAccount);
        if (inFile.is_open())
        {
            string storedEmail, storedNama, storedUsername, storedPassword;
            bool isEmailUnique = true;

            while (getline(inFile, storedEmail, '|') &&
                   getline(inFile, storedNama, '|') &&
                   getline(inFile, storedUsername, '|') &&
                   getline(inFile, storedPassword))
            {
                if (storedEmail == email)
                {
                    cout << "Email sudah digunakan. Masukkan email lain." << endl;
                    isEmailUnique = false;
                    break;
                }
            }

            if (isEmailUnique)
            {
                inFile.close();
                break;
            }

            inFile.close();
        }
        else
        {
            cout << "Unable to open file for reading." << endl;
        }
    } while (true);

    // Ensure unique username
    do
    {
        cout << "Masukkan username: ";
        getline(cin, username);

        ifstream inFile(dataAccount);
        if (inFile.is_open())
        {
            string storedEmail, storedNama, storedUsername, storedPassword;
            bool isUsernameUnique = true;

            while (getline(inFile, storedEmail, '|') &&
                   getline(inFile, storedNama, '|') &&
                   getline(inFile, storedUsername, '|') &&
                   getline(inFile, storedPassword))
            {
                if (storedUsername == username)
                {
                    cout << "Username sudah digunakan. Masukkan username lain." << endl;
                    isUsernameUnique = false;
                    break;
                }
            }

            if (isUsernameUnique)
            {
                inFile.close();
                break;
            }

            inFile.close();
        }
        else
        {
            cout << "Unable to open file for reading." << endl;
        }
    } while (true);

    // Continue with the rest of the registration
    cout << "Masukkan nama lengkap: ";
    getline(cin, nama);

    cout << "Masukkan password: ";
    getline(cin, password);

    saveAccountToFile(email, nama, username, password);
}


void login()
{
    string enteredEmail, enteredPassword;

    cout << "--Login Akun--" << endl;

    cout << "Masukkan email: ";
    getline(cin, enteredEmail);

    cout << "Masukkan password: ";
    getline(cin, enteredPassword);

    ifstream inFile(dataAccount);
    if (inFile.is_open())
    {
        string storedEmail, storedNama, storedUsername, storedPassword;

        while (getline(inFile, storedEmail, '|') &&
               getline(inFile, storedNama, '|') &&
               getline(inFile, storedUsername, '|') &&
               getline(inFile, storedPassword))
        {
            // You can do something with the loaded account information
            // For now, let's just print it
            if (storedEmail == enteredEmail && storedPassword == enteredPassword)
            {
                accountFound = true;
                cout << "Login berhasil. Selamat datang, " << storedNama << "!" << endl
                     << endl;
                email = enteredEmail;
                break;
            }
        }

        if (!accountFound)
        {
            cout << "Login gagal. Email atau password salah." << endl;
        }

        inFile.close();
    }
    else
    {
        cout << "Unable to open file for reading. Assuming no existing accounts." << endl;
    }
}

void saveAccountToFile(const string& email, const string& nama, const string& username, const string& password)
{
    ofstream outFile(dataAccount, ios::app); // Open file in append mode
    if (outFile.is_open())
    {
        outFile << email << "|" << nama << "|" << username << "|" << password << endl;
        outFile.close();
    }
    else
    {
        cout << "Unable to open file for writing." << endl;
    }
}

void saveServisHistoryToFile(const string& email, const string& jenis, const string& merek, const string& tipe, const string& tahun, const string& datang, const string& pickup, const string& jarak, const string& jadwal, const string& servis, const string& mekanik, const string& sparepart, const string& harga)
{
    string datangValue = datang.empty() ? "null" : datang;
    string pickupValue = pickup.empty() ? "null" : pickup;
    string jarakValue = jarak.empty() ? "null" : jarak;
    string sparepartValue = sparepart.empty() ? "null" : sparepart;

    ofstream outFile(dataServisHistory, ios::app); // Open file in append mode
    if (outFile.is_open())
    {
        outFile << email << "|" << jenis << "|" << merek << "|" << tipe << "|" << tahun << "|" << datang << "|" << pickup << "|" << jarak << "|" << jadwal << "|" << servis << "|" << mekanik << "|" << sparepart << "|" << harga << endl;
        outFile.close();
    }
    else
    {
        cout << "Unable to open file for writing." << endl;
    }
}

void saveBelanjaToFile(const string& id, const string& jenis, const string& barang, const string& harga)
{
    ofstream outFile(dataBelanja, ios::app); // Open file in append mode
    if (outFile.is_open())
    {
        outFile << id << " " << jenis << " " << barang << " " << harga << endl;
        outFile.close();
    }
    else
    {
        cout << "Unable to open file for writing." << endl;
    }
}

void saveBelanjaHistoryToFile(const string& email, const string& jenis, const string& barang, const string& harga, const string& jumlah)
{
    ofstream outFile(dataBelanjaHistory, ios::app); // Open file in append mode
    if (outFile.is_open())
    {
        outFile << email << "|" << jenis << "|" << barang << "|" << harga << "|" << jumlah << endl;
        outFile.close();
    }
    else
    {
        cout << "Unable to open file for writing." << endl;
    }
}

void saveMekanikToFile(const string& id, const string& nama, const string& jadwal, const string& harga)
{
    ofstream outFile(dataMekanik, ios::app); // Open file in append mode
    if (outFile.is_open())
    {
        outFile << id << " " << nama << " " << jadwal << " " << harga << endl;
        outFile.close();
    }
    else
    {
        cout << "Unable to open file for writing." << endl;
    }
}

void loadAccountsFromFile()
{
    ifstream inFile(dataAccount);
    if (inFile.is_open())
    {
        // You can add code here if needed to process the loaded accounts
        inFile.close();
    }
    else
    {
        cout << "Unable to open file for reading. Assuming no existing accounts." << endl;
    }
}

void loadServisHistoryFromFile()
{
    ifstream inFile(dataServisHistory);
    if (inFile.is_open())
    {
        // You can add code here if needed to process the loaded accounts
        inFile.close();
    }
    else
    {
        cout << "Unable to open file for reading. Assuming no existing accounts." << endl;
    }
}

void loadBelanjaFromFile()
{
    ifstream inFile(dataBelanja);
    if (inFile.is_open())
    {
        // You can add code here if needed to process the loaded accounts
        inFile.close();
    }
    else
    {
        cout << "Unable to open file for reading. Assuming no existing accounts." << endl;
    }
}

void loadBelanjaHistoryFromFile()
{
    ifstream inFile(dataBelanjaHistory);
    if (inFile.is_open())
    {
        // You can add code here if needed to process the loaded accounts
        inFile.close();
    }
    else
    {
        cout << "Unable to open file for reading. Assuming no existing accounts." << endl;
    }
}

void loadMekanikFromFile()
{
    ifstream inFile(dataMekanik);
    if (inFile.is_open())
    {
        // You can add code here if needed to process the loaded accounts
        inFile.close();
    }
    else
    {
        cout << "Unable to open file for reading. Assuming no existing accounts." << endl;
    }
}

void menu()
{
    int pilihLayanan;
    do
    {
        cout << endl << "1. Servis Kendaraan" << endl << "2. Belanja Spare Part" << endl <<"3. Konsultasi Kendaraan" << endl <<"4. Mode Admin" << endl << "5. Kembali ke Akun" << endl  << "0. Keluar Program" <<endl << "Pilih Layanan: ";
        cin >> pilihLayanan;
        switch (pilihLayanan)
        {
        case 0:
            cout << endl << "Terimakasih telah menggunakan ByBeng!!";
            break;
        case 1:
            servis();
            break;
        case 2:
            belanja();
            break;
        case 3:
            konsultasi();
            break;
        case 4:
            admin();
            break;
        case 5:
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            accountFound = false;
            akun();
            menu();
            break;
        }
    } while ((pilihLayanan < 0 || pilihLayanan > 5) && pilihLayanan != 9);
    

}

bool isNumeric(const string& str) {
    return str.find_first_not_of("0123456789") == string::npos;
}

void servis()
{
    int pilihJenisKendaraan, pilihMerekKendaraan, pilihJadwal, pilihSparepart, pilihMekanik, pilihJenisServis, layanan, hargaDatang, hargaServis, hargaSparepart = 0, hargaMekanik, hargaTotal;
    string  jenisKendaraan, merekKendaraan, tipeKendaraan, tahunKendaraan,
            butuhDatang, butuhPickup, butuhSparepart,ambilKendaraan, datangKendaraan, jarak,
            jadwal, sparepart, mekanik,
            jenisServis,
            konfirmasiBayar;

    cout << "==== Servis Kendaraan ====" << endl;

    // Jenis Kendaraan
    do
    {
        cout << endl << "0. Kembali ke Menu" << endl << "1. Motor" << endl << "2. Mobil" << endl << "3. Sepeda" << endl;
        cout << "Pilih Jenis Kendaraan: ";
        cin >> pilihJenisKendaraan;

        switch (pilihJenisKendaraan)
        {
        case 0:
            menu();
            break;
        case 1:
            jenisKendaraan = "motor";
            break;
        case 2:
            jenisKendaraan = "mobil";
            break;
        case 3:
            jenisKendaraan = "sepeda";
            break;
        }
    } while (pilihJenisKendaraan < 0 || pilihJenisKendaraan > 3);

    // Merek Kendaraan
    do 
    {
        // Motor
        if (pilihJenisKendaraan == 1)
        {
            cout << endl << "1. Honda" << endl << "2. Yamaha" << endl << "3. Suzuki" << endl;
            cout << "Pilih Merek Motor: ";
            cin >> pilihMerekKendaraan;

            switch (pilihMerekKendaraan)
            {
            case 1:
                merekKendaraan = "Honda";
                break;
            case 2:
                merekKendaraan = "Yamaha";
                break;
            case 3:
                merekKendaraan = "Suzuki";
                break;
            }
        }

        // Mobil
        if (pilihJenisKendaraan == 2)
        {
            cout << endl << "1. Hyundai" << endl << "2. Toyota" << endl << "3. Daihatsu" << endl;
            cout << "Pilih Merek Mobil: ";
            cin >> pilihMerekKendaraan;

            switch (pilihMerekKendaraan)
            {
            case 1:
                merekKendaraan = "Hyundai";
                break;
            case 2:
                merekKendaraan = "Toyota";
                break;
            case 3:
                merekKendaraan = "Daihatsu";
                break;
            }
        }

        // Sepeda
        if (pilihJenisKendaraan == 3)
        {
            cout << endl << "1. Polygon" << endl << "2. United" << endl << "3. Wimcycle" << endl;
            cout << "Pilih Merek Sepeda: ";
            cin >> pilihMerekKendaraan;
            
            switch (pilihMerekKendaraan)
            {
            case 1:
                merekKendaraan = "Polygon";
                break;
            case 2:
                merekKendaraan = "United";
                break;
            case 3:
                merekKendaraan = "Wimcycle";
                break;
            }
        }

    } while (pilihMerekKendaraan < 1 || pilihMerekKendaraan > 3);
    

    // Tipe Kendaraan
    do
    {
        cout << "Pilih Tipe Kendaraan: ";
        cin.ignore();
        getline(cin, tipeKendaraan);
    } while (tipeKendaraan.empty());


    // Tahun Kendaraan
    do
    {
        cout << "Tahun Kendaraan: ";
        cin >> tahunKendaraan;
    } while (!isNumeric(tahunKendaraan)); // still not sure if working or not
    
    // Perlu Datang ?
    do
    {
        cout << "Butuh Datang? (y/n): ";
        cin >> butuhDatang;
        if (butuhDatang == "y")
        {
            hargaDatang = 5000;
            datangKendaraan = "datang";
            do
            {
                cout << "Butuh Pick-up? (y/n): ";
                cin >> butuhPickup;
                if (butuhPickup == "y")
                {
                    ambilKendaraan = "pickup";
                    hargaDatang = 7500;
                }
                else if (butuhPickup == "n")
                {
                    ambilKendaraan = "null";
                }
                
            } while (butuhPickup != "y" && butuhPickup != "n");    
            do
            {
                cout << "Masukkan Jarak Kendaraan(KM): ";
                cin >> jarak;
                hargaDatang = hargaDatang + (hargaDatang * (stoi(jarak) * 0.3));
            } while (!isNumeric(jarak));
        }
        else if (butuhDatang == "n")
        {
            datangKendaraan = "null";
            jarak = "null";
        }
        
        
    } while (butuhDatang != "y" && butuhDatang != "n");
    

    // Jadwal servis
    do
    {
        cout << endl << "1. Pagi" << endl << "2. Siang" << endl << "3. Sore" << endl;
        cout << "Pilih Jadwal Servis: ";
        cin >> pilihJadwal;

        switch (pilihJadwal)
        {
        case 1:
            jadwal = "pagi";
            break;
        case 2:
            jadwal = "siang";
            break;
        case 3:
            jadwal = "sore";
            break;
        }

    } while (pilihJadwal < 1 || pilihJadwal > 3);

    // Jenis Servis
    do
    {
        // Motor
        if (pilihJenisKendaraan == 1)
        {
            cout << endl << "1. Ganti Oli - Rp30.000" << endl << "2. Tune-up Mesin - Rp50.000" << endl << "3. Pengecekan Rem - Rp20.000" << endl << "4. Servis Karburator - Rp80.000" << endl;
            cout << "Pilih Jenis Servis: ";
            cin >> pilihJenisServis;

            switch (pilihJenisServis)
            {
            case 1:
                jenisServis = "Ganti Oli";
                hargaServis = 30000;
                break;
            case 2:
                jenisServis = "Tune-up Mesin";
                hargaServis = 50000;
                break;
            case 3:
                jenisServis = "Pengecekan Rem";
                hargaServis = 20000;
                break;
            case 4:
                jenisServis = "Servis Karburator";
                hargaServis = 80000;
                break;
            }
        }

        // Mobil
        if (pilihJenisKendaraan == 2)
        {
            cout << endl << "1. Ganti Oli dan Filter - Rp100.000" << endl << "2. Perawatan AC - Rp150.000" << endl << "3. Ganti Busi - Rp 60.000" << endl << "4. Servis Transmisi - Rp120.000" << endl;
            cout << "Pilih Jenis Servis: ";
            cin >> pilihJenisServis;

            switch (pilihJenisServis)
            {
            case 1:
                jenisServis = "Ganti Oli dan Filter";
                hargaServis = 100000;
                break;
            case 2:
                jenisServis = "Perawatan AC";
                hargaServis = 150000;
                break;
            case 3:
                jenisServis = "Ganti Busi";
                hargaServis = 60000;
                break;
            case 4:
                jenisServis = "Servis Transmisi";
                hargaServis = 120000;
                break;
            }
        }

        // Sepeda
        if (pilihJenisKendaraan == 3)
        {
            cout << endl << "1. Pelumasan Rantai - Rp20.000" << endl << "2. Perbaikan Ban Bocor - Rp25.000" << endl << "3. Penyetelan Rem - Rp15.000" << endl << "4. Ganti Gear - Rp30.000" << endl;
            cout << "Pilih Jenis Servis: ";
            cin >> pilihJenisServis;
            
            switch (pilihJenisServis)
            {
            case 1:
                jenisServis = "Pelumasan Rantai";
                hargaServis = 20000;
                break;
            case 2:
                jenisServis = "Perbaikan Ban Bocor";
                hargaServis = 25000;
                break;
            case 3:
                jenisServis = "Penyetelan Rem";
                hargaServis = 15000;
                break;
            case 4:
                jenisServis = "Ganti Gear";
                hargaServis = 30000;
                break;
            }
        }
    } while (pilihJenisServis < 1 || pilihJenisServis > 4);

    // Pilih Mekanik
    do
    {
        displayMekanikJadwal(jadwal);
        cout << endl << "Pilih ID Mekanik: ";
        cin >> pilihMekanik;
        
        ifstream inFile(dataMekanik);

    if (inFile.is_open())
    {
        string id, nama, jadwalMekanik, harga;

        while (getline(inFile, id, '|') &&
               getline(inFile, nama, '|') &&
               getline(inFile, jadwalMekanik, '|') &&
               getline(inFile, harga))
        {
            if (stoi(id) == pilihMekanik)
            {
                mekanik = nama;
                hargaMekanik = stoi(harga);
                
            }
        }

        inFile.close();
    }
    else
    {
        cout << "Unable to open file for reading." << endl;
    }

    } while (!isValidMekanikID(pilihMekanik, jadwal));
    

    // Ganti Spare Part ?
    do
    {   
        cout << "Beli Spare-part? (y/n): ";
        cin >> butuhSparepart;
        // Motor
        if (pilihJenisKendaraan == 1 && butuhSparepart == "y")
        {
            do
            {
                cout << endl << "1. Oli Mesin - Rp50.000" << endl << "2. Rantai - Rp200.000" << endl << "3. Busi - Rp 20.000" << endl << "4. Filter Udara - Rp15.000" << endl;
                cout << "Pilih Spare-part: ";
                cin >> pilihSparepart;

                switch (pilihSparepart)
                {
                case 1:
                    sparepart = "Oli Mesin";
                    hargaSparepart = 50000;
                    break;
                case 2:
                    sparepart = "Rantai";
                    hargaSparepart = 200000;
                    break;
                case 3:
                    sparepart = "Busi";
                    hargaSparepart = 20000;
                    break;
                case 4:
                    sparepart = "Filter Udara";
                    hargaSparepart = 15000;
                    break;
                }
            } while (pilihSparepart < 1 || pilihSparepart > 4);
        }
        else if (pilihJenisKendaraan == 1 && butuhSparepart == "n")
        {
            sparepart = "null";
        }
        

        // Mobil
        if (pilihJenisKendaraan == 2 && butuhSparepart == "y")
        {
            do
            {
                cout << endl << "1. Oli Mesin - Rp 80.000" << endl << "2. Rem Cakram - Rp 500.000" << endl << "3. Aki Mobil -  - Rp 600.000" << endl << "4. Kampas Rem - Rp 150.000" << endl;
                cout << "Pilih Spare-part: ";
                cin >> pilihSparepart;

                switch (pilihSparepart)
                {
                case 1:
                    sparepart = "Oli Mesin";
                    hargaSparepart = 80000;
                    break;
                case 2:
                    sparepart = "Rem Cakram";
                    hargaSparepart = 500000;
                    break;
                case 3:
                    sparepart = "Aki Mobil";
                    hargaSparepart = 600000;
                    break;
                case 4:
                    sparepart = "Suzuki";
                    hargaSparepart = 150000;
                    break;
                }
            } while (pilihSparepart < 1 || pilihSparepart > 4);
        }
        else if (pilihJenisKendaraan == 2 && butuhSparepart == "n")
        {
            sparepart = "null";
        }

        // Sepeda
        if (pilihJenisKendaraan == 3 && butuhSparepart == "y")
        {
            do
            {
                cout << endl << "1. Ban Sepeda - Rp100.000" << endl << "2. Rantai Sepeda - Rp50.000" << endl << "3. Pedal Sepeda - Rp30.000" << endl << "4. Sadel Sepeda - Rp40.000" << endl;
                cout << "Pilih Spare-part: ";
                cin >> pilihSparepart;

                switch (pilihSparepart)
                {
                case 1:
                    sparepart = "Ban Sepeda";
                    hargaSparepart = 100000;
                    break;
                case 2:
                    sparepart = "Rantai Sepeda";
                    hargaSparepart = 50000;
                    break;
                case 3:
                    sparepart = "Pedal Sepeda";
                    hargaSparepart = 30000;
                    break;
                case 4:
                    sparepart = "Suzuki";
                    hargaSparepart = 40000;
                    break;
                }
            } while (pilihSparepart < 1 || pilihSparepart > 4);
        }
        else if (pilihJenisKendaraan == 3 && butuhSparepart == "n")
        {
            sparepart = "null";
        }

    } while (butuhSparepart != "y" && butuhSparepart != "n");
    
    // Konfirmasi Bayaran
    hargaTotal = hargaDatang + hargaServis + hargaSparepart + hargaMekanik;
    do
    {
        cout << endl << "Harga Datang: " << hargaDatang << endl << "Harga Servis: " << hargaServis << endl << "Harga Spare-part: " << hargaSparepart << endl << "Harga Mekanik: " << hargaMekanik << endl;
        cout << "Total Harga adalah: " << hargaTotal << endl;
        cout << "Apakah Anda Ingin Mengonfirmasi Pembayaran? (y/n): ";
        cin >> konfirmasiBayar;
    } while (konfirmasiBayar != "y" && konfirmasiBayar != "n");
    if (konfirmasiBayar == "y")
    {
        cout << "Terima Kasih Telah Menggunakan Jasa Servis Kendaraan ByBeng!" << endl;
        saveServisHistoryToFile(email, jenisKendaraan, merekKendaraan, tipeKendaraan, tahunKendaraan, datangKendaraan, ambilKendaraan, jarak, jadwal, jenisServis, mekanik, sparepart, to_string(hargaTotal));
    }
    do
    {
        cout << endl << "1. Servis Kendaraan" << endl << "2. Kembali ke Menu" << endl << "0. Keluar Program" << endl;
        cout << "Pilih Layanan: ";
        cin >> layanan;
    } while (layanan < 0 || layanan > 2);
    
    switch (layanan)
    {
    case 1:
        servis();
        break;
    case 2:
        menu();
        break;
    case 0:
        cout << endl << "Terimakasih telah menggunakan ByBeng!!";
        break;
    }
    

}

void belanja()
{
    cout << "==== Belanja Spare-part ====" << endl;
    int     pilihJenis, pilihBelanja, layanan, hargaTotal,hargaBarang;
    string  jenisBelanja, barang, jumlah, jumlahBarang, 
            konfirmasiBayar;
    
    do
    {
        cout << endl << "1. Motor" << endl << "2. Mobil" << endl << "3. Sepeda" << endl;
        cout << "Pilih Jenis Kendaraan: ";
        cin >> pilihJenis;

        switch (pilihJenis)
        {
        case 1:
            jenisBelanja = "motor";
            break;
        case 2:
            jenisBelanja = "mobil";
            break;
        case 3:
            jenisBelanja = "sepeda";
            break;
        }
    } while (pilihJenis < 1 || pilihJenis > 3);

    do
    {
        displayJenisBelanja(jenisBelanja);

        cout << endl << "Pilih ID Spare-part: ";
        cin >> pilihBelanja;

        ifstream inFile(dataBelanja);

        if (inFile.is_open())
        {
            string storedID, storedJenis, storedBarang, storedHarga;
            while (getline(inFile, storedID, '|') &&
                    getline(inFile, storedJenis, '|') &&
                    getline(inFile, storedBarang, '|') &&
                    getline(inFile, storedHarga))
            {
                if (stoi(storedID) == pilihBelanja && jenisBelanja == storedJenis)
                {
                    cout << endl << "Jenis kendaraan: " << storedJenis << endl;
                    barang = storedBarang;
                    hargaBarang = stoi(storedHarga);
                    
                }
            }

            inFile.close();
        }
        else
        {
            cout << "Unable to open file for reading." << endl;
        }

    } while (!isValidBelanjaID(pilihBelanja, jenisBelanja));

    do
    {
        cout << "Berapa banyak yang ingin dibeli?: ";
        cin >> jumlahBarang;
    } while (!isNumeric(jumlahBarang));
    
    
    

    
    // Konfirmasi Bayaran
    hargaTotal = hargaBarang * stoi(jumlahBarang);
    do
    {
        cout << endl << "Harga Spare-part: " << hargaBarang << endl << "Jumlah pembelian: " << jumlahBarang << endl << endl;
        cout << "Total Harga adalah: " << hargaTotal << endl;
        cout << "Apakah Anda Ingin Mengonfirmasi Pembayaran? (y/n): ";
        cin >> konfirmasiBayar;
    } while (konfirmasiBayar != "y" && konfirmasiBayar != "n");
    if (konfirmasiBayar == "y")
    {
        cout << "Terima Kasih Telah Menggunakan Jasa Servis Kendaraan ByBeng!" << endl;
        saveBelanjaHistoryToFile(email, jenisBelanja, barang, to_string(hargaTotal), jumlah);
    }
    do
    {
        cout << endl << "1. Belanja Spare-part" << endl << "2. Kembali ke Menu" << endl << "0. Keluar Program" << endl;
        cout << "Pilih Layanan: ";
        cin >> layanan;
    } while (layanan < 0 || layanan > 2);
    
    switch (layanan)
    {
    case 1:
        belanja();
        break;
    case 2:
        menu();
        break;
    case 0:
        cout << endl << "Terimakasih telah menggunakan ByBeng!!";
        break;
    }
}

void konsultasi()
{
    int layanan;

    cout << "==== Konsultasi Kendaraan ====" << endl;

    string chats[5];

    // Konsultasi kendaraan
    chats[0] = "Pelanggan: Selamat pagi! Saya ingin berkonsultasi mengenai masalah mesin mobil saya.";
    chats[1] = "CS: Selamat pagi! " + email + " Tentu, silakan ceritakan detail masalahnya.";
    chats[2] = "Pelanggan: Mobil saya mengeluarkan suara aneh dan terkadang sulit untuk dinyalakan.";
    chats[3] = "CS: Saya mengerti. Apakah lampu indikator mesin menyala? Dan kapan terakhir kali Anda melakukan servis rutin?";
    chats[4] = "Pelanggan: Ya, lampu indikator menyala. Dan servis terakhir dilakukan sekitar dua bulan yang lalu.";

    // Menampilkan percakapan
    for (const string& chat : chats) {
        cout << chat << endl;
    }

    do
    {
        cout << endl << "1. Konsultasi" << endl << "2. Kembali ke Menu" << endl << "0. Keluar Program" << endl;
        cout << "Pilih Layanan: ";
        cin >> layanan;
    } while (layanan < 0 || layanan > 2);
    
    switch (layanan)
    {
    case 1:
        konsultasi();
        break;
    case 2:
        menu();
        break;
    case 0:
        cout << endl << "Terimakasih telah menggunakan ByBeng!!";
        break;
    }
}

void admin()
{
    int pilihLayanan;
    cout << "==== Mode Admin ====" << endl;
    do
    {
        cout << "1. Mekanik" << endl << "2. Item Belanja" << endl << "3. Kembali ke Menu Layanan"  << endl;
        cout << "Pilih Layanan: ";
        cin >> pilihLayanan;

        switch (pilihLayanan)
        {
        case 1:
            mekanikAdmin();
            break;
        case 2:
            belanjaAdmin();
            break;
        case 3:
            menu();
            break;
        }
    } while (pilihLayanan < 1 || pilihLayanan > 2);
    
}

void mekanikAdmin()
{
    int pilihLayanan;
    do
    {
        cout << "1. Tambah Mekanik" << endl << "2. Edit Mekanik" << endl << "3. Hapus Mekanik" << endl << "4. Tampilkan Mekanik" << endl << "5. Kembali ke Menu Admin" << endl;
        cout << "Pilih Layanan: ";
        cin >> pilihLayanan;

        switch (pilihLayanan)
        {
        case 1:
            addMekanik();
            break;
        case 2:
            editMekanik();
            break;
        case 3:
            deleteMekanik();
            break;
        case 4:
            loadMekanik();
            break;
        case 5:
            admin();
            break;
        }

    } while (pilihLayanan < 1 || pilihLayanan > 4);
    
}

void belanjaAdmin()
{
    int pilihLayanan;
    do
    {
        cout << "1. Tambah Belanja" << endl << "2. Edit Belanja" << endl << "3. Hapus Belanja" << endl << "4. Tampilkan Belanja" << endl << "5. Kembali ke Menu Admin" << endl;
        cout << "Pilih Layanan: ";
        cin >> pilihLayanan;

        switch (pilihLayanan)
        {
        case 1:
            addBelanja();
            break;
        case 2:
            editBelanja();
            break;
        case 3:
            deleteBelanja();
            break;
        case 4:
            loadBelanja();
            break;
        }

    } while (pilihLayanan < 1 || pilihLayanan > 4);
}

void addMekanik()
{
    string lastID = getLastMekanikID();
    string nextID = generateNextID(lastID);
    string nama, jadwal, harga;
    int pilihJadwal, pilihLayanan;

    cout << "Nama Mekanik: ";
    cin.ignore(); // Clear newline character from the buffer
    getline(cin, nama);

    do
    {
        cout << "1. Pagi" << endl << "2. Siang" << endl << "3. Sore" << endl;
        cout << "Jadwal Servis: ";
        cin >> pilihJadwal;

        switch (pilihJadwal)
        {
        case 1:
            jadwal = "pagi";
            break;
        case 2:
            jadwal = "siang";
            break;
        case 3:
            jadwal = "sore";
            break;
        }

    } while (pilihJadwal < 1 || pilihJadwal > 3);
    
    do
    {
        cout << "Harga Mekanik: ";
        cin.ignore();
        getline(cin, harga);
    } while (!isNumeric(harga));
    
    
    ofstream outFile(dataMekanik, ios::app); // Open file in append mode
    if (outFile.is_open())
    {
        outFile << nextID << "|" << nama << "|" << jadwal << "|" << harga << endl;
        outFile.close();
        cout << "Mekanik berhasil ditambahkan." << endl;
    }

    do
    {
        cout << "1. Tambah Mekanik" << endl << "2. Edit Mekanik" << endl << "3. Hapus Mekanik" << endl << "4. Tampilkan Mekanik" << endl << "5. Kembali ke Admin" << endl;
        cout << "Pilih Layanan: ";
        cin >> pilihLayanan;

        switch (pilihLayanan)
        {
        case 1:
            addMekanik();
            break;
        case 2:
            editMekanik();
            break;
        case 3:
            deleteMekanik();
            break;
        case 4:
            loadMekanik();
            break;
        case 5:
            admin();
            break;
        }

    } while (pilihLayanan < 1 || pilihLayanan > 4);
}
void editMekanik()
{
    displayMekanikData();

    string editID, nama, jadwal, harga;
    int pilihJadwal, pilihLayanan;

    cout << "Masukkan ID Mekanik yang akan di-edit: ";
    cin >> editID;

    ifstream inFile(dataMekanik);
    ofstream tempFile("tempMekanik.txt");

    if (inFile.is_open() && tempFile.is_open())
    {
        string id, storedNama, storedJadwal, storedHarga;
        bool found = false;

        while (getline(inFile, id, '|') &&
               getline(inFile, storedNama, '|') &&
               getline(inFile, storedJadwal, '|') &&
               getline(inFile, storedHarga))
        {
            if (id == editID)
            {
                found = true;
                cout << "Nama Mekanik: ";
                cin.ignore(); // Clear newline character from the buffer
                getline(cin, nama);

                do
                {
                    cout << "1. Pagi" << endl << "2. Siang" << endl << "3. Sore" << endl;
                    cout << "Jadwal Servis: ";
                    cin >> pilihJadwal;

                    switch (pilihJadwal)
                    {
                    case 1:
                        jadwal = "pagi";
                        break;
                    case 2:
                        jadwal = "siang";
                        break;
                    case 3:
                        jadwal = "sore";
                        break;
                    }

                } while (pilihJadwal < 1 || pilihJadwal > 3);

                do
                {
                    cout << "Harga Mekanik: ";
                    cin >> harga;
                } while (!isNumeric(harga));

                tempFile << id << "|" << nama << "|" << jadwal << "|" << harga << endl;
                cout << "Mekanik berhasil di-edit." << endl;
            }
            else
            {
                tempFile << id << "|" << storedNama << "|" << storedJadwal << "|" << storedHarga << endl;
            }
        }

        inFile.close();
        tempFile.close();

        remove(dataMekanik.c_str());
        rename("tempMekanik.txt", dataMekanik.c_str());

        if (!found)
        {
            cout << "ID Mekanik tidak ditemukan." << endl;
        }
    }
    else
    {
        cout << "Unable to open file for reading or writing." << endl;
    }

    do
    {
        cout << "1. Tambah Mekanik" << endl << "2. Edit Mekanik" << endl << "3. Hapus Mekanik" << endl << "4. Tampilkan Mekanik" << endl << "5. Kembali ke Admin" << endl;
        cout << "Pilih Layanan: ";
        cin >> pilihLayanan;

        switch (pilihLayanan)
        {
        case 1:
            addMekanik();
            break;
        case 2:
            editMekanik();
            break;
        case 3:
            deleteMekanik();
            break;
        case 4:
            loadMekanik();
            break;
        case 5:
            admin();
            break;
        }

    } while (pilihLayanan < 1 || pilihLayanan > 4);
}
void deleteMekanik()
{
    displayMekanikData();

    int pilihLayanan;
    string deleteID;

    cout << "Masukkan ID Mekanik yang akan di-delete: ";
    cin >> deleteID;

    // Open the input file (account_mekanik.txt) and create a temporary output file (temp.txt)
    ifstream inFile(dataMekanik);
    ofstream outFile("temp.txt");

    // Check if both files are open
    if (inFile.is_open() && outFile.is_open())
    {
        // Declare variables to store Mekanik data
        string id, storedNama, storedJadwal, storedHarga;
        bool found = false;

        // Loop through each line in the input file
        while (getline(inFile, id, '|') &&
               getline(inFile, storedNama, '|') &&
               getline(inFile, storedJadwal, '|') &&
               getline(inFile, storedHarga))
        {
            // Check if the current Mekanik's ID matches the target ID
            if (id == deleteID)
            {
                // Mekanik found, set the 'found' flag to true
                found = true;
            }
            else
            {
                // Mekanik not found, write its data to the temporary file
                outFile << id << "|" << storedNama << "|" << storedJadwal << "|" << storedHarga << endl;
            }
        }

        // Close both input and output files
        inFile.close();
        outFile.close();

        // Check if the Mekanik with the specified ID was found
        if (found)
        {
            // Remove the original file (account_mekanik.txt)
            remove(dataMekanik.c_str());

            // Rename the temporary file (temp.txt) to the original filename (account_mekanik.txt)
            rename("temp.txt", dataMekanik.c_str());

            // Display a success message
            cout << "Mekanik berhasil dihapus." << endl;
        }
        else
        {
            // Mekanik not found, remove the temporary file and display a message
            remove("temp.txt");
            cout << "Mekanik dengan ID " << deleteID << " tidak ditemukan." << endl;
        }
    }
    else
    {
        // Display an error message if there was an issue opening the files
        cout << "Error opening files." << endl;
    }

    do
    {
        cout << "1. Tambah Mekanik" << endl << "2. Edit Mekanik" << endl << "3. Hapus Mekanik" << endl << "4. Tampilkan Mekanik" << endl << "5. Kembali ke Admin" << endl;
        cout << "Pilih Layanan: ";
        cin >> pilihLayanan;

        switch (pilihLayanan)
        {
        case 1:
            addMekanik();
            break;
        case 2:
            editMekanik();
            break;
        case 3:
            deleteMekanik();
            break;
        case 4:
            loadMekanik();
            break;
        case 5:
            admin();
            break;
        }

    } while (pilihLayanan < 1 || pilihLayanan > 4);
}
void loadMekanik()
{
    displayMekanikData();

    int pilihLayanan;
    
    do
    {
        cout << "1. Tambah Mekanik" << endl << "2. Edit Mekanik" << endl << "3. Hapus Mekanik" << endl << "4. Tampilkan Mekanik" << endl << "5. Kembali ke Admin" << endl;
        cout << "Pilih Layanan: ";
        cin >> pilihLayanan;

        switch (pilihLayanan)
        {
        case 1:
            addMekanik();
            break;
        case 2:
            editMekanik();
            break;
        case 3:
            deleteMekanik();
            break;
        case 4:
            loadMekanik();
            break;
        case 5:
            admin();
            break;
        }

    } while (pilihLayanan < 1 || pilihLayanan > 4);
}

void displayMekanikData()
{
    ifstream inFile(dataMekanik);

    if (inFile.is_open())
    {
        string id, nama, jadwal, harga;

        cout << "Existing Mekanik Data:" << endl;

        while (getline(inFile, id, '|') &&
               getline(inFile, nama, '|') &&
               getline(inFile, jadwal, '|') &&
               getline(inFile, harga))
        {
            cout << "ID: " << id << endl;
            cout << "Nama: " << nama << endl;
            cout << "Jadwal: " << jadwal << endl;
            cout << "Harga: " << harga << endl;

            cout << "-----------------------------" << endl;
        }

        inFile.close();
    }
    else
    {
        cout << "Unable to open file for reading." << endl;
    }
}

void displayMekanikJadwal(string jadwalMekanik)
{
    ifstream inFile(dataMekanik);

    if (inFile.is_open())
    {
        int counter = 1;
        string id, nama, jadwal, harga;

        while (getline(inFile, id, '|') &&
               getline(inFile, nama, '|') &&
               getline(inFile, jadwal, '|') &&
               getline(inFile, harga))
        {
            if (jadwalMekanik == jadwal)
            {
                cout << counter <<". " << nama << " - Rp" << harga << " -- ID " << id << endl;    
                counter++;
            }
        }

        inFile.close();
    }
    else
    {
        cout << "Unable to open file for reading." << endl;
    }
}

bool isValidMekanikID(int pilihMekanik, const string& jadwal)
{
    ifstream inFile(dataMekanik);

    if (inFile.is_open())
    {
        string id, nama, jadwalMekanik, harga;
        int temporaryID;

        while (getline(inFile, id, '|') &&
               getline(inFile, nama, '|') &&
               getline(inFile, jadwalMekanik, '|') &&
               getline(inFile, harga))
        {
            temporaryID = stoi(id);
            if (temporaryID == pilihMekanik && jadwal == jadwalMekanik)
            {
                inFile.close();
                return true; // Valid Mekanik ID
            }
        }

        inFile.close();
    }
    else
    {
        cout << "Unable to open file for reading." << endl;
    }

    return false; // Invalid Mekanik ID
}

bool isValidBelanjaID(int pilihBelanja, const string& barang)
{
    ifstream inFile(dataBelanja);

    if (inFile.is_open())
    {
        string id, barangSparepart, jenisBarang, harga;
        int temporaryID;

        while (getline(inFile, id, '|') &&
               getline(inFile, jenisBarang, '|') &&
               getline(inFile, barangSparepart, '|') &&
               getline(inFile, harga))
        {
            temporaryID = stoi(id);
            if (temporaryID == pilihBelanja && barang == jenisBarang)
            {
                inFile.close();
                return true; // Valid Mekanik ID
            }
        }

        inFile.close();
    }
    else
    {
        cout << "Unable to open file for reading." << endl;
    }

    return false; // Invalid Spare-part ID
}

void addBelanja()
{
    string lastID = getLastBelanjaID();
    string nextID = generateNextID(lastID);
    string barang, jenis, harga;
    int pilihJenis, pilihLayanan;

    do
    {
        cout << "1. Motor" << endl << "2. Mobil" << endl << "3. Sepeda" << endl;
        cout << "Jenis Spare-part: ";
        cin >> pilihJenis;

        switch (pilihJenis)
        {
        case 1:
            jenis = "motor";
            break;
        case 2:
            jenis = "mobil";
            break;
        case 3:
            jenis = "sepeda";
            break;
        }

    } while (pilihJenis < 1 || pilihJenis > 3);

    cout << "Nama Spare-part: ";
    cin.ignore(); // Clear newline character from the buffer
    getline(cin, barang);

    do
    {
        cout << "Harga Spare-part: ";
        getline(cin, harga);
    } while (!isNumeric(harga));
    
    
    ofstream outFile(dataBelanja, ios::app); // Open file in append mode
    if (outFile.is_open())
    {
        outFile << nextID << "|" << jenis << "|" << barang << "|" << harga << endl;
        outFile.close();
        cout << "Spare-part berhasil ditambahkan." << endl;
    }

    do
    {
        cout << "1. Tambah Belanja" << endl << "2. Edit Belanja" << endl << "3. Hapus Belanja" << endl << "4. Tampilkan Belanja" << endl << "5. Kembali ke Admin" << endl;
        cout << "Pilih Layanan: ";
        cin >> pilihLayanan;

        switch (pilihLayanan)
        {
        case 1:
            addBelanja();
            break;
        case 2:
            editBelanja();
            break;
        case 3:
            deleteBelanja();
            break;
        case 4:
            loadBelanja();
            break;
        case 5:
            admin();
            break;
        }

    } while (pilihLayanan < 1 || pilihLayanan > 4);
}
void editBelanja()
{
    displayBelanjaData();

    string editID, belanja, jenis, harga;
    int pilihJenis, pilihLayanan;

    cout << "Masukkan ID spare-part yang akan di-edit: ";
    cin >> editID;

    ifstream inFile(dataBelanja);
    ofstream tempFile("tempBelanja.txt");

    if (inFile.is_open() && tempFile.is_open())
    {
        string id, storedBelanja, storedJenis, storedHarga;
        bool found = false;

        while (getline(inFile, id, '|') &&
               getline(inFile, storedJenis, '|') &&
               getline(inFile, storedBelanja, '|') &&
               getline(inFile, storedHarga))
        {
            if (id == editID)
            {
                found = true;
                cout << "Nama Spare-part: ";
                cin.ignore(); // Clear newline character from the buffer
                getline(cin, belanja);

                do
                {
                    cout << "1. Motor" << endl << "2. Mobil" << endl << "3. Sepeda" << endl;
                    cout << "jenis Servis: ";
                    cin >> pilihJenis;

                    switch (pilihJenis)
                    {
                    case 1:
                        jenis = "motor";
                        break;
                    case 2:
                        jenis = "mobil";
                        break;
                    case 3:
                        jenis = "sepeda";
                        break;
                    }

                } while (pilihJenis < 1 || pilihJenis > 3);

                do
                {
                    cout << "Harga Spare-part: ";
                    cin >> harga;
                } while (!isNumeric(harga));

                tempFile << id << "|" << jenis << "|" << belanja << "|" << harga << endl;
                cout << "Mekanik berhasil di-edit." << endl;
            }
            else
            {
                tempFile << id << "|" << storedJenis << "|" << storedBelanja << "|" << storedHarga << endl;
            }
        }

        inFile.close();
        tempFile.close();

        remove(dataBelanja.c_str());
        rename("tempBelanja.txt", dataBelanja.c_str());

        if (!found)
        {
            cout << "ID spare-part tidak ditemukan." << endl;
        }
    }
    else
    {
        cout << "Unable to open file for reading or writing." << endl;
    }

    do
    {
        cout << "1. Tambah Belanja" << endl << "2. Edit Belanja" << endl << "3. Hapus Belanja" << endl << "4. Tampilkan Belanja" << endl << "5. Kembali ke Admin" << endl;
        cout << "Pilih Layanan: ";
        cin >> pilihLayanan;

        switch (pilihLayanan)
        {
        case 1:
            addBelanja();
            break;
        case 2:
            editBelanja();
            break;
        case 3:
            deleteBelanja();
            break;
        case 4:
            loadBelanja();
            break;
        case 5:
            admin();
            break;
        }

    } while (pilihLayanan < 1 || pilihLayanan > 4);
}
void deleteBelanja()
{
    displayBelanjaData();

    int pilihLayanan;
    string deleteID;

    cout << "Masukkan ID spare-part yang akan di-delete: ";
    cin >> deleteID;

    // Open the input file (account_mekanik.txt) and create a temporary output file (temp.txt)
    ifstream inFile(dataBelanja);
    ofstream outFile("temp.txt");

    // Check if both files are open
    if (inFile.is_open() && outFile.is_open())
    {
        // Declare variables to store Mekanik data
        string id, storedBarang, storedJenis, storedHarga;
        bool found = false;

        // Loop through each line in the input file
        while (getline(inFile, id, '|') &&
               getline(inFile, storedJenis, '|') &&
               getline(inFile, storedBarang, '|') &&
               getline(inFile, storedHarga))
        {
            // Check if the current Mekanik's ID matches the target ID
            if (id == deleteID)
            {
                // Mekanik found, set the 'found' flag to true
                found = true;
            }
            else
            {
                // Mekanik not found, write its data to the temporary file
                outFile << id << "|" << storedJenis << "|" << storedBarang << "|" << storedHarga << endl;
            }
        }

        // Close both input and output files
        inFile.close();
        outFile.close();

        // Check if the Mekanik with the specified ID was found
        if (found)
        {
            // Remove the original file (account_mekanik.txt)
            remove(dataBelanja.c_str());

            // Rename the temporary file (temp.txt) to the original filename (account_mekanik.txt)
            rename("temp.txt", dataBelanja.c_str());

            // Display a success message
            cout << "Mekanik berhasil dihapus." << endl;
        }
        else
        {
            // Mekanik not found, remove the temporary file and display a message
            remove("temp.txt");
            cout << "Spare-part dengan ID " << deleteID << " tidak ditemukan." << endl;
        }
    }
    else
    {
        // Display an error message if there was an issue opening the files
        cout << "Error opening files." << endl;
    }

    do
    {
        cout << "1. Tambah Belanja" << endl << "2. Edit Belanja" << endl << "3. Hapus Belanja" << endl << "4. Tampilkan Belanja" << endl << "5. Kembali ke Admin" << endl;
        cout << "Pilih Layanan: ";
        cin >> pilihLayanan;

        switch (pilihLayanan)
        {
        case 1:
            addBelanja();
            break;
        case 2:
            editBelanja();
            break;
        case 3:
            deleteBelanja();
            break;
        case 4:
            loadBelanja();
            break;
        case 5:
            admin();
            break;
        }

    } while (pilihLayanan < 1 || pilihLayanan > 4);
}
void loadBelanja()
{
    displayBelanjaData();

    int pilihLayanan;

    do
    {
        cout << "1. Tambah Belanja" << endl << "2. Edit Belanja" << endl << "3. Hapus Belanja" << endl << "4. Tampilkan Belanja" << endl << "5. Kembali ke Admin" << endl;
        cout << "Pilih Layanan: ";
        cin >> pilihLayanan;

        switch (pilihLayanan)
        {
        case 1:
            addBelanja();
            break;
        case 2:
            editBelanja();
            break;
        case 3:
            deleteBelanja();
            break;
        case 4:
            loadBelanja();
            break;
        case 5:
            admin();
            break;
        }

    } while (pilihLayanan < 1 || pilihLayanan > 4);
}

void displayBelanjaData()
{
    ifstream inFile(dataBelanja);

    if (inFile.is_open())
    {
        string id, jenis, barang, harga;

        cout << "Existing Belanja Data:" << endl;

        while (inFile >> id >> jenis >> barang)
        {
            // Read the rest of the line into the harga variable
            getline(inFile >> ws, harga);

            cout << "ID: " << id << endl;
            cout << "Jenis: " << jenis << endl;
            cout << "Spare-part: " << barang << endl;
            cout << "Harga: " << harga << endl;

            cout << "-----------------------------" << endl;
        }

        inFile.close();
    }
    else
    {
        cout << "Unable to open file for reading." << endl;
    }
}

void displayJenisBelanja(string jenisBelanja)
{
    ifstream inFile(dataBelanja);

    if (inFile.is_open())
    {
        int counter = 1;
        string id, jenis, barang, harga;

        while (getline(inFile, id, '|') &&
               getline(inFile, jenis, '|') &&
               getline(inFile, barang, '|') &&
               getline(inFile, harga))
        {
            if (jenisBelanja == jenis)
            {
                cout << counter <<". " << barang << " - Rp" << harga << " -- ID " << id << endl;    
                counter++;
            }
        }

        inFile.close();
    }
    else
    {
        cout << "Unable to open file for reading." << endl;
    }
}

// Function to get the last ID from account_belanja.txt
string getLastBelanjaID()
{
    ifstream inFile(dataBelanja);
    string lastID;

    if (inFile.is_open())
    {
        string line;
        while (getline(inFile, line))
        {
            istringstream iss(line);
            iss >> lastID; // Assuming the ID is the first item in the line
        }

        inFile.close();
    }

    return lastID;
}

// Function to get the last ID from account_mekanik.txt
string getLastMekanikID()
{
    ifstream inFile(dataMekanik);
    string lastID;

    if (inFile.is_open())
    {
        string line;
        while (getline(inFile, line))
        {
            istringstream iss(line);
            iss >> lastID; // Assuming the ID is the first item in the line
        }

        inFile.close();
    }

    return lastID;
}

// Function to generate the next ID based on the last ID
string generateNextID(const string& lastID)
{
    if (lastID.empty())
    {
        return "1";
    }

    int nextID = stoi(lastID) + 1;
    return to_string(nextID);
}

void akun()
{
    string konfirmasi;
    do
    {
        cout << "Sudah punya akun? (y/n): ";
        getline(cin, konfirmasi);

        if (konfirmasi == "y")
        {
            login();
        }
        else if (konfirmasi == "n")
        {
            registrasi();
            cout << "Registrasi berhasil. Silakan login.\n";
            login();
        }
        
    } while (!accountFound);
}