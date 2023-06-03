#ifndef PCH_H
#define PCH_H

#include "framework.h"

extern bool g_running;
extern HWND g_window;


//define namespaces
using namespace std::chrono;
using namespace std::chrono_literals;

//defines
using u64 = uint64_t;
using i64 = int64_t;
using u32 = uint32_t;
using i32 = int32_t;
using u16 = uint16_t;
using i16 = int16_t;
using u8 = uint8_t;
using i8 = int8_t;
using cc = const char;
using ccp = cc*;
using fp = float_t;
using db = double_t;

template <typename t>
	requires std::is_function_v<t>
using fnptr = std::add_pointer_t<t>;




#endif 
