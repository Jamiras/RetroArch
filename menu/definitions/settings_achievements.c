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

#include "../menu_items.h"

#include "configuration.h"
#include "msg_hash.h"

static void menu_convert_achievement_password(menu_item_t* item)
{
   settings_t* settings = config_get_ptr();
   if (settings->arrays.cheevos_password[0] || settings->arrays.cheevos_token[0])
      menu_item_set_value_static(item, "********");
   else
      menu_item_set_value_static(item, "");
}

void menu_init_settings_achievements(menu_list_t* list)
{
   settings_t* settings = config_get_ptr();
   menu_item_t* item;

   item = menu_list_add(list);
   menu_item_set_label_static(item, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CHEEVOS_ENABLE));
   menu_item_set_sublabel_static(item, msg_hash_to_str(MENU_ENUM_SUBLABEL_CHEEVOS_ENABLE));
   menu_item_bind_boolean(item, &settings->bools.cheevos_enable);
   item->flags |= MENU_ITEM_FLAG_REFRESH_LIST_ON_CHANGE;

   if (!settings->bools.cheevos_enable)
      return;

   item = menu_list_add(list);
   menu_item_set_label_static(item, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_ACCOUNTS_CHEEVOS_USERNAME));
   menu_item_set_sublabel_static(item, msg_hash_to_str(MENU_ENUM_SUBLABEL_CHEEVOS_USERNAME));
   menu_item_bind_string(item, settings->arrays.cheevos_username, ARRAY_SIZE(settings->arrays.cheevos_username));
   item->flags |= MENU_ITEM_FLAG_REFRESH_VALUES_ON_CHANGE;

   item = menu_list_add(list);
   menu_item_set_label_static(item, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_ACCOUNTS_CHEEVOS_PASSWORD));
   menu_item_set_sublabel_static(item, msg_hash_to_str(MENU_ENUM_SUBLABEL_CHEEVOS_PASSWORD));
   menu_item_bind_string(item, settings->arrays.cheevos_password, ARRAY_SIZE(settings->arrays.cheevos_password));
   menu_item_set_value_converter(item, menu_convert_achievement_password);

   item = menu_list_add(list);
   menu_item_set_label_static(item, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CHEEVOS_HARDCORE_MODE_ENABLE));
   menu_item_set_sublabel_static(item, msg_hash_to_str(MENU_ENUM_SUBLABEL_CHEEVOS_HARDCORE_MODE_ENABLE));
   menu_item_bind_boolean(item, &settings->bools.cheevos_hardcore_mode_enable);

   item = menu_list_add(list);
   menu_item_set_label_static(item, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CHEEVOS_LEADERBOARDS_ENABLE));
   menu_item_set_sublabel_static(item, msg_hash_to_str(MENU_ENUM_SUBLABEL_CHEEVOS_LEADERBOARDS_ENABLE));
   menu_item_bind_boolean(item, &settings->bools.cheevos_leaderboards_enable);

   item = menu_list_add(list);
   menu_item_set_label_static(item, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CHEEVOS_RICHPRESENCE_ENABLE));
   menu_item_set_sublabel_static(item, msg_hash_to_str(MENU_ENUM_SUBLABEL_CHEEVOS_RICHPRESENCE_ENABLE));
   menu_item_bind_boolean(item, &settings->bools.cheevos_richpresence_enable);

   item = menu_list_add(list);
   menu_item_set_label_static(item, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CHEEVOS_BADGES_ENABLE));
   menu_item_set_sublabel_static(item, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CHEEVOS_BADGES_ENABLE));
   menu_item_bind_boolean(item, &settings->bools.cheevos_badges_enable);

   if (settings->bools.menu_show_advanced_settings)
   {
      item = menu_list_add(list);
      menu_item_set_label_static(item, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CHEEVOS_ENABLE));
      menu_item_set_sublabel_static(item, msg_hash_to_str(MENU_ENUM_SUBLABEL_CHEEVOS_ENABLE));
      menu_item_bind_boolean(item, &settings->bools.cheevos_test_unofficial);
   }

#ifdef HAVE_AUDIOMIXER
   item = menu_list_add(list);
   menu_item_set_label_static(item, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CHEEVOS_UNLOCK_SOUND_ENABLE));
   menu_item_set_sublabel_static(item, msg_hash_to_str(MENU_ENUM_SUBLABEL_CHEEVOS_UNLOCK_SOUND_ENABLE));
   menu_item_bind_boolean(item, &settings->bools.cheevos_unlock_sound_enable);
#endif

   item = menu_list_add(list);
   menu_item_set_label_static(item, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CHEEVOS_VERBOSE_ENABLE));
   menu_item_set_sublabel_static(item, msg_hash_to_str(MENU_ENUM_SUBLABEL_CHEEVOS_VERBOSE_ENABLE));
   menu_item_bind_boolean(item, &settings->bools.cheevos_verbose_enable);

   item = menu_list_add(list);
   menu_item_set_label_static(item, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CHEEVOS_AUTO_SCREENSHOT));
   menu_item_set_sublabel_static(item, msg_hash_to_str(MENU_ENUM_SUBLABEL_CHEEVOS_AUTO_SCREENSHOT));
   menu_item_bind_boolean(item, &settings->bools.cheevos_auto_screenshot);

   if (settings->bools.menu_show_advanced_settings)
   {
      item = menu_list_add(list);
      menu_item_set_label_static(item, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CHEEVOS_START_ACTIVE));
      menu_item_set_sublabel_static(item, msg_hash_to_str(MENU_ENUM_SUBLABEL_CHEEVOS_START_ACTIVE));
      menu_item_bind_boolean(item, &settings->bools.cheevos_start_active);
   }
}