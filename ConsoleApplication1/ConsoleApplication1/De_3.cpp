#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <ctime>
#include <sstream>

using namespace std;

struct Sach {
    string maSach;
    string tenSach;
    string tacGia;
    string nhaXuatBan;
    int namXuatBan = 0;
};

string path = "C:\\Users\\HOME\\OneDrive\\Desktop\\hoc\\github\\kynanglaptrinh\\chuong6\\chuong 6\\ConsoleApplication1\\sach.dat";

Sach* ds = nullptr;
int n = 0;

#pragma region cau a

// Chuyen ma sach thanh chu hoa
string toUpperString(string s) {

    for (size_t i = 0; i < s.length(); i++) {
        s[i] = toupper((unsigned char)s[i]);
    }

    return s;
}

// Viet hoa ky tu dau moi tu
string vietHoaDauTu(string s) {

    bool vietHoa = true;

    for (size_t i = 0; i < s.length(); i++) {

        if (s[i] == ' ') {
            vietHoa = true;
        }
        else if (vietHoa) {
            s[i] = toupper((unsigned char)s[i]);
            vietHoa = false;
        }
    }

    return s;
}

// Kiem tra ma sach co bi trung hay khong
bool trungMaSach(string ma, int soLuong) {

    for (int i = 0; i < soLuong; i++) {

        if (ds[i].maSach == ma) {
            return true;
        }
    }

    return false;
}

// Nhap mot sach
void nhapMotSach(Sach* sach, int soLuong) {

    // Nhap ma sach
    while (true) {

        cout << "Ma sach: ";
        getline(cin, sach->maSach);

        if (sach->maSach.empty()) {
            cout << "Ma sach khong duoc de trong! Vui long nhap lai.\n";
            continue;
        }

        sach->maSach = toUpperString(sach->maSach);

        if (trungMaSach(sach->maSach, soLuong)) {
            cout << "Ma sach da ton tai! Vui long nhap ma khac.\n";
            continue;
        }

        break;
    }

    // Nhap ten sach
    while (true) {

        cout << "Ten sach: ";
        getline(cin, sach->tenSach);

        if (sach->tenSach.empty()) {
            cout << "Ten sach khong duoc de trong! Vui long nhap lai.\n";
            continue;
        }

        sach->tenSach = vietHoaDauTu(sach->tenSach);

        break;
    }

    // Nhap tac gia
    while (true) {

        cout << "Tac gia: ";
        getline(cin, sach->tacGia);

        if (sach->tacGia.empty()) {
            cout << "Tac gia khong duoc de trong! Vui long nhap lai.\n";
            continue;
        }

        sach->tacGia = vietHoaDauTu(sach->tacGia);

        break;
    }

    // Nhap nha xuat ban
    while (true) {

        cout << "Nha xuat ban: ";
        getline(cin, sach->nhaXuatBan);

        if (sach->nhaXuatBan.empty()) {
            cout << "Nha xuat ban khong duoc de trong! Vui long nhap lai.\n";
            continue;
        }

        sach->nhaXuatBan = vietHoaDauTu(sach->nhaXuatBan);

        break;
    }

    // Nhap nam xuat ban
    while (true) {

        cout << "Nam xuat ban: ";
        cin >> sach->namXuatBan;

        if (cin.fail()) {

            cin.clear();
            cin.ignore(1000, '\n');

            cout << "Nam xuat ban phai la so! Vui long nhap lai.\n";
            continue;
        }

        // Lay nam hien tai
        time_t now = time(0);
        tm ltm;
        localtime_s(&ltm, &now);

        int namHienTai = 1900 + ltm.tm_year;

        if (sach->namXuatBan <= 0 ||
            sach->namXuatBan > namHienTai) {

            cin.ignore(1000, '\n');

            cout << "Nam xuat ban khong hop le! Vui long nhap lai.\n";
            continue;
        }

        cin.ignore(1000, '\n');
        break;
    }
}

// Nhap danh sach sach
void nhapDanhSach() {

    cout << "\n===== NHAP DANH SACH SACH =====\n";

    // Nhap so luong sach
    while (true) {

        cout << "Nhap so luong sach: ";
        cin >> n;

        if (cin.fail() || n <= 0) {

            cin.clear();
            cin.ignore(1000, '\n');

            cout << "So luong khong hop le! Vui long nhap lai.\n";
            continue;
        }

        cin.ignore(1000, '\n');
        break;
    }

    // Xoa danh sach cu
    delete[] ds;
    ds = nullptr;

    // Cap phat danh sach moi
    ds = new Sach[n];

    for (int i = 0; i < n; i++) {

        cout << "\n===== SACH " << i + 1 << " =====\n";

        nhapMotSach(&ds[i], i);
    }

    cout << "\nNhap danh sach thanh cong!\n";
    // Hien thi danh sach
    cout << "\n===== DANH SACH SACH =====\n";

    for (int i = 0; i < n; i++) {

        cout << "\nSach " << i + 1 << ":" << endl;
        cout << "Ma sach: " << ds[i].maSach << endl;
        cout << "Ten sach: " << ds[i].tenSach << endl;
        cout << "Tac gia: " << ds[i].tacGia << endl;
        cout << "Nha xuat ban: " << ds[i].nhaXuatBan << endl;
        cout << "Nam xuat ban: " << ds[i].namXuatBan << endl;
    }
}

#pragma endregion


#pragma region cau b

void ghiFileNhiPhan() {

    if (ds == nullptr || n == 0) {

        cout << "Chua co danh sach sach!\n";
        cout << "Vui long chon 1 de nhap danh sach!\n";

        return;
    }

    ofstream file(path, ios::binary);

    if (!file) {

        cout << "Khong mo duoc file!\n";

        return;
    }

    // Ghi so luong sach
    file.write((char*)&n, sizeof(n));

    // Ghi tung sach
    for (int i = 0; i < n; i++) {

        // Ghi ma sach
        size_t doDai = ds[i].maSach.length();

        file.write((char*)&doDai, sizeof(doDai));
        file.write(ds[i].maSach.c_str(),
            static_cast<streamsize>(doDai));

        // Ghi ten sach
        doDai = ds[i].tenSach.length();

        file.write((char*)&doDai, sizeof(doDai));
        file.write(ds[i].tenSach.c_str(),
            static_cast<streamsize>(doDai));

        // Ghi tac gia
        doDai = ds[i].tacGia.length();

        file.write((char*)&doDai, sizeof(doDai));
        file.write(ds[i].tacGia.c_str(),
            static_cast<streamsize>(doDai));

        // Ghi nha xuat ban
        doDai = ds[i].nhaXuatBan.length();

        file.write((char*)&doDai, sizeof(doDai));
        file.write(ds[i].nhaXuatBan.c_str(),
            static_cast<streamsize>(doDai));

        // Ghi nam xuat ban
        file.write((char*)&ds[i].namXuatBan,
            sizeof(ds[i].namXuatBan));
    }

    file.close();

    cout << "Ghi danh sach ra file nhi phan thanh cong!\n";

    // Hien thi danh sach
    cout << "\n===== DANH SACH SACH =====\n";

    for (int i = 0; i < n; i++) {

        cout << "\nSach " << i + 1 << ":" << endl;
        cout << "Ma sach: " << ds[i].maSach << endl;
        cout << "Ten sach: " << ds[i].tenSach << endl;
        cout << "Tac gia: " << ds[i].tacGia << endl;
        cout << "Nha xuat ban: " << ds[i].nhaXuatBan << endl;
        cout << "Nam xuat ban: " << ds[i].namXuatBan << endl;
    }
}

#pragma endregion


#pragma region cau c

void docFileNhiPhan() {

    ifstream file(path, ios::binary);

    if (!file) {

        cout << "Khong mo duoc file!\n";

        return;
    }

    // Tao danh sach rieng de doc file
    int soLuongFile;

    // Doc so luong sach
    file.read((char*)&soLuongFile, sizeof(soLuongFile));

    if (soLuongFile <= 0) {

        cout << "File khong co du lieu!\n";

        file.close();

        return;
    }

    // Cap phat danh sach rieng
    Sach* dsFile = new Sach[soLuongFile];

    for (int i = 0; i < soLuongFile; i++) {

        size_t doDai;

        // Doc ma sach
        file.read((char*)&doDai, sizeof(doDai));

        dsFile[i].maSach.resize(doDai);

        file.read(&dsFile[i].maSach[0],
            static_cast<streamsize>(doDai));


        // Doc ten sach
        file.read((char*)&doDai, sizeof(doDai));

        dsFile[i].tenSach.resize(doDai);

        file.read(&dsFile[i].tenSach[0],
            static_cast<streamsize>(doDai));


        // Doc tac gia
        file.read((char*)&doDai, sizeof(doDai));

        dsFile[i].tacGia.resize(doDai);

        file.read(&dsFile[i].tacGia[0],
            static_cast<streamsize>(doDai));


        // Doc nha xuat ban
        file.read((char*)&doDai, sizeof(doDai));

        dsFile[i].nhaXuatBan.resize(doDai);

        file.read(&dsFile[i].nhaXuatBan[0],
            static_cast<streamsize>(doDai));


        // Doc nam xuat ban
        file.read((char*)&dsFile[i].namXuatBan,
            sizeof(dsFile[i].namXuatBan));
    }

    file.close();

    cout << "\nDoc danh sach tu file nhi phan thanh cong!\n";

    // In danh sach doc tu file
    cout << "\n===== DANH SACH DOC TU FILE =====\n";

    for (int i = 0; i < soLuongFile; i++) {

        cout << "\nSach " << i + 1 << ":" << endl;
        cout << "Ma sach: " << dsFile[i].maSach << endl;
        cout << "Ten sach: " << dsFile[i].tenSach << endl;
        cout << "Tac gia: " << dsFile[i].tacGia << endl;
        cout << "Nha xuat ban: " << dsFile[i].nhaXuatBan << endl;
        cout << "Nam xuat ban: " << dsFile[i].namXuatBan << endl;
    }

    // Xoa danh sach rieng
    delete[] dsFile;
}

#pragma endregion


#pragma region cau d

void timKiemTheoMaSach() {

    if (ds == nullptr || n == 0) {

        cout << "Chua co danh sach sach!\n";
        cout << "Vui long chon 1 hoac 3 de co danh sach!\n";

        return;
    }

    string maNhap;

    // Nhap ma sach
    while (true) {

        cout << "\n===== TIM KIEM SACH =====\n";
        cout << "Nhap ma sach can tim: ";

        cin >> ws;
        getline(cin, maNhap);

        if (maNhap.empty()) {

            cout << "Ma sach khong duoc de trong! Vui long nhap lai.\n";

            continue;
        }

        maNhap = toUpperString(maNhap);

        break;
    }

    // Tim sach
    for (int i = 0; i < n; i++) {

        if (toUpperString(ds[i].maSach) == maNhap) {

            cout << "\n===== THONG TIN SACH =====\n";
            cout << "Ma sach: " << ds[i].maSach << endl;
            cout << "Ten sach: " << ds[i].tenSach << endl;
            cout << "Tac gia: " << ds[i].tacGia << endl;
            cout << "Nha xuat ban: " << ds[i].nhaXuatBan << endl;
            cout << "Nam xuat ban: " << ds[i].namXuatBan << endl;

            return;
        }
    }

    cout << "Khong tim thay sach!\n";
}

#pragma endregion


#pragma region cau e

void themSach() {

    cout << "\n===== THEM SACH MOI =====\n";

    // Tao sach moi
    Sach sachMoi = {};

    // Nhap sach moi
    nhapMotSach(&sachMoi, n);

    // Tao mang moi
    Sach* dsMoi = new Sach[n + 1];

    // Copy danh sach cu
    for (int i = 0; i < n; i++) {
        dsMoi[i] = ds[i];
    }

    // Them sach moi
    dsMoi[n] = sachMoi;

    // Xoa danh sach cu
    delete[] ds;

    // Gan danh sach moi
    ds = dsMoi;

    // Tang so luong
    n++;

    cout << "\nThem sach thanh cong!\n";
}

#pragma endregion

#pragma region cau f

void xoaTheoMaSach() {

    if (ds == nullptr || n == 0) {

        cout << "Chua co danh sach sach!\n";
        cout << "Vui long chon 1 hoac 3 de co danh sach!\n";

        return;
    }

    string maNhap;

    cout << "\n===== XOA SACH THEO MA =====\n";
    cout << "Nhap ma sach can xoa: ";

    getline(cin, maNhap);

    if (maNhap.empty()) {

        cout << "Ma sach khong duoc de trong!\n";

        return;
    }

    // Chuyen ma nhap vao thanh chu hoa
    maNhap = toUpperString(maNhap);

    // Tim vi tri sach
    int viTri = -1;

    for (int i = 0; i < n; i++) {

        if (toUpperString(ds[i].maSach) == maNhap) {

            viTri = i;
            break;
        }
    }

    // Khong tim thay
    if (viTri == -1) {

        cout << "Khong tim thay sach co ma: "
            << maNhap << endl;

        return;
    }

    // Xoa sach bang cach dich cac phan tu phia sau len
    for (int i = viTri; i < n - 1; i++) {

        ds[i] = ds[i + 1];
    }

    // Giam so luong sach
    n--;

    // Tao danh sach moi
    Sach* dsMoi = new Sach[n];

    // Copy danh sach sau khi xoa
    for (int i = 0; i < n; i++) {

        dsMoi[i] = ds[i];
    }

    // Xoa danh sach cu
    delete[] ds;

    // Gan danh sach moi
    ds = dsMoi;

    cout << "Xoa sach thanh cong!\n";
}

#pragma endregion

#pragma region cau g

void xoaTheoTacGia() {

    if (ds == nullptr || n == 0) {

        cout << "Chua co danh sach sach!\n";
        cout << "Vui long chon 1 hoac 3 de co danh sach!\n";

        return;
    }

    string tacGiaNhap;

    cout << "\n===== XOA SACH THEO TAC GIA =====\n";
    cout << "Nhap ten tac gia can xoa: ";

    getline(cin, tacGiaNhap);

    if (tacGiaNhap.empty()) {

        cout << "Ten tac gia khong duoc de trong!\n";

        return;
    }

    tacGiaNhap = toUpperString(tacGiaNhap);

    // Dem so sach can xoa
    int soLuongXoa = 0;

    for (int i = 0; i < n; i++) {

        if (toUpperString(ds[i].tacGia) == tacGiaNhap) {
            soLuongXoa++;
        }
    }

    // Khong tim thay
    if (soLuongXoa == 0) {

        cout << "Khong tim thay sach cua tac gia: "
            << tacGiaNhap << endl;

        return;
    }

    // So luong sach con lai
    int soLuongMoi = n - soLuongXoa;

    // Tao mang moi co kich thuoc bang n cu
    // de tranh loi Code Analysis
    Sach* dsMoi = new Sach[n];

    int j = 0;

    // Copy nhung sach khong phai tac gia can xoa
    for (int i = 0; i < n; i++) {

        if (toUpperString(ds[i].tacGia) != tacGiaNhap) {

            dsMoi[j] = ds[i];
            j++;
        }
    }

    // Xoa danh sach cu
    delete[] ds;

    // Gan danh sach moi
    ds = dsMoi;

    // Cap nhat so luong
    n = soLuongMoi;

    cout << "Da xoa " << soLuongXoa
        << " sach cua tac gia: "
        << tacGiaNhap << endl;
}

#pragma endregion
#pragma region cau h

void inTheoNhaXuatBan() {

    if (ds == nullptr || n == 0) {

        cout << "Chua co danh sach sach!\n";
        cout << "Vui long chon 1 de nhap danh sach!\n";

        return;
    }

    string nhaXuatBanNhap;

    cout << "\n===== IN SACH THEO NHA XUAT BAN =====\n";
    cout << "Nhap nha xuat ban: ";

    getline(cin, nhaXuatBanNhap);

    if (nhaXuatBanNhap.empty()) {

        cout << "Nha xuat ban khong duoc de trong!\n";

        return;
    }

    // Chuyen ve chu hoa de so sanh
    nhaXuatBanNhap = toUpperString(nhaXuatBanNhap);

    // Tim va in sach
    int soLuongTimThay = 0;

    for (int i = 0; i < n; i++) {

        if (toUpperString(ds[i].nhaXuatBan) == nhaXuatBanNhap) {

            cout << "\n===== SACH " << soLuongTimThay + 1 << " =====\n";

            cout << "Ma sach: " << ds[i].maSach << endl;
            cout << "Ten sach: " << ds[i].tenSach << endl;
            cout << "Tac gia: " << ds[i].tacGia << endl;
            cout << "Nha xuat ban: " << ds[i].nhaXuatBan << endl;
            cout << "Nam xuat ban: " << ds[i].namXuatBan << endl;

            soLuongTimThay++;
        }
    }

    if (soLuongTimThay == 0) {

        cout << "Khong tim thay sach cua nha xuat ban: "
            << nhaXuatBanNhap << endl;
    }
}

#pragma endregion
#pragma region cau i

void inTheoNamGiamDan() {

    if (ds == nullptr || n == 0) {

        cout << "Chua co danh sach sach!\n";
        cout << "Vui long chon 1 de nhap danh sach!\n";

        return;
    }

    // Tao danh sach tam
    Sach* dsTam = new Sach[n];

    // Copy danh sach chinh sang danh sach tam
    for (int i = 0; i < n; i++) {
        dsTam[i] = ds[i];
    }

    // Sap xep nam xuat ban giam dan
    for (int i = 0; i < n - 1; i++) {

        for (int j = i + 1; j < n; j++) {

            if (dsTam[i].namXuatBan < dsTam[j].namXuatBan) {

                Sach temp = dsTam[i];
                dsTam[i] = dsTam[j];
                dsTam[j] = temp;
            }
        }
    }

    // In danh sach
    cout << "\n===== DANH SACH SACH THEO NAM GIAM DAN =====\n";

    for (int i = 0; i < n; i++) {

        cout << "\nSach " << i + 1 << ":" << endl;
        cout << "Ma sach: " << dsTam[i].maSach << endl;
        cout << "Ten sach: " << dsTam[i].tenSach << endl;
        cout << "Tac gia: " << dsTam[i].tacGia << endl;
        cout << "Nha xuat ban: " << dsTam[i].nhaXuatBan << endl;
        cout << "Nam xuat ban: " << dsTam[i].namXuatBan << endl;
    }

    // Xoa danh sach tam
    delete[] dsTam;
}

#pragma endregion
int main() {

    int chon = 0;

    do {

        cout << "\n========== MENU ==========\n";
        cout << "1. Nhap danh sach sach\n";
        cout << "2. Ghi danh sach ra file nhi phan\n";
        cout << "3. Doc danh sach tu file nhi phan\n";
        cout << "4. Tim kiem sach theo ma sach\n";
        cout << "5. Them sach moi\n";
        cout << "6. Xoa sach theo ma sach\n";
        cout << "7. Xoa sach theo ten tac gia\n";
        cout << "8. In sach theo nha xuat ban\n";
        cout << "9. In sach theo nam xuat ban giam dan\n";
        cout << "0. Thoat\n";
        cout << "==========================\n";

        cout << "Chon: ";
        cin >> chon;
        cin.ignore(1000, '\n');

        switch (chon) {

        case 1:
            nhapDanhSach();
            break;

        case 2:
            ghiFileNhiPhan();
            break;

        case 3:
            docFileNhiPhan();
            break;

        case 4:
            timKiemTheoMaSach();
            break;

        case 5:
            themSach();
            break;

        case 6:
            xoaTheoMaSach();
            break;

        case 7:
            xoaTheoTacGia();
            break;

        case 8:
            inTheoNhaXuatBan();
            break;

        case 9:
            inTheoNamGiamDan();
            break;
    
        case 0:
            cout << "Thoat!\n";
            break;

        default:
            cout << "Chuc nang chua lam!\n";
        }

    } while (chon != 0);

    delete[] ds;

    return 0;
}