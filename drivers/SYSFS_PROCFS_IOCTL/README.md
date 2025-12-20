# Module Sysfs – sensor_hub_sysfs.c

## Fonctionnalité :
Expose les capteurs dans /sys/class/sensor_hub/.

## Structures clés :

struct sensor_device {
    struct device *dev;            // Device kernel
    int id;                        // ID capteur
    const char *name;              // Nom logique
    int value;                     // Valeur courante
    bool enabled;                  // État actif
    struct device_attribute attr;  // Attribut sysfs
};

## Fonctions clés :

| Fonction | Description |
|--------|-------------|
| sensor_hub_attr_show(...) | Lecture sysfs. |
| sensor_hub_attr_store(...) | Écriture sysfs. |
| sensor_hub_create_sysfs_files(...) | Création des fichiers sysfs. |
| sensor_hub_remove_sysfs_files(...) | Suppression des fichiers sysfs. |
| sensor_hub_sysfs_read_temperature(...) | Lecture température. |
| sensor_hub_sysfs_read_power(...) | Lecture power. |
| sensor_hub_sysfs_write_power(...) | Activation/désactivation. |
| sensor_hub_sysfs_show_status(...) | Statut global. |
| sensor_hub_sysfs_store_config(...) | Modification configuration. |


# Module Procfs – sensor_hub_proc.c

## Fonctionnalité :
Interface /proc/sensor_hub/ pour debug et supervision.

## Structures clés :

struct sensor_proc_entry {
    struct proc_dir_entry *entry;
    int sensor_id;
    const char *name;
    bool writable;
};

## Fonctions clés :

| Fonction | Description |
|--------|-------------|
| sensor_hub_proc_init() | Création des entrées procfs. |
| sensor_hub_proc_exit() | Suppression des entrées procfs. |
| sensor_hub_proc_read(...) | Lecture des données. |
| sensor_hub_proc_write(...) | Écriture de commandes. |
| sensor_hub_proc_show_all_sensors(...) | Affichage global. |
| sensor_hub_proc_reset_sensor(...) | Reset capteur. |
| sensor_hub_proc_set_threshold(...) | Configuration seuil. |

## Callbacks Procfs :

static const struct proc_ops proc_file_ops = {
    .proc_open    = proc_temperature_open,
    .proc_read    = seq_read,
    .proc_lseek   = seq_lseek,
    .proc_release = single_release,
};

