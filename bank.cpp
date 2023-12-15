#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

string file = "data.txt";
int key = 3;

struct akun
{
    string user;
    string password;
    float saldo;
    int pin;
};

vector<akun> dataFile(const string file)
{
    vector<akun> datas;
    ifstream isiData(file);
    if (isiData.is_open())
    {
        string ambil;
        while (getline(isiData, ambil))
        {
            size_t panjang = ambil.find(" ");
            size_t panjang1 = ambil.find(" ", panjang + 1);
            size_t panjang2 = ambil.find(" ", panjang1 + 1);
            if (panjang != string::npos && panjang1 != string::npos && panjang2 != string::npos)
            {
                akun data;
                data.user = ambil.substr(0, panjang);
                data.password = ambil.substr(panjang + 1, panjang1 - panjang - 1);
                data.saldo = stof(ambil.substr(panjang1 + 1, panjang2 - panjang1 - 1));
                data.pin = stoi(ambil.substr(panjang2 + 1));
                datas.push_back(data);
            }
        }
        isiData.close();
    }
    return datas;
}

string enkripPass(string pass, int key)
{
    string hasil = "";
    for (char &c : pass)
    {
        if (isalpha(c))
        {
            char cek = isupper(c) ? 'A' : 'a';
            c = (c - cek + key) % 26 + cek;
            key++;
        }
        else if (isdigit(c))
        {
            c = (c - '0' + key) % 10 + '0';
            key++;
        }
        hasil += c;
    }
    return hasil;
}

string dekrip(string pass, int key)
{
    string hasil = "";
    for (char &c : pass)
    {
        if (isalpha(c))
        {
            char cek = isupper(c) ? 'A' : 'a';
            c = (c - cek - key + 26) % 26 + cek; // 98-97-15 = -14 + 97
            key++;
            if (c == cek - 1)
            {
                c = cek + 25;
            }
        }
        else if (isdigit(c))
        {
            c = (c - '0' - key + 10) % 10 + '0'; // 48 - 48 - 11 + 10
            if (c == '0' - 1)
            {
                c = '0' + 9;
            }
            key++;
        }
        hasil += c;
    }
    return hasil;
}

// luar login
void login(vector<akun> datas);
void daftar();
void lupaPassword(vector<akun> datas);

// dalam login
void menuLogin(string user, string password, float saldo, int pin);
float updateSaldo(string user, string password, float depo, int pin, int pilih)
{
    vector<akun> datas;
    string duser, dpass;
    float dsaldo;
    int dpin, status;
    password = enkripPass(password, key);
    ifstream dataUser("data.txt");
    while (dataUser >> duser >> dpass >> dsaldo >> dpin)
    {
        if (user == duser && password == dpass)
        {
            if (pilih == 1)
            {
                datas.push_back({user, password, depo + dsaldo, pin});
                system("cls");
                cout << "+--------------------------------------------+" << endl;
                cout << "|             Depo Berhasil !!!              |" << endl;
                cout << "+--------------------------------------------+" << endl;
                status = true;
            }
            else if (pilih == 2)
            {
                if (dsaldo >= depo)
                {
                    system("cls");
                    cout << "+--------------------------------------------+" << endl;
                    cout << "|           WithDraw Berhasil !!!            |" << endl;
                    cout << "+--------------------------------------------+" << endl;
                    datas.push_back({user, password, dsaldo - depo, pin});
                    status = true;
                }
                else
                {
                    system("cls");
                    cout << "+--------------------------------------------+" << endl;
                    cout << "|          Saldo Anda Kurang !!!             |" << endl;
                    cout << "+--------------------------------------------+" << endl;
                    return false;
                }
            }
            else if (pilih == 3)
            {
                system("cls");
                cout << "+--------------------------------------------+" << endl;
                cout << "| Saldo Anda : " << dsaldo << "                          |" << endl;
                return true;
            }
        }
        else
        {
            datas.push_back({duser, dpass, dsaldo, dpin});
        }
    }
    dataUser.close();

    ofstream datax("data.txt");
    if (status)
    {
        if (datax.is_open())
        {
            for (const auto &newData : datas)
            {
                datax << newData.user << " " << newData.password << " " << newData.saldo << " " << newData.pin << endl;
            }
            datax.close();
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

int main()
{
    vector<akun> datas = dataFile(file);
    int pilih;
    cout << "+--------------------------------------------+" << endl;
    cout << "|                 Bank Kons                  |" << endl;
    cout << "+--------------------------------------------+" << endl;
    cout << "| 1. Register                                |" << endl;
    cout << "| 2. Login                                   |" << endl;
    cout << "| 3. Lupa Password                           |" << endl;
    cout << "| 0. Exit                                    |" << endl;
    cout << "+--------------------------------------------+" << endl;
    cout << "Pilih menu : ";
    cin >> pilih;

    switch (pilih)
    {
    case 1:
        system("cls");
        daftar();
        break;
    case 2:
        system("cls");
        login(datas);
        break;
    case 3:
        system("cls");
        lupaPassword(datas);
        break;
    case 0:
        cout << "+--------------------------------------------+" << endl;
        cout << "|                Terima Kasih                |" << endl;
        cout << "+--------------------------------------------+" << endl;
        break;
    default:
        system("cls");
        cout << "+--------------------------------------------+" << endl;
        cout << "|          Pilih Sesuai Nomor !!!            |" << endl;
        cout << "+--------------------------------------------+" << endl;
        main();
        break;
    }
}

void menuLogin(string user, string password, float saldo, int pin)
{
awal:
    float depo;
    int pilih;
    cout << "+--------------------------------------------+" << endl;
    cout << "|                 Bank Kons                  |" << endl;
    cout << "+--------------------------------------------+" << endl;
    cout << "| 1. Deposit                                 |" << endl;
    cout << "| 2. Withdraw                                |" << endl;
    cout << "| 3. Cek Saldo                               |" << endl;
    cout << "| 0. Logout                                  |" << endl;
    cout << "+--------------------------------------------+" << endl;
    cout << "Pilih menu : ";
    cin >> pilih;
    switch (pilih)
    {
    case 1:
        cout << "Masukkan Jumlah Depo : ";
        cin >> depo;
        updateSaldo(user, password, depo, pin, pilih);
        goto awal;
    case 2:
        cout << "Masukkkan Jumlah WD : ";
        cin >> depo;
        updateSaldo(user, password, depo, pin, pilih);
        goto awal;
    case 3:
        updateSaldo(user, password, depo, pin, pilih);
        goto awal;
    case 0:
        system("cls");
        cout << "+--------------------------------------------+" << endl;
        cout << "|            Logout Berhasil !!!             |" << endl;
        cout << "+--------------------------------------------+" << endl;
        main();
        break;
    default:
        system("cls");
        cout << "Pilih Sesuai Nomor !!!" << endl;
        main();
        break;
    }
}

void daftar()
{
    string user, pass;
    string dUser, dPass;
    float saldo, dSaldo;
    int pin, dPin, status;
    cout << "+--------------------------------------------+" << endl;
    cout << "|                Pendaftaran                 |" << endl;
    cout << "+--------------------------------------------+" << endl;
    cout << "  Masukkan Username : ";
    cin >> dUser;
    ifstream input("data.txt");
    while (input >> user >> pass >> saldo >> pin)
    {
        if (dUser == user)
        {
            status = 1;
            break;
        }
    }
    input.close();
    if (status == 1)
    {
        system("cls");
        cout << "+--------------------------------------------+" << endl;
        cout << "|          Username Sudah Digunakan          |" << endl;
        cout << "+--------------------------------------------+" << endl;
        daftar();
    }
    else
    {
        cout << "  Masukkan Password : ";
        cin >> dPass;
        cout << "  Masukkan Saldo : ";
        cin >> dSaldo;
        cout << "  Masukkan Pin : ";
        cin >> dPin;
        dPass = enkripPass(dPass, key);
        ofstream f1("data.txt", ios::app);
        f1 << dUser << " " << dPass << " " << dSaldo << " " << dPin << endl;
        system("cls");
        cout << "+--------------------------------------------+" << endl;
        cout << "|               Berhasil Daftar              |" << endl;
        cout << "+--------------------------------------------+" << endl;
        main();
    }
}

void login(vector<akun> datas)
{
    akun login;
    string user, pass, zuser, zpass;
    float zsaldo, saldo;
    int pin, zpin;
    int status;
    system("cls");
ulang:
    cout << "+--------------------------------------------+" << endl;
    cout << "|                   Login                    |" << endl;
    cout << "+--------------------------------------------+" << endl;
    cout << "  Username : ";
    cin >> user;
    cout << "  Password : ";
    cin >> pass;
    ifstream data(file);
    while (data >> zuser >> zpass >> zsaldo >> zpin)
    {
        zpass = dekrip(zpass, key);
        if (user == zuser && pass == zpass)
        {
            status = 1;
            break;
        }
    }
    if (status == 1)
    {
        cout << "  Masukkan Pin : ";
        cin >> pin;
        if (pin == zpin)
        {
            system("cls");
            cout << "+--------------------------------------------+" << endl;
            cout << "|               Login Berhasil               |" << endl;
            cout << "+--------------------------------------------+" << endl;
            menuLogin(zuser, zpass, zsaldo, zpin);
        }
        else
        {
            system("cls");
            cout << "+--------------------------------------------+" << endl;
            cout << "|                PIN SALAH !!!               |" << endl;
            cout << "+--------------------------------------------+" << endl;
            main();
        }
    }
    else
    {
        system("cls");
        cout << "+--------------------------------------------+" << endl;
        cout << "|                Login Gagal                 |" << endl;
        cout << "+--------------------------------------------+" << endl;
        goto ulang;
    }
}

void lupaPassword(vector<akun> datas)
{
    string user, pass;
    bool count = false;
    system("cls");
    cout << "+--------------------------------------------+" << endl;
    cout << "|               Lupa Password                |" << endl;
    cout << "+--------------------------------------------+" << endl;
    cout << "  Username : ";
    cin >> user;
    for (akun &data : datas)
    {
        if (user == data.user)
        {
            count = true;
            cout << "  Masukkan Password Baru : ";
            cin >> pass;
            pass = enkripPass(pass, key);
            data.password = pass;
            break;
        }
    }
    if (!count)
    {
        system("cls");
        cout << "+--------------------------------------------+" << endl;
        cout << "|      " << user << " Tidak ditemukkan       |" << endl;
        cout << "+--------------------------------------------+" << endl;
        main();
    }
    else
    {
        ofstream datax(file);
        if (datax.is_open())
        {
            for (const akun &data : datas)
            {
                datax << data.user << " " << data.password << " " << data.saldo << " " << data.pin << endl;
            }
            system("cls");
            cout << "+--------------------------------------------+" << endl;
            cout << "|              Berhasil Diubah               |" << endl;
            cout << "+--------------------------------------------+" << endl;
            datax.close();
            main();
        }
        else
        {
            cerr << "  Gagal Membuka FILE" << endl;
            main();
        }
    }
}