#include <cstdlib>
#include <windows.h>
#include <iostream>
#include <time.h>
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
		printf("DLL found\n");
		foundDLL = 1;
	}
	else
	{
			printf("DLL not found\n");return 0;

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


	if (foundDLL)
	
	{   
		time_t timer;
		double t_start, t_stop, t_diff;
		int user_input;
		cout << endl << "Welcome to train-speed measure" << endl;
		cout << "Press Enter something to start stopwatch" << endl;
		cin >> user_input;
		t_start = time(&timer);
		cout << "Press Enter something again to stop stopwatch" << endl;
		cin >> user_input;
		t_stop = time(&timer);
		t_diff = t_stop - t_start;
		cout << t_diff << " s" << endl;
		
		 ResetCounter(2); 
		 ClearAllDigital(); 
         CloseDevice();
         FreeLibrary(hDLL);
         //system("pause");
    }
    
}
