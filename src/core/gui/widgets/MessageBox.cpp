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

MessageBox::MessageBox(WidgetPtr parent, const std::string &text, const std::string &caption, Callback cb):
    Widget(parent)
{
    // FIXME support more than one button again
    std::string title = "";
    buttons.pop_back();
    buttons.push_back(strdup(caption.c_str()));
    // invariant: the last entry of buttons is always an empty string
    buttons.push_back("");

    callbacks.push_back(cb);

    lv_obj_t *mbox = lv_msgbox_create(parentObj(), title.c_str(), text.c_str(), &buttons[0], false);
    addCallback();

    lv_obj_set_user_data(mbox, this);
    setObj(mbox);

    lv_obj_set_width(mbox, lv_obj_get_width(parentObj()) / 2);

}
/* FIXME
void MessageBox::addButton(const std::string& caption, Callback cb) {
    buttons.pop_back();
    buttons.push_back(strdup(caption.c_str()));
    buttons.push_back("");

    callbacks.push_back(cb);

    lv_msgbox_add_btns(obj(), &buttons[0]);
    lv_obj_add_event_cb(obj(), [] (lv_event_t *e) {
        lv_obj_t *o = lv_event_get_current_target(e);
        const char *txt = lv_msgbox_get_active_btn_text(o);
        if (!txt) {
            return;
        }

        MessageBox *us = reinterpret_cast<MessageBox *>(lv_obj_get_user_data(o));
        if (us) {
            for (size_t i = 0; i < us->buttons.size(); i++) {
                if (strcmp(us->buttons[i], txt) == 0) {
                    us->callbacks[i]();
                    break;
                }
            }
        }
    }, LV_EVENT_CLICKED, nullptr);
}
*/
void MessageBox::addCallback() {
    lv_obj_t *btnm = lv_msgbox_get_btns(obj());

    lv_obj_add_event_cb(btnm, [] (lv_event_t *e) {
        lv_obj_t *o = lv_event_get_current_target(e);
        lv_event_code_t ev = lv_event_get_code(e);
        if (ev == LV_EVENT_VALUE_CHANGED) {
            const char *txt = lv_msgbox_get_active_btn_text(o);
            if (!txt) {
                return;
            }

            MessageBox *us = reinterpret_cast<MessageBox *>(lv_obj_get_user_data(o));
            if (us) {
                for (size_t i = 0; i < us->buttons.size(); i++) {
                    if (strcmp(us->buttons[i], txt) == 0) {
                        us->callbacks[i]();
                        break;
                    }
                }
            }
        }
    }, LV_EVENT_ALL, nullptr);
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
