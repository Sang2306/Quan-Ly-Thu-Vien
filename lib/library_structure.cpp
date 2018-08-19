#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "library_structure.hpp"
using namespace std;
//=========================================LIST============================================
bool Empty(List ls){//ham kiem tra rong cua danh sach tuyen tinh DAUSACH
	return ls.soLuong == 0;
}
bool Full(List ls){//ham kiem tra day cua danh sach tuyen tinh DAUSACH
	return ls.soLuong == MAX_SIZE;
}
int ThemDauSach(List &ls, DauSach* dsach)//ham insert DauSach vao List
{
	if(Full(ls))
		return 0;
	ls.dausach[ls.soLuong] = dsach;
	ls.soLuong += 1;
	return 1;
}
bool TonTaiISBN(const List& ls, string ISBN){//kiem tra ma so ISBN nhap vao khong bi trung
	for (int i = 0; i < ls.soLuong; i++){
		if (ls.dausach[i]->ISBN == ISBN)
			return true;
	}
	return false;
}
int TimDauSach(List ls, string tenSach, DauSach* dsach)//Tim thong tin sach trong danh sach cac dau sach
{
	for ( int i =0 ; i < ls.soLuong ; i++)
	{
		if (ls.dausach[i]->tenSach == tenSach)
		{
			*dsach = *ls.dausach[i];
			return 1;
		}
	}
	return 0;
}
//=========================================DANH_MUC_SACH===================================
void DANH_MUC_SACH::Insert_First(Sach x)//ham Insert_First(Sach x)
{
	Node_Sach* p = new Node_Sach;
	p->_sach = x;
	p->next	= this->first;
	this->first = p;
}
bool DANH_MUC_SACH::Empty(){//ham kiem tra rong Empty()
	return(this->first == NULL);
}

void DANH_MUC_SACH::Clearlist()
{  
    Node_Sach* p;  
  	while(this->first != NULL)
    {
      p = this->first;
      this->first = this->first->next;
      delete p;
    }
}
void DANH_MUC_SACH::Traverse(Sach* sachArr, int dieuKien)
{ 
	int i = 0;
   	for(Node_Sach* p = this->first; p != NULL; p = p->next)
   	{
   		if(p->_sach.trangThai==dieuKien)		//chi them vao vector nhung sach thoa dk
   			sachArr[i++] = p->_sach;
	}
}

int DANH_MUC_SACH::TongSoLuongSach(int dieuKien)
{ 
	int _tongsoluongsach = 0;
   	for(Node_Sach* p = this->first; p != NULL; p = p->next)
   	{
   		if(p->_sach.trangThai==dieuKien)		//chi them vao vector nhung sach thoa dk
   			_tongsoluongsach++;
	}
	return _tongsoluongsach;
}

int DANH_MUC_SACH::TonTai(string maSach)
{
   	for(Node_Sach* p = this->first; p != NULL; p = p->next)
   	{
   		if(p->_sach.maSach==maSach && p->_sach.trangThai == 0)
   			return 1;
	}
	return 0;
}
void DANH_MUC_SACH::DanhDau(string maSach, int tt)
{
   	for(Node_Sach* p = this->first; p != NULL; p = p->next)
   	{
   		if(p->_sach.maSach==maSach)
   		{
   			p->_sach.trangThai = tt;	//danh dau la ma sach nay da duoc muon, tra, hay mat sach va thoat
   			break;
		}
	}
}
//=========================================DANH_SACH_MUON_TRA===================================
void DANH_SACH_MUON_TRA::Insert_First(PhieuMuon x)//ham Insert_First
{
	Node_Muon_Tra* p = new Node_Muon_Tra;
	p->_phieuMuon = x;
	p->next	= this->first;
	this->first = p;
}
bool DANH_SACH_MUON_TRA::Empty(){//ham kiem tra rong Empty()
	return(this->first == NULL);
}

void DANH_SACH_MUON_TRA::Clearlist()
{  
    Node_Muon_Tra* p; 
  	while(this->first != NULL)
    {
      p = this->first;
      this->first = this->first->next;
      delete p;
    }
}
void DANH_SACH_MUON_TRA::Traverse(PhieuMuon* danhSachPhieuMuon, int dieuKien)
{
	int i = 0;
   	for(Node_Muon_Tra* pm = this->first; pm != NULL; pm = pm->next)//duyet danh sach muon tra
   	{
   		if(pm->_phieuMuon.trangThai==dieuKien)
   			danhSachPhieuMuon[i++] = pm->_phieuMuon;
	}
}
int DANH_SACH_MUON_TRA::TongSoPhieuMuon(int dieuKien)///dem so phieu muon co trang thai = 0(dang muon)
{
	int _sosachdangmuon = 0;
   	for(Node_Muon_Tra* pm = this->first; pm != NULL; pm = pm->next)//duyet danh sach muon tra
   	{
   		if(pm->_phieuMuon.trangThai==dieuKien)
   			_sosachdangmuon++;
	}
	return _sosachdangmuon;//tra ve so luong phieu muon(tu la so luong sach da muon)
}
//================================CAY_NHI_PHAN_DOC_GIA=========================================
void Initialize(NODEPTR &root)
{
   root = NULL;
}

void Insert_node(NODEPTR &p, int x, Doc_Gia a)//ham duoc dung trong ham Create_Tree
{ 
    if(p == NULL)    					// nut p hien tai la nut la
    {
	    p = new node;
	    p->key  = x;      	p->info = a;//gan noi dung doc gia vao node p
	    p->left = NULL;     p->right = NULL;
	}
    else if(x < p->key )
      	Insert_node(p->left, x, a);
    else if(x > p->key )	    
		Insert_node(p->right, x, a);
}

int Empty_Tree(NODEPTR root){
   return(root == NULL ? true : false);
}
//Huy mot doc gia
NODEPTR rp;
void  remove_case_3( NODEPTR  &r)
{
  	if (r->left != NULL)
	   remove_case_3 (r->left);
   	//den day r la nut cuc trai cua cay con ben phai co nut goc la rp}
    else 
	{
	   rp->key = r->key;    //Chep noi dung cua r sang rp ";
	   rp->info =r->info;	//de lat nua delete rp
	   rp = r;           	
	   r = rp->right;
	}
}
int  remove(int x ,  NODEPTR &p)//xoa theo key cua node doc gia
{
	if (p == NULL)
		return 0;
	if (x < p->key)
		remove (x, p->left);
	else if (x > p->key)
		remove (x, p->right);
	else{// p->key = x
	
		rp = p;
        if (rp->right == NULL)  p = rp->left;   
		// p là nút lá hoac la nut chi co cay con ben trai
		else if (rp->left == NULL)
			p = rp->right;  // p là nut co cay con ben phai
		else
			remove_case_3 (rp->right);
		delete rp;
   }
   return 1;
}

NODEPTR Search(NODEPTR root, int x)//tim kiem tren cay nhi phan theo khoa x
{
   	NODEPTR p;
   	p = root;
   	while (p != NULL && p->key !=x)
    {
    	if(x < p->key)
       		p = p->left;
      	else
         	p = p->right;
	}
	return p;
}
int i = 0;
void Inorder(NODEPTR p, Doc_Gia* docGia, int n)
{ 
	
	if(p != NULL)    
  	{  
		Inorder(p->left, docGia, n);
		docGia[i++] = p->info;
		if(i==n)
   			i = 0;
		Inorder(p->right, docGia, n);
   	}
}
//==================================
bool CheckLeapYear(const int& year){
	return (year%4==0 && year%100!=0 && year%400==0);
}

int months[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int SoNgayCuaThang(const int& month, const int& year){
	if(CheckLeapYear(year))
		return (month==2)?(months[month]+1):(months[month]);
	else
		return months[month];
}
