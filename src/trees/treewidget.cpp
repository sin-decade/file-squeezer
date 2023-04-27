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
#include "treewidget.hpp"
#include "node.hpp"


int find_depth(const Node *root) {
    const auto &children = root->getChildren();

    if (children.empty()) {
        return 1; // if the root has no children, return 1
    }

    int max_child_depth = 0;
    for (const auto *child: children) {
        max_child_depth = std::max(max_child_depth, find_depth(child));
    }

    return 1 + (max_child_depth ? max_child_depth : 0);
}

Node *generateTree(int depth) {
    if (depth == 0) {
        return new Node(1 + rand() % 100);
    }
    const int num_children = rand() % 7;
    QVector<Node *> children(num_children);
    for (int i = 0; i < num_children; i++) {
        children[i] = generateTree(depth - 1);
    }
    return children.isEmpty() ? new Node(rand() % 100) : new Node(children);
}

void TreeWidget::drawTree(QVector<Node *> parents, int y) {
    int x = width() / (parents.size() + 1);
    QVector<Node *> children;
    for (int offset = x, i = 0; i < parents.size(); i++, offset += x) {
        auto *nodeItem = new NodeGraphicsItem(parents[i]);
        nodeItem->setRect(-radius_, -radius_, 2 * radius_, 2 * radius_);
        nodeItem->setPos(offset, y);
        scene->addItem(nodeItem);
        children.append(parents[i]->getChildren());
    }
    if (!children.isEmpty()) {
        drawTree(children, y + levelStep);
    }
}

void TreeWidget::drawTree() {
    int depth = find_depth(root_);
    if (depth == 1) {
        levelStep = height();
    } else {
        levelStep = (height() - 3 * radius_) / (depth - 1);
    }
    drawTree({root_}, radius_);
    root_->getItem()->updateEdges();
}

TreeWidget::TreeWidget(Node *root, QWidget *parent)
        : QGraphicsView(parent), root_(root) {
    if (!root_) {
        root_ = generateTree(rand() % 7);
    }
    scene = new QGraphicsScene(this);
    setScene(scene);
    setAlignment(Qt::AlignLeft | Qt::AlignTop);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    drawTree();
}

void TreeWidget::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    scene->clear();
    drawTree();
}
