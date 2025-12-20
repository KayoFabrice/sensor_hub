KERNEL_SRC := /rpi-kernel
ARCH ?= arm64
CROSS_COMPILE ?= aarch64-linux-gnu-

obj-m += drivers/CHAR_driver/sensor_hub.o
obj-m += drivers/GPIO/sensor_hub_gpio.o
obj-m += drivers/SYSFS_PROCFS_IOCTL/sensor_hub_sysfs_procfs.o



all:
	$(MAKE) -C $(KERNEL_SRC) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

clean:
	$(MAKE) -C $(KERNEL_SRC) M=$(PWD) clean
