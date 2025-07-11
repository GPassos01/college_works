#MIPS_Monocycle
# 🧠 Processador MIPS Monociclo em VHDL

Este projeto implementa um **processador MIPS monociclo** desenvolvido em **VHDL** utilizando o ambiente **Quartus II 13.0sp1**. O projeto tem como objetivo estudar e simular o funcionamento interno de uma CPU baseada na arquitetura MIPS.

## 🛠️ Tecnologias utilizadas

- Quartus II 13.0sp1
- VHDL
- ModelSim-Altera (para simulações)

## 📚 Componentes implementados

O processador foi desenvolvido de forma modular, incluindo:

- **ALU** (`ULA.vhd`)
- **Banco de Registradores** (`register_file.vhd`)
- **Extensor de Sinal** (`sign_extend.vhd`)
- **Memória de Instruções** (`instruction_memory.vhd`)
- **Memória de Dados** (`data_memory.vhd`)
- **Decodificadores de Controle** (`control_unit.vhd`, `main_decoder.vhd`, `ALU_decoder.vhd`)
- **Somador de PC** (`somador.vhd`)
- **Contador de Programa (PC)** (`program_counter.vhd`)
- **MUXes** (`mux5.vhd`, `mux32.vhd`)
- **Shift left** (`sll2.vhd`, `sll2_j.vhd`)
- **Top-level** (`MIPSGMN.bdf`)

## 📃 Instruções MIPS implementadas

Esse processador é capaz de executar:

- Instruções do tipo **R**: `add`, `sub`, `and`, `or`, `slt`
- Instruções do tipo **I**: `lw`, `sw`, `beq`, `addi`
- Instrução do tipo **J**: `j`

## 🧪 Simulação

Foram feitas em Waveform, analisando ciclo a ciclo do processador com outputs eu lugares estratégicos para verificação como:

- Saida da ULA
- Saidas da memoria de registradores
- Algumas saidas da unidade de controle
- Entre outros

As simulações foram realizadas no ModelSim-Altera integrado ao Quartus.

## 🚀 Como executar

- Abra o Quartus II 13.0sp1
- Abra o projeto (MIPSGMN.qpf)
- Compile o projeto
- Simule o comportamento usando os arquivos .vwf disponíveis (File > New > University Program VWF, na nova janela: File > Open > Waveform3.vwf. Rode a simulação)

## 📜 Observações

As instruções foram escritas manualmente no codigo VHDL da memoria de instruções (inst_memory) em assembly convertido para hexadecimal.

![image](https://github.com/user-attachments/assets/22115069-7e14-45d6-b6ed-56c75c625dbd)

## 🎓 Sobre

Projeto acadêmico desenvolvido na disciplina de Laboratório de Projetos Digitais do curso de Ciência da Computação, seguindo o capitulo 7 do livro: "Projeto Digital e Arquitetura de Computadores" por David Money Harris & Sarah L. Harris.

## 📩 Contato

Desenvolvido por Gabriel Passos
GitHub: @GPassos01
