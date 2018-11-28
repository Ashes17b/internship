#include <iostream>

namespace iterator {
    template <class Generator>
    class generator_iterator {
      public:
        generator_iterator() {}
        generator_iterator(Generator *g) : m_g(g), m_value((*m_g)()) {}

        generator_iterator
        & operator++() {
            m_value = (*m_g)();
            return *this;
        }

        generator_iterator
        operator++(int) {
            generator_iterator result(*this);
            ++(*this);
            return result;
        }

        typename Generator::result_type 
        operator *() const {
            return m_value;
        }

        bool equal(generator_iterator const &y) const {
            return this->m_g == y.m_g && this->m_value == y.m_value;
        }

      private:
        Generator *m_g;
        typename Generator::result_type m_value;
    };

    template <class Generator>
    struct generator_iterator_generator {
        typedef generator_iterator<Generator> type;
    };

    template <class Generator>
    constexpr generator_iterator<Generator>
    make_generator_iterator(Generator &gen) {
        typedef generator_iterator<Generator> result_t;
        return result_t(&gen);
    }
}

using iterator::generator_iterator;
using iterator::generator_iterator_generator;
using iterator::make_generator_iterator;