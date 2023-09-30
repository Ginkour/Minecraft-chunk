#include "OpenGL.h"
int main(int argc, char** argv)
{
    // Get the number of available CPU cores
    unsigned int numThreads = std::thread::hardware_concurrency();
    logprint("Number of CPU threads: %d \n", numThreads);
    mge::OpenGL gl;
    gl.Run();
    return 0;
}