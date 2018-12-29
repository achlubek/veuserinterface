#include "stdafx.h"
#include "UIBitmap.h"
#include "UIRenderer.h"
#include "UIAbsDrawable.h"

namespace VEngine
{
    namespace UserInterface
    {
        using namespace VEngine::Renderer;
        UIBitmap::UIBitmap(UIRenderer* irenderer, float x, float y, float width, float height, ImageInterface* itexture, UIColor color)
            : UIAbsDrawable(irenderer, x, y, width, height, color), texture(itexture)
        {
            set = renderer->getSetLayout()->generateDescriptorSet();
            set->bindBuffer(0, dataBuffer);
            set->bindBuffer(1, customBuffer);
            set->bindImageViewSampler(2, texture);
        }


        UIBitmap::~UIBitmap()
        {
        }

        void UIBitmap::updateBuffer()
        {
            size_t offset = 0;
            void* data;
            dataBuffer->map(0, dataBuffer->getSize(), &data);

            #define emplaceFloat(val) static_cast<float*>(data)[offset] = val; offset++
            #define emplaceInt(val) static_cast<int32_t*>(data)[offset] = val; offset++

            if (horizontalAlignment == HorizontalAlignment::left) {
                emplaceFloat(x);
            }
            else if (horizontalAlignment == HorizontalAlignment::center) {
                emplaceFloat(x - 0.5f * width);
            }
            else if (horizontalAlignment == HorizontalAlignment::right) {
                emplaceFloat(x - width);
            }

            if (verticalAlignment == VerticalAlignment::top) {
                emplaceFloat(y);
            }
            else if (verticalAlignment == VerticalAlignment::center) {
                emplaceFloat(y - 0.5f * height);
            }
            else if (verticalAlignment == VerticalAlignment::bottom) {
                emplaceFloat(y - height);
            }
            emplaceFloat(width);
            emplaceFloat(height);

            emplaceFloat(color.red);
            emplaceFloat(color.green);
            emplaceFloat(color.blue);
            emplaceFloat(color.alpha);

            emplaceFloat(0.0f);
            emplaceFloat(0.0f);
            emplaceFloat(1.0f);
            emplaceFloat(1.0f);

            emplaceInt(2);
            emplaceInt(2);
            emplaceInt(2);
            emplaceInt(2);

            dataBuffer->unmap();
        }
    }
}