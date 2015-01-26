// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MOTLD_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MOTLD_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef MOTLD_EXPORTS
#define MOTLD_API __declspec(dllexport)
#else
#define MOTLD_API __declspec(dllimport)
#endif

// This class is exported from the motld.dll
class MOTLD_API Cmotld {
public:
	Cmotld(void);
	// TODO: add your methods here.
};

extern MOTLD_API int nmotld;

MOTLD_API int fnmotld(void);
