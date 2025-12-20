#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>

#define DEVICE_NAME "sensor_hub"
#define BUFFER_SIZE 1024

MODULE_LICENSE("GPL");
MODULE_AUTHOR("FabriceKAYO");
MODULE_DESCRIPTION("Minimal character device for Sensor Hub");

static char device_buffer[BUFFER_SIZE];
static int major_number;
static int open_count = 0;

// open
static int dev_open(struct inode *inodep, struct file *filep) {
    open_count++;
    printk(KERN_INFO "sensor_hub: device opened %d times\n", open_count);
    return 0;
}

// release
static int dev_release(struct inode *inodep, struct file *filep) {
    printk(KERN_INFO "sensor_hub: device closed\n");
    return 0;
}

// read
static ssize_t dev_read(struct file *filep, char __user *buffer, size_t len, loff_t *offset) {
    ssize_t bytes_to_read = min(len, (size_t)BUFFER_SIZE - *offset);
    if (bytes_to_read == 0)
        return 0;

    if (copy_to_user(buffer, device_buffer + *offset, bytes_to_read) != 0)
        return -EFAULT;

    *offset += bytes_to_read;
    return bytes_to_read;
}

// write
static ssize_t dev_write(struct file *filep, const char __user *buffer, size_t len, loff_t *offset) {
    ssize_t bytes_to_write = min(len, (size_t)BUFFER_SIZE - *offset);
    if (bytes_to_write == 0)
        return -ENOMEM;

    if (copy_from_user(device_buffer + *offset, buffer, bytes_to_write) != 0)
        return -EFAULT;

    *offset += bytes_to_write;
    return bytes_to_write;
}

static struct file_operations fops = {
    .open = dev_open,
    .release = dev_release,
    .read = dev_read,
    .write = dev_write,
};

static int __init sensor_init(void) {
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "sensor_hub: failed to register major number\n");
        return major_number;
    }
    printk(KERN_INFO "sensor_hub: module loaded, major number = %d\n", major_number);
    return 0;
}

static void __exit sensor_exit(void) {
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "sensor_hub: module unloaded\n");
}

module_init(sensor_init);
module_exit(sensor_exit);
