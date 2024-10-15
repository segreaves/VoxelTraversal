#pragma once
#include <SFML/Graphics.hpp>

struct Ray
{
    Ray(const sf::Vector2f& start, const sf::Vector2f& dir) :
        m_start(start),
        m_dir(dir)
    {
    }

    sf::Vector2f m_start;
    sf::Vector2f m_dir;
};

class Grid
{
public:
    Grid(int cellSize, int rows, int cols, float posX, float posY);

    int cellSize() const { return m_cellSize; }
    int rows() const { return m_rows; }
    int cols() const { return m_cols; }

    float getLeftEdge() const { return m_posX; }
    float getRightEdge() const { return m_posX + m_cols * m_cellSize; }
    float getTopEdge() const { return m_posY; }
    float getBottomEdge() const { return m_posY + m_rows * m_cellSize; }
    bool isCellValid(const int& col, const int& row) const;
    bool isCellValid(const sf::Vector2i& cell) const { return isCellValid(cell.x, cell.y); }
    bool contains(float x, float y) const;
    bool contains(const sf::Vector2f& coords) const { return contains(coords.x, coords.y); }
    sf::Vector2i getCell(const sf::Vector2f& coords) const;
    sf::Vector2f getCellCoords(const sf::Vector2i& cell) const;
    std::vector<sf::Vector2i> getIntersect(const Ray& ray, float maxTraversal = std::numeric_limits<float>::infinity()) const;
private:
    int m_cellSize, m_rows, m_cols;
    float m_posX, m_posY;
};
