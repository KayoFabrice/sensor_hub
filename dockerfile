# ============================================================
# Raspberry Pi Kernel Module Cross-Compilation Environment
# ============================================================

FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

# ------------------------------------------------------------
# Install essentials
# ------------------------------------------------------------
RUN apt-get update && apt-get install -y \
    git build-essential bc bison flex libssl-dev libncurses5-dev \
    wget curl ca-certificates xz-utils kmod rsync tree \
    gcc-aarch64-linux-gnu gcc-arm-linux-gnueabihf \
    && apt-get clean

# ------------------------------------------------------------
# Clone Raspberry Pi kernel source
# ------------------------------------------------------------
RUN git clone --depth=1 --branch rpi-6.12.y https://github.com/raspberrypi/linux.git /rpi-kernel

# ------------------------------------------------------------
# Copy config_pi if present in build context
# ------------------------------------------------------------
# You can place your Pi's /boot/config-<kernel> as config_pi in your project folder
COPY config_pi /rpi-kernel/.config

# ------------------------------------------------------------
# Prepare kernel for module compilation
# ------------------------------------------------------------
RUN cd /rpi-kernel && \
    if [ -f .config ]; then \
        echo "Using config_pi"; \
        make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- olddefconfig; \
    else \
        echo "Using default bcm2711_defconfig"; \
        make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- bcm2711_defconfig; \
    fi && \
    make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- prepare && \
    make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- modules_prepare && \
    make -j9 ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu-

# ------------------------------------------------------------
# Set environment for module compilation
# ------------------------------------------------------------
ENV KERNEL_SRC=/rpi-kernel
ENV ARCH=arm64
ENV CROSS_COMPILE=aarch64-linux-gnu-

WORKDIR /workspace

CMD ["/bin/bash"]
