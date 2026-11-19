# Registro de uso de IA

Ferramenta principal: Codex, para implementação, documentação e operação da interface do Wokwi. O conteúdo foi verificado por testes no simulador e por assinatura MQTT independente, conforme `evidencias-testes.md`.

## Solicitações principais
1. Foi solicitado criar e testar no Wokwi um protótipo ESP32 para uma CitizenTech de prevenção a golpes, com botão de ajuda, LEDs, debounce e indicação de que nenhum familiar foi notificado sem integração real.
2. Na continuação, foi solicitado atualizar o projeto existente para publicar pedidos fictícios em MQTT, preservar o circuito, testar conexão, repetição, toque prolongado, falha e reconexão; comprovar publicação com cliente assinante; preparar arquivos, documentação e roteiro de entrega. Foram excluídos painel, aplicativo receptor, WhatsApp e confirmação familiar.

3. Foi solicitado organizar os fios do circuito existente. Os LEDs e resistores foram alinhados, os percursos de sinal e terra foram separados e os arquivos locais e o ZIP foram sincronizados com o projeto salvo. Um novo pedido foi recebido por assinante MQTT independente após a mudança visual.

4. Foi solicitado gravar a demonstração do teste, preparar um texto para a equipe narrar e depois juntar a voz ao vídeo. Foi montada inicialmente uma base sem narração de 2min55s, com capturas reais dos testes no Wokwi e uma imagem real do recebimento no MQTTX. Os vídeos foram salvos no disco de dados discoooolol.
5. Foi recebida a narração da equipe em um arquivo de áudio do WhatsApp. Uma transcrição local com Whisper serviu para identificar as entradas das cenas. O texto e as marcações de tempo foram conferidos com apoio do Gemini. O áudio ficou no ambiente local. As cenas foram sincronizadas com a gravação e o volume foi equilibrado, preservando o ritmo original da fala.
6. Uma abertura de 20 segundos apresenta o Alethos, o botão PEDIR AJUDA e o envio por MQTT. O texto foi preparado com apoio do Claude Sonnet 5.5 Medium e narrado localmente com Piper. A versão de 3min15s conserva a demonstração original e mostra os nomes completos e os RMs no encerramento.

## Apoio delegado
- Gemini 3.8 Flash Medium: conferência da correspondência entre os trechos falados e as oito cenas da demonstração, recebendo apenas texto e marcações de tempo.
- Gemini 3.8 Flash Medium: proposta inicial de roteiro oral, revisada e reescrita de acordo com o que foi demonstrado no vídeo.
- Gemini 3.8 Flash Medium: sugestão de disposição dos componentes e separação de sinais e retornos de terra. A sugestão foi revisada antes da aplicação e a versão final foi testada no Wokwi.
- Gemini 3.8 Flash High: proposta de lógica de debounce e indicadores na primeira etapa.
- Gemini 3.8 Flash High: revisão geral de riscos de Wi-Fi/MQTT, reconexão, falhas de publicação e limitações de QoS 0 na segunda etapa. A proposta foi considerada como apoio, não como comprovação de testes; o resultado incluiu hipóteses genéricas e não recebeu o código do projeto.

## Verificação humana pendente
A equipe deve revisar a documentação e o código, conferir o vídeo narrado e observar as regras da disciplina sobre uso de IA. A montagem com a narração foi concluída; o envio da atividade ainda está pendente.
