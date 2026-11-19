# Registro de testes observados

Data: 10/11/2026. Testes na interface do Wokwi e cliente web MQTTX, que assinou o tópico no mesmo broker via WebSocket seguro na porta 8081. Os trechos abaixo são transcrições dos estados exibidos nas interfaces; não são arquivos de captura de tela.

## Conexão e duas publicações
O Wokwi exibiu:
```text
Wi-Fi conectado.
Tentando conectar ao broker MQTT...
Broker MQTT conectado.
Pedido 1 acionado.
Publicacao enviada ao transporte MQTT (QoS 0). Nao confirma entrega ou leitura.
Pedido 2 acionado.
Publicacao enviada ao transporte MQTT (QoS 0). Nao confirma entrega ou leitura.
```
O MQTTX recebeu no tópico `citizentech/gs-480337469931445249/pedidos`, QoS 0:
```json
{"dispositivo":"botao-demo-01","pedido_id":"27dab6dc-1","tipo":"pedido_ajuda","descricao":"Duvida sobre possivel golpe digital"}
{"dispositivo":"botao-demo-01","pedido_id":"27dab6dc-2","tipo":"pedido_ajuda","descricao":"Duvida sobre possivel golpe digital"}
```
O segundo pedido resultou de um toque mantido por cerca de seis segundos de tempo real. O cliente exibiu apenas uma mensagem para esse toque. Trata-se de uma verificação da simulação, não de um ensaio com ruído de botão real.

## Indisponibilidade e retorno
Em uma nova execução, enviou-se `f` pelo monitor serial e pressionou-se o botão. Em seguida, enviou-se `r`:
```text
TESTE: broker indisponivel simulado.
Tentando conectar ao broker MQTT...
Falha MQTT, codigo: -2
Broker MQTT desconectado; tentando reconectar.
Pedido 1 acionado.
FALHA ao publicar: verifique a conexao. Pedido nao foi armazenado.
Tentando conectar ao broker MQTT...
Falha MQTT, codigo: -2
TESTE: broker normal restaurado; aguardando reconexao.
Tentando conectar ao broker MQTT...
Broker MQTT conectado.
Pedido 2 acionado.
Publicacao enviada ao transporte MQTT (QoS 0). Nao confirma entrega ou leitura.
```
Após a reconexão, o MQTTX recebeu:
```json
{"dispositivo":"botao-demo-01","pedido_id":"954acdd9-2","tipo":"pedido_ajuda","descricao":"Duvida sobre possivel golpe digital"}
```
O primeiro pedido dessa execução falhou e não foi armazenado. O teste de falha altera temporariamente o destino para o endereço local e não prova comportamento diante de todas as falhas reais. A versão salva foi reaberta em outra aba e o texto do sketch comparado com o código testado.

## Verificação após organizar os fios — 10/11/2026

Os LEDs e resistores foram alinhados, os fios passaram a seguir percursos separados e os retornos foram ligados aos pinos GND mais próximos. Foram mantidos os GPIOs 18, 25 e 26, os componentes e os valores dos resistores. O firmware não foi alterado.

Após salvar o diagrama, a simulação conectou ao broker e o botão gerou um pedido. Um assinante MQTT independente, conectado por TCP à porta 1883 do mesmo broker e inscrito apenas no tópico do projeto, recebeu às 18h48min10s (horário de Brasília):

```json
{"dispositivo":"botao-demo-01","pedido_id":"d5b81f7f-1","tipo":"pedido_ajuda","descricao":"Duvida sobre possivel golpe digital"}
```

O projeto foi recarregado no navegador e a nova disposição permaneceu salva. A imagem `circuito-organizado.jpg` mostra o desenho final.
