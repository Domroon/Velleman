#include <cstdlib>
#include <windows.h>
#include <iostream>
#include <time.h>
#include <unistd.h>
#include<stdio.h>
#include "k8055.cpp"
#include<stdlib.h>

using namespace std;


int board_init(int h, int foundDLL)
{
	   
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
			printf("Card 0 opened\n");
			return foundDLL;
		}
		else
		{
			printf("\nCard 0 not opened" ); return 0;
		}
	}
}

bool capture_input(int input)
{
	bool capture = false;
	do
	{
		capture = ReadDigitalChannel(input);
		
	} while(capture != true);
}

int main(int argc, char *argv[])
{
    int CardAddress;
    int dataOut1, dataOut2;
    int dataIn1, dataIn2;
    int h;
	int foundDLL = 0;

	if (board_init(h, foundDLL)) //Function initialize the board
	{   
		time_t timer;
		double t_start, t_stop, t_diff;
		int sensor_channel;
		unsigned int sleep_time = 1; //in seconds
		
		cout << endl << "Welcome to train-speed measure" << endl;
		cout << "What Input-Channel to you want to use to detect the train? (1-4)" << endl;
		cin >> sensor_channel;
		
		cout << "Press Input " << sensor_channel << " to start the stopwatch" << endl;
		capture_input(sensor_channel); //waiting for sensor interaction
		t_start = time(&timer);
		sleep(sleep_time); //digital_input needs time to reset
		
		cout << "Press Input " << sensor_channel << " again to stop the stopwatch" << endl;
		capture_input(sensor_channel); //waiting for sensor interaction
		t_stop = time(&timer);
		
		t_diff = t_stop - t_start;
		cout << t_diff << " s" << endl;
		 
		 ClearAllDigital(); 
         CloseDevice();
         FreeLibrary(hDLL);
         //system("pause");
    }
}
