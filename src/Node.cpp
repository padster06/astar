#include "Node.h"

#include <iostream>

Node::Node(int p_i, int p_j)
{
    start = end = false;
    walkable = true;
    closed = false;
    open = false;
    w = 20;
    i = p_i;
    j = p_j;
    shape.setFillColor(Color::White);
    shape.setOutlineColor(Color::Black);
    shape.setOutlineThickness(3);
    shape.setSize(Vector2f(w, w));
    shape.setPosition(Vector2f(i * w, j * w));
}

void Node::calculate(Node *start, Node *end)
{
    // if ((start->i - 1 == i && start->j == j) || (start->i + 1 == i && start->j == j) || (start->i == i && start->j - 1 == j) || (start->i == i && start->j + 1 == j))
    // {
    //     gCost += 10;
    // }
    // else if ((start->i + 1 == i && start->j + 1 == j) || (start->i + 1 == i && start->j - 1 == j) || (start->i - 1 == i && start->j + 1 == j) || (start->i - 1 == i && start->j - 1 == j))
    // {
    //     gCost += 14;
    // }
    gCost = sqrt(((i - start->i) * (i - start->i)) + ((j - start->j) * (j - start->j))) * 10;

    hCost = sqrt(((i - end->i) * (i - end->i)) + ((j - end->j) * (j - end->j))) * 10;
    fCost = hCost + gCost;
}

void Node::draw(RenderWindow &window)
{
    if (!walkable)
    {
        shape.setFillColor(Color::Black);
    }
    if (open)
    {
        shape.setFillColor(Color::Green);
    }
    if (start || end)
    {
        shape.setFillColor(Color::Blue);
    }
    if (closed)
    {
        shape.setFillColor(Color::Red);
    }
    window.draw(shape);
}