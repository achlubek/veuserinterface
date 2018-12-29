#include "stdafx.h"
#include "UIRenderer.h"
#include "UIBox.h"
#include "UIBitmap.h"
#include "UIText.h"

namespace VEngine
{
    namespace UserInterface
    {
        using namespace VEngine::Renderer;
        using namespace VEngine::Input;

        UIRenderer::UIRenderer(ToolkitInterface* toolkit, ImageInterface* outputImage, int width, int height) :
            toolkit(toolkit), width(width), height(height)
        {
            unsigned char * emptytexture = new unsigned char[4]{ (unsigned char)0x255, (unsigned char)0x255, (unsigned char)0x255, (unsigned char)0x255 };
            dummyTexture = toolkit->getImageFactory()->build(1, 1, 4, emptytexture);

            layout = toolkit->getDescriptorSetLayoutFactory()->build();
            layout->addField(VEngineDescriptorSetFieldType::FieldTypeUniformBuffer, VEngineDescriptorSetFieldStage::FieldStageAll);
            layout->addField(VEngineDescriptorSetFieldType::FieldTypeUniformBuffer, VEngineDescriptorSetFieldStage::FieldStageAll);
            layout->addField(VEngineDescriptorSetFieldType::FieldTypeSampler, VEngineDescriptorSetFieldStage::FieldStageFragment);

            auto vert = toolkit->getShaderFactory()->build(VEngineShaderModuleType::Vertex, "ui.vert.spv");
            auto frag = toolkit->getShaderFactory()->build(VEngineShaderModuleType::Fragment, "ui.frag.spv");

            stage = toolkit->getRenderStageFactory()->build(width, height, { vert, frag }, { layout },
                { outputImage->getAttachment(VEngineAttachmentBlending::Alpha, true,{ { 0.0f, 0.0f, 0.0f, 0.0f } }, false) });
        }


        void UIRenderer::draw() {

            for (int a = 0; a < drawables.size(); a++) {
                for (int b = 0; b < drawables.size(); b++) {
                    auto index_a = drawables[a]->getZIndex();
                    auto index_b = drawables[b]->getZIndex();
                    if (index_a > index_b) {
                        auto tmp = drawables[b];
                        drawables[b] = drawables[a];
                        drawables[a] = tmp;
                    }
                }
            }

            for (int i = 0; i < drawables.size(); i++) {
                drawables[i]->updateBuffer();
            }

            stage->beginDrawing();

            for (int i = 0; i < drawables.size(); i++) {
                drawables[i]->draw(stage);
            }

            stage->endDrawing();
            stage->submitNoSemaphores({});
        }

        void UIRenderer::addDrawable(IDrawable * drawable)
        {
            drawables.push_back(drawable);
        }

        void UIRenderer::removeDrawable(IDrawable * drawable)
        {
            auto found = std::find(drawables.begin(), drawables.end(), drawable);
            if (found != drawables.end()) {
                drawables.erase(found);
            }
        }

        std::vector<IDrawable*> UIRenderer::getDrawables()
        {
            return drawables;
        }

        void UIRenderer::removeAllDrawables()
        {
            drawables.clear();
        }

        std::vector<IDrawable*> UIRenderer::rayCast(float x, float y)
        {
            auto result = std::vector<IDrawable*>();
            for (int a = 0; a < drawables.size(); a++) {
                if (
                    x > drawables[a]->getX()
                    && x < (drawables[a]->getX() + drawables[a]->getWidth())
                    && y > drawables[a]->getY()
                    && y < (drawables[a]->getY() + drawables[a]->getHeight())) {
                    result.push_back(drawables[a]);
                }
            }
            return result;
        }

        ToolkitInterface * UIRenderer::getToolkit()
        {
            return toolkit;
        }

        uint32_t UIRenderer::getWidth()
        {
            return width;
        }

        uint32_t UIRenderer::getHeight()
        {
            return height;
        }

        DescriptorSetLayoutInterface * UIRenderer::getSetLayout()
        {
            return layout;
        }

        ImageInterface * UIRenderer::getDummyTexture()
        {
            return dummyTexture;
        }

        UIRenderer::~UIRenderer()
        {
        }
    }
}