#include "rw_file.h"

int main(int argc, char *argv[])
{
    char *file_name = argv[2];
    auto w_f = r_w::op_file();
    std::string s;
    int _f = w_f.o_file(file_name);

    while (true)
    {
        std::getline(std::cin, s);
        w_f.w_file(s);
        if (s == quit_file)
        {
            w_f.c_file(_f);
            return EXIT_SUCCESS;
        }
    }

    return EXIT_FAILURE;
}