#pragma once

#if defined(__tex_dll)
	#if defined(_WIN32)
		#if defined(__tex_build_dll)
			#define TEX_DLL __declspec(dllexport)
		#else
			#define TEX_DLL __declspec(dllimport)
		#endif
	#elif defined(__GNUC__) && defined(__tex_build_dll)
		#define TEX_DLL __attribute__((visibility("default")))
	#else
		#define TEX_DLL
	#endif
#else
	#define TEX_DLL
#endif
