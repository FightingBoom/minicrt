// iostream.cpp

#include "minicrt.h"
#include "iostream"

#ifdef WIN32
#include <Windows.h>
#endif

namespace std
{

stdout_stream::stdout_stream() : ofstream()
{
    fp = stdout;
}

stdout_stream cout;

ofstream::ofstream() : fp(0)
{

}

ofstream::ofstream(const char *filename, ofstream::openmode md)
    : fp(0)
{
    open(filename, md);
}

ofstream::~ofstream()
{
    close();
}

ofstream& ofstream::operator<<(char c)
{
    fputc(c, fp);
    return *this;
}

ofstream& ofstream::operator<<(int n)
{
    fprintf(fp, "%d", n);
    return *this;
}

ofstream& ofstream::operator<<(const char * str)
{
    fprintf(fp, "%s", str);
    return *this;
}

ofstream& ofstream::operator<<(ofstream& (*manip)(ofstream&))
{
    return manip(*this);
}

void ofstream::open(const char *filename, ofstream::openmode md)
{
    char mode[4];
    close();

    switch (md)
    {
        case out | trunc:
            strcpy(mode, "w");
            break;
        case out | in | trunc:
            strcpy(mode, "w+");
        case out | trunc | binary:
            strcpy(mode, "wb");
            break;
        case out | in | trunc | binary:
            strcpy(mode, "wb+");
    }

    fp = fopen(filename, mode);
}

void ofstream::close()
{
    if (fp)
    {
        fclose(fp);
        fp = 0;
    }
}

ofstream& ofstream::write(const char *buf, unsigned size)
{
    fwrite(buf, 1, size, fp);
    return *this;
}


}


/*
$gcc -c -fno-builtin -nostdlib -fno-stack-protector entry.c malloc.c stdio.c string.c printf.c atexit.c
$g++ -c -nostdinc++ -fno-rtti -fno-exceptions -fno-builtin -nostdlib -fno-stack-protector crtbegin.cpp crtend.cpp c    tor.cpp new_delete.cpp sysdep.cpp iostream.cpp sysdep.cpp
$ar -rs minicrt.a malloc.o printf.o stdio.o string.o ctor.o atexit.o iostream.o new_delete.o sysdep.o


$g++ -c -nostdinc++ -fno-rtti -fno-exceptions -fno-builtin -nostdlib -fno-stack-protector test.cpp
$ld -static -e mini_crt_entry entry.o crtbegin.o test.o minicrt.a crtend.o -o test

*/

