#ifndef CHECK_H
#define CHECK_H
#include <iostream>
#include <cstring>
#include <conio.h>
#define USERNAME "admin"
#define PASSWORD "12345"
bool IsNotNumber(std::string testStr){
	for (int i = 0; i < testStr.length(); i++){
		if(!isdigit(testStr[i]) || testStr[i] == ' ')
			return true;
	}
	return false;
}

int KichThuocISBN(std::string ISBN){
	int size = 0;
	for(int i = 0; i < ISBN.length(); i++){
		if(isdigit(ISBN[i]))
			size++;
		else
			return 0;
	}
	return size;
}
std::string chuanHoaChuoi(std::string temp){
	int changed_last = temp.length();
	while(temp[changed_last]==' ')
		temp.erase(changed_last--, 1);
	int changed_first = 0;
	while(temp[changed_first]==' ')
		changed_first++;
	temp = temp.substr(changed_first, temp.length());
	for(int i = changed_first; i < temp.length(); i++)
	{
		if(temp[i]==' ' && temp[i+1]==' ')
		{
			temp.erase(i, 1);
			i = 0;
		}
	}
	return temp;
}
template<typename _Tp>
void Swap(_Tp& a, _Tp& b){
	_Tp temp;
	temp = a;
	a = b;
	b = temp;
}
#endif
