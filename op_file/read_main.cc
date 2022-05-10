#include "rw_file.h"

int main(int argc, char *argv[])
{
    char *file_name = argv[2];
    auto op = r_w::op_file();
    int _f = op.o_file(file_name);
    op.r_file(_f);
    op.c_file(_f);

    return EXIT_SUCCESS;
}