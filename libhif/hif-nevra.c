/*
 * Copyright © 2016  Igor Gnatenko <ignatenko@redhat.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "hif-nevra.h"

/**
 * SECTION: HifNevra
 * @short_description: NEVRA
 *
 * #HifNevra rappresents NEVRA (Name, Epoch, Version, Release, Arch).
 */

struct _HifNevra
{
    GObject parent_instance;

    gchar *name;
    int epoch;
    gchar *version;
    gchar *release;
    gchar *arch;
};

G_DEFINE_TYPE (HifNevra, hif_nevra, G_TYPE_OBJECT)

enum {
    PROP_0,
    PROP_NAME,
    PROP_EPOCH,
    PROP_VERSION,
    PROP_RELEASE,
    PROP_ARCH,
    N_PROPS
};

static GParamSpec *properties [N_PROPS];

/**
 * hif_nevra_new:
 *
 * Allocates a new #HifNevra.
 *
 * Returns: an #HifNevra
 *
 * Since: 0.7.0
 */
HifNevra *
hif_nevra_new (void)
{
    return g_object_new (HIF_TYPE_NEVRA, NULL);
}

static void
hif_nevra_finalize (GObject *object)
{
    HifNevra *self = (HifNevra *)object;

    g_clear_pointer (&self->name, g_free);
    g_clear_pointer (&self->version, g_free);
    g_clear_pointer (&self->release, g_free);
    g_clear_pointer (&self->arch, g_free);

    G_OBJECT_CLASS (hif_nevra_parent_class)->finalize (object);
}

static void
hif_nevra_get_property (GObject    *object,
                        guint       prop_id,
                        GValue     *value,
                        GParamSpec *pspec)
{
    HifNevra *self = HIF_NEVRA (object);

    switch (prop_id)
      {
      case PROP_NAME:
        g_value_set_string (value, self->name);
      case PROP_EPOCH:
        g_value_set_int (value, self->epoch);
        break;
      case PROP_VERSION:
        g_value_set_string (value, self->version);
        break;
      case PROP_RELEASE:
        g_value_set_string (value, self->release);
        break;
      case PROP_ARCH:
        g_value_set_string (value, self->arch);
        break;
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      }
}

static void
hif_nevra_set_property (GObject      *object,
                        guint         prop_id,
                        const GValue *value,
                        GParamSpec   *pspec)
{
    HifNevra *self = HIF_NEVRA (object);

    switch (prop_id)
      {
      case PROP_NAME:
        g_free (self->name);
        self->name = g_value_dup_string (value);
        break;
      case PROP_EPOCH:
        self->epoch = g_value_get_int (value);
        break;
      case PROP_VERSION:
        g_free (self->version);
        self->version = g_value_dup_string (value);
        break;
      case PROP_RELEASE:
        g_free (self->release);
        self->release = g_value_dup_string (value);
        break;
      case PROP_ARCH:
        g_free (self->arch);
        self->arch = g_value_dup_string (value);
        break;
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      }
}

static void
hif_nevra_class_init (HifNevraClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);

    object_class->finalize = hif_nevra_finalize;
    object_class->get_property = hif_nevra_get_property;
    object_class->set_property = hif_nevra_set_property;

    /**
     * HifNevra:name:
     *
     * Name.
     */
    properties [PROP_NAME] =
        g_param_spec_string ("name",
                             "Name",
                             "Name",
                             NULL,
                             (G_PARAM_READWRITE |
                              G_PARAM_STATIC_STRINGS));

    /**
     * HifNevra:epoch:
     *
     * Epoch.
     */
    properties [PROP_EPOCH] =
        g_param_spec_int ("epoch",
                          "Epoch",
                          "Epoch",
                          -1,
                          G_MAXINT,
                          -1,
                          (G_PARAM_READWRITE |
                           G_PARAM_STATIC_STRINGS));

    /**
     * HifNevra:version:
     *
     * Version.
     */
    properties [PROP_VERSION] =
        g_param_spec_string ("version",
                             "Version",
                             "Version",
                             NULL,
                             (G_PARAM_READWRITE |
                              G_PARAM_STATIC_STRINGS));

    /**
     * HifNevra:release:
     *
     * Release.
     */
    properties [PROP_RELEASE] =
        g_param_spec_string ("release",
                             "Release",
                             "Release",
                             NULL,
                             (G_PARAM_READWRITE |
                              G_PARAM_STATIC_STRINGS));

    /**
     * HifNevra:arch:
     *
     * Architecture.
     */
    properties [PROP_ARCH] =
        g_param_spec_string ("arch",
                             "Architecture",
                             "Architecture",
                             NULL,
                             (G_PARAM_READWRITE |
                              G_PARAM_STATIC_STRINGS));

    g_object_class_install_properties (object_class, N_PROPS, properties);
}

static void
hif_nevra_init (HifNevra *self)
{
}

/**
 * hif_nevra_get_name:
 * @nevra: a #HifNevra
 *
 * Returns: (transfer none): Name
 *
 * Since: 0.7.0
 */
const gchar *
hif_nevra_get_name (HifNevra *nevra)
{
    g_return_val_if_fail (HIF_IS_NEVRA (nevra), NULL);

    return nevra->name;
}

/**
 * hif_nevra_get_evr:
 * @nevra: a #HifNevra
 *
 * If epoch is not set then will return Version and Release, otherwise Epoch,
 * Version and Release.
 *
 * Returns: (transfer full): an EVR string
 *
 * Since: 0.7.0
 */
gchar *
hif_nevra_get_evr (HifNevra *nevra)
{
    g_return_val_if_fail (HIF_IS_NEVRA (nevra), NULL);

    if (nevra->epoch == -1)
        return g_strdup_printf ("%s-%s",
                                nevra->version,
                                nevra->release);
    else
        return g_strdup_printf ("%d:%s-%s",
                                nevra->epoch,
                                nevra->version,
                                nevra->release);
}
