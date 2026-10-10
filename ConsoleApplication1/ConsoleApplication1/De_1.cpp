#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <iomanip>
using namespace std;

struct SinhVien {
    string mssv;
    string ho;
    string ten;
    float diemMon1 = 0;
    float diemMon2 = 0;
};

SinhVien* ds = nullptr;
int n = 0;

string path = "C:\\Users\\HOME\\OneDrive\\Desktop\\hoc\\github\\kynanglaptrinh\\chuong6\\chuong 6\\ConsoleApplication1\\sinhvien.txt";

#pragma region cau a

// Chuyen mot dong trong file thanh thong tin sinh vien.
// Chi goi ham nay sau khi dong da duoc kiem tra hop le.
SinhVien tachDong(string dong) {
    SinhVien sv;
    string phan[5];
    size_t pos;

    for (int i = 0; i < 4; i++) {
        pos = dong.find('-');
        phan[i] = dong.substr(0, pos);
        dong = dong.substr(pos + 1);
    }

    phan[4] = dong;

    sv.mssv = phan[0];
    sv.ho = phan[1];
    sv.ten = phan[2];
    sv.diemMon1 = stof(phan[3]);
    sv.diemMon2 = stof(phan[4]);

    return sv;
}

bool laSo(string s) {

    stringstream ss(s);
    float x;

    ss >> x;

    if (ss.fail()) {
        return false;
    }

    ss >> ws;

    return ss.eof();
}

bool diemHopLe(string diem) {
    if (!laSo(diem)) {
        return false;
    }

    float x = stof(diem);
    return x >= 0 && x <= 10;
}

// Kiem tra dong co dung dinh dang MSSV-Ho-Ten-Diem1-Diem2 hay khong.
bool kiemTraDong(string dong) {
    string phan[5];
    size_t pos;

    for (int i = 0; i < 4; i++) {
        pos = dong.find('-');

        if (pos == string::npos) {
            return false;
        }

        phan[i] = dong.substr(0, pos);
        if (phan[i].empty()) {
            return false;
        }

        dong = dong.substr(pos + 1);
    }

    phan[4] = dong;

    if (phan[4].empty()) {
        return false;
    }

    if (!diemHopLe(phan[3]) || !diemHopLe(phan[4])) {
        return false;
    }

    return true;
}



// Nhap danh sach sinh vien tu file.
bool nhapTuFile(string tenFile) {
    ifstream file(tenFile);

    if (!file) {
        cout << "Khong mo duoc file!\n";
        return false;
    }

    string dong;
    int soLuongDong = 0;

    while (getline(file, dong)) {
        soLuongDong++;
    }

    file.clear();
    file.seekg(0, ios::beg);

    if (soLuongDong == 0) {
        file.close();
        delete[] ds;
        ds = nullptr;
        n = 0;
        cout << "File rong!\n";
        return true;
    }

    SinhVien* dsMoi = new SinhVien[soLuongDong];
    int soLuongSV = 0;
    int soDongLoi = 0;

    while (getline(file, dong)) {
        if (!kiemTraDong(dong)) {
            cout << "\nDong khong hop le: " << dong << endl;
            soDongLoi++;
            continue;
        }

        dsMoi[soLuongSV] = tachDong(dong);
        soLuongSV++;
    }

    file.close();

    if (soDongLoi > 0) {
        cout << "\nFile co du lieu khong hop le. Danh sach cu duoc giu nguyen.\n";
        delete[] dsMoi;
        return false;
    }

    delete[] ds;
    ds = dsMoi;
    n = soLuongSV;

    cout << "\nNhap file thanh cong!\n";
    cout << "Da nhap " << n << " sinh vien.\n";

    cout << "\n===== DANH SACH SINH VIEN =====\n";
    for (int i = 0; i < n; i++) {
        cout << ds[i].mssv << " - "
            << ds[i].ho << " - "
            << ds[i].ten << " - "
            << ds[i].diemMon1 << " - "
            << ds[i].diemMon2 << endl;
    }

    return true;
}

#pragma endregion

#pragma region cau b

string toLowerString(string s) {
    for (int i = 0; i < static_cast<int>(s.length()); i++) {
        s[i] = (tolower(unsigned char(s[i])));
    }
    return s;
}

float tinhDiemTB(SinhVien sv) {
    return (sv.diemMon1 + sv.diemMon2) / 2;
}

void inThongTinSinhVien(SinhVien sv) {
    cout << "\nMSSV: " << sv.mssv;
    cout << "\nHo: " << sv.ho;
    cout << "\nTen: " << sv.ten;
    cout << "\nDiem mon 1: " << sv.diemMon1;
    cout << "\nDiem mon 2: " << sv.diemMon2;
    cout << "\nDiem trung binh: " << tinhDiemTB(sv) << endl;
}

void timKiemTheoMSSV() {
    string mssv;

    cout << "Nhap MSSV can tim: ";
    getline(cin, mssv);

    string mssvInput = toLowerString(mssv);

    for (int i = 0; i < n; i++) {
        if (toLowerString(ds[i].mssv) == mssvInput) {
            inThongTinSinhVien(ds[i]);
            return;
        }
    }

    cout << "Khong tim thay sinh vien!\n";
}

#pragma endregion

#pragma region cau c
// Ghi danh sach hien tai vao file, moi sinh vien mot dong.
bool ghiDanhSachRaFile() {
    ofstream file(path);

    if (!file) {
        cout << "Khong mo duoc file de ghi!\n";
        return false;
    }

    for (int i = 0; i < n; i++) {
        file << ds[i].mssv << "-"
            << ds[i].ho << "-"
            << ds[i].ten << "-"
            << ds[i].diemMon1 << "-"
            << ds[i].diemMon2;

        if (i < n - 1) {
            file << '\n';
        }
    }

    file.close();
    return true;
}
bool kiemTraDanhSach() {
    if (ds == nullptr || n == 0) {
        cout << "Chua co danh sach sinh vien!\n";
        cout << "Vui long chon 1 de nhap danh sach tu file!\n";
        return false;
    }
    return true;
}

void themSinhVien() {
    SinhVien sv;
    string input;

    cout << "\n===== THEM SINH VIEN =====\n";

    cout << "Nhap MSSV: ";
    getline(cin, sv.mssv);

    if (sv.mssv.empty()) {
        cout << "MSSV khong duoc de trong!\n";
        return;
    }

    string mssvInput = toLowerString(sv.mssv);
    for (int i = 0; i < n; i++) {
        if (toLowerString(ds[i].mssv) == mssvInput) {
            cout << "MSSV da ton tai!\n";
            return;
        }
    }

    cout << "Nhap ho: ";
    getline(cin, sv.ho);
    if (sv.ho.empty()) {
        cout << "Ho khong duoc de trong!\n";
        return;
    }

    cout << "Nhap ten: ";
    getline(cin, sv.ten);
    if (sv.ten.empty()) {
        cout << "Ten khong duoc de trong!\n";
        return;
    }

    do {
        cout << "Nhap diem mon 1 (0-10): ";
        getline(cin, input);
        if (!diemHopLe(input)) {
            cout << "Diem phai la so tu 0 den 10!\n";
        }
    } while (!diemHopLe(input));
    sv.diemMon1 = stof(input);

    do {
        cout << "Nhap diem mon 2 (0-10): ";
        getline(cin, input);
        if (!diemHopLe(input)) {
            cout << "Diem phai la so tu 0 den 10!\n";
        }
    } while (!diemHopLe(input));
    sv.diemMon2 = stof(input);

    int soLuongMoi = n + 1;
    SinhVien* dsMoi = new SinhVien[soLuongMoi];

    for (int i = 0; i < n; i++) {
        dsMoi[i] = ds[i];
    }
    dsMoi[soLuongMoi - 1] = sv;

    delete[] ds;
    ds = dsMoi;
    n = soLuongMoi;

    if (!ghiDanhSachRaFile()) {
        cout << "Da them vao danh sach trong bo nho, nhung ghi file that bai!\n";
        return;
    }

    cout << "Them sinh vien thanh cong!\n";
}

#pragma endregion

#pragma region cau d

void xoaSinhVien() {
    string mssv;

    cout << "\n===== XOA SINH VIEN =====\n";
    cout << "Nhap MSSV can xoa: ";
    getline(cin, mssv);

    string mssvInput = toLowerString(mssv);
    int viTri = -1;

    for (int i = 0; i < n; i++) {
        if (toLowerString(ds[i].mssv) == mssvInput) {
            viTri = i;
            break;
        }
    }

    if (viTri == -1) {
        cout << "Khong tim thay sinh vien!\n";
        return;
    }

    if (n == 1) {
        delete[] ds;
        ds = nullptr;
        n = 0;
    }
    else {
        int soLuongMoi = n - 1;
        SinhVien* dsMoi = new SinhVien[soLuongMoi];
        int j = 0;

        for (int i = 0; i < n; i++) {
            if (i != viTri) {
                dsMoi[j] = ds[i];
                j++;
            }
        }

        delete[] ds;
        ds = dsMoi;
        n = soLuongMoi;
    }

    if (!ghiDanhSachRaFile()) {
        cout << "Da xoa trong bo nho, nhung ghi file that bai!\n";
        return;
    }

    cout << "Xoa sinh vien thanh cong!\n";
}

#pragma endregion

#pragma region cau e

void inDanhSachTheoTen() {
    cout << "\n===== DANH SACH SINH VIEN THEO TEN TANG DAN =====\n";

    SinhVien* dsTam = new SinhVien[n];

    for (int i = 0; i < n; i++) {
        dsTam[i] = ds[i];
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (toLowerString(dsTam[i].ten) > toLowerString(dsTam[j].ten)) {
                SinhVien temp = dsTam[i];
                dsTam[i] = dsTam[j];
                dsTam[j] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        inThongTinSinhVien(dsTam[i]);
        cout << "-------------------------\n";
    }

    delete[] dsTam;
}

#pragma endregion

#pragma region cau f

void inDanhSachTheoDiemTB() {
    cout << "\n===== DANH SACH SINH VIEN THEO DIEM TRUNG BINH GIAM DAN =====\n";

    SinhVien* dsTam = new SinhVien[n];

    for (int i = 0; i < n; i++) {
        dsTam[i] = ds[i];
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (tinhDiemTB(dsTam[i]) < tinhDiemTB(dsTam[j])) {
                SinhVien temp = dsTam[i];
                dsTam[i] = dsTam[j];
                dsTam[j] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        inThongTinSinhVien(dsTam[i]);
        cout << "-------------------------\n";
    }

    delete[] dsTam;
}

#pragma endregion

#pragma region cau g

void inDanhSachDauRot() {
    cout << "\n===== DANH SACH SINH VIEN DAU =====\n";

    for (int i = 0; i < n; i++) {
        if (tinhDiemTB(ds[i]) >= 5) {
            inThongTinSinhVien(ds[i]);
            cout << "-------------------------\n";
        }
    }

    cout << "\n===== DANH SACH SINH VIEN ROT =====\n";

    for (int i = 0; i < n; i++) {
        if (tinhDiemTB(ds[i]) < 5) {
            inThongTinSinhVien(ds[i]);
            cout << "-------------------------\n";
        }
    }
}

#pragma endregion

int main() {
    int chon;

    do {
        cout << "\n========== MENU ==========\n";
        cout << "1. Nhap danh sach sinh vien tu file\n";
        cout << "2. Tim kiem sinh vien theo MSSV\n";
        cout << "3. Them sinh vien\n";
        cout << "4. Xoa sinh vien\n";
        cout << "5. In danh sach theo Ten\n";
        cout << "6. In danh sach theo diem trung binh giam dan\n";
        cout << "7. In sinh vien dau va rot\n";
        cout << "0. Thoat\n";
        cout << "==========================\n";
        cout << "Chon: ";

        if (!(cin >> chon)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Vui long nhap lua chon bang so!\n";
            continue;
        }
        cin.ignore(1000, '\n');

        switch (chon) {
        case 1:
            if (!nhapTuFile(path)) {
                cout << "Khong the nap danh sach tu file.\n";
            }
            break;

        case 2:
            if (kiemTraDanhSach()) {
                timKiemTheoMSSV();
            }
            break;

        case 3:
            if (kiemTraDanhSach()) {
                themSinhVien();
            }
            break;

        case 4:
            if (kiemTraDanhSach()) {
                xoaSinhVien();
            }
            break;

        case 5:
            if (kiemTraDanhSach()) {
                inDanhSachTheoTen();
            }
            break;

        case 6:
            if (kiemTraDanhSach()) {
                inDanhSachTheoDiemTB();
            }
            break;

        case 7:
            if (kiemTraDanhSach()) {
                inDanhSachDauRot();
            }
            break;

        case 0:
            cout << "Thoat!\n";
            break;

        default:
            cout << "Lua chon khong hop le!\n";
        }

    } while (chon != 0);

    delete[] ds;
    ds = nullptr;
    n = 0;

    return 0;
}
