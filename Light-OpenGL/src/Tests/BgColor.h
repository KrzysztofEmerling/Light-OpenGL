#pragma once
#include "Test.h"
namespace Tests
{
    class BgColor :
        public Test
    {
    private:
        float m_BgColor[4];
    public:
        BgColor();
        ~BgColor();

        void OnRender() override;
        void OnImGuiRender() override;
    };
}