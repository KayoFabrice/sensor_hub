#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>

#define DRIVER_NAME "sensor_hub_gpio"

#define LED_GPIO    529
#define BUTTON_GPIO 539

MODULE_LICENSE("GPL");
MODULE_AUTHOR("YourName");
MODULE_DESCRIPTION("Sensor Hub GPIO module with button IRQ");

/* IRQ number for the button */
static unsigned int button_irq;
static bool led_state = false;

/* ---------- Interrupt Service Routine ---------- */
static irqreturn_t button_isr(int irq, void *dev_id)
{
    led_state = !led_state;
    gpio_set_value(LED_GPIO, led_state);

    printk(KERN_INFO "%s: button pressed, LED %s\n",
           DRIVER_NAME, led_state ? "ON" : "OFF");

    return IRQ_HANDLED;
}

/* ---------- Module init ---------- */
static int __init sensor_hub_gpio_init(void)
{
    int ret;

    printk(KERN_INFO "%s: initializing\n", DRIVER_NAME);

    /* Request LED GPIO */
    ret = gpio_request(LED_GPIO, "sensor_hub_led");
    if (ret) {
        printk(KERN_ERR "%s: failed to request LED GPIO\n", DRIVER_NAME);
        return ret;
    }
    gpio_direction_output(LED_GPIO, 0);

    /* Request Button GPIO */
    ret = gpio_request(BUTTON_GPIO, "sensor_hub_button");
    if (ret) {
        printk(KERN_ERR "%s: failed to request BUTTON GPIO\n", DRIVER_NAME);
        gpio_free(LED_GPIO);
        return ret;
    }
    gpio_direction_input(BUTTON_GPIO);

    /* Map GPIO to IRQ */
    button_irq = gpio_to_irq(BUTTON_GPIO);
    if (button_irq < 0) {
        printk(KERN_ERR "%s: failed to get IRQ number\n", DRIVER_NAME);
        ret = button_irq;
        goto err_gpio;
    }

    /* Request IRQ */
    ret = request_irq(button_irq,
                      button_isr,
                      IRQF_TRIGGER_FALLING,
                      "sensor_hub_button_irq",
                      NULL);
    if (ret) {
        printk(KERN_ERR "%s: failed to request IRQ\n", DRIVER_NAME);
        goto err_gpio;
    }

    printk(KERN_INFO "%s: GPIO and IRQ successfully initialized\n", DRIVER_NAME);
    return 0;

err_gpio:
    gpio_free(BUTTON_GPIO);
    gpio_free(LED_GPIO);
    return ret;
}

/* ---------- Module exit ---------- */
static void __exit sensor_hub_gpio_exit(void)
{
    free_irq(button_irq, NULL);
    gpio_set_value(LED_GPIO, 0);
    gpio_free(LED_GPIO);
    gpio_free(BUTTON_GPIO);

    printk(KERN_INFO "%s: unloaded\n", DRIVER_NAME);
}

module_init(sensor_hub_gpio_init);
module_exit(sensor_hub_gpio_exit);
