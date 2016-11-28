#ifndef MY_BASE_COMMON_DLL_EXPORT_MACRO_H
#define MY_BASE_COMMON_DLL_EXPORT_MACRO_H

#if COMPILING_DLL
#define DLLEXPORT __declspec(dllexport)
#endif 

#if USE_DLL
#define DLLEXPORT __declspec(dllimport)
#endif

#ifndef  DLLEXPORT
#define DLLEXPORT 
#endif 

#endif //MY_BASE_COMMON_DLL_EXPORT_MACRO_H
