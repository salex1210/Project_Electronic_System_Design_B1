# Generación de Voltaje de Control Analógico para Voltamperometría

Este proyecto presenta el diseño e implementación de un sistema electrónico para la **generación de voltaje analógico de control** orientado a aplicaciones de **voltamperometría**. El sistema convierte señales digitales (PWM) provenientes de un microcontrolador en señales analógicas precisas, adecuadas para técnicas electroquímicas como **LSV (Linear Sweep Voltammetry)** y **DPV (Differential Pulse Voltammetry)**.

El diseño se basa en una arquitectura de **tres etapas**, utilizando un convertidor digital–analógico (DAC), amplificadores operacionales y aislamiento galvánico para preservar la integridad de la señal.

---

## 📌 Autores

- **Carlos Fernando Carreño Jerez** – 2201729  
- **Gerson Alexander Sánchez Brito** – 2192987  
- **Brayan Smith Gil Cárdenas** – 2200493  
- **Kevin Sayari Durán Lizarazo** – 2194097  

---

## 🧠 Descripción General

La voltamperometría es una técnica electroanalítica utilizada para el análisis de procesos redox en sistemas electroquímicos. Para su correcta implementación se requiere:

- Control preciso del potencial aplicado.
- Alta resolución y estabilidad de la señal.
- Bajo nivel de ruido.
- Aislamiento entre dominios digitales y analógicos.

Este proyecto resuelve dichas necesidades mediante:

1. **Generación de alimentación dual** a partir de una fuente simple de 5 V.  
2. **Conversión digital–analógica** mediante el DAC **LTC2644**.  
3. **Acondicionamiento de señal** con amplificadores operacionales para adaptar el rango de salida a aplicaciones electroquímicas.  

Adicionalmente, se implementa **aislamiento galvánico** con optoacopladores para minimizar ruido e interferencias.

---

## 🏗️ Arquitectura del Sistema

### 🔹 Etapa 1 – Alimentación
- Conversión de una fuente simple de **5 V** a una alimentación dual mediante **MAX1044 / ICL7660**.
- Permite alimentar correctamente los amplificadores operacionales.

### 🔹 Etapa 2 – Conversión Digital–Analógica
- Uso del **LTC2644 DAC**, que convierte señales PWM del microcontrolador en salidas analógicas estables.
- Soporta referencias internas o externas.
- Incluye desacoplos para reducción de ruido.

### 🔹 Etapa 3 – Acondicionamiento de Señal
- Implementación con **TL081**.
- Ajusta la salida del DAC desde **0–2.5 V** al rango requerido: **–1.25 V a 1.25 V**.
- Elimina la necesidad de tierra virtual al aprovechar la referencia del DAC.

### 🔹 Aislamiento Galvánico
- Se emplea un **optoacoplador PS9851** para separar la electrónica digital de la analógica.
- Mejora la estabilidad y reduce interferencias electromagnéticas.

---

## 💻 Microcontrolador

El sistema fue probado con:

- **Arduino UNO** (descartado por picos de hasta 5.8 V).
- **ESP32** (seleccionado finalmente por su salida de **3.3 V**, más segura para el DAC).

---

## ⚙️ Técnicas Implementadas

### 🔸 LSV – Linear Sweep Voltammetry
- Señal triangular (rampa ascendente y descendente).
- 300 escalones por rampa.
- Resolución: **12 bits (0–4095)**.
- Frecuencia PWM: **5 kHz**.
- Tiempo por rampa: **12.5 s**.

### 🔸 DPV – Differential Pulse Voltammetry
- Barrido escalonado con pulsos diferenciales superpuestos.
- 30 escalones.
- Pulso de amplitud adicional configurable.
- Resolución: **12 bits**.
- Frecuencia PWM: **5 kHz**.

---

## 📐 Diseño de PCB

Se desarrollaron dos versiones:

### 🔹 Versión 1
- Tecnología **THT**.
- Uso de tres amplificadores.
- Problemas de enrutamiento bajo componentes.

### 🔹 Versión 2 (Optimizada)
- Inclusión de **optoacoplador**.
- Reducción a un solo amplificador operacional.
- Componentes **SMD**.
- Plano de tierra general.
- Cumple con recomendaciones de fabricación profesional.

---

## 📊 Resultados

### ✔ Funcionamiento por Componentes

| Componente | Resultado |
|-----------|----------|
| MAX1044 | –3.7 V a –4.1 V |
| PS9851 (Optoacoplador) | Falla detectada |
| LTC2644 | 0 V–2.5 V |
| TL081 | –1.14 V a 1.34 V |

Se detectó daño en el optoacoplador por falta de resistencia de protección en el LED de entrada.  
Como solución:
- Se reemplazó el microcontrolador por **ESP32**.
- Se eliminó el optoacoplador para pruebas directas.
- Se aceptó una mezcla de tierras (con ruido leve).

### 📈 Barrido LSV
- Rango obtenido: **–1.18 V a 1.31 V**.
- Leve desplazamiento por variaciones en **Vref** y ruido del TL081.
- Presencia de pequeños picos atribuibles a mezcla de tierras.

### 📉 Barrido DPV
- Comportamiento general correcto.
- Mayor sensibilidad al ruido debido a los pulsos diferenciales.
- Mantiene la estructura típica de la técnica.

---

## ✅ Conclusiones

- El uso de una arquitectura por etapas facilita el análisis, mantenimiento y optimización del sistema.
- La reducción de componentes mejoró el consumo energético y el tamaño de la PCB.
- El ESP32 permitió una salida más segura para el DAC.
- El aislamiento galvánico mejora la estabilidad y reduce ruido.
- Se recomienda añadir capacitores en paralelo en **Vcc, Vee y Vref** para mitigar fluctuaciones.
- El proyecto demuestra la viabilidad de generar señales voltamperométricas precisas mediante PWM + DAC.

---

## 📂 Contenido del Repositorio

- **Simulaciones en Proteus**
- **Código del microcontrolador (LSV y DPV)**
- **Diseño PCB**
- **Documentación técnica**

---

## 🔗 Referencias

- Analog Devices – **LTC2644 DAC Datasheet**  
- Analog Devices – **MAX1044 / ICL7660**  
- Renesas – **PS9851 Optocoupler**  
- Turmero, P. *Técnicas Voltamperométricas*  
- Labcenter Electronics – Proteus  

---

## 🚀 Cómo Usar el Proyecto

1. Cargar el código LSV o DPV en un **ESP32**.
2. Conectar la salida PWM al **LTC2644**.
3. Verificar alimentación dual.
4. Medir la salida acondicionada (–1.25 V a 1.25 V).
5. Conectar a un sistema electroquímico o banco de pruebas.

---

## 🛠️ Mejoras Futuras

- Reintegrar aislamiento galvánico con protecciones adecuadas.
- Filtrado adicional con capacitores en paralelo.
- Implementación de adquisición de corriente (potenciostato completo).
- Optimización del filtrado de ruido.

---

📌 *Proyecto académico de diseño de sistemas electrónicos para instrumentación electroquímica.*
