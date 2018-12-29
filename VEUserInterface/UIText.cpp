#include "stdafx.h"
#include "UIText.h"
#include "UIBitmap.h"
#include "UIRenderer.h"

namespace VEngine
{
    namespace UserInterface
    {
        using namespace VEngine::Renderer;

        UIText::UIText(UIRenderer* irenderer, float x, float y, UIColor color, std::string fontmediakey, int ifontsize, std::string text)
            : UIAbsDrawable(irenderer, x, y, 0, 0, color), fontsize(ifontsize)
        {
            irenderer->getToolkit()->getMedia()->readBinary(fontmediakey, &fontBuffer);
            font = new stbtt_fontinfo();
            if (!stbtt_InitFont(font, fontBuffer, 0))
            {
                printf("font loading failed\n");
            }
            set = renderer->getSetLayout()->generateDescriptorSet();
            updateText(text);
        }


        UIText::~UIText()
        {
            delete texture;
            delete font;
            delete fontBuffer;
        }

        void UIText::updateBuffer()
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

            emplaceInt(3);
            emplaceInt(3);
            emplaceInt(3);
            emplaceInt(3);

            dataBuffer->unmap();
        }

        void UIText::updateText(std::string text)
        {
            if (currentText == text) return;
            currentText = text;

            int l_h = fontsize;

            float scale = stbtt_ScaleForPixelHeight(font, static_cast<float>(l_h));

            const char* word = text.c_str();

            int nx = 0;
            int maxy = 0;

            int ascent, descent, lineGap;
            stbtt_GetFontVMetrics(font, &ascent, &descent, &lineGap);

            ascent = static_cast<int>(static_cast<float>(ascent) * scale);
            descent = static_cast<int>(static_cast<float>(descent) * scale);

            for (int i = 0; i < strlen(word); ++i)
            {
                /* get bounding box for character (may be offset to account for chars that dip above or below the line */
                int c_x1, c_y1, c_x2, c_y2;
                stbtt_GetCodepointBitmapBox(font, word[i], scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);

                /* compute y (different characters have different heights */
                int y = (c_y2 - c_y1) + ascent;
                if (y > maxy) maxy = y;

                /* render character (stride and offset is important here) */
               // int byteOffset = x + (y  * b_w);
               // stbtt_MakeCodepointBitmap(&info, bitmap + byteOffset, c_x2 - c_x1, c_y2 - c_y1, b_w, scale, scale, word[i]);

                /* how wide is this character */
                int ax;
                stbtt_GetCodepointHMetrics(font, word[i], &ax, 0);
                nx += static_cast<int>(static_cast<float>(ax) * scale);

                /* add kerning */
                int kern;
                kern = stbtt_GetCodepointKernAdvance(font, word[i], word[i + 1]);
                nx += static_cast<int>(static_cast<float>(kern) * scale);
                nx += 2;
            }
            if (nx * maxy == 0) {
                width = 0;
                height = 0;
                return;
            }
            unsigned char* bitmap = new unsigned char[nx * maxy];
            for (int i = 0; i < nx * maxy; i++)bitmap[i] = 0;
            int b_w = nx;

            nx = 0;
            for (int i = 0; i < strlen(word); ++i)
            {
                /* get bounding box for character (may be offset to account for chars that dip above or below the line */
                int c_x1, c_y1, c_x2, c_y2;
                stbtt_GetCodepointBitmapBox(font, word[i], scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);

                /* compute y (different characters have different heights */
                int y = ascent + c_y1;

                /* render character (stride and offset is important here) */
                int byteOffset = nx + (y  * b_w);
                stbtt_MakeCodepointBitmap(font, bitmap + byteOffset, c_x2 - c_x1, c_y2 - c_y1, b_w, scale, scale, word[i]);

                /* how wide is this character */
                int ax;
                stbtt_GetCodepointHMetrics(font, word[i], &ax, 0);
                nx += static_cast<int>(static_cast<float>(ax) * scale);

                /* add kerning */
                int kern;
                kern = stbtt_GetCodepointKernAdvance(font, word[i], word[i + 1]);
                nx += static_cast<int>(static_cast<float>(kern) * scale);
                nx += 2;
            }

            width = (float)nx / (float)renderer->getWidth();
            height = (float)maxy / (float)renderer->getHeight();

            if (texture != nullptr) delete texture;
            texture = renderer->getToolkit()->getImageFactory()->build(nx, maxy, 1, (void*)bitmap);
            set->bindBuffer(0, dataBuffer);
            set->bindBuffer(1, customBuffer);
            set->bindImageViewSampler(2, texture);

            // delete[] bitmap; // stb deletes
        }
    }
}