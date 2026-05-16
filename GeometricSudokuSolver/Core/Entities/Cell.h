#ifndef CELL_H
#define CELL_H

class Cell {
public:
    Cell(int x, int y);

    int getX() const;
    int getY() const;
    int getValue() const;
    void setValue(int value);
    bool isInitial() const;
    void setInitial(bool initial);
    bool isHinted() const;
    void setHinted(bool hinted);

private:
    int m_x;
    int m_y;
    int m_value;
    bool m_isInitial;
    bool m_isHinted;
};

#endif