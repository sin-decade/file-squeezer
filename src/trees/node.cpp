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

// own
#include "nodegraphicsitem.hpp"
#include "node.hpp"

Node::Node(int key)
        : m_key(key) {
}

Node::Node(const QVector<Node *> &children)
        : m_children(children) {
    for (auto *child: m_children) {
        child->setParent(this);
    }
}

QString Node::toString() const {
    if (m_key == 0) {
        return "";
    }
    return QString::number(m_key);
}

void Node::setItem(NodeGraphicsItem *nodeItem) {
    m_item = nodeItem;
}

NodeGraphicsItem *Node::getItem() const {
    return m_item;
}

void Node::setParent(Node *node) {
    m_parent = node;
}

Node *Node::getParent() const {
    return m_parent;
}

QVector<Node *> Node::getChildren() const {
    return m_children;
}