#pragma once
#include "UIColor.h"
#include "DrawableInterface.h"

namespace VEngine
{
    namespace UserInterface
    {
        class UIRenderer;

        class UIAbsDrawable : public DrawableInterface
        {
        public:
            UIAbsDrawable(UIRenderer* renderer, float x, float y, float width, float height, UIColor icolor);
            virtual ~UIAbsDrawable();

            enum class HorizontalAlignment { left, center, right };
            enum class VerticalAlignment { top, center, bottom };

            virtual void updateBuffer() = 0;
            void draw(VEngine::Renderer::RenderStageInterface* stage);

            virtual float getX() override;
            virtual float getY() override;
            virtual int32_t getZIndex() override;
            virtual float getWidth() override;
            virtual float getHeight() override;
            virtual UIColor getColor() override;
            virtual VEngine::Renderer::GenericBufferInterface* getCustomBuffer() override;

            virtual void setX(float value) override;
            virtual void setY(float value) override;
            virtual void setZIndex(int32_t value) override;
            virtual void setWidth(float value) override;
            virtual void setHeight(float value) override;
            virtual void setColor(UIColor value) override;

        protected:
            float x{ 0 }, y{ 0 }, width{ 0 }, height{ 0 };
            int32_t zIndex{ 0 };

            UIColor color{ UIColor(0.0, 0.0, 0.0, 0.0) };

            UIRenderer* renderer{ nullptr };
            VEngine::Renderer::DescriptorSetInterface* set;
            VEngine::Renderer::GenericBufferInterface* dataBuffer{ nullptr };
            VEngine::Renderer::GenericBufferInterface* customBuffer{ nullptr };

            HorizontalAlignment horizontalAlignment = HorizontalAlignment::left;
            VerticalAlignment verticalAlignment = VerticalAlignment::top;

        };

    }
}