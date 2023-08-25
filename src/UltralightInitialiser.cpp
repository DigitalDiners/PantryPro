#include "UltralightInitialiser.h"

UltralightInitializer::UltralightInitializer() {
    ultralight::Config config;
    //ultralight::Platform::set_config();
    //Platform::instance().set_config(config);
    //config.enable_gpu_acceleration = true;

    //platform_ = ultralight::Platform::instance();
    renderer_ = ultralight::Renderer::Create();
}

UltralightInitializer::~UltralightInitializer() {
    // renderer_ = nullptr;
    // platform_ = nullptr;
}

void UltralightInitializer::Initialize() {
    // Additional initialization steps if needed
}

void UltralightInitializer::Shutdown() {
    // Cleanup steps if needed
}
