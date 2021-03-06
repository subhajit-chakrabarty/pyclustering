/**
*
* Copyright (C) 2014-2018    Andrei Novikov (pyclustering@yandex.ru)
*
* GNU_PUBLIC_LICENSE
*   pyclustering is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   pyclustering is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*/

#pragma once


#include <vector>


namespace ccore {

namespace clst {


using wce_sequence      = std::vector<double>;


class elbow_data {
private:
    std::size_t           m_amount  = 0;
    wce_sequence          m_wce     = { };

public:
    elbow_data(void) = default;

    ~elbow_data(void) = default;

public:
    const wce_sequence & get_wce(void) const { return m_wce; }

    wce_sequence & get_wce(void) { return m_wce; }

    void set_amount(const std::size_t p_amount) { m_amount = p_amount; }

    std::size_t get_amount(void) { return m_amount; }
};


}

}