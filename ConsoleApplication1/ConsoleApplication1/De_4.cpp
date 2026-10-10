#include <iostream>
#include <string>
#include <cctype>
#include <fstream>

using namespace std;

struct Product {
    string Id;
    string Name;
    double price= 0;
};

Product* ds = nullptr;
int n = 0;

string path = "C:\\Users\\HOME\\OneDrive\\Desktop\\hoc\\github\\kynanglaptrinh\\chuong6\\chuong 6\\ConsoleApplication1\\product.dat";
// Chuyen Id thanh chu hoa
string toUpperString(string s) {

    for (int i = 0; i < s.length(); i++) {
        s[i] = toupper((unsigned char)s[i]);
    }

    return s;
}

// Kiem tra Id co bi trung hay khong
bool trungId(string id, int soLuong) {

    for (int i = 0; i < soLuong; i++) {

        if (ds[i].Id == id) {
            return true;
        }
    }

    return false;
}
bool kiemTraDanhSach() {

    if (ds == nullptr || n == 0) {

        cout << "Chua co danh sach product!\n";
        cout << "Vui long chon 1 de nhap danh sach product!\n";

        return false;
    }

    return true;
}
// In danh sach san pham
void inDanhSach() {

    cout << "\n";
    cout << "Id\tName\t\t\tPrice\n";
    cout << "................................................\n";

    for (int i = 0; i < n; i++) {

        cout << ds[i].Id << "\t:\t"
            << ds[i].Name << "\t\t:\t"
            << ds[i].price << endl;
    }
}
#pragma region cau a 

void nhapDanhSach() {

    while (true) {

        cout << "Number of Product: ";
        cin >> n;

        if (cin.fail() || n <= 0) {

            cin.clear();
            cin.ignore(1000, '\n');

            cout << "Number of Product khong hop le! Vui long nhap lai.\n";
            continue;
        }

        cin.ignore(1000, '\n');
        break;
    }

    // Cap phat mang
    delete[] ds;
    ds = new Product[n];

    for (int i = 0; i < n; i++) {

        cout << "Product Id: ";

        while (true) {

            getline(cin, ds[i].Id);

            // Chuyen Id thanh chu hoa
            ds[i].Id = toUpperString(ds[i].Id);

            // Kiem tra Id rong
            if (ds[i].Id.empty()) {

                cout << "Product Id khong duoc de trong!\n";
                cout << "Product Id: ";

                continue;
            }

            // Kiem tra trung Id
            if (trungId(ds[i].Id, i)) {

                cout << "Duplicate Product Id!\n";
                cout << "Product Id: ";

                continue;
            }

            break;
        }

        cout << "Product Name: ";
        getline(cin, ds[i].Name);


        cout << "Price: ";

        while (true) {

            cin >> ds[i].price;

            if (cin.fail() || ds[i].price < 0) {

                cin.clear();
                cin.ignore(1000, '\n');

                cout << "Price khong hop le! Vui long nhap lai.\n";
                cout << "Price: ";

                continue;
            }

            // Kiem tra ky tu thua sau gia
            char kyTu;
            if (cin.get(kyTu) && kyTu != '\n') {

                cin.clear();
                cin.ignore(1000, '\n');

                cout << "Price khong hop le! Vui long nhap lai.\n";
                cout << "Price: ";

                continue;
            }

            break;
        }

    }

    // In danh sach sau khi nhap
    inDanhSach();
}
#pragma endregion
#pragma region cau b

void ghiFileNhiPhan() {

    ofstream file(path, ios::binary);

    if (!file) {

        cout << "Khong mo duoc file!\n";

        return;
    }

    // Ghi so luong san pham
    file.write((char*)&n, sizeof(n));

    // Ghi danh sach san pham
    for (int i = 0; i < n; i++) {

        // Ghi Id
        int doDai = static_cast<int>(ds[i].Id.length());

        file.write((char*)&doDai, sizeof(doDai));
        file.write(ds[i].Id.c_str(), doDai);

        // Ghi Name
        doDai = static_cast<int>(ds[i].Name.length());

        file.write((char*)&doDai, sizeof(doDai));
        file.write(ds[i].Name.c_str(), doDai);

        // Ghi price
        file.write((char*)&ds[i].price,
            sizeof(ds[i].price));
    }

    file.close();

    cout << "Write file successfully!\n";
}

#pragma endregion
#pragma region cau c

void docFileNhiPhan() {

    ifstream file(path, ios::binary);

    if (!file) {

        cout << "Khong mo duoc file!\n";

        return;
    }

    // Doc so luong san pham
    int soLuongFile;

    file.read((char*)&soLuongFile, sizeof(soLuongFile));

    if (soLuongFile <= 0) {

        cout << "File khong co du lieu!\n";

        file.close();

        return;
    }

    // Tao danh sach rieng de doc file
    Product* dsFile = new Product[soLuongFile];

    for (int i = 0; i < soLuongFile; i++) {

        int doDai;

        // Doc Id
        file.read((char*)&doDai, sizeof(doDai));

        dsFile[i].Id.resize(doDai);

        file.read(&dsFile[i].Id[0], doDai);

        // Doc Name
        file.read((char*)&doDai, sizeof(doDai));

        dsFile[i].Name.resize(doDai);

        file.read(&dsFile[i].Name[0], doDai);

        // Doc price
        file.read((char*)&dsFile[i].price,
            sizeof(dsFile[i].price));
    }

    file.close();

    cout << "Read file successfully!\n";

    // In danh sach doc tu file
    cout << "\n";
    cout << "Id\tName\t\t\tPrice\n";
    cout << "................................................\n";

    for (int i = 0; i < soLuongFile; i++) {

        cout << dsFile[i].Id << "\t:\t"
            << dsFile[i].Name << "\t\t:\t"
            << dsFile[i].price << endl;
    }

    // Xoa danh sach doc tu file
    delete[] dsFile;
}

#pragma endregion
#pragma region cau d

void sapXepTheoGia() {

    for (int i = 0; i < n - 1; i++) {

        for (int j = i + 1; j < n; j++) {

            if (ds[i].price < ds[j].price) {

                Product temp = ds[i];
                ds[i] = ds[j];
                ds[j] = temp;
            }
        }
    }

    cout << "\n";
    cout << "Id\tName\t\t\tPrice\n";
    cout << "................................................\n";

    for (int i = 0; i < n; i++) {

        cout << ds[i].Id << "\t:\t"
            << ds[i].Name << "\t\t:\t"
            << ds[i].price << endl;
    }
}

#pragma endregion
#pragma region cau e

void sapXepTheoTen() {

    for (int i = 0; i < n - 1; i++) {

        for (int j = i + 1; j < n; j++) {

            if (ds[i].Name > ds[j].Name) {

                Product temp = ds[i];
                ds[i] = ds[j];
                ds[j] = temp;
            }
        }
    }

    cout << "\n";
    cout << "Id\tName\t\t\tPrice\n";
    cout << "................................................\n";

    for (int i = 0; i < n; i++) {

        cout << ds[i].Id << "\t:\t"
            << ds[i].Name << "\t\t:\t"
            << ds[i].price << endl;
    }
}

#pragma endregion

int main() {

    int chon;

    do {

        cout << "\nPRODUCT MANAGER\n";
        cout << "1. Init list\n";
        cout << "2. Write to file\n";
        cout << "3. Read from file\n";
        cout << "4. Sort by price\n";
        cout << "5. Sort by product name\n";
        cout << "Other number: exit\n";

        cout << "Choose: ";
        cin >> chon;
        cin.ignore(1000, '\n');

        switch (chon) {

        case 1:
            nhapDanhSach();
            break;

        case 2:
            if (kiemTraDanhSach()) {
                ghiFileNhiPhan();
            }

            break;

        case 3:
            if (kiemTraDanhSach()) {
                docFileNhiPhan();

            }           
            break;

        case 4:
            if (kiemTraDanhSach()) {
                sapXepTheoGia();

            }            
            break;

        case 5:
            if (kiemTraDanhSach()) {
                sapXepTheoTen();
            }            
            break;

        default:
            cout << "Exit!\n";
        }

    } while (chon >= 1 && chon <= 5);

    delete[] ds;

    return 0;
}