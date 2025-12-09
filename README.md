# BSP & Linux Driver Lab

## 📌 Description

**BSP & Linux Driver Lab** est un projet pratique pour apprendre le développement de drivers Linux et la maîtrise du Board Support Package (BSP) sur plateformes embarquées comme **Raspberry Pi**. Il couvre l’ensemble du workflow embarqué : bootloader, kernel Linux, Device Tree, drivers, et applications userspace. Le projet utilise GitHub pour un suivi structuré via **labels, issues et workflows automatisés**.

---

## 🎯 Objectifs

* Apprendre le développement de drivers Linux et l’intégration hardware.
* Mettre en pratique sur matériel réel (GPIO, I2C, SPI…).
* Suivre un workflow clair avec GitHub (issues, labels, CI/CD).
* Créer un portfolio technique pour ingénieur BSP/Linux embarqué.

---

## ⚡ Fonctionnalités

* **Bootloader** : U-Boot, configuration, debug UART, secure boot.
* **Kernel Linux** : compilation, modules, debug, workqueues, mmap, DMA.
* **Device Tree** : création d’overlays, nodes personnalisés, intégration hardware.
* **Drivers Linux** : GPIO, I2C, SPI, USB, character devices, sysfs, procfs.
* **Userspace** : applications C/Python pour interagir avec les drivers.
* **Tests & Debug** : validation hardware/software, optimisation.
* **GitHub Automation** : synchronisation labels et import des issues.

---

## 🗂 Structure du projet

```
BSP-Linux-Driver-Lab/
│
├── bootloader/         # Sources et scripts U-Boot
├── kernel/             # Sources kernel, modules externes
├── drivers/            # Drivers Linux (GPIO, I2C, SPI…)
├── device-tree/        # Device Tree sources et overlays
├── userspace/          # Applications C/Python pour tester les drivers
├── .github/
│   ├── labels.yml      # Labels GitHub
│   ├── issues.json     # Issues backlog BSP
│   └── workflows/
│       ├── labels.yml        # Workflow pour synchroniser les labels
│       └── import-issues.yml # Workflow pour importer les issues
└── README.md
```

---

## 🚀 Installation & usage

### 1️⃣ Cloner le repo

```bash
git clone git@github.com:TON_UTILISATEUR/TON_REPO.git
cd TON_REPO
```

### 2️⃣ Synchroniser les labels

Le workflow `Sync Labels` se déclenche automatiquement lors d’un push. Vérifie dans **Actions → Sync Labels**.

### 3️⃣ Importer les issues

* Sur GitHub : **Actions → Import Issues → Run workflow**
* Les issues seront créées automatiquement avec leurs labels.

### 4️⃣ Compiler et tester

* **Bootloader** :

```bash
cd bootloader
# Instructions pour compiler et tester U-Boot
```

* **Kernel Linux** :

```bash
cd kernel
make defconfig
make -j$(nproc)
```

* **Drivers** :

```bash
cd drivers
make modules
sudo insmod <module>.ko
```

* **Userspace** :

```bash
cd userspace
gcc app.c -o app
./app
```

---

## 📚 Bonnes pratiques

* Respecter l’arborescence pour faciliter le suivi GitHub.
* Documenter chaque module, driver et application.
* Utiliser labels et issues pour tracker les tâches et bugs.
* Faire des commits clairs et descriptifs.

---

## ✨ Contribution

* Fork → Crée une branche → Pull request
* Respecte les labels et workflow GitHub
* Documente toutes les modifications

---

## 📖 Licence

MIT License Fabrice KAYO
