/*  RetroArch - A frontend for libretro.
 *  Copyright (C) 2020
 *
 *  RetroArch is free software: you can redistribute it and/or modify it under the terms
 *  of the GNU General Public License as published by the Free Software Found-
 *  ation, either version 3 of the License, or (at your option) any later version.
 *
 *  RetroArch is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *  PURPOSE.  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with RetroArch.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __MENU_ITEMS_H__
#define __MENU_ITEMS_H__

#include <stdint.h>
#include <stddef.h>

#include <boolean.h>
#include <retro_common_api.h>

RETRO_BEGIN_DECLS

enum menu_item_flags
{
   MENU_ITEM_FLAG_ALLOC_LABEL = (1 << 0),
   MENU_ITEM_FLAG_ALLOC_SUBLABEL = (1 << 1),
   MENU_ITEM_FLAG_ALLOC_VALUE = (1 << 2),
   MENU_ITEM_FLAG_REFRESH_LIST_ON_CHANGE = (1 << 3),
   MENU_ITEM_FLAG_REFRESH_VALUES_ON_CHANGE = (1 << 4)
};

enum menu_item_type
{
   MENU_ITEM_TYPE_NONE = 0,
   MENU_ITEM_TYPE_BOOLEAN,
   MENU_ITEM_TYPE_STRING
};

struct menu_item;
typedef void (*menu_item_convert_value_func)(struct menu_item* item);
typedef void (*menu_item_navigate_func)(struct menu_item* item);

typedef struct menu_item
{
   const char* label;
   const char* sublabel;
   const char* value;

   union bind_t {
      bool* boolean;

      struct string_t {
         char* buffer;
         size_t buffer_size;
      } str;
   } bind;
   enum menu_item_type bind_type;

   enum menu_item_flags flags;

   menu_item_convert_value_func convert_value;
   menu_item_navigate_func next_value;
   menu_item_navigate_func prev_value;
   menu_item_navigate_func open_child_menu;

} menu_item_t;

void menu_item_destroy(menu_item_t* item);

void menu_item_set_label_static(menu_item_t* item, const char* label);
void menu_item_set_label_dynamic(menu_item_t* item, const char* label);
void menu_item_set_sublabel_static(menu_item_t* item, const char* sublabel);
void menu_item_set_sublabel_dynamic(menu_item_t* item, const char* sublabel);
void menu_item_set_value_static(menu_item_t* item, const char* value);
void menu_item_set_value_dynamic(menu_item_t* item, const char* value);

void menu_item_bind_boolean(menu_item_t* item, bool* value);
void menu_item_bind_string(menu_item_t* item, char* buffer, size_t buffer_size);

void menu_item_set_value_converter(menu_item_t* item, menu_item_convert_value_func func);

void menu_item_value_changed(menu_item_t* item);

typedef struct menu_list
{
   menu_item_t items[16];
   int count;

   struct menu_list* next;
} menu_list_t;

void menu_list_destroy(menu_list_t* list);
menu_item_t* menu_list_add(menu_list_t* list);

int menu_list_size(const menu_list_t* list);
menu_item_t* menu_list_get(menu_list_t* list, int index);

RETRO_END_DECLS

#endif