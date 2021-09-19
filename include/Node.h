#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

using namespace sf;

class Node
{
public:
    Node(int p_i, int p_j);
    void draw(RenderWindow &window);
    void calculate(Node *start, Node *end);

    bool closed, open, walked, walkable, start, end;
    float fCost, hCost, gCost;
    int w, x, y, i, j;

private:
    RectangleShape shape;
};