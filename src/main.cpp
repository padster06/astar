#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <ctime>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Node.h"

using namespace sf;

Node *sort(std::vector<Node *> vec)
{
    float max = vec[0]->fCost;
    int index = 0;
    for (long unsigned int i = 0; i < vec.size(); i++)
    {
        if (vec[i]->fCost < max)
        {
            max = vec[i]->fCost;
            index = i;
        }
    }
    return vec[index];
}

int main()
{
    srand((unsigned)time(0));

    std::vector<std::vector<Node *>> nodes(800 / 20, std::vector<Node *>(800 / 20));

    std::vector<Node *> open;
    std::vector<Node *> closed;

    for (int i = 0; i < 800 / 20; i++)
    {
        // nodes.push_back(std::vector<Node>);
        for (int j = 0; j < 800 / 20; j++)
        {
            nodes[i][j] = new Node(i, j);
        }
    }

    for (int i = 0; i < 100; i++)
    {
        int highest = 800 / 20;
        int random_integer = rand() % highest;
        int random_integer2 = rand() % highest;
        nodes[random_integer][random_integer2]->walkable = false;
    }

    int highest = 800 / 20;
    int random_integer = rand() % highest;
    int random_integer2 = rand() % highest;
    auto start = nodes[random_integer][random_integer2];
    auto end = nodes[rand() % 40][rand() % 40];

    start->start = true;
    end->end = true;

    start->calculate(start, end);

    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }
            open.push_back(nodes[start->i + i][start->j + j]);
            nodes[start->i + i][start->j + j]->open = true;
            nodes[start->i + i][start->j + j]->calculate(start, end);
        }
    }

    std::cout << open.size();

    RenderWindow window(VideoMode(800, 800), "A*", Style::Close);
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        // Event processing
        Event event;
        while (window.pollEvent(event))
        {
            // Request for closing the window
            if (event.type == Event::Closed)
            {

                window.close();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        auto current = sort(open);
        // std::cout << current->fCost;
        if (current == end)
        {
            continue;
        }

        for (int i = -1; i < 2; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                if (i == 0 && j == 0)
                {
                    nodes[current->i + i][current->j + j]->closed = true;
                    nodes[current->i + i][current->j + j]->open = false;
                    open.erase(find(open.begin(), open.end(), nodes[current->i + i][current->j + j]));
                    closed.push_back(nodes[current->i + i][current->j + j]);
                }
                if (nodes[current->i + i][current->j + j]->closed || !nodes[current->i + i][current->j + j]->walkable || nodes[current->i + i][current->j + j]->start)
                {
                    continue;
                }
                else
                {
                    open.push_back(nodes[current->i + i][current->j + j]);
                    nodes[current->i + i][current->j + j]->open = true;
                    nodes[current->i + i][current->j + j]->calculate(start, end);
                }
            }
        }

        window.clear();

        for (int i = 0; i < 40; i++)
        {
            for (int j = 0; j < 40; j++)
            {
                nodes[i][j]->draw(window);
            }
        }

        window.display();
    }
    return 0;
}