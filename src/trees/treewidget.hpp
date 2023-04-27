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
 * @brief The TreeWidget class is responsible for creating and updating the visualization of the tree.
 */
class TreeWidget : public QGraphicsView {
public:
    /**
     * @brief Constructs a TreeWidget object with a root node and a parent widget.
     * @param root The root node of the tree.
     * @param parent The parent widget of the TreeWidget.
     */
    explicit TreeWidget(Node *root = nullptr, QWidget *parent = nullptr);

protected:
    /**
     * @brief Overrides the resize event of QGraphicsView to update the scene.
     * @param event A pointer to the resize event.
     */
    void resizeEvent(QResizeEvent *event) override;

private:
    /**
     * @brief Recursively draws the tree starting from the given parents at the specified y-coordinate.
     * @param parents The parent nodes of the current level.
     * @param y The y-coordinate of the current level.
     */
    void drawTree(QVector<Node *> parents, int y);

    /**
     * @brief Draws the entire tree by calling drawTree with the root node.
     */
    void drawTree();

    Node *root_; /**< The root node of the tree. */
    int radius_ = 10; /**< The radius of each node. */
    int levelStep{}; /**< The vertical spacing between each level. */
    QGraphicsScene *scene; /**< The scene containing the tree visualization. */
};

#endif //FILE_SQUEEZER_TREEWIDGET_HPP
