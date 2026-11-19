// Alethos: guardião antigolpe — botão PEDIR AJUDA com ESP32
// Witalon Antonio Rodrigues — RM 559023
// Alexandre Colvet Delfino — RM 560059
// Enzo Luciano Barros de Oliveira — RM 559557
// Pedro Claudino Scarceli — RM 561023
// Luigi Thiengo Pires — RM 560755

#include <WiFi.h>
#include <PubSubClient.h>
#include <esp_system.h>

// Demonstracao com dados ficticios; o broker publico nao oferece privacidade.
const int BOTAO = 18, LED_PRONTO = 25, LED_PEDIDO = 26;
const char* WIFI_NOME = "Wokwi-GUEST";
const char* BROKER = "test.mosquitto.org";
const int PORTA = 1883;
const char* TOPICO = "citizentech/gs-480337469931445249/pedidos";
const char* DISPOSITIVO = "botao-demo-01";
const unsigned long DEBOUNCE_MS = 50, INTERVALO_WIFI = 10000;
const unsigned long INTERVALO_MQTT = 5000, DURACAO_STATUS = 3000;
WiFiClient rede;
PubSubClient mqtt(rede);
char sessao[9], clientId[32];
unsigned long contador = 0, mudouEm = 0, wifiEm = 0, mqttEm = 0, statusEm = 0;
int leituraAnterior = HIGH, estadoEstavel = HIGH;
bool wifiAnterior = false, mqttAnterior = false;
enum Resultado { NENHUM, ENVIO_OK, FALHA };
Resultado resultado = NENHUM;

void iniciarWifi() {
  Serial.println("Tentando conectar ao Wi-Fi...");
  WiFi.begin(WIFI_NOME, "", 6);
  wifiEm = millis();
}

void publicarPedido() {
  contador++;
  char payload[240];
  snprintf(payload, sizeof(payload),
    "{\"dispositivo\":\"%s\",\"pedido_id\":\"%s-%lu\",\"tipo\":\"pedido_ajuda\",\"descricao\":\"Duvida sobre possivel golpe digital\"}",
    DISPOSITIVO, sessao, contador);
  Serial.print("Pedido "); Serial.print(contador); Serial.println(" acionado.");
  bool enviado = mqtt.connected() && mqtt.publish(TOPICO, payload, false);
  statusEm = millis();
  resultado = enviado ? ENVIO_OK : FALHA;
  if (enviado) {
    Serial.println("Publicacao enviada ao transporte MQTT (QoS 0). Nao confirma entrega ou leitura.");
    Serial.println(payload);
  } else {
    Serial.println("FALHA ao publicar: verifique a conexao. Pedido nao foi armazenado.");
  }
}

void setup() {
  pinMode(BOTAO, INPUT_PULLUP);
  pinMode(LED_PRONTO, OUTPUT); pinMode(LED_PEDIDO, OUTPUT);
  Serial.begin(115200);
  Serial.println("Alethos | Botao PEDIR AJUDA");
  // Identificador aleatorio por execucao reduz colisoes entre simulacoes.
  snprintf(sessao, sizeof(sessao), "%08lx", (unsigned long)esp_random());
  snprintf(clientId, sizeof(clientId), "gs-ajuda-%s", sessao);
  mqtt.setServer(BROKER, PORTA);
  mqtt.setSocketTimeout(2);
  WiFi.mode(WIFI_STA);
  iniciarWifi();
  mqttEm = millis() - INTERVALO_MQTT;
  Serial.println("Botao pronto para leitura. Aguardando rede.");
}

void loop() {
  // Comandos de teste no monitor serial: f simula falha; r restaura o broker.
  while (Serial.available()) {
    char comando = Serial.read();
    if (comando == 'f') {
      mqtt.disconnect();
      mqtt.setServer("127.0.0.1", PORTA); // Endereco local sem broker: teste de falha.
      Serial.println("TESTE: broker indisponivel simulado.");
    } else if (comando == 'r') {
      mqtt.disconnect();
      mqtt.setServer(BROKER, PORTA);
      Serial.println("TESTE: broker normal restaurado; aguardando reconexao.");
    }
  }
  unsigned long agora = millis();
  // Debounce e deteccao da transicao: segurar nao cria novos pedidos.
  int leitura = digitalRead(BOTAO);
  if (leitura != leituraAnterior) mudouEm = agora;
  if (agora - mudouEm >= DEBOUNCE_MS && leitura != estadoEstavel) {
    estadoEstavel = leitura;
    if (estadoEstavel == LOW) publicarPedido();
  }
  leituraAnterior = leitura;

  bool wifiOK = WiFi.status() == WL_CONNECTED;
  if (wifiOK != wifiAnterior) {
    Serial.println(wifiOK ? "Wi-Fi conectado." : "Wi-Fi desconectado.");
    wifiAnterior = wifiOK;
  }
  if (!wifiOK && agora - wifiEm >= INTERVALO_WIFI) iniciarWifi();
  if (wifiOK && !mqtt.connected() && agora - mqttEm >= INTERVALO_MQTT) {
    mqttEm = agora;
    Serial.println("Tentando conectar ao broker MQTT...");
    if (mqtt.connect(clientId)) Serial.println("Broker MQTT conectado.");
    else { Serial.print("Falha MQTT, codigo: "); Serial.println(mqtt.state()); }
  }
  if (mqtt.connected()) mqtt.loop();
  bool mqttOK = wifiOK && mqtt.connected();
  if (mqttAnterior && !mqttOK) Serial.println("Broker MQTT desconectado; tentando reconectar.");
  mqttAnterior = mqttOK;

  if (resultado != NENHUM && millis() - statusEm >= DURACAO_STATUS) resultado = NENHUM;
  // Verde: broker conectado. Vermelho fixo: publicacao; piscando: falha/conexao.
  digitalWrite(LED_PRONTO, mqttOK ? HIGH : LOW);
  bool pisca = (millis() / 250) % 2 == 0;
  digitalWrite(LED_PEDIDO, resultado == ENVIO_OK ? HIGH :
               (resultado == FALHA || !mqttOK ? pisca : LOW));
  delay(1);
}
