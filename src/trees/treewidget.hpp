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

#ifndef FILE_SQUEEZER_TREEWIDGET_HPP
#define FILE_SQUEEZER_TREEWIDGET_HPP

// Qt
#include <QGraphicsView>

class Node;

/**
 * The TreeWidget class represents a widget that displays a tree structure.
 * It inherits QGraphicsView and manages a QGraphicsScene, where each node in the tree is represented
 * by a QGraphicsEllipseItem object.
 */
class TreeWidget : public QGraphicsView {
public:

    /**
     * Constructs a new TreeWidget with the given root node and parent widget.
     *
     * @param root The root node of the tree. If null, a random tree will be generated.
     * @param parent The parent widget of this TreeWidget.
     */
    explicit TreeWidget(Node *root = nullptr, QWidget *parent = nullptr);

    /**
     * Generates a random tree with the given _depth.
     *
     * @param depth The _depth of the tree to generate.
     * @return The root node of the generated tree.
     */
    static Node *generateTree(int depth);

protected:

    /**
     * This function is called when the widget is resized.
     * It resizes the nodes in the tree to fit the new _size of the widget.
     *
     * @param event The resize event.
     */
    void resizeEvent(QResizeEvent *event) override;

private:

    /**
     * This function sets the positions of the nodes in the tree.
     *
     * @param parents The nodes to set the positions of.
     * @param yOffset The y coordinate offset.
     */
    void setTree(QVector<Node *> parents, int yOffset);

    /**
     * This function recursively draws the tree starting from the given root node.
     *
     * @param root The root node of the tree to draw.
     */
    void drawTree(Node *root);

    /**
     * This function sets the positions of the nodes in the tree.
     */
    void setTree();

    QGraphicsScene *_scene; /**< The QGraphicsScene where the nodes in the tree are displayed. */
    Node *_root; /**< The root node of the tree. */
    QSizeF _size; /**< The _size of the widget. */
    int level_step{}; /**< The vertical distance between levels in the tree. */
};

#endif //FILE_SQUEEZER_TREEWIDGET_HPP
