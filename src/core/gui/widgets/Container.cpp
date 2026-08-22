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
#include "Container.h"

namespace avitab {

Container::Container(WidgetPtr parent):
    Widget(parent)
{
    lv_obj_t *cont = lv_obj_create(parentObj());
    lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_hor(cont, 2 , 0);
    lv_obj_set_style_pad_ver(cont, 2 , 0);
    setObj(cont);
}

Container::Container():
    Widget(nullptr)
{
    lv_obj_t *cont = lv_obj_create(lv_screen_active());
    lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_pad_hor(cont, 2 , 0);
    lv_obj_set_style_pad_ver(cont, 2 , 0);
    setObj(cont);
}

void Container::setLayoutFlex() {
    lv_obj_set_flex_flow(obj(), LV_FLEX_FLOW_ROW_WRAP);
    //lv_obj_align(obj(), LV_FLEX_ALIGN_SPACE_BETWEEN, 0, 0);
    lv_obj_set_flex_align(obj(),  LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
}

void Container::setLayoutGrid() {
    lv_obj_set_layout(obj(), LV_LAYOUT_GRID);
}

void Container::setGridArray(std::vector<lv_coord_t> cols, std::vector<lv_coord_t> rows) {
    lv_coord_t col_dsc[cols.size() + 1];
    lv_coord_t row_dsc[rows.size() + 1];

    std::transform(cols.begin(),cols.end(),col_dsc,[](const lv_coord_t& x){
	return x;
    });
    col_dsc[sizeof(col_dsc) - 1] = LV_GRID_TEMPLATE_LAST;

    std::transform(rows.begin(),rows.end(),row_dsc,[](const lv_coord_t& x){
	return x;
    });
    row_dsc[sizeof(row_dsc) - 1] = LV_GRID_TEMPLATE_LAST;

    lv_obj_set_size(obj(), LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_grid_dsc_array(obj(), col_dsc, row_dsc);
}

/* FIXME
void Container::setLayoutRightColumns() {
    lv_obj_set_layout(obj(), LV_LAYOUT_COLUMN_RIGHT);
}

void Container::setLayoutPretty() {
    lv_obj_set_layout(obj(), LV_LAYOUT_PRETTY_MID);
}

void Container::setLayoutRow() {
    lv_obj_set_layout(obj(), LV_LAYOUT_ROW_MID);
}

void Container::setLayoutColumn() {
    lv_obj_set_layout(obj(), LV_LAYOUT_COLUMN_MID);
}

void Container::setLayoutGrid() {
    lv_obj_set_layout(obj(), LV_LAYOUT_GRID);
}

void Container::setFit(Fit horiz, Fit vert) {
    lv_obj_set_fit2(obj(), toLvFit(horiz), toLvFit(vert));
}

lv_fit_t Container::toLvFit(Container::Fit fit) {
    switch (fit) {
        case Fit::OFF:      return LV_FIT_NONE;
        case Fit::TIGHT:    return LV_FIT_TIGHT;
        case Fit::FLOOD:    return LV_FIT_FLOOD;
        case Fit::FILL:     return LV_FIT_FILL;
        default: return LV_FIT_NONE;
    }
}
*/
} /* namespace avitab */
