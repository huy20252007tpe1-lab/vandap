#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct Xe {
    int soXe = 0;
    string loaiXe;
    string mauSac;
    int namSX = 0;
};

Xe* ds = nullptr;
int n = 0;

//string path = "C:\\Users\\HOME\\OneDrive\\Desktop\\hoc\\github\\kynanglaptrinh\\chuong6\\chuong 6\\ConsoleApplication1\\xesample.txt";
string path = "C:\\Users\\HOME\\OneDrive\\Desktop\\hoc\\github\\kynanglaptrinh\\chuong6\\chuong 6\\ConsoleApplication1\\xesampleErr.txt";
bool kiemTraDanhSach() {

    if (ds == nullptr || n == 0) {

        cout << "Chua co danh sach xe!\n";
        cout << "Vui long chon 1 de nhap danh sach tu file!\n";

        return false;
    }

    return true;
}

#pragma region cau a
// Kiem tra chuoi co phai so hay khong
bool laSo(string s) {

    stringstream ss(s);
    int x;

    ss >> x;

    return !ss.fail() && ss.eof();
}


// Kiem tra dong co dung dinh dang hay khong
Xe* kiemTraDong(string dong) {

    Xe* xe = new Xe;
    string phan[4];

    int dem = 0;
    size_t pos;

    while (dem < 3) {

        pos = dong.find('#');

        if (pos == string::npos) {
            delete xe;
            return nullptr;
        }

        phan[dem] = dong.substr(0, pos);

        if (phan[dem].empty()) {
            delete xe;
            return nullptr;
        }

        dong = dong.substr(pos + 1);

        dem++;
    }

    if (dong.empty()) {
        delete xe;
        return nullptr;
    }

    phan[3] = dong;

    // Kiem tra so xe va nam san xuat
    if (!laSo(phan[0]) || !laSo(phan[3])) {
        delete xe;
        return nullptr;
    }

    int soXe = stoi(phan[0]);

    // So xe phai co 5 chu so
    if (soXe < 10000 || soXe > 99999) {
        delete xe;
        return nullptr;
    }

    // Tao Xe
    xe->soXe = soXe;
    xe->loaiXe = phan[1];
    xe->mauSac = phan[2];
    xe->namSX = stoi(phan[3]);

    return xe;
}

// Kiem tra so xe co bi trung hay khong
bool trungSoXe(int soXe, int soLuong) {

    for (int i = 0; i < soLuong; i++) {

        if (ds[i].soXe == soXe)
            return true;
    }

    return false;
}


// Nhap danh sach xe tu file
bool nhapTuFile(string tenFile) {

    ifstream file(tenFile);

    if (!file) {
        cout << "Khong mo duoc file!\n";
        return false;
    }

    string dong;

    // Dem so dong
    n = 0;

    while (getline(file, dong)) {
        n++;
    }

    file.clear();
    file.seekg(0, ios::beg);

    if (n == 0) {

        cout << "File rong!\n";
        delete[] ds;
        ds = nullptr;
        n = 0;
        file.close();

        return true;
    }

    ds = new Xe[n];

    int soDongLoi = 0;
    int soLuongXe = 0;

    while (getline(file, dong)) {

        // Kiem tra dong va lay Xe
        Xe* xe = kiemTraDong(dong);

        // Dong khong hop le
        if (xe == nullptr) {

            cout << "\nDong khong hop le: "
                << dong << endl;

            soDongLoi++;

            continue;
        }

        // Kiem tra so xe trung
        if (trungSoXe(xe->soXe, soLuongXe)) {

            cout << "\nSo xe bi trung: "
                << xe->soXe << endl;

            delete xe;
            soDongLoi++;

            continue;
        }

        // Them xe vao danh sach
        ds[soLuongXe] = *xe;
        soLuongXe++;

        delete xe;
    }

    file.close();

    if (soDongLoi > 0) {

        cout << "\nFile co du lieu khong hop le!\n";

        delete[] ds;
        ds = nullptr;
        n = 0;

        return false;
    }

    cout << "\nNhap file thanh cong!\n";
    cout << "Da nhap " << n << " xe.\n";

    cout << "\n===== DANH SACH XE =====\n";

    for (int i = 0; i < n; i++) {

        cout << ds[i].soXe << " - "
            << ds[i].loaiXe << " - "
            << ds[i].mauSac << " - "
            << ds[i].namSX << endl;
    }

    return true;
}
#pragma endregion
#pragma region cau b


void timKiemTheoSoXe() {

    string input;
    int soXe;

    while (true) {

        cout << "\n===== TIM KIEM XE =====\n";
        cout << "Nhap so xe can tim: ";
        cin >> input;

        // Kiem tra co phai so hay khong
        if (!laSo(input)) {
            cout << "So xe khong hop le! Vui long nhap lai.\n";
            continue;
        }

        // Kiem tra dung 5 chu so
        if (input.length() != 5) {
            cout << "So xe phai co 5 chu so! Vui long nhap lai.\n";
            continue;
        }

        soXe = stoi(input);

        // Tim xe
        for (int i = 0; i < n; i++) {

            if (ds[i].soXe == soXe) {

                cout << "\n===== THONG TIN XE =====\n";
                cout << "So xe: " << ds[i].soXe << endl;
                cout << "Loai xe: " << ds[i].loaiXe << endl;
                cout << "Mau sac: " << ds[i].mauSac << endl;
                cout << "Nam san xuat: " << ds[i].namSX << endl;

                return;
            }
        }

        cout << "Khong tim thay xe!\n";
        return;
    }
}
#pragma endregion
#pragma region cau c
void themXe() {

    Xe xeMoi;
    string input;

    cout << "\n===== THEM XE MOI =====\n";

    // Nhap so xe
    while (true) {

        cout << "Nhap so xe: ";
        cin >> ws;
        getline(cin, input);

        if (!laSo(input)) {
            cout << "So xe khong hop le! Vui long nhap lai.\n";
            continue;
        }

        if (input.length() != 5) {
            cout << "So xe phai co 5 chu so! Vui long nhap lai.\n";
            continue;
        }

        xeMoi.soXe = stoi(input);

        if (trungSoXe(xeMoi.soXe, n)) {
            cout << "So xe da ton tai! Vui long nhap so khac.\n";
            continue;
        }

        break;
    }

    // Nhap loai xe
    cout << "Nhap loai xe: ";
    cin >> ws;
    getline(cin, xeMoi.loaiXe);

    // Nhap mau sac
    cout << "Nhap mau sac: ";
    cin >> ws;
    getline(cin, xeMoi.mauSac);

    // Nhap nam san xuat
    while (true) {

        cout << "Nhap nam san xuat: ";
        cin >> ws;
        getline(cin, input);

        if (!laSo(input)) {
            cout << "Nam san xuat khong hop le! Vui long nhap lai.\n";
            continue;
        }

        xeMoi.namSX = stoi(input);
        break;
    }

    // Tao danh sach moi co them 1 xe
    int soLuongMoi = n + 1;

    Xe* dsMoi = new Xe[soLuongMoi];

    for (int i = 0; i < n; i++) {
        dsMoi[i] = ds[i];
    }

    dsMoi[soLuongMoi - 1] = xeMoi;

    delete[] ds;
    ds = dsMoi;
    n = soLuongMoi;

    cout << "\nThem xe thanh cong!\n";
}
#pragma endregion
#pragma region cau d

void xoaXe() {

    string input;
    int soXe;
    int viTri = -1;

    cout << "\n===== XOA XE =====\n";

    // Nhap so xe can xoa
    while (true) {

        cout << "Nhap so xe can xoa: ";
        getline(cin >> ws, input);

        if (!laSo(input) || input.length() != 5) {
            cout << "So xe khong hop le! Vui long nhap lai.\n";
            continue;
        }

        soXe = stoi(input);
        break;
    }

    // Tim vi tri xe
    for (int i = 0; i < n; i++) {

        if (ds[i].soXe == soXe) {
            viTri = i;
            break;
        }
    }

    if (viTri == -1) {
        cout << "Khong tim thay xe!\n";
        return;
    }

    // In thong tin xe can xoa
    cout << "\n===== THONG TIN XE CAN XOA =====\n";
    cout << "So xe: " << ds[viTri].soXe << endl;
    cout << "Loai xe: " << ds[viTri].loaiXe << endl;
    cout << "Mau sac: " << ds[viTri].mauSac << endl;
    cout << "Nam san xuat: " << ds[viTri].namSX << endl;

    // Dich cac phan tu ve ben trai
    for (int i = viTri; i < n - 1; i++) {
        ds[i] = ds[i + 1];
    }

    n--;

    // Ghi lai danh sach vao file
    ofstream file(path);

    if (!file) {
        cout << "Khong mo duoc file de ghi!\n";
        return;
    }

    for (int i = 0; i < n; i++) {

        file << ds[i].soXe << "#"
            << ds[i].loaiXe << "#"
            << ds[i].mauSac << "#"
            << ds[i].namSX;

        if (i < n - 1) {
            file << endl;
        }
    }

    file.close();

    cout << "\nXoa xe thanh cong!\n";

    // In danh sach xe con lai
    cout << "\n===== DANH SACH XE CON LAI =====\n";

    for (int i = 0; i < n; i++) {

        cout << ds[i].soXe << " - "
            << ds[i].loaiXe << " - "
            << ds[i].mauSac << " - "
            << ds[i].namSX << endl;
    }

}

#pragma endregion
#pragma region cau e
void inDanhSachTheoNamSX() {

    // Sap xep nam san xuat giam dan
    for (int i = 0; i < n - 1; i++) {

        for (int j = i + 1; j < n; j++) {

            if (ds[i].namSX < ds[j].namSX) {

                Xe tam = ds[i];
                ds[i] = ds[j];
                ds[j] = tam;
            }
        }
    }

    // In danh sach
    cout << "\n===== DANH SACH XE THEO NAM SX GIAM DAN =====\n";

    for (int i = 0; i < n; i++) {

        cout << ds[i].soXe << " - "
            << ds[i].loaiXe << " - "
            << ds[i].mauSac << " - "
            << ds[i].namSX << endl;
    }
}
#pragma endregion
#pragma region cau f
string toLowerString(string s) {

    for (int i = 0; i < s.length(); i++) {
        s[i] = tolower(s[i]);
    }

    return s;
}
void inDanhSachCungLoai() {

    if (!kiemTraDanhSach()) {
        return;
    }

    string loaiXe;
    bool timThay = false;

    cout << "\n===== TIM XE CUNG LOAI =====\n";
    cout << "Nhap loai xe: ";
    cin >> ws;
    getline(cin, loaiXe);

    cout << "\n===== DANH SACH XE CUNG LOAI =====\n";

    string loaiXeNhap = toLowerString(loaiXe);

    for (int i = 0; i < n; i++) {

        string loaiXeTrongDanhSach = toLowerString(ds[i].loaiXe);

        if (loaiXeTrongDanhSach == loaiXeNhap) {

            cout << ds[i].soXe << " - "
                << ds[i].loaiXe << " - "
                << ds[i].mauSac << " - "
                << ds[i].namSX << endl;

            timThay = true;
        }
    }

    if (!timThay) {
        cout << "Khong tim thay xe cung loai!\n";
    }
}
#pragma endregion
#pragma region cau g
void thongKeTheoLoai() {

    string loai[100];
    int soLuong[100];

    int soLoai = 0;

    // Thong ke tung loai xe
    for (int i = 0; i < n; i++) {

        string loaiXe = toLowerString(ds[i].loaiXe);

        int viTri = -1;

        // Tim loai xe da ton tai trong danh sach thong ke
        for (int j = 0; j < soLoai; j++) {

            if (loai[j] == loaiXe) {
                viTri = j;
                break;
            }
        }

        // Neu da co loai xe
        if (viTri != -1) {
            soLuong[viTri]++;
        }
        // Neu la loai xe moi
        else {
            loai[soLoai] = loaiXe;
            soLuong[soLoai] = 1;
            soLoai++;
        }
    }

    // In ket qua
    cout << "\n===== THONG KE SO LUONG XE THEO LOAI =====\n";

    for (int i = 0; i < soLoai; i++) {

        cout << loai[i] << ": "
            << soLuong[i] << " xe" << endl;
    }
}
#pragma endregion
#pragma region MyRegion
int tinhSoNut(int soXe) {

    int tong = 0;

    while (soXe > 0) {

        tong += soXe % 10;
        soXe /= 10;
    }

    return tong % 10;
}
void inDanhSach9Nut() {

    if (!kiemTraDanhSach()) {
        return;
    }

    bool timThay = false;

    cout << "\n===== DANH SACH XE 9 NUT =====\n";

    for (int i = 0; i < n; i++) {

        if (tinhSoNut(ds[i].soXe) == 9) {

            cout << ds[i].soXe << " - "
                << ds[i].loaiXe << " - "
                << ds[i].mauSac << " - "
                << ds[i].namSX << endl;

            timThay = true;
        }
    }

    if (!timThay) {
        cout << "Khong co xe nao co bang so 9 nut!\n";
    }
}
#pragma endregion



int main() {

    int chon;

    do {

        cout << "\n========== MENU ==========\n";

        cout << "1. Nhap danh sach xe tu file\n";              // a
        cout << "2. Tim kiem xe theo so xe\n";                // b
        cout << "3. Them xe moi\n";                          // c
        cout << "4. Xoa xe theo so xe\n";                    // d
        cout << "5. In danh sach xe theo nam SX giam dan\n"; // e
        cout << "6. In danh sach xe cung loai\n";            // f
        cout << "7. Thong ke so luong xe theo tung loai\n";  // g
        cout << "8. In danh sach xe co bang so 9 nut\n";     // h
        cout << "0. Thoat\n";

        cout << "==========================\n";

        cout << "Chon: ";
        cin >> chon;
        cin.ignore(1000, '\n');

        switch (chon) {

        case 1:

            if (!nhapTuFile(path)) {
                return 0;
            }

            break;

        case 2:

            if (kiemTraDanhSach()) {
                timKiemTheoSoXe();
            }
            break;

        case 3:

            if (kiemTraDanhSach()) {
                themXe();
            }
            break;

        case 4:

            if (kiemTraDanhSach()) {
                xoaXe();
            }
            break;

        case 5:

            if (kiemTraDanhSach()) {
                inDanhSachTheoNamSX();
            }
            break;

        case 6:

            if (kiemTraDanhSach()) {
                inDanhSachCungLoai();
            }
            break;

        case 7:
            if (kiemTraDanhSach()) {
                thongKeTheoLoai();
            }
            break;

        case 8:
            if (kiemTraDanhSach()) {
                inDanhSach9Nut();
            }
            break;

        default:

            cout << "Lua chon khong hop le!\n";
        }

    } while (chon != 0);


    // Giai phong bo nho
    delete[] ds;

    return 0;
}