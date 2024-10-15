#include "Grid.h"
#include <iostream>

int main()
{
    const int windowWidth = 1024;
    const int windowHeight = 768;

    const int cellSize = 40;
    sf::Vector2f gridPosition(100.0f, 80.f);
    Grid grid(cellSize, 15, 20, gridPosition.x, gridPosition.y);

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Ray-casting in 2D grid");

    // instructions
    sf::Font font;
    if (!font.loadFromFile("fonts/arial.ttf")) {
        std::cerr << "Error: Font not found." << std::endl;
        return -1;
    }
    sf::Text instructions;
    instructions.setFont(font);
    instructions.setString("Left-click to set start position");
    instructions.setCharacterSize(16);
    instructions.setFillColor(sf::Color::White);
    instructions.setPosition(10.f, 10.f);

    // default ray at center of window
    sf::Vector2f rayStart(windowWidth / 2.0f, windowHeight / 2.0f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
					window.close();
			}
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                // left-click sets the start position of the line
                if (event.mouseButton.button == sf::Mouse::Left)
                    rayStart = sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
            }
        }

        // start render
        window.clear(sf::Color::Black);

        // mouse position relative to the window
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f rayEnd(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        // create ray
        // get ray direction
        sf::Vector2f dir = rayEnd - rayStart;
        float lineLength = sqrt(dir.x * dir.x + dir.y * dir.y);
        dir /= lineLength;
        Ray ray(rayStart, dir);
        // get the intersection path
        std::vector<sf::Vector2i> path = grid.getIntersect(ray, lineLength);

        // draw the grid
        sf::RectangleShape cellShape(sf::Vector2f(static_cast<float>(grid.cellSize()), static_cast<float>(grid.cellSize())));
        cellShape.setFillColor(sf::Color(50, 50, 50));
        cellShape.setOutlineThickness(1.0f);
        cellShape.setOutlineColor(sf::Color(150, 150, 150));

        for (int row = 0; row < grid.rows(); row++)
        {
            for (int col = 0; col < grid.cols(); col++)
            {
                cellShape.setPosition(grid.getCellCoords(sf::Vector2i(col, row)));

                // check if the current cell is in the intersection path
                if (std::find(path.begin(), path.end(), sf::Vector2i(col, row)) != path.end())
                    cellShape.setFillColor(sf::Color(100, 100, 100));
                else
                    cellShape.setFillColor(sf::Color(50, 50, 50));

                window.draw(cellShape);
            }
        }

        // draw ray
        sf::Vertex line[] = { sf::Vertex(rayStart, sf::Color::Red), sf::Vertex(rayEnd, sf::Color::Red) };
        window.draw(line, 2, sf::Lines);

        // draw the instruction text
        window.draw(instructions);

        window.display();
    }
}
