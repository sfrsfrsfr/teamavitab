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
#include <cstring>
#include <cstdlib>
#include "MessageBox.h"
#include "Logger.h"

namespace avitab {

MessageBox::MessageBox(WidgetPtr parent, const std::string& text, const std::vector<std::string>& captions):
    Widget(parent)
{
    std::string title = "";
    for (auto btn : captions) {
        buttons.push_back(strdup(btn.c_str()));
    }
    // invariant: the last entry of buttons is always an empty string
    buttons.push_back("");

    lv_obj_t *mbox = lv_msgbox_create(parentObj(), title.c_str(), text.c_str(), buttons.data(), false);

    setObj(mbox);

    lv_obj_set_width(mbox, lv_obj_get_width(parentObj()) / 2);
}

MessageBox::MessageBox(WidgetPtr parent, const std::string& text):
    Widget(parent)
{
    std::string title = "";
    // invariant: the last entry of buttons is always an empty string
    buttons.push_back("");

    lv_obj_t *mbox = lv_msgbox_create(parentObj(), title.c_str(), text.c_str(), buttons.data(), true);

    setObj(mbox);

    lv_obj_set_width(mbox, lv_obj_get_width(parentObj()) / 2);
}

void MessageBox::setCallback(Callback cb) {
    callbackFunc = cb;
    lv_obj_set_user_data(obj(), this);

    lv_obj_add_event_cb(obj(), [] (lv_event_t *e) {
        lv_obj_t *o = lv_event_get_current_target(e);
        MessageBox *us = reinterpret_cast<MessageBox *>(lv_obj_get_user_data(o));
        if (us->callbackFunc) {
            us->callbackFunc(lv_msgbox_get_active_btn(o));
        }
    }, LV_EVENT_VALUE_CHANGED, nullptr);
}

MessageBox::~MessageBox() {
    if (!buttons.empty()) {
        for (size_t i = 0; i < buttons.size() - 1; i++) {
            free((void *) buttons[i]);
            buttons[i] = "";
        }
    }
}

} /* namespace avitab */
