#include "KartDeste.h"

// Kart Getter Tanýmlarý
int Kart::getSeri() { return seri; }
int Kart::getDeger() { return deger; }

// Kart Yazdýrma (Maça As gibi) Taným
void Kart::yazdir()const {	//	Seri ve deðerlerin düzgün yazdýrýlabilmesi için Switch-Case kullanýldý
	switch (seri) {
	case maca: { cout << "Maça"; break; }
	case sinek: { cout << "Sinek"; break; }
	case karo: { cout << "Karo"; break; }
	case kupa: { cout << "Kupa"; break; }
	}	cout << " ";
	switch (deger) {
	case as: { cout << "As"; break; }
	case bacak: { cout << "Bacak"; break; }
	case kiz: { cout << "Kýz"; break; }
	case papaz: { cout << "Papaz"; break; }
	default: {cout << deger; }
	}	cout << endl;
}

// Deste Constructor Taným
Deste::Deste() {			//	Deste kurucusu ile burada döngüyle boþ kartlarýn üzerine isimleri yazýldý
	top = 0;
	for (int i = 0; i < 52; i++) {
		kartlar[i] = Kart(i / 13, i % 13 + 1);
	}
}

// Deste Yazdýrma Taným
void Deste::desteYazdir()const {	//	Ýstenildiðinde döngü ile deste yazdýrýlabiliyor (Kart::yazdýr kullanýlýyor)
	for (int i = 0; i < 52; i++) {
		kartlar[i].yazdir();
	}
}

// kartlar Dizisine Göre Kart Yazdýr Taným
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

//	Deste Karma Parametresiz Taným
void Deste::karistir() {				//	Kardeþim Volkan SARP'ýn dünyada yaþadýðý gün sayýsý kadar kart birbiriyle
	for (int i = 0; i < 15180; i++) {	//	yer deðiþir. Yüksek bir deðer gibi görünebilir, bilinçli kullanýldý, parametreli
		swap(kartlar[rand() % 52], kartlar[rand() % 52]);	// gönderildiðinde overloadlý alttaki metod kullanýlacaktýr.
	}
}

//	Deste Karma Parametreli Overload Taným
void Deste::karistir(int kacKere) {
	for (int i = 0; i < kacKere; i++) {	
		swap(kartlar[rand() % 52], kartlar[rand() % 52]);
	}
}
