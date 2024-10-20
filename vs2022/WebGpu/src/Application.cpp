#include "Header/Application.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <webgpu/webgpu.h>
#include <cassert>
#include <vector>

bool Application::Initialize()
{
	// Open window
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // <-- extra info for glfwCreateWindow
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(640, 480, "Learn WebGPU", nullptr, nullptr);

	// Create instance
	WGPUInstance instance = wgpuCreateInstance(nullptr);

	// Get adapter
	std::cout << "Requesting adapter..." << std::endl;
	surface = glfwGetWGPUSurface(instance, window);
	WGPURequestAdapterOptions adapterOpts = {};
	adapterOpts.nextInChain = nullptr;
	adapterOpts.compatibleSurface = surface;
	//                              ^^^^^^^ Use the surface here

	WGPUAdapter adapter = requestAdapterSync(instance, &adapterOpts);
	std::cout << "Got adapter: " << adapter << std::endl;

	// We no longer need to access the instance
	wgpuInstanceRelease(instance);


	// Get device
	std::cout << "Requesting device..." << std::endl;
	WGPUDeviceDescriptor deviceDesc = {};
	deviceDesc.nextInChain = nullptr;
	{ { Build device descriptor } }
	device = requestDeviceSync(adapter, &deviceDesc);
	std::cout << "Got device: " << device << std::endl;


	return true;
}

void Application::Terminate()
{
}

void Application::MainLoop()
{
#if defined(WEBGPU_BACKEND_DAWN)
	wgpuDeviceTick(device);
#elif defined(WEBGPU_BACKEND_WGPU)
	wgpuDevicePoll(device, false, nullptr);
#endif
}

bool Application::IsRunning()
{
	return false;
}
