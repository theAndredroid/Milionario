#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// dichiarazione delle librerie usate solo in ambiente Windows
#ifdef _WIN32
	#include <Windows.h>
	#include <io.h>
	#include <fcntl.h>
	#include <conio.h>

// dichiarazione delle librerie e funzioni usate in ambiente UNIX-like
#else
	#include <unistd.h>
	#include <termios.h>


	char getch();
#endif

void welcome_screen();
void win_screen();
void lose_screen();
int lettura();
char accensione(int *, int);
FILE *ndomanda(int, int *);
void box_domanda_start();
void box_risposta_start(int, int);
void screen_print(char, int);
void clear();
void mysleep(int);
int char_in_line(char, int *, int *);
void question_read(FILE *);
void asks_read(FILE *, int *);
void asks_random(int *);
void cinquantaecinquanta(int *);

char box_domanda[10][63];
int quantepossibilitahaiancoradiusareilcinquantaecinquanta=1;	//mezzo voto in più per la simpatia :)

// stuttura del main che fa scorrere i vari liveli
void main(){
	welcome_screen();
	getch();
	int i=0;
	do{
		box_domanda_start();
		i++;
	}while (lettura(i));
	getch();
}

// funzione che stampa dal file benvenuto.txt la schermata iniziale allineata al centro
void welcome_screen(){
	clear();
	FILE *in;
	in=fopen("benvenuto.txt", "r");
	for(int i=0; i<10; i++){
		long int temp=ftell(in);
		char ch;
		int j=0;
		do{
			ch=fgetc(in);
			if(ch!=13)
				j++;
		}while(ch!=10);
		fseek(in, temp, 0);
		int n_space=(79-j)/2;
		do{
			printf(" ");
			n_space--;
		}while(n_space>0);	
		do{
			screen_print(fgetc(in), 0);
			j--;
		}while(j>1);
		do{
			ch=fgetc(in);
		}while(ch!=10);
		printf("\n");
	}
	fclose(in);
}

// funzione che stampa dal file vittoria.txt la schermata finale di quando si giunge al milione
void win_screen(){
	clear();
	FILE *in;
	in=fopen("vittoria.txt", "r");
	for(int i=0; i<7; i++){
		long int temp=ftell(in);
		char ch;
		int j=0;
		do{
			ch=fgetc(in);
			if(ch!=13)
				j++;
		}while(ch!=10);
		fseek(in, temp, 0);
		int n_space=(79-j)/2;
		do{
			printf(" ");
			n_space--;
		}while(n_space>0);	
		do{
			screen_print(fgetc(in), 0);
			j--;
		}while(j>1);
		do{
			ch=fgetc(in);
		}while(ch!=10);
		printf("\n");
	}
	fclose(in);
	printf("\n");
	for (int i=0; i<25; i++)
		printf(" ");
	printf("Clicca un tasto per uscire...\n");
}

// funzione che stampa dal file sconfitta.txt la schermata di quando di sbaglia una risposta
void lose_screen(){
	clear();
	FILE *in;
	in=fopen("sconfitta.txt", "r");
	for(int i=0; i<5; i++){
		long int temp=ftell(in);
		char ch;
		int j=0;
		do{
			ch=fgetc(in);
			if(ch!=13)
				j++;
		}while(ch!=10);
		fseek(in, temp, 0);
		int n_space=(79-j)/2;
		do{
			printf(" ");
			n_space--;
		}while(n_space>0);	
		do{
			screen_print(fgetc(in), 0);
			j--;
		}while(j>1);
		do{
			ch=fgetc(in);
		}while(ch!=10);
		printf("\n");
	}
	fclose(in);
	printf("\n");
	for (int i=0; i<25; i++)
		printf(" ");
	printf("Clicca un tasto per uscire...\n");
}

// funzione generale per la gestione di ogni livello
int lettura(int liv){

	// appertura del file associato al livello e scelta (in modo random) di una domanda contenuta nel file
	FILE *in;
	int mdimoney;
	in=ndomanda(liv, &mdimoney);
	int n_question;
	fscanf(in, "%d\n", &n_question);
	srand(time(NULL));
	n_question=rand()%n_question;
	for(int i=0; i<n_question*6; i++){
		char ch;
		do{
			ch=fgetc(in);
		}while (ch!=10);
	}

	// gestione della domanda e delle risposte
	question_read(in);
	int asks_order[4];
	asks_read(in, asks_order);
	fclose(in);
	char r;

	// gestione della stampa delle varie schermate
		// stampa della presentazione della domanda
	do{
		clear();
		printf("\nIl tuo montepremi ");
		screen_print(-88, 0);	//è 
		printf(" di %d", mdimoney);
		screen_print(13, 0);	//€
		printf("\n\n");
		for(int i=0; i<10; i++){
			for (int j=0; j<63; j++)
				screen_print(box_domanda[i][j], 0);
			printf("\n");
		}
		r=accensione(asks_order, mdimoney);
	} while(r==5);

	// stampa della schermata, dopo aver risposto alla domanda
	int y=(r/2*3)+3, x=(r%2*31);
	clear();
	printf("\nIl tuo montepremi ");
	screen_print(-88, 0);	//è 
	printf(" di %d", mdimoney);
	screen_print(13, 0);	//€
	printf("\n\n");
	if(asks_order[r]==0){
		for(int i=0; i<10; i++){
			for (int j=0; j<63; j++){
				int temp=0;
				if(i>y && i<y+4 && j>x && j<x+31)
					temp=2;
				screen_print(box_domanda[i][j], temp);
			}
			printf("\n");
		}

		// gestione dell'arrivo al milione
		if (liv==15){
			mysleep(2);
			win_screen();
			printf("\n");
			mysleep(2);
       			return 0;
		}

		// gestione della risposta in modo correto alla domanda
		else{
			printf("La risposta ");
			screen_print(-88, 0);	//è
			printf(" corretta!\n");
			mysleep(2);
		}
		return 1;
	
	// gestione della risposta in modo sbagliato
	} else{
		int k=0, l;
		while(asks_order[k]!=0)
			k++;
		l=(k/2*3)+3, k=(k%2*31);
		for(int i=0; i<10; i++){
			for (int j=0; j<63; j++){
				int temp=0;
				if(i>y && i<y+4 && j>x && j<x+31)
					temp=3;
				if(i>l && i<l+4 && j>k && j<k+31)
					temp=2;
				screen_print(box_domanda[i][j], temp);
			}
			printf("\n");
		}
		mysleep(2);
		lose_screen();
	}
	return 0;
}

// lettura della domanda da file e salvattagio dentro la matrice box_domanda
void question_read(FILE *in){
	int temp=0, lf, i=0, j=1;
	long int pos=ftell(in);
	char temp2;
	do{
		temp2=fgetc(in);
	} while(char_in_line(temp2, &temp, &lf));
	
	fseek(in, pos, 0);
	do{
		int x=31-lf/2+i;
		box_domanda[j][x]=fgetc(in);
		if(box_domanda[j][x]!=-61 && box_domanda[j][x]!=13)
			i++;
		if(i==lf){
			j++;
			lf=temp-lf;
			temp-=i;
			i=0;
		}
	} while(temp!=0);
	do{
		temp2=fgetc(in);
	} while(temp2!=10);
}


// funzione che conta i carratteri di ogni riga
int char_in_line(char temp, int *i, int *j){
	switch(temp){
		case 10:
			if(*i<=57)
				*j=*i;
			return 0;
		case -61:
		case 13:
			return 1;
		case 32:
			if(*i<=57)
				*j=*i;
		default:
			(*i)++;
			return 1;
	}
}


// lettura delle domande dal file e salvataggio nella matrice
void asks_read(FILE *in, int *asks_order){
	asks_random(asks_order);
	for(int i=0; i<4; i++){
		int j=0;
		while(asks_order[j]!=i)
			j++;
		int r=(j/2*3)+5, x=(j%2*31)+2;
		box_risposta_start(r, x);
		box_domanda[r][x]='A'+j;
		box_domanda[r][++x]=':';
		box_domanda[r][++x]=' ';
		do{
			box_domanda[r][++x]=fgetc(in);
			if(box_domanda[r][x]==-61 || box_domanda[r][x]==13)
				x--;
		} while(box_domanda[r][x]!=10);
		box_domanda[r][x]=32;
	}
}


// funzione che si occupa di mescolare le risposte in modo random
void asks_random(int *asks_order){
	srand(time(NULL));
	for(int i=0; i<4; i++)
		asks_order[i]=0;
	for(int i=3; i>0; i--){
		int x, j=0;
		x=rand()%(i+1);
		do{
			if(asks_order[j]!=0)
				x=(x+1)%4;
			j=(j+1)%5;
		} while(j!=x+1);
		asks_order[(j+3)%4]=i;
	}
	return;
}


// gestione del l'input per la risposta alla domanda, con la possibilità di usare una volta il 50/50
char accensione(int *asks_order, int mdimoney){
	char r;
	do{
		fflush(stdin);
		r=getch();
		if (r==53 && quantepossibilitahaiancoradiusareilcinquantaecinquanta==1){
			cinquantaecinquanta(asks_order);
			quantepossibilitahaiancoradiusareilcinquantaecinquanta=0;
			return 5;
		}
		if(r==53){
			printf("Hai gi");
			screen_print(-96, 0);	//à
			printf(" usato il 50/50\n");
		}
		r=r & 0b11011111;
	}while(r<'A' || r>'D');

	// stampa della schermata con la risposta selezionata
	r-='A';
	int y=(r/2*3)+3, x=(r%2*31);
	clear();
	printf("\nIl tuo montepremi ");
	screen_print(-88, 0);	//è 
	printf(" di %d", mdimoney);
	screen_print(13, 0);	//€
	printf("\n\n");
	for(int i=0; i<10; i++){
		for (int j=0; j<63; j++){
			int temp=0;
			if(i>y && i<y+4 && j>x && j<x+31)
				temp++;
			screen_print(box_domanda[i][j], temp);
		}
		printf("\n");
	}
	mysleep(2);
	return r;
}


//funzione che si occupa di nascondere le risposte dopo aver usato il 50/50
void cinquantaecinquanta(int *asks_order){
	for(int i=0; i<4; i++){
		if(asks_order[i]>1){
			int r=(i/2*3)+5, x=(i%2*31)+2;
			while((box_domanda[r][x]!=32 || box_domanda[r][x+1]!=32) && box_domanda[r][x]!=11) 
			box_domanda[r][x++]=32;
		}
	}
}

//  funzione che si occupa della gestione dei riquadri delle domande
//  usando i carrateri di fincatura (contaggiati dalla prof. De Poli),
//  associando un numero "personalizatto" per ogni carattere che sucessimente,
//  con due metodi divesi (uno per Windows e l'altro per Linux) stampa 
//  i rispettivi carrateri nello standard Unicode
void box_domanda_start(){
	for (int i=0; i<10; i++){
		for(int j=0; j<63; j++)
			box_domanda[i][j]=' ';
	}
	box_domanda[0][0]=1;
	box_domanda[0][62]=2;
	box_domanda[3][0]=3;
	box_domanda[3][62]=4;
	for(int i=1; i<=2; i++){
		for(int j=0; j<=62; j+=62)
			box_domanda[i][j]=5;
	}
	for(int i=0; i<=3; i+=3){
		for(int j=1; j<=61; j++)
			box_domanda[i][j]=6;
	}

}


// gestione dei riquadri delle risposte come per le domande
void box_risposta_start(int r, int x){
	box_domanda[r-1][x-1]=7;
	box_domanda[r-1][x+28]=8;
	box_domanda[r+1][x-1]=9;
	box_domanda[r+1][x+28]=10;
	for(int i=x-1; i<=x+28; i+=29)
		box_domanda[r][i]=11;
	for(int i=r-1; i<=r+1; i+=2){
		for(int j=x; j<=x+27; j++)
			box_domanda[i][j]=12;
	}

}

// gestione di alcune funzioni solo per ambiente Windows
#ifdef _WIN32
	
	// riadatatmento della funzione clear
	void clear(){
		system("cls");
		return;
	}


	// riadatamento della funzione sleep che ha bisogno del tempo espresso in millisecondi
	void mysleep(int temp){
		sleep(temp*1000);
		return;
	}
	

	// stampa di ogni carratere
	void screen_print(char temp, int mode){
		// scelta del colore di sfondo 
		switch(mode){
			case 0:
				break;
			case 1:
				printf("\033[43m");	// giallo
				break;
			case 2:
				printf("\033[42m");	// verde
				break;
			case 3:
				printf("\033[41m");	// rosso
				break;
		}
		// stampa dei carrrtteri "normali"
		if(temp>=' ')
			printf("%c", temp);
		else{
			// stampa dei carratteri attraverso il codice ascii
			// documentazione: https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/setmode?view=vs-2019
			_setmode(_fileno(stdout), _O_U16TEXT);
			switch(temp){
				/* RIQUADRO DOMANDA */
				case 1: // angolo alto sinistra
					wprintf(L"\x2554");
					break;
				case 2: // angolo alto destra
					wprintf(L"\x2557");
					break;
				case 3: // angolo basso sinistra
					wprintf(L"\x255A");
					break;
				case 4: // angolo basso destra
					wprintf(L"\x255D");
					break;
				case 5: // verticale
					wprintf(L"\x2551");
					break;
				case 6: // orizzontale
					wprintf(L"\x2550");
					break;
				/* RIQUADRO RISPOSTE */
				case 7: // angolo alto sinistra
					wprintf(L"\x250C");
					break;
				case 8: // angolo alto destro
					wprintf(L"\x2510");
					break;
				case 9: // angolo basso sinistro
					wprintf(L"\x2514");
					break;
				case 10: // angolo basso desto
					wprintf(L"\x2518");
					break;
				case 11: // verticale
					wprintf(L"\x2502");
					break;
				case 12: // orizzontale
					wprintf(L"\x2500");
					break;
				/* CARRATERI SPECIALI */
				case 13: // simbolo Euro
					wprintf(L"\x20AC");
					break;
				case -61:
					break;
				case -88: // e accentata
					wprintf(L"\x00E8");
					break;
				case -71: // u accentata
					wprintf(L"\x00F9");
					break;
				case -78: // o accentata
					wprintf(L"\x00F2");
					break;
				case -84: // i accentata
					wprintf(L"\x00EC");
					break;
				case -96: // a accentata
					wprintf(L"\x00E0");
					break;
				default:
					wprintf(L"\x0020");
					break;
			}

		// ritorno ai valori predefiniti
			_setmode(_fileno(stdout), _O_TEXT);
		}
		printf("\e[0m");
	}
// gestione di alcune funzioni solo per ambiente UNIX-like
#else
	// riadatamento della funzione clear
	void clear(){
		system("clear");
		return;
	}

	// riadatamento  della funzione sleep che ha bisogno del tempo espresso in secondi
	void mysleep(int temp){
		sleep(temp);
		return;
	}

	// riadatamento della funzione getch.h già presente nel ambiente Windows con la libreria conio.h
	// documentazione: https://stackoverflow.com/questions/7469139/what-is-the-equivalent-to-getch-getche-in-linux
	char getch(){
		char buf = 0;
		struct termios old = { 0 };
		fflush(stdin);
		if (tcgetattr(0, &old) < 0)
			perror("tcsetattr()");
		old.c_lflag    &= ~ICANON;   // local modes = Non Canonical mode
		old.c_lflag    &= ~ECHO;     // local modes = Disable echo. 
		old.c_cc[VMIN]  = 1;         // control chars (MIN value) = 1
		old.c_cc[VTIME] = 0;         // control chars (TIME value) = 0 (No time)
		if (tcsetattr(0, TCSANOW, &old) < 0)
			perror("tcsetattr ICANON");
		if (read(0, &buf, 1) < 0)
			perror("read()");
		old.c_lflag    |= ICANON;    // local modes = Canonical mode
		old.c_lflag    |= ECHO;      // local modes = Enable echo. 
		if (tcsetattr(0, TCSADRAIN, &old) < 0)
		       	perror ("tcsetattr ~ICANON");
		return buf;
	}

	
	// stampa di ogni singolo carrattere
	void screen_print(char temp, int mode){

		// scelta del colore
		switch(mode){
			case 0:
				break;
			case 1:
				printf("\033[43m");
				break;
			case 2:
				printf("\033[42m");
				break;
			case 3:
				printf("\033[41m");
				break;
		}

		// stampa dei carrateri "normali"
		if(temp>=' ' && temp!='*')
			printf("%c", temp);

		// stampa dei carratteri attraverso il codice ascii
		else{
			switch(temp){
				/* RIQUADRO DOMANDA */
				case 1: // angolo alto sinistra
					printf("\u2554");
					break;
				case 2: // angolo alto destra
					printf("\u2557");
					break;
				case 3: // angolo basso sinistra
					printf("\u255A");
					break;
				case 4: // angolo basso destra
					printf("\u255D");
					break;
				case 5: // verticale
					printf("\u2551");
					break;
				case 6: // orizzontale
					printf("\u2550");
					break;
				/* RIQUADRO RISPOSTE */
				case 7: // angolo alto sinistra
					printf("\u250C");
					break;
				case 8: // angolo alto destro
					printf("\u2510");
					break;
				case 9: // angolo basso sinistro
					printf("\u2514");
					break;
				case 10: // angolo basso desto
					printf("\u2518");
					break;
				case 11: // verticale
					printf("\u2502");
					break;
				case 12: // orizzontale
					printf("\u2500");
					break;
				 /* CARRATERI PARTICOLARI */
				case 13: // simbolo Euro
					printf("\u20AC");
					break;
				case '*':
					printf("\033[1;30m");
					return;
					break;
				case -61: 
					break;
				case -88: // e accentata
				case -71: // u accentata
				case -78: // o accentata
				case -84: // i accentata
				case -96: // a accentata
					printf("%c%c", -61, temp);
					break;
				default:
					printf(" ");
					break;
			}
		}
		// ripristino del colore
		printf("\033[0m");
	}
#endif


// funzione che in base al livello sceglie il file da aprire e a quanto arriva il montepremi
FILE *ndomanda(int i, int *mdimoney){
	switch(i){
		case 1:
			*mdimoney=0;
			return fopen("1liv.txt", "r");
		case 2:
			*mdimoney=500;
			return fopen("2liv.txt", "r");
		case 3:
			*mdimoney=1000;
			return fopen("3liv.txt", "r");
		case 4:
			*mdimoney=1500;
			return fopen("4liv.txt", "r");
		case 5:
			*mdimoney=2000;
			return fopen("5liv.txt", "r");
		case 6:
			*mdimoney=3000;
			return fopen("6liv.txt", "r");
		case 7:
			*mdimoney=5000;
			return fopen("7liv.txt", "r");
		case 8:
			*mdimoney=7000;
			return fopen("8liv.txt", "r");
		case 9:
			*mdimoney=10000;
			return fopen("9liv.txt", "r");
		case 10:
			*mdimoney=15000;
			return fopen("10liv.txt", "r");
		case 11:
			*mdimoney=20000;
			return fopen("11liv.txt", "r");
		case 12:
			*mdimoney=30000;
			return fopen("12liv.txt", "r");
		case 13:
			*mdimoney=70000;
			return fopen("13liv.txt", "r");
		case 14:
			*mdimoney=150000;
			return fopen("14liv.txt", "r");
		case 15:
			*mdimoney=300000;
			return fopen("15liv.txt", "r");
	}
}
