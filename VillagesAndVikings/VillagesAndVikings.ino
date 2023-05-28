// Variables de juego
uint8_t poblacion = 20;
uint8_t recursos = 30;
uint8_t limiteRecursos = 45;
uint8_t limitePoblacion = 30; // Límite de población inicial
int8_t dinero = 5;
uint16_t turno = 0;
#define prefixInfo "[INFO] "
#define prefixCitizen"[NOTICIAS] "

uint8_t probabilidadInvasion = 0;

void setup() {
  // Inicializa la comunicación Serial
  Serial.begin(9600);

  // Muestra el mensaje de bienvenida y comandos
  Serial.println(F("¡Bienvenido a VillagesAndVikings!"));
  mostrarComandos();
}

void loop() {
  if (Serial.available()) {
    String comando = Serial.readStringUntil('\n');
    manejarComando(comando);
    verificarInvasion();
  }
}

void verificarInvasion() {
  if (probabilidadInvasion >= 70 && probabilidadInvasion < 100) {
    Serial.print(prefixCitizen);
    Serial.println(F("¡Alerta de invasión! Los vikingos se están acercando. Prepárate para defender la aldea."));
  } else if (probabilidadInvasion >= 100) {
    eventoAtaqueVikingo();
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
  Serial.print(prefixInfo);
  Serial.println(F("Comandos disponibles:"));
  Serial.println(F("- recolectar (r): recolecta 5 recursos"));
  Serial.println(F("- usar (u): usa 5 recursos y añade 2 de población"));
  Serial.println(F("- almacén (a): construye un almacén para aumentar el límite de recursos posibles (+10)"));
  Serial.println(F("- expandir (e): consume 15 recursos y aumenta el límite de población en 8"));
  Serial.println(F("- info (i): muestra un resumen de la información del juego"));
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
  Serial.print(F("║Población: "));
  Serial.println(poblacion);
  Serial.print(F("║Recursos: "));
  Serial.println(recursos);
  Serial.print(F("║Límite de Recursos: "));
  Serial.println(limiteRecursos);
  Serial.print(F("║Límite de Población: "));
  Serial.println(limitePoblacion);
  Serial.print(F("║Turno: "));
  Serial.println(turno);
  Serial.print(F("║Dinero: "));
  Serial.println(dinero);

  // Imprimir la parte inferior de la cuadrícula
  Serial.println(F("╚═════════════════════════════════╝"));
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
