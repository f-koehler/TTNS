#ifndef TTNS_BFITERATOR_HPP
#define TTNS_BFITERATOR_HPP

#include "Tree.hpp"

#include <queue>

namespace TTNS {

template <typename NodeT>
class BFIterator {
  public:
    using NodeType = NodeT;

    using value_type = NodeType;
    using difference_type = std::ptrdiff_t;
    using reference = NodeType &;
    using pointer = NodeType *;
    using iterator_category = std::forward_iterator_tag;

  private:
    std::queue<NodeType *> m_queue;

  public:
    BFIterator() = default;
    explicit BFIterator(NodeType *node);
    virtual ~BFIterator() = default;

    NodeType &operator*() const;
    BFIterator &operator++();
    BFIterator operator++(int);
    bool operator==(const BFIterator &other) const;
    bool operator!=(const BFIterator &other) const;
};

template <typename NodeT>
BFIterator<NodeT>::BFIterator(BFIterator<NodeT>::NodeType *node) {
    if (node != nullptr) {
        m_queue.push(node);
    }
}

template <typename NodeT>
typename BFIterator<NodeT>::NodeType &BFIterator<NodeT>::operator*() const {
    return *m_queue.front();
}

template <typename NodeT>
BFIterator<NodeT> &BFIterator<NodeT>::operator++() {
    if (m_queue.empty()) {
        return *this;
    }

    auto node = m_queue.front();
    m_queue.pop();
    for (std::size_t i = 0; i < node->get_num_children(); ++i) {
        m_queue.push(&node->operator[](i));
    }
    return *this;
}

template <typename NodeT>
BFIterator<NodeT> BFIterator<NodeT>::operator++(int) {
    BFIterator copy(*this);
    ++(*this);
    return copy;
}

template <typename NodeT>
bool BFIterator<NodeT>::operator==(const BFIterator<NodeT> &other) const {
    if (m_queue.empty() != other.m_queue.empty()) {
        return false;
    }
    if (m_queue.empty()) {
        return true;
    }
    return m_queue.front() == other.m_queue.front();
}

template <typename NodeT>
bool BFIterator<NodeT>::operator!=(const BFIterator<NodeT> &other) const {
    return !(*this == other);
}
} // namespace TTNS

#endif /* TTNS_BFITERATOR_HPP */
