#ifndef DRAW_H
#define DRAW_H
#include <iostream>
#include <ctime>
#include "consolelib.h"
#include "check.h"
using std::cout;
void XoaKhuNoiDung(int x, int y, int x1, int y1);
///strcut Point de su chi dinh mot diem bat ky tren consoles
struct Point{
	int x,y;
	Point(int i, int j):x(i), y(j){}
};
void drawLine(Point start, int lenght, short direct, int symbolCode)
{
	if(direct==1){
		for (int i = start.x; i <= lenght; i++)
			Print_at(i, start.y, (char)symbolCode);
	}else if(direct==2){
		for (int j = start.y; j <= lenght; j++)
			Print_at(start.x, j, (char)symbolCode);
	}
}
/*
	@param start : chi dinh diem bat ky ky tren console
	@param lenght: chieu dai cua duong thang muon ve
	@param direct: huong cua duong thang (!: ngang, 2: doc)
	@param symbolcode: ma cua bieu tuong can in ra
*/


void drawRect(Point topLeft, Point bottomRight)
{
	Print_at(topLeft.x, topLeft.y, (char)218);
	Print_at(bottomRight.x, topLeft.y, (char)191);
	Print_at(bottomRight.x, bottomRight.y, (char)217);
	Print_at(topLeft.x, bottomRight.y, (char)192);
	drawLine(Point(topLeft.x+1, topLeft.y), bottomRight.x-1, 1, 196);
	drawLine(Point(topLeft.x+1, bottomRight.y), bottomRight.x-1, 1, 196);
	drawLine(Point(topLeft.x, topLeft.y+1), bottomRight.y-1, 2, 179);
	drawLine(Point(bottomRight.x, topLeft.y+1), bottomRight.y-1, 2, 179);
	Moveto(topLeft.x+1, (bottomRight.y-topLeft.y)/2 + topLeft.y);
}
/*
	@param topLeft: goc tren ben trai
	@param bottomRight: goc duoi ben phai
	1: ngang
	2: doc
*/
int w,h, bienTrai = 41;
void DrawInterface(){
	GetWindowSize(w, h);//lay kich thuoc cua so console
	h = h-1;
	HighLight(LIGHTGREEN, BLACK);
	Print_at(10, 1, "QUAN LY THU VIEN");
	Print_at(2, 2, "2018");
	Print_at(6, 2, " - De tai so 5");
	Normal(WHITE, BLACK);
	Print_at(1, 0, (char)201);
	Print_at(1, 3,(char)204);
	Print_at(1, h,(char)200);
	for (int bar = 2; bar <= w - 2; bar++){
		if (bar==bienTrai){
			Print_at(bar, 0, (char)203);//ve thanh ngang ben phai cot doc
			Print_at(bar, 3, (char)206);//ve thanh ngang ben trai cot doc
		}else if (bar==w-2){
			Print_at(bar, 0, (char)187);
			Print_at(bar, 3, (char)185);
		}else{
			Print_at(bar, 0, (char)205);
			Print_at(bar, 3, (char)205);//y = 3 thi ver = y + 1
		}
	}
	
	
	
	for (int ver = 0; ver < h; ver++){//ve thanh doc xuong ben trai
		if(ver==0 || ver==3)
			continue;
		Print_at(1, ver, (char)186);
		Print_at(bienTrai, ver, (char)186);
		Print_at(w-2, ver, (char)186);
	}
	
	
	for (int bar = 2; bar <= w - 2; bar++)//ve thanh ngang duoi cung
	{
		if (bar==bienTrai){
			Print_at(bar, h, (char)202);
		}else if (bar==w-2){
			Print_at(bar, h, (char)188);
		}
		else{
			Print_at(bar, h, (char)205);
		}
	}
	
		
}

///hien thi noi dung trong hinh chu nhat
int HopNoiDung(std::string noiDung[], int so_item, int x0, int y0, int x1, int y1, bool take_iterator = false){
	drawRect(Point(x0-1,y0-1), Point(x1, y1));
	const int bienTren = y0-1;
	const int bienDuoi = y1;
	int dong = y0;	int cot = x0;
	int i = 0;		int phanTu = 0;
	int trove = y1-y0-1;
	int flag = 0;
again:
	XoaKhuNoiDung(x0,y0,x1-1,y1-1);
	int demSoDong = 0;
	for (i ; i < so_item ; i++)
	{
		if(dong==bienDuoi)
	    	break;
	    Print_at(cot, dong, noiDung[i]);
	    dong += 1;
	    demSoDong++;//so dong duoc hien thi
	}
		
	HighLight(BLACK, WHITE);
	
	if(flag==0)
		dong -= demSoDong;
	else
		dong = bienDuoi - 1;//hight light dong dau tien tu duoi bien tro len
		
	Print_at(cot, dong, noiDung[phanTu]);
	Normal(WHITE, BLACK);
	Print_at(x1, dong, (char)219);
	while(true){
	  char kytu = getch();
	  switch (kytu) 
	  {
	    case KEY_UP:if (phanTu + 1	> 1){
	    				Normal(WHITE, BLACK);
		  		       	Print_at(x1, dong, (char)179);
		              	Print_at(cot, dong, noiDung[phanTu]);
		              	dong -= 1;
		              	phanTu--;
		              	
		              	if(dong==bienTren)
		              	{
		              		dong = y0;
							cot = x0;
							i = phanTu - trove;//tro ve trang truoc do "trove" dong
							flag = 1;
		              		goto again;
						}
						
		              	HighLight(BLACK, WHITE);
		              	Print_at(cot, dong, noiDung[phanTu]);
		              	Normal(WHITE, BLACK);
		            	Print_at(x1, dong, (char)219);
	  			 	}break;
	  	case KEY_DOWN:if (phanTu + 1 < so_item){
	  					Normal(WHITE, BLACK);
		  		        Print_at(x1, dong, (char)179);
		              	Print_at(cot, dong, noiDung[phanTu]);
		              	dong += 1;
		              	phanTu++;
		              	
		              	if(dong==bienDuoi)
		              	{
							i = phanTu;
							dong = y0;
							cot = x0;
							flag = 0;
		              		goto again;
						}
						
						HighLight(BLACK, WHITE);
			            Print_at(cot, dong, noiDung[phanTu]);
			            Normal(WHITE, BLACK);
			            Print_at(x1, dong, (char)219);
	  				}break;
	  	case ENTER:{
	  				if(take_iterator){	//neu muon lay vi tri hien tai cua thanh hightlight 
	  					return phanTu;
					}
		  		}break;
	    }
	     if(kytu==KEY_ESC)
			break;
	}
	return -1;
}
/*
	@param noiDung: mot mang chuoi ky tu luu tru can xuat ra man hinh
	@param so_item: so luong item cua @param noiDung
	@param x0, y0, x1, y1: Chi dinh vi tri xuat noi dung
*/
void XoaKhuNoiDung(int x = bienTrai+1, int y = 4, int x1 = w-3, int y1 = h-1){
	ShowCursor(false);
	int i = x;
	while (i <= x1){
			if(i+20 > x1){
				if(i+5 > x1){
					for (int j = y; j <= y1; j++){
						Print_at(i, j, " ");//1 khoang trong
					}
					i++;
				}else{
					for (int j = y; j <= y1; j++){
						Print_at(i, j, "     ");//5 khoang trong
					}
					i += 5;
				}
			}else{
				for (int j = y; j <= y1; j++){
					Print_at(i, j, "                    ");//20 khoang trong
				}
				i += 20;
			}
		
	}
}
/*x = bienTrai+1, y = 4 
-------------------------------------------------------------------
x+20<w-3|x+20<w-3|x+20<w-3|x+20<w-3|x+20<w-3|x+20<w-3|x+20<w-3| | |
		|		 |		  |		   |		|		 |		  | | |
		|		 |		  |		   |		|		 |		  | | |
		|		 |		  |		   |		|		 |		  | | |
		|		 |		  |		   |		|		 |		  | | |
		|		 |		  |        |		|		 |		  | | |
		|		 |		  |		   |		|	 	 |		  | | |
-------------------------------------------------------------------
													x = w-3, y = h-1
*/
#endif
