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


#include "spinlock.hpp"

#include <thread>


namespace ccore {

namespace parallel {


bool spinlock::try_lock(void) {
    return !m_lock.test_and_set(std::memory_order_acquire);
}

void spinlock::lock(void) {
    for(std::size_t i = 0; !try_lock(); i++) {
        if (i % 100)
          std::this_thread::yield();
    }
}

void spinlock::unlock(void) {
    m_lock.clear(std::memory_order_release);
}


}

}