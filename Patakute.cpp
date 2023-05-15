#include <iostream>
#include <clocale>	//	Türkçe
#include <ctime>	//	srand için gerekli
using namespace std;

/*	--- SÜREÇ: Çekilen kartýn eþleþip eþleþmediðinin takip testi
PATAKÜTE - v.1
2017 sonlarýnda kaybettiðimiz babam Salim SARP'ýn, 2022 sonlarýnda Gliablastoma'dan kaybettiðimiz
kardeþim Volkan SARP'la bana öðretmiþ olduðu oyundur. Bir iskambil destesini tahminen 2'ye ayýrarak
bölüþülür. Kullanýcýlar ellerindeki kaðýtlarýn içeriðine bakmadan en üstten yere kartlarý atarak oynarlar.
Basit bir oyundur. Ayný kartý denk getiren yerdekileri kendi tarafýna toplar. Bacak, yine üzerine geldiði
kartlarý toplar. Son kaðýtlarý ise en son alan taraf alýr. Oyun sonunda en çok kaðýt toplayan kazanýr.
Basitliði ve çabuk kurulmasý, masada, yerde, kanepede, her yerde oynanmasý ile kardeþimle yýllarca
oynamýþýzdýr.
Not: Ýrfan Altýok, Yazýlýma Gönül Ver OOP Eðitim Seti 38-39. video pratiðinin devamý olarak oluþturulmaya çalýþýlýyor.
...Ayný mezarda birlikte uyuyor olan babam ve kardeþimin güzel anýsýna ithafen...
*/

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
	Kart(int seri=maca,int deger=2):seri(seri),deger(deger){}	// Parametresiz gelen istekler Maça 2 dönecek
	int getSeri() {		return seri;	}	//	Encalsulation gereði getterlar
	int getDeger() {	return deger;	}
	
	void yazdir()const {	//	Seri ve deðerlerin düzgün yazdýrýlabilmesi için Switch-Case kullanýldý
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
};

//	Deste Sýnýfý
class Deste {
private:
	Kart kartlar[52];	//	Kart sýnýfýndan 52 Kart'lýk boþ deste
public:
	int top = 0;
	Deste() {			//	Deste kurucusu ile burada döngüyle boþ kartlarýn üzerine isimleri yazýldý
		for (int i = 0; i < 52; i++) {
			kartlar[i] = Kart(i / 13, i % 13 + 1);
		}
	}

	void yazdir()const {	//	Ýstenildiðinde döngü ile deste yazdýrýlabiliyor (Kart::yazdýr kullanýlýyor)
		for (int i = 0; i < 52; i++) {
			kartlar[i].yazdir();
		}
	}

	//	Ýlk anda define'lara göre sýralý bir deste olduðu için desteyi karmak gerekecek
	void karistir(int kackere=15180) {	//	Kardeþim Volkan SARP'ýn dünyada yaþadýðý gün sayýsý default parametredir
		for (int i = 0; i < kackere; i++) {	//	Yüksek bir deðer gibi görünebilir, bilinçli olarak düþürmedim, parametreli
			swap(kartlar[rand() % 52],kartlar[rand() % 52]);	// gönderildiðinde o kadar karýþtýrýlacaktýr.
		}
	}

	Kart getir() {
		return kartlar[top++];	//	return kartlar[top]; top++; yapýlabilirdi, kýsaltýlmýþ postfix kullanýldý
	}

};


int main() {
	setlocale(LC_ALL,"Turkish");
	srand(time(0));

	int x = 0; int y = 0;

	Deste d;
	x = d.getir().getDeger;
	y = d.getir().getDeger;
	
	cout << x << "-" << y;




	return 0;
}