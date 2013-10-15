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
            ModelObject(ID const& p_id = ID(1))
                : m_id(p_id)
                , m_root(this)
            {}
            virtual ~ModelObject();

            bool IsParentOf(ModelObject const& p_obj) const
            {
                return m_id.IsParentOf(p_obj.m_id);
            }

            bool IsChildOf(ModelObject const& p_obj) const
            {
                return m_id.IsChildOf(p_obj.m_id);
            }

            //ModelObject& FindModelObject(ID const& targetId) const
            //{
            //    struct : ModelObjectVisitor
            //    {
            //        ID target;

            //        virtual void Visit(ModelObject const& p_obj)
            //        {

            //        }
            //    }
            //    finder;
            //    
            //    Visit(finder);
            //}

            void Visit(ModelObjectVisitor &visitor) const
            {
                visitor.Visit(*this);
            }

            const ID& Id() const 
            {
                return m_id;
            }

            utils::Signal<void(ModelObject const&)> on_modified;
            utils::Signal<void(ModelObject const&)> on_child_modified;

        protected:
            ID m_id;
            ModelObject *m_root;

            void AddChild(ModelObject &p_child)
            {
                p_child.SetRoot(m_root);
                p_child.m_id = m_id.NewChild();
            }

            void SetRoot(ModelObject *p_root)
            {
                m_root = p_root;
            }


        private:

        };
    }
}

