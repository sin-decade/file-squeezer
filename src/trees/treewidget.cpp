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
#include "node.hpp"
#include "treewidget.hpp"

Node *TreeWidget::generateTree(int depth) {
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

void TreeWidget::setTree(QVector<Node *> parents, int yOffset) {
    if (parents.isEmpty()) {
        return;
    }
    int x = width() / (parents.size() + 1);
    QVector<Node *> children;
    for (int offset = x, i = 0; i < parents.size(); i++, offset += x) {
        parents[i]->changePos(offset, yOffset);
        children.append(parents[i]->getChildren());
    }
    setTree(children, yOffset + level_step);
}

void TreeWidget::setTree() {
    int depth = _root->getDepth();
    level_step = (height() - 30) / qMax(1, depth - 1);
    setTree({_root}, 0);
}


TreeWidget::TreeWidget(Node *root, QWidget *parent)
        : QGraphicsView(parent), _root(root) {
    if (!_root) {
        _root = generateTree(rand() % 7);
    }
    _scene = new QGraphicsScene(this);
    setScene(_scene);
    setAlignment(Qt::AlignLeft | Qt::AlignTop);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    drawTree(_root);
    setTree();
    _size = rect().size();
}

void TreeWidget::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
//    fitInView(_scene->sceneRect(), Qt::IgnoreAspectRatio);
    _root->scalePos(rect().width() / _size.width(), rect().height() / _size.height());
    _size = rect().size();
}

void TreeWidget::drawTree(Node *root) {
    _scene->addItem(root);
    auto children = root->getChildren();
    for (auto &i: children) {
        drawTree(i);
    }
}
