#include <iostream>
#include <clocale>	//	Türkçe
#include <ctime>	//	srand için gerekli
using namespace std;

/*
Süreç:
+ 2 kullanıcı p1-p23 yazıldı
+ Çekilen kartların yazılması ve değerinin gösterilmesi arasındaki sıkıntı giderildi
- Oynanış şekliyle aynı olması için kartlar karıldıktan sonra rand%3 ile 2ye bölünecek
- Belki basit bir kart görüntüsü / ascii veya utf karakter yazımıyla 
- Kurallar geçirilecek
- Test
- Başlık


PATAKÜTE - v.1
2017 sonlarında kaybettiğimiz babam Salim SARP'ın, 2022 sonlarında Gliablastoma'dan kaybettiğimiz
kardeşim Volkan SARP'la bana öğretmiş olduğu oyundur. Bir iskambil destesini tahminen 2'ye ayırarak
bölüşülür. Kullanıcılar ellerindeki kağıtların içeriğine bakmadan en üstten yere kartları atarak oynarlar.
Basit bir oyundur. Aynı kartı denk getiren yerdekileri kendi tarafına toplar. Bacak, yine üzerine geldiği
kartları toplar. Son kağıtları ise en son alan taraf alır. Oyun sonunda en çok kağıt toplayan kazanır.
Basitliği ve çabuk kurulması, masada, yerde, kanepede, her yerde oynanması ile kardeşimle yıllarca
oynamışızdır. * İrfan Altıok, Yazılıma Gönül Ver OOP Eğitim Seti 38-39. videosu pratiği olarak geliştiriliyor

...Aynı mezarda birlikte uyuyor olan babam ve kardeşimin güzel anısına ithafen...
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

//	Kart Sınıfı
class Kart {
private:
	int seri;
	int deger;
public:
	Kart(int seri=maca,int deger=2):seri(seri),deger(deger){}	// Parametresiz gelen istekler Maça 2 dönecek
	int getSeri() {		return seri;	}	//	Encalsulation gereği getterlar
	int getDeger() {	return deger;	}
	
	void yazdir()const {	//	Seri ve değerlerin düzgün yazdırılabilmesi için Switch-Case kullanıldı
		switch (seri) {
		case maca: { cout << "Maça"; break; }
		case sinek: { cout << "Sinek"; break; }
		case karo: { cout << "Karo"; break; }
		case kupa: { cout << "Kupa"; break; }
		}	cout << " ";
		switch (deger) {
		case as: { cout << "As"; break; }
		case bacak: { cout << "Bacak"; break; }
		case kiz: { cout << "Kız"; break; }
		case papaz: { cout << "Papaz"; break; }
		default: {cout << deger; }
		}	cout << endl;
	}

	// İlk kart solda, yanında önceki kartın izi olmadan yazdırılır
	void ilkKartYazdir()const {
		int seriCharSayi = 0;	// char() içine koyulacak sayı #define'dan bakılarak belirlendi, ascii olarak gösterilebilir
		if (this->seri == 0) { seriCharSayi = 6; }
		if (this->seri == 1) { seriCharSayi = 5; }
		if (this->seri == 2) { seriCharSayi = 4; }
		if (this->seri == 3) { seriCharSayi = seri; }

		cout << " ,---," << endl;
		cout << " |" << char(seriCharSayi) << "  |" << endl;
		cout << " |";
		
		// 1'lerde A yazdırmak için ara ayar
		if (this->deger == 1) { cout << " A "; }
		
		// 10'lu kartta sağa veya sola yaslı olmasının çirkin görüntüsü +
		// resimli kartların J-Q-K charlarıyla görüntülenmesi için çözüm
		if (deger > 9) { 
			if (deger == 10)cout << "1 0";
			else if (deger > 10) {
				cout << " ";
				if (this->deger == 11) { cout << "J"; }
				if (this->deger == 12) { cout << "Q"; }
				if (this->deger == 13) { cout << "K"; }
				cout << " ";
			}
		}else {	if (this->deger!=1)cout << " " << deger << " ";
		}
		cout << "|" << endl;
		cout << " |  " << char(seriCharSayi) << "|" << endl;
		cout << " '---'" << endl;
	}


	// 2. ve çift sayılı sırada atılan kartlar, ilkinin üzerinde olması için solunda, altındaki kartın solunun
	// izi görünür
	void ikincilSiraSayiKartYazdir()const {
		int seriCharSayi = 0;	// char() içine koyulacak sayı #define'dan bakılarak belirlendi, ascii olarak gösterilebilir
		if (this->seri == 0) { seriCharSayi = 6; }
		if (this->seri == 1) { seriCharSayi = 5; }
		if (this->seri == 2) { seriCharSayi = 4; }
		if (this->seri == 3) { seriCharSayi = seri; }

		cout << " ,,---," << endl;
		cout << " ||" << char(seriCharSayi) << "  |" << endl;
		cout << " ||";

		// 1'lerde A yazdırmak için ara ayar
		if (this->deger == 1) { cout << " A "; }

		// 10'lu kartta sağa veya sola yaslı olmasının çirkin görüntüsü +
		// resimli kartların J-Q-K charlarıyla görüntülenmesi için çözüm
		if (deger > 9) {
			if (deger == 10)cout << "1 0";
			else if (deger > 10) {
				cout << " ";
				if (this->deger == 11) { cout << "J"; }
				if (this->deger == 12) { cout << "Q"; }
				if (this->deger == 13) { cout << "K"; }
				cout << " ";
			}
		}
		else {
			if (this->deger != 1)cout << " " << deger << " ";
		}
		cout << "|" << endl;
		cout << " ||  " << char(seriCharSayi) << "|" << endl;
		cout << " ''---'" << endl;
	}

	void tekilSiraSayiKartYazdir()const {
		int seriCharSayi = 0;	// char() içine koyulacak sayı #define'dan bakılarak belirlendi, ascii olarak gösterilebilir
		if (this->seri == 0) { seriCharSayi = 6; }
		if (this->seri == 1) { seriCharSayi = 5; }
		if (this->seri == 2) { seriCharSayi = 4; }
		if (this->seri == 3) { seriCharSayi = seri; }

		cout << " ,---,," << endl;
		cout << " |" << char(seriCharSayi) << "  ||" << endl;
		cout << " |";

		// 1'lerde A yazdırmak için ara ayar
		if (this->deger == 1) { cout << " A "; }

		// 10'lu kartta sağa veya sola yaslı olmasının çirkin görüntüsü +
		// resimli kartların J-Q-K charlarıyla görüntülenmesi için çözüm
		if (deger > 9) {
			if (deger == 10)cout << "1 0";
			else if (deger > 10) {
				cout << " ";
				if (this->deger == 11) { cout << "J"; }
				if (this->deger == 12) { cout << "Q"; }
				if (this->deger == 13) { cout << "K"; }
				cout << " ";
			}
		}
		else {
			if (this->deger != 1)cout << " " << deger << " ";
		}
		cout << "||" << endl;
		cout << " |  " << char(seriCharSayi) << "||" << endl;
		cout << " '---''" << endl;
	}



	/*♦karo4
		♥kupa3
		♣sinek5
		♠maça6*/

};

//	Deste Sınıfı
class Deste {
private:
	int top;
	Kart kartlar[52];	//	Kart sınıfından 52 Kart'lık boş deste
public:
	
	Deste() {			//	Deste kurucusu ile burada döngüyle boş kartların üzerine isimleri yazıldı
		top = 0;
		for (int i = 0; i < 52; i++) {
			kartlar[i] = Kart(i / 13, i % 13 + 1);
		}
	}

	void desteYazdir()const {	//	İstenildiğinde döngü ile deste yazdırılabiliyor (Kart::yazdır kullanılıyor)
		for (int i = 0; i < 52; i++) {
			kartlar[i].yazdir();
		}
	}

	//	İlk anda define'lara göre sıralı bir deste olduğu için desteyi karmak gerekecek
	void karistir(int kackere=15180) {	//	Kardeşim Volkan SARP'ın dünyada yaşadığı gün sayısı default parametredir
		for (int i = 0; i < kackere; i++) {	//	Yüksek bir değer gibi görünebilir, bilinçli olarak düşürmedim, parametreli
			swap(kartlar[rand() % 52],kartlar[rand() % 52]);	// gönderildiğinde o kadar karıştırılacaktır.
		}
	}

	Kart getir() {
		return kartlar[top++];	//	return kartlar[top]; top++; yapılabilirdi, kısaltılmış postfix kullanıldı
	}
};


int main() {
	setlocale(LC_ALL, "Turkish");
	srand(time(0));

	Deste d;		//	Deste yaptık
	d.karistir();	//	Karıştırdık

	int p1KartSayisi = 0;
	int p2KartSayisi = 0;
	int yerdekiKartSayisi = 0;
	int kacinciKartAtilacak = 1;



	Kart p1 = d.getir();
	p1.yazdir();
	cout << p1.getDeger() << endl;

	Kart p2 = d.getir();
	p2.yazdir();
	cout << p2.getDeger() << endl;

	

	if (p2.getDeger() == p1.getDeger() || p2.getDeger() == 11) {
		cout << "Aynı kart ya da Bacak geldi, topla" << endl;
	}
	else {
		cout << "Farklı değerlerde kartlar, oyuna devam" << endl;
	}

	if (kacinciKartAtilacak == 1)p1.ilkKartYazdir();
	else if (kacinciKartAtilacak % 2 == 0)p2.ikincilSiraSayiKartYazdir();
	else if (kacinciKartAtilacak % 2 == 1)p2.tekilSiraSayiKartYazdir();	// p2 değil tabi değişecek sürekli
	// ayrıca tekSayiKartYazdir özelliği yok

	
	p2.ikincilSiraSayiKartYazdir();

	p1 = d.getir();
	cout << p1.getDeger() << endl;
	p1.tekilSiraSayiKartYazdir();
	

	/*
	İlk Kart	İkinci Kart		Üçüncü Kart
	,---,		,,---,			,---,,
	|♦  |		||♥  |			|♣  ||
	|1 0|		|| 5 |			| K ||
	|  ♦|		||  ♥|			|  ♣||
	'---'		''---'			'---''
	*/

		/*♦karo4
		♥kupa3
		♣sinek5
		♠maça6*/
	return 0;
}	//	T21B/476 / 40.0007035,32.7898625