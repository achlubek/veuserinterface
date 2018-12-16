#pragma once
namespace VEngine
{
    namespace UserInterface
    {
        class IDrawable;
        class UIRenderer
        {
        public:
            UIRenderer(VEngine::Renderer::VulkanToolkit* vulkan, VEngine::Renderer::VulkanImage* outputImage, int width, int height);
            ~UIRenderer();
            void draw();
            void addDrawable(IDrawable* drawable);
            void removeDrawable(IDrawable* drawable);
            std::vector<IDrawable*> getDrawables();
            void removeAllDrawables();
            std::vector<IDrawable*> rayCast(float x, float y);

            VEngine::Renderer::VulkanToolkit* getToolkit();
            uint32_t getWidth();
            uint32_t getHeight();
            VEngine::Renderer::VulkanDescriptorSetLayout* getSetLayout();
            VEngine::Renderer::VulkanImage* getDummyTexture();


        private:
            VEngine::Renderer::VulkanRenderStage * stage{ nullptr };
            std::vector<IDrawable*> drawables;
            VEngine::Input::Mouse* mouse;
            VEngine::Renderer::VulkanToolkit* vulkan{ nullptr };
            uint32_t width{ 0 }, height{ 0 };
            VEngine::Renderer::VulkanDescriptorSetLayout* layout{ nullptr };
            VEngine::Renderer::VulkanImage* dummyTexture;
        };

    }
}