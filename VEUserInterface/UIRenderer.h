#pragma once
namespace VEngine
{
    namespace UserInterface
    {
        class UIAbsDrawable;
        class UIRenderer
        {
        public:
            UIRenderer(VEngine::Renderer::VulkanToolkit* vulkan, VEngine::Input::Mouse* mouse, VEngine::Renderer::VulkanImage* outputImage, int width, int height);
            ~UIRenderer();
            void draw();
            void addDrawable(UIAbsDrawable* drawable);
            void removeDrawable(UIAbsDrawable* drawable);
            std::vector<UIAbsDrawable*> getDrawables();
            void removeAllDrawables();
            std::vector<UIAbsDrawable*> rayCast(float x, float y);

            VEngine::Renderer::VulkanToolkit* getToolkit();
            uint32_t getWidth();
            uint32_t getHeight();
            VEngine::Renderer::VulkanDescriptorSetLayout* getSetLayout();
            VEngine::Renderer::VulkanImage* getDummyTexture();


        private:
            VEngine::Renderer::VulkanRenderStage * stage{ nullptr };
            std::vector<UIAbsDrawable*> drawables;
            VEngine::Input::Mouse* mouse;
            VEngine::Renderer::VulkanToolkit* vulkan{ nullptr };
            uint32_t width{ 0 }, height{ 0 };
            VEngine::Renderer::VulkanDescriptorSetLayout* layout{ nullptr };
            VEngine::Renderer::VulkanImage* dummyTexture;
        };

    }
}