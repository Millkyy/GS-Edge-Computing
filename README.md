    GS - InfoMed

Camilly Breitbach Ishida - RM 551474
Vinícius Almeida Bernardino de Souza - RM 97888

  - Descrição do Problema de Saúde Abordado
O InfoMed Connect visa solucionar a demora e a eficácia na triagem em serviços de emergência médica. Muitas vezes, a falta de informações precisas pode levar a diagnósticos imprecisos, aumentando o tempo de espera e comprometendo a qualidade do atendimento.

  - Visão Geral da Solução Proposta
InfoMed Connect é uma plataforma inovadora de triagem para pronto-socorro que coloca a informação certa nas mãos dos profissionais de saúde, acelerando o processo e melhorando a precisão do atendimento. Os usuários fornecem dados essenciais, enquanto a plataforma utiliza lógica de priorização, integração com wearables e algoritmos para avaliar a gravidade da condição.

  Adição Tecnológica - Uso do DHT com ESP32
Para enriquecer ainda mais a coleta de dados em tempo real, implementaremos um sensor DHT junto ao ESP32. Esse dispositivo que servia  para medir temperatura e umidade, simulará a saturação de oxigênio (SpO2) e batimentos por minuto (BPM) no nosso projeto, oferecendo uma visão mais abrangente do estado de saúde do paciente.

  - Como Funcionará:
O ESP32, com o sensor DHT, realizará leituras simuladas de SpO2 e BPM. Esses dados serão integrados à plataforma, proporcionando uma avaliação mais completa e precisa da condição do paciente durante a triagem.

Como configurar e executar a aplicação:
  No Wokwi
- Conecte o DHT no ESP32, como mostrado na imagem.
- Cole nosso código.

  No node-red
- Faça dois nós no Node-red usando a rede MQTT in,  o analisador sintático jso, debug e o dashboard de sua preferência. (usamos o gauge para saturação e o chart para BPM)
- (veja na imagem como se conecta os nós) 
    - MQTT:
  - Clique no lapis e no servidor coloque "mqtt-dashboard.com" e na porta coloque "1883".
  - Nos topicos coloque "/Thinkitive/BPM" e "/Thinkitive/Saturação" (um para cada nó).
  - coloque 0 no QoS
    - Gauge:
  - Clique no lapis de group e coloque "Default" no nome e "Home" no Tab.
  - Na label coloque "Saturação"
  - Em units coloque "%"
    - Chart:
  - Na label coloque "BPM"
- Implemente o código e abra o dashboard.

  No Hive.mq
- Abra https://www.hivemq.com/demos/websocket-client/
- No host coloque "mqtt-dashboard.com" e port "8884"
- Conecta
- Adciona dois topicos: "/Thinkitive/BPM" e "/Thinkitive/Saturação"

- Rode o projeto no Wokwi e veja a leitura dos sensores nas aplicações.

link do wokwi:
  https://wokwi.com/projects/382323624225376257
