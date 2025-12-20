# Module GPIO – sensor_hub_gpio.c

## Fonctionnalité :
Gestion des GPIO pour piloter et lire les capteurs.

## Structures clés :

struct sensor_gpio {
    int gpio_num;              // Numéro de la broche
    bool direction_out;        // Direction : entrée=false, sortie=true
    const char *label;         // Nom de la GPIO
    int irq;                   // Numéro d’interruption
    unsigned int debounce_ms;  // Anti-rebond
    bool active_high;          // Polarité de la GPIO
};


## Fonctions clés :

|Fonction	                                                                |Description                                                     |
|---------------------------------------------------------------------------|----------------------------------------------------------------|
|sensor_hub_gpio_init()	                                                    |Initialise toutes les GPIO et configure la direction par défaut.|
|sensor_hub_gpio_exit()	                                                    |Libère toutes les GPIO et désactive les interruptions.          |
|sensor_hub_gpio_request(int gpio)	                                        |Réserve une GPIO pour usage du driver.                          |
|sensor_hub_gpio_free(int gpio)	                                            |Libère une GPIO réservée.                                       |
|sensor_hub_gpio_direction_input(int gpio)	                                |Configure une GPIO en entrée.                                   |
|sensor_hub_gpio_direction_output(int gpio, int value)	                    |Configure une GPIO en sortie et initialise sa valeur.           |
|sensor_hub_gpio_read(int gpio)	                                            |Lit l’état actuel d’une GPIO (0 ou 1).                          |
|sensor_hub_gpio_write(int gpio, int value)	                                |Écrit une valeur sur une GPIO.                                  |
|sensor_hub_gpio_toggle(int gpio)	                                        |Inverse la valeur d’une GPIO configurée en sortie.              |
|sensor_hub_gpio_to_irq(int gpio)	                                        |Convertit une GPIO en IRQ pour interruptions.                   |
|sensor_hub_gpio_set_debounce(int gpio, unsigned int debounce_ms)	        |Définit l’anti-rebond pour une GPIO.                            |
|sensor_hub_gpio_set_active_low(int gpio, bool low)	                        |Définit la polarité active pour une GPIO.                       |
|sensor_hub_gpio_irq_handler(int irq, void *dev_id)                         |                                                                |