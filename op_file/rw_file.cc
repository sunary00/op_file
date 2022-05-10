#include "rw_file.h"
#include <sstream>

namespace r_w
{

    op_file::op_file()
    {

        _buf = new char[bufsize];
        if (_buf == nullptr)
        {
            std::cout << " Buf Initialization failed" << std::endl;
        }
        memset(_buf, 0, bufsize);
    }

    op_file::~op_file()
    {

        if (_buf != nullptr)
        {
            delete[] _buf;
        }
    }
    // open file
    int op_file::o_file(char *n_f)
    {
        _fd = open(n_f, O_CREAT | O_APPEND | O_RDWR, S_IREAD | S_IWRITE);
        if (-1 == _fd)
        {
            std::cout << "Can't open " << n_f << " because error: " << errno << std::endl;
            exit(errno);
        }
        return _fd;
    }

    // close file
    void op_file::c_file(int _fd)
    {
        if (-1 != _fd)
        {
            close(_fd);
        }
    }

    // read file
    int op_file::r_file(int _fd)
    {
        ssize_t f_read = -1;

        do
        {
            f_read = read(_fd, _buf, BUFSIZ);
        } while (f_read != 0);

        while (true)
        {
            f_read = read(_fd, _buf, BUFSIZ);
            // std::string m = std::string(_buf, _buf + f_read);
            
            // stream begin
            std::stringstream m;
            m.write(_buf, f_read);
            // stream end

            if (m.str() == quit_file)
            {
                std::cout << "file have done" << std::endl;
                return EXIT_SUCCESS;
            }
            else if (f_read == 0)
            {
                sleep(2);
                continue;
            }
            std::cout << m.str() << std::endl;
        }
        return EXIT_FAILURE;
    }

    // write file
    void op_file::w_file(const std::string &s)
    {
        write(_fd, s.c_str(), s.size());
    }

}
