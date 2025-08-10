# Projet-IOT
# 🔥 Détection de Gaz IoT avec ESP32, MQ-2, OLED et Blynk

## 📜 Description du Projet
Ce projet vise à concevoir un système intelligent et connecté de **détection de gaz inflammables** afin de renforcer la sécurité domestique et industrielle.  
Il repose sur un **ESP32** connecté à un capteur **MQ-2** pour mesurer en temps réel la concentration de gaz tels que le butane, propane, méthane, GPL, hydrogène ou fumée.  

Le système utilise :
- **OLED SSD1306** pour afficher l’état de détection.
- **LED rouge** pour une alerte visuelle locale.
- **Application Blynk** pour des notifications push et e-mail à distance.

Un traitement logiciel (moyenne glissante, hystérésis) permet de réduire les fausses alertes et d’optimiser la précision de détection.

---

## 🛠️ Architecture du Projet

### **Module 1 : ESP32 + Capteur MQ-2**
- Lecture analogique des niveaux de gaz.
- Pré-chauffage et calibration automatique.
- Transmission des données vers Blynk via Wi-Fi.
- **Technologies** : ESP32, Arduino IDE, C++.

### **Module 2 : OLED SSD1306 (Interface Locale)**
- Affichage en temps réel du niveau de gaz et de l’état ("Safe Air" / "GAS Detected").
- Affichage dynamique lors de la phase de calibration.

### **Module 3 : LED Rouge (Alerte Locale)**
- Allumage immédiat en cas de détection de gaz au-dessus du seuil.

### **Module 4 : Application Mobile Blynk (Surveillance à Distance)**
- Tableau de bord avec jauge en temps réel.
- LED virtuelle d’alerte.
- Notifications push et e-mail.

---

## 🔗 Flux de Données
1. Le **capteur MQ-2** lit la concentration de gaz et transmet la valeur à l’ESP32.
2. L’ESP32 applique un traitement (moyenne glissante, seuil + hystérésis).
3. Si gaz détecté : LED rouge ON, message OLED "GAS Detected", notification Blynk + e-mail.
4. Les données sont affichées sur le **dashboard Blynk** pour un suivi à distance.

---

## 🛠️ Technologies Utilisées
- **IoT & Microcontrôleur** : ESP32  
- **Capteur** : MQ-2  
- **Affichage** : OLED SSD1306  
- **Alerte** : LED + résistance 220Ω  
- **Application Mobile** : Blynk IoT  
- **Langage** : C++ (Arduino IDE)  

---

## ⚙️ Installation et Exécution

### **1. ESP32 (Détection et Envoi des Données)**
- Ouvrir le code `gas_detection.ino` dans Arduino IDE.
- Installer les bibliothèques :
  - WiFi.h
  - BlynkSimpleEsp32.h
  - Adafruit_GFX.h
  - Adafruit_SSD1306.h
- Configurer le SSID, mot de passe Wi-Fi et token Blynk.
- Compiler et téléverser sur l’ESP32.

### **2. Configuration Blynk**
- Créer un projet Blynk IoT.
- Ajouter :
  - **Gauge** (V4)
  - **LED virtuelle** (V1)
  - **Notifications**

---

## 📊 Résultats
- **Alerte locale** : LED rouge + affichage OLED.
- **Alerte distante** : Notifications push + e-mail via Blynk.
- **Surveillance continue** via dashboard Blynk.

---

## 📂 Structure du Dépôt



