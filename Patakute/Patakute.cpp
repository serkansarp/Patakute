#include <iostream>
#include <clocale>	//	T�rk�e
#include <ctime>	//	srand i�in gerekli
using namespace std;

/*
S�re�:
+ 2 kullan�c� p1-p2 yaz�ld�
+ �ekilen kartlar�n yaz�lmas� ve de�erinin g�sterilmesi aras�ndaki s�k�nt� giderildi
- Oynan�� �ekliyle ayn� olmas� i�in kartlar kar�ld�ktan sonra rand%3 ile 2ye b�l�necek
- Belki basit bir kart g�r�nt�s� / ascii veya utf karakter yaz�m�yla 
- Kurallar ge�irilecek
- Test
- Ba�l�k


PATAK�TE - v.1
2017 sonlar�nda kaybetti�imiz babam Salim SARP'�n, 2022 sonlar�nda Gliablastoma'dan kaybetti�imiz
karde�im Volkan SARP'la bana ��retmi� oldu�u oyundur. Bir iskambil destesini tahminen 2'ye ay�rarak
b�l���l�r. Kullan�c�lar ellerindeki ka��tlar�n i�eri�ine bakmadan en �stten yere kartlar� atarak oynarlar.
Basit bir oyundur. Ayn� kart� denk getiren yerdekileri kendi taraf�na toplar. Bacak, yine �zerine geldi�i
kartlar� toplar. Son ka��tlar� ise en son alan taraf al�r. Oyun sonunda en �ok ka��t toplayan kazan�r.
Basitli�i ve �abuk kurulmas�, masada, yerde, kanepede, her yerde oynanmas� ile karde�imle y�llarca
oynam���zd�r. * �rfan Alt�ok, Yaz�l�ma G�n�l Ver OOP E�itim Seti 38-39. videosu prati�i olarak geli�tiriliyor

...Ayn� mezarda birlikte uyuyor olan babam ve karde�imin g�zel an�s�na ithafen...
*/


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
	Kart(int seri=maca,int deger=2):seri(seri),deger(deger){}	// Parametresiz gelen istekler Ma�a 2 d�necek
	int getSeri() {		return seri;	}	//	Encalsulation gere�i getterlar
	int getDeger() {	return deger;	}
	
	void yazdir()const {	//	Seri ve de�erlerin d�zg�n yazd�r�labilmesi i�in Switch-Case kullan�ld�
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
};

//	Deste S�n�f�
class Deste {
private:
	int top;
	Kart kartlar[52];	//	Kart s�n�f�ndan 52 Kart'l�k bo� deste
public:
	
	Deste() {			//	Deste kurucusu ile burada d�ng�yle bo� kartlar�n �zerine isimleri yaz�ld�
		top = 0;
		for (int i = 0; i < 52; i++) {
			kartlar[i] = Kart(i / 13, i % 13 + 1);
		}
	}

	void desteYazdir()const {	//	�stenildi�inde d�ng� ile deste yazd�r�labiliyor (Kart::yazd�r kullan�l�yor)
		for (int i = 0; i < 52; i++) {
			kartlar[i].yazdir();
		}
	}

	//	�lk anda define'lara g�re s�ral� bir deste oldu�u i�in desteyi karmak gerekecek
	void karistir(int kackere=15180) {	//	Karde�im Volkan SARP'�n d�nyada ya�ad��� g�n say�s� default parametredir
		for (int i = 0; i < kackere; i++) {	//	Y�ksek bir de�er gibi g�r�nebilir, bilin�li olarak d���rmedim, parametreli
			swap(kartlar[rand() % 52],kartlar[rand() % 52]);	// g�nderildi�inde o kadar kar��t�r�lacakt�r.
		}
	}

	Kart getir() {
		return kartlar[top++];	//	return kartlar[top]; top++; yap�labilirdi, k�salt�lm�� postfix kullan�ld�
	}
};


int main() {
	setlocale(LC_ALL,"Turkish");
	srand(time(0));

	Deste d;		//	Deste yapt�k
	d.karistir();	//	Kar��t�rd�k
	
	Kart p1 = d.getir();
	p1.yazdir();
	cout << p1.getDeger() << endl;
	
	Kart p2 = d.getir();
	p2.yazdir();
	cout << p2.getDeger() << endl;


	if (p2.getDeger() == p1.getDeger()) {
		cout << "ayn� de�erdeki kart geldi, yerdekileri topla";
	}
	else{
		cout << "farkl� de�erlerde kartlar, oyuna devam ediyoruz";
	}
	
	
	


	return 0;
}	//	T21B/476 / 40.0007035,32.7898625