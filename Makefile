KERNEL_SRC := /rpi-kernel
ARCH ?= arm64
CROSS_COMPILE ?= aarch64-linux-gnu-

obj-m += drivers/sensor_hub.o
obj-m += drivers/sensor_hub_gpio.o

all:
	$(MAKE) -C $(KERNEL_SRC) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules

clean:
	$(MAKE) -C $(KERNEL_SRC) M=$(PWD) clean
