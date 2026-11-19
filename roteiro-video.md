# Vídeo da demonstração do Alethos — 3min15s

[Vídeo no YouTube](https://youtu.be/h70IXoB_XMI)

A abertura de 20 segundos usa uma imagem do circuito e narração sintética para apresentar o Alethos, o botão PEDIR AJUDA e o envio via MQTT. A demonstração preserva a narração original e usa capturas dos testes no Wokwi e uma imagem do pedido recebido no cliente MQTT. Os créditos apresentam os nomes completos e os RMs. O arquivo tem vídeo H.264 em 1280 × 720 e áudio AAC.

## Sequência do vídeo narrado

- 00:00–00:20 — Apresentação do Alethos e do botão PEDIR AJUDA.
- 00:20–01:07 — Contexto e componentes.
- 01:07–01:20 — Conexão ao Wi-Fi e ao broker.
- 01:20–01:42 — Primeiro pedido.
- 01:42–02:00 — Botão mantido pressionado.
- 02:00–02:20 — Falha controlada.
- 02:20–02:35 — Restauração e reconexão.
- 02:35–02:51 — Cliente MQTT mostrando o pedido 3a8cb64d-4.
- 02:51–03:15 — Limites e próximos passos, com os créditos a partir de 03:04.

## Texto de referência da narração

Olá! Este é o Alethos, um guardião antigolpe criado para ajudar idosos diante de uma suspeita de golpe. Ao apertar o botão PEDIR AJUDA, o ESP32 envia um pedido por MQTT, para que um familiar possa receber. Os LEDs indicam conexão e o envio do pedido.

Este é o nosso protótipo de IoT para a GS CitizenTech, voltado à prevenção de golpes digitais contra idosos. O botão representa uma forma simples de iniciar um pedido de ajuda antes de tomar uma decisão sob pressão.

O circuito foi montado no Wokwi com uma placa ESP32, um botão, dois LEDs e dois resistores de 220 ohms. O botão usa o pino 18, e os LEDs usam os pinos 25 e 26. O código registra apenas um pedido por pressão.

Quando a simulação começa, a placa se conecta ao Wi-Fi virtual e ao servidor MQTT, chamado broker. O LED verde indica que a conexão está ativa.

Ao apertar o botão, o ESP32 publica uma mensagem no tópico do projeto. Ela contém uma identificação fictícia do dispositivo, o identificador do pedido e o tipo de solicitação. O LED vermelho acende por alguns segundos.

No teste seguinte, mantemos o botão pressionado. Mesmo assim, aparece apenas um novo pedido. Para enviar outro, é preciso soltar e apertar novamente. Isso evita disparos repetidos em um único toque.

Também simulamos uma falha controlada. O comando f no monitor serial muda temporariamente o destino da conexão. Ao apertar o botão nessa situação, o programa informa a falha. Esse pedido não fica armazenado para reenvio.

Com o comando r, restauramos o endereço do broker. A placa tenta se reconectar automaticamente. Depois da recuperação, é possível publicar outro pedido, como mostra o teste.

No cliente MQTT de teste, conferimos uma mensagem recebida com o identificador correspondente. Esse cliente serve para comprovar a comunicação com o broker; ele não é um aplicativo da família.

Este protótipo demonstra o envio do pedido de ajuda, sem confirmar leitura por uma pessoa. Usamos apenas dados fictícios no broker público. Para uso real, seriam necessários um serviço receptor, proteção dos dados e um tratamento mais confiável das falhas.
