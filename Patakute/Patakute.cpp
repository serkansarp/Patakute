#include <iostream>
#include <iomanip>	//	Sekme kaymamaması için
#include <clocale>	//	Türkçe
#include <ctime>	//	srand için
#include <string>
#include <thread>
#include <chrono>
#include "KartDeste.h"
#ifdef _WIN32
	#include <conio.h>  // getch()
#else
	#include <termios.h>
	#include <unistd.h>

	// UNIX/Linux için getch()
	int getch() {
		struct termios oldtc, newtc;
		int ch;
		tcgetattr(STDIN_FILENO, &oldtc);
		newtc = oldtc;
		newtc.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newtc);
		ch = getchar();
		tcsetattr(STDIN_FILENO, TCSANOW, &oldtc);
	return ch;
}
#endif

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




void kartSekillendirici(int, int, int, int);


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
	char _getchTutucu = '0';
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
	d.karistir();	//	Parametresiz gönderip 15180 kartı birbiriyle random yer değiştirdik, anlamı metod yorumundadır
	//	d.desteYazdir(); system("pause");	//	Gerektiğinde kullanmak için
	
	
	
	
	for (int i = 0; i < 52; i++) {		//	FOR DÖNGÜ BAŞI
		
		//cout << "\033[14;0H\033[J";
		
		
		
		if (yerdekiKart == 0) {			//	- IF Yerdeki Kart 0 başlangıcı
			
			if (i % 2 == 0) {			//	-- P1 Başlayacak
				
				//oyuncuAdiYazdirAnsiKacis(); // Önce 15 satır ve altını sildirip, Oyuncu/Volkan adını 15.Satır 33 sütundan yazdırma
				cout << "\033[15;33H";
				cout << "====== OYUNCU ======" << endl;
				_getchTutucu = _getch();
				d.kartYazdir(i);	// Kart at
				yerdekiKart++;		// Yerdeki kart sayısı arttır
				kartSekillendirici(d.getKartSeri(i), d.getKartDeger(i),yerdekiKart,51-i);
				
			}
			else {						//	-- Volkan başlayacak
				cout << "\033[15;33H";
				cout << "====== VOLKAN ======" << endl;
				_getchTutucu = _getch();
				d.kartYazdir(i);	// Kart at
				yerdekiKart++;		// Yerdeki kart sayısı arttır
				kartSekillendirici(d.getKartSeri(i), d.getKartDeger(i), yerdekiKart, 51 - i);
			}


		} else {						//	- IF Yerdeki Kart 0 DEĞİLSE		(AŞIRI KURALLI BÖLGE)

			if (i % 2 == 0) {			//	-- P1 Devam ediyor
				cout << "\033[15;33H";
				cout << "====== OYUNCU ======" << endl;
				_getchTutucu = _getch();
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
				//oyuncuAdiYazdirAnsiKacis();
				cout << "\033[15;33H";
				cout << "====== VOLKAN ======" << endl;
				_getchTutucu = _getch();
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





void kartSekillendirici(int _seri, int _deger, int _yerdekiKart, int _kacKartKaldi) {



	cout << char(6 - _seri)<<endl;
	cout << _seri << "|" << _deger << "|" << _yerdekiKart << "|" << _kacKartKaldi << endl;

	cout << endl;
	
	char _fGetchTutucu = '0';
	int y = rand() % 7 + 17;				//	20	-	+-3 kayabilir max		-	17-23 arası
	int x = rand() % 9 + 32;				//	35	-	+-4 yana kayabilir max	-	32-40 arası
	
	string kartUstuDeger = "E ";
	if (_deger < 2 || _deger > 9) {
		if (_deger == 1) { kartUstuDeger = "A "; }
		else if (_deger == 10) { kartUstuDeger = "10"; }
		else if (_deger == 11) { kartUstuDeger = "J "; }
		else if (_deger == 12) { kartUstuDeger = "Q "; }
		else if (_deger == 13) { kartUstuDeger = "K "; }
		else { kartUstuDeger = "EE"; }
		} else { kartUstuDeger = to_string(_deger) + " ";
	}
	
	


	cout << "\033["; cout << y <<";"; cout << x <<"H";

	cout << ",-----------," << "\033[" << ++y << ";" << x << "H";
	cout << "| " << kartUstuDeger<<"        |"<< endl << "\033[" << ++y << ";" << x << "H";
	cout << "|           |" << "\033[" << ++y << ";" << x << "H";
	cout << "|           |" << "\033[" << ++y << ";" << x << "H";
	cout << "|           |" << "\033[" << ++y << ";" << x << "H";
	cout << "|     ";
	
	// Tam kartın ortasına Seri işareti koyuluyor, define ile belirlenen işaret char(x)
	// ile 6'dan çıkarılarak yazdırılabiliyor (Oyunda dikkat çeken bir nokta değil)
	cout << char(6 - _seri);
	cout <<	"     |" << "\033[" << ++y << ";" << x << "H";
	cout << "|           |" << "\033[" << ++y << ";" << x << "H";
	cout << "|           |" << "\033[" << ++y << ";" << x << "H";
	cout << "|           |" << "\033[" << ++y << ";" << x << "H";
	cout << "|        " << kartUstuDeger<< " |" << "\033[" << ++y << ";" << x << "H";
	cout << "\033["; cout << ++y << "; "; cout << x << "H";
	cout << "'-----------'" << endl;	cout << "\033["; cout << ++y << ";"; cout << x << "H";
	_fGetchTutucu = _getch();
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

