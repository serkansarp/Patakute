#pragma once
#include <iostream>
#include <clocale>	//	Türkçe
using namespace std;

//	Define Seri 
#define maca (0)
#define sinek (1)
#define karo (2)
#define kupa (3)

//	Define As veya Özel Kartlar
#define as (1)
#define bacak (11)
#define kiz (12)
#define papaz (13)

//	Kart Sýnýfý
class Kart {
private:
	int seri;
	int deger;
public:
	Kart(int seri = maca, int deger = 2) :seri(seri), deger(deger) {}	// Parametresiz gelen istekler Maça 2 dönecek
	// Getter Prototipleri (Encapsulation gereði)
	int getSeri();
	int getDeger();

	// Kart Yazdýrma (Maça As gibi) Prototip
	void yazdir()const;
};

//	Deste Sýnýfý
class Deste {
private:
	int top;
	Kart kartlar[52];	//	Kart sýnýfýndan 52 Kart'lýk boþ deste
public:

	// Deste Constructor Prototip
	Deste();

	// Deste Yazdýrma Prototip
	void desteYazdir()const;

	// kartlar Dizisine Göre Kart Yazdýr Prototip
	void kartYazdir(int)const;

	// Getter Prototipler
	int getKartDeger(int);
	int getKartSeri(int);

	//	Desteyi Karma Prototip
	void karistir();
	void karistir(int);	// Parametreli Overload

	Kart getir() {
		return kartlar[top++];	//	return kartlar[top]; top++; yapýlabilirdi, kýsaltýlmýþ postfix kullanýldý
	}

};

