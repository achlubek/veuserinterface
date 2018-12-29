#pragma once
#include "UIAbsDrawable.h"
namespace VEngine
{
    namespace UserInterface
    {
        class UIBitmap : public UIAbsDrawable
        {
        public:
            UIBitmap(UIRenderer* renderer, float x, float y, float width, float height, VEngine::Renderer::ImageInterface* texture, UIColor color);
            ~UIBitmap();
            void updateBuffer();
        private:
            VEngine::Renderer::ImageInterface* texture{ nullptr };
        };

    }
}