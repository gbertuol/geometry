#pragma once

#include <utils/Signals.h>
#include <model/ID.h>
#include <model/ModelObjectVisitor.h>

namespace geometry
{
    namespace model
    {
        class ModelObject
            : public utils::SignalTrackable
        {
        public:
            ModelObject(ID const& p_id = ID(1));
            virtual ~ModelObject();
            
            const ID& GetID() const;
            const ModelObject* GetRoot() const;
            bool IsParentOf(ModelObject const& p_obj) const;
            bool IsChildOf(ModelObject const& p_obj) const;
            const ModelObject* FindModelObject(ID const& p_id) const;

            virtual void Visit(ModelObjectVisitor &visitor) const
            {
                visitor.Visit(*this);
            }

            utils::Signal<void(ModelObject const&)> on_modified;
            utils::Signal<void(ModelObject const&)> on_child_modified;

        protected:
            ID m_id;
            ModelObject *m_root;

            void AddChild(ModelObject &p_child);
            void SetRoot(ModelObject *p_root);
        };
    }
}

