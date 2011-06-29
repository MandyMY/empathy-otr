/*
 * Copyright (C) 2010 Collabora Ltd.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Authors: Guillaume Desmottes <guillaume.desmottes@collabora.co.uk>
 */

#include <config.h>

#include "empathy-client-factory.h"

#include "empathy-tp-chat.h"
#include "empathy-utils.h"
	
#include <telepathy-yell/telepathy-yell.h>

G_DEFINE_TYPE (EmpathyClientFactory, empathy_client_factory,
    TP_TYPE_AUTOMATIC_CLIENT_FACTORY)

#define chainup ((TpSimpleClientFactoryClass *) \
    empathy_client_factory_parent_class)

static TpChannel *
empathy_client_factory_create_channel (TpSimpleClientFactory *factory,
    TpConnection *conn,
    const gchar *path,
    const GHashTable *properties,
    GError **error)
{
  const gchar *chan_type;

  chan_type = tp_asv_get_string (properties, TP_PROP_CHANNEL_CHANNEL_TYPE);

  if (!tp_strdiff (chan_type, TP_IFACE_CHANNEL_TYPE_TEXT))
    {
      TpAccount *account;

      account = empathy_get_account_for_connection (conn);

      return TP_CHANNEL (empathy_tp_chat_new (account, conn, path, properties));
    }
  else if (!tp_strdiff (chan_type, TPY_IFACE_CHANNEL_TYPE_CALL))
    {
      return TP_CHANNEL (tpy_call_channel_new (conn, path, properties,
            error));
    }

  return chainup->create_channel (factory, conn, path, properties, error);
}

static GArray *
empathy_client_factory_dup_channel_features (TpSimpleClientFactory *factory,
    TpChannel *channel)
{
  GArray *features;
  GQuark feature;

  features = chainup->dup_channel_features (factory, channel);

  if (EMPATHY_IS_TP_CHAT (channel))
    {
      feature = TP_CHANNEL_FEATURE_CHAT_STATES;
      g_array_append_val (features, feature);

      feature = EMPATHY_TP_CHAT_FEATURE_READY;
      g_array_append_val (features, feature);
    }

  return features;
}

static void
empathy_client_factory_class_init (EmpathyClientFactoryClass *cls)
{
  TpSimpleClientFactoryClass *simple_class = (TpSimpleClientFactoryClass *) cls;

  simple_class->create_channel = empathy_client_factory_create_channel;
  simple_class->dup_channel_features = empathy_client_factory_dup_channel_features;
}

static void
empathy_client_factory_init (EmpathyClientFactory *self)
{
}

EmpathyClientFactory *
empathy_client_factory_new (TpDBusDaemon *dbus)
{
    return g_object_new (EMPATHY_TYPE_CLIENT_FACTORY,
        "dbus-daemon", dbus,
        NULL);
}

EmpathyClientFactory *
empathy_client_factory_dup (void)
{
  static EmpathyClientFactory *singleton = NULL;
  TpDBusDaemon *dbus;

  if (singleton != NULL)
    return g_object_ref (singleton);

  dbus = tp_dbus_daemon_dup ();
  singleton = empathy_client_factory_new (dbus);
  g_object_unref (dbus);

  g_object_add_weak_pointer (G_OBJECT (singleton), (gpointer) &singleton);

  return singleton;
}

TpAccountManager *
empathy_account_manager_dup (void)
{
  EmpathyClientFactory *factory;
  TpAccountManager *manager;

  factory = empathy_client_factory_dup ();
  manager = tp_client_factory_dup_account_manager (factory);
  g_object_unref (factory);

  return manager;
}
