# Module I2C – sensor_hub_i2c.c

## Fonctionnalité :
Communication avec les capteurs via le bus I2C.

## Structures clés :

struct sensor_i2c {
    struct i2c_client *client; // Client I2C
    u8 addr;                   // Adresse I2C
    const char *name;          // Nom du capteur
    int id;                    // ID interne
    struct mutex lock;         // Protection concurrente
    bool initialized;          // État d’initialisation
};

struct sensor_config {
    int sample_rate;           // Fréquence d’échantillonnage
    int threshold_high;        // Seuil haut
    int threshold_low;         // Seuil bas
    bool enabled;              // Capteur actif
};

## Fonctions clés :

| Fonction | Description |
|--------|-------------|
| sensor_hub_i2c_probe(struct i2c_client *client) | Initialise le capteur. |
| sensor_hub_i2c_remove(struct i2c_client *client) | Libère les ressources I2C. |
| sensor_hub_i2c_read(struct i2c_client *client, u8 reg) | Lit un registre. |
| sensor_hub_i2c_write(struct i2c_client *client, u8 reg, u8 value) | Écrit un registre. |
| sensor_hub_i2c_read_block(...) | Lecture multi-octets. |
| sensor_hub_i2c_write_block(...) | Écriture multi-octets. |
| sensor_hub_i2c_set_config(...) | Configure le capteur. |
| sensor_hub_i2c_get_status(...) | Récupère l’état. |
| sensor_hub_i2c_reset(...) | Reset du capteur. |
| sensor_hub_i2c_update(...) | Mise à jour périodique. |
