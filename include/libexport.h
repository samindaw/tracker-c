/*
 * libexport.h
 *
 *  Created on: Sep 23, 2018
 *      Author: samindaw
 */

#ifndef INCLUDE_LIBEXPORT_H_
#define INCLUDE_LIBEXPORT_H_
#if defined(WIN32)
    //  Microsoft
	#ifdef EXPMODULE
		#define EXPORT_SYMBOL __declspec(dllexport)
	#else
		#define EXPORT_SYMBOL __declspec(dllimport)
	#endif
#elif defined(__GNUC__)
    //  GCC
	#define EXPORT_SYMBOL __attribute__ ((__visibility__("default")))
    //#define EXPORT_SYMBOL __attribute__((visibility("default")))
    #//define IMPORT
#else
    //  do nothing and hope for the best?
    #define EXPORT_SYMBOL
    #pragma warning Unknown dynamic link import/export semantics.
#endif


#endif /* INCLUDE_LIBEXPORT_H_ */
