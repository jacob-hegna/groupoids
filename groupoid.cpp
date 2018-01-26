#include "groupoid.h"

#include <random>
#include <sstream>

Groupoid::Groupoid(uint size)
    : m_size(size) {

    for(int i = 0; i < m_size; ++i) {
        m_table.emplace_back(m_size);
    }
}

Groupoid::Groupoid(std::vector<std::vector<uint>> table)
    : m_size(table.size())
    , m_table(table)
    {}


/* static */ GroupoidPtr Groupoid::from_random(uint size) {
    auto groupoid = std::make_shared<Groupoid>(size);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, size - 1);

    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            groupoid->set(i, j, dist(mt));
        }
    }
    return groupoid;
}

bool Groupoid::set(uint a, uint b, uint ab) {
    if(a >= m_size || b >= m_size) {
        return false;
    }

    m_table[a][b] = ab;
    return true;
}

uint Groupoid::get(uint a, uint b) {
    if(a >= m_size || b >= m_size) {
        return m_size;
    }

    return m_table[a][b];
}

uint Groupoid::size() {
    return m_size;
}

std::string Groupoid::to_str() {
    std::stringstream ss;

    for(int i = 0; i < m_size; ++i) {
        for(int j = 0; j < m_size; ++j) {
            ss << m_table[i][j] << " ";
        }
        if(i != m_size - 1) ss << std::endl;
    }

    return ss.str();
}

bool Groupoid::operator==(const Groupoid& rhs) {
    return this->m_table == rhs.m_table;
}
