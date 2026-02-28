#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Ham chuan hoa chuoi
string formatString(string str) {
    string formatted = "";
    for (int i = 0; i < str.length(); i++) {
        char c = str[i];
        if (isalpha(c)) {
            c = toupper(c);
            if (c == 'J') c = 'I'; 
            formatted += c;
        }
    }
    return formatted;
}

// Ham tao ma tran khoa 5x5
void generateKeyTable(string key, char keyTable[5][5]) {
    key = formatString(key); 
    bool dict[26] = {false};
    int r = 0, c = 0;

    for (int i = 0; i < key.length(); i++) {
        char ch = key[i];
        if (!dict[ch - 'A']) {
            dict[ch - 'A'] = true;
            keyTable[r][c] = ch;
            c++;
            if (c == 5) {
                c = 0;
                r++;
            }
        }
    }

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue;
        if (!dict[ch - 'A']) {
            keyTable[r][c] = ch;
            c++;
            if (c == 5) {
                c = 0;
                r++;
            }
        }
    }
}

// Ham tim vi tri trong ma tran
void search(char keyTable[5][5], char a, char b, int pos[]) {
    if (a == 'J') a = 'I';
    if (b == 'J') b = 'I';

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (keyTable[i][j] == a) {
                pos[0] = i;
                pos[1] = j;
            } else if (keyTable[i][j] == b) {
                pos[2] = i;
                pos[3] = j;
            }
        }
    }
}

// chia cap
string pairText(string text) {
    text = formatString(text);
    string pair = "";
    for (int i = 0; i < text.length(); i += 2) {
        pair += text[i];
        if (i + 1 < text.length()) {
            if (text[i] == text[i + 1]) {
                pair += 'X';
                i--; 
            } else {
                pair += text[i + 1];
            }
        }
    }
    if (pair.length() % 2 != 0) {
        pair += 'X';
    }
    return pair;
}

// Ham ma hoa/giai ma
string playfairProcess(string text, char keyTable[5][5], int direction) {
    string result = "";
    int pos[4];
    
    for (int i = 0; i < text.length(); i += 2) {
        search(keyTable, text[i], text[i + 1], pos);
        int r1 = pos[0], c1 = pos[1];
        int r2 = pos[2], c2 = pos[3];

        if (r1 == r2) { 
            result += keyTable[r1][(c1 + direction + 5) % 5];
            result += keyTable[r2][(c2 + direction + 5) % 5];
        } else if (c1 == c2) { 
            result += keyTable[(r1 + direction + 5) % 5][c1];
            result += keyTable[(r2 + direction + 5) % 5][c2];
        } else { 
            result += keyTable[r1][c2];
            result += keyTable[r2][c1];
        }
    }
    return result;
}

// Ham in ma tran
void printMatrix(char keyTable[5][5]) {
    cout << "\n[ Ma tran khoa 5x5 hien tai ]\n";
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << keyTable[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    string key, plaintext;
    char keyTable[5][5];
    int choice;

    cout << "=== THUAT TOAN PLAYFAIR ===\n";
    
    cout << "Vui long nhap tu khoa (Key) ban dau de khoi tao: ";
    getline(cin, key);
    key = formatString(key); 
    
    generateKeyTable(key, keyTable);
    printMatrix(keyTable);
    
    while (true) {
        cout << "\n================= MENU ================\n";
        cout << "1. Ma hoa & Giai ma (Key dang dung: " << (key.empty() ? "Khong co" : key) << ")\n";
        cout << "2. Thay doi Key\n";
        cout << "3. Thoat\n";
        cout << "=======================================\n";
        cout << "Nhap lua chon cua ban (1-3): ";
        
        cin >> choice;
        cin.ignore(); 

        if (choice == 3) {
            cout << "Da thoat \n";
            break;
        } 
        else if (choice == 2) {
            cout << "\nNhap tu khoa (Key) MOI: ";
            getline(cin, key);
            key = formatString(key);
            
            generateKeyTable(key, keyTable);
            cout << "=> Da cap nhat Key thanh cong!\n";
            printMatrix(keyTable);
        } 
        else if (choice == 1) {
            cout << "\nNhap van ban can ma hoa (Plaintext): ";
            getline(cin, plaintext);

            string newText = pairText(plaintext);
            cout << "Van ban sau khi xu ly (Digraphs): " << newText << "\n";

            string ciphertext = playfairProcess(newText, keyTable, 1);
            cout << "-> Van ban MA HOA (Ciphertext): " << ciphertext << "\n";

            string decryptedText = playfairProcess(ciphertext, keyTable, -1);
            cout << "-> Van ban GIAI MA (Decrypted text): " << decryptedText << "\n";
        }
        else {
            cout << "Lua chon khong hop le. Vui long nhap tu 1 den 3.\n";
        }
    }

    return 0;
}