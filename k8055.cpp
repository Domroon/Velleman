// ALLE BOARD-FUNKTIONEN AUFGELISTET UND DEFINIERT!!

typedef void(CALLBACK* t_func)(int );
typedef void(CALLBACK* t_func0)();
typedef int(CALLBACK* t_func1)();
typedef void(CALLBACK* t_func2)(int *, int *);
typedef void(CALLBACK* t_func3)(int , int );
typedef int(CALLBACK* t_func4)(int );
typedef bool(CALLBACK* t_func5)(int );

t_func4 OpenDevice;
t_func0 CloseDevice;
t_func0 Version_;
t_func4 ReadAnalogChannel;
t_func2 ReadAllAnalog;
t_func3 OutputAnalogChannel;
t_func3 OutputAllAnalog;
t_func ClearAnalogChannel; 
t_func0 ClearAllAnalog;
t_func SetAnalogChannel; 
t_func0 SetAllAnalog;
t_func WriteAllDigital;
t_func ClearDigitalChannel;
t_func0 ClearAllDigital;
t_func SetDigitalChannel;
t_func0 SetAllDigital;
t_func5 ReadDigitalChannel;
t_func1 ReadAllDigital;
t_func4 ReadCounter; 
t_func ResetCounter; 
HINSTANCE hDLL;
int foundDLL = 0;
int init();
int count;

using namespace std;

// FUNKTION ZUR BOARD-AKTIVIERUNG (ALLE FUNKTIONEN WERDEN AKTIVIERT)!!

int init()
{
	hDLL = LoadLibrary("K8055d.dll");         // DIE DLL-DATEI SOLL IN DEM GLEICHEN VERZEICHNISS LIEGEN WO DAS HAUPTPROGRAMM IST
	
	
	if (hDLL != NULL)
	{
		OpenDevice = (t_func4) GetProcAddress(hDLL, "OpenDevice");
		ReadCounter = (t_func4) GetProcAddress(hDLL, "ReadCounter");
		ResetCounter = (t_func) GetProcAddress(hDLL, "ResetCounter");
		if (!OpenDevice)		
		{						// handle the error
			FreeLibrary(hDLL);	
			return -2;
		}
		CloseDevice = (t_func0) GetProcAddress(hDLL, "CloseDevice");
		if (!CloseDevice)
		{						// handle the error
			FreeLibrary(hDLL);	
			return -2;
		}
		ReadAnalogChannel = (t_func4) GetProcAddress(hDLL, "ReadAnalogChannel");
		if (!ReadAnalogChannel)
		{						// handle the error
			FreeLibrary(hDLL);	
			return -2;
		}
		ReadAllAnalog = (t_func2) GetProcAddress(hDLL, "ReadAllAnalog");
		if (!ReadAllAnalog)
		{						// handle the error
			FreeLibrary(hDLL);	
			return -2;
		}
		OutputAnalogChannel = (t_func3) GetProcAddress(hDLL, "OutputAnalogChannel");
		if (!OutputAnalogChannel)
		{						// handle the error
			FreeLibrary(hDLL);	
			return -2;
		}
		OutputAllAnalog = (t_func3) GetProcAddress(hDLL, "OutputAllAnalog");
		if (!OutputAllAnalog)		
		{						// handle the error
			FreeLibrary(hDLL);	
			return -2;
		}
		ClearAnalogChannel = (t_func) GetProcAddress(hDLL, "ClearAnalogChannel");
		if (!ClearAnalogChannel)
		{						// handle the error
			FreeLibrary(hDLL);	
			return -2;
		}
		ClearAllAnalog = (t_func0) GetProcAddress(hDLL, "ClearAllAnalog");
		if (!ClearAllAnalog)
		{						// handle the error
			FreeLibrary(hDLL);	
			return -2;
		}
		SetAnalogChannel = (t_func) GetProcAddress(hDLL, "SetAnalogChannel");
		if (!SetAnalogChannel)
		{						// handle the error
			FreeLibrary(hDLL);	
			return -2;
		}
		SetAllAnalog = (t_func0) GetProcAddress(hDLL, "SetAllAnalog");
		if (!SetAllAnalog)
		{						// handle the error
			FreeLibrary(hDLL);	
			return -2;
		}
		WriteAllDigital = (t_func) GetProcAddress(hDLL, "WriteAllDigital");
		if (!WriteAllDigital)
		{						// handle the error
			FreeLibrary(hDLL);	
			return -2;
		}
		ClearDigitalChannel = (t_func) GetProcAddress(hDLL, "ClearDigitalChannel");
		if (!ClearDigitalChannel)
		{						// handle the error
			FreeLibrary(hDLL);	
			return -2;
		}
		ClearAllDigital = (t_func0) GetProcAddress(hDLL, "ClearAllDigital");
		if (!ClearAllDigital)		
		{						// handle the error
			FreeLibrary(hDLL);	
			return -2;
		}
		SetDigitalChannel = (t_func) GetProcAddress(hDLL, "SetDigitalChannel");
		if (!SetDigitalChannel)
		{						// handle the error
			FreeLibrary(hDLL);	
			return -2;
		}
		SetAllDigital = (t_func0) GetProcAddress(hDLL, "SetAllDigital");
		if (!SetAllDigital)		
		{						// handle the error
			FreeLibrary(hDLL);	
			return -2;
		}
		ReadDigitalChannel = (t_func5) GetProcAddress(hDLL, "ReadDigitalChannel");
		if (!ReadDigitalChannel)
		{						// handle the error
			FreeLibrary(hDLL);	
			return -2;
		}
		ReadAllDigital = (t_func1) GetProcAddress(hDLL, "ReadAllDigital");
		if (!ReadAllDigital)
		{						// handle the error
			FreeLibrary(hDLL);	
			return -2;
		}
		Version_ = (t_func0) GetProcAddress(hDLL, "Version");
		if (!Version_)
		{						// handle the error
			FreeLibrary(hDLL);	
			return -2;
		}
		return 0;				// ok
	}       
	return -1;					// error load DLL
}

