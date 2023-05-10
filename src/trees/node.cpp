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
// Qt
#include <QMenu>
#include <QPen>
#include <QGraphicsSceneMouseEvent>
// own
#include "node.hpp"

Node::Node(int key, QGraphicsItem *parent)
        : QGraphicsEllipseItem(parent), _key(key) {
    setGraphic();
    addTextItem();
    _depth = 1;
}


Node::Node(QVector<Node *> children, QGraphicsItem *parent)
        : QGraphicsEllipseItem(parent), _children(std::move(children)) {
    setGraphic();
    addLinks();
}

void Node::addLinks() {
    for (auto &child: _children) {
        _depth = qMax(_depth, child->getDepth() + 1);
        auto *edge = new QGraphicsLineItem(this);
        edge->setPen(QPen(Qt::white));
        child->setParent(this, edge);
    }
}

void Node::setGraphic() {
    setFlag(ItemIsMovable);
    setPen(QPen(Qt::white));
    setBrush(QBrush(Qt::blue));
    setRect(-_radius, -_radius, 2 * _radius, 2 * _radius);
}

void Node::addTextItem() {
    textItem = new QGraphicsSimpleTextItem(toString());
    textItem->setParentItem(this);
    textItem->setPen(QPen(Qt::white));
    QRectF textRect = textItem->boundingRect();
    textItem->setPos(-textRect.width() / 2, -textRect.height() / 2);
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsEllipseItem::mousePressEvent(event);
    clearFocus();
    if (event->button() == Qt::RightButton) {
        if (_parent && _parent->getChildrenCount() > 1) {
            auto children = _parent->getChildren();
            int idx = children.indexOf(this);
            auto *menu = new QMenu;
            if (idx > 0) {
                menu->addAction("Move Left", [=]() {
                    swapPos(children[idx - 1], this);
                });
            }
            if (idx < children.size() - 1)
                menu->addAction("Move Right", [=]() {
                    swapPos(this, children[idx + 1]);
                });
            menu->exec(QCursor::pos());
        }
    }
}

void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsEllipseItem::mouseMoveEvent(event);
    clearFocus();
    updateEdge();
}

QString Node::toString() const {
    if (_key == 0) {
        return "";
    }
    return QString::number(_key);
}

void Node::setParent(Node *node, QGraphicsLineItem *edge) {
    _parent = node;
    parentEdge = edge;
    updateEdge();
}

QVector<Node *> Node::getChildren() const {
    return _children;
}

int Node::getDepth() const {
    return _depth;
}

void Node::changePos(qreal ax, qreal ay) {
    QGraphicsItem::setPos(ax, ay);
    updateEdge();
}

void Node::changePos(QPointF newPos) {
    QGraphicsItem::setPos(newPos);
    updateEdge();
}

void Node::updateEdge() {
    if (_parent) {
        QPointF pos = scenePos() - _parent->pos();
        parentEdge->setLine(QLineF{{0, 0}, pos});
    }
    for (auto &child: _children) {
        QPointF pos = child->pos() - scenePos();
        auto *edge = child->getParentEdge();
        if (edge) {
            edge->setLine(QLineF{{0, 0}, pos});
        }
    }
}

void Node::scalePos(qreal ax, qreal ay) {
    QPointF pos = scenePos();
    changePos(pos.x() * ax, pos.y() * ay);
    for (auto &child: _children) {
        child->scalePos(ax, ay);
    }
}

QGraphicsLineItem *Node::getParentEdge() {
    return parentEdge;
}

void Node::swapPos(Node *left, Node *right) {
    if (left->pos().x() > right->pos().x()) {
        swapPos(right, left);
        return;
    }
    auto tmpPos = left->scenePos();
    left->changePos(right->scenePos());
    right->changePos(tmpPos);
    this->relocateChildren({right, left});
}

void Node::relocateChildren(const QVector<Node *>& nodes) {
    if (nodes.size() < 2) {
        return;
    }
    QVector<Node *> children;
    QVector<QPointF> positions;
    for (auto &node: nodes) {
        auto nodeChildren = node->getChildren();
        for (auto &child: nodeChildren) {
            children.push_back(child);
            positions.push_back(child->pos());
        }
    }
    std::sort(positions.begin(), positions.end(), [](QPointF a, QPointF b) {
        return a.x() < b.x();
    });
    int n = positions.size();
    for (int i = 0; i < n; i++) {
        if (children[i]->pos() != positions[i]) {
            children[i]->changePos(positions[i]);
        }
    }
    relocateChildren(children);
}

int Node::getChildrenCount() const {
    return _children.size();
}


