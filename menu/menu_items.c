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

#include "menu_items.h"

#include "msg_hash.h"

#include <retro_miscellaneous.h>

#include <stdlib.h>
#include <string.h>

void menu_item_destroy(menu_item_t* item)
{
   if (item->flags & MENU_ITEM_FLAG_ALLOC_LABEL)
      free((void*)item->label);

   if (item->flags & MENU_ITEM_FLAG_ALLOC_SUBLABEL)
      free((void*)item->sublabel);

   if (item->flags & MENU_ITEM_FLAG_ALLOC_VALUE)
      free((void*)item->value);

   memset(item, 0, sizeof(*item));
}

void menu_item_set_label_static(menu_item_t* item, const char* label)
{
   if (item->flags & MENU_ITEM_FLAG_ALLOC_LABEL) {
      free((void*)item->label);
      item->flags &= ~MENU_ITEM_FLAG_ALLOC_LABEL;
   }

   item->label = label;
}

void menu_item_set_label_dynamic(menu_item_t* item, const char* label)
{
   if (item->flags & MENU_ITEM_FLAG_ALLOC_LABEL)
      free((void*)item->label);

   item->label = strdup(label);
   item->flags |= MENU_ITEM_FLAG_ALLOC_LABEL;
}

void menu_item_set_sublabel_static(menu_item_t* item, const char* sublabel)
{
   if (item->flags & MENU_ITEM_FLAG_ALLOC_SUBLABEL) {
      free((void*)item->sublabel);
      item->flags &= ~MENU_ITEM_FLAG_ALLOC_SUBLABEL;
   }

   item->sublabel = sublabel;
}

void menu_item_set_sublabel_dynamic(menu_item_t* item, const char* sublabel)
{
   if (item->flags & MENU_ITEM_FLAG_ALLOC_SUBLABEL)
      free((void*)item->sublabel);

   item->sublabel = strdup(sublabel);
   item->flags |= MENU_ITEM_FLAG_ALLOC_SUBLABEL;
}

void menu_item_set_value_static(menu_item_t* item, const char* value)
{
   if (item->flags & MENU_ITEM_FLAG_ALLOC_VALUE) {
      free((void*)item->value);
      item->flags &= ~MENU_ITEM_FLAG_ALLOC_VALUE;
   }

   item->value = value;
}

void menu_item_set_value_dynamic(menu_item_t* item, const char* value)
{
   if (item->flags & MENU_ITEM_FLAG_ALLOC_VALUE)
      free((void*)item->value);

   item->value = strdup(value);
   item->flags |= MENU_ITEM_FLAG_ALLOC_VALUE;
}

void menu_item_value_changed(menu_item_t* item)
{
   if (item->flags & MENU_ITEM_FLAG_REFRESH_LIST_ON_CHANGE)
   {
      // rebuild current list
   }
   else if (item->flags & MENU_ITEM_FLAG_REFRESH_VALUES_ON_CHANGE)
   {
      // update values for current list
   }
   else if (item->convert_value)
   {
      item->convert_value(item);
   }
}

static void menu_item_convert_boolean(menu_item_t* item)
{
   if (*item->bind.boolean)
      menu_item_set_value_static(item, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_ON));
   else
      menu_item_set_value_static(item, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_OFF));
}

static void menu_item_toggle_boolean(menu_item_t* item)
{
   *item->bind.boolean = !*item->bind.boolean;
   menu_item_value_changed(item);
}

void menu_item_bind_boolean(menu_item_t* item, bool* value)
{
   item->bind_type = MENU_ITEM_TYPE_BOOLEAN;
   item->bind.boolean = value;
   item->convert_value = menu_item_convert_boolean;
   item->next_value = menu_item_toggle_boolean;
   item->prev_value = menu_item_toggle_boolean;
}

void menu_item_bind_string(menu_item_t* item, char* buffer, size_t buffer_size)
{
   item->bind_type = MENU_ITEM_TYPE_STRING;
   item->bind.str.buffer = buffer;
   item->bind.str.buffer_size = buffer_size;
}

void menu_item_set_value_converter(menu_item_t* item, menu_item_convert_value_func func)
{
   item->convert_value = func;
}


void menu_list_destroy(menu_list_t* list)
{
   int i;

   if (list->next)
   {
      menu_list_destroy(list->next);
      free(list->next);
      list->next = NULL;
   }

   for (i = 0; i < list->count; ++i)
      menu_item_destroy(&list->items[i]);

   list->count = 0;
}

menu_item_t* menu_list_add(menu_list_t* list)
{
   while (list->count == ARRAY_SIZE(list->items))
   {
      if (list->next == NULL)
         list->next = (menu_list_t*)calloc(1, sizeof(menu_list_t));

      list = list->next;
   }

   return &list->items[list->count++];
}

int menu_list_size(const menu_list_t* list)
{
   int count = 0;

   while (list)
   {
      count += list->count;
      list = list->next;
   }

   return count;
}

menu_item_t* menu_list_get(menu_list_t* list, int index)
{
   while (list)
   {
      if (index < list->count)
         return &list->items[index];

      if (index < ARRAY_SIZE(list->items))
         break;

      index -= ARRAY_SIZE(list->items);
      list = list->next;
   }

   return NULL;
}