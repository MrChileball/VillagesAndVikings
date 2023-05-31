#include <EEPROM.h>

// Variables de juego

uint8_t poblacion = 20;
uint8_t limitePoblacion = 30; // Límite de población inicial

uint8_t recursos = 30;
uint8_t limiteRecursos = 45; // Límite de recursos inicial

int dinero= 5; // Dinero inicial
int ingreso;
const byte ingresoBase = 5;
int turno = 0;
byte turnosRecaudacion = 10;

// Direcciones de memoria en la EEPROM para cada variable
#define ADDR_POBLACION 60
#define ADDR_LIMITE_POBLACION 61
#define ADDR_RECURSOS 62
#define ADDR_LIMITE_RECURSOS 63
#define ADDR_DINERO 64
#define ADDR_TURNO 65
#define ADDR_PROBABILIDAD_INVASION 66



//Se definen los prefijos para información y noticias
#define prefixInfo "[INFO] "
#define prefixCitizen"[NOTICIAS] "

uint8_t probabilidadInvasion = 0; //Probabilidad inicial de un ataque.

void setup() {
  // Inicializa la comunicación Serial
  Serial.begin(9600);

  // Muestra el mensaje de bienvenida y comandos
  Serial.println(F("¡Bienvenido a VillagesAndVikings!")); // la función F() almacena cadenas de texto en la flash, se ahorra MUCHA sram!
  mostrarComandos(); //Muestra el mensaje de comandos disponibles
  

  /* NO SE DEBEN CARGAR LOS DATOS DE GUARDADO EN EL VOIDSETUP NI VOIDLOOP
  Explicación: La memoria EEPROM tiene una capacidad limite de entre 100 mil a 1 millón de escritura, 
  si se realiza una escritura en cada void loop  o setup la memoria va a degradarse rápidamente.
  */
}

void loop() {
  if (Serial.available()) {
    String comando = Serial.readStringUntil('\n');
    manejarComando(comando);
    verificarInvasion(); //Cada turno se verifica la probabilidad de invasión
    ingresosContador();
  }
}



void manejarComando(String comando) {
  // Convertir el comando a minúsculas
  comando.toLowerCase();

  if (comando == "ayuda" || comando == "a") {
    mostrarComandos();
  } else if (comando == "recolectar" || comando == "r") {
    turno++;
    recolectarRecursos();
    probabilidadInvasion += 14;
  } else if (comando == "usar" || comando == "u") {
    turno++;
    usarRecursos();
    probabilidadInvasion += 14;
  } else if (comando == "almacén" || comando == "almacen" || comando == "a") {
    turno++;
    construirAlmacen();
    probabilidadInvasion += 14;
  } else if (comando == "expandir" || comando == "e") {
    turno++;
    expandirAldea();
    probabilidadInvasion += 14;
  } else if ( comando == "guardar") {
    guardarVariablesEnEEPROM();
  } else if ( comando == "cargar") {
    cargarVariablesDesdeEEPROM();
  } else if (comando == "test1") {
    eventoAtaqueVikingo();
  } else if (comando == "info" || comando == "i") {
    mostrarInfo();
  } else {
    Serial.print(prefixInfo);
    Serial.println(F("Comando inválido. Introduce 'ayuda' para ver la lista de comandos."));
  }
  
}

void mostrarComandos() {
  Serial.println(F("╔════════════════════════════════╗"));
  Serial.println(F("          MENÚ DE AYUDA:           "));
  Serial.println(F("╚════════════════════════════════╝"));
  Serial.println();
  Serial.println(F("Juego:"));
  Serial.println(F("- recolectar (r): recolecta 5 recursos"));
  Serial.println(F("- usar (u): usa 5 recursos y añade 2 de población"));
  Serial.println(F("- almacén (a): construye un almacén para aumentar el límite de recursos posibles (+10)"));
  Serial.println(F("- expandir (e): consume 15 recursos y aumenta el límite de población en 8"));
  Serial.println(F("Ayuda:"));
  Serial.println(F("- info (i): muestra un resumen de la información del juego"));
  Serial.println(F("Partida:"));
  Serial.println(F("- guardar: guarda la partida en la EEPROM"));
  Serial.println(F("- cargar: carga las partida de la EEPROM"));
}

void recolectarRecursos() {
  if (recursos + 5 <= limiteRecursos) {
    recursos += 5;
    Serial.print(prefixInfo);
    Serial.println(F("Has recolectado 5 recursos."));
  } else {
    Serial.print(prefixInfo);
    Serial.println(F("No puedes recolectar más recursos. Has alcanzado el límite."));
  }
}
void usarRecursos() {
  if (recursos >= 5) {
    recursos -= 5;
    if (poblacion + 2 <= limitePoblacion) {
      poblacion += 2;
      Serial.print(prefixInfo);
      Serial.println(F("Has usado 5 recursos y has añadido 2 de población."));
    } else {
      Serial.print(prefixInfo);
      Serial.println(F("No puedes añadir más población. Has alcanzado el límite."));
    }
  } else {
    Serial.print(prefixInfo);
    Serial.println(F("No tienes suficientes recursos para realizar esta acción."));
  }
}
void construirAlmacen() {
  if (recursos >= 10) {
    recursos -= 10;
    limiteRecursos += 10;
    Serial.print(prefixInfo);
    Serial.println(F("Has construido un almacén y aumentado el límite de recursos posibles."));
  } else {
    Serial.print(prefixInfo);
    Serial.println(F("No tienes suficientes recursos para construir un almacén."));
  }
}
void expandirAldea() {
  if (recursos >= 15) {
    recursos -= 15;
    limitePoblacion += 8;
    Serial.print(prefixInfo);
    Serial.println(F("Has expandido la aldea y aumentado el límite de población."));
  } else {
    Serial.print(prefixInfo);
    Serial.println(F("No tienes suficientes recursos para expandir la aldea."));
  }
}

void mostrarInfo() {
  // Imprimir la parte superior de la cuadrícula
  Serial.println(F("╔═════════════════════════════════╗"));
  Serial.println(F("║     Resumen de información      ║"));
  Serial.println(F("╠═════════════════════════════════╣"));

  // Imprimir cada variable en una línea separada
  Serial.print(F("║ Población: "));
  Serial.println(poblacion);
  Serial.print(F("║ Recursos: "));
  Serial.println(recursos);
  Serial.print(F("║ Límite de Recursos: "));
  Serial.println(limiteRecursos);
  Serial.print(F("║ Límite de Población: "));
  Serial.println(limitePoblacion);
  Serial.print(F("║ Turno: "));
  Serial.println(turno);
  Serial.print(F("║ Dinero e ingresos c/5T: "));
  Serial.println(dinero);
  Serial.print(F(" / "));
  Serial.println(ingreso);

  // Imprimir la parte inferior de la cuadrícula
  Serial.println(F("╚═════════════════════════════════╝"));
}

void gestorDinero (){
  int multiplicador;
  multiplicador = poblacion * 0.8;
  ingreso = ingresoBase + multiplicador;
}

void ingresosContador() {
  gestorDinero();
  if  (turno  % turnosRecaudacion == 5) {
      dinero = dinero + ingreso;
      Serial.println("");
      Serial.print("[ECONOMIA] ");
      Serial.print("¡Se ha añadido ");
      Serial.print(ingreso);
      Serial.println(" al dinero! ");
      Serial.println("");
    }
}
void verificarInvasion() {
  if (probabilidadInvasion >= 20 && probabilidadInvasion < 50) {
    Serial.print(prefixCitizen);
    Serial.println(F("¡Hemos avistado una expedición vikinga pasando las montañas!"));
    Serial.println(F("Deberiamos tomar medidas preventivas en caso de un ataque"));
  } else if (probabilidadInvasion >= 50 && probabilidadInvasion < 100) {
    Serial.print(prefixCitizen);
    Serial.println(F("¡Alerta de invasión! Los vikingos se están acercando ¡Acaban de cruzar las montañas!."));
  } else if (probabilidadInvasion >= 100) {
    eventoAtaqueVikingo();

  }
}
void eventoAtaqueVikingo() {
  // Define el porcentaje de disminución de recursos por el ataque
  uint8_t porcentajeDisminucion = 15; // 10% de disminución de recursos
  // Calcula la cantidad a disminuir
  uint8_t cantidadDisminuir = recursos * porcentajeDisminucion / 100;
  recursos -= cantidadDisminuir; // resta los recursos saqueados
  // Muestra un mensaje indicando el resultado del ataque
  Serial.print(prefixInfo);
  Serial.print(F("¡Los vikingos han atacado el pueblo! Recursos disminuidos en "));
  Serial.print(cantidadDisminuir);
  Serial.println(F("."));
  Serial.print(F("Recursos restantes: "));
  Serial.println(recursos);
  probabilidadInvasion = 0;
}
void cargarVariablesDesdeEEPROM() {
  // Cargar poblacion desde la EEPROM
  EEPROM.get(ADDR_POBLACION, poblacion);
  EEPROM.get(ADDR_LIMITE_POBLACION, limitePoblacion);
  EEPROM.get(ADDR_RECURSOS, recursos);
  EEPROM.get(ADDR_LIMITE_RECURSOS, limiteRecursos);
  EEPROM.get(ADDR_DINERO, dinero);
  EEPROM.get(ADDR_TURNO, turno);
  EEPROM.get(ADDR_PROBABILIDAD_INVASION, probabilidadInvasion);
}
void guardarVariablesEnEEPROM() {
  EEPROM.put(ADDR_POBLACION, poblacion);
  EEPROM.put(ADDR_LIMITE_POBLACION, limitePoblacion);
  EEPROM.put(ADDR_RECURSOS, recursos);
  EEPROM.put(ADDR_LIMITE_RECURSOS, limiteRecursos);
  EEPROM.put(ADDR_DINERO, dinero);
  EEPROM.put(ADDR_TURNO, turno);
  EEPROM.put(ADDR_PROBABILIDAD_INVASION, probabilidadInvasion);
}


