/*
 *   The GNU General Public License v3.0
 *
 *   Copyright (C) 2023 Yaroslav Riabtsev <yaroslav.riabtsev@rwth-aachen.de>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
*/


#ifndef FILE_SQUEEZER_NODE_HPP
#define FILE_SQUEEZER_NODE_HPP


class NodeGraphicsItem;

/**
 * @brief The Node class represents a node in a binary tree.
 */
class Node {
public:
    /**
     * @brief Constructs a node with the given key.
     *
     * @param key The key value associated with this node.
     */
    explicit Node(int key);

    /**
     * @brief Constructs a node with the given children.
     *
     * @param children A vector containing pointers to the children of this node.
     */
    explicit Node(const QVector<Node *> &children);

    /**
     * @brief Returns a string representation of this node.
     *
     * @return A string containing the key value of this node.
     */
    QString toString() const;

    /**
     * @brief Sets the graphics item associated with this node.
     *
     * @param nodeItem A pointer to the graphics item representing this node.
     */
    void setItem(NodeGraphicsItem *nodeItem);

    /**
     * @brief Returns the graphics item associated with this node.
     *
     * @return A pointer to the graphics item representing this node.
     */
    NodeGraphicsItem *getItem() const;

    /**
     * @brief Sets the parent of this node.
     *
     * @param node A pointer to the parent node.
     */
    void setParent(Node *node);

    /**
     * @brief Returns the parent of this node.
     *
     * @return A pointer to the parent node.
     */
    Node *getParent() const;

    /**
     * @brief Returns the children of this node.
     *
     * @return A vector containing pointers to the children of this node.
     */
    QVector<Node *> getChildren() const;

private:
    int m_key = 0; /**< The key value associated with this node. */
    NodeGraphicsItem *m_item = nullptr; /**< A pointer to the graphics item representing this node. */
    Node *m_parent = nullptr; /**< A pointer to the parent node. */
    QVector<Node *> m_children; /**< A vector containing pointers to the children of this node. */
};

#endif //FILE_SQUEEZER_NODE_HPP
