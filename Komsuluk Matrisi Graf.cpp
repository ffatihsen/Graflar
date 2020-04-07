#include<stdio.h>
#include<conio.h>
#include<stdlib.h>



/*
Dosyada verilen komþuluk listesine göre graf oluþturma. Verilen düðümün derecesini hesaplama.
Graftaki toplam kenar sayýsýný buma. Grafý DFS ile dolaþarak d ve f dizilerini hesaplama
*/

typedef struct B_Liste{
	
	int index;
	struct B_Liste *ileri;
}BListe;

typedef struct TABLE{
	
	BListe dizi[10];
}Table;

Table Tablo;
BListe *gecici, *yeni;
int i, j, sayac;

void Tablo_Doldur( ){
	
	for(i=0; i<10; i++){
		
		Tablo.dizi[i].index = i;
		Tablo.dizi[i].ileri = NULL;
	}
}

void KomsulukMatrisiOlustur(int x, int y ){
	
	yeni = new BListe;
	yeni -> index = y;
	yeni -> ileri = NULL;
	gecici = &Tablo.dizi[x];
	
	while( gecici -> ileri != NULL ){
		
		gecici = gecici -> ileri;
	}
	gecici -> ileri = yeni;
}

void EkranaBas( ){
	int eleman=5; // Kac elemanli ise belirtin.
	
	for(i=0; i<eleman; i++){
		
		printf("\n%d. dugumun komsulari : ", (Tablo.dizi[i].index)+1);
		gecici = Tablo.dizi[i].ileri;
		while(gecici != NULL){
			
			printf("%d ", gecici -> index+1);
			gecici = gecici -> ileri;
		}
	}	
}

void DugumDerecesiBul( int derece ){
	
	sayac = 0;
	gecici = &Tablo.dizi[derece-1];
	while(gecici -> ileri != NULL){
		
		sayac++;
		gecici = gecici -> ileri;
	}
	printf("\n%d. Dugugmun Derecesi : %d", Tablo.dizi[derece].index, sayac);
}

void KenarSayisiBul( ){
	
	sayac = 0;
	for(i=0; i<10; i++){
		
		gecici = &Tablo.dizi[i];
		while(gecici -> ileri != NULL){
			
			gecici = gecici -> ileri;
			sayac++;
		}	
	}
	printf("\nGraftaki Toplam Kenar Sayisi = %d", sayac/2); //Yönsüz Grafsa
	//printf("\nGraftaki Toplam Kenar Sayisi = %d", sayac); //Yönlü Grafsa
}


/*	Renkler:
		1 : BEYAZ
		2 : GRÝ
		3 : SÝYAH	*/
		
int color[5],  time = 0, d[10], f[10], adj[5][5], x;

void DFS_Visit(int u){

	color[u] = 2;
	d[u] = time = time+1;
	if( color[u] == 2 )
		printf(" %d ",Tablo.dizi[u].index);
	gecici = &Tablo.dizi[u];
	j=0;
	while(gecici -> ileri != NULL){	//Her düðüm için komþularý bulma
		
		gecici = gecici -> ileri;
		adj[u][j] = gecici -> index;
		j++;
	}
	adj[u][j] = NULL;
	x = u;
	for(int a=0; adj[x][a]!=NULL; a++){
		
		if(color[adj[x][a]] == 1){
			
			DFS_Visit( adj[x][a] );
		}
	}
	color[u] = 3;
	f[u] = time = time+1;
}

void DFS( ){
	int eleman=5; // Eleman sayisini buraya belirtin.
	for(i=0; i<eleman; i++){
		
		color[i] = 1;
	}	
	time =0;
	printf("\n0 Dugumunden Baslayarak DFS :\n");
	for(i=0; i<eleman ;i++){
		
		if(color[i] == 1){
			
			DFS_Visit( i );			
		}
	}
	printf("\n\n d dizisi : ");
	for(i=0; d[i] != NULL; i++)	printf("%d ", d[i]);
	printf("\n f dizisi : ");
	for(i=0; f[i] != NULL; i++)	printf("%d ", f[i]);
	
}

int main(){
	int eleman=5; // Dosyadaki matrisin satir sayisini buraya belirtin.
	int eleman2=5; // Dosyadaki matrisin sutun sayisini buraya belirtin.
	FILE *oku;
    int okunan[10][10];
    int secim;
       
    if((oku = fopen("graf.txt","r")) == NULL)	printf("\nDosya acilamadi..");
	while( !feof(oku) ){	//Dosyadan okuyup diziye atama
		
		for(i=0; i<eleman; i++)
			for(j=0; j<eleman2; j++)
				fscanf(oku, "%d ", &okunan[i][j]);
	}
  	Tablo_Doldur();
 	for(i=0; i<eleman; i++)
 		for(j=0; j<eleman2; j++)
 			 if(okunan[i][j] == 1)
			 	KomsulukMatrisiOlustur(i, j); 	
   	while(1==1){
		

		printf("\n1 --> Komsuluk Listesini Goruntule\n2 --> Girilen Dugumun Derecesini Hesapla\n3 --> Toplam Kenar Sayisini Hesapla\n4 --> Grafi DFS Olarak Dolas\n5 --> Cikis\n");
		scanf("%d",&secim);
	
		switch( secim ){
			
			case 1:
				EkranaBas();
				printf("\n");
				break;
			
			case 2:
				int derece;
				printf("\nDerecesi bulunacak dugumu giriniz :");
				scanf("%d",&derece);
				DugumDerecesiBul( derece );
				printf("\n");
				break;
				
			case 3:
				KenarSayisiBul();
				printf("\n");
				break;
				
			case 4:
				DFS();
				printf("\n");
				break;
			
			case 5:
				exit(0);
				
			default:
				printf("\nYanlis secim yaptiniz.Lutfen tekrar giris yapiniz.");
				break;
		}
	}

	return 0;
}
