// SPDX-License-Identifier: GPL-2.0
/*
 * sensor_hub_sysfs_proc.c
 * STEP 4 — Sysfs + Procfs Interface
 * Expose temperature via sysfs (ABI kernel <-> user) and procfs
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#define DRIVER_NAME "sensor_hub"

static struct class *sensor_hub_class;
static struct device *sensor_hub_dev;
static struct proc_dir_entry *proc_entry;

/* Simulated temperature value in milli-degrees Celsius */
static int temperature_millic = 42000;

/* Future structure for prof sensors */
struct prof_sensor {
    const char *name;
    int value_millic;
};

static struct prof_sensor profs[] = {
    {"prof1", 42000},
    {"prof2", 43000},
};

/* Sysfs show callback */
static ssize_t temperature_show(struct device *dev,
                                struct device_attribute *attr,
                                char *buf)
{
    return sysfs_emit(buf, "%d\n", temperature_millic);
}

/* Read-only sysfs attribute */
static DEVICE_ATTR_RO(temperature);

/* Procfs show callback */
static int proc_temperature_show(struct seq_file *m, void *v)
{
    seq_printf(m, "Temperature: %d m°C\n", temperature_millic);
    for (int i = 0; i < ARRAY_SIZE(profs); i++) {
        seq_printf(m, "%s: %d m°C\n", profs[i].name, profs[i].value_millic);
    }
    return 0;
}

static int proc_temperature_open(struct inode *inode, struct file *file)
{
    return single_open(file, proc_temperature_show, NULL);
}

static const struct proc_ops proc_file_ops = {
    .proc_open = proc_temperature_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init sensor_hub_init(void)
{
    int ret;

    pr_info(DRIVER_NAME ": init\n");

    /* Create sysfs class */
    sensor_hub_class = class_create(DRIVER_NAME);
    if (IS_ERR(sensor_hub_class))
        return PTR_ERR(sensor_hub_class);

    /* Create device */
    sensor_hub_dev = device_create(sensor_hub_class,
                                   NULL,
                                   0,
                                   NULL,
                                   "sensor0");
    if (IS_ERR(sensor_hub_dev)) {
        ret = PTR_ERR(sensor_hub_dev);
        class_destroy(sensor_hub_class);
        return ret;
    }

    /* Create sysfs file */
    ret = device_create_file(sensor_hub_dev, &dev_attr_temperature);
    if (ret) {
        device_destroy(sensor_hub_class, 0);
        class_destroy(sensor_hub_class);
        return ret;
    }

    /* Create procfs entry */
    proc_entry = proc_create("sensor_hub_temperature", 0444, NULL, &proc_file_ops);
    if (!proc_entry) {
        device_remove_file(sensor_hub_dev, &dev_attr_temperature);
        device_destroy(sensor_hub_class, 0);
        class_destroy(sensor_hub_class);
        return -ENOMEM;
    }

    pr_info(DRIVER_NAME ": sysfs and procfs ready\n");
    return 0;
}

static void __exit sensor_hub_exit(void)
{
    proc_remove(proc_entry);
    device_remove_file(sensor_hub_dev, &dev_attr_temperature);
    device_destroy(sensor_hub_class, 0);
    class_destroy(sensor_hub_class);

    pr_info(DRIVER_NAME ": exit\n");
}

module_init(sensor_hub_init);
module_exit(sensor_hub_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("BSP Student");
MODULE_DESCRIPTION("Sensor Hub sysfs and procfs interface (STEP 4) with profs");
