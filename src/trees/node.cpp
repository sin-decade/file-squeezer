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
        if (_parent) {
            auto children = _parent->getChildren();
            if (children.size() > 1) {
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

void Node::swapPos(Node *right, Node *left) {
    auto tmpPos = left->scenePos();
    left->changePos(right->scenePos());
    right->changePos(tmpPos);
    auto leftChildren = left->getChildren();
    auto rightChildren = right->getChildren();
    if (!leftChildren.isEmpty() && !rightChildren.isEmpty()) {
        int leftSize = leftChildren.size();
        int rightSize = rightChildren.size();
        for (int i = 0; i < leftSize / 2; i++) {
            swapPos(leftChildren[i], leftChildren[leftSize - i - 1]);
        }
        for (int i = 0; i < rightSize / 2; i++) {
            swapPos(rightChildren[i], rightChildren[rightSize - i - 1]);
        }
        for (int i = 0, j = rightSize + leftSize - 1; i < j; i++, j--) {
            auto *leftNode = i < leftSize ? leftChildren[i] : rightChildren[i - leftSize];
            auto *rightNode = j < leftSize ? leftChildren[j] : rightChildren[j - leftSize];
            swapPos(leftNode, rightNode);
        }
    }
}


