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
		ClearAllDigital();
		while(1 == 1) //main loop
		{
			if(ReadAllChannel() == 1)
			{
				printf("1");
				sleep(1);
			}
			if(ReadAllChannel() == 2)
			{
				printf("2");
				sleep(1);
			}
			if(ReadAllChannel() == 3)
			{
				printf("3");
				sleep(1);
			}
			if(ReadAllChannel() == 4)
			{
				printf("4");
				sleep(1);
			}
			if(ReadAllChannel() == 5)
			{
				printf("5");
				sleep(1);
			}
		}
		
		ClearAllDigital(); 
        CloseDevice();
        FreeLibrary(hDLL);
        //system("pause");
    }
}
