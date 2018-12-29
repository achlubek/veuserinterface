#pragma once
#include "UIColor.h"
namespace VEngine
{
    namespace UserInterface
    {
        class IDrawable
        {
        public:
            virtual void updateBuffer() = 0;
            virtual void draw(VEngine::Renderer::RenderStageInterface* stage) = 0;

            virtual float getX() = 0;
            virtual float getY() = 0;
            virtual int32_t getZIndex() = 0;
            virtual float getWidth() = 0;
            virtual float getHeight() = 0;
            virtual UIColor getColor() = 0;
            virtual VEngine::Renderer::GenericBufferInterface* getCustomBuffer() = 0;

            virtual void setX(float value) = 0;
            virtual void setY(float value) = 0;
            virtual void setZIndex(int32_t value) = 0;
            virtual void setWidth(float value) = 0;
            virtual void setHeight(float value) = 0;
            virtual void setColor(UIColor value) = 0;
        };

    }
}