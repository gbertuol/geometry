#include "stdafx.h"

#include <model/ModelObject.h>

using namespace geometry::model;


class A
    : public ModelObject
{
public:
    virtual ~A()
    {}

    virtual void Visit(ModelObjectVisitor &p_visitor) const
    {
        p_visitor.Visit(*this);
    }
    void Do()
    {
        on_modified(*this);
    }
};
typedef A B;
typedef A C;

class Project
    : public ModelObject
{
public:
    Project()
        : ModelObject(ID(1))
    {
        AddChild(a);
        AddChild(b);
        AddChild(c);
    }

    virtual ~Project()
    {}

    virtual void Visit(ModelObjectVisitor &p_visitor) const
    {
        p_visitor.Visit(*this);
        a.Visit(p_visitor);
        b.Visit(p_visitor);
        c.Visit(p_visitor);
    }
    A a;
    B b;
    C c;
};

class ModelObjectTest
    : public ::testing::Test
{
public:
    void callback(ModelObject const&)
    {
        //Logger::WriteMessage("called");
    }
};

TEST_F(ModelObjectTest, TestSimple)
{
    Project project;
    project.on_child_modified.connect(std::bind(&ModelObjectTest::callback, this, std::placeholders::_1));
    ASSERT_TRUE(project.a.IsChildOf(project));
    project.a.Do();

    const ModelObject *obj = project.a.FindModelObject(project.b.GetID());

    ASSERT_TRUE(obj != nullptr);

    std::stringstream sstream;
    sstream << obj->GetID();
    std::cout << sstream.str() << std::endl;
}
