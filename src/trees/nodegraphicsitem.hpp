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

#ifndef FILE_SQUEEZER_NODEGRAPHICSITEM_HPP
#define FILE_SQUEEZER_NODEGRAPHICSITEM_HPP

// Qt
#include <QGraphicsEllipseItem>

class Node;

/**
 * @class NodeGraphicsItem
 * @brief A QGraphicsEllipseItem representing a node in a tree.
 */
class NodeGraphicsItem : public QGraphicsEllipseItem {
public:
    /**
     * @brief Constructs a NodeGraphicsItem.
     * @param node The node represented by this item.
     * @param parent The parent QGraphicsItem, if any.
     */
    explicit NodeGraphicsItem(Node *node, QGraphicsItem *parent = nullptr);

    /**
     * @brief Adds a text item to this NodeGraphicsItem.
     */
    void addTextItem();

    /**
     * @brief Updates the edges connecting this NodeGraphicsItem to its children.
     */
    void updateEdges() const;

protected:
    /**
     * @brief Handles mouse move events for this NodeGraphicsItem.
     * @param event The mouse event.
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    /**
     * @brief Handles mouse double-click events for this NodeGraphicsItem.
     * @param event The mouse event.
     */
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QGraphicsSimpleTextItem *textItem{};
    Node *node;
    std::vector<QGraphicsLineItem *> edges;
};



#endif //FILE_SQUEEZER_NODEGRAPHICSITEM_HPP
