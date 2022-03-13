#pragma once
#include <algorithm>
#include <cassert>
#include <charconv>
#include <chrono>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>
#include <cmath>
#include <sstream>
#include <ctime>
#include <cstdlib>

#ifndef CL_HPP_TARGET_OPENCL_VERSION
#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#define CL_HPP_TARGET_OPENCL_VERSION 120
#endif

#define CL_HPP_CL_1_2_DEFAULT_BUILD
#define CL_HPP_ENABLE_EXCEPTIONS

#include "CL/opencl.hpp"

#define TYPE int

#define STRINGIFY(X) #X
#define TSTRINGIFY(X) STRINGIFY(X)
#define STYPE TSTRINGIFY(TYPE)

#define KERNEL_PATH "../source/Kernel.cl"

class OclApp {
    cl::Platform P_;
    cl::Context C_;
    cl::CommandQueue Q_;
    std::string K_;
    static cl::Platform select_platform();
    static cl::Context get_gpu_context(cl_platform_id);
    std::string readFile(const char *Path);
    using bit_sort_t = cl::KernelFunctor<cl::Buffer, int, int, int>;
    public:
    OclApp() : P_(select_platform()), C_(get_gpu_context(P_())), Q_(C_),  K_(readFile(KERNEL_PATH)) {
        std::string Def = std::string("#define TYPE ") + STYPE + "\n";
        K_ = Def + K_;
    }
    cl::Event Bitonic_sort(cl::vector<TYPE>& Array, size_t size);

};


cl::Platform OclApp::select_platform() {
    cl::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    for (auto p : platforms) {
        cl_uint numdevices = 0;
        ::clGetDeviceIDs(p(), CL_DEVICE_TYPE_GPU, 0, NULL, &numdevices);
        if (numdevices > 0)
        return cl::Platform(p);
    }
    throw std::runtime_error("No platform selected");
}


cl::Context OclApp::get_gpu_context(cl_platform_id PId) {
    cl_context_properties properties[] = {
        CL_CONTEXT_PLATFORM, reinterpret_cast<cl_context_properties>(PId),
        0 // signals end of property list
    };
    return cl::Context(CL_DEVICE_TYPE_GPU, properties);
}


std::string OclApp::readFile(const char *Path) {
    std::string Code;
    std::ifstream KernelFile;
    KernelFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    KernelFile.open(Path);
    std::stringstream ShaderStream;
    ShaderStream << KernelFile.rdbuf();
    KernelFile.close();
    Code = ShaderStream.str();
    return Code;
}


cl::Event OclApp::Bitonic_sort(cl::vector<TYPE>& Array, size_t size) {
    size_t size_multiple_2 = pow(2, std::ceil(log2(size)));
    size_t BufSz = size_multiple_2 * sizeof(TYPE);

    cl::Buffer A(C_, CL_MEM_READ_WRITE, BufSz);
    Array.resize(size_multiple_2, 0);
    cl::copy(Q_, Array.begin(), Array.end(), A);

    cl::Program program(C_, K_, true /* build immediately */);
    bit_sort_t bitonic_step(program, "bitonic_sort_step");

    cl::NDRange GlobalRange(size_multiple_2);
    cl::NDRange LocalRange(1);
    cl::EnqueueArgs Args(Q_, GlobalRange, LocalRange);
    cl::Event evt;
    for (size_t part_size = 2; part_size <= size_multiple_2; part_size <<= 1) {
        for (size_t compare_dist = part_size >> 1; compare_dist > 0; compare_dist = compare_dist >> 1) {
            evt = bitonic_step(Args, A, part_size, compare_dist, 0);
            evt.wait();
        }
    }

    cl::copy(Q_, A, Array.begin(), Array.end());
    cl::vector<TYPE>::iterator it = std::find(Array.begin(), Array.end(), 0);
    Array.erase(it, it + (size_multiple_2 - size));
    return evt;
}
