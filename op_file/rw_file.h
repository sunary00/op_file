#pragma once

#ifndef RW_H
#define RW_H

#include <fcntl.h>    // open/close
#include <sys/stat.h> //open share
#include <cstdio>     // read/write
#include <unistd.h>   //sleep
#include <cerrno>     // std error
#include <iostream>
#include <cstring>


const int bufsize = 4096;

const std::string quit_file = "quit";

namespace r_w
{

    // const char *file_name = "shm_file";

    // A class to operate file.
    class op_file
    {

    public:
        op_file();
        ~op_file();

        // open file
        int o_file(char *n_f);

        // close file
        void c_file(int _fd);

        // read file
        int r_file(int _fd);

        // write file
        void w_file(const std::string &s);

    private:
        int _fd = -1;
        char *_buf;
    };
}

#endif
