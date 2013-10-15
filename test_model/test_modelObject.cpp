#include "stdafx.h"
#include <CppUnitTest.h>

#include <model/ModelObject.h>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace geometry::model;

namespace test_model
{
    TEST_CLASS(TestModelObject)
    {
    public:

        void callback()
        {
            Logger::WriteMessage("called");
        }
        TEST_METHOD(TestSimple) 
        {
        }

    };
}