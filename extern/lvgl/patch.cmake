# This file is part of the Avitab project. See the README and LICENSE for details.

# LVGL sources have #include "../../../lv_conf.h" which steps outside the downloaded
# and extracted package tree. To mitigate this we create a new directory and move the
# sources into it.

file(MAKE_DIRECTORY "${AVITAB_lvgl_SOURCE_DIR}/lvgl")
file(REMOVE_RECURSE "${AVITAB_lvgl_SOURCE_DIR}/lvgl/src")
file(RENAME "${AVITAB_lvgl_SOURCE_DIR}/src" "${AVITAB_lvgl_SOURCE_DIR}/lvgl/src")
file(RENAME "${AVITAB_lvgl_SOURCE_DIR}/lvgl.h" "${AVITAB_lvgl_SOURCE_DIR}/lvgl/lvgl.h")
file(RENAME "${AVITAB_lvgl_SOURCE_DIR}/lv_version.h" "${AVITAB_lvgl_SOURCE_DIR}/lvgl/lv_version.h")
file(COPY_FILE "${CMAKE_CURRENT_LIST_DIR}/patches/font/lv_font_montserrat_10.c" "${AVITAB_lvgl_SOURCE_DIR}/lvgl/src/font/lv_font_montserrat_10.c")
file(COPY_FILE "${CMAKE_CURRENT_LIST_DIR}/patches/font/lv_font_montserrat_12.c" "${AVITAB_lvgl_SOURCE_DIR}/lvgl/src/font/lv_font_montserrat_12.c")
file(COPY_FILE "${CMAKE_CURRENT_LIST_DIR}/patches/font/lv_font_montserrat_14.c" "${AVITAB_lvgl_SOURCE_DIR}/lvgl/src/font/lv_font_montserrat_14.c")
file(COPY_FILE "${CMAKE_CURRENT_LIST_DIR}/patches/font/lv_font_montserrat_16.c" "${AVITAB_lvgl_SOURCE_DIR}/lvgl/src/font/lv_font_montserrat_16.c")
file(COPY_FILE "${CMAKE_CURRENT_LIST_DIR}/patches/font/lv_font_montserrat_18.c" "${AVITAB_lvgl_SOURCE_DIR}/lvgl/src/font/lv_font_montserrat_18.c")
file(COPY_FILE "${CMAKE_CURRENT_LIST_DIR}/patches/font/lv_font_montserrat_20.c" "${AVITAB_lvgl_SOURCE_DIR}/lvgl/src/font/lv_font_montserrat_20.c")
file(COPY_FILE "${CMAKE_CURRENT_LIST_DIR}/patches/tabview/lv_tabview.h" "${AVITAB_lvgl_SOURCE_DIR}/lvgl/src/widgets/tabview/lv_tabview.h")
file(COPY_FILE "${CMAKE_CURRENT_LIST_DIR}/patches/tabview/lv_tabview.c" "${AVITAB_lvgl_SOURCE_DIR}/lvgl/src/widgets/tabview/lv_tabview.c")
file(COPY_FILE "${CMAKE_CURRENT_LIST_DIR}/patches/lv_conf.h" "${AVITAB_lvgl_SOURCE_DIR}/lv_conf.h")
