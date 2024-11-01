#pragma once
#include <iostream>
#include <GLFW/glfw3.h>
#include <webgpu/webgpu.h>
#include <glfw3webgpu.h>
#include <cassert>
#include <vector>
#define WEBGPU_BACKEND_WGPU

class Application {
public:
    /*
    // Initialize everything and return true if it went all right
    bool Initialize();

    // Uninitialize everything that was initialized
    void Terminate();

    // Draw a frame and handle events
    void MainLoop();

    // Return true as long as the main loop should keep on running
    bool IsRunning();
    */

    int launch();

    WGPUTextureView GetNextSurfaceTextureView();
    WGPUAdapter requestAdapterSync(WGPUInstance instance, WGPURequestAdapterOptions const* options);
    WGPUDevice requestDeviceSync(WGPUAdapter adapter, WGPUDeviceDescriptor const* descriptor);
    void inspectAdapter(WGPUAdapter adapter);

public:
    // We put here all the variables that are shared between init and main loop
    WGPUSurface surface;
    GLFWwindow* window;

    WGPUInstance instance;
    WGPUAdapter adapter;

    WGPUDeviceDescriptor deviceDesc;
    WGPUDevice device;

    WGPUTextureView targetView;

    WGPUInstanceDescriptor desc;

    WGPURenderPassEncoder renderPass;
    WGPURenderPassDescriptor renderPassDesc;
    WGPURenderPassColorAttachment renderPassColorAttachment;

    WGPUCommandEncoder encoder;
    WGPUCommandEncoderDescriptor encoderDesc;

    WGPUCommandBufferDescriptor cmdBufferDescriptor;
    WGPUCommandBuffer command;
};
