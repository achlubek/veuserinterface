#pragma once
namespace VEngine
{
    namespace UserInterface
    {
        class DrawableInterface;
        class UIRenderer
        {
        public:
            UIRenderer(VEngine::Renderer::ToolkitInterface* vulkan, VEngine::Renderer::ImageInterface* outputImage, int width, int height);
            ~UIRenderer();
            void draw();
            void addDrawable(DrawableInterface* drawable);
            void removeDrawable(DrawableInterface* drawable);
            std::vector<DrawableInterface*> getDrawables();
            void removeAllDrawables();
            std::vector<DrawableInterface*> rayCast(float x, float y);

            VEngine::Renderer::ToolkitInterface* getToolkit();
            uint32_t getWidth();
            uint32_t getHeight();
            VEngine::Renderer::DescriptorSetLayoutInterface* getSetLayout();
            VEngine::Renderer::ImageInterface* getDummyTexture();


        private:
            VEngine::Renderer::RenderStageInterface * stage{ nullptr };
            std::vector<DrawableInterface*> drawables;
           // VEngine::Input::MouseInterface* mouse;
            VEngine::Renderer::ToolkitInterface* toolkit{ nullptr };
            uint32_t width{ 0 }, height{ 0 };
            VEngine::Renderer::DescriptorSetLayoutInterface* layout{ nullptr };
            VEngine::Renderer::ImageInterface* dummyTexture;
        };

    }
}