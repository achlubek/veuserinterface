#pragma once
struct stbtt_fontinfo;
#include "UIAbsDrawable.h"
namespace VEngine
{
    namespace UserInterface
    {
        class UIText : public UIAbsDrawable
        {
        public:
            UIText(UIRenderer* renderer, float x, float y, UIColor color, std::string fontmediakey, int ifontsize, std::string text);
            ~UIText();
            VEngine::Renderer::ImageInterface* texture{ nullptr };
            stbtt_fontinfo* font;
            unsigned char* fontBuffer;
            int fontsize = 64;
            void updateText(std::string text);
            std::string currentText = "";
            void updateBuffer();
        };

    }
}