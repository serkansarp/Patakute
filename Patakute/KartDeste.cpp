#include "KartDeste.h"

// Kart Getter Tan�mlar�
int Kart::getSeri() { return seri; }
int Kart::getDeger() { return deger; }

// Kart Yazd�rma (Ma�a As gibi) Tan�m
void Kart::yazdir()const {	//	Seri ve de�erlerin d�zg�n yazd�r�labilmesi i�in Switch-Case kullan�ld�
	switch (seri) {
	case maca: { cout << "Ma�a"; break; }
	case sinek: { cout << "Sinek"; break; }
	case karo: { cout << "Karo"; break; }
	case kupa: { cout << "Kupa"; break; }
	}	cout << " ";
	switch (deger) {
	case as: { cout << "As"; break; }
	case bacak: { cout << "Bacak"; break; }
	case kiz: { cout << "K�z"; break; }
	case papaz: { cout << "Papaz"; break; }
	default: {cout << deger; }
	}	cout << endl;
}

// Deste Constructor Tan�m
Deste::Deste() {			//	Deste kurucusu ile burada d�ng�yle bo� kartlar�n �zerine isimleri yaz�ld�
	top = 0;
	for (int i = 0; i < 52; i++) {
		kartlar[i] = Kart(i / 13, i % 13 + 1);
	}
}

// Deste Yazd�rma Tan�m
void Deste::desteYazdir()const {	//	�stenildi�inde d�ng� ile deste yazd�r�labiliyor (Kart::yazd�r kullan�l�yor)
	for (int i = 0; i < 52; i++) {
		kartlar[i].yazdir();
	}
}

// kartlar Dizisine G�re Kart Yazd�r Tan�m
void Deste::kartYazdir(int k = 0)const {
	kartlar[k].Kart::yazdir();
}

// Getter Prototipler
int Deste::getKartDeger(int k = 0) {
	return kartlar[k].Kart::getDeger();
}

int Deste::getKartSeri(int k = 0) {
	return kartlar[k].Kart::getSeri();
}

//	Deste Karma Parametresiz Tan�m
void Deste::karistir() {				//	Karde�im Volkan SARP'�n d�nyada ya�ad��� g�n say�s� kadar kart birbiriyle
	for (int i = 0; i < 15180; i++) {	//	yer de�i�ir. Y�ksek bir de�er gibi g�r�nebilir, bilin�li kullan�ld�, parametreli
		swap(kartlar[rand() % 52], kartlar[rand() % 52]);	// g�nderildi�inde overloadl� alttaki metod kullan�lacakt�r.
	}
}

//	Deste Karma Parametreli Overload Tan�m
void Deste::karistir(int kacKere) {
	for (int i = 0; i < kacKere; i++) {	
		swap(kartlar[rand() % 52], kartlar[rand() % 52]);
	}
}
