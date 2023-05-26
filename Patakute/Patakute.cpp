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
- Kurallar geçirilecek
- Test
+ Başlık
+ 2. oyuncu Volkan'ın olması, en son atılan aynı değerdeki kart ile hepsini toplama ihtimalinin güçlendirilmesi
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
void kartAlaniTemizle();
void kartToplayanTemizle();
void bekle();

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
	cout << " \033[90m" << "11.2017 Babamın ve"<<"\033[0m" <<"                               |\\__\\ |\\__\\"<< "\033[90m"<<"      T21B / 476, Karşıyaka" << "\033[0m" <<endl;
	cout << "\033[90m" << " 02.2023 Kardeşimin güzel anılarına ithafen..." << "\033[0m" << "    \\|__| \\|__| " << "\033[90m" << "    40.0002459, 32.7889089      "<< "\033[0m" << endl;
	cout << "  ________  ________  _________  ________  ___  __    ___  ___  _________  _______" << endl;
	cout << " |\\   __  \\|\\   __  \\|\\___   ___|\\   __  \\|\\  \\|\\  \\ |\\  \\|\\  \\|\\___   __\\|\\  ___ \\" << endl;
	cout << " \\ \\  \\|\\  \\ \\  \\|\\  \\|___ \\  \\_\\ \\  \\|\\  \\ \\  \\/  /|\\ \\  \\\\\\  \\|___ \\  \\/\\ \\   __/|" << endl;
	cout << "  \\ \\   ____\\ \\   __  \\   \\ \\  \\ \\ \\   __  \\ \\   ___  \\ \\  \\\\\\  \\   \\ \\  \\ \\ \\  \\_|/__" << endl;
	cout << "   \\ \\  \\___|\\ \\  \\ \\  \\   \\ \\  \\ \\ \\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\\\\\  \\   \\ \\  \\ \\ \\  \\_|\\ \\" << endl;
	cout << "    \\ \\__\\    \\ \\__\\ \\__\\   \\ \\__\\ \\ \\__\\ \\__\\ \\__\\\\ \\__\\ \\_______\\   \\ \\__\\ \\ \\_______\\" << endl;
	cout << "     \\|__|     \\|__|\\|__|    \\|__|  \\|__|\\|__|\\|__| \\|__|\\|_______|    \\|__|  \\|_______|" << endl;
	cout << " _______________________________________________________________________________________" << endl;

	
	// SOL TABLO BOŞ veya 0 DEĞERLİ
	cout << "\033[19;1H" << "   - PUANLAR -"<<endl;
	cout << " ===============" << endl;
	cout << "  " << char(15) << "  OYUNCU:  0" << endl;
	cout << "  " << char(15) << "  VOLKAN:  0" << endl;
	cout << " ---------------" << endl;
	cout << "  Son Toplayan" << endl << "        -" << endl << " ===============" << endl;


	// SAĞ TABLO
	cout << "\033[19;74H" << " Kalan Kart: 52" << endl;
	cout << "\033[20;72H" << " Yerdeki Kart:  0" << endl;
	cout << "\033[21;71H" << "==================" << endl;
	cout << "\033[22;71H" << "Alttaki Son 3 Kart" << endl;
	cout << "\033[23;71H" << "------------------" << endl;
	cout << "\033[24;72H" << char(31) << " ------     ";
	cout << "\033[25;72H" << char(31) << " ------     ";
	cout << "\033[26;72H" << char(31) << " ------     ";



	Deste d;		//	Deste yaptık
	d.karistir();	//	Parametresiz gönderip 15180 kartı birbiriyle random yer değiştirdik, anlamı metod yorumundadır
	//	d.desteYazdir(); system("pause");	//	Gerektiğinde kullanmak için
	
	
	
	
	for (int i = 0; i < 52; i++) {		//	FOR DÖNGÜ BAŞI	- OYUN MOTORUDUR
		
		
		if (yerdekiKart == 0) {			//	- IF Yerdeki Kart 0 başlangıcı
			
			if (i % 2 == 0) {			//	-- P1 Başlayacak
				cout << "\033[15;33H" << "====== OYUNCU ======" << endl;
				cout << "\033[16;33H" << "- Enter bekleniyor -";
				_getchTutucu = _getch();
				//system("pause");
				cout << "\033[16;33H" << "                    ";
				kartSekillendirici(d.getKartSeri(i), d.getKartDeger(i),yerdekiKart,51-i);
				yerdekiKart++;		// Yerdeki kart sayısı arttır
				
				
				
			}
			else {						//	-- Volkan başlayacak
				cout << "\033[15;33H" << "====== VOLKAN ======" << endl;
				bekle();
				kartSekillendirici(d.getKartSeri(i), d.getKartDeger(i), yerdekiKart, 51 - i);
				yerdekiKart++;		// Yerdeki kart sayısı arttır
			}


		} else {						//	- IF Yerdeki Kart 0 DEĞİLSE	- (KART TOPLAMA KURALLI BÖLGE)

			if (i % 2 == 0) {			//	-- P1 Devam ediyor
				cout << "\033[15;33H" << "====== OYUNCU ======" << endl;
				cout << "\033[16;33H" << "- Enter bekleniyor -";
				_getchTutucu = '0';
				cout << _getchTutucu;
				//system("pause");
				cout << "\033[16;33H" << "                    ";
				kartSekillendirici(d.getKartSeri(i), d.getKartDeger(i), yerdekiKart, 51 - i);
				yerdekiKart++;		// Yerdeki kart sayısı arttır
				

				if (d.getKartDeger(i) == d.getKartDeger(i - 1) || d.getKartDeger(i)==11) {	// --- Eşit değerde kartı P1'in tutturması IF'i
					p1Puan += yerdekiKart;	//	Yerdeki kartların P1'e geçmesi
					yerdekiKart = 0;		//	Yerdeki kartların Sıfırlanması
					sonAlan = 1979;			//	Son alanın P1 olarak belirlenmesi
					bekle();
					kartAlaniTemizle();
					cout << "\033[19;34H" "KARTLARI  TOPLAYAN" << "\033[20;38H" << "- OYUNCU -";
					bekle();
					kartToplayanTemizle();
				}						// --- Eşit değerde kartı P1'in tutturması IF SONU

			}							//	-- P1 Devam ediyor Sonu
			else
			{							//	-- Volkan devam ediyor	
				cout << "\033[15;33H" << "====== VOLKAN ======" << endl;
				bekle();
				kartSekillendirici(d.getKartSeri(i), d.getKartDeger(i), yerdekiKart, 51 - i);
				yerdekiKart++;		// Yerdeki kart sayısı arttır
				

				if (d.getKartDeger(i) == d.getKartDeger(i - 1) || d.getKartDeger(i) == 11) {	// --- Eşit değerde kartı Volkan'ın tutturması IF'i
					p2Puan += yerdekiKart;	//	Yerdeki kartların Volkan'a geçmesi
					yerdekiKart = 0;		//	Yerdeki kartların Sıfırlanması
					sonAlan = 1981;			//	Son alanın Volkan olarak belirlenmesi
					bekle();
					kartAlaniTemizle();
					cout << "\033[19;34H" << "KARTLARI  TOPLAYAN" << "\033[20;38H" << "- VOLKAN -";
					bekle();
					kartToplayanTemizle();
				}						// --- Eşit değerde kartı Volkan'ın tutturması IF SONU
			}							//	-- Volkan devam ediyor Sonu

					
		}								//	- IF Yerdeki Kart 0/DEĞİL sonu
		

		if (i == 51) {
			bekle();
			kartAlaniTemizle();
			if (yerdekiKart == 0) {
				cout << "\033[19;33H" <<"-YERDE KART KALMADI-";
				bekle();
				kartToplayanTemizle();
				_getchTutucu = _getch();
				bekle();
			}
			else {

				if (sonAlan == 1979) {
					cout << "\033[19;36H" << "YERDEKİLER DE" << "\033[20;37H" << "- VOLKAN -" << "\033[21;35H" << "PUANINA EKLENDİ";
					p1Puan += yerdekiKart;
					yerdekiKart = 0;
				}
				else if (sonAlan == 1981) {
					cout << "\033[19;36H" << "YERDEKİLER DE" << "\033[20;37H" << "- OYUNCU -" << "\033[21;35H" << "PUANINA EKLENDİ";
					p2Puan += yerdekiKart;
					yerdekiKart = 0;
				}
			}



		}

		
		cout << "\033[21;14H" << setfill(' ') << setw(2) << p1Puan << endl;
		cout << "\033[22;14H" << setfill(' ') << setw(2) << p2Puan << endl;
		if (sonAlan == 1979) cout << "\033[25;2H" << "  - OYUNCU -" << endl;
		if (sonAlan == 1981) cout << "\033[25;2H" << "  - VOLKAN -" << endl;
		

		cout << "\033[19;87H" << setfill(' ') << setw(2) << 51 - i;
		cout << "\033[20;87H" << setfill(' ') << setw(2) << yerdekiKart;
			
			

		if(yerdekiKart==0 || yerdekiKart==1){
			cout << "\033[24;72H" << char(31) << " ------     ";
			cout << "\033[25;72H" << char(31) << " ------     ";
			cout << "\033[26;72H" << char(31) << " ------     ";
		}
		else if (yerdekiKart == 2) {
			cout << "\033[24;72H" << char(31) << " ";
			d.kartYazdir(i - 1);	cout << "     ";
		}
		else if (yerdekiKart == 3) {
			cout << "\033[24;72H" << char(31) << " ";
			d.kartYazdir(i - 1);	cout << "     ";
			cout << "\033[25;72H" << char(31) << " ";
			d.kartYazdir(i - 2);	cout << "     ";			
		}
		else if (yerdekiKart > 3) {
			cout << "\033[24;72H" << char(31) << " ";
			d.kartYazdir(i - 1);	cout << "     ";
			cout << "\033[25;72H" << char(31) << " ";
			d.kartYazdir(i - 2);	cout << "     ";
			cout << "\033[26;72H" << char(31) << " ";
			d.kartYazdir(i - 3);	cout << "     ";
		}
		else {
			cout << "\033[26;72H" << " !! HATA !!    " << " ";
		}
						
	}			//	FOR DÖNGÜ SONU
	
	// OYUN SONU VE PUAN HESAPLAMA (sayı farkı düşükse, o durum da dahil)
	p1Puan = 26; p2Puan = 26;
	cout << "\033[22;35H" << "---------------";
	cout << "\033[23;35H" << "  OYUN  SONU";
	cout << "\033[24;35H" << "Oyuncu Puanı: " << p1Puan;
	cout << "\033[25;35H" << "Volkan Puanı: " << p2Puan;
	if (p1Puan > p2Puan) {
		cout << "\033[26;35H" << "Kazanan:  OYUNCU";
		if (p1Puan - p2Puan <= 6)cout << "\033[27;35H" << p1Puan - p2Puan << "kart farkla...";
	}
	else if (p2Puan > p1Puan) {
		cout << "\033[26;35H" << "Kazanan:  VOLKAN";
		if (p2Puan - p1Puan <= 6)cout << "\033[27;35H" << p2Puan - p1Puan << " kart farkla...";
	}
	else if (p1Puan == 26 && p2Puan == 26) {
		cout << "\033[26;35H" << "Nadiren karşılaşılan bir durum ancak PATA olundu";
	}
	else { 
		cout << " !! HATA !! ";
	}

	
	return 0;
}	





void kartSekillendirici(int _seri, int _deger, int _yerdekiKart, int _kacKartKaldi) {

	char _fGetchTutucu = '0';
	int y = rand() % 7 + 17;				//	20	-	+-3 kayabilir max		-	17-23 arası
	int x = rand() % 9 + 32;				//	35	-	+-4 yana kayabilir max	-	32-40 arası
	
	

	// 1 yerine A, J,Q,K karakterleri ve 10 değerinin 2 karakterlik alan kaplamasından dolayı ara IF (EE'ler hata belirteci)
	string kartUstuDeger = "EE";
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
	
	// A,J,Q,K karakterleri ve 10 değerinin 2 karakterlik alan kaplamasından dolayı ara IF (EE'ler hata belirteci)
	// Ayrıca sağ alt köşedeki gösteriminin 1 karakter daha yakın gösterimi için tekrar belirlendi
	kartUstuDeger = "EE";
	if (_deger < 2 || _deger > 9) {
		if (_deger == 1) { kartUstuDeger = " A"; }
		else if (_deger == 10) { kartUstuDeger = "10"; }
		else if (_deger == 11) { kartUstuDeger = " J"; }
		else if (_deger == 12) { kartUstuDeger = " Q"; }
		else if (_deger == 13) { kartUstuDeger = " K"; }
		else { kartUstuDeger = "EE"; }
	}
	else {
		kartUstuDeger = " " + to_string(_deger);
	}

	
	cout << "|        " << kartUstuDeger<< " |" << "\033[" << ++y << ";" << x << "H";
	cout << "\033["; cout << ++y << "; "; cout << x << "H";
	cout << "'-----------'" << endl;	cout << "\033["; cout << ++y << ";"; cout << x << "H";
}

void kartAlaniTemizle() {
	for(int i=17;i<34;i++){	cout << "\033[" << i << ";" << "31H" << "                      "; }
}
void kartToplayanTemizle() {
	cout << "\033[19;33H" << "                    " << "\033[20;33H" << "                   ";
}
void bekle() { this_thread::sleep_for(chrono::milliseconds(503)); } //803 önceki değer