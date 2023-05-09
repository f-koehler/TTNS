#ifndef TTNS_BFSITERATOR_HPP
#define TTNS_BFSITERATOR_HPP

#include "Tree.hpp"

#include <queue>

namespace TTNS {

template <typename NodeT>
class BFSIterator {
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
    BFSIterator() = default;
    explicit BFSIterator(NodeType *node);
    virtual ~BFSIterator() = default;

    NodeType &operator*() const;
    BFSIterator &operator++();
    BFSIterator operator++(int);
    bool operator==(const BFSIterator &other) const;
    bool operator!=(const BFSIterator &other) const;
};

template <typename NodeT>
BFSIterator<NodeT>::BFSIterator(BFSIterator<NodeT>::NodeType *node) {
    if (node != nullptr) {
        m_queue.push(node);
    }
}

template <typename NodeT>
typename BFSIterator<NodeT>::NodeType &BFSIterator<NodeT>::operator*() const {
    return *m_queue.front();
}

template <typename NodeT>
BFSIterator<NodeT> &BFSIterator<NodeT>::operator++() {
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
BFSIterator<NodeT> BFSIterator<NodeT>::operator++(int) {
    BFSIterator copy(*this);
    ++(*this);
    return copy;
}

template <typename NodeT>
bool BFSIterator<NodeT>::operator==(const BFSIterator<NodeT> &other) const {
    if (m_queue.empty() != other.m_queue.empty()) {
        return false;
    }
    if (m_queue.empty()) {
        return true;
    }
    return m_queue.front() == other.m_queue.front();
}

template <typename NodeT>
bool BFSIterator<NodeT>::operator!=(const BFSIterator<NodeT> &other) const {
    return !(*this == other);
}
} // namespace TTNS

#endif /* TTNS_BFSITERATOR_HPP */
