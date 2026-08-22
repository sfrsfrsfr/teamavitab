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
#include "List.h"

namespace avitab {

List::List(WidgetPtr parent):
    Widget(parent)
{
    lv_obj_t *lst = lv_list_create(parentObj());
    lv_obj_set_user_data(lst, this);
    grp = lv_group_create();
    setObj(lst);
}

void List::setCallback(ListCallback cb) {
    onSelect = cb;
}

void List::add(const std::string& entry, int data) {
    add(entry, Widget::Symbol::NONE, data);
}

void List::add(const std::string& entry, Symbol smb, int data) {
    lv_obj_t *btn = lv_list_add_button(obj(), symbolToLVSymbol(smb), entry.c_str());
    lv_obj_set_user_data(btn, reinterpret_cast<void *>(data));
    lv_group_add_obj(grp, btn);

    lv_obj_add_event_cb(btn, [] (lv_event_t *e) {
        lv_obj_t *o = lv_event_get_target_obj(e);
        lv_obj_t *listObj = lv_obj_get_parent(lv_obj_get_parent(o));
        void *list = lv_obj_get_user_data(listObj);
        if (list) {
            int usrData = reinterpret_cast<intptr_t>(lv_obj_get_user_data(o));
            reinterpret_cast<List *>(list)->onSelect(usrData);
        }
    }, LV_EVENT_CLICKED, nullptr);
}

void List::clear() {
    lv_obj_clean(obj());
}

void List::scrollUp() {
    lv_group_focus_prev(grp);
}

void List::scrollDown() {
    lv_group_focus_next(grp);
}

} /* namespace avitab */
