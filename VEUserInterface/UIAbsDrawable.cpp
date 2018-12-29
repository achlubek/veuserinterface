#include "stdafx.h"
#include "UIAbsDrawable.h"
#include "UIRenderer.h"

namespace VEngine
{
    namespace UserInterface
    {
        using namespace VEngine::Renderer;

        UIAbsDrawable::UIAbsDrawable(UIRenderer* irenderer, float ix, float iy, float iwidth, float iheight, UIColor icolor)
            : renderer(irenderer), x(ix), y(iy), width(iwidth), height(iheight), color(icolor)
        {
            dataBuffer = renderer->getToolkit()->getBufferFactory()->build(VEngineBufferType::BufferTypeUniform, 1024);
            customBuffer = renderer->getToolkit()->getBufferFactory()->build(VEngineBufferType::BufferTypeUniform, 16 * 1024);
        }

        UIAbsDrawable::~UIAbsDrawable()
        {
            delete dataBuffer;
            delete customBuffer;
            delete set;
        }

        void UIAbsDrawable::draw(RenderStageInterface * stage)
        {
            if (width == 0 || height == 0) return;
            stage->setSets({ set });
            stage->drawMesh(renderer->getToolkit()->getObject3dInfoFactory()->getFullScreenQuad(), 1);
        }

        float UIAbsDrawable::getX()
        {
            return x;
        }

        float UIAbsDrawable::getY()
        {
            return y;
        }

        int32_t UIAbsDrawable::getZIndex()
        {
            return zIndex;
        }

        float UIAbsDrawable::getWidth()
        {
            return width;
        }

        float UIAbsDrawable::getHeight()
        {
            return height;
        }

        UIColor UIAbsDrawable::getColor()
        {
            return color;
        }

        VEngine::Renderer::GenericBufferInterface* UIAbsDrawable::getCustomBuffer()
        {
            return customBuffer;
        }

        void UIAbsDrawable::setX(float value)
        {
            x = value;
        }

        void UIAbsDrawable::setY(float value)
        {
            y = value;
        }

        void UIAbsDrawable::setZIndex(int32_t value)
        {
            zIndex = value;
        }

        void UIAbsDrawable::setWidth(float value)
        {
            width = value;
        }

        void UIAbsDrawable::setHeight(float value)
        {
            height = value;
        }

        void UIAbsDrawable::setColor(UIColor value)
        {
            color = value;
        }

    }
}