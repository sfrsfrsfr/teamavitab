/*
 *   AviTab - Aviator's Virtual Tablet
 *   Copyright (C) 2018-2026 Folke Will and Avitab Contributors
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Affero General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Affero General Public License for more details.
 *
 *   You should have received a copy of the GNU Affero General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "Timer.h"
#include <thread>
#include "Logger.h"

namespace avitab {

Timer::Timer(TimerFunc callback, int periodMs):
    func(callback)
{
    logger::verbose("Creating timer in thread %d", std::this_thread::get_id());
    task = lv_timer_create([] (lv_timer_t *tsk) {
        Timer *tmr = (Timer *)(lv_timer_get_user_data(tsk));
        bool wantContinue = tmr->func();
        if (!wantContinue) {
            tmr->stop();
        }
    }, periodMs, this);
}

void Timer::stop() {
    if (task) {
        lv_timer_delete(task);
        task = nullptr;
    }
}

Timer::~Timer() {
    logger::verbose("Destroying timer in thread %d", std::this_thread::get_id());
    stop();
}

} /* namespace avitab */
