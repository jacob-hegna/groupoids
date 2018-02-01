#ifndef __GROUPOID_H_
#define __GROUPOID_H_

#include <memory>
#include <string>
#include <vector>

typedef unsigned int uint; // this is terrible

class Groupoid {
public:
    Groupoid() = delete;
    Groupoid(uint size);
    Groupoid(std::vector<std::vector<uint>> table);

    static std::shared_ptr<Groupoid> from_random(uint size);
    static std::shared_ptr<Groupoid> from_vector(std::vector<std::vector<uint>> table);

    bool set(uint a, uint b, uint ab);
    uint get(uint a, uint b);

    uint size();

    std::string to_str();

    bool operator==(const Groupoid& rhs);

private:
    const uint m_size;
    std::vector<std::vector<uint>> m_table;
};

typedef std::shared_ptr<Groupoid> GroupoidPtr;

#endif