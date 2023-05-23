#pragma once
#include <iostream>
#include <clocale>	//	T�rk�e
using namespace std;

//	Define Seri 
#define maca (0)
#define sinek (1)
#define karo (2)
#define kupa (3)

//	Define As veya �zel Kartlar
#define as (1)
#define bacak (11)
#define kiz (12)
#define papaz (13)

//	Kart S�n�f�
class Kart {
private:
	int seri;
	int deger;
public:
	Kart(int seri = maca, int deger = 2) :seri(seri), deger(deger) {}	// Parametresiz gelen istekler Ma�a 2 d�necek
	// Getter Prototipleri (Encapsulation gere�i)
	int getSeri();
	int getDeger();

	// Kart Yazd�rma (Ma�a As gibi) Prototip
	void yazdir()const;
};

//	Deste S�n�f�
class Deste {
private:
	int top;
	Kart kartlar[52];	//	Kart s�n�f�ndan 52 Kart'l�k bo� deste
public:

	// Deste Constructor Prototip
	Deste();

	// Deste Yazd�rma Prototip
	void desteYazdir()const;

	// kartlar Dizisine G�re Kart Yazd�r Prototip
	void kartYazdir(int)const;

	// Getter Prototipler
	int getKartDeger(int);
	int getKartSeri(int);

	//	Desteyi Karma Prototip
	void karistir();
	void karistir(int);	// Parametreli Overload

	Kart getir() {
		return kartlar[top++];	//	return kartlar[top]; top++; yap�labilirdi, k�salt�lm�� postfix kullan�ld�
	}

};

