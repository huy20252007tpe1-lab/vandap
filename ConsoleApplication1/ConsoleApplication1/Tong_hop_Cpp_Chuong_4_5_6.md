# TỔNG HỢP C++ – CHƯƠNG 4, 5, 6

---

# CHƯƠNG 4: CHUỖI KÝ TỰ

## 4.1. Giới thiệu về chuỗi trong C++

### Khái niệm
- Chuỗi ký tự là tập hợp nhiều ký tự liên tiếp.
- Trong C++ có 2 kiểu chuỗi chính:
  - **C-string**: dùng `char[]` hoặc `char*`.
  - **string**: lớp `string` của C++.

### Phân biệt C-string và string

| C-string | `string` |
|---|---|
| Dùng `char[]` hoặc `char*` | Dùng lớp `string` |
| Kết thúc bằng `'\0'` | Tự quản lý chuỗi |
| Khó thao tác hơn | Dễ thao tác hơn |
| Dùng `strlen`, `strcpy`,... | Dùng `.length()`, `.append()`,... |

---

## 4.2. Khai báo C-string

### Dùng mảng một chiều

```cpp
char name[20];
char name[] = "Huy";
```

Chuỗi `"Huy"` thực tế gồm:

```text
'H' 'u' 'y' '\0'
```

`'\0'` là ký tự kết thúc chuỗi.

### Dùng con trỏ

```cpp
char *name = "Huy";
```

`name` trỏ đến vùng nhớ chứa chuỗi.

---

## 4.3. Nhập / xuất chuỗi

### Xuất chuỗi

```cpp
cout << name;
```

### Nhập bằng `cin >>`

```cpp
cin >> name;
```

- Chỉ đọc đến khi gặp khoảng trắng.
- Ví dụ nhập `Nguyen Gia Huy` thì chỉ nhận `Nguyen`.

### `cin.get()`

Đọc một ký tự hoặc dữ liệu có thể chứa khoảng trắng.

### `cin.getline()`

Đọc toàn bộ một dòng, kể cả khoảng trắng.

```cpp
cin.getline(name, 20);
```

### `cin.ignore()`

Bỏ qua các ký tự còn lại trong bộ đệm nhập.

Thường dùng trước `getline()` sau khi dùng `cin >>`.

---

## 4.4. Các thao tác với C-string

### Truy xuất từng ký tự

```cpp
name[0]
name[1]
```

Ví dụ:

```cpp
char name[] = "Huy";
cout << name[0];
```

Kết quả:

```text
H
```

### Xác định chiều dài

```cpp
strlen(name);
```

Ví dụ `"Huy"` có độ dài `3`.

> `strlen()` không tính ký tự `'\0'`.

### Gán / sao chép chuỗi

Không thể gán trực tiếp cho mảng `char`:

```cpp
name = "Huy"; // Sai
```

Dùng:

```cpp
strcpy(name, "Huy");
```

### Một số hàm trong `ctype`

```cpp
isalpha()   // kiểm tra chữ cái
isdigit()   // kiểm tra chữ số
isalnum()   // chữ hoặc số
isspace()   // khoảng trắng
islower()   // chữ thường
isupper()   // chữ hoa
tolower()   // chuyển thành chữ thường
toupper()   // chuyển thành chữ hoa
```

---

## 4.5. Các hàm xử lý C-string

Thư viện:

```cpp
#include <cstring>
```

| Hàm | Công dụng |
|---|---|
| `strlen(s)` | Trả về độ dài chuỗi |
| `strcpy(a,b)` | Sao chép `b` vào `a` |
| `strcat(a,b)` | Nối `b` vào cuối `a` |
| `strcmp(a,b)` | So sánh 2 chuỗi |
| `strchr(s,c)` | Tìm ký tự `c` |
| `strstr(s,sub)` | Tìm chuỗi con `sub` |
| `strtok()` | Tách chuỗi |
| `atoi()` | Chuỗi → số nguyên |
| `atof()` | Chuỗi → số thực |

### `strcmp()`

```cpp
strcmp(a, b);
```

Kết quả:

```text
= 0  → hai chuỗi giống nhau
< 0  → a nhỏ hơn b
> 0  → a lớn hơn b
```

### `strcat()`

```cpp
char a[20] = "Hello ";
char b[] = "World";

strcat(a, b);
```

Kết quả:

```text
Hello World
```

---

## 4.6. Lớp `string`

Khai báo:

```cpp
#include <string>
using namespace std;

string name;
```

### Khởi tạo

```cpp
string name = "Huy";
```

### Nhập

```cpp
cin >> name;
```

Hoặc đọc cả dòng:

```cpp
getline(cin, name);
```

### Xuất

```cpp
cout << name;
```

### Các hàm thành viên quan trọng

| Hàm | Công dụng |
|---|---|
| `s.length()` | Độ dài chuỗi |
| `s.size()` | Độ dài chuỗi |
| `s.empty()` | Kiểm tra chuỗi rỗng |
| `s.append()` | Nối chuỗi |
| `s.push_back()` | Thêm 1 ký tự |
| `s.pop_back()` | Xóa ký tự cuối |
| `s.insert()` | Chèn chuỗi |
| `s.erase()` | Xóa |
| `s.replace()` | Thay thế |
| `s.find()` | Tìm ký tự / chuỗi |
| `s.substr()` | Lấy chuỗi con |
| `s.compare()` | So sánh chuỗi |

### Ưu điểm của `string`

- Không cần tự quản lý `'\0'`.
- Không cần kích thước cố định như `char[]`.
- Dễ nối, tìm, cắt, xóa và thay thế.
- Thuận tiện và an toàn hơn C-string.

---

# CHƯƠNG 5: KIỂU DỮ LIỆU NGƯỜI DÙNG

## Nội dung chính

Gồm 3 phần:

1. `typedef`
2. `struct`
3. `enum`

---

## 5.1. `typedef`

### Khái niệm

`typedef` dùng để đặt **bí danh cho một kiểu dữ liệu đã có**.

### Cú pháp

```cpp
typedef kiểu_dữ_liệu tên_mới;
```

Ví dụ:

```cpp
typedef int Integer;

Integer a = 10;
```

`Integer` là bí danh của `int`.

---

## 5.2. Kiểu `struct`

### Khái niệm

`struct` dùng để gom nhiều dữ liệu, có thể khác kiểu, vào cùng một đối tượng.

Ví dụ:

```cpp
struct Student
{
    string name;
    int age;
    float score;
};
```

Một `Student` gồm:
- `name`
- `age`
- `score`

### Khai báo biến

```cpp
Student sv;
```

### Truy xuất thành phần

Dùng toán tử `.`:

```cpp
sv.name = "Huy";
sv.age = 20;
sv.score = 8.5;
```

### Nhập / xuất

```cpp
cin >> sv.age;
cout << sv.name;
```

### Struct và hàm

Có thể truyền `struct` vào hàm:

```cpp
void show(Student sv)
{
    cout << sv.name;
}
```

### Struct và mảng

```cpp
Student ds[100];
```

Dùng để lưu danh sách 100 sinh viên.

### Struct bên trong struct

```cpp
struct Address
{
    string city;
};

struct Student
{
    string name;
    Address address;
};
```

Truy xuất:

```cpp
sv.address.city;
```

### Struct và con trỏ

```cpp
Student *p = &sv;

p->age = 20;
```

**Cần nhớ:**

```text
Biến struct       → .
Con trỏ struct    → ->
```

---

## 5.3. Kiểu `enum`

### Khái niệm

`enum` dùng để tạo kiểu dữ liệu gồm một tập hợp các giá trị có tên cố định.

Ví dụ:

```cpp
enum Color
{
    RED,
    GREEN,
    BLUE
};
```

Sử dụng:

```cpp
Color c = RED;
```

### Giá trị mặc định

Nếu không chỉ định:

```text
RED   = 0
GREEN = 1
BLUE  = 2
```

Có thể tự đặt:

```cpp
enum Color
{
    RED = 1,
    GREEN = 5,
    BLUE = 10
};
```

### Ý nghĩa

Giúp chương trình dễ đọc, dễ quản lý hơn so với việc dùng các con số trực tiếp.

---

# CHƯƠNG 6: TẬP TIN VÀ LUỒNG

## Mục tiêu

- Hiểu khái niệm tập tin và luồng.
- Biết đọc dữ liệu từ file.
- Biết ghi dữ liệu vào file.
- Phân biệt file văn bản và file nhị phân.

---

## 6.1. Giới thiệu

### Tập tin (File)

File là nơi lưu trữ dữ liệu lâu dài trên bộ nhớ.

Ví dụ:

```text
data.txt
student.txt
data.dat
```

### Luồng (Stream)

Stream là luồng dữ liệu giữa chương trình và nơi lưu trữ / thiết bị.

Ví dụ:

```text
Chương trình → File
File → Chương trình
```

---

## Hai loại tập tin

### File văn bản

Dữ liệu được lưu dưới dạng ký tự mà con người có thể đọc.

Ví dụ:

```text
Nguyen Van A
20
8.5
```

Thường dùng `.txt`.

### File nhị phân

Dữ liệu được lưu dưới dạng binary / byte.

- Phù hợp lưu dữ liệu trực tiếp.
- Thường xử lý nhanh và tiết kiệm dung lượng hơn trong một số trường hợp.

---

## Quy trình làm việc với file

```text
Mở file
   ↓
Đọc / ghi dữ liệu
   ↓
Đóng file
```

Thư viện:

```cpp
#include <fstream>
```

---

# 6.2. Đọc / ghi file văn bản

## Ghi file: `ofstream`

Khai báo:

```cpp
ofstream file("data.txt");
```

Ghi dữ liệu:

```cpp
file << "Hello";
file << 123;
```

Đóng file:

```cpp
file.close();
```

### Quy trình

```text
ofstream
   ↓
Mở file
   ↓
Ghi bằng <<
   ↓
close()
```

---

## Đọc file: `ifstream`

Khai báo:

```cpp
ifstream file("data.txt");
```

Đọc dữ liệu:

```cpp
file >> name;
```

Đọc cả dòng:

```cpp
getline(file, name);
```

Đóng file:

```cpp
file.close();
```

### Quy trình

```text
ifstream
   ↓
Mở file
   ↓
Đọc bằng >> / getline()
   ↓
close()
```

---

# 6.3. Đọc / ghi file nhị phân

## Ghi file nhị phân

Mở file ở chế độ binary:

```cpp
ofstream file("data.dat", ios::binary);
```

Ghi:

```cpp
file.write(...);
```

## Đọc file nhị phân

```cpp
ifstream file("data.dat", ios::binary);
```

Đọc:

```cpp
file.read(...);
```

### Cần nhớ

```text
File văn bản:
ofstream → ghi → <<
ifstream → đọc → >> / getline()

File nhị phân:
ofstream → ghi → write()
ifstream → đọc → read()

Binary mode:
ios::binary
```

---

# ⭐ BẢNG ÔN THI NHANH

| Chủ đề | Cần nhớ |
|---|---|
| C-string | `char[]`, `char*`, kết thúc `'\0'` |
| Độ dài C-string | `strlen()` |
| Sao chép | `strcpy()` |
| Nối | `strcat()` |
| So sánh | `strcmp()` |
| Tìm ký tự | `strchr()` |
| Tìm chuỗi con | `strstr()` |
| Tách chuỗi | `strtok()` |
| Chuỗi → số | `atoi()`, `atof()` |
| C++ string | `string` |
| Độ dài string | `.length()`, `.size()` |
| Tìm string | `.find()` |
| Chuỗi con | `.substr()` |
| Nối string | `.append()` |
| Xóa string | `.erase()` |
| Thay string | `.replace()` |
| `typedef` | Đặt bí danh kiểu dữ liệu |
| `struct` | Gom nhiều dữ liệu khác kiểu |
| Struct truy xuất | `.` |
| Con trỏ struct | `->` |
| `enum` | Tập giá trị có tên |
| File văn bản ghi | `ofstream`, `<<` |
| File văn bản đọc | `ifstream`, `>>`, `getline()` |
| File binary ghi | `write()` |
| File binary đọc | `read()` |
| Binary mode | `ios::binary` |

---

# 🎯 CÔNG THỨC NHỚ NHANH

## C-STRING

```text
char[] / char*
    ↓
'\0' = kết thúc chuỗi

strlen  → độ dài
strcpy  → sao chép
strcat  → nối
strcmp  → so sánh
strchr  → tìm ký tự
strstr  → tìm chuỗi
strtok  → tách
atoi    → chuỗi → số nguyên
atof    → chuỗi → số thực
```

## STRING

```text
.length()  → độ dài
.find()    → tìm
.substr()  → lấy chuỗi con
.append()  → nối
.erase()   → xóa
.replace() → thay thế
```

## STRUCT

```text
struct
  ↓
Gom nhiều dữ liệu

Biến struct    → .
Con trỏ struct → ->
```

## ENUM

```text
enum
 ↓
Tập các giá trị có tên
```

## FILE

```text
ofstream → GHI
ifstream → ĐỌC

Text:
<< / >> / getline()

Binary:
write() / read()

Binary mode:
ios::binary
```
