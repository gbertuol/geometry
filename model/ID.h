#pragma once

#include <vector>

namespace geometry
{
    namespace model
    {
        class ID
        {
        public:
            ID(int p_id = 1)
                : m_sibling_count(0)
            {
                m_id.push_back(p_id);
            }

            ID NewChild()
            {
                ID id(-1);
                id.m_id = m_id;
                id.m_id.push_back(++m_sibling_count);
                return id;
            }

            bool IsParentOf(ID const& p_child) const
            {
                if (p_child.m_id.size() < m_id.size())
                    return false;
                for (size_t k = 0; k < m_id.size(); ++k)
                    if (m_id[k] != p_child.m_id[k])
                        return false;

                return true;
            }

            bool IsChildOf(ID const& p_parent) const
            {
                return p_parent.IsParentOf(*this);
            }


        private:
            int m_sibling_count;
            std::vector<int> m_id;
        };
    }
}
