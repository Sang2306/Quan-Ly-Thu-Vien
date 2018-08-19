#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include "lib/MenuDong.h"
#include "lib/draw.h"
#include "lib/check.h"
#include "lib/consolelib.h"
#include "lib/library_structure.hpp"
using namespace std;
void ThanhPhanDocGia();
void HienThiThongTinDocGia(Doc_Gia& d_gia);
void ChinhSuaDocGia(Doc_Gia& d_gia);
int ThemDocGia(Doc_Gia& d_gia);
int XoaDocGia();
void HieuChinhThongTinDocGia();
void HienThiTheoHoTenDocGiaTangDan();
void HienThiTheoMaDocGiaTangDan();
void MuonSach();
void TraSach();
void KiemTraSachDocGiaDangMuon();
int CacSachDocGiaDangMuon(const PhieuMuon* danhSachPhieuMuon, int soLuongSachDangMuon, int y1, int y2);
void DocGiaMuonSachQuaHan();
void TopMuoiSachDuocMuonNhieuNhat();
///////////////////////////////////////////////////////////////////////////////////////
void HienThiThongTinDauSach(DauSach* dsach);
void ChinhSuaDauSach(DauSach* dsach);
int ThemDauSach(DauSach* dsach);
void DanhMaSachTuDong(DauSach* dsach);
void HienThiDauSachTenTangDan();
void TimThongTinSach(string ten_sach = "default");
///////////////////////////////////////////////////////////////////////////////////////
const int SO_MA_SACH = 1000;
const int SO_MA_DOC_GIA = 1000;
int bookCode[SO_MA_SACH];
int readerCode[SO_MA_DOC_GIA];
void CreateRandomCode(int CodeArray[], int N);
int TakeReaderCode();
int TakeBookCode();
void GhiFileReaderCode(int readerCode[]){
	ofstream code("data/readerRandomCode.txt");
	for(int i = 0; i < SO_MA_DOC_GIA; i++){
		code << readerCode[i] << " ";
	}
	code.close();
}
void DocFileReaderCode(int readerCode[]){
	ifstream code("data/readerRandomCode.txt");
	int i = 0;
	while(code >> readerCode[i]){
		i++;
	}
	code.close();
}
//////////////////////////////////////////////////////////////////////////////////////////////
void GhiFileDocGia(const char* fileName, Doc_Gia& Object);
void GhiFilePhieuMuon(const char* fileName, PhieuMuon& Object);
void GhiFileDauSach(const char* fileName, DauSach* Object);
void GhiFileDanhMucSach(const char* fileName, DauSach* Object);

void DocDuLieuDocGia(const char* fileName);
void DocDuLieuPhieuMuon(const char* fileName, Doc_Gia& docgia);
void DocDuLieuDauSach(const char* fileName);
void DocDuLieuDanhMucSach(const char* fileName, DauSach* dausach);

void CapNhatDuLieuDocGia(NODEPTR p);
void CapNhatDanhSachPhieuMuon(NODEPTR p);
void CapNhatDanhMucSach(List& khosach);
int getKeyCode();
void userInput(int y, int start, int limit, string& _userstring);
void LoginSession();
void Insertion_Sort(int arr1[], int arr2[]);

struct RatingStar{//thong tin sach nam trong top 10 sach duoc muon nhieu nhat
	int _soLuotMuon;
	string _tenSach;
};
void QuickSort(RatingStar A[], int left, int right);
////////////////////////////////////////////////////
void GiaiPhongDocGia_DanhSachMuonTra(NODEPTR p);
void GiaiPhongDanhMucSach(List& khosach);
////////////////////////////////////////////////////
List khoSach;
////////////////////////////////////////////////////
NODEPTR root;
int _soLuongDocGia = 0;
int readerIndex = 0;
int bookIndex = 1;
////////////////////////////////////////////////////
int main(){
	ChangeFont();								//thay doi font
	SetConsoleTitleA("Library");				//Thiet lap ten cua so hien thi
	MoveWindow(GetConsoleWindow(), 0, 0, 1370, 768, TRUE);//chinh lai kich thuoc console
	DisableMaximizeButton();					//khong cho user mo rong cosole
	LoginSession();								//man hinh dang nhap
	ShowCursor(false);							//an con tro
	DrawInterface();							//ve giao dien
	CreateRandomCode(bookCode, SO_MA_SACH);		//khoi tao mang luu tru ma sach ngau nhien
//	CreateRandomCode(readerCode, SO_MA_DOC_GIA);//chi tao ma doc gia khi muon tao mang chua cac ma doc gia duoc tao ngau nhien moi
	Initialize(root);
//	GhiFileReaderCode(readerCode);				//chi su dung khi muon tao file chua ma doc gia ngau nhien moi
	DocFileReaderCode(readerCode);				//luu tru ma doc gia tu file vao mang
	DocDuLieuDocGia("data/reader.dat");			//doc du lieu doc gia
	DocDuLieuDauSach("data/book.dat");			//doc du lieu dau sach
	int chon;
	while(chon!=10)
	{
		main_menu:
		chon = MenuChinh(main_Menu, 10, 2, 4);
		if(chon==1){
			XoaKhuNoiDung(2, 4, bienTrai-2, h-2);
			sub_menu0:
			int chon1 = MenuChinh(nhapdocgia, 4, 2, 4);
			if(chon1==1){
				Print_at(bienTrai+1, 1, "Nhap QUIT de tro ve");
				Print_at((w-bienTrai)/2 + bienTrai - 7, 2, "THEM DOC GIA");
				Doc_Gia d;
				if(ThemDocGia(d)){
					ChinhSuaDocGia(d);
					Insert_node(root, d.maDocGia, d);
					GhiFileDocGia("data/reader.dat", d);//ghi doc gia vao file
			 		_soLuongDocGia++;
			 		GhiFileReaderCode(readerCode);       //cap nhat lai du lieu trong file
				}else{
					int msg = MessageBox(GetConsoleWindow(), "Ban co muon luu du lieu?", "Cau hoi", MB_OKCANCEL | MB_ICONQUESTION);
					if(msg == IDOK){
						Insert_node(root, d.maDocGia, d);//luu du lieu khong hoan thien trong RAM
						_soLuongDocGia++;
					}else{
						readerIndex--;
						Swap(readerCode[readerIndex], readerCode[rand()%SO_MA_DOC_GIA + (readerIndex+1)]);
						GhiFileReaderCode(readerCode);       //cap nhat lai du lieu trong file
					}
				}
				Print_at(bienTrai+1, 1, "                    ");
				Print_at((w-bienTrai)/2 + bienTrai - 7, 2, "            ");
				XoaKhuNoiDung();
				goto sub_menu0;
			}else if(chon1==2){
				Print_at(bienTrai + 1, 1, "Nhap QUIT de tro ve");
				Print_at((w-bienTrai)/2 + bienTrai - 7, 2, "XOA THONG TIN DOC GIA");
				int maDocGiaDaXoa = XoaDocGia();
				if (maDocGiaDaXoa!=-1) //khi nguoi dung nhap QUIT
				{
					int vitri = 0;
					while(readerCode[vitri] != maDocGiaDaXoa) { vitri++;}//tim kiem tuyen tinh vi tri ma doc gia trong mang
					Swap(readerCode[vitri], readerCode[--readerIndex]); //swap vi tri tim kiem duoc voi vi tri ma tiep theo sau cung
					GhiFileReaderCode(readerCode);
					DocFileReaderCode(readerCode);
					_soLuongDocGia--;
				}
				Print_at(bienTrai + 1, 1, "                   ");
				Print_at((w-bienTrai)/2 + bienTrai - 7, 2, "                     ");
				XoaKhuNoiDung();
				goto sub_menu0;
			}else if(chon1==3){
				Print_at(bienTrai + 1, 1, "Nhap QUIT de tro ve");
				Print_at((w-bienTrai)/2 + bienTrai - 7, 2, "HIEU CHINH THONG TIN DOC GIA");
				HieuChinhThongTinDocGia();
				Print_at(bienTrai + 1, 1, "                   ");
				Print_at((w-bienTrai)/2 + bienTrai - 7, 2, "                            ");
				XoaKhuNoiDung();
				goto sub_menu0;
			}
		}
		if(chon==2){
			XoaKhuNoiDung(2, 4, bienTrai-2, h-2);
			Print_at((w-bienTrai)/2 + bienTrai - 7, 2, "DANH SACH DOC GIA");
			sub_menu1:
			int chon2 = MenuChinh(tuyChon_HienThi, 3, 2, 4);
			if(chon2==1){
				Print_at(bienTrai + 1, 1, "ESC: Tro ve");
				HienThiTheoHoTenDocGiaTangDan();
				Print_at(bienTrai + 1, 1, "           ");
				XoaKhuNoiDung();
				goto sub_menu1;
			}else if(chon2==2){
				Print_at(bienTrai + 1, 1, "ESC: Tro ve");
				HienThiTheoMaDocGiaTangDan();
				Print_at(bienTrai + 1, 1, "           ");
				XoaKhuNoiDung();
				goto sub_menu1;
			}else if(chon2==3){
				Print_at(bienTrai + 1, 1, "           ");
				Print_at((w-bienTrai)/2 + bienTrai - 7, 2, "                 ");
			}
		}
		if(chon==3){
			Print_at(bienTrai + 1, 1, "Nhap QUIT de tro ve");
			Print_at((w-bienTrai)/2 + bienTrai - 7, 2, "THEM DAU SACH");
			DauSach* a = new DauSach;
			if(ThemDauSach(a)){
				ChinhSuaDauSach(a);
				DanhMaSachTuDong(a);					//danh ma sach tu dong cho so luong sach da nhap trong NhapDauSach()
				ThemDauSach(khoSach, a);				//them DauSach a vao khoSach
				GhiFileDauSach("data/book.dat", a);		//ghi Dau Sach Vao file
				const string fileName = "data/" + a->ISBN + ".dat";
				GhiFileDanhMucSach(fileName.c_str(), a);//ghi danh muc sach cua dau sach a vao file "isbn".dat
			}
			Print_at(bienTrai + 1, 1, "                     ");
			Print_at((w-bienTrai)/2 + bienTrai - 7, 2, "             ");
			XoaKhuNoiDung();
		}
		if(chon==4){
			Print_at(bienTrai + 1, 1, "ESC: Tro ve | ENTER: Xem thong tin");
			Print_at((w-bienTrai)/2 + bienTrai - 7, 2, "DANH SACH DAU SACH");
			HienThiDauSachTenTangDan();
			Print_at(bienTrai + 1, 1, "                                  ");
			Print_at((w-bienTrai)/2 + bienTrai - 7, 2, "                  ");
			XoaKhuNoiDung();
		}
		if(chon==5){
			Print_at((w-bienTrai)/2 + bienTrai - 7, 2, "TIM THONG TIN SACH");
			TimThongTinSach();
			Print_at((w-bienTrai)/2 + bienTrai - 7, 2, "                  ");
			XoaKhuNoiDung();
		}
		if(chon==6){
			XoaKhuNoiDung(2, 4, bienTrai-2, h-1);
			sub_menu2:
			int chon6 = MenuChinh(muon_sach, 3, 2, 4);
			if(chon6==1){
				Print_at(bienTrai + 1, 1, "Nhap QUIT de tro ve");
				Print_at((w-bienTrai)/2 + bienTrai - 7, 2, "MUON SACH");
				MuonSach();
				Print_at(bienTrai + 1, 1, "                   ");
				Print_at((w-bienTrai)/2 + bienTrai - 7, 2, "         ");
				XoaKhuNoiDung();
				goto sub_menu2;
			}else if(chon6==2){
				Print_at(bienTrai + 1, 1, "Nhap QUIT de tro ve");
				Print_at((w-bienTrai)/2 + bienTrai - 7, 2, "TRA SACH");
				TraSach();
				XoaKhuNoiDung();
				Print_at(bienTrai + 1, 1, "                   ");
				Print_at((w-bienTrai)/2 + bienTrai - 7, 2, "        ");
				goto sub_menu2;
			}
			
		}
		if(chon==7){
			Print_at(bienTrai + 1, 1, "Nhap QUIT de tro ve");
			Print_at((w-bienTrai)/2 + bienTrai - 7, 2, "SACH DOC GIA DANG MUON");
			KiemTraSachDocGiaDangMuon();
			Print_at(bienTrai + 1, 1, "                   ");
			Print_at((w-bienTrai)/2 + bienTrai - 7, 2, "                      ");
			XoaKhuNoiDung();
		}
		if(chon==8){
			Print_at((w-bienTrai)/2 + bienTrai - 7, 2, "DANH SACH DOC GIA QUA HAN");
			DocGiaMuonSachQuaHan();
			Print_at((w-bienTrai)/2 + bienTrai - 7, 2, "                         ");
		}
		if(chon==9){
			Print_at((w-bienTrai)/2 + bienTrai - 7, 2, "TOP 10 SACH DUOC MUON NHIEU NHAT");
			TopMuoiSachDuocMuonNhieuNhat();
			Print_at((w-bienTrai)/2 + bienTrai - 7, 2, "                                ");
			XoaKhuNoiDung();
		}
	}
	remove("data/reader.dat");//xoa file
	CapNhatDuLieuDocGia(root);//, va tao file moi
	CapNhatDanhSachPhieuMuon(root);
	CapNhatDanhMucSach(khoSach);
	//giai phong vung nho
	GiaiPhongDocGia_DanhSachMuonTra(root);//giai phong bo nho cho danh sach muon tra va doc gia
	GiaiPhongDanhMucSach(khoSach);
	return EXIT_SUCCESS;
}
/*end main*/
//================================CAC_CHUC_NANG_CUA_CHUONG_TRINH=================================================
//================================Cac ham tao ma sach va ma doc gia tu dong======================================
void CreateRandomCode(int CodeArray[], int N)
{
	srand(time(NULL));
	int RANGE = N;
	int *Temp = new int[N];
	for(int i = 1; i <= N; i++)
		Temp[i] = i;
	for(int i = 1; i <= N; i++){
		int r = rand()%RANGE + 1;
		CodeArray[i] = Temp[r];
		Temp[r] = Temp[RANGE];
		RANGE--;
	}
	delete[] Temp;
}

int TakeReaderCode()
{   
	return readerCode[readerIndex++];						
}																	
int TakeBookCode()
{
	if(bookIndex>=SO_MA_SACH)
		bookIndex = 1;
	return bookCode[bookIndex++];
}
//================================Cac ham xu xu DocGia va danh sach muon tra=====================================
void ThanhPhanDocGia()
{
	Print_at(bienTrai + 1, 5, "Ma DG ");
	drawRect(Point(bienTrai + 8 , 4), Point(bienTrai + 38, 6));
	Print_at(bienTrai + 1, 8, "Ho ");
	drawRect(Point(bienTrai + 8 , 7), Point(bienTrai + 38, 9));
	Print_at(bienTrai + 1, 11, "Ten ");
	drawRect(Point(bienTrai + 8 , 10), Point(bienTrai + 38, 12));
	Print_at(bienTrai + 1, 14, "G.Tinh");
	drawRect(Point(bienTrai + 8 , 13), Point(bienTrai + 38, 15));
	Print_at(bienTrai + 1, 17, "T.Thai");
	drawRect(Point(bienTrai + 8 , 16), Point(bienTrai + 38, 18));
	Setcolor(YELLOW);
	Print_at(bienTrai + 1, 25, "Tuy chon");
	for(int x = 1; x < w-bienTrai-2; x++){
		for(int y = 26; y < h; y++){
			Setbkcolor(LIGHTBLUE);
			Print_at(bienTrai+x, y, ' ');
		}
	}
	Print_at(bienTrai + 15, h-3, "Nhap day du cac thong tin truoc khi chinh sua !");
	Setcolor(WHITE);
	Setbkcolor(BLACK);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ThemDocGia(Doc_Gia& d_gia)
{
	ThanhPhanDocGia();//hien thi cac truong cua doc gia
	stringstream ss;
	string temp;
	
m1:	Moveto(bienTrai + 9, 5);
	int ma_doc_gia = TakeReaderCode();
	cout << ma_doc_gia;
	d_gia.maDocGia = ma_doc_gia;
	
m2: userInput(8, bienTrai + 9, bienTrai + 38, d_gia.ho);
	
	if(d_gia.ho=="QUIT") {
		d_gia.ho.clear();
		return 0;
	}
	if(d_gia.ho.empty()) goto m2;
	
m3:	userInput(11, bienTrai + 9, bienTrai + 38, d_gia.ten);
	
	if(d_gia.ten=="QUIT") {
		d_gia.ten.clear();
		return 0;
	}
	if(d_gia.ten.empty()) goto m3;
	
m4:	userInput(14, bienTrai + 9, bienTrai + 38, d_gia.gioiTinh);
	
	if(d_gia.gioiTinh=="QUIT") {
		d_gia.gioiTinh.clear();
		return 0;
	}
	if(d_gia.gioiTinh.empty()) goto m4;
	if(d_gia.gioiTinh!="NAM" && d_gia.gioiTinh!="NU"){
		MessageBox(GetConsoleWindow(), "Gioi tinh Nam hoac Nu", "Canh bao", MB_OK | MB_ICONWARNING);
		goto m4;
	}
		
m5:	userInput(17, bienTrai + 9, bienTrai + 38, temp);
	
	if(temp=="QUIT")
		return 0;
	if(temp.empty()) goto m5;
	ss << temp;
	int j;
	ss >> j;
	if(IsNotNumber(temp) || (j!=0 && j!=1)) {
		MessageBox(GetConsoleWindow(),"Trang thai the khong hop le\n0-Bi khoa\n1-Dang hoat dong!","Canh bao", MB_OK | MB_ICONWARNING);
		ss.clear();
		goto m5;
	}
	d_gia.trangThai=j;
	return 1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HienThiThongTinDocGia(Doc_Gia& d_gia)
{
	Print_at(bienTrai + 1, 5, "Ma DG ");
	drawRect(Point(bienTrai + 8 , 4), Point(bienTrai + 38, 6));
	Print_at(bienTrai + 9, 5, d_gia.maDocGia);
	Print_at(bienTrai + 1, 8, "Ho ");
	drawRect(Point(bienTrai + 8 , 7), Point(bienTrai + 38, 9));
	Print_at(bienTrai + 9, 8, d_gia.ho);
	Print_at(bienTrai + 1, 11, "Ten ");
	drawRect(Point(bienTrai + 8 , 10), Point(bienTrai + 38, 12));
	Print_at(bienTrai + 9, 11, d_gia.ten);
	Print_at(bienTrai + 1, 14, "G.Tinh");
	drawRect(Point(bienTrai + 8 , 13), Point(bienTrai + 38, 15));
	Print_at(bienTrai + 9, 14, d_gia.gioiTinh);
	Print_at(bienTrai + 1, 17, "T.Thai");
	drawRect(Point(bienTrai + 8 , 16), Point(bienTrai + 38, 18));
	Print_at(bienTrai + 9, 17, d_gia.trangThai);;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChinhSuaDocGia(Doc_Gia& d_gia)
{
	Print_at(bienTrai+1, 2,"                              ");
	Setcolor(YELLOW);
	Print_at(bienTrai + 1, 25, "Tuy chon");
	Setcolor(WHITE);
	stringstream ss;
	string temp;
	int chon = -1;
	while(chon != 0)
	{
		chon = HopNoiDung(edit_Doc_Gia, 5, bienTrai + 2, 27, w-3, h-1, true);
		if(chon==0) break;
		switch(chon)
		{
			case 1:{
			c1:	userInput(8, bienTrai + 9, bienTrai + 38, d_gia.ho);
				if(d_gia.ho.empty()) goto c1;
			}break;
			case 2:{
			c2:	userInput(11, bienTrai + 9, bienTrai + 38, d_gia.ten);
				if(d_gia.ten.empty()) goto c2;
			}break;
			case 3:{
			c3:	userInput(14, bienTrai + 9, bienTrai + 38, d_gia.gioiTinh);
				if(d_gia.gioiTinh.empty()) goto c3;
				if(d_gia.gioiTinh!="NAM" && d_gia.gioiTinh!="NU"){
					MessageBox(GetConsoleWindow(), "Gioi tinh Nam hoac Nu", "Canh bao", MB_OK | MB_ICONWARNING);
					goto c3;
				}
			}break;
			case 4:{
				temp = to_string(d_gia.trangThai);
			c4:	userInput(17, bienTrai + 9, bienTrai + 38, temp);
				ss << temp;
				int j;
				ss >> j;
				if(temp.empty()) goto c4;
				if(IsNotNumber(temp) || (j!=0 && j!=1)) {
					MessageBox(GetConsoleWindow(),"Trang thai the khong hop le\n0-Bi khoa\n1-Dang hoat dong!","Canh bao", MB_OK | MB_ICONWARNING);
					ss.clear();
					goto c4;
				}
				d_gia.trangThai=j;
			}break;
			default: break;
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HienThiTheoHoTenDocGiaTangDan()
{
	if(_soLuongDocGia==0){
		Print_at((w-bienTrai)/2 + bienTrai - 8, (h-3)/2 + 3, "(Khong co du lieu)");
		_getch();
		return;
	}
	Doc_Gia docGia[_soLuongDocGia];
	Inorder(root, docGia, _soLuongDocGia);
	for(int i = 1; i < _soLuongDocGia; i++)//dung thuat toan sap xep chen de sap xep theo thu tu ho+ten tang dan
	{
		Doc_Gia X = docGia[i];
		int pos = 0;
		while(docGia[i].ho + docGia[i].ten > docGia[pos].ho + docGia[pos].ten)
			pos++;
		for (int j = i; j > pos; j--){
			docGia[j] = docGia[j-1];
		}
		docGia[pos] = X;
	}
	fstream file("docgia.txt", ios::out);
	for(int i = 0; i < _soLuongDocGia; i++)//luu du lieu ra file voi moi doc gia tuong ung voi mot dong trong file
	{
		file << docGia[i].maDocGia << "\t\t" << docGia[i].ho;
		for(int space = 0; space < 8 + (10 - docGia[i].ho.length()); space++)
			file << " ";
		file << docGia[i].ten;
		for(int space = 0; space < 8 + (22 - docGia[i].ten.length()); space++)
			file << " ";
		file << docGia[i].gioiTinh << "\t\t" << docGia[i].trangThai << "\n";
	}
	file.close();
	file.open("docgia.txt", ios::in);//lay du lieu trong file voi moi dong tuong ung la mot chuoi ky tu 
	if(!file.is_open()){
		return;
	}
	string str[_soLuongDocGia];
	for(int i = 0; i < _soLuongDocGia; i++){
		getline(file, str[i]);
	}
	Print_at(bienTrai+2, 4, "Ma DG\tHo\t\t  Ten\t\t\t\tGioi Tinh\tTrang Thai");
	HopNoiDung(str, _soLuongDocGia, bienTrai+2, 6, w-3, h-1);
	file.close();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HienThiTheoMaDocGiaTangDan()
{
	if(_soLuongDocGia==0){
		Print_at((w-bienTrai)/2 + bienTrai - 8, (h-3)/2 + 3, "(Khong co du lieu)");
		_getch();
		return;
	}
	Doc_Gia docGia[_soLuongDocGia];
	Inorder(root, docGia, _soLuongDocGia);//duyet va luu doc gia vao mang docGia ma doc gia tang dan de hien thi
	fstream file("docgia.txt", ios::out);
	for(int i = 0; i < _soLuongDocGia; i++)//luu du lieu ra file voi moi doc gia tuong ung voi mot dong trong file
	{
		file << docGia[i].maDocGia << "\t\t" << docGia[i].ho;
		for(int space = 0; space < 8 + (10 - docGia[i].ho.length()); space++)
			file << " ";
		file << docGia[i].ten;
		for(int space = 0; space < 8 + (22 - docGia[i].ten.length()); space++)
			file << " ";
		file << docGia[i].gioiTinh << "\t\t" << docGia[i].trangThai << "\n";
	}
	file.close();
	file.open("docgia.txt", ios::in);//lay du lieu trong file voi moi dong tuong ung la mot chuoi ky tu 
	if(!file.is_open()){
		return;
	}
	string str[_soLuongDocGia];
	for(int i = 0; i < _soLuongDocGia; i++){
		getline(file, str[i]);
	}
	Print_at(bienTrai+2, 4, "Ma DG\tHo\t\t  Ten\t\t\t\tGioi Tinh\tTrang Thai");
	HopNoiDung(str, _soLuongDocGia, bienTrai+2, 6, w-3, h-1);
	file.close();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int XoaDocGia()
{
	drawRect(Point(bienTrai+1, 4), Point(bienTrai+9, 6));
	cout << "Ma DG";
	drawRect(Point(bienTrai+10, 4), Point(w-3, 6));
	string temp;
	stringstream ss;
x1:	userInput(5, bienTrai+11, w-3, temp);
	if(temp.empty())
		goto x1;
	if(temp=="QUIT") return -1;
x2:	if(IsNotNumber(temp)){
		MessageBox(GetConsoleWindow(), "Ma doc la so nguyen", "Thong bao", MB_OK | MB_ICONINFORMATION);
		userInput(5, bienTrai + 11, w-3, temp);
		if(temp.empty())
			goto x1;
		if(temp=="QUIT") return -1;
		goto x2;
	}
	ss << temp;
	int maDocGia;
	ss >> maDocGia;
	NODEPTR doc_gia = Search(root, maDocGia);
	if(doc_gia!=NULL){
		int msg = MessageBox(GetConsoleWindow(), "Ban co muon xoa doc gia nay", "Cau hoi", MB_OKCANCEL | MB_ICONQUESTION);
		if(msg==IDOK){
			remove(maDocGia, root);
			temp = "data/" + temp + ".dat";//xoa luon phieu muon cua doc gia
			remove(temp.c_str());
			MessageBox(GetConsoleWindow(), "Hoan thanh!", "Thong bao", MB_OK | MB_ICONINFORMATION);
		}
	}else{
		MessageBox(GetConsoleWindow(), "Khong tim thay!", "Thong bao", MB_OK | MB_ICONINFORMATION);
	}
	fflush(stdin);
	return maDocGia;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HieuChinhThongTinDocGia()
{
	drawRect(Point(bienTrai+1, 4), Point(bienTrai+9, 6));
	cout << "Ma DG";
	drawRect(Point(bienTrai+10, 4), Point(w-3, 6));
	string temp;
	stringstream ss;
x1:	userInput(5, bienTrai+11, w-3, temp);
	if(temp.empty())
		goto x1;
	if(temp=="QUIT") return;
x2:	if(IsNotNumber(temp)){
		MessageBox(GetConsoleWindow(), "Ma doc gia la so nguyen", "Thong bao", MB_OK | MB_ICONINFORMATION);
		userInput(5, bienTrai + 11, w-3, temp);
		if(temp.empty())
			goto x1;
		if(temp=="QUIT") return;
		goto x2;
	}
	ss << temp;
	int maDocGia;
	ss >> maDocGia;
	NODEPTR doc_gia = Search(root, maDocGia);
	if(doc_gia!=NULL){
		XoaKhuNoiDung();
		HienThiThongTinDocGia(doc_gia->info);
		int msg = MessageBox(GetConsoleWindow(), "Ban co muon chinh sua doc gia nay", "Cau hoi", MB_OKCANCEL | MB_ICONQUESTION);
		if(msg==IDOK){
			ChinhSuaDocGia(doc_gia->info);
			MessageBox(GetConsoleWindow(), "Hoan thanh!", "Thong bao", MB_OK | MB_ICONINFORMATION);
		}
	}else{
		MessageBox(GetConsoleWindow(), "Khong tim thay!", "Thong bao", MB_OK | MB_ICONINFORMATION);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MuonSach()
{
	time_t rawtime;
	time(&rawtime);
	struct tm* currTime;
	currTime = localtime(&rawtime);
	Print_at(bienTrai + 2, 4, "Ngay muon: ");
	cout << currTime->tm_mday << "/" << currTime->tm_mon + 1 << "/" << currTime->tm_year + 1900;//in ra ngay thang nam hien tai cua he thong
		
	drawRect(Point(bienTrai+1, 5), Point(bienTrai+9, 7));
	cout << "Ma DG";
	drawRect(Point(bienTrai+10, 5), Point(w-3, 7));
	fflush(stdin);
	string temp;
	stringstream ss;
x1:	userInput(6, bienTrai + 11, w-3, temp);
	if(temp.empty())
		goto x1;
	if(temp=="QUIT") return;
x2:	if(IsNotNumber(temp))
	{
		MessageBox(GetConsoleWindow(), "Ma doc gia la so nguyen", "Thong bao", MB_OK | MB_ICONINFORMATION);
		userInput(6, bienTrai + 11, w-3, temp);
		if(temp.empty())
			goto x1;
		if(temp=="QUIT") return;
		goto x2;
	}
	ss << temp;
	int maDocGia;
	ss >> maDocGia;
	NODEPTR doc_gia = Search(root, maDocGia);
	if(doc_gia!=NULL)	//neu co doc gia thi hien thi khung nhap ten sach muon muon
	{					
		if(doc_gia->info.trangThai==0)//////////////////kiem tra trang thai cua the
		{
			Print_at(bienTrai+1, 1, "Nhap phim bat ky de tro ve");
			Setcolor(LIGHTGREEN);
			Print_at((w-bienTrai)/2 + bienTrai - 8, 10, "The da bi khoa!");
			Setcolor(WHITE);
			_getch();
			Print_at(bienTrai+1, 1, "                          ");
			return;
		}
		////////////////////////hien ra danh sach cac sach ma doc gia nay dang muon
		int soLuongSachDangMuon = doc_gia->info.danhSachMuonTra.TongSoPhieuMuon(0);//tong so phieu dang muon
		int catchSig;////bat tin hieu khong the muon them sach
		if(soLuongSachDangMuon!=0)
		{
			PhieuMuon danhSachPhieuMuon[soLuongSachDangMuon];
		    doc_gia->info.danhSachMuonTra.Traverse(danhSachPhieuMuon, 0);////duyet va luu phieu dang muon vao mang danhSachPhieuMuon
			Print_at(bienTrai + 1, 1, "                   ");
			Print_at(bienTrai + 1, 1, "ESC: Tiep tuc");
			Setcolor(YELLOW);
			Print_at(bienTrai + 2, h-2, "--Chu y--");
			Print_at(bienTrai + 2, h-1, "*TT 0: Sach dang muon");
			Setcolor(WHITE);
			catchSig = CacSachDocGiaDangMuon(danhSachPhieuMuon, soLuongSachDangMuon, 10, 14);//catchSig chi bat tin hieu doc gia muon sach qua han
			Print_at(bienTrai + 1, 1, "             ");
		}else
			Print_at((w-bienTrai)/2 + bienTrai - 8, 12, "(Chua muon sach nao)");
		
		if(soLuongSachDangMuon>=3 || catchSig == 0 && soLuongSachDangMuon!=0)
		{
			Print_at(bienTrai + 1, 1, "Nhan phim bat ky de tiep tuc");
			Print_at((w-bienTrai)/2 + bienTrai - 8, 19, "(Khong the muon them sach)");
			getch();
			Print_at(bienTrai + 1, 1, "                            ");
			return;
		}
		
		Print_at(bienTrai + 1, 1, "                       ");
		drawRect(Point(bienTrai+1, 15), Point(bienTrai+9, 17));
		cout << "Ma Sach";
		drawRect(Point(bienTrai+10, 15), Point(w-3, 17));
x3:		string _masach;
		userInput(16, bienTrai + 11, w-3, _masach);
		if(_masach.empty()){goto x3;}
		////////////////////
		string _tensach;
		bool daTimThay = false;
		for(int vitri = 0; vitri < khoSach.soLuong; vitri++)
		{
			for(Node_Sach* p = khoSach.dausach[vitri]->danhMucSach.first; p!=NULL; p=p->next)
			{
				if(p->_sach.maSach == _masach)
				{
					_tensach =  khoSach.dausach[vitri]->tenSach;
					daTimThay = true;
					break;
				}
			}
			if(daTimThay)
				break;
		}
		if(!daTimThay)
		{
			int msg = MessageBox(GetConsoleWindow(), "Ma sach khong ton tai\n Thu lai?", "Thong bao", MB_OKCANCEL | MB_ICONINFORMATION);
			if(msg==IDOK)
			{
				XoaKhuNoiDung(bienTrai+11, 16, w-4, 16);
				goto x3;
			}
			else if(msg==IDCANCEL)
				return;
		}
		DauSach *dsach = new DauSach;
		TimDauSach(khoSach, _tensach, dsach);
		////////////////////kiem tra xem ma sach vua nhap da muon roi hay chua
		for(Node_Sach* p = dsach->danhMucSach.first; p!=NULL; p=p->next)
		{
			if(p->_sach.maSach == _masach && p->_sach.trangThai == 1)
			{
				int msg = MessageBox(GetConsoleWindow(), "Ma sach da duoc muon\n Thu lai?", "Thong bao", MB_OKCANCEL | MB_ICONINFORMATION);
				if(msg==IDOK)
				{
					XoaKhuNoiDung(bienTrai+11, 16, w-4, 16);
					goto x3;
				}
				else if(msg==IDCANCEL)
					return;
			}
		}
		////////////////////neu chua duoc muon thi duoc phep muon
		Ngay ngay_muon(currTime->tm_mday, currTime->tm_mon + 1, currTime->tm_year + 1900);//Tao ngay muon bang thoi gian he thong
		PhieuMuon pm;
		pm.maSach = _masach;
		pm.ngayMuon = ngay_muon;						//gan ngay muon cho phieu muon
		pm.trangThai = 0;								//trang thai phieu muon == 0 sach dang muon chua tra
		doc_gia->info.danhSachMuonTra.Insert_First(pm);	//them phieu muon vao danhsachmuontra cua doc gia
		dsach->danhMucSach.DanhDau(_masach, 1);			//danh dau la sach nay da duoc muon
		
		const string fileName = "data/" + to_string(maDocGia) + ".dat";
		GhiFilePhieuMuon(fileName.c_str(), pm);			//ghi file dinh dang madocgia.dat vd 535.dat trong thu muc data
		MessageBox(GetConsoleWindow(), "Hoan thanh!", "Thong bao", MB_OK | MB_ICONINFORMATION);
		delete dsach;
	}else{
		MessageBox(GetConsoleWindow(), "Khong tim thay!", "Thong bao", MB_OK | MB_ICONINFORMATION);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TraSach()
{
	time_t rawtime;
	time(&rawtime);
	struct tm* currTime;
	currTime = localtime(&rawtime);
	Print_at(bienTrai + 2, 4, "Ngay Tra: ");
	cout << currTime->tm_mday << "/" << currTime->tm_mon + 1 << "/" << currTime->tm_year + 1900;//in ra ngay thang nam hien tai cua he thong
		
	drawRect(Point(bienTrai+1, 5), Point(bienTrai+9, 7));
	cout << "Ma DG";
	drawRect(Point(bienTrai+10, 5), Point(w-3, 7));
	string temp;
	stringstream ss;
x1:	userInput(6, bienTrai + 11, w-3, temp);
	if(temp.empty())
		goto x1;
	if(temp=="QUIT") return;
x2:	if(IsNotNumber(temp)){
		MessageBox(GetConsoleWindow(), "Ma doc gia la so nguyen", "Thong bao", MB_OK | MB_ICONINFORMATION);
		userInput(6, bienTrai + 11, w-3, temp);
		if(temp.empty())
			goto x1;
		if(temp=="QUIT") return;
		goto x2;
	}
	ss << temp;
	int maDocGia;
	ss >> maDocGia;
	NODEPTR doc_gia = Search(root, maDocGia);
	if(doc_gia!=NULL)//////////////////////////neu co doc gia thi hien thi khung nhap ten sach muon muon
	{
		int soLuongSachDangMuon = doc_gia->info.danhSachMuonTra.TongSoPhieuMuon(0);
		if(soLuongSachDangMuon==0)
		{
			Print_at(bienTrai + 1, 1, "Nhan phim bat ky de tiep tuc");
			Print_at((w-bienTrai)/2 + bienTrai - 8, 10, "(Chua muon sach nao)");
			getch();
			Print_at(bienTrai + 1, 1, "                            ");
			return;
		}
		PhieuMuon danhSachPhieuMuon[soLuongSachDangMuon];
		doc_gia->info.danhSachMuonTra.Traverse(danhSachPhieuMuon, 0);////duyet va luu phieu dang muon vao mang danhSachPhieuMuon
		Print_at(bienTrai + 1, 1, "                       ");
		drawRect(Point(bienTrai+1, 8), Point(bienTrai+9, 10));
		cout << "Ma Sach";
		drawRect(Point(bienTrai+10, 8), Point(w-3, 10));
x3:		string _masach;
		userInput(9, bienTrai + 11, w-3, _masach);
		if(_masach.empty()){goto x3;}
		/////////kiem tra trong danh sach phieu muon cua doc gia co ma sach vua nhap vao hay khong neu khong co thi bao
		bool co_muon = false;
		for(Node_Muon_Tra* p = doc_gia->info.danhSachMuonTra.first; p!=NULL; p=p->next)
		{
			if(p->_phieuMuon.maSach == _masach && p->_phieuMuon.trangThai == 0)///////co muon va chua tra
			{
				co_muon = true;
				break;
			}
		}
		if(!co_muon)///////neu doc gia chua muon ma sach nay thi bao
		{
			int msg = MessageBox(GetConsoleWindow(), "Ma sach tren chua duoc doc gia muon hoac doc gia da tra truoc do\n Thu lai?", "Thong bao", MB_OKCANCEL | MB_ICONINFORMATION);
			if(msg==IDOK)
			{
				XoaKhuNoiDung(bienTrai+11, 9, w-4, 9);
				goto x3;
			}
			else if(msg==IDCANCEL)
				return;
		}
		/////////sau khi co duoc ma sach, tim ma sach trong kho sach -> ten sach, neu khong co bao khong tim thay du lieu//////////
		string _tensach;
		bool daTimThay = false;
		for(int vitri = 0; vitri < khoSach.soLuong; vitri++)
		{
			for(Node_Sach* p = khoSach.dausach[vitri]->danhMucSach.first; p!=NULL; p=p->next)
			{
				if(p->_sach.maSach == _masach)
				{
					_tensach =  khoSach.dausach[vitri]->tenSach;
					daTimThay = true;
					break;
				}
			}
			if(daTimThay)
				break;
		}

		if(!daTimThay)					//neu khong tim thay ten sach trong kho sach
		{
			int msg = MessageBox(GetConsoleWindow(), "Ma sach khong ton tai\n Thu lai?", "Thong bao", MB_OKCANCEL | MB_ICONINFORMATION);
			if(msg==IDOK)
			{
				XoaKhuNoiDung(bienTrai+11, 9, w-4, 9);
				goto x3;
			}
			else if(msg==IDCANCEL)
				return;
		}
		DauSach *dsach = new DauSach;
		TimDauSach(khoSach, _tensach, dsach);
		///////////////////////////////////////////////////////////////////////////////////////////////////////
		Ngay ngay_tra(currTime->tm_mday, currTime->tm_mon + 1, currTime->tm_year + 1900);//Tao ngay muon bang thoi gian he thong
		
		bool Success = true;
		for(Node_Muon_Tra* pm = doc_gia->info.danhSachMuonTra.first; pm != NULL; pm = pm->next)//duyet danh sach muon tra cua doc_gia
	   	{
	   		if(pm->_phieuMuon.maSach == _masach)
				{
	   				pm->_phieuMuon.trangThai = 1;						//trang thai 1 da tra sach
	   				pm->_phieuMuon.ngayTra = ngay_tra;					//gan ngay tra cho phieu muon
	   				dsach->danhMucSach.DanhDau(pm->_phieuMuon.maSach, 0);//danh dau la sach nay co the cho muon duoc
	   				Success = true;
					break;
				}
			else
				Success = false;
		}
		delete dsach;
		if(Success)
			MessageBox(GetConsoleWindow(), "Hoan thanh!", "Thong bao", MB_OK | MB_ICONINFORMATION);
		else
			MessageBox(GetConsoleWindow(), "Doc gia chua muon sach nay!", "Thong bao", MB_OK | MB_ICONINFORMATION);
	}else
		MessageBox(GetConsoleWindow(), "Khong tim thay!", "Thong bao", MB_OK | MB_ICONINFORMATION);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void KiemTraSachDocGiaDangMuon()
{
	drawRect(Point(bienTrai+1, 4), Point(bienTrai+9, 6));
	cout << "Ma DG";
	drawRect(Point(bienTrai+10, 4), Point(w-3, 6));
	fflush(stdin);
	string temp;
	stringstream ss;
x1:	userInput(5, bienTrai+11, w-3, temp);
	if(temp.empty())
		goto x1;
	if(temp=="QUIT") return;
x2:	if(IsNotNumber(temp)){
		MessageBox(GetConsoleWindow(), "Ma doc gia la so nguyen", "Thong bao", MB_OK | MB_ICONINFORMATION);
		userInput(5, bienTrai + 11, w-3, temp);
		if(temp.empty())
			goto x1;
		if(temp=="QUIT") return;
		goto x2;
	}
	ss << temp;
	int maDocGia;
	ss >> maDocGia;
	NODEPTR doc_gia = Search(root, maDocGia);
	if(doc_gia!=NULL){//neu co doc gia thi hien thi khung nhap ten sach muon muon
		/*hien ra danh sach cac sach ma doc gia nay dang muon*/
		int soLuongSachDangMuon = doc_gia->info.danhSachMuonTra.TongSoPhieuMuon(0);
		int catchSig;////bat tin hieu khong the muon them sach
		if(soLuongSachDangMuon!=0){
			PhieuMuon danhSachPhieuMuon[soLuongSachDangMuon];
			doc_gia->info.danhSachMuonTra.Traverse(danhSachPhieuMuon, 0);////duyet va luu phieu dang muon vao mang danhSachPhieuMuon
			Print_at(bienTrai + 1, 1, "                   ");
			Print_at(bienTrai + 1, 1, "ESC: tro ve");
			Setcolor(YELLOW);
			Print_at(bienTrai + 2, h-2, "--Chu y--");
			Print_at(bienTrai + 2, h-1, "*TT 0: Sach dang muon");
			Setcolor(WHITE);
			CacSachDocGiaDangMuon(danhSachPhieuMuon, soLuongSachDangMuon, 10, h-3);//catchSig chi bat tin hieu doc gia muon sach qua han
			Print_at(bienTrai + 1, 1, "            ");
		}else{
			Print_at(bienTrai + 1, 1, "Nhan phim bat ky de tro ve");
			Print_at((w-bienTrai)/2 + bienTrai - 8, 10, "(Chua muon sach nao)");
			getch();
			Print_at(bienTrai + 1, 1, "                          ");
		}
    }else{
		MessageBox(GetConsoleWindow(), "Khong tim thay!", "Thong bao", MB_OK | MB_ICONINFORMATION);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CacSachDocGiaDangMuon(const PhieuMuon* danhSachPhieuMuon, int soLuongSachDangMuon, int y1, int y2)
{
	time_t rawtime;
	time(&rawtime);
	struct tm* currTime;
	currTime = localtime(&rawtime);//lay thoi gian he thong
	HighLight(BLACK, LIGHTCYAN);
	Print_at(bienTrai+2, 8, "TT");
	Print_at(bienTrai+5, 8, "Ten Sach");
	Print_at(w-37, 8, "Ma Sach");
	Print_at(w-10, 8, "So ngay");
	Normal(WHITE, BLACK);
	fstream file("danhsachmuontra.txt", ios::out);
	int signal = 1;		///////neu doc gia khong co cuon sach muon qua han signal = 1 nguoc lai signal = 0
	for (int i = 0; i < soLuongSachDangMuon; i++)
	{	
		string _tensach;
		for(int vitri = 0; vitri < khoSach.soLuong; vitri++)
		{
			bool daTimThay = false;
			for(Node_Sach* p = khoSach.dausach[vitri]->danhMucSach.first; p!=NULL; p=p->next)
			{
				if(p->_sach.maSach == danhSachPhieuMuon[i].maSach)     /////so sanh ma sach trong phieu muon va cac ma sach trong tung dau sach thuoc kho sach
				{
					_tensach =  khoSach.dausach[vitri]->tenSach;		   /////gan ten dau sach vao _tensach
					daTimThay = true;							  
					break;
				}
			}
			if(daTimThay)
				break;
		}
		if(_tensach.length() >= 50){	 /////neu ten sach co do dai > 70 thi ta dinh dang lai de in ra khong bi vo khung
			_tensach = _tensach.substr(0, 46) + "...";
			file << danhSachPhieuMuon[i].trangThai << "  " << _tensach;
			for(int space = 0; space < 50 - _tensach.length(); space++)
				file << " ";
		}else{
			file<< danhSachPhieuMuon[i].trangThai << "  " << _tensach;
			for(int space = 0; space < 50 - _tensach.length(); space++)
				file << " ";
		}
		file << danhSachPhieuMuon[i].maSach;
		
		int soNgay = 0;	
		if(currTime->tm_mon+1 - danhSachPhieuMuon[i].ngayMuon.thang == 1)
		{
			soNgay = currTime->tm_mday + (SoNgayCuaThang(danhSachPhieuMuon[i].ngayMuon.thang, currTime->tm_year+1900) - danhSachPhieuMuon[i].ngayMuon.ngay);
		}
		else if(currTime->tm_mon+1 - danhSachPhieuMuon[i].ngayMuon.thang == 0)
		{
			soNgay = currTime->tm_mday - danhSachPhieuMuon[i].ngayMuon.ngay;
		}
		else if(currTime->tm_mon+1 - danhSachPhieuMuon[i].ngayMuon.thang > 1)
		{
			soNgay = currTime->tm_mday + (SoNgayCuaThang(danhSachPhieuMuon[i].ngayMuon.thang, currTime->tm_year+1900) - danhSachPhieuMuon[i].ngayMuon.ngay);
			for(int b = danhSachPhieuMuon[i].ngayMuon.thang + 1; b < currTime->tm_mon+1; b++)
				soNgay += SoNgayCuaThang(b, currTime->tm_year+1900);
		}
		for(int space = 0; space < 27 - danhSachPhieuMuon[i].maSach.length(); space++)
			file << " ";				
		file << soNgay << "\n";	

		if(soNgay>=15)
			signal = 0;
	}
	file.close();
	file.open("danhsachmuontra.txt", ios::in);//lay du lieu trong file voi moi dong tuong ung la mot chuoi ky tu 
	if(!file.is_open()){
		remove("danhsachmuontra.txt");
		return -1;
	}
	string str[soLuongSachDangMuon];
	for(int i = 0; i < soLuongSachDangMuon; i++){
		getline(file, str[i]);
	}
	HopNoiDung(str, soLuongSachDangMuon, bienTrai+2, y1, w-3, y2);//co the chon de tra sach
	file.close();
	remove("danhsachmuontra.txt");
	return signal;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DocGiaMuonSachQuaHan()//duyet cay nhi phan doc gia khong de quy (NRL)
{
	time_t rawtime;
	time(&rawtime);
	struct tm* currTime;
	currTime = localtime(&rawtime);						//lay thoi gian he thong tru cho ngay muon = so ngay ke tu luc muon sach
    int maDocGiaMuonQuaHan[_soLuongDocGia+1] = {0};		//luu tru ma doc gia muon sach qua han
    int soNgayMuonQuaHan[_soLuongDocGia+1]   = {0};		//mac dinh khong co doc gia nao muon sacch qua han -> so ngay muon qua han cua tung doc gia  = 0
    int i = 0;											//chi so cua 2 mang maDocGiaMuonQuaHan va soNgayMuonQuaHan
    
	const int STACKSIZE = _soLuongDocGia+1;
    NODEPTR Stack[STACKSIZE];
    int sp = -1;										//Khoi tao Stack rong
    NODEPTR p=root;
    while (p!=NULL)
    {
    	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    	int soLuongSachDangMuon = p->info.danhSachMuonTra.TongSoPhieuMuon(0);
    	PhieuMuon danhSachPhieuMuon[soLuongSachDangMuon];
		p->info.danhSachMuonTra.Traverse(danhSachPhieuMuon, 0);////duyet va luu phieu dang muon vao mang danhSachPhieuMuon
        int _songayquahan = 0;
        bool quaHan = false;
        for (int i = 0; i < soLuongSachDangMuon; i++)
		{
			int soNgay = 0;
			if(currTime->tm_mon+1 - danhSachPhieuMuon[i].ngayMuon.thang == 1)
			{
				soNgay = currTime->tm_mday + (SoNgayCuaThang(danhSachPhieuMuon[i].ngayMuon.thang, currTime->tm_year+1900) - danhSachPhieuMuon[i].ngayMuon.ngay);
			}
			else if(currTime->tm_mon+1 - danhSachPhieuMuon[i].ngayMuon.thang == 0)
			{
				soNgay = currTime->tm_mday - danhSachPhieuMuon[i].ngayMuon.ngay;
			}
			else if(currTime->tm_mon+1 - danhSachPhieuMuon[i].ngayMuon.thang > 1)
			{
				soNgay = currTime->tm_mday + (SoNgayCuaThang(danhSachPhieuMuon[i].ngayMuon.thang, danhSachPhieuMuon[i].ngayMuon.nam) - danhSachPhieuMuon[i].ngayMuon.ngay);
				for(int b = danhSachPhieuMuon[i].ngayMuon.thang + 1; b < currTime->tm_mon+1; b++)
				{
					soNgay += SoNgayCuaThang(b, currTime->tm_year+1900);
				}
			}
			if(soNgay>=15 && danhSachPhieuMuon[i].trangThai == 0)		//sach dang muon chua tra
			{ 
				_songayquahan += soNgay;
				quaHan = true;
			}
		}
		if(quaHan)
		{
			maDocGiaMuonQuaHan[i] = p->info.maDocGia;
			soNgayMuonQuaHan[i] = _songayquahan;
			i++;		
		}
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (p->right != NULL)
			Stack[++sp] = p->right;
        if (p->left != NULL)
			p=p->left;
        else  if (sp == -1)
			break;
	    else
			p = Stack[sp--];
   }
   
   Insertion_Sort(soNgayMuonQuaHan, maDocGiaMuonQuaHan);//sap xep danh sach doc gia muon sach theo thoi gian qua han giam dan
   
   fstream file("danhsachdocgiaquahan.txt", ios::out | ios::binary);
   int dem = 0;
   for(int _madocgia = _soLuongDocGia; _madocgia >= 0; _madocgia--)
   {
   		if(soNgayMuonQuaHan[_madocgia]==0 || maDocGiaMuonQuaHan[_madocgia]==0)
   			continue;
   			
		NODEPTR doc_gia = Search(root, maDocGiaMuonQuaHan[_madocgia]);//tim kiem doc gia trong cay nhi phan
		
		string _hoten = doc_gia->info.ho + " " + doc_gia->info.ten;
		file << doc_gia->info.maDocGia << "\t\t" << _hoten;
		for(int space = 0; space < 33 - _hoten.length(); space++)
			file << " ";
		file << soNgayMuonQuaHan[_madocgia] << "\n";
		dem++;
   }
   file.close();
   if(dem==0)		//khong co doc gia nao muon sach qua han het
   {
   		Print_at(bienTrai + 1, 1, "Nhan phim bat ky de tro ve");
   		Print_at((w-bienTrai)/2 + bienTrai - 15, (h-3)/2 + 3, "(Khong co doc gia muon sach qua han)");
		getch();
		Print_at(bienTrai + 1, 1, "                          ");
		Print_at((w-bienTrai)/2 + bienTrai - 15, (h-3)/2 + 3, "                                    ");
		remove("danhsachdocgiaquahan.txt");
		return;	
   }
   file.open("danhsachdocgiaquahan.txt", ios::in | ios::binary);

   string str[dem];
   for(int i = 0; i < dem; i++)
   		getline(file, str[i]);

   Print_at(bienTrai + 1, 1, "ESC: Tro ve");
   Print_at(bienTrai+2, 4, "Ma DG\tTen\t\t\t\tSo ngay qua han");
   HopNoiDung(str, dem, bienTrai+2, 6, w-3, h-1);
   file.close();
   remove("danhsachdocgiaquahan.txt");
   Print_at(bienTrai + 1, 1, "           ");
   XoaKhuNoiDung();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TopMuoiSachDuocMuonNhieuNhat()
{
	if(khoSach.soLuong==0)
	{
		Print_at(bienTrai + 1, 1, "Nhan phim bat ky de tro ve");
   		Print_at((w-bienTrai)/2 + bienTrai - 9, (h-3)/2 + 3, "(Kho sach trong)");
		getch();
		Print_at(bienTrai + 1, 1, "                          ");
		return;
	}
	int count = 0;
	RatingStar Rate[khoSach.soLuong] = {0, "rong"}; 			//khoi tao chua co dau sach nao duoc muon = 0 va ten la "rong"
	for(int i = 0; i < khoSach.soLuong; i++)
	{
		int soLuongSachDuocMuon = khoSach.dausach[i]->danhMucSach.TongSoLuongSach(1);//tong so luong sach da duoc muon, trang thai sach = 1
		if(soLuongSachDuocMuon==0)
			continue;
		Rate[count]._soLuotMuon = soLuongSachDuocMuon;				//gan so luot muon vao Rate[i]
		Rate[count]._tenSach    = khoSach.dausach[i]->tenSach;		//gan ten sach vao Rate[i]
		count++;
	}
	
	if(count < 50) //neu so luong it thi insertion sort
	{
		for (int i = 1; i < count; i++)
		{
			int j = i;
			while(Rate[j-1]._soLuotMuon < Rate[j]._soLuotMuon && j > 0)
			{
				Swap(Rate[j], Rate[j-1]);
				j--;
			}
		}
	}else        //nguoc lai thi dung quick sort
		QuickSort(Rate, 0, count-1);
	
	fstream file("top10sach.txt", ios::out);
	if(!file.is_open())	return;
	for(int i = 0; i < count && i < 10; i++)		//chi in ra 10 dau sach dau tien
	{
		file << Rate[i]._tenSach;
		
		for(int space = 0; space < 75 - Rate[i]._tenSach.length(); space++)
			file << " ";
		
		file << Rate[i]._soLuotMuon << "\n";
	}
	file.close();
	file.open("top10sach.txt", ios::in);
	
	string str[count];
	for(int i = 0; i < count; i++)
		getline(file, str[i]);
	
	if(str[0].empty())	//neu chua co sach nao duoc muon thi thong bao va thoat
	{
		Print_at(bienTrai + 1, 1, "Nhan phim bat ky de tro ve");
   		Print_at((w-bienTrai)/2 + bienTrai - 12, (h-3)/2 + 3, ":( Chua co sach duoc muon");
		getch();
		Print_at(bienTrai + 1, 1, "                          ");
		Print_at((w-bienTrai)/2 + bienTrai - 12, (h-3)/2 + 3, "                         ");
		return;
	}
	
	Print_at(bienTrai + 1, 1, "ESC: Tro ve");
	Print_at(bienTrai+2, 5, "Ten Sach");
	Print_at(w-15, 5, "So luot muon");
	HopNoiDung(str, count, bienTrai+2, 7, w-3, h-1);
	Print_at(bienTrai + 1, 1, "           ");
	file.close();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void QuickSort(RatingStar A[], int left, int right){//ham sap xep so luot muon cua cac dau sach giam dan
	int i, j;
	if(left < right)
	{
		i = left + 1;
		j = right;
		do{
			while(A[i]._soLuotMuon >= A[left]._soLuotMuon && i <= right){ i++; }
			while(A[j]._soLuotMuon < A[left]._soLuotMuon){ j--; }
			if(i < j)
				Swap(A[i], A[j]);
		}while(i < j);
		Swap(A[left],A[j]);
		if(left < j - 1){ QuickSort(A, left, j - 1); }
		if(j + 1 < right){ QuickSort(A, j + 1, right); }
	}
}
//================================Cac ham xu ly DauSach va DanhMucSach===========================================
void ThanhPhanDauSach()
{
	Print_at(bienTrai + 1, 5, "ISBN ");
	drawRect(Point(bienTrai + 8 , 4), Point(w-3, 6));
	Print_at(bienTrai + 1, 8, "NXB ");
	drawRect(Point(bienTrai + 8 , 7), Point(w-3, 9));
	Print_at(bienTrai + 1, 11, "S.Trang");
	drawRect(Point(bienTrai + 8 , 10), Point(w-3, 12));
	Print_at(bienTrai + 1, 14, "T.Gia");
	drawRect(Point(bienTrai + 8 , 13), Point(w-3, 15));
	Print_at(bienTrai + 1, 17, "Ten");
	drawRect(Point(bienTrai + 8 , 16), Point(w-3, 18));
	Print_at(bienTrai + 1, 20, "T.Loai");
	drawRect(Point(bienTrai + 8 , 19), Point(w-3, 21));
	Print_at(bienTrai + 1, 23, "S.Luong");
	drawRect(Point(bienTrai + 8 , 22), Point(w-60, 24));
	Setcolor(YELLOW);
	Print_at(bienTrai + 1, 25, "Tuy chon");
	for(int x = 1; x < w-bienTrai-2; x++){
		for(int y = 26; y < h; y++){
			Setbkcolor(LIGHTBLUE);
			Print_at(bienTrai+x, y, ' ');
		}
	}
	Print_at(bienTrai + 15, h-3, "Nhap day du cac thong tin truoc khi chinh sua !");
	Setcolor(WHITE);
	Setbkcolor(BLACK);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ThemDauSach(DauSach* dsach)
{
	ThanhPhanDauSach();//hien thi thong tin dau sach tam thoi
	stringstream ss;
	string temp;
	
m1:	userInput(5, bienTrai + 9, w-3, dsach->ISBN);
	
	if(dsach->ISBN=="QUIT")
		return 0;
	if(dsach->ISBN.empty() || KichThuocISBN(dsach->ISBN) != 13 &&
		KichThuocISBN(dsach->ISBN) != 10)
	{
		MessageBox(GetConsoleWindow(),"Vui long nhap ISBN hop le!\nISBN hop le la chuoi so 10 hoac 13 so",
		"Canh bao", MB_OK | MB_ICONWARNING);
		goto m1;
	}
	if(TonTaiISBN(khoSach, dsach->ISBN))		//kiem tra xem ma isbn da ton tai hay chua neu ton tai thi nhap lai
	{
		MessageBox(GetConsoleWindow(),"Ma ISBN da ton tai",
		"Canh bao", MB_OK | MB_ICONWARNING);
		goto m1;
	}

m2:	userInput(8, bienTrai + 9, w-3, dsach->NXB);

	if(dsach->NXB=="QUIT")
		return 0;
	if(dsach->NXB.empty()) goto m2;
	if(IsNotNumber(dsach->NXB))
	{
		MessageBox(GetConsoleWindow(),"Vui long nhap nam xuat ban hop le!","Canh bao", MB_OK | MB_ICONWARNING);
		goto m2;
	}
		
m3:	userInput(11, bienTrai + 9, w-3, temp);
	
	if(temp=="QUIT")
		return 0;
	if(temp.empty()) goto m3;
	if(IsNotNumber(temp)) {
		MessageBox(GetConsoleWindow(),"Vui long nhap so trang hop le!","Canh bao", MB_OK | MB_ICONWARNING);
		goto m3;
	}
	ss << temp;
	ss >> dsach->soTrang;
	ss.clear();		//xoa du lieu con lai trong ss
	temp.clear();	//xoa du lieu cua temp
	
m4:	userInput(14, bienTrai + 9, w-3, dsach->tacGia);
	
	if(dsach->tacGia=="QUIT")
		return 0;
	if(dsach->tacGia.empty()) goto m4;
	
m5:	userInput(17, bienTrai + 9, w-3, dsach->tenSach);
	
	if(dsach->tenSach=="QUIT")
		return 0;
	if(dsach->tenSach.empty()) goto m5;
	
m6:	userInput(20, bienTrai + 9, w-3, dsach->theLoai);

	if(dsach->theLoai=="QUIT")
		return 0;
	if(dsach->theLoai.empty()) goto m6;
	
m7:	userInput(23, bienTrai + 9, w-60, temp);
	
	if(temp=="QUIT")
		return 0;
	if(temp.empty()) goto m7;
	if(IsNotNumber(temp)) {
		MessageBox(GetConsoleWindow(),"Vui long nhap so luong sach hop le!","Canh bao", MB_OK | MB_ICONWARNING);
		goto m7;
	}
	ss << temp;
	ss >> dsach->soLuongSach;
	return 1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HienThiThongTinDauSach(DauSach* dsach)//dung khi muon chinh sua dau sach da co
{
	Print_at(bienTrai + 2, 7, "ISBN: ");
	Print_at(bienTrai + 12, 7, dsach->ISBN);
	Print_at(bienTrai + 2, 8, "NXB: ");
	Print_at(bienTrai + 12, 8, dsach->NXB);
	Print_at(bienTrai + 2, 9, "So Trang: ");
	Print_at(bienTrai + 12, 9, dsach->soTrang);
	Print_at(bienTrai + 2, 10, "Tac Gia: ");
	Print_at(bienTrai + 12, 10, dsach->tacGia);
	Print_at(bienTrai + 2, 11, "Ten: ");
	Print_at(bienTrai + 12, 11, dsach->tenSach);
	Print_at(bienTrai + 2, 12, "The Loai: ");
	Print_at(bienTrai + 12, 12, dsach->theLoai);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ChinhSuaDauSach(DauSach* dsach)
{
	Print_at(bienTrai+1, 2,"                              ");
	Setcolor(YELLOW);
	Print_at(bienTrai + 1, 25, "Tuy chon");
	Setcolor(WHITE);
	stringstream ss;
	string temp;
	int chon = -1;
	while(chon != 0)
	{
		chon = HopNoiDung(edit_DauSach, 8, bienTrai + 2, 27, w-3, h-1, true);
		if(chon==0) break;
		switch(chon)
		{
			case 1:{
			c1:	userInput(5, bienTrai + 9, w-3, dsach->ISBN);
				if(dsach->ISBN.empty() || KichThuocISBN(dsach->ISBN) != 13 &&
					KichThuocISBN(dsach->ISBN) != 10) {
					MessageBox(GetConsoleWindow(),"Vui long nhap ISBN hop le!\nISBN hop le la chuoi so 10 hoac 13 so",	"Canh bao", MB_OK | MB_ICONWARNING);
					goto c1;
				}
				if(dsach->ISBN.empty()){goto c1;}
				if(TonTaiISBN(khoSach, dsach->ISBN)){//kiem tra neu ma isbn da ton tai thi nhap lai
					MessageBox(GetConsoleWindow(),"Ma ISBN da ton tai",
					"Canh bao", MB_OK | MB_ICONWARNING);
					goto c1;
				}
			}break;
			case 2:{
			c2:	userInput(8, bienTrai + 9, w-3, dsach->NXB);
				if(dsach->NXB.empty()) {goto c2;}
				if(IsNotNumber(dsach->NXB))
				{
					MessageBox(GetConsoleWindow(),"Vui long nhap nam xuat ban hop le!","Canh bao", MB_OK | MB_ICONWARNING);
					goto c2;
				}
			}break;
			case 3:{
				temp = to_string(dsach->soTrang);
			c3:	userInput(11, bienTrai + 9, w-3, temp);
				if(IsNotNumber(temp)) {
					MessageBox(GetConsoleWindow(),"Vui long nhap so trang hop le!",
					"Canh bao", MB_OK | MB_ICONWARNING);
					goto c3;
				}
				if(temp.empty()){chon = 4; goto c3;}
				ss << temp;
				ss >> dsach->soTrang;
				ss.clear();
				temp.clear();
			}break;
			case 4:{
			c4:	userInput(14, bienTrai + 9, w-3, dsach->tacGia);
				if(dsach->tacGia.empty()) {goto c4;}
			}break;
			case 5:{
			c5:	userInput(17, bienTrai + 9, w-3, dsach->tenSach);
				if(dsach->tenSach.empty()) {goto c5;}
			}break;
			case 6:{
			c6:	userInput(20, bienTrai + 9, w-3, dsach->theLoai);
				if(dsach->theLoai.empty()) {goto c6;}
			}break;
			case 7:{
				temp = to_string(dsach->soLuongSach);
			c7:	userInput(23, bienTrai + 9, w-60, temp);
				if(IsNotNumber(temp)) {
					MessageBox(GetConsoleWindow(),"Vui long nhap so luong sach hop le!",
					"Canh bao", MB_OK | MB_ICONWARNING);
					goto c7;
				}
				if(temp.empty()){goto c7;}
				ss << temp;
				ss >> dsach->soLuongSach;
			}break;
			default: break;
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DanhMaSachTuDong(DauSach* dsach)
{
	bookIndex = 1;
	for(int i = 1; i <= dsach->soLuongSach; i++)//so luong sach cua dau sach dsach
	{
		Sach  x;
		x.maSach = dsach->ISBN + "-" + to_string(TakeBookCode());//masah = isbn-matudong
		x.trangThai = 0;						//ban dau tat ca cac quyen sach deu co the cho muon duoc
		x.viTri = i;							//vi tri cua sach la vi tri cua con chay i 
		dsach->danhMucSach.Insert_First(x);		//da them sach x vao dsach
	}
}

void HienThiDauSachTenTangDan()
{
	fstream file("dausach.txt", ios::out);
	if(!file.is_open())
		return;
	if(Empty(khoSach)){
		Print_at(bienTrai + 1, 1, "Nhan phim bat ky de tro ve                   ");
		Print_at((w-bienTrai)/2 + bienTrai - 8, (h-3)/2 + 3, "(Khong co du lieu)");
		getch();
		Print_at(bienTrai + 1, 1, "                                             ");
		return;
	}
	for(int i = 1; i < khoSach.soLuong; i++){
		DauSach* X = khoSach.dausach[i];
		int pos = 0;
		while(khoSach.dausach[pos]->tenSach < X->tenSach)
			pos++;
		for(int j = i; j > pos; j--){
			khoSach.dausach[j] = khoSach.dausach[j-1];
		}
		khoSach.dausach[pos] = X;
	}
	for (int i = 0; i < khoSach.soLuong; i++)
		file<< khoSach.dausach[i]->tenSach << "\n";	//sau nay khi muon in du lieu ra man hinh chi can getline tung dong
		
	file.close();
	file.open("dausach.txt", ios::in);
	string str[khoSach.soLuong];
	for (int i = 0; i < khoSach.soLuong; i++){
		getline(file, str[i]);
	}
again:
	Print_at(bienTrai+2, 4, "Ten Dau Sach");
	int iterator_dau_sach = HopNoiDung(str, khoSach.soLuong, bienTrai+2, 6, w-3, h-1, true);
	XoaKhuNoiDung();
	if(iterator_dau_sach==-1)	//truong hop nguoi dung bam ESC, khong bam ENTER de chon
		return;
	TimThongTinSach(str[iterator_dau_sach]);
	XoaKhuNoiDung();
	Print_at(bienTrai + 1, 1, "ESC: Tro ve | ENTER: Xem thong tin");
	goto again;
	file.close();
	return;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TimThongTinSach(string ten_sach)
{
	string tenSach;
	if(ten_sach == "default")
	{
		drawRect(Point(bienTrai+1, 4), Point(bienTrai+9, 6));
		cout << "Search";
		drawRect(Point(bienTrai+10, 4), Point(w-3, 6));
	x1:	userInput(5, bienTrai+11, w-3, tenSach);
		if(tenSach.empty()) goto x1;
	}else{
		tenSach = ten_sach;
	}
	DauSach* dsach = new DauSach;
	if(!TimDauSach(khoSach, tenSach, dsach))//neu khong tim thay ten sach trong kho sach
	{
		Print_at(bienTrai + 1, 1, "Nhan phim bat ky de tro ve");
		Print_at((w-bienTrai)/2 + bienTrai - 8, (h-3)/2 + 3, "(Khong tim thay du lieu)");
		getch();
		Print_at(bienTrai + 1, 1, "                          ");
		delete dsach;
		return;
	}
	
	HienThiThongTinDauSach(dsach);
	
	int soLuongSachConLai = dsach->danhMucSach.TongSoLuongSach(0);///tong so luong sach voi dieu kien trang thai sach = 0
		
	Print_at(bienTrai + 2, 13, "So luong: ");
	Print_at(bienTrai + 12, 13, dsach->soLuongSach);
	Print_at(bienTrai + 31, 13, "Con lai: ");
	Print_at(bienTrai + 40, 13, soLuongSachConLai);
	if(soLuongSachConLai==0)
	{
		Print_at((w-bienTrai)/2 + bienTrai - 8, (h-3)/2 + 3, "(Khong con sach)");
		getch();
		return;
	}
	
	Sach cacSachConLai[soLuongSachConLai];
	dsach->danhMucSach.Traverse(cacSachConLai, 0);//duyet danh muc sach cua DauSach dsach va luu cac sach co trang thai = 0 vao mang cacSachConLai
	
	fstream file("danhmucsach.txt", ios::out | ios::trunc);
	for(int i = 0; i < soLuongSachConLai; i++)////////////////do insert vao danh muc sach la Insert_first
	{
		file << cacSachConLai[i].maSach;
		for(int space = 0; space <= 30 - cacSachConLai[i].maSach.length(); space++)
			file << " ";
		file << cacSachConLai[i].trangThai << "\n";
	}
	file.close();
	file.open("danhmucsach.txt", ios::in);
	string str[soLuongSachConLai];
	for(int i = 0; i < soLuongSachConLai; i++){
		getline(file, str[i]);
	}
	Print_at(bienTrai + 1, 1, "ESC: Tro ve                       ");
	Print_at(bienTrai+2, 15, "Ma Sach\t\t\tTrang Thai");
	HopNoiDung(str, soLuongSachConLai, bienTrai+2, 17, w-3, h-1);
	Print_at(bienTrai + 1, 1, "                                  ");
	file.close();
	remove("danhmucsach.txt");
	delete dsach;
}
//======================================CAC HAM KHAC================================================================
int getKeyCode()
{
    int ch = getch();
    if (ch == 0 || ch == 224)
        ch = 128 + getch();
    return ch;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void userInput(int y, int start, int limit, string& _userstring)
{
	Moveto(start, y);
	ShowCursor(true);
	const int ARROW_UP    = 128 + 72;
	const int ARROW_DOWN  = 128 + 80;
	const int ARROW_LEFT  = 128 + 75;
	const int ARROW_RIGHT = 128 + 77;
	int ch, x = start;
	int i = 0;//////////////i bien pos de insert va erase
	while((ch = getKeyCode()) != ENTER)
	{
		if(ch != ARROW_UP && ch != ARROW_DOWN)
		{
			if(ch == BACK_SPACE)
			{
				if(x > start)
				{
					string temp = _userstring.substr(i, _userstring.length()-i);//////lay chuoi con tu tai vi tri con tro tro ve sau cua chuoi
					temp = chuanHoaChuoi(temp);					 				//////chuan hoa chuoi xoa cac khoang trang lien ke lien tiep
					_userstring.erase(i-1);			  					  		//////xoa phan tu i-1 trong chuoi input
					_userstring += temp;
					
					ShowCursor(false);
					for(int space = 0; x+space < limit-1; space++)				//////xoa tu vi tri x tro ve sau
						Print_at(x+space, y, ' ');
					if(temp.length()==0)
						Print_at(x-1, y, ' ');
					else
						Print_at(x-1, y, temp);
					Moveto(x-1,y);
					x--;
					i--;
					ShowCursor(true);
				}			
			}
			//Chi in ra khi ky tu nhap vao la so hoac chu . - ,
			else if(ch == 32 || ch >= 97 && ch <= 122 || ch >= 65 && ch <= 90 || ch >= 33 && ch <= 57)
			{
				string temp = _userstring.substr(i, _userstring.length()-i);
				if(x + temp.length() < limit - 1)
				{
					if(ch >= 97 && ch <= 122)
						ch -= 32;
					_userstring.insert(i, reinterpret_cast<const char*>(&ch));
					cout << (char)ch;
					temp = chuanHoaChuoi(temp);
					cout << temp;
					i++;
					x++;
					Moveto(x,y);	
				}
			}else if(ch == ARROW_LEFT){
				if(x > start){
					x--;
					i--;
					Moveto(x, y);
				}
			}else if(ch == ARROW_RIGHT){
				string temp = _userstring.substr(i, _userstring.length());
				temp = chuanHoaChuoi(temp);
				const int fixLen = temp.length() + x;//gioi han di chuyen sang phai
				if(x < fixLen){
					x++;
					i++;
					Moveto(x, y);
				}
			}
		}
	}
	_userstring = chuanHoaChuoi(_userstring);
	ShowCursor(false);
	XoaKhuNoiDung(start, y, limit-1, y);
	Moveto(start, y);
	cout << _userstring;	
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LoginSession()
{
	int m = 0, j = 110, k = 0, n = 110;
	ShowCursor(false);
	while(m < bienTrai+10 && j > bienTrai && k < bienTrai && n > bienTrai)
	{
		Print_at(m, 7, "DANG NHAP");
		Print_at(j, 10, "Username: ");
		Print_at(k, 12, "Password: ");
		Print_at(n, 16, "Vui long dang nhap!");
		Sleep(5);
		Print_at(m, 7, "                     ");
		Print_at(j, 10, "                     ");
		Print_at(k, 12,"                     ");
		Print_at(n, 16,"                     ");
		m++; j--; k++; n--;
	}
again:
	ShowCursor(true);
	Print_at(bienTrai+10, 7, "DANG NHAP");
	Print_at(bienTrai, 10, "Username: ");
	Print_at(bienTrai, 12, "Password: ");
	Print_at(bienTrai, 16, "Vui long dang nhap!");
	string userName;
	string passWord;
	Moveto(bienTrai+10, 10);
	getline(cin, userName);
	Moveto(bienTrai+10, 12);
	char c;
	int i = 0;
	while(c!=ENTER)
	{
		c = getKeyCode();
		if(c == BACK_SPACE && i > 0){
			i--;
			Print_at(bienTrai + 10 + i, 12, ' ');
			Moveto(bienTrai + 10 + i, 12);
			passWord.pop_back();
		}
		if((int)c >= 48 && (int)c <= 122){
			cout << "*";
			passWord.push_back(c);
			i++;
		}
	}
	if(userName != USERNAME || strcmp(PASSWORD, passWord.c_str())!=0)
	{
		Setcolor(LIGHTGREEN);
		Print_at(bienTrai, 14, "Ten hoac mat khau khong dung, Thu lai!");
		Setcolor(WHITE);
		getch();
		XoaKhuNoiDung(bienTrai, 7, bienTrai+40, 16);
		c = '0';
		goto again;
	}
	XoaKhuNoiDung(bienTrai, 7, bienTrai+40, 16);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Insertion_Sort(int arr1[], int arr2[])//sap xep tren hai mang arr1 va arr2 cung mot luc
{
	for(int i = 1; i <= _soLuongDocGia; i++){
		int X = arr1[i];
		int Y = arr2[i];
		int pos = 0;
		while(arr1[pos] < X) //chi dua vao dieu kien sap xep cua mang arr1
			pos++;
		for(int j = i; j > pos; j--){
			arr1[j] = arr1[j-1];
			arr2[j] = arr2[j-1];
		}
		arr1[pos] = X;
		arr2[pos] = Y;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GhiFileDocGia(const char* fileName, Doc_Gia& Object)//dung macro de bien dich neu dieu kien thoa man
{
	ofstream file;
	file.open(fileName, ios::binary | ios::app);
	
	file.write(reinterpret_cast<char*>(&Object.maDocGia), sizeof(Object.maDocGia));
	
	char buffer1[100];
	strcpy(buffer1, Object.ho.c_str());
	file.write(buffer1, sizeof(buffer1));
	
	char buffer2[100];
	strcpy(buffer2, Object.ten.c_str());
	file.write(buffer2, sizeof(buffer2));
	
	char buffer3[100];
	strcpy(buffer3, Object.gioiTinh.c_str());
	file.write(buffer3, sizeof(buffer3));
	
	file.write(reinterpret_cast<char*>(&Object.trangThai), sizeof(Object.trangThai));
	
	file.close();
}

void GhiFilePhieuMuon(const char* fileName, PhieuMuon& Object)//du lieu phieu muon cho moi doc gia
{
	ofstream file;
	file.open(fileName, ios::binary | ios::app);
	
	char buffer1[100];
	strcpy(buffer1, Object.maSach.c_str());
	file.write(buffer1, sizeof(buffer1));
	
	file.write(reinterpret_cast<char*>(&Object.ngayMuon), sizeof(Object.ngayMuon));
	
	file.write(reinterpret_cast<char*>(&Object.ngayTra), sizeof(Object.ngayTra));
	
	file.write(reinterpret_cast<char*>(&Object.trangThai), sizeof(Object.trangThai));
	file.close();
}

void GhiFileDauSach(const char* fileName, DauSach* Object)
{
	ofstream file;
	file.open(fileName, ios::binary | ios::app);
	
	char buffer1[100];
	strcpy(buffer1, Object->ISBN.c_str());
	file.write(buffer1, sizeof(buffer1));
		
	char buffer2[100];
	strcpy(buffer2, Object->tenSach.c_str());
	file.write(buffer2, sizeof(buffer2));
	
	file.write(reinterpret_cast<char*>(&Object->soTrang), sizeof(Object->soTrang));

	char buffer3[100];
	strcpy(buffer3, Object->tacGia.c_str());
	file.write(buffer3, sizeof(buffer3));
	
	char buffer4[100];
	strcpy(buffer4, Object->NXB.c_str());
	file.write(buffer4, sizeof(buffer4));

	char buffer5[100];
	strcpy(buffer5, Object->theLoai.c_str());
	file.write(buffer5, sizeof(buffer5));
	
	file.write(reinterpret_cast<char*>(&Object->soLuongSach), sizeof(Object->soLuongSach));
	
	file.close();
}

void GhiFileDanhMucSach(const char* fileName, DauSach* Object)
{
	ofstream file;
	file.open(fileName, ios::binary | ios::trunc);
	for(Node_Sach* q = Object->danhMucSach.first; q != NULL; q = q->next){
		char buffer1[100];
		strcpy(buffer1, q->_sach.maSach.c_str());
		file.write(buffer1, sizeof(buffer1));
		
		file.write(reinterpret_cast<char*>(&q->_sach.trangThai), sizeof(q->_sach.trangThai));//luu tru danh muc sach voi moi dau sach khac nhau se co danh muc tuong ung
		file.write(reinterpret_cast<char*>(&q->_sach.viTri), sizeof(q->_sach.viTri));//luu tru danh muc sach voi moi dau sach khac nhau se co danh muc tuong ung

	}
	file.close();
}

void DocDuLieuDocGia(const char* fileName)
{
	ifstream file;
	file.open(fileName, ios::binary);
	if(!file.is_open()) return;
	while(!file.eof()){
		Doc_Gia docgia;
		
		file.read(reinterpret_cast<char*>(&docgia.maDocGia), sizeof(docgia.maDocGia));
		
		char buffer1[100];
		file.read(buffer1, sizeof(buffer1));
		docgia.ho = buffer1;
			
		char buffer2[100];
		file.read(buffer2, sizeof(buffer2));
		docgia.ten = buffer2;
			
		char buffer3[100];
		file.read(buffer3, sizeof(buffer3));
		docgia.gioiTinh = buffer3;
		
		file.read(reinterpret_cast<char*>(&docgia.trangThai), sizeof(docgia.trangThai));
			
		if(!file.eof()){
			const string fileName = "data/" + to_string(docgia.maDocGia) + ".dat";
			DocDuLieuPhieuMuon(fileName.c_str(), docgia);
			Insert_node(root, docgia.maDocGia, docgia);	//them doc gia vao cay nhi phan
			_soLuongDocGia++;		//tang so doc gia len 1 sau moi lan doc duoc 1 doc gia tu file
		}
	}
	readerIndex = _soLuongDocGia;
	file.close();
}

void DocDuLieuPhieuMuon(const char* fileName, Doc_Gia& docgia)//ten file bat dau voi cac chu so dai dien cho ma so doc gia vd: 543.dat
{
	ifstream file;
	file.open(fileName, ios::binary);
	if(!file.is_open()) return;
	while(!file.eof()){
		PhieuMuon pm;
		
		char buffer1[100];
		file.read(buffer1, sizeof(buffer1));
		pm.maSach = buffer1;
		
		file.read(reinterpret_cast<char*>(&pm.ngayMuon), sizeof(pm.ngayMuon));
		
		file.read(reinterpret_cast<char*>(&pm.ngayTra), sizeof(pm.ngayTra));
		
		file.read(reinterpret_cast<char*>(&pm.trangThai), sizeof(pm.trangThai));
		if(!file.eof()){
			docgia.danhSachMuonTra.Insert_First(pm);
		}
	}
	file.close();
}

void DocDuLieuDauSach(const char* fileName)
{
	ifstream file;
	file.open(fileName, ios::binary);
	if(!file.is_open()) return;
	while(!file.eof()){
		DauSach* dausach = new DauSach;
		char buffer1[100];
		file.read(buffer1, sizeof(buffer1));
		dausach->ISBN = buffer1;
		
		char buffer2[100];
		file.read(buffer2, sizeof(buffer2));
		dausach->tenSach = buffer2;
		
		file.read(reinterpret_cast<char*>(&dausach->soTrang), sizeof(dausach->soTrang));
		
		char buffer3[100];
		file.read(buffer3, sizeof(buffer3));
		dausach->tacGia = buffer3;
		
		char buffer4[100];
		file.read(buffer4, sizeof(buffer4));
		dausach->NXB = buffer4;
			
		char buffer5[100];
		file.read(buffer5, sizeof(buffer5));
		dausach->theLoai = buffer5;
		
		file.read(reinterpret_cast<char*>(&dausach->soLuongSach), sizeof(dausach->soLuongSach));
		if(!file.eof()){	
			const string tenFile = "data/" + dausach->ISBN + ".dat";
			DocDuLieuDanhMucSach(tenFile.c_str(), dausach);
			ThemDauSach(khoSach, dausach);//them dausach vao Kho Sach
		}
	}
	file.close();
}

void DocDuLieuDanhMucSach(const char* fileName, DauSach* dausach)
{
	ifstream file;
	file.open(fileName, ios::binary);
	if(!file.is_open()) return;
	while(!file.eof()){
		Sach _sach;
		
		char buffer1[100];
		file.read(buffer1, sizeof(buffer1));
		_sach.maSach = buffer1;
		
		file.read(reinterpret_cast<char*>(&_sach.trangThai), sizeof(_sach.trangThai));
		file.read(reinterpret_cast<char*>(&_sach.viTri), sizeof(_sach.viTri));
		if(!file.eof()){
			dausach->danhMucSach.Insert_First(_sach);
		}
	}
	file.close();
}

void CapNhatDuLieuDocGia(NODEPTR p)//cap nhat lai du lieu doc gia (LNR)
{
	if(p != NULL){
		CapNhatDuLieuDocGia(p->left);
		GhiFileDocGia("data/reader.dat", p->info);
		CapNhatDuLieuDocGia(p->right);
	}
}

void CapNhatDanhSachPhieuMuon(NODEPTR p)//cap nhat lai du lieu phieu muon (LRN)
{
	if(p != NULL){
		CapNhatDanhSachPhieuMuon(p->left);
		CapNhatDanhSachPhieuMuon(p->right);
		const string fileName = "data/" + to_string(p->info.maDocGia) + ".dat";//lay ten file
		remove(fileName.c_str());//xoa file
		for(Node_Muon_Tra* q = p->info.danhSachMuonTra.first; q != NULL; q = q->next){
			GhiFilePhieuMuon(fileName.c_str(), q->_phieuMuon);//ghi file moi
		}
	}
}

void CapNhatDanhMucSach(List& khosach)
{
	for(int i = 0; i < khosach.soLuong; i++){
		const string fileName = "data/" + khosach.dausach[i]->ISBN + ".dat";
		GhiFileDanhMucSach(fileName.c_str(), khosach.dausach[i]);	
	}
}
/*Thu hoi bo nho o day*/
void GiaiPhongDocGia_DanhSachMuonTra(NODEPTR p){
	if(p!=NULL){
		GiaiPhongDocGia_DanhSachMuonTra(p->left);
		GiaiPhongDocGia_DanhSachMuonTra(p->right);
		p->info.danhSachMuonTra.Clearlist();//giai phong danh sach muon tra cua doc gia trong khi duyet cay nhi phan
		delete p;							//giai phong vung nho ma p dang tro den
	}
}

void GiaiPhongDanhMucSach(List& khosach){
	for(int i = 0; i < khosach.soLuong; i++){
		khosach.dausach[i]->danhMucSach.Clearlist();//giai phong bo nho cua danh muc sach truoc
		delete khosach.dausach[i];		  			//giai phong bo nho dausach da cap phat o module DocDuLieuDauSach line 1846
	}
}
