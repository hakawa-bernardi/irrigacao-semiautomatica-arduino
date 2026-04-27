# 🌱 Projeto de Irrigação Semiautomático com Arduino

> Trabalho de Conclusão de Curso — Engenharia de Computação  
> Pontifícia Universidade Católica de Goiás (PUC Goiás) — 2025  
> Aprovado em 02/12/2025

---

## 📋 Sobre o Projeto

Sistema de irrigação semiautomático desenvolvido com Arduino UNO, capaz de monitorar a umidade do solo e o nível de água do reservatório em tempo real, acionando a bomba de irrigação automaticamente quando necessário — e também manualmente, por meio de um botão físico.

O projeto foi desenvolvido como TCC do curso de Engenharia de Computação da PUC Goiás, com foco em **sustentabilidade hídrica**, **sistemas embarcados** e **automação de baixo custo**.

---

## ⚙️ Funcionalidades

- ✅ Leitura contínua da umidade do solo via sensor analógico
- ✅ Medição do nível de água no reservatório com sensor de distância laser (VL53L0X)
- ✅ Acionamento automático da bomba quando a umidade estiver abaixo do limiar (valor digital < 800)
- ✅ Acionamento manual da bomba via botão físico
- ✅ Exibição de status em tempo real no display LCD 16x2
- ✅ LED de alerta visual para baixo nível de água ou erro de sensor
- ✅ Proteção elétrica da bomba via módulo relé

---

## 🧰 Componentes de Hardware

| Componente | Descrição |
|---|---|
| Arduino UNO R3 | Microcontrolador principal |
| Sensor de umidade do solo | Leitura analógica (pino A0) |
| Sensor VL53L0X | Distância laser I2C para nível do reservatório |
| Display LCD 16x2 com I2C | Interface visual do sistema (endereço 0x27) |
| Módulo Relé 5V | Acionamento seguro da bomba |
| Minibomba d'água 3V–6V | Responsável pela irrigação |
| LED 5mm vermelho | Indicador visual de alerta |
| Botão push-button | Acionamento manual da irrigação |
| Protoboard 400 furos + Jumpers | Montagem do circuito |

---

## 📚 Bibliotecas Utilizadas

Instale as bibliotecas abaixo pelo **Gerenciador de Bibliotecas** do Arduino IDE:

| Biblioteca | Finalidade |
|---|---|
| `Wire.h` | Comunicação I2C (nativa do Arduino IDE) |
| `LiquidCrystal_I2C` | Controle do display LCD via I2C |
| `Adafruit_VL53L0X` | Comunicação com o sensor de distância laser |

---

## 🔌 Mapeamento de Pinos

| Pino Arduino | Componente |
|---|---|
| `A0` | Sensor de umidade do solo |
| `2` | Botão de irrigação manual (INPUT_PULLUP) |
| `8` | LED de alerta |
| `11` | Módulo relé (bomba) |
| `SDA / SCL` | LCD I2C + Sensor VL53L0X |

---

## 🧠 Lógica de Funcionamento

```
Inicialização
│
├── Verificação do sensor VL53L0X
│     └── Falha → exibe erro no LCD e para
│
└── Loop principal (a cada 1 segundo)
      │
      ├── Botão pressionado?
      │     └── Sim → pisca LED 3x, aciona bomba por ~3s (modo manual)
      │
      ├── Medir distância do sensor VL53L0X
      │     ├── dist ≤ 10 cm → "Nivel Adequado" no LCD, LED apagado
      │     ├── dist > 10 cm → "Reabastecer!!!" no LCD, LED aceso
      │     └── Erro (-1)   → "ERRO NO SENSOR!" no LCD, LED piscando
      │
      └── Controle automático da bomba
            ├── Umidade < 800 → liga relé (bomba ligada)
            └── Umidade ≥ 800 → desliga relé (bomba desligada)
```

---

## 🚀 Como usar

### 1. Clone o repositório

```bash
git clone https://github.com/seu-usuario/irrigacao-semiautomatica.git
cd irrigacao-semiautomatica
```

### 2. Abra o código no Arduino IDE

- Abra o arquivo `VersaoFinal.ino` no **Arduino IDE 2.x**
- Instale as bibliotecas listadas acima pelo Gerenciador de Bibliotecas

### 3. Configure e envie

- Conecte o Arduino UNO via USB
- Selecione a porta correta em **Ferramentas → Porta**
- Clique em **Upload** (→)

### 4. Monte o circuito

Siga o mapeamento de pinos da tabela acima e conecte todos os componentes na protoboard conforme o projeto.

---

## 📁 Estrutura do Repositório

```
irrigacao-semiautomatica/
│
├── VersaoFinal.ino                        # Código-fonte principal (Arduino)
├── README.md                              # Documentação do projeto
└── docs/
    └── TCC_Hakawa_Bernardi_VersaoFinal.pdf  # Trabalho de Conclusão de Curso completo
```

> 📖 O TCC também está disponível no repositório institucional da PUC Goiás:  
> [Projeto de Irrigação Semiautomático — Repositório PUC Goiás](https://repositorio.pucgoias.edu.br/jspui/handle/123456789/9711)

---

## 🔬 Metodologia

O projeto foi desenvolvido seguindo o **Modelo em Cascata**, com as etapas:

1. **Levantamento de Requisitos** — definição dos sensores, atuadores e funcionalidades
2. **Projeto** — arquitetura do hardware e lógica do software, incluindo Diagrama de Contexto
3. **Implementação** — codificação modular no Arduino IDE
4. **Verificação** — testes unitários e integrados de cada componente
5. **Manutenção** — ajustes de calibração e identificação de melhorias futuras

---

## 📈 Possibilidades de Expansão

- 📡 Integração com IoT para monitoramento remoto via app ou dashboard web
- ☀️ Alimentação por energia solar (painéis fotovoltaicos)
- 📊 Registro de histórico de umidade com cartão SD ou banco de dados em nuvem
- 🌡️ Adição de sensor de temperatura e umidade do ar (DHT22)
- 📱 Notificações push via Wi-Fi com módulo ESP8266/ESP32

---

## 👨‍💻 Autor

**Hakawã Luiz Bernardi**  
Engenharia de Computação — PUC Goiás  
Orientador: Prof. Me. André Luiz Alves  
Banca: Prof. Me. Daniel Corrêa da Silva · Prof.ª Dra. Martha Nascimento Castro

📖 [Leia o TCC completo no repositório da PUC Goiás](https://repositorio.pucgoias.edu.br/jspui/handle/123456789/9711)

---

## 📄 Licença

Este projeto está sob a licença [MIT](LICENSE). Sinta-se livre para estudar, modificar e reutilizar com os devidos créditos.
