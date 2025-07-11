# 🦽 SmartAssebility

**Sistema de Acessibilidade com Sensor Ultrassônico e Comunicação BLE**

Um projeto que combina **Galaxy Watch5** (Wear OS) + **Raspberry Pi** + **Sensor HC-SR04** para criar um sistema de acessibilidade que detecta obstáculos e comunica via Bluetooth Low Energy.

## 🆕 Melhorias Recentes

### **📱 App Android (Galaxy Watch5)**
- ✅ **Detecta TODOS os dispositivos BLE** (não apenas os com nomes específicos)
- ✅ **Compatibilidade total** com Android 11, 12 e 13+
- ✅ **Interface melhorada** para mostrar todos os dispositivos encontrados
- ✅ **Destaque visual** para dispositivos conhecidos (Raspberry Pi)
- ✅ **Vibração configurável** para qualquer dispositivo detectado
- ✅ **Códigos de erro corrigidos** e compatibilidade de API

### **🍓 Raspberry Pi Scripts**
- ✅ **Script avançado** que testa múltiplos nomes de dispositivos
- ✅ **Nomes variados**: SmartAssebility, SmartAsb, Raspberry, raspberrypi, RPi-BLE, BLE-Device
- ✅ **Detecção automática** de problemas e soluções
- ✅ **Melhor compatibilidade** com diferentes versões de Bluetooth

## 🚀 Como Usar (Versão Atualizada)

### **1. 📱 Galaxy Watch5 - Preparação**

1. **Instalar o app** no Galaxy Watch5
2. **Conceder todas as permissões** (Bluetooth, Localização)
3. **Ficar próximo** da Raspberry Pi (< 5 metros)

### **2. 🍓 Raspberry Pi - Executar Script Melhorado**

```bash
# Navegue até o diretório
cd raspCode/assesible_watch

# Execute o script melhorado (RECOMENDADO)
python3 simple_test.py
```

**O que o script faz agora:**
- ✅ Testa **6 nomes diferentes** sequencialmente
- ✅ Cada nome fica ativo por **15 segundos**
- ✅ **Detecta problemas** automaticamente
- ✅ **Instruções claras** de quando procurar no watch

### **3. 🔍 No Galaxy Watch5 - Buscar Dispositivos**

1. **Abrir app** SmartAssebility
2. **Tocar no botão 🔍** para iniciar busca
3. **Aguardar** - agora mostra **TODOS** os dispositivos
4. **Procurar** por qualquer um destes nomes:
   - `SmartAssebility`
   - `SmartAsb` 
   - `Raspberry`
   - `raspberrypi`
   - `RPi-BLE`
   - `BLE-Device`

### **4. ✅ Resultado Esperado**

- **📱 Lista completa** de dispositivos BLE próximos
- **🎯 Destaque verde** para dispositivos reconhecidos
- **📱 Ícone neutro** para outros dispositivos
- **📊 Informações** de sinal (dBm) e endereço MAC

## 🔧 Solução de Problemas (Atualizada)

### **❌ Galaxy Watch5 não detecta nada**

**Soluções em ordem de prioridade:**

1. **Verificar permissões**:
   ```
   - Bluetooth ✅
   - Localização ✅ 
   - Armazenamento ✅
   ```

2. **Teste com app externo**:
   - Instalar **nRF Connect** no telefone
   - Usar para confirmar que a Raspberry está transmitindo

3. **Raspberry Pi - script diagnóstico**:
   ```bash
   # Script simples e confiável
   python3 simple_test.py
   
   # Script com mais detalhes
   python3 test_visibility.py
   ```

4. **Distância e ambiente**:
   - Ficar **< 3 metros** da Raspberry
   - Evitar **interferência Wi-Fi**
   - Testar em **ambiente aberto**

### **🔧 Comandos de Debug (Raspberry Pi)**

```bash
# Status do Bluetooth
sudo systemctl status bluetooth
sudo hciconfig

# Reiniciar stack completo
sudo systemctl restart bluetooth
sudo hciconfig hci0 down
sudo hciconfig hci0 up

# Monitor em tempo real
sudo hcidump -i hci0
sudo btmon

# Verificar se está advertising
sudo hciconfig hci0 | grep ADVERTISE
```

## 📋 Tecnologias e Compatibilidade

### **📱 Android/Wear OS**
- **API Level**: 30+ (Android 11+)
- **Permissões**: Condicionais por versão do Android
- **Bluetooth**: BLE com fallback para versões antigas
- **Interface**: Jetpack Compose + Wear OS Material

### **🍓 Raspberry Pi**
- **OS**: Raspberry Pi OS (Bullseye ou Bookworm)
- **Python**: 3.7+
- **Dependências**: `bluezero`, `RPi.GPIO`
- **Hardware**: HC-SR04, Raspberry Pi 3/4

### **📡 Comunicação**
- **Protocolo**: Bluetooth Low Energy (BLE)
- **Alcance**: ~10 metros (ideal < 5m)
- **Frequência**: 2.4 GHz (evitar interferência Wi-Fi)

## 🧪 Scripts Disponíveis

| Script | Descrição | Quando Usar |
|--------|-----------|-------------|
| `simple_test.py` | **Teste múltiplos nomes** (RECOMENDADO) | Primeiro teste, problemas de detecção |
| `test_visibility.py` | Teste completo com diagnóstico | Debug avançado |
| `basic_advertiser.py` | Servidor BLE com sensor | Uso em produção |
| `check_bluetooth.sh` | Verificação do sistema | Problemas de configuração |

## 🎯 Status das Funcionalidades

| Funcionalidade | Status | Observações |
|----------------|--------|-------------|
| 📱 **App Wear OS** | ✅ **Funcionando** | Detecta todos os dispositivos BLE |
| 🍓 **BLE Advertising** | ✅ **Funcionando** | Múltiplos nomes testados |
| 📊 **Sensor HC-SR04** | ✅ **Funcionando** | Medições de distância |
| 🔗 **Comunicação BLE** | ✅ **Funcionando** | Conexão estabelecida |
| 📱 **Interface Visual** | ✅ **Melhorada** | Lista todos os dispositivos |
| ⚙️ **Compatibilidade** | ✅ **Expandida** | Android 11, 12, 13+ |

## 🔄 Próximos Passos

- [ ] Implementar **conexão automática** com dispositivo detectado
- [ ] Adicionar **configurações** no app (filtros, sensibilidade)
- [ ] Melhorar **feedback visual** e sonoro
- [ ] Implementar **logging** e **métricas** de uso
- [ ] Adicionar **modo de calibração** do sensor

## 💡 Dicas de Uso

1. **Primeira vez**: Use sempre `python3 simple_test.py`
2. **Problemas de detecção**: Ficar muito próximo (< 2 metros)
3. **Interferência**: Desligar Wi-Fi 2.4GHz temporariamente
4. **Debug**: Usar `nRF Connect` para confirmar transmissão
5. **Produção**: Usar `basic_advertiser.py` com sensor

---

**🔗 Links Úteis:**
- [Debug Guide](raspCode/assesible_watch/DEBUG.md)
- [Galaxy Watch5 Setup](https://developer.samsung.com/galaxy-watch)
- [Raspberry Pi BLE](https://learn.adafruit.com/intro-to-bluetooth-low-energy)

*Desenvolvido com ❤️ para tornar a tecnologia mais acessível* 