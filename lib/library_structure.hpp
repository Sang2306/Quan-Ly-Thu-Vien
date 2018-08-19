#ifndef LIBRARY_STRUCTURE_HPP
#define LIBRARY_STRUCTURE_HPP
#include <iostream>
#include <vector>
#define MAX_SIZE 100
using namespace std;
//=========================================DANH_MUC_SACH===================================
struct Sach{
	string maSach;
	short trangThai;
	int viTri;
};
struct Node_Sach{
	Sach _sach;//du lieu cua Node
	Node_Sach *next;
};
struct DANH_MUC_SACH{
	Node_Sach* first;
	DANH_MUC_SACH(){///khoi tao danh muc sach(danh sach lien ket don
		this->first = NULL;
	}
	void Insert_First(Sach x);
	bool Empty();
	void Clearlist();
	void Traverse(Sach* sachArr, int dieuKien); //duyet va luu  sach voi dieu kien cho truoc vao mang sachArr
	int TongSoLuongSach(int dieuKien); //duyet va dem so luong sach voi dieu kien cho truoc
	int TonTai(string maSach);
	void DanhDau(string maSach, int tt);//Danh dau ma sach voi trang thai tt
};
//=========================================LIST============================================
struct DauSach{
	string ISBN;
	string tenSach;
	int soTrang;
	string tacGia;
	string NXB;
	string theLoai;
	int soLuongSach;
	DANH_MUC_SACH danhMucSach; //moi dau sach se co 1 danh muc sach
};
struct LIST{
	DauSach *dausach[MAX_SIZE];//mang con tro dau sach
	int soLuong;
};
typedef LIST List;
bool Empty(List ls);//kiem tra xem danh sach dau sach co rong hay khong
bool Full(List ls);//kiem tra xem danh sach dau sach co day hay khong
int ThemDauSach(List &ls, DauSach* dsach);//Them dau sach vao danh sach dau sach
bool TonTaiISBN(const List& ls, string ISBN);//kiem tra ma so ISBN nhap vao khong bi trung
int TimDauSach(List ls, string tenSach, DauSach* dsach);//Tim kiem thong thong dau sach dua vao ten sach
//================================DANH_SACH_MUON_TRA==========================================
bool CheckLeapYear(const int& year);//kiem tra nam nhuan?
int SoNgayCuaThang(const int& month, const int& year);
struct Ngay{
	int ngay, thang, nam;
	Ngay():ngay(1), thang(1), nam(1970){}
	Ngay(int d, int m, int y):ngay(d), thang(m), nam(y){}
};
struct PhieuMuon{
	string maSach;//key khong duoc trung ISBN+ma so tu dong ngau nhien
	Ngay ngayMuon;
	Ngay ngayTra;
	short trangThai;
};

struct Node_Muon_Tra{
	PhieuMuon _phieuMuon;//du lieu cua Node(moi lan muon sach tuong ung voi 1 phieu muon)
	Node_Muon_Tra *next;//tro den node_muon_tra ke tiep
};

struct DANH_SACH_MUON_TRA{
	Node_Muon_Tra* first;
	DANH_SACH_MUON_TRA(){///khoi tao danh muc sach(danh sach lien ket don)
		this->first = NULL;
	}
	void Insert_First(PhieuMuon x);
	void Traverse(PhieuMuon* danhSachPhieuMuon, int dieuKien);//duyet va luu phieu muon voi dieu kien cho truoc vao mang danhSachPhieuMuon
	int TongSoPhieuMuon(int dieuKien);//dem so phieu muon dang muon chua tra = _phieuMuon.trangThai = 0
	bool Empty();
	void Clearlist();
};
//================================CAY_NHI_PHAN_DOC_GIA=========================================
struct Doc_Gia{
	int maDocGia; //so nguyen ngau nhien tu dong, keyword tim kiem
	string ho;
	string ten;
	string gioiTinh;
	short trangThai;
	DANH_SACH_MUON_TRA danhSachMuonTra;
};

struct node{
   int key;
   Doc_Gia info;
   struct node *left;
   struct node *right;
};
typedef node* NODEPTR;
void Initialize(NODEPTR &root);//khoi tao cay nhi phan
void Insert_node(NODEPTR &p, int x, Doc_Gia a);//chen nut vao cay nhi phan
int Empty_Tree(NODEPTR root);//kiem tra cay nhi phan rong hay khong
void remove_case_3( NODEPTR  &r);
int remove(int x,  NODEPTR &p);//xoa node tren cay nhi phan--xoa doc gia
NODEPTR Search(NODEPTR root, int x);//tim kiem thong tin doc gia dua vao ma so doc gia--tim kiem de hieu chinh thong tin doc gia
void Inorder(NODEPTR p, Doc_Gia* docGia, int n);//duyet cay bang phuong phap LNR va luu vao mang docGia, n so luong doc gia
#endif
