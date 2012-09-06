/* # Generated using empathy/ubuntu-online-accounts/cc-plugins/generate-plugins.py
 * Do NOT edit manually */

/*
 * empathy-accounts-plugin-zephyr.h
 *
 * Copyright (C) 2012 Collabora Ltd. <http://www.collabora.co.uk/>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */


#ifndef __EMPATHY_ACCOUNTS_PLUGIN_ZEPHYR_H__
#define __EMPATHY_ACCOUNTS_PLUGIN_ZEPHYR_H__

#include "empathy-accounts-plugin.h"

G_BEGIN_DECLS

typedef struct _EmpathyAccountsPluginZephyr EmpathyAccountsPluginZephyr;
typedef struct _EmpathyAccountsPluginZephyrClass EmpathyAccountsPluginZephyrClass;

struct _EmpathyAccountsPluginZephyrClass
{
  /*<private>*/
  EmpathyAccountsPluginClass parent_class;
};

struct _EmpathyAccountsPluginZephyr
{
  /*<private>*/
  EmpathyAccountsPlugin parent;
};

GType empathy_accounts_plugin_zephyr_get_type (void);

/* TYPE MACROS */
#define EMPATHY_TYPE_ACCOUNTS_PLUGIN_ZEPHYR \
  (empathy_accounts_plugin_zephyr_get_type ())
#define EMPATHY_ACCOUNTS_PLUGIN_ZEPHYR(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), \
    EMPATHY_TYPE_ACCOUNTS_PLUGIN_ZEPHYR, \
    EmpathyAccountsPluginZephyr))
#define EMPATHY_ACCOUNTS_PLUGIN_ZEPHYR_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass), \
    EMPATHY_TYPE_ACCOUNTS_PLUGIN_ZEPHYR, \
    EmpathyAccountsPluginZephyrClass))
#define EMPATHY_IS_ACCOUNTS_PLUGIN_ZEPHYR(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), \
    EMPATHY_TYPE_ACCOUNTS_PLUGIN_ZEPHYR))
#define EMPATHY_IS_ACCOUNTS_PLUGIN_ZEPHYR_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass), \
    EMPATHY_TYPE_ACCOUNTS_PLUGIN_ZEPHYR))
#define EMPATHY_ACCOUNTS_PLUGIN_ZEPHYR_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), \
    EMPATHY_TYPE_ACCOUNTS_PLUGIN_ZEPHYR, \
    EmpathyAccountsPluginZephyrClass))

GType ap_module_get_object_type (void);

G_END_DECLS

#endif /* #ifndef __EMPATHY_ACCOUNTS_PLUGIN_ZEPHYR_H__*/