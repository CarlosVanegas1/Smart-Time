#include <WiFi.h>
#include <BluetoothSerial.h>

const int MAX_INTENTOS = 5;

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

BluetoothSerial SerialBT;
bool isConnectedToWiFi = false;

void connectToWiFi(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);
  int intentos = 0;

  while (WiFi.status() != WL_CONNECTED) {
    // VERIFICAR INTENTOS CON CONTRASEÑA INCORRECTA
    if (intentos > MAX_INTENTOS) {
        SerialBT.println("¡Demasiados intentos fallidos! Inicie nuevamente.");
        return;
      }
    if (WiFi.status() == WL_CONNECT_FAILED) {
      intentos++;
      SerialBT.println("¡Contraseña incorrecta!");
      SerialBT.print("Quedan ");SerialBT.print(MAX_INTENTOS - intentos);SerialBT.println("Intentos");
      SerialBT.println("Ingrese la contraseña nuevamente:");
      while (!SerialBT.available()) {
        delay(100);
      }
      String newPassword = SerialBT.readString();
      newPassword.trim();//Quitar espacios en blanco antes y después.
      
      connectToWiFi(ssid, newPassword.c_str());
      
      return;
    } else {
      SerialBT.println("Error al conectarse a la red WiFi");
    }

    delay(1000);
  }

  SerialBT.print("Conectado a la red: ");
  SerialBT.println(ssid);

  isConnectedToWiFi = true;

  // Resto del código una vez que se conecta a la red WiFi
  // ...
}

void setup() {
  SerialBT.begin("ESP32"); // Nombre del dispositivo Bluetooth
  Serial.begin(115200);
}

void loop() {
  if (!isConnectedToWiFi) {
    // Realizar acciones específicas cuando no está conectado a una red WiFi
    // ...

    if (SerialBT.available()) {
      char rx = SerialBT.read();
      if (rx == 'c') {
        while (true) {
          // Escanear redes WiFi disponibles
          int numRedes = WiFi.scanNetworks();
          SerialBT.println("Redes WiFi disponibles:");

          for (int i = 0; i < numRedes; i++) {
            SerialBT.print(i + 1);
            SerialBT.print(": ");
            SerialBT.println(WiFi.SSID(i));
          }

          SerialBT.println("Seleccione una opción:");
          SerialBT.println("1. Conectar a una red WiFi");
          SerialBT.println("2. Reiniciar proceso de conexión");

          int opcion = 0;
          while (opcion < 1 || opcion > 2) {
            while (!SerialBT.available()) {
              delay(100);
            }
            opcion = SerialBT.parseInt();
            SerialBT.read(); // Limpiar el buffer del serial

            if (opcion < 1 || opcion > 2) {
              SerialBT.println("Opción inválida. Por favor, ingrese 1 o 2.");
            } else if (opcion == 1) {
              int seleccionRed = 0;
              while (seleccionRed < 1 || seleccionRed > numRedes) {
                SerialBT.println("Ingrese el número de la red a la que desea conectar:");
                while (!SerialBT.available()) {
                  delay(100);
                }
                seleccionRed = SerialBT.parseInt();
                SerialBT.read(); // Limpiar el buffer del serial

                if (seleccionRed < 1 || seleccionRed > numRedes) {
                  SerialBT.println("Opción inválida. Por favor, ingrese un número válido.");
                } else {
                  // Mostrar el nombre de la red seleccionada
                  String ssid = WiFi.SSID(seleccionRed - 1);
                  SerialBT.print("Conectando a la red: ");
                  SerialBT.println(ssid);

                  SerialBT.println("Ingrese la contraseña:");
                  while (!SerialBT.available()) {
                    delay(100);
                  }
                  String password = SerialBT.readString();
                  password.trim(); // Eliminar espacios en blanco al inicio y final

                  SerialBT.print("Contraseña ingresada: ");
                  SerialBT.println(password);

                  connectToWiFi(ssid.c_str(), password.c_str());

                  if (isConnectedToWiFi) {
                    break; // Salir del bucle y continuar con el resto del código
                  }
                }
              }
            } else if (opcion == 2) {
              SerialBT.println("Reiniciando proceso de conexión...");
              isConnectedToWiFi = false;
              break; // Volver al inicio para reiniciar el proceso de conexión
            }
          }
        }
      }
    }
  } else {
    // Realizar acciones específicas cuando está conectado a una red WiFi
    // ...

    if (SerialBT.available()) {
      char rx = SerialBT.read();
      if (rx == 'd') {
        isConnectedToWiFi = false;
        SerialBT.println("Desconectado de la red WiFi. Volviendo al inicio...");
      } else if (rx == 'r') {
        SerialBT.println("Reiniciando proceso de conexión...");
        isConnectedToWiFi = false;
      }
    }
  }
}
