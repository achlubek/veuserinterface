#pragma once
#include "UIAbsDrawable.h"
namespace VEngine
{
    namespace UserInterface
    {
        class UIBitmap : public UIAbsDrawable
        {
        public:
            UIBitmap(UIRenderer* renderer, float x, float y, float width, float height, VEngine::Renderer::VulkanImage* texture, UIColor color);
            ~UIBitmap();
            VEngine::Renderer::VulkanImage* texture{ nullptr };
            void updateBuffer();
        };

    }
}