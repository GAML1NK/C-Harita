//muhammed ufuk aslan
//231030001

#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <cstring>
#include <list>

using namespace std;
const int ROWS = 51;//harita sınırları
const int COLS = 71;

int Farazi[ROWS][COLS];

class Harf {
public:
	char Ad;
	int ilkX, ilkY;
	int X, Y;
	Harf(char c, int x, int y) : Ad(c), ilkX(x), ilkY(y),X(x),Y(y) {}
	};

class Arazi {
public:
	int harfSayisi;
	char arazi[ROWS][COLS];
	int araziYukseklik[ROWS][COLS]; // arazi
	Harf *harfler[52];            // Harf nesneleri

	Arazi(int Farazi[ROWS][COLS]) {
		srand(time(0));
		for (int i = 0; i < ROWS; ++i)			for (int j = 0; j < COLS; ++j)
		{
						araziYukseklik[i][j] = Farazi[i][j];
						arazi[i][j] = ' ';
		}
		char isim[] = "MuhammedUFUKAslan"; //isim değeri girilir
		 harfSayisi = sizeof(isim) - 1;
		for (int i = 0; i < harfSayisi; ++i) {
			// Harfin konumunu belirle
			int x = 26 + static_cast<int>((15 + rand() % 6) * cos(2 * 3.14159 * i / harfSayisi));
			int y = 36 + static_cast<int>((15 + rand() % 6) * sin(2 * 3.14159 * i / harfSayisi));

			// Harf nesnesini oluştur
			Harf *harf = new Harf(isim[i], x, y);

			// Harfin konumunu haritada işaretle
			arazi[x][y] = isim[i];

			// Harfi listeye ekle
			harfler[i] = harf;
		}
	}
	int KüçükBulucu(int *sayılar,int tane) { //ilk başta rastgele haritaya attığımız sayının çevresindeki konumlardan küçük olup olmadığını buluruz.
		int degisken = sayılar[0],index=0;
		for (int i = 0; i < tane; ++i) {
			if (degisken > sayılar[i]) {
				degisken = sayılar[i];
					index = i;
			} 
		}
		return index;
	}

	bool Kaydır() {// Harfin konumu ve çevresineki konum bulunur ona göre hareket etmesi sağlanır.
		bool sonuc = true;
		for (int i = 0; i < harfSayisi; i++) {
			Harf *harf = harfler[i];
			int Yukseklik = araziYukseklik[harf->ilkX][harf->ilkY];
			
			int sol = araziYukseklik[harf->ilkX - 1][harf->ilkY] ;
			if ((harf->ilkX - 1) < 0)sol = 99;
			int sag = araziYukseklik[harf->ilkX + 1][harf->ilkY];
			if ((harf->ilkX + 1) > ROWS)sag = 99;
			int ust = araziYukseklik[harf->ilkX][harf->ilkY + 1];
			if ((harf->ilkY + 1 )> COLS)ust = 99;
			int alt = araziYukseklik[harf->ilkX][harf->ilkY - 1];
			if ((harf->ilkY - 1 )< 0)alt = 99;
			int cevre[] = { sol,sag,alt,ust,Yukseklik };
			KüçükBulucu(cevre, 5);
			int index = KüçükBulucu(cevre, 5);
			if (index == 0)
				harf->ilkX--;

			else if (index == 1)
				harf->ilkX++;

			else if (index == 2)
				harf->ilkY--;

			else if (index == 3)
				harf->ilkY++;
			sonuc = sonuc && (index == 4);
			
			arazi[harf->ilkX][harf->ilkY] = harf->Ad;
			
		}
		return sonuc;
	}

	void AraziYazdir() {
		// Haritayı ekrana yazdır
		for (int i = 0; i < ROWS; ++i) {
			for (int j = 0; j < COLS; ++j) {
				cout << arazi[i][j] << ' ';
			}
			cout << endl;
		}

	}


};





int main()
{
	
	{
		setlocale(LC_ALL, "Turkish");
		FILE* fp; //dosya açma
		errno_t err;
		err = fopen_s(&fp, "Veri.csv", "r");

		if (err != 0)
		{
			cout << "Dosya açılamadı.."<< err;
			return -1;
		}

		char satir[512];
		int y = 0, x = 0;
		while (fgets(satir, 512, fp)) 
		{
			char* token;
			char* sonraki = NULL;
			token = strtok_s(satir, ";", &sonraki); // ";" dan sonraki karakteri okur
			Farazi[y][x++] = atoi(token);
			while ((token = strtok_s(NULL, ";", &sonraki)))
			{
				Farazi[y][x++] = atoi(token);
			}
			y++;
			x = 0;
		}

		

		
	}
	Arazi arazi(Farazi); //yazdırma işlemleri
	arazi.AraziYazdir(); //yazdırma işlemleri
	for (int i = 0; !arazi.Kaydır(); ++i) {

		cout << "Adim " << i + 1 << endl;
		
		cout << endl;
	}arazi.AraziYazdir();
	
		return 0;}