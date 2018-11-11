#pragma once

class MaximumPath
{
private:
    MaximumPath(std::vector<std::vector<uint64_t>*> *data);
    ~MaximumPath();

public:
    static MaximumPath *parse(std::string str);

    static inline uint64_t eval(std::string str)
    {
        auto mp = parse(str);
        mp->reduce();
        auto result = mp->tip();
        delete mp;
        return result;
    }

    void reduce();
    uint64_t tip() const;

private:
    std::vector<std::vector<uint64_t>*> *m_data;
};
