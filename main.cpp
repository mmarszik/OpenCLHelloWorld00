#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <string>

//#define CL_USE_DEPRECATED_OPENCL_2_0_APIS
#include <CL/cl.hpp>

using utyp = unsigned int;
constexpr utyp SIZE = 100000000;

int main(int argc, char *argv[] ) {
    std::vector< cl::Platform > platforms;

    assert( CL_SUCCESS == cl::Platform::get( &platforms ) );
    std::cout << "Platforms.size == " << platforms.size() << std::endl;
    assert( platforms.size() > 0 );

    auto platform = platforms.front();
    std::vector<cl::Device> devices;
    platform.getDevices(CL_DEVICE_TYPE_ALL,&devices);
    std::cout << "devices.size == " << devices.size() << std::endl;
    assert( devices.size() > 0 );

    auto device = devices.front();
    auto vendor = device.getInfo<CL_DEVICE_VENDOR>();
    auto version = device.getInfo<CL_DEVICE_VERSION>();

    std::ifstream hello_world_00("hello_world.cl");
    std::string src( std::istreambuf_iterator<char>(hello_world_00), (std::istreambuf_iterator<char>()) );
    std::cout << "src: " << std::endl << src << std::endl;

    cl::Program::Sources sources = { std::pair<const char*,::size_t>(src.c_str(), src.length()+1 ) };

    cl::Context context(device);
    cl::Program program(context,sources);
    auto err = program.build("-cl-std=CL2.0");

    std::cout << "err == " << err << std::endl;

    char buf[20];
    cl::Buffer memBuf( context , CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY , sizeof(buf) );
    cl::Kernel kernel( program , "hello_world_00" , &err );
    kernel.setArg(0,memBuf);
    cl::CommandQueue queue( context , device );
    queue.enqueueTask( kernel );
    queue.enqueueReadBuffer(memBuf,CL_TRUE,0,sizeof(buf),buf);

    std::cout << buf << std::endl;


    return 0;
}
