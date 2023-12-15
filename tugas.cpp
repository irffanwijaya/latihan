#include <iostream>
#include <string>

using namespace std;

// void chipper(string plain, int key)
// {
//     string ciphertext = "";

//     for (char &c : plain)
//     {
//         if (c == ' ')
//         {
//             c = ' ';
//         }
//         if (isalpha(c))
//         {
//             char base = isupper(c) ? 'A' : 'a';
//             c = (c - base + key) % 26 + base;
//         }
//         ciphertext += c;
//     }
//     cout << ciphertext << endl;
// }

// void encryptVigenere(const string &plaintext, const string &key)
// {
//     string ciphertext = "";
//     int keyLength = key.length();

//     for (int i = 0; i < plaintext.length(); ++i)
//     {
//         char plainChar = plaintext[i];

//         // Jika karakter merupakan huruf alfabet
//         if (isalpha(plainChar))
//         {
//             char keyChar = key[i % keyLength];
//             keyChar = toupper(keyChar); // Pastikan kunci dalam huruf kapital

//             char encryptedChar = ((toupper(plainChar) + keyChar - 2 * 'A') % 26) + 'A';

//             // Jaga karakter untuk tetap huruf kecil jika karakter asli juga huruf kecil
//             if (islower(plainChar))
//             {
//                 encryptedChar = tolower(encryptedChar);
//             }

//             ciphertext += encryptedChar;
//         }
//         else
//         {
//             // Jika karakter bukan huruf alfabet, tambahkan langsung ke ciphertext
//             ciphertext += plainChar;
//         }
//     }

//     cout << ciphertext << endl;
// }

// void encryptBeaufort(string plaintext, string key)
// {
//     string ciphertext = "";
//     int keyLength = key.length();
//     int spaces = 0; // Menyimpan jumlah spasi pada plaintext

//     for (char &c : plaintext)
//     {
//         if (c == ' ')
//         {
//             // Pertahankan spasi
//             ciphertext += ' ';
//             spaces++;
//         }
//         else if (isalpha(c))
//         {
//             char base = isupper(c) ? 'A' : 'a';
//             char encryptedChar = ('Z' - (key[(c - spaces) % keyLength] - base) + c) % 26 + base;
//             ciphertext += encryptedChar;
//         }
//     }
//     cout << ciphertext << endl;
// }

int main()
{
    int pilih, a;
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
        system("cls");
        cout << "Masukan Text : ";
        cin.ignore();
        getline(cin, plain);
        cout << "Masukan Key : ";
        cin >> key;
        a = stoi(key);
        chipper(plain, a);
        break;
    case 2:
        system("cls");
        cout << "Masukan Text : ";
        cin.ignore();
        getline(cin, plain);
        cout << "Masukan Key : ";
        cin >> key;
        encryptVigenere(plain, key);
        break;
    case 3:
        system("cls");
        cout << "Masukan Text : ";
        cin.ignore();
        getline(cin, plain);
        cout << "Masukan Key : ";
        cin >> key;
        encryptBeaufort(plain, key);
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