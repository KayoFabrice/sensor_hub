# Driver Caractère – sensor_hub_char.c

## Fonctionnalité :
Expose /dev/sensor_hub pour un accès direct user space.

## Structures clés :

struct sensor_char_device {
    dev_t dev_num;
    struct cdev cdev;
    struct class *class;
    struct device *device;
    struct mutex lock;
};

## Fonctions clés :

| Fonction | Description |
|--------|-------------|
| sensor_hub_char_init() | Initialisation du char device. |
| sensor_hub_char_exit() | Suppression du char device. |
| dev_open(...) | Ouverture du device. |
| dev_release(...) | Fermeture du device. |
| dev_read(...) | Lecture des données. |
| dev_write(...) | Écriture de commandes. |
| dev_ioctl(...) | Commandes ioctl. |
| dev_poll(...) | Support poll/select. |

## Callbacks Char Device :

static struct file_operations fops = {
    .open           = dev_open,
    .release        = dev_release,
    .read           = dev_read,
    .write          = dev_write,
    .unlocked_ioctl = dev_ioctl,
    .poll           = dev_poll,
};
