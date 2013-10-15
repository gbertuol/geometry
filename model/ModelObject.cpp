#include "ModelObject.h"


namespace geometry
{
    namespace model
    {
        ModelObject::ModelObject(ID const& p_id)
            : m_id(p_id)
            , m_root(this)
        {
        }

        ModelObject::~ModelObject()
        {
        }

        const ModelObject* ModelObject::GetRoot() const
        {
            return m_root;
        }

        bool ModelObject::IsParentOf(ModelObject const& p_obj) const
        {
            return m_id.IsParentOf(p_obj.m_id);
        }

        bool ModelObject::IsChildOf(ModelObject const& p_obj) const
        {
            return m_id.IsChildOf(p_obj.m_id);
        }

        const ID& ModelObject::GetID() const
        {
            return m_id;
        }

        void ModelObject::AddChild(ModelObject &p_child)
        {
            p_child.SetRoot(m_root);
            p_child.m_id = m_id.NewChild();
            p_child.on_modified.connect(this->on_child_modified);
            p_child.on_child_modified.connect(this->on_child_modified);
        }

        void ModelObject::SetRoot(ModelObject *p_root)
        {
            m_root = p_root;
        }

        struct Finder
            : public ModelObjectVisitor
        {
            Finder(ID const& p_id)
                : target(p_id)
                , found(nullptr)
            {
            }
            virtual ~Finder() {}

            ID target;
            const ModelObject *found;
            virtual void Visit(ModelObject const& p_obj)
            {
                if(p_obj.GetID() == target)
                    found = &p_obj;
            }
        };

        const ModelObject* ModelObject::FindModelObject(ID const& p_id) const
        {
            Finder visitor(p_id);
            m_root->Visit(visitor);
            return visitor.found;
        }
    }
}
