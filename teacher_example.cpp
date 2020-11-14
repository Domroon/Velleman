
#include <cstdlib>
#include <windows.h>
#include <iostream>
#include<time.h>
#include <unistd.h>
#include<stdio.h>
#include "k8055.cpp"
#include<stdlib.h>

using namespace std;


// HAUPTPROGRAMM 
// HIER WERDEN SIE IHRE PROGRAMME SCHREIBEN

int main(int argc, char *argv[])
{
    int CardAddress;
    int dataOut1, dataOut2;
    int dataIn1, dataIn2;
    int h;
int foundDLL = 0;

   //BOARD WIRD INITIALISIERT!!
   
    h = init();
	if (!h)
	{
		printf("DLL found");
		foundDLL = 1;
	}
	else
	{
			printf("DLL not found");return 0;

	}
	if (foundDLL)
	{
		h = OpenDevice(0);
		if (h == 0)
		{
			printf("Card 0 opened" );
		}
		else
		{
			printf("\nCard 0 not opened" ); return 0;
		}
	}



// AB HIER STEHT IHR CODE!!
//HIER EIN  BEISPIEL VON MIR


	if (foundDLL)
	
	{   
		double time1=0.0, tstart;      // time measurment variables
		clock_t start_t, end_t, total_t,startnew_t;
		float strecke;
		int Start,Zug_start;
		Start=0;
		cout <<endl << "Karte testen"<<endl;

		// Karte wird getestet

		for (int j=1;j<9;j++){		
		  	
			  SetDigitalChannel(j);
        for (int i=0;i<50;i++)
		
			ClearDigitalChannel(j);
		}
		
		int Rundenanzahl;
	
		// Beschreibung und Daten einlesen
			
			cout <<endl << "Berechnung der Durchschnittsgeschwindigkeit der Bahn"<<endl;
			cout <<endl << "Input 5 druecken fuer Karte schließen und Programm beenden"<<endl<<" Input 2 ist der Bewegungssensor"<<endl;
       		cout << "Bitte geben Sie die Laenge der Strecke in Metern"<<endl<<endl;
			cin >> strecke;
			cout << "Bitte Anzahl der Fahrtrunden eingeben (Takte bei Input 2 plus ein Takt zum Starten der Zeitmessung)"<<endl;
			cin>>Rundenanzahl;
			cout << endl;
			int start1=0;
			int count_alt=0;
		// Programmstart
		cout<<"Druecken Sie jetzt den Input 2 als Sensor"<<endl;
		do {
				if(ReadDigitalChannel(5)==1) return 0;	
				
// ZAEHLE EINGANGSTAKTE -- Input 2 ist der Sensor der die Fahrtrunden zählt

				count = ReadCounter(2); 
				if (count > count_alt) {				
				cout << "Durchlauf Nummer " << count << endl;
				count_alt = count;
			}
				if(count==1)
				
				// Stoppuhr starten
				
				{ if (start1==0)
				 start_t = clock();
				 start1=1;

				}
				
				// Zeit berechnen nach Fahrtrunden
				
				if(count==Rundenanzahl)  
				 {
				 	end_t=clock();
					total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
					Rundenanzahl=count - 1;
					Start = 1;
			}

		 
			 } while(Start==0);
			 
		// Ausgabe 
		
		float geschwindigkeit=strecke*Rundenanzahl/total_t;
		 cout <<endl << "INSGESAMT    "<< count <<"  TAKTE"<< endl<<"Zeit in sec ="<<total_t<<endl<<"Strecke = "<< strecke<<endl;
		 cout << endl<<Rundenanzahl << " Durchlaeufe am Sensor "<<endl<<"Geschwindigkeit (s/t) = "<<strecke <<"*"<<Rundenanzahl<<"/"<<total_t<<"="<< geschwindigkeit<<"m/s"<<endl<<geschwindigkeit*3.6<<"km/h"<<endl;
		 ResetCounter(2); 
		 ClearAllDigital(); 
         CloseDevice();
         FreeLibrary(hDLL);
         system("pause");
    }
    
}


