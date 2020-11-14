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
		double round_length;
		double speed;
		
		//Information
		cout << endl << "Welcome to train-speed measure" << endl;
		cout << "This program can measure the speed from a train thats drives in a circle" << endl;
		
		//get data from user
		cout << "What Input-Channel to you want to use to detect the train? (1-4)" << endl;
		cin >> sensor_channel;
		cout << "How long is one round in [cm]?" << endl;
		cin >> round_length;
		
		//start stopwatch
		cout << endl << "Waiting for train at input-channel: " << sensor_channel << endl;
		capture_input(sensor_channel); //waiting for sensor interaction
		t_start = time(&timer);
		cout << endl << "Detect train at input-channel: " << sensor_channel << endl;
		sleep(sleep_time); //digital_input needs time to reset
		
		//stop stopwatch
		cout << endl  << "Waiting for train at input-channel: " << sensor_channel << endl;
		capture_input(sensor_channel); //waiting for sensor interaction
		t_stop = time(&timer);
		cout << endl  << "Detect train at input-channel: " << sensor_channel << endl;
		
		//calculate time of one round
		t_diff = t_stop - t_start;
		cout << t_diff << " s" << endl;
		
		//calculate speed
		round_length = round_length/100; //convert cm in m
		round_length = round_length/1000; //convert m in km
		t_diff = t_diff/3600; //convert s in h
		speed = round_length/t_diff;
		
		//Output
		cout << endl << "Speed: " << speed << " km/h" << endl;
		
		ClearAllDigital(); 
        CloseDevice();
        FreeLibrary(hDLL);
        //system("pause");
    }
}
