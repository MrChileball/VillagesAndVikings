void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

void mostrarComandos() {
  Serial.print(prefixInfo);
  Serial.println("Comandos disponibles:");
  Serial.println("- recolectar: recolecta 5 recursos");
  Serial.println("- usar: usa 5 recursos y añade 2 de población");
  Serial.println("- almacén: construye un almacén para aumentar el límite de recursos posibles (+10)");
  Serial.println("- expandir: consume 15 recursos y aumenta el límite de población en 8");
  Serial.println("- info: muestra un resumen de la información del juego");
}

void recolectarRecursos() {
  if (recursos + 5 <= limiteRecursos) {
    recursos += 5;
    Serial.print(prefixInfo);
    Serial.println("Has recolectado 5 recursos.");
  } else {
    Serial.print(prefixInfo);
    Serial.println("No puedes recolectar más recursos. Has alcanzado el límite.");
  }
}

void usarRecursos() {
  if (recursos >= 5) {
    recursos -= 5;
    poblacion += 2;
    Serial.print(prefixInfo);
    Serial.println("Has usado 5 recursos y has añadido 2 de población.");
  } else {
    Serial.print(prefixInfo);
    Serial.println("No tienes suficientes recursos para realizar esta acción.");
  }
}

void construirAlmacen() {
  if (recursos >= 10) {
    recursos -= 10;
    limiteRecursos += 10;
    Serial.print(prefixInfo);
    Serial.println("Has construido un almacén y aumentado el límite de recursos posibles.");
  } else {
    Serial.println("No tienes suficientes recursos para construir un almacén.");
  }
}

void expandirAldea() {
  if (recursos >= 15) {
    recursos -= 15;
    limitePoblacion += 8;
    Serial.print(prefixInfo);
    Serial.println("Has expandido la aldea y aumentado el límite de población.");
  } else {
    Serial.print(prefixInfo);
    Serial.println("No tienes suficientes recursos para expandir la aldea.");
  }
}