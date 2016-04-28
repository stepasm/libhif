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

#pragma once

#include <glib-object.h>

G_BEGIN_DECLS

#define HIF_TYPE_NEVRA (hif_nevra_get_type())

G_DECLARE_FINAL_TYPE (HifNevra, hif_nevra, HIF, NEVRA, GObject)

HifNevra    *hif_nevra_new      (void);

const gchar *hif_nevra_get_name (HifNevra *nevra);
gchar       *hif_nevra_get_evr  (HifNevra *nevra);

G_END_DECLS
