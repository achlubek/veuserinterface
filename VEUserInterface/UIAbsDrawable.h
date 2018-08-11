#pragma once
#include "UIColor.h"
#include <Utilities/EventHandler.h>
namespace VEngine
{
    namespace UserInterface
    {
        class UIRenderer;
        class UIAbsDrawable
        {
        public:
            UIAbsDrawable(UIRenderer* renderer, float x, float y, float width, float height, UIColor icolor);
            virtual ~UIAbsDrawable();
            float x{ 0 }, y{ 0 }, width{ 0 }, height{ 0 };
            UIColor color{ UIColor(0.0, 0.0, 0.0, 0.0) };
            UIRenderer* renderer{ nullptr };
            VEngine::Renderer::VulkanDescriptorSet* set;
            VEngine::Renderer::VulkanGenericBuffer* dataBuffer{ nullptr };
            int32_t zIndex{ 0 };
            virtual void updateBuffer() = 0;
            void draw(VEngine::Renderer::VulkanRenderStage* stage);
            enum class HorizontalAlignment { left, center, right };
            enum class VerticalAlignment { top, center, bottom };
            HorizontalAlignment horizontalAlignment = HorizontalAlignment::left;
            VerticalAlignment verticalAlignment = VerticalAlignment::top;
            VEngine::Utilities::EventHandler<int> onMouseDown;
            VEngine::Utilities::EventHandler<int> onMouseUp;
        };

    }
}