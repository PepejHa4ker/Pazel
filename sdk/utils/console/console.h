//
// Created by pepej on 09.06.2022.
//

#ifndef PAZEL_CONSOLE_H
#define PAZEL_CONSOLE_H

#include <windows.h>
#include <iostream>

class console {
public:
    void initialize( const char* title );
    void release( );

    template <typename ... Args>
    void log( char const* const format, Args const& ... args ) {
#ifdef _DEBUG
        printf( format, args ... );
#endif
    }
};

extern console g_console;

#endif //PAZEL_CONSOLE_H
