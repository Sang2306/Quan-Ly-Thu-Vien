#ifndef MENUDONG_H
#define MENUDONG_H
#include <iostream>
#include <conio.h>
#include <cstring>
#include "consolelib.h"
#include "draw.h"
using namespace std;
const int khoangCachHaiDong = 2;
int MenuChinh(string menu[], int so_item, int toaDoX, int toaDoY){
	int dong = toaDoY;
	int cot = toaDoX;
	for (int i=0; i < so_item ; i++)
	{
	    Print_at(cot, dong, menu[i]);
	    dong = dong + khoangCachHaiDong;
	}
	int phanTu = 0;
	HighLight(BLACK, WHITE);
	dong = dong - (so_item*khoangCachHaiDong);
	Print_at(cot, dong, menu[phanTu]);
	Normal(WHITE, BLACK);
	Print_at(bienTrai, dong, (char)219);
	while(true){
	  char kytu = getch();
	  switch (kytu) 
	  {
	    case KEY_UP:if (phanTu + 1	> 1){
	    				Normal(WHITE, BLACK);
		  		       	Print_at(bienTrai, dong, (char)186);
		              	Print_at(cot, dong, menu[phanTu]);
		              	dong = dong - khoangCachHaiDong;
		              	phanTu--;
		              	HighLight(BLACK, WHITE);
		              	Print_at(cot, dong, menu[phanTu]);
		              	Normal(WHITE, BLACK);
		            	Print_at(bienTrai, dong, (char)219);
	  			 	}break;
	  	case KEY_DOWN:if (phanTu + 1 < so_item){
	  					Normal(WHITE, BLACK);
		  		        Print_at(bienTrai, dong, (char)186);
		              	Print_at(cot, dong, menu[phanTu]);
		              	dong = dong + khoangCachHaiDong;
		              	phanTu++;
		              	HighLight(BLACK, WHITE);
		              	Print_at(cot, dong, menu[phanTu]);
		              	Normal(WHITE, BLACK);
		              	Print_at(bienTrai, dong, (char)219);
	  				}break;
	  	case ENTER:	{
	  				Normal(WHITE, BLACK);
		  		    Print_at(bienTrai, dong, (char)186);
					return phanTu + 1;}
	  }
	}
}
///create main menu
string main_Menu[10] = {	">Nhap doc gia                        +",
			            	">Danh sach doc gia                   +",
			                ">Nhap dau sach                        ",
			                ">Danh sach cac dau sach               ",
			                ">Tim thong tin sach                   ",
			                ">Muon + Tra sach                     +",
							">Hien thi cac sach 1 doc gia dang muon", 
							">Hien thi doc gia muon sach qua han   ",
							">10 sach duoc muon nhieu nhat         ",
							">Luu va thoat                         "
};
///create submenu
string edit_DauSach[8] = {
	">Xong                 ",
	">Toi muon sua ISBN    ",
	">Toi muon sua NXB     ",
	">Toi muon sua S.Trang ",
	">Toi muon sua T.Gia   ",
	">Toi muon sua Ten     ",
	">Toi muon sua T.Loai  ",
	">Toi muon sua S.Luong "
};
string edit_Doc_Gia[5] = {
	">Xong                ",
	">Toi muon sua Ho     ",
	">Toi muon sua Ten    ",
	">Toi muon sua G.Tinh ",
	">Toi muon sua T.Thai ",
};
string tuyChon_HienThi[3] = {
	">Ho ten tang dan     ",
	">Ma doc gia tang dan ",
	"<Tro ve              "
};
string nhapdocgia[4] = {
	">Them doc gia       ",
	">Xoa doc gia        ",
	">Hieu chinh doc gia ",
	"<Tro ve             "
};
string muon_sach[3] = {
	">Muon sach          ",
	">Tra sach           ",
	"<Tro ve             "
};
#endif
