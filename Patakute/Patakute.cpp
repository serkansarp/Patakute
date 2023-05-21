#include <iostream>
#include <iomanip>	//	Sekme kaymamaması için
#include <clocale>	//	Türkçe
#include <ctime>	//	srand için
#include <string>
#include <thread>
#include <chrono>
using namespace std;

/*
Süreç:
+ 2 kullanıcı p1-p2 yazıldı
+ Çekilen kartların yazılması ve değerinin gösterilmesi arasındaki sıkıntı giderildi
+ Belki basit bir kart görüntüsü / ascii veya utf karakter yazımıyla 
** Kurallar geçirilecek
- Test
+ Başlık
- 2. oyuncu Volkan'ın olması, en son atılan aynı değerdeki kart ile hepsini toplama ihtimalinin güçlendirilmesi
ki aynı zamanda çok keyif verici bir hareketti, o ihtimalin kardeşimde kalmasını istedim


PATAKÜTE - v.1.1
2017 sonlarında kaybettiğimiz babam Salim SARP'ın, 2023 başlarında Gliablastoma'dan kaybettiğimiz
kardeşim Volkan SARP'la bana öğretmiş olduğu oyundur. Bir iskambil destesini kalınlığa bakıp tahminen 2'ye
ayırarak bölüşülür. Kullanıcılar ellerindeki kağıtların içeriğine bakmadan en üstten yere kartları atarak
oynarlar. Basit bir oyundur. Aynı kartı denk getiren yerdekileri kendi tarafına toplar. Herhangi bir kart
hepsini toplar şeklinde bir kural yoktur. Son kağıtları ise en son alan taraf alır. Oyun sonunda en çok kağıt
toplayan kazanır. Kalınlık ölçümü ya da yakınsa sayılması ile kazanan taraf belirlenir. Birkaç tur halinde
oynanabilir '5 elin 3'ünü alan kazanır' gibi. Basitliği ve çabuk kurulması, masada, yerde, kanepede, her yerde
oynanması ile kardeşimle yıllarca oynamışızdır. Ayrıca oyun boyunca hiçbir taraf kazanamazsa kazanan olmaz,
babamın öğretimi ile PATA olunur. Bilgisayar oyuncu ismi Volkan olarak kalacaktır. İrfan Altıok, Yazılıma
Gönül Ver OOP Eğitim Seti 38-39. videosu pratiği olarak geliştiriliyor

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

void kartSekillendirici(int, int, int, int);
void oyuncuAdiYazdirAnsiKacis();

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

	void kartYazdir(int k=0) {
		kartlar[k].yazdir();
	}

	int getKartDeger(int k = 0) {
		return kartlar[k].getDeger();
	}

	int getKartSeri(int k = 0) {
		return kartlar[k].getSeri();
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
	srand(static_cast<unsigned int>(time(0)));
	
	Kart p1(karo, 88);	//	İlk atılan kartın döngü içerisinde kendisinden önce atılmış
	Kart p2(maca, 99);	//	bir kart ile karşılaştırılması için ön değerli p1 ve p2 kartları
	
	int p1Puan = 0;
	int p2Puan = 0;
	int yerdekiKart = 0;
	int sonAlan = 0;
	int p1Deger = 79;
	int p2Deger = 81;

	// Atıflı Ascii Logo çalışması, backslashlarda \\ kullanıldı
	cout << "  by Serkan SARP			                            Logo: Manytools.org" << endl;
	cout << " _______________________________________________________________________________________" << endl;
	cout << "                                                   ___   ___ " << endl;
	cout << "                                                  |\\__\\ |\\__\\" << endl;
	cout << "                                                  \\|__| \\|__|" << endl;
	cout << "  ________  ________  _________  ________  ___  __    ___  ___  _________  _______" << endl;
	cout << " |\\   __  \\|\\   __  \\|\\___   ___|\\   __  \\|\\  \\|\\  \\ |\\  \\|\\  \\|\\___   __\\|\\  ___ \\" << endl;
	cout << " \\ \\  \\|\\  \\ \\  \\|\\  \\|___ \\  \\_\\ \\  \\|\\  \\ \\  \\/  /|\\ \\  \\\\\\  \\|___ \\  \\/\\ \\   __/|" << endl;
	cout << "  \\ \\   ____\\ \\   __  \\   \\ \\  \\ \\ \\   __  \\ \\   ___  \\ \\  \\\\\\  \\   \\ \\  \\ \\ \\  \\_|/__" << endl;
	cout << "   \\ \\  \\___|\\ \\  \\ \\  \\   \\ \\  \\ \\ \\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\\\\\  \\   \\ \\  \\ \\ \\  \\_|\\ \\" << endl;
	cout << "    \\ \\__\\    \\ \\__\\ \\__\\   \\ \\__\\ \\ \\__\\ \\__\\ \\__\\\\ \\__\\ \\_______\\   \\ \\__\\ \\ \\_______\\" << endl;
	cout << "     \\|__|     \\|__|\\|__|    \\|__|  \\|__|\\|__|\\|__| \\|__|\\|_______|    \\|__|  \\|_______|" << endl;
	cout << " _______________________________________________________________________________________" << endl;


	Deste d;		//	Deste yaptık
	d.karistir();	//	Karıştırdık
	
	for (int i = 0; i < 52; i++) {		//	FOR DÖNGÜ BAŞI
		
		cout << "\033[14;0H\033[J";
		
		
		
		if (yerdekiKart == 0) {			//	- IF Yerdeki Kart 0 başlangıcı
			
			if (i % 2 == 0) {			//	-- P1 Başlayacak
				
				oyuncuAdiYazdirAnsiKacis(); // Önce 15 satır ve altını sildirip, Oyuncu/Volkan adını 15.Satır 33 sütundan yazdırma
				cout << "------ OYUNCU ------" << endl;
				cout << endl << "Kart atmak için bir tuşa basın" << endl;
				d.kartYazdir(i);	// Kart at
				yerdekiKart++;		// Yerdeki kart sayısı arttır
				kartSekillendirici(d.getKartSeri(i), d.getKartDeger(i),yerdekiKart,51-i);
				//cout << "\033[15;0H\033[J";
			}
			else {						//	-- Volkan başlayacak
				oyuncuAdiYazdirAnsiKacis();
				cout << "------ VOLKAN ------" << endl;
				d.kartYazdir(i);	// Kart at
				yerdekiKart++;		// Yerdeki kart sayısı arttır
				kartSekillendirici(d.getKartSeri(i), d.getKartDeger(i), yerdekiKart, 51 - i);
			}


		} else {						//	- IF Yerdeki Kart 0 DEĞİLSE		(AŞIRI KURALLI BÖLGE)

			if (i % 2 == 0) {			//	-- P1 Devam ediyor
				oyuncuAdiYazdirAnsiKacis();
				cout << "------ OYUNCU ------" << endl;
				cout << endl << "Kart atmak için bir tuşa basın" << endl; system("pause");
				yerdekiKart++;		//	Yerdeki kart sayısı arttır
				kartSekillendirici(d.getKartSeri(i), d.getKartDeger(i), yerdekiKart, 51 - i);

				if (d.getKartDeger(i) == d.getKartDeger(i - 1)) {	// --- Eşit değerde kartı P1'in tutturması IF'i
					p1Puan += yerdekiKart;	//	Yerdeki kartların P1'e geçmesi
					yerdekiKart = 0;		//	Yerdeki kartların Sıfırlanması
					sonAlan = 1979;			//	Son alanın P1 olarak belirlenmesi
				}													// --- Eşit değerde kartı P1'in tutturması IF SONU

			}							//	-- P1 Devam ediyor Sonu
			else
			{							//	-- Volkan devam ediyor	
				oyuncuAdiYazdirAnsiKacis();
				cout << "------ VOLKAN ------" << endl;
				d.kartYazdir(i);	// Kart at
				yerdekiKart++;		// Yerdeki kart sayısı arttır
				kartSekillendirici(d.getKartSeri(i), d.getKartDeger(i), yerdekiKart, 51 - i);

				if (d.getKartDeger(i) == d.getKartDeger(i - 1)) {	// --- Eşit değerde kartı Volkan'ın tutturması IF'i
					p2Puan += yerdekiKart;	//	Yerdeki kartların Volkan'a geçmesi
					yerdekiKart = 0;		//	Yerdeki kartların Sıfırlanması
					sonAlan = 1981;			//	Son alanın Volkan olarak belirlenmesi
				}													// --- Eşit değerde kartı Volkan'ın tutturması IF SONU
			}							//	-- Volkan devam ediyor Sonu


		
		}								//	- IF Yerdeki Kart 0/DEĞİL sonu
		


		//cout << "P1: " << p1Puan << "\tYerdeki Kart: " << yerdekiKart << endl;
		//cout << "VO: " << p2Puan << "\tKalan Kart  : " << 51-i << endl;

		
		
	}									//	FOR DÖNGÜ SONU
	
			
	return 0;
}	//	T21B/476 / 40.0007035,32.7898625

void oyuncuAdiYazdirAnsiKacis() {	cout << "\033[15;1H\033[J" << endl; cout << "\033[15;33H";		}

void kartSekillendirici(int _seri, int _deger, int _yerdekiKart, int _kacKartKaldi) {

	cout << char(6 - _seri)<<endl;
	cout << _seri << "|" << _deger << "|" << _yerdekiKart << "|" << _kacKartKaldi << endl;


	cout << ",-----------," << endl;
	cout << "| " << char(6 - _seri) << "         |" << endl;
	cout << "|           |" << endl;
	cout << "|           |" << endl;
	cout << "|           |" << endl;
	cout << "|     J     |" << endl;
	cout << "|           |" << endl;
	cout << "|           |" << endl;
	cout << "|           |" << endl;
	cout << "|         " << char(6 - _seri) << " |" << endl;
	cout << "'-----------'" << endl;
	system("pause");
}

/*
#define maca (0)	char(6)
#define sinek (1)	char(5)
#define karo (2)	char(4)
#define kupa (3)	char(3)

//	Define As veya Özel Kartlar
#define as (1)
#define bacak (11)
#define kiz (12)
#define papaz (13)
*/

