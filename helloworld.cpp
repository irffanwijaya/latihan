#include <iostream> //chiper, encryptVigenere, enkripBeaufort, AutoKEY
#include <string>

using namespace std;

string enkripPass(string pass, int key)
{
    string hasil = "";
    for (char &c : pass)
    {
        if (isalpha(c))
        {
            char cek = isupper(c) ? 'A' : 'a';
            c = (c - cek + key) % 26 + cek;
        }
        else if (c == ' ')
        {
            c = ' ';
        }
        else if (isdigit(c))
        {
            c = (c - '0' + key) % 10 + '0';
        }
        hasil += c;
    }
    return hasil;
}

string vigenere(string plain, string key)
{
    cout << key.length() << endl;
}

int main()
{
    int pilih, keys;
    string plain, key;
    cout << "+--------------------------------------------+" << endl;
    cout << "|                 Enkrip                     |" << endl;
    cout << "+--------------------------------------------+" << endl;
    cout << "| 1. Chiper                                  |" << endl;
    cout << "| 2. Vigenere                                |" << endl;
    cout << "| 3. Beaufort                                |" << endl;
    cout << "| 4. Autokey                                 |" << endl;
    cout << "| 0. Exit                                    |" << endl;
    cout << "+--------------------------------------------+" << endl;
    cout << "Pilih menu : ";
    cin >> pilih;

    switch (pilih)
    {
    case 1:
        cout << "Nasukkan text : ";
        cin.ignore();
        getline(cin, plain);
        cout << "Masukkan Key : ";
        cin >> key;
        keys = stoi(key);
        cout << enkripPass(plain, keys);
        break;
    case 2:
        cout << "Nasukkan text : ";
        cin.ignore();
        getline(cin, plain);
        cout << "Masukkan Key : ";
        cin >> key;
        cout << vigenere(plain, key);
        break;
    case 3:
        cout << "Hello World" << endl;
        break;
    case 4:
        cout << "Hello World" << endl;
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
        break;
    }
}