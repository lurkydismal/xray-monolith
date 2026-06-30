#pragma once

#ifdef _MSC_VER
#define TRY __try
#define EXCEPT( x ) __except ( x )
#else
#define TRY
#define EXCEPT( x ) if ( 0 )
#endif
