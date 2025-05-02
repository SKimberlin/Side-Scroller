#pragma once

class RendererComponent;

class IRenderer {
public:
    virtual ~IRenderer() = default;

    virtual void BeginRender() = 0;
    virtual void EndRender() = 0;

    virtual void Draw(RendererComponent* renderer) = 0;
};
