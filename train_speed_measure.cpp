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
	cout << "waiting for the train ..." << endl;
	bool capture = false;
	do
	{
		capture = ReadDigitalChannel(input);
		
	} while(capture != true);
	cout << "train detected!" << endl;
}

double get_time()
{
	time_t timer;
	double get_time = 0;
	get_time = time(&timer);
	return get_time;
}

double calculate_speed(double start_time, double end_time, double round_length)
{
	double speed = 0;
	double t_diff = 0;
	
	round_length = round_length/100; 	//convert cm in m
	round_length = round_length/1000; 	//convert m in km
	
	
	//calculate time of one round
	t_diff = end_time - start_time;
	t_diff = t_diff/3600; //convert s in h
	
	//calculate speed
	speed = round_length/t_diff;
	
	return speed;
}

void show_speed(double speed)
{
	cout << endl << "Speed: " << speed << " km/h" << endl;
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
		double first_round_start_time, start_time, end_time;
		
		//Information
		cout << endl << "Welcome to train-speed measure" << endl;
		cout << "This program can measure the speed from a train thats drives in a circle" << endl;
		
		//get data from user
		cout << "What Input-Channel to you want to use to detect the train? (1-4)" << endl;
		cin >> sensor_channel;
		cout << "How long is one round in [cm]?" << endl;
		cin >> round_length;
		
		//start stopwatch
		capture_input(sensor_channel);
		first_round_start_time = get_time();
		sleep(sleep_time); //digital_input needs time to reset
		
		//stop stopwatch
		capture_input(sensor_channel);
		end_time = get_time();
		
		//calculate speed
		speed = calculate_speed(first_round_start_time, end_time, round_length);
		
		//show speed
		show_speed(speed);
		
		while(1 == 1)
		{
			start_time = end_time; //take last stop time as start-time
			
			//stop stopwatch when a train is detected
			capture_input(sensor_channel);
			end_time = get_time();
			sleep(sleep_time); //digital_input needs time to reset
			
			//calculate speed
			speed = calculate_speed(start_time, end_time, round_length);
			
			//show speed
			show_speed(speed);
		}
		
		ClearAllDigital(); 
        CloseDevice();
        FreeLibrary(hDLL);
        //system("pause");
    }
}
