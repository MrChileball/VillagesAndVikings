# VillagesAndVikings

VillagesAndVikings es un juego para los microcontroladores Arduino, hecho con la intención de probar el rendimiento y las capacidades de un microcontrolador tan limitado como lo es el Arduino UNO R3.

## Un proyecto y un juego a la vez.

El proyecto por el momento es bastante limitado y solo cuenta con algunas funciones básicas, como población, sistema de invasiones, recursos y almacenes.
La meta del proyecto es principalmente aprender a programar proyectos grandes, optimizar y hacer un buen uso de los recursos de arduino. Respecto al objetivo dentro del juego, la idea es gestionar una aldea por turnos, intentando sobrevivir a los ataques vikingos

## Objetivos cumplidos.

* Reducir el consumo de SRAM de 1890 Bytes a solo 289 Bytes (-84,71% de consumo)
* Organizar de manera correcta el programa
* Reducir el consumo de las variables globales
* Sistema de economía
* Gestor de ingresos en base a la población 
* Permitir guardar partidas en slots dedicados usando la memoria EEPROM.
* Arreglar el sistema de economía y calculos de los ingresos
* Sistema de invasiones y probabilidad de invasión

### Funciones por implementar



* Separar las funciones y comandos del archivo principal, creando una librería o archivos separados.
* Hacer que la felicidad y otras variables afecten a la cantidad de impuestos recaudados.
* Añadir un sistema de felicidad
* Añadir un Períodico con noticias sobre la aldea
* Añadir un sistema de soldados
