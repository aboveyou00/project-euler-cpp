#include "stdafx.h"
#include "euler.h"

class MinPathSumFourWays
{
private:
    MinPathSumFourWays(std::vector<std::vector<uint64_t>*> *data)
    {
        auto width = data->at(0)->size();
        auto height = data->size();

        m_width = width;
        m_height = height;

        m_edgeCost = new uint64_t[width * height];
        m_nodes = new Node[width * height];

        m_minEdgeLength = std::numeric_limits<uint64_t>::max();

        for (size_t w = 0; w < height; w++)
        {
            auto row = data->at(w);
            for (size_t q = 0; q < height; q++)
            {
                auto val = row->at(q);
                this->edgeCost(q, w) = val;
                if (val < m_minEdgeLength)
                {
                    m_minEdgeLength = val;
                }
            }
        }


        for (size_t w = 0; w < height; w++)
        {
            auto row = data->at(w);
            for (size_t q = 0; q < height; q++)
            {
                auto &node = this->nodes(q, w);
                node.x = q;
                node.y = w;
                node.g = std::numeric_limits<uint64_t>::max();
                node.h = m_minEdgeLength * ((width - q) + (height - w) - 1);
                node.isClosed = false;
            }
        }
    }
    ~MinPathSumFourWays()
    {
        delete[] m_edgeCost;
    }

    struct Node
    {
        size_t x;
        size_t y;
        uint64_t g;
        uint64_t h;

        bool isClosed;
    };

public:
    static MinPathSumFourWays *parse(std::string str)
    {
        //Assumption: None of the parsed values will be 0
        //Assumption: None of the parsed values will overflow a 32-bit unsigned integer

        size_t idx = 0;
        uint64_t collected = 0;
        size_t requiredCols = 0;
        auto rows = new std::vector<std::vector<uint64_t>*>();
        auto currentRow = new std::vector<uint64_t>();

        while (idx <= str.length())
        {
            auto chr = (idx == str.length()) ? '\n' : str.at(idx);
            idx++;

            if (chr >= '0' && chr <= '9')
            {
                collected = (collected * 10) + (chr - '0');
            }
            else if (chr == ' ' || chr == ',' || chr == '\r' || chr == '\n')
            {
                if (collected != 0)
                {
                    currentRow->push_back(collected);
                    collected = 0;
                }
                if ((chr == '\r' || chr == '\n') && currentRow->size() > 0)
                {
                    if (requiredCols == 0)
                    {
                        requiredCols = currentRow->size();
                    }
                    else if (currentRow->size() != requiredCols)
                    {
                        throw std::exception("Parsed line with an unexpected number of values");
                    }
                    rows->push_back(currentRow);
                    currentRow = new std::vector<uint64_t>();
                }
            }
            else
            {
                throw std::exception("Unparsable character.");
            }
        }

        delete currentRow;
        return new MinPathSumFourWays(rows);
    }

    static inline uint64_t eval(std::string str)
    {
        auto mp = parse(str);
        mp->reduce();
        auto result = mp->answer();
        delete mp;
        return result;
    }

    void reduce()
    {
        std::vector<Node*> open;

        this->nodes(0, 0).g = this->edgeCost(0, 0);
        open.push_back(&this->nodes(0, 0));

        while (open.size() > 0)
        {
            uint64_t minf = std::numeric_limits<uint64_t>::max();
            size_t nextNodeIdx = 0;
            
            for (size_t q = 0; q < open.size(); q++)
            {
                auto &node = *open.at(q);
                auto f = node.g + node.h;
                if (f < minf)
                {
                    minf = f;
                    nextNodeIdx = q;
                }
            }

            {
                auto &node = *open.at(nextNodeIdx);
                open.erase(open.begin() + nextNodeIdx);
                node.isClosed = true;

                if (node.x == m_width - 1 && node.y == m_height - 1)
                {
                    break;
                }

                if (node.x > 0)
                {
                    auto &left = this->nodes(node.x - 1, node.y);
                    auto newg = node.g + this->edgeCost(node.x - 1, node.y);
                    if (!left.isClosed)
                    {
                        auto it = std::find(open.begin(), open.end(), &left);
                        if (it == open.end())
                        {
                            open.push_back(&left);
                        }
                        left.g = min(newg, left.g);
                    }
                }

                if (node.y > 0)
                {
                    auto &up = this->nodes(node.x, node.y - 1);
                    auto newg = node.g + this->edgeCost(node.x, node.y - 1);
                    if (!up.isClosed)
                    {
                        auto it = std::find(open.begin(), open.end(), &up);
                        if (it == open.end())
                        {
                            open.push_back(&up);
                        }
                        up.g = min(newg, up.g);
                    }
                }

                if (node.x < m_width - 1)
                {
                    auto &right = this->nodes(node.x + 1, node.y);
                    auto newg = node.g + this->edgeCost(node.x + 1, node.y);
                    if (!right.isClosed)
                    {
                        auto it = std::find(open.begin(), open.end(), &right);
                        if (it == open.end())
                        {
                            open.push_back(&right);
                        }
                        right.g = min(newg, right.g);
                    }
                }

                if (node.y < m_height - 1)
                {
                    auto &down = this->nodes(node.x, node.y + 1);
                    auto newg = node.g + this->edgeCost(node.x, node.y + 1);
                    if (!down.isClosed)
                    {
                        auto it = std::find(open.begin(), open.end(), &down);
                        if (it == open.end())
                        {
                            open.push_back(&down);
                        }
                        down.g = min(newg, down.g);
                    }
                }
            }
        }
    }
    uint64_t answer() const
    {
        return nodes(m_width - 1, m_height - 1).g;
    }

private:
    template <typename T>
    T &at(size_t x, size_t y, T *data)
    {
        if (x > m_width || y > m_height)
        {
            throw std::exception("Index out of bounds!");
        }
        return data[x + (y * m_width)];
    }
    template <typename T>
    const T &at(size_t x, size_t y, T *data) const
    {
        if (x > m_width || y > m_height)
        {
            throw std::exception("Index out of bounds!");
        }
        return data[x + (y * m_width)];
    }

    uint64_t &edgeCost(size_t x, size_t y)
    {
        return this->at(x, y, m_edgeCost);
    }
    uint64_t edgeCost(size_t x, size_t y) const
    {
        return this->at(x, y, m_edgeCost);
    }
    Node &nodes(size_t x, size_t y)
    {
        return this->at(x, y, m_nodes);
    }
    const Node &nodes(size_t x, size_t y) const
    {
        return this->at(x, y, m_nodes);
    }

    uint32_t m_width, m_height;
    uint64_t m_minEdgeLength;
    uint64_t *m_edgeCost;
    Node *m_nodes;
};

std::uint64_t euler<83>::value()
{
    //Should be 2297
    //    auto testVal = MinPathSumFourWays::eval(R"HEREDOC(
    //131,673,234,103,18
    //201,96, 342,965,150
    //630,803,746,422,111
    //537,699,497,121,956
    //805,732,524,37, 331
    //)HEREDOC");
    //    return testVal;

    auto input = readFile("path-sum-matrix.txt");
    return MinPathSumFourWays::eval(input);
}
