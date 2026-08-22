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

MessageBox::MessageBox(WidgetPtr parent, const std::string &text):
    Widget(parent)
{
    lv_obj_t *mbox = lv_msgbox_create(parentObj());
    lv_msgbox_add_text(mbox, text.c_str());
    lv_obj_set_user_data(mbox, this);
    setObj(mbox);

    lv_obj_set_width(mbox, lv_obj_get_width(parentObj()) / 2);
}

void MessageBox::addButton(const std::string& caption, Callback cb) {
    lv_obj_t *button = lv_msgbox_add_footer_button(obj(), caption.c_str());
    lv_obj_set_user_data(button, this);
    buttons.push_back(button);
    callbacks.push_back(cb);

    lv_obj_add_event_cb(button, [] (lv_event_t *e) {
        lv_obj_t *o = lv_event_get_target_obj(e);
        MessageBox *us = reinterpret_cast<MessageBox *>(lv_obj_get_user_data(o));
        if (us) {
            for (size_t i = 0; i < us->buttons.size(); i++) {
                if (us->buttons[i] == o) {
                    us->callbacks[i]();
                    break;
                }
            }
        }
    }, LV_EVENT_CLICKED, nullptr);
}

} /* namespace avitab */
