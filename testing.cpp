
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
		int input1 = 0, input2 = 0, input3 = 0;
		do
		{
			input1 = ReadDigitalChannel(1); 
			
			input2 = ReadDigitalChannel(2);
	
			if(input1 == 1)
			{
				SetDigitalChannel(1);
			}
			
			if(input2 == 1)
			{
				ClearAllDigital(); 
			}
			
		} while(1 == 1);
	
		
		 ResetCounter(2); 
		 system("Pause");
		 
		 ClearAllDigital(); 
         CloseDevice();
         FreeLibrary(hDLL);
         system("pause");
    }
    
}


