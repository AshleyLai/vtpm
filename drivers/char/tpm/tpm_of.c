/*
 * Copyright (C) 2005, 2012 IBM Corporation
 *
 * Authors:
 *	Ashley Lai <adlai@us.ibm.com>
 *	Kent Yoder <key@linux.vnet.ibm.com>
 *	Seiji Munetoh <munetoh@jp.ibm.com>
 *	Stefan Berger <stefanb@us.ibm.com>
 *	Reiner Sailer <sailer@watson.ibm.com>
 *	Kylene Hall <kjhall@us.ibm.com>
 *
 * Maintained by: <tpmdd-devel@lists.sourceforge.net>
 *
 * Adapted from tpm_bios.c
 *
 * Access function for the eventlog extended by TCG-aware firmware for PPC
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 *
 */

#include <linux/slab.h>
#include <linux/of.h>

#include "tpm.h"
#include "tpm_eventlog.h"

/* read binary event log */
int read_log(struct tpm_bios_log *log)
{
	struct device_node *np;
	const u32 *sizep;
	const __be64 *basep;

	if (log->bios_event_log != NULL) {
		printk(KERN_ERR
		       "%s: ERROR - Eventlog already initialized\n",
		       __func__);
		return -EFAULT;
	}

	np = of_find_node_by_name(NULL, "ibm,vtpm");
	if (!np) {
		printk(KERN_ERR "%s: ERROR - IBMVTPM not supported\n",
		       __func__);
		return -ENODEV;
	}

	sizep = of_get_property(np, "linux,sml-size", NULL);
	basep = of_get_property(np, "linux,sml-base", NULL);
	if (sizep == NULL || basep == NULL) {
		printk(KERN_ERR "%s: ERROR - Property not found\n",
		       __func__);
		return -EIO;
	}

	if (*sizep == 0) {
		printk(KERN_ERR "%s: ERROR - event log area empty\n", __func__);
		return -EIO;
	}

	/* malloc EventLog space */
	log->bios_event_log = kmalloc(*sizep, GFP_KERNEL);
	if (!log->bios_event_log) {
		printk("%s: ERROR - Not enough  Memory for BIOS measurements\n",
		       __func__);
		return -ENOMEM;
	}

	log->bios_event_log_end = log->bios_event_log + *sizep;

	memcpy(log->bios_event_log, __va(be64_to_cpup(basep)), *sizep);

	return 0;
}

