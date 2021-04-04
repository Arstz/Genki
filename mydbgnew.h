#pragma once

#ifdef _DEBUG
#define MYDEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define MYDEBUG_NEW
#endif 