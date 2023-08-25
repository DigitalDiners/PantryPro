#ifndef ULTRALIGHT_INITIALIZER_H
#define ULTRALIGHT_INITIALIZER_H

#include <Ultralight/Ultralight.h>
#include <Ultralight/platform/Config.h>
#include <Ultralight/platform/Platform.h>
#include <Ultralight/Renderer.h>
#include <Ultralight/String.h> // Include this for Ultralight String type

class UltralightInitializer {
public:
    UltralightInitializer();
    ~UltralightInitializer();

    void Initialize();
    void Shutdown();

private:
    ultralight::RefPtr<ultralight::Platform> platform_;
    ultralight::RefPtr<ultralight::Renderer> renderer_;
};

#endif // ULTRALIGHT_INITIALIZER_H
