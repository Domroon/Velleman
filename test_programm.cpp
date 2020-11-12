
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
		
		cout <<endl << "Karte testen"<<endl;
		// Karte wird getestet	 
		// Ausgabe 
		 ResetCounter(2); 
		 ClearAllDigital(); 
         CloseDevice();
         FreeLibrary(hDLL);
         system("pause");
    }
    
}


