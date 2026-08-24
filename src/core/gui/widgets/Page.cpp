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
#include "Page.h"

namespace avitab {

Page::Page(WidgetPtr parent):
    Widget(parent)
{
    lv_obj_t *page = lv_obj_create(parentObj());
    lv_obj_set_style_pad_hor(page, 0 , 0);
    lv_obj_set_style_pad_ver(page, 0 , 0);
    setObj(page);
}

Page::Page(WidgetPtr parent, lv_obj_t *page):
    Widget(parent)
{
    setManagedObj(page);

    lv_obj_set_style_pad_hor(page, 0 , 0);
    lv_obj_set_style_pad_ver(page, 0 , 0);
}

void Page::clear() {
    lv_obj_clean((obj()));
}

int Page::getContentWidth() {
    lv_obj_update_layout(obj());
    return lv_obj_get_width(obj());
}

int Page::getContentHeight() {
    lv_obj_update_layout(obj());
    return lv_obj_get_height(obj());
}
/* FIXME
void Page::setFit(bool horz, bool vert) {
    lv_page_set_scrl_fit2(obj(), horz, vert);
}

void Page::setLayoutCenterColumns() {
    lv_page_set_scrl_layout(obj(), LV_LAYOUT_CENTER);
}

void Page::setLayoutRows() {
    lv_page_set_scrl_layout(obj(), LV_LAYOUT_ROW_T);
}
*/

} /* namespace avitab */
