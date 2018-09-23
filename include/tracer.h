

#ifndef TRACER_H
#define TRACER_H
#define DEBUG
#ifdef DEBUG
    #include <iostream>
    #include <sstream>
    #include <cstdlib>
    #include <stdarg.h>
    #include <utility>
    #include <iostream>
    #include <cxxabi.h>
    #include <execinfo.h>
	#include "libexport.h"
    #define _nl std::endl
    extern thread_local int debug_counter;
    extern thread_local int debug_thread_id;
    extern int global_proc_rank;
//    int _getFuncName(char* &funcName, int &funcLength, int skipDepth);
    namespace trackerc{
		EXPORT_SYMBOL void trace_print_func_data(std::stringstream &stream, int first_arg);
		std::string trace_prefix(int skipDepth = 0);
		template<typename First, typename ...Rest>
		EXPORT_SYMBOL void trace_print_func_data(std::stringstream &stream, int first_arg, First && first, Rest && ...rest){
			stream << ((first_arg)?"":",") << first;
			trace_print_func_data(stream, 0,std::forward<Rest>(rest)...);
		}
		template<typename ...Rest>
		EXPORT_SYMBOL void trace_print_func(const char* funcName, Rest && ...rest){
			std::stringstream stream;
			stream << trace_prefix(1) << "["<<funcName << "]"<<": (";
			trace_print_func_data(stream, 1, std::forward<Rest>(rest)...);
			std::cout<<stream.str();
		}
	//    template<typename ...Rest>
	//    void trace_print_func(Rest && ...rest){
	//        std::stringstream stream;
	//        stream << trace_prefix() << "(";
	//        trace_print_func_data(stream, 1, std::forward<Rest>(rest)...);
	//        std::cout<<stream.str();
	//    }
    }
    #define _T(x) { std::stringstream stream; stream << trackerc::trace_prefix() << x << _nl; std::cout << stream.str(); }
    #define _TF(...) trackerc::trace_print_func(__VA_ARGS__)
#else
    #define _nl
    #define _T(x)
    #define _TF(...)
#endif


#endif // ndef TRACER_H
