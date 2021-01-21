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

void startscreen()
{
	
	cout << endl;
	cout << "**************************************************" << endl;
	cout << "*        Automatic agitator Rotana               *" << endl;
	cout << "*------------------------------------------------*" << endl;
	cout << "*     S1: Automatic Mode - S2: Manual Mode         *" << endl;
	cout << "*   S3: Right run - S4: Left run - S5: Stop      *" << endl;
	cout << "**************************************************" << endl;
	cout << " " << endl;  
}

int ReadAllChannel()
{
	bool s1, s2, s3, s4, s5;
	s1 = ReadDigitalChannel(1); // Auto
	s2 = ReadDigitalChannel(2); // Hand
	s3 = ReadDigitalChannel(3); // Hand Rechts
	s4 = ReadDigitalChannel(4); // Hand Links
	s5 = ReadDigitalChannel(5); // Stopp
	
	if(s1)
	{
		return 1;
	}
	if(s2)
	{
		return 2;
	}
	if(s3)
	{
		return 3;
	}
	if(s4)
	{
		return 4;
	}
	if(s5)
	{
		return 5;
	}
}

double get_time()
{
	time_t timer;
	double get_time = 0;
	get_time = time(&timer);
	return get_time;
}

void right_run(double time, bool automatic_mode)
{
	double start_time = 0;
	double end_time = 0;
	double t_diff = 0;
	
	start_time = get_time();
	end_time = 0;
	t_diff = 0;
	printf("right run\n");
	SetDigitalChannel(1);
	while(t_diff != time && automatic_mode == true)
	{
		end_time = get_time();
		t_diff = end_time - start_time;
		if(ReadAllChannel() == 5)
		{
			ClearAllDigital();
			break;
		}
	}
	
	while(automatic_mode == false)
	{
		if(ReadAllChannel() == 5)
		{
			ClearAllDigital();
			break;
		}
	}
	
	if(automatic_mode == true)
	{
		ClearDigitalChannel(1);
	}
}

void left_run(double time, bool automatic_mode)
{
	double start_time = 0;
	double end_time = 0;
	double t_diff = 0;
	
	start_time = get_time();
	end_time = 0;
	t_diff = 0;
	printf("left run\n");
	SetDigitalChannel(2);
	while(t_diff != time && automatic_mode == true)
	{
		end_time = get_time();
		t_diff = end_time - start_time;
		if(ReadAllChannel() == 5)
		{
			ClearAllDigital();
			break;
		}
	}
	
	while(automatic_mode == false)
	{
		if(ReadAllChannel() == 5)
		{
			ClearAllDigital();
			break;
		}
	}
	
	if(automatic_mode == true)
	{
		ClearDigitalChannel(2);
	}
}

void automatic_mode(double time, double stir_total_time)
{
	//The many if-querys are necessary to stop the agitator reliable
	printf("**automatic mode**\n");
	printf("\n");
	sleep(0.1); //input need time to reset
	
	double start_stir_time = get_time();
	double end_stir_time = 0;
	double stir_time_diff = 0;
	
	while(ReadAllChannel() != 5)
	{
		
		right_run(time, true);
		
		if(ReadAllChannel() == 5)
		{
			break;
		}
		
		left_run(time, true);
		
		if(ReadAllChannel() == 5)
		{
			break;
		}
		
		end_stir_time = get_time();
		stir_time_diff = end_stir_time - start_stir_time;
		
		if(stir_time_diff >= stir_total_time)
		{
			break;
		}
	}
}

void manual_mode()
{
	bool automatic_mode = false;
	while(ReadAllChannel() != 1 && automatic_mode == false)
	{
		printf("**manual mode**\n");
		while(ReadAllChannel() != 5)
		{
			if(ReadAllChannel() == 3)
			{
				right_run(0.1, false);
				printf("stop\n");
				sleep(1);
				break;
			}
			
			if(ReadAllChannel() == 4)
			{
				left_run(0.1, false);
				printf("stop\n");
				sleep(1);
				break;
			}
			
			if(ReadAllChannel() == 1)
			{
				automatic_mode = true;
				break;
			}
		}
		ClearAllDigital();
		startscreen();
		sleep(1);
		
		if(ReadAllChannel() == 1)
		{
			automatic_mode = true;
		}
	}
}

int main(int argc, char *argv[])
{
    int CardAddress;
    int dataOut1, dataOut2;
    int dataIn1, dataIn2;
    int h;
	int foundDLL = 0;
	int input;

	if (board_init(h, foundDLL)) //Function initialize the board
	{   
		startscreen();
		
		ClearAllDigital();
		
		while(1 == 1) //main loop
		{
			if(ReadAllChannel() == 1)
			{
				automatic_mode(2, 10);
				printf("stop\n");
				startscreen();
				sleep(1); //input need time to reset
			}
			if(ReadAllChannel() == 2)
			{
				manual_mode();
				sleep(1); //input need time to reset
			}
		}
		
		ClearAllDigital(); 
        CloseDevice();
        FreeLibrary(hDLL);
        //system("pause");
    }
}
