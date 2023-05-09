#ifndef TTNS_DFITERATOR_HPP
#define TTNS_DFITERATOR_HPP

#include "Tree.hpp"

#include <stack>

namespace TTNS {

template <typename NodeT>
class DFIterator {
  public:
    using NodeType = NodeT;

    using value_type = NodeType;
    using difference_type = std::ptrdiff_t;
    using reference = NodeType &;
    using pointer = NodeType *;
    using iterator_category = std::forward_iterator_tag;

  private:
    std::stack<NodeType *> m_stack;

  public:
    DFIterator() = default;
    explicit DFIterator(NodeType *node);
    virtual ~DFIterator() = default;

    NodeType &operator*() const;
    DFIterator &operator++();
    DFIterator operator++(int);
    bool operator==(const DFIterator &other) const;
    bool operator!=(const DFIterator &other) const;
};

template <typename NodeT>
DFIterator<NodeT>::DFIterator(NodeT *node) {
    if (node != nullptr) {
        m_stack.push(node);
    }
}

template <typename NodeT>
NodeT &DFIterator<NodeT>::operator*() const {
    return *m_stack.top();
}

template <typename NodeT>
DFIterator<NodeT> &DFIterator<NodeT>::operator++() {
    if (m_stack.empty()) {
        return *this;
    }

    auto node = m_stack.top();
    m_stack.pop();
    for (std::size_t i = node->get_num_children(); i > 0; --i) {
        m_stack.push(&node->operator[](i - 1));
    }
    return *this;
}

template <typename NodeT>
DFIterator<NodeT> DFIterator<NodeT>::operator++(int) {
    BFIterator copy(*this);
    ++(*this);
    return copy;
}

template <typename NodeT>
bool DFIterator<NodeT>::operator==(const DFIterator<NodeT> &other) const {
    if (m_stack.empty() != other.m_stack.empty()) {
        return false;
    }
    if (m_stack.empty() && other.m_stack.empty()) {
        return true;
    }
    return m_stack.top() == other.m_stack.top();
}

template <typename NodeT>
bool DFIterator<NodeT>::operator!=(const DFIterator<NodeT> &other) const {
    return !(*this == other);
}

} // namespace TTNS

#endif /* TTNS_DFITERATOR_HPP */
