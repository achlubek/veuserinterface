#include "stdafx.h"
#include "UIBox.h"
#include "UIRenderer.h"

namespace VEngine
{
    namespace UserInterface
    {
        using namespace VEngine::Renderer;
        UIBox::UIBox(UIRenderer* renderer, float x, float y, float width, float height, UIColor color)
            : UIAbsDrawable(renderer, x, y, width, height, color)
        {
            set = renderer->getSetLayout()->generateDescriptorSet();
            set->bindBuffer(0, dataBuffer);
            set->bindBuffer(1, customBuffer);
            set->bindImageViewSampler(2, renderer->getDummyTexture());
        }

        UIBox::~UIBox()
        {
        }

        void UIBox::updateBuffer()
        {
            size_t offset = 0;
            void* data;
            dataBuffer->map(0, dataBuffer->getSize(), &data);

            #define emplaceFloat(val) static_cast<float*>(data)[offset] = val; offset++
            #define emplaceInt(val) static_cast<int32_t*>(data)[offset] = val; offset++

            emplaceFloat(x);
            emplaceFloat(y);
            emplaceFloat(width);
            emplaceFloat(height);

            emplaceFloat(color.red);
            emplaceFloat(color.green);
            emplaceFloat(color.blue);
            emplaceFloat(color.alpha);

            emplaceFloat(0.0f);
            emplaceFloat(0.0f);
            emplaceFloat(0.0f);
            emplaceFloat(0.0f);

            emplaceInt(1);
            emplaceInt(1);
            emplaceInt(1);
            emplaceInt(1);

            dataBuffer->unmap();
        }
    }
}