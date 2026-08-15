#pragma once

#define WIDEN2( x ) L##x
#define WIDEN( x ) WIDEN2( x )

#define PIX_EVENT( Name ) dxPixEventWrapper pixEvent##Name( WIDEN( #Name ) )

class dxPixEventWrapper {
public:
    dxPixEventWrapper( LPCWSTR wszName );
    ~dxPixEventWrapper();
};
