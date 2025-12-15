# Diretório de Eletrônica

Este diretório contém todos os arquivos relacionados ao projeto eletrônico do robô *mini sumô*
---

## 1. Lista de Componentes (BOM)

**Planilha Completa (Google Sheets):** [Acessar Planilha de Componentes Eletrónicos](https://docs.google.com/spreadsheets/d/1agG4XEwVY7tFlbT6GtZfWE7ugiVqS48p61Cghws9TIE/edit?usp=sharing)

| Componente | Função no Robô |
| :--- | :--- |
| ESP32 Devkit V1 | Microcontrolador central (cérebro do robô). |
| Ponte H Dupla com Driver TB6612FNG | Conexão e Controle dos motores N20. |
| Bateria 7,7V (2x Células de Lítio em Série) | Fonte de energia principal para todo o sistema. |
| Regulador De Tensão Step Down LM2596 | Converte 7,7V para 5V, alimentando o ESP32|
| Switch | Interruptor principal de energia. |
| Barra de pinos | Conectores para fácil prototipagem e interligação. |
| 2 Motores N20 | Motores de corrente contínua para propulsão. |
| 2 Rodas de Silicone | Acoplamento aos motores para locomoção. |
| Placa Universal | Base para montagem dos componentes eletrônicos. |
| Buzzer ativo 5V | Sinalização sonora e feedback de status. |
|2 Conectores Borne 2 vias | Dispositivos que permitem a conexão elétrica entre diferentes fios ou cabos.


## 2. Diagramas de Conexão

| Título | Imagem | 
| :--- | :--- | 
| **Diagrama de Conexões (Versão Final)** | <img src="img/Diagramas de conexões (Versão Final).png" alt="Diagramas de conexões (Versão Final)" width="100%"> |
| **Diagrama de Conexões Sem ESP32** | <img src="img/Circuito Eletrônico Sem ESP32 (Versão Final).png" alt="Diagramas de Conexões Sem ESP32 (Versão Final)" width="100%"> |

**Cirkit Designer (Diagrama Final 12/12)** |[ Link para Visualização do Diagramas de Conexões no site do Cirkit](https://app.cirkitdesigner.com/project/8f864acf-6e72-45a9-822b-39d40fed3360) |

## 3. Esquemáticos eletrônicos
| Título | Imagem | 
| :--- | :--- | 
| **Esquemático Eletrônico (Versão Final)** | <img src="img/Esquemático Eletrônico_V.Final.png" alt="Diagramas de conexões (Versão Final)" width="100%"> |
|**Layout de PCB (Rascunho)** | <img src="img/Rascunho layout PCI.png" alt="Esquemático do Projeto" width="100%"> |


## 4. Diagramas de Pinout
| Pino do ESP32 | Componente Conectado | Pino do Componente | Função |
| :--- | :--- | :--- | :--- |
| **Vin** | StepDownLM2596, TB6612FNG | Vout, VM | Alimentação lógica (Tensão regulada). |
| **GND** | StepDownLM2596, TB6612FNG, Buzzer | GND | Referência de terra comum. |
| **D33** | TB6612FNG Motor Driver | STBY | Habilita/Desabilita o driver (Standby). |
| **D26** | TB6612FNG Motor Driver | PWMA | Sinal PWM para o Motor A (Velocidade). |
| **D13** | TB6612FNG Motor Driver | AI1 | Controle de direção 1 do Motor A. |
| **D14** | TB6612FNG Motor Driver | AI2 | Controle de direção 2 do Motor A. |
| **D25** | TB6612FNG Motor Driver | PWMB | Sinal PWM para o Motor B (Velocidade). |
| **D12** | TB6612FNG Motor Driver | BI1 | Controle de direção 1 do Motor B. |
| **D27** | TB6612FNG Motor Driver | BI2 | Controle de direção 2 do Motor B. |
| **D4** | Buzzer | VCC | Ativação do Buzzer (Sinal Digital HIGH/LOW). |

| Componente | Pino | Conexão de Saída/Entrada | Destino |
| :--- | :--- | :--- | :--- |
| **Bateria**| **IN+** | Saída de tensão bruta| Toggle Switch (L2) |
| **Bateria** | **GND** | Referência de terra | StepDownLM2596 (Gnd) |
| **Toggle Switch** | **COM** | Tensão com chaveamento (liga/desliga) | StepDownLM2596 (Vin) |
| **StepDownLM2596** | **Vin** | Entrada de tensão (do Switch) | Toggle Switch (COM) |
| **StepDownLM2596** | **Gnd** | Terra Comum | Bateria (GND), ESP32 (GND), TB6612FNG (GND) |
| **StepDownLM2596** | **Vout** | Tensão regulada 5V | ESP32 (Vin) e TB6612FNG (VM) |
## Documentação

Neste README deve conter as instruções de uso, pinos utilizados e explicação do circuito.
