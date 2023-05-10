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

#include <QGraphicsEllipseItem>

/**
 * @brief The Node class represents a node in a tree.
 */
class Node : public QGraphicsEllipseItem {
public:
    /**
     * @brief Constructs a node with a given key value and a parent item.
     * @param key The key value of the node.
     * @param parent The parent item of the node.
     */
    explicit Node(int key, QGraphicsItem *parent = nullptr);

    /**
     * @brief Constructs a node with a vector of children and a parent item.
     * @param children The vector of children of the node.
     * @param parent The parent item of the node.
     */
    explicit Node(QVector<Node *> children, QGraphicsItem *parent = nullptr);

    /**
     * @brief Sets the parent node and the edge that connects the parent and this node.
     * @param node The parent node.
     * @param edge The edge that connects the parent and this node.
     */
    void setParent(Node *node, QGraphicsLineItem *edge);

    /**
     * @brief Returns the vector of children of the node.
     * @return The vector of children of the node.
     */
    QVector<Node *> getChildren() const;

    int getChildrenCount() const;

    /**
     * @brief Returns the depth of the node in the tree.
     * @return The depth of the node in the tree.
     */
    int getDepth() const;

    /**
     * @brief Changes the position of the node.
     * @param ax The horizontal displacement.
     * @param ay The vertical displacement.
     */
    void changePos(qreal ax, qreal ay);

    /**
     * @brief Changes the position of the node.
     * @param newPos The position.
     */
    void changePos(QPointF newPos);

    /**
     * @brief Scales the position of the node.
     * @param ax The horizontal scaling factor.
     * @param ay The vertical scaling factor.
     */
    void scalePos(qreal ax, qreal ay);

    /**
     * @brief Returns the parent edge of the node.
     * @return The parent edge of the node.
     */
    QGraphicsLineItem *getParentEdge();

    /**
     * @brief Changes the order of the two vertices relative to the parent.
     */
    void swapPos(Node *right, Node *left);

    void relocateChildren(const QVector<Node *>& nodes);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    /**
     * @brief Sets the graphic properties of the node.
     */
    void setGraphic();

    /**
     * @brief Adds a text item to the node.
     */
    void addTextItem();

    /**
     * @brief Adds edges to the children of the node.
     */
    void addLinks();

    /**
     * @brief Returns a string representation of the node.
     * @return A string representation of the node.
     */
    QString toString() const;

    /**
     * @brief Changes the position of the edge associated with the node.
     */
    void updateEdge();

    QGraphicsSimpleTextItem *textItem{}; /**< The text item of the node. */
    QGraphicsLineItem *parentEdge = nullptr; /**< The edge that connects the parent and this node. */

    Node *_parent = nullptr; /**< The parent node of the node. */
    QVector<Node *> _children; /**< The vector of children of the node. */
    int _key = 0; /**< The key value of the node. */
    int _depth = 0; /**< The _depth of the node in the tree. */
    qreal _radius = 10; /**< The _radius of the node. */
};

#endif //FILE_SQUEEZER_NODE_HPP

