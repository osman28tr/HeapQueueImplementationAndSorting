// 202804012.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdlib.h>
using namespace std;

struct Dugum {
	int veri; 
	Dugum* sonraki; 
};
struct Kuyruk {
	Dugum* bas; 
	Dugum* son; 
	int sayac = 0;
	void olustur(); 
	void kapat(); 
	void ekle(int veri); 
	int cikar(); 
	bool bosMu(); 
};
struct Yigin {
	Kuyruk k1, k2; 

	int curr_size;
	void olustur(); 
	void kapat(); 
	void ekle(int veri); 
	int cikar(); 
	bool bosMu(); 
	int tepe(); 
	void yazdir(); 
	void yiginCikar(Yigin* s);
	void siraliEkle(Yigin* s, int x);
};

int main()
{
	Yigin y;
	Yigin* y1;


	y.olustur();
	y.ekle(3);
	y.ekle(1);
	y.ekle(7);
	y.ekle(4);
	y.ekle(8);
	
	cout << "Yigina eklenen elemanlar: 3,1,7,4,8" << endl;

	cout << "Orjinal Yigin: " << endl;
	y.yazdir();


	y.ekle(3);
	y.ekle(1);
	y.ekle(7);
	y.ekle(4);
	y.ekle(8);
	y1 = &y;
	cout << "---yiginCikar fonksiyon cagrisi---" << endl;
	y.yiginCikar(y1);
	cout << "Sirali Yigin: " << endl;
	y.yazdir();
	y.kapat();

	
	return 0;
}
void Yigin::olustur() {
	k1.bas = NULL, k2.bas = NULL;
	k1.son = NULL, k2.son = NULL;
	curr_size = 0;
}
void Yigin::yazdir() {
	while (!bosMu())
	{
		cout << tepe() << endl;
		cikar();
	}
}
void Yigin::siraliEkle(Yigin* s, int x) {
	if (s->bosMu() || x > s->tepe())
	{
		s->ekle(x);
		return;
	}

	int temp = s->cikar();
	siraliEkle(s, x);

	s->ekle(temp);
	
}
void Yigin::yiginCikar(Yigin* s) {
	if (!s->bosMu()) {
		int x = s->cikar();
		yiginCikar(s);
		siraliEkle(s, x);
	}
}
void Yigin::kapat() {
	delete k1.bas, k2.bas, k1.son, k2.son;
}
int Yigin::cikar() {
	if (k1.bosMu())
		return 0;
	curr_size--;
	return k1.cikar();
}
void Yigin::ekle(int veri) {
	curr_size++;

	k2.ekle(veri);
	while (!k1.bosMu())
	{
		k2.ekle(k1.bas->veri);
		k1.cikar();
	}

	Kuyruk k = k1;
	k1 = k2;
	k2 = k;
}
bool Yigin::bosMu() {
	if (curr_size == 0)
		return true;
	else
		return false;
}
int Yigin::tepe() {
	if (k1.bosMu())
		return -1;
	return k1.bas->veri;
}


void Kuyruk::olustur() {
	bas = NULL;
	son = NULL;
}
void Kuyruk::kapat() {
	Dugum* p;
	while (bas)
	{
		p = bas;
		bas = bas->sonraki;
		delete p;
	}
}
void Kuyruk::ekle(int veri)
{
	Dugum* yeniDugum = new Dugum();
	yeniDugum->veri = veri;
	yeniDugum->sonraki = NULL;
	if (bas == NULL)
	{
		bas = yeniDugum;
		son = bas;
	}
	else {
		son->sonraki = yeniDugum;
		son = yeniDugum;
	}
	sayac++;
}
int Kuyruk::cikar() {
	Dugum* ustDugum;
	int gecici;
	ustDugum = bas;
	bas = bas->sonraki;
	gecici = ustDugum->veri;
	delete ustDugum;
	return gecici;
}
bool Kuyruk::bosMu() {
	return bas == NULL;
}