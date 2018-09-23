#include "tracer.h"

#ifdef DEBUG

		#include <mutex>
		#define max_frames 63
    namespace trackerc{
		int debug_thread_id_counter = 0;
		std::mutex debug_thread_id_counter_m;
		int get_unique_thread_id(){
			int id;
			debug_thread_id_counter_m.lock();
			id = debug_thread_id_counter++;
			debug_thread_id_counter_m.unlock();
			return id;
		}
		thread_local int debug_counter = 0;
		int global_proc_rank;
		thread_local int debug_thread_id = get_unique_thread_id();
		void trace_print_func_data(std::stringstream &stream, int first_arg){
			stream << ")"<<_nl;
		}
		int _getFuncName(char* &funcName, size_t &funcLength, int skipDepth)
		{
			skipDepth++; //include this function depth
			funcLength = 0;

			char* funcname = (char *)malloc(funcLength);

			void* addrlist[max_frames+1];
			int addrlen = backtrace(addrlist, sizeof(addrlist) / sizeof(void*));
			char **messages = backtrace_symbols(addrlist, skipDepth+1);
			int k=skipDepth;
			char *begin_name = 0, *begin_offset = 0, *end_offset = 0;

			for (char *p = messages[k]; *p; ++p)
			{
				if (*p == '(') begin_name = p;
				else if (*p == '+') begin_offset = p;
				else if (*p == ')' && begin_offset)
				{
					end_offset = p;
					break;
				}
			}

			if (begin_name && begin_offset && end_offset && begin_name < begin_offset)
			{
				*begin_name++ = '\0';*begin_offset++ = '\0';*end_offset = '\0';
				int status;
				char* ret = abi::__cxa_demangle(begin_name, funcname, &funcLength, &status);
				if (status == 0){
					//Remove parameters section
					begin_name = 0;
					for (char *p = ret; *p; ++p)
						if (*p == '(')
						{
							begin_name = p;
							break;
						}
					*begin_name++ = '\0';
					funcName = ret;
				}
			}
			free(messages);
			return addrlen - skipDepth;
		}
		std::string trace_prefix(int skipDepth){
			std::stringstream stream;
			debug_counter++;
			stream << "TRACE: " << "[" << global_proc_rank << ":"<< debug_thread_id <<"] ("<< debug_counter << ")\t";
			char *funcname;
			size_t len;
			int addrlen = _getFuncName(funcname, len, skipDepth+1);
			for(int i=0; i<addrlen; i++) stream<<"  ";
			if (len)
			{
				stream<<funcname<<": ";
				free(funcname);
			} else
				stream<<"main"<<": ";
			return stream.str();
		}
    }
#endif
