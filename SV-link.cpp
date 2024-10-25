#include <iostream>
using namespace std;

struct Ngay {
    int ngay, thang, nam;
};

struct SinhVien {
    char maSV[8];
    char hoTen[50];
    int gioiTinh;
    Ngay ngaySinh;
    char diaChi[100];
    char lop[12];
    char khoa[7];
};

struct Node {
    SinhVien data;
    Node* link;
};

struct list {
    Node* first;
    Node* last;
};

int cmp(char a[], char b[]) {
    int i=0;
    while (i<8)
    {
    	if (a[i]>b[i]) return 1;
    	if (a[i]<b[i]) return 0;
    	i++;
	}
}

// khoi tao danh sach
void link_init(list* lists) {
    lists->first = NULL;
    lists->last = NULL;
}

// them sinh vien vao danh sach
void plusSV(list* lists, SinhVien sv) {
    Node* newN = new Node();  // khoi tao node moi de them vao danh sach
    newN->data = sv;
    newN->link = NULL;

    if (lists->first == NULL || cmp(lists->first->data.maSV, sv.maSV) > 0) {
        newN->link = lists->first;
        lists->first = newN;
        if (lists->last == NULL) {
            lists->last = newN;
        }
    } else {
        Node* current = lists->first;
        while (current->link != NULL && cmp(current->link->data.maSV, sv.maSV) < 0) {
            current = current->link;
        }
        newN->link = current->link;
        current->link = newN;
        if (newN->link == NULL) {
            lists->last = newN;
        }
    }
}

// nhap sinh vien
SinhVien nhapSV() {
    SinhVien sv;
    cout << "MSSV: "; cin >> sv.maSV;
    cout << "Ho va ten: "; cin.ignore(); cin.getline(sv.hoTen, 50);
    cout << "Gioi tinh (0:Nam, 1:Nu): "; cin >> sv.gioiTinh;
    cout << "Ngay sinh (dd mm yyyy): "; 
    cin >> sv.ngaySinh.ngay >> sv.ngaySinh.thang >> sv.ngaySinh.nam;
    cout << "Dia chi: "; cin.ignore(); cin.getline(sv.diaChi, 100);
    cout << "Lop: "; cin >> sv.lop;
    cout << "Khoa: "; cin >> sv.khoa;
    return sv;
}

// hien thi danh sach sinh vien
void display(list* lists) {
    Node* current = lists->first;
    while (current != NULL) {
        SinhVien sv = current->data;
        cout << "MSSV: " << sv.maSV << endl;
        cout << "Ho va ten: " << sv.hoTen << endl;
        cout << "Gioi tinh: " << (sv.gioiTinh == 0 ? "Nam" : "Nu") << endl;
        cout << "Ngay sinh: " << sv.ngaySinh.ngay << "/" << sv.ngaySinh.thang << "/" << sv.ngaySinh.nam << endl;
        cout << "Dia chi: " << sv.diaChi << endl;
        cout << "Lop: " << sv.lop << endl;
        cout << "Khoa: " << sv.khoa << endl;
        current = current->link;
    }
}

// tim va hien thi sinh vien cung ngay sinh
void SearchSV(list lists, Ngay ngay) {
    Node* current = lists.first;
    int found = 0;
    while (current != NULL) {
        SinhVien sv = current->data;
        if (sv.ngaySinh.ngay == ngay.ngay && sv.ngaySinh.thang == ngay.thang && sv.ngaySinh.nam == ngay.nam) {
            cout << "Sinh vien cung ngay sinh: " << sv.maSV << " - " << sv.hoTen << endl;
            found = 1;
        }
        current = current->link;
    }
    if (!found) {
        cout << "Khong tim thay sinh vien cung ngay sinh" << endl;
    }
}

// xoa sinh vien cung ngay sinh
void SV_del(list* lists, Ngay ngay) {
    Node* current = lists->first;
    Node* prev = NULL;

    while (current != NULL) {
        SinhVien sv = current->data;
        if (sv.ngaySinh.ngay == ngay.ngay && sv.ngaySinh.thang == ngay.thang && sv.ngaySinh.nam == ngay.nam) {
            if (prev == NULL) { // xoa phan tu dau tien
                lists->first = current->link;
                if (lists->first == NULL) {
                    lists->last = NULL;
                }
            } else {
                prev->link = current->link;
                if (prev->link == NULL) {
                    lists->last = prev;
                }
            }
            Node* temp = current;
            current = current->link;
            delete temp;
        } else {
            prev = current;
            current = current->link;
        }
    }
}

void MSSVsort(list* lists) {
    if (lists->first == NULL) return;  // neu danh sach khong co phan tu khong can sap xep

    int swapped;
    Node* ptr1;
    Node* lptr = NULL;  // con tro danh dau phan tu duoc sap xep

    do {
        swapped = 0;
        ptr1 = lists->first;

        //duyet danh sach va hoan doi phan tu
        while (ptr1->link != lptr) {
            if (cmp(ptr1->data.maSV, ptr1->link->data.maSV) == 1) {
                // hoan doi
                SinhVien temp = ptr1->data;
                ptr1->data = ptr1->link->data;
                ptr1->link->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->link;
        }
        lptr = ptr1;  // giam kich thuoc danh sach
    } while (swapped);  // lap lai neu co su hoan doi
}


int main() {
    list lists;
    link_init(&lists);
    int n;

    // nhap so luong sinh vien
    cout << "Nhap so luong sinh vien: ";
    cin >> n;

    // nhap danh sach sinh vien
    for (int i = 0; i < n; i++) {
        cout << "Sinh vien " << i + 1 << ":" << endl;
        SinhVien sv = nhapSV();
        plusSV(&lists, sv);
    }

    // In danh sach sinh vien
    cout << "Danh sach sinh vien:\n";
    display(&lists);
	// sort sinh vien va in ra
	MSSVsort(&lists); 
	cout << "Danh sach sinh vien:\n";
    display(&lists);

    // tim ra cac sinh vien cung ngay sinh
    Ngay ngay;
    cout << "Nhap ngay thang nam de tim sinh vien cung ngay sinh (dd mm yyyy): ";
    cin >> ngay.ngay >> ngay.thang >> ngay.nam;
    SearchSV(lists, ngay);

    // xoa sinh vien cung ngay
    cout << "Xoa sinh vien cung ngay sinh...\n";
    SV_del(&lists, ngay);

    // danh sach sinh vien sau khi xoa
    cout << "Danh sach sinh vien sau khi xoa:\n";
    display(&lists);

    return 0;
}

