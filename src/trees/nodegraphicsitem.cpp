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
#include <QAction>
#include <QMenu>
#include <QPen>
// own
#include "node.hpp"
#include "nodegraphicsitem.hpp"

NodeGraphicsItem::NodeGraphicsItem(Node *node, QGraphicsItem *parent)
        : QGraphicsEllipseItem(parent), node(node) {
    setFlag(ItemIsMovable);
    setPen(QPen(Qt::white));
    setBrush(QBrush(Qt::blue));
    addTextItem();
    node->setItem(this);
    edges.resize(node->getChildren().size());
    for (auto &edge: edges) {
        edge = new QGraphicsLineItem(this);
        edge->setPen(QPen(Qt::white));
    }
}

void NodeGraphicsItem::addTextItem() {
    textItem = new QGraphicsSimpleTextItem(node->toString());
    textItem->setParentItem(this);
    textItem->setPen(QPen(Qt::white));
    QRectF textRect = textItem->boundingRect();
    textItem->setPos(-textRect.width() / 2, -textRect.height() / 2);
}

void NodeGraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsEllipseItem::mouseDoubleClickEvent(event);
    auto *menu = new QMenu;
    QAction *action1 = menu->addAction("Action 1");
    QAction *action2 = menu->addAction("Action 2");
    menu->exec(QCursor::pos());
}

void NodeGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsEllipseItem::mouseMoveEvent(event);
    if (node->getParent()) {
        node->getParent()->getItem()->updateEdges();
    } else {
        node->getItem()->updateEdges();
    }
}

void NodeGraphicsItem::updateEdges() const {
    const auto &children = node->getChildren();
    QPointF pos = scenePos();

    int n = edges.size();
    for (int i = 0; i < n; ++i) {
        auto *child = children[i]->getItem();

        if (!child->isVisible()) {
            continue;
        }

        QPointF childPos = child->scenePos();
        edges[i]->setLine(0, 0, childPos.x() - pos.x(), childPos.y() - pos.y());
        child->updateEdges();
    }
}
