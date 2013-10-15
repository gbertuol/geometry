#pragma once


namespace geometry
{
    namespace model
    {
        class ModelObject;

        class ModelObjectVisitor
        {
        public:
            virtual ~ModelObjectVisitor();

            virtual void Visit(ModelObject const&)
            {}
        };
    }
}

