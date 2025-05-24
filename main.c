#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// kitap kullanıcı ve ödünç için structlar oluşturdum
struct Kitap
{
	int numara;
	char isim[50];
	char yazar[50];
	int sayfa_sayisi;
	// alacağı özellikleri yazdık
};

struct Kullanici
{
	int numara;
	char isim[50];
	char soyisim[50];
	char dogum_tarihi[11];

};

struct Odunc
{
	int kullanici_numara;
	int kitap_numara;
	char baslangic_tarihi[11];
	char bitis_tarihi[11];

};
//fonkisyonları tanımladım aşşağıda kullanabilmek için
void menu();
void kitapIslemleri();
void kullaniciIslemleri();
void oduncIslemleri();

// kitap listesi
struct Kitap kitaplar[100]; //
// kitap sayısını tutan değişken
int kitapSayisi = 0;
// kullanıcı listesi
struct Kullanici kullanicilar[100];
//kullanıcı sayısını tutan değişken
int kullaniciSayisi = 0;

// ödünç listesi
struct Odunc odunclar[100];
//ödünç sayısını tutan değişken
int oduncSayisi = 0;

// kullanacağımız fonksiyonları tanımladım
void dosyadanKitapOku();
void dosyayaKitapYaz();
void kitapEkle();
void kitapListele();
void kitapGuncelle();
void kitapSil();
void kitapArama();
void kullaniciEkle();
void kullaniciListele();
void kullaniciGuncelle();
void kullaniciSil();
void kullaniciArama();
void oduncAl();
void kitabiGeriGetir();
void oduncListele();

// Dosya işlemleri için kullancağımız fonksiyonlar
void dosyadanKullaniciOku();
void dosyayaKullaniciYaz();
void dosyadanOduncOku();
void dosyayaOduncYaz();

int main()
{
	dosyadanKitapOku(); //arreylere atıyor bu 3 fonksiyon
	dosyadanKullaniciOku();
	dosyadanOduncOku();

	menu();

	dosyayaKitapYaz(); //menüde yaptığımız array değişiklikleri önbellekte tutulur, uygulama kapatıldığında kaybolur. bu bilgileri kaybetmemek için, menüde işlemlerimiz bittikten sonra aşağıdaki dosya güncelleme fonksiyonlarımız çağrılır ve uygulama biter
	dosyayaKullaniciYaz();
	dosyayaOduncYaz();
	return 0;
}

void menu()
{
	int secim;

	do // döngü seçim
	{
		printf("\n-- ANA MENU --\n");
		printf("1. Kitap Islemleri\n");
		printf("2. Kullanici Islemleri\n");
		printf("3. Odunc Alma Islemleri\n");
		printf("0. Cikis\n");
		printf("Seciminiz: ");
		scanf("%d", &secim);

		switch (secim)
		{
		case 1:
			kitapIslemleri();
			break;
		case 2:
			kullaniciIslemleri();
			break;
		case 3:
			oduncIslemleri();
			break;
		case 0:
			printf("Programdan cikiliyor...\n");
			break;
		default:
			printf("Gecersiz secim! Tekrar deneyin.\n");
		}
	} while (secim != 0);//döngüden çıkma
}

void kitapIslemleri()
{
	int secim; // yine döngü secim

	do
	{
		printf("\n-- KITAP ISLEMLERI --\n");
		printf("1. Kitap Ekle\n");
		printf("2. Kitap Listele\n");
		printf("3. Kitap Guncelle\n");
		printf("4. Kitap Sil\n");
		printf("5. Kitap Arama\n");
		printf("0. Ana Menuye Don\n");
		printf("Seciminiz: ");
		scanf("%d", &secim);

		switch (secim)
		{
		case 1:
			kitapEkle();
			break;
		case 2:
			kitapListele();
			break;
		case 3:
			kitapGuncelle();
			break;
		case 4:
			kitapSil();
			break;
		case 5:
			kitapArama();
			break;
		case 0:
			printf("Ana menuye donuluyor...\n");
			break;
		default:
			printf("Gecersiz secim! Tekrar deneyin.\n");
		}
	} while (secim != 0);
}
// kitap ekleme fonksiyonu
void kitapEkle()
{
	printf("\n-- KITAP EKLE --\n");
    // rastgele sayı üretimi için zamanı kullanıyoruz
    srand(time(NULL)); // time hafıza sıfırlıyor
	// Kitap numarasını otomatik atıyor
	kitaplar[kitapSayisi].numara = 100000 + rand() % 900000;

	printf("Kitap Adi: ");
	fflush(stdin); // belleği temizliyor reset
	 fgets(kitaplar[kitapSayisi].isim, sizeof(kitaplar[kitapSayisi].isim), stdin);
	kitaplar[kitapSayisi].isim[strcspn(kitaplar[kitapSayisi].isim, "\n")] = 0; // dosyada yan yana yazabilmek için \n karakterini kaldırmaya yarıyor
	printf("Yazar Adi: ");
	fflush(stdin); // sağlıklı fgets kullanımı için
	fgets(kitaplar[kitapSayisi].yazar, sizeof(kitaplar[kitapSayisi].yazar), stdin);
	kitaplar[kitapSayisi].yazar[strcspn(kitaplar[kitapSayisi].yazar, "\n")] = 0;

	printf("Sayfa Sayisi: ");
	scanf("%d", &kitaplar[kitapSayisi].sayfa_sayisi);

	printf("Kitap basariyla eklendi! Kitap Numarasi: %d\n", kitaplar[kitapSayisi].numara);

	kitapSayisi++;
}

// tüm kitapları listelemye yarayan fonksiyon
void kitapListele()
{
    printf("\n-- KITAP LISTELE --\n");

    if (kitapSayisi == 0)
    {
        printf("Henuz hic kitap eklenmemis.\n");
    }
    else
    {
        printf("Kitap Numarasi\tKitap Adi\tYazar\t\tSayfa Sayisi\n");

        for (int i = 0; i < kitapSayisi; i++)
        {
            printf("%d\t\t%s\t\t%s\t\t%d\n", kitaplar[i].numara, kitaplar[i].isim, kitaplar[i].yazar, kitaplar[i].sayfa_sayisi);
        }
    }
}


// kitapları güncellemeye yarayan fonksiyon
void kitapGuncelle()
{
	printf("\n-- KITAP GUNCELLE --\n");

	int numara;
	printf("Guncellemek istediginiz kitap numarasini girin: ");
	scanf("%d", &numara);

	int indeks = -1; // indeksi istediğimiz kitabın indeksi bulana kadar artırıyoruz
	for (int i = 0; i < kitapSayisi; i++)
	{
		if (kitaplar[i].numara == numara)
		{
			indeks = i;
			break;
		}
	}

	if (indeks == -1)
	{
		printf("Belirtilen kitap numarasi bulunamadi.\n");
	}
	else
	{
		printf("Yeni Kitap Adi: ");
		fflush(stdin);
		fgets(kitaplar[indeks].isim, sizeof(kitaplar[indeks].isim), stdin);
		kitaplar[indeks].isim[strcspn(kitaplar[indeks].isim, "\n")] = '\0'; // satır sonu karakterini temizlemeye yarıyor

		printf("Yeni Yazar Adi: ");
		fflush(stdin);
		fgets(kitaplar[indeks].yazar, sizeof(kitaplar[indeks].yazar), stdin);
		kitaplar[indeks].yazar[strcspn(kitaplar[indeks].yazar, "\n")] = '\0';

		printf("Yeni Sayfa Sayisi: ");
		scanf("%d", &kitaplar[indeks].sayfa_sayisi);

		printf("Kitap basariyla guncellendi!\n");
	}
}
// kitap silmek için kullanılacak fonksiyon
void kitapSil()
{
	printf("\n-- KITAP SIL --\n");

	int numara;
	printf("Silmek istediginiz kitap numarasini girin: ");
	scanf("%d", &numara);

	int indeks = -1; // Kitap numarasının indeksini bulmak için
	for (int i = 0; i < kitapSayisi; i++)
	{
		if (kitaplar[i].numara == numara)
		{
			indeks = i;
			break;
		}
	}

	if (indeks == -1)
	{
		printf("Belirtilen kitap numarasi bulunamadi.\n");
	}
	else
	{


		// Silme işlemi
		for (int i = indeks; i < kitapSayisi -1; i++)
		{
			kitaplar[i] = kitaplar[i + 1];
		}

		kitapSayisi--;

		printf("Kitap basariyla silindi!\n");
	}
}

// Kitapları aramaya yarayan fonskiyon
void kitapArama()
{
	printf("\n-- KITAP ARAMA --\n");

	char aramaKelimesi[50];
	printf("Aramak istediginiz kelimeyi girin: ");
	fflush(stdin);
	fgets(aramaKelimesi, sizeof(aramaKelimesi), stdin);
	aramaKelimesi[strcspn(aramaKelimesi, "\n")] = '\0';

	int bulunanSayisi = 0;
	printf("Kitap Numarasi\tKitap Adi\tYazar\t\tSayfa Sayisi\n");

	for (int i = 0; i < kitapSayisi; i++)
	{
		if (strstr(kitaplar[i].isim, aramaKelimesi) != NULL || strstr(kitaplar[i].yazar, aramaKelimesi) != NULL) // bir karakter dizisinin diğer karakter dizisi içinde bulunduğu ilk yerin bellek adresini geri döndürür
		{
			printf("%d\t\t%s\t\t%s\t\t%d\n", kitaplar[i].numara, kitaplar[i].isim, kitaplar[i].yazar, kitaplar[i].sayfa_sayisi);
			bulunanSayisi++;
		}
	}

	if (bulunanSayisi == 0)
	{
		printf("Aranan kelimeye uygun kitap bulunamadi.\n");
	}
}

void kullaniciIslemleri()
{

	int secim;

	do
	{
		printf("\n-- KULLANICI ISLEMLERI --\n");
		printf("1. Kullanici Ekle\n");
		printf("2. Kullanici Listele\n");
		printf("3. Kullanici Guncelle\n");
		printf("4. Kullanici Sil\n");
		printf("5. Kullanici Arama\n");
		printf("0. Ana Menuye Don\n");
		printf("Seciminiz: ");
		scanf("%d", &secim);

		switch (secim)
		{
		case 1:
			kullaniciEkle();
			break;
		case 2:
			kullaniciListele();
			break;
		case 3:
			kullaniciGuncelle();
			break;
		case 4:
			kullaniciSil();
			break;
		case 5:
			kullaniciArama();
			break;
		case 0:
			printf("Ana menuye donuluyor...\n");
			break;
		default:
			printf("Gecersiz secim! Tekrar deneyin.\n");
		}
	} while (secim != 0);
}

void kullaniciEkle()
{
	printf("\n-- KULLANICI EKLE --\n");

    srand(time(NULL));

	kullanicilar[kullaniciSayisi].numara =  100000 + rand() % 900000;

	printf("Isim: ");
	fflush(stdin);
	fgets(kullanicilar[kullaniciSayisi].isim, sizeof(kullanicilar[kullaniciSayisi].isim), stdin);
	kullanicilar[kullaniciSayisi].isim[strcspn(kullanicilar[kullaniciSayisi].isim, "\n")] = 0;

	printf("Soyisim: ");
	fflush(stdin);
	fgets(kullanicilar[kullaniciSayisi].soyisim, sizeof(kullanicilar[kullaniciSayisi].soyisim), stdin);
	kullanicilar[kullaniciSayisi].soyisim[strcspn(kullanicilar[kullaniciSayisi].soyisim, "\n")] = 0;

	printf("Dogum Tarihi (dd/mm/yyyy): ");
	fflush(stdin);
	fgets(kullanicilar[kullaniciSayisi].dogum_tarihi, sizeof(kullanicilar[kullaniciSayisi].dogum_tarihi), stdin);
	kullanicilar[kullaniciSayisi].dogum_tarihi[strcspn(kullanicilar[kullaniciSayisi].dogum_tarihi, "\n")] = 0;

	printf("Kullanici basariyla eklendi! Kullanici Numarasi: %d\n", kullanicilar[kullaniciSayisi].numara);

	kullaniciSayisi++;
}

void kullaniciListele()
{
	printf("\n-- KULLANICI LISTELE --\n");

	if (kullaniciSayisi == 0)
	{
		printf("Henuz hic kullanici eklenmemis.\n");
	}
	else
	{
		printf("Kullanici Numarasi\tIsim\t\tSoyisim\t\tDogum Tarihi\n");

		for (int i = 0; i < kullaniciSayisi; i++)
		{
			printf("%d\t\t\t%s\t\t%s\t\t%s\n", kullanicilar[i].numara, kullanicilar[i].isim, kullanicilar[i].soyisim, kullanicilar[i].dogum_tarihi);
		}
	}
}

void kullaniciGuncelle()
{
	printf("\n-- KULLANICI GUNCELLE --\n");

	int numara;
	printf("Guncellemek istediginiz kullanici numarasini girin: ");
	scanf("%d", &numara);

	int indeks = -1; // Kullanici numarasının indeksini bulmak için
	for (int i = 0; i < kullaniciSayisi; i++)
	{
		if (kullanicilar[i].numara == numara)
		{
			indeks = i;
			break;
		}
	}

	if (indeks == -1)
	{
		printf("Belirtilen kullanici numarasi bulunamadi.\n");
	}
	else
	{
		// Eski verileri temizle
		fflush(stdin);

		printf("Yeni Isim: ");
		fgets(kullanicilar[indeks].isim, sizeof(kullanicilar[indeks].isim), stdin);
		kullanicilar[indeks].isim[strcspn(kullanicilar[indeks].isim, "\n")] = '\0'; // Satır sonu karakterini temizle

		printf("Yeni Soyisim: ");
		fgets(kullanicilar[indeks].soyisim, sizeof(kullanicilar[indeks].soyisim), stdin);
		kullanicilar[indeks].soyisim[strcspn(kullanicilar[indeks].soyisim, "\n")] = '\0'; // Satır sonu karakterini temizle

		printf("Yeni Dogum Tarihi: ");
		fgets(kullanicilar[indeks].dogum_tarihi, sizeof(kullanicilar[indeks].dogum_tarihi), stdin);
		kullanicilar[indeks].dogum_tarihi[strcspn(kullanicilar[indeks].dogum_tarihi, "\n")] = '\0'; // Satır sonu karakterini temizle

		printf("Kullanici basariyla guncellendi!\n");
	}
}

void kullaniciSil()
{
	printf("\n-- KULLANICI SIL --\n");

	int numara;
	printf("Silmek istediginiz kullanici numarasini girin: ");
	scanf("%d", &numara);

	int indeks = -1;
	for (int i = 0; i < kullaniciSayisi; i++)
	{
		if (kullanicilar[i].numara == numara)
		{
			indeks = i;
			break;
		}
	}

	if (indeks == -1)
	{
		printf("Belirtilen kullanici numarasi bulunamadi.\n");
	}
	else
	{
		// Silme işlemi
		for (int i = indeks; i < kullaniciSayisi - 1; i++)
		{
			kullanicilar[i] = kullanicilar[i + 1];
		}

		kullaniciSayisi--;

		printf("Kullanici basariyla silindi!\n");
	}
}

void kullaniciArama()
{
	printf("\n-- KULLANICI ARAMA --\n");

	char aramaKelimesi[50];
	printf("Aramak istediginiz kelimeyi girin: ");
	fflush(stdin);
	fgets(aramaKelimesi, sizeof(aramaKelimesi), stdin);
	aramaKelimesi[strcspn(aramaKelimesi, "\n")] = '\0';

	int bulunanSayisi = 0;
	printf("Kullanici Numarasi\tIsim\t\tSoyisim\t\tDogum Tarihi\n");

	for (int i = 0; i < kullaniciSayisi; i++)
	{
		if (strstr(kullanicilar[i].isim, aramaKelimesi) != NULL || strstr(kullanicilar[i].soyisim, aramaKelimesi) != NULL)
		{
			printf("%d\t\t\t%s\t\t%s\t\t%s\n", kullanicilar[i].numara, kullanicilar[i].isim, kullanicilar[i].soyisim, kullanicilar[i].dogum_tarihi);
			bulunanSayisi++;
		}
	}

	if (bulunanSayisi == 0)
	{
		printf("Aranan kelimeye uygun kullanici bulunamadi.\n");
	}
}

void oduncIslemleri()
{

	int secim;

	do
	{
		printf("\n-- ODUNC ALMA ISLEMLERI --\n");
		printf("1. Kitap Odunc Al\n");
		printf("2. Kitabi Geri Getir\n");
		printf("3. Odunc Listele\n");
		printf("0. Ana Menuye Don\n");
		printf("Seciminiz: ");
		scanf("%d", &secim);

		switch (secim)
		{
		case 1:
			oduncAl();
			break;
		case 2:
			kitabiGeriGetir();
			break;
		case 3:
			oduncListele();
			break;
		case 0:
			printf("Ana menuye donuluyor...\n");
			break;
		default:
			printf("Gecersiz secim! Tekrar deneyin.\n");
		}
	} while (secim != 0);
}

void oduncAl()
{
	printf("\n-- ODUNC AL --\n");

	if (kitapSayisi == 0 || kullaniciSayisi == 0)
	{
		printf("Odunc almak icin yeterli kitap veya kullanici bulunmamaktadir.\n");
		return;
	}

	// kullanıcıları listeliyor
	kullaniciListele();

	int kullaniciNumara;
	printf("Odunc alacak kullanici numarasini girin: ");
	scanf("%d", &kullaniciNumara);

	// kullanıcı var mı diye kontrol ediyor
	int kullaniciIndex = -1;
	for (int i = 0; i < kullaniciSayisi; i++)
	{
		if (kullanicilar[i].numara == kullaniciNumara)
		{
			kullaniciIndex = i; //numara eşitleyene kadar index arttıroyr
			break;
		}
	}

	if (kullaniciIndex == -1)
	{
		printf("Belirtilen kullanici numarasi bulunamadi.\n");
		return;
	}

	// kitapları listeliyor
	kitapListele();

	int kitapNumara;
	printf("Odunc alinacak kitap numarasini girin: ");
	scanf("%d", &kitapNumara);

	// kitabın olup olmadğına bakıyor
	int kitapIndex = -1;
	for (int i = 0; i < kitapSayisi; i++)
	{
		if (kitaplar[i].numara == kitapNumara)
		{
			kitapIndex = i;
			break;
		}
	}

	if (kitapIndex == -1)
	{
		printf("Belirtilen kitap numarasi bulunamadi.\n");
		return;
	}

	// kitabın önceden ödünç alınp alınmadığına bakıyor
	for (int i = 0; i < oduncSayisi; i++)
	{
		if (odunclar[i].kitap_numara == kitapNumara)
		{
			printf("Belirtilen kitap zaten odunc alinmistir.\n");
			return;
		}
	}

	// odunç alma işlemini gerçekleştiriyor
	printf("Odunc alinacak kitap: %s - %s\n", kitaplar[kitapIndex].isim, kitaplar[kitapIndex].yazar);

	printf("Baslangic Tarihi (dd/mm/yyyy): ");
	scanf("%s", odunclar[oduncSayisi].baslangic_tarihi);
    // Başlangıç tarihine 15 gün ekleyerek bitiş tarihini hesaplıyor

    char* baslangicPtr = odunclar[oduncSayisi].baslangic_tarihi;
    int gun, ay, yil;
    sscanf(baslangicPtr, "%d/%d/%d", &gun, &ay, &yil);

    // Basit bir şekilde 15 gün ekliyoruz
    gun += 15;

    // Daha sonra gün sayısını kontrol ederek ay ve yılı güncelliyoruz
    while (gun > 30) {
        gun -= 30;
        ay += 1;
        if (ay > 12) {
            ay = 1;
            yil += 1;
        }
    }
    sprintf(odunclar[oduncSayisi].bitis_tarihi, "%02d/%02d/%04d", gun, ay, yil); //kitabın baslangıc tarihine 15 ekleyerk bukuyorz // stringe yazar
	odunclar[oduncSayisi].kullanici_numara = kullaniciNumara;
	odunclar[oduncSayisi].kitap_numara = kitapNumara;

	// değişkeni güncelliyoruz
	oduncSayisi++;

	printf("Odunc alma islemi basariyla tamamlandi.\n");
}
void kitabiGeriGetir()
{
    printf("\n-- KITABI GERI GETIR --\n");

    if (oduncSayisi == 0)
    {
        printf("Geri getirilecek kitap bulunmamaktadir.\n");
        return;
    }

    // odunç listesini gösterir
    oduncListele();

    int kitapNumarasi;
    // Kullanıcının girdiği kitap numarasını listedeki kitap numaraları ile karşılaştırıyoruz
    printf("Geri getirilecek kitap numarasini girin: ");
    scanf("%d", &kitapNumarasi);

    int oduncIndex = -1;

    // dosyadaki kitap numaralarını kontrol etmeye yarayan döngü
    for (int i = 0; i < oduncSayisi; i++)
    {
        if (odunclar[i].kitap_numara == kitapNumarasi)
        {
            oduncIndex = i;
            break;
        }
    }

    // kitap numarası bulunamazsa
    if (oduncIndex == -1)
    {
        printf("Belirtilen kitap numarasi bulunamadi.\n");
        return;
    }

    // kitap numarasına göre işlemleri gerçekleştir
    printf("Geri getirilen kitap: %s - %s\n", kitaplar[oduncIndex].isim, kitaplar[oduncIndex].yazar);



    // Ödünç alma işlemi geri alındığında diğer değişkenleri güncelliyoruz
    for (int j = oduncIndex; j < oduncSayisi - 1; j++)
    {
        odunclar[j] = odunclar[j + 1]; //örneğin 3. indeksi 4 e 4.indeksi 5e eşitliyor döngü bitince 3 . indeks siliniyor
    }

    oduncSayisi--;

    printf("Kitap basariyla geri getirildi.\n");
}

void oduncListele()
{
	printf("\n-- ODUNC LISTELE --\n");

	if (oduncSayisi == 0)
	{
		printf("Henuz hic odunc alma islemi gerceklesmemis.\n");
	}
	else
	{
		printf("Kullanici Numarasi\tKitap Numarasi\tBaslangic Tarihi\tBitis Tarihi\n");

		for (int i = 0; i < oduncSayisi; i++)
		{
			printf("%d\t\t\t%d\t\t\t%s\t\t%s\n", odunclar[i].kullanici_numara, odunclar[i].kitap_numara, odunclar[i].baslangic_tarihi, odunclar[i].bitis_tarihi);
		}
	}
}

// Kitap yapısı için dosya okuma fonksiyonu
void dosyadanKitapOku()
{
	FILE *dosya = fopen("kitaplar.txt", "r");

	if (dosya == NULL)
	{
		printf("Kitaplar dosyasi bulunamadi veya acilamadi.\n");
		return;
	}

	char satir[1000]; //her satırı arreylerde indekselre atıyor örneğin sıfırıncı indeks ilk satırı tutyor
	while (fgets(satir, sizeof(satir), dosya) != NULL)
	{
		sscanf(satir, "%d-%[^-]-%[^-]-%d", &kitaplar[kitapSayisi].numara,//stringden alıyoruz
			   kitaplar[kitapSayisi].isim, kitaplar[kitapSayisi].yazar,
			   &kitaplar[kitapSayisi].sayfa_sayisi);
		kitapSayisi++;
	}

	fclose(dosya);
}

// Kitap yapısı için dosya yazma fonksiyonu
void dosyayaKitapYaz()
{
	FILE *dosya = fopen("kitaplar.txt", "w");// w dosyayı sıfırlar öyle yazar

	if (dosya == NULL)
	{
		printf("Kitaplar dosyasi acilamadi.\n");
		return;
	}

	for (int i = 0; i < kitapSayisi; i++)
	{
		fprintf(dosya, "%d-%s-%s-%d\n", kitaplar[i].numara,
				kitaplar[i].isim, kitaplar[i].yazar, kitaplar[i].sayfa_sayisi); //fprintf ile dosyaya yazıyoruz bilgileri
	}

	fclose(dosya);
}

void dosyayaKullaniciYaz() {
    FILE *dosya = fopen("kullanicilar.txt", "w");

    if (dosya == NULL) {
        printf("Kullanicilar dosyasi acilamadi.\n");
        return;
    }

    for (int i = 0; i < kullaniciSayisi; i++) {
        fprintf(dosya, "%d-%s-%s-%s\n", kullanicilar[i].numara,
                kullanicilar[i].isim, kullanicilar[i].soyisim, kullanicilar[i].dogum_tarihi);
    }

    fclose(dosya);
}

void dosyadanKullaniciOku() {
    FILE *dosya = fopen("kullanicilar.txt", "r");

    if (dosya == NULL) {
        printf("Kullanicilar dosyasi acilamadi.\n");
        return;
    }

    while (fscanf(dosya, "%d-%[^-]-%[^-]-%[^\n]", &kullanicilar[kullaniciSayisi].numara,
                  kullanicilar[kullaniciSayisi].isim, kullanicilar[kullaniciSayisi].soyisim,
                  kullanicilar[kullaniciSayisi].dogum_tarihi) == 4) {
        kullaniciSayisi++;
    }

    fclose(dosya);
}

// Odunc yapısı için dosya okuma fonksiyonu
void dosyadanOduncOku()
{
	FILE *dosya = fopen("odunclar.txt", "r");

	if (dosya == NULL)
	{
		printf("Odunclar dosyasi bulunamadi veya acilamadi.\n");
		return;
	}

	char satir[100];
	while (fgets(satir, sizeof(satir), dosya) != NULL)
	{
		sscanf(satir, "%d-%d-%[^-]-%[^\n]", &odunclar[oduncSayisi].kullanici_numara,
			   &odunclar[oduncSayisi].kitap_numara, odunclar[oduncSayisi].baslangic_tarihi,
			   odunclar[oduncSayisi].bitis_tarihi);
		oduncSayisi++;
	}

	fclose(dosya);
}


void dosyayaOduncYaz()
{
	FILE *dosya = fopen("odunclar.txt", "w");

	if (dosya == NULL)
	{
		printf("Odunclar dosyasi acilamadi.\n");
		return;
	}

	for (int i = 0; i < oduncSayisi; i++)
	{
		fprintf(dosya, "%d-%d-%s-%s\n", odunclar[i].kullanici_numara,
				odunclar[i].kitap_numara, odunclar[i].baslangic_tarihi, odunclar[i].bitis_tarihi);
	}

	fclose(dosya);
}
