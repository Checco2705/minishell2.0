# 🐚 Minishell - A Beautiful Unix Shell

<div align="center">

[![42 School](https://img.shields.io/badge/42-School-000000?style=for-the-badge&logo=42&logoColor=white)](https://42.fr)
[![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Norminette](https://img.shields.io/badge/Norminette-Passed-success?style=for-the-badge)](https://github.com/42School/norminette)
[![Memory Leaks](https://img.shields.io/badge/Memory%20Leaks-0-brightgreen?style=for-the-badge)](https://valgrind.org/)

*Un'implementazione completa di una shell Unix in C*

</div>

---

## 📖 Descrizione

**Minishell** è un progetto della 42 School che ricrea le funzionalità principali di una shell Unix (come Bash). Il progetto mira a fornire una comprensione approfondita dei processi di sistema, della gestione della memoria e dell'architettura delle shell.

### 🎯 Obiettivi Raggiunti
- ✅ **Zero Memory Leaks** - Gestione perfetta della memoria
- ✅ **Parsing Completo** - Gestione di quote, variabili e operatori
- ✅ **Esecuzione Robusta** - Supporto per pipe, redirezioni e built-in
- ✅ **Gestione Segnali** - Comportamento identico a Bash
- ✅ **Norminette Compliant** - Codice conforme agli standard 42

---

## ✨ Funzionalità

### 🔧 Comandi Built-in
| Comando | Descrizione | Opzioni Supportate |
|---------|-------------|-------------------|
| `echo` | Stampa testo | `-n` (no newline) |
| `cd` | Cambia directory | `~`, `-`, percorsi relativi/assoluti |
| `pwd` | Stampa directory corrente | Nessuna |
| `export` | Esporta variabili d'ambiente | Visualizzazione e assegnazione |
| `unset` | Rimuove variabili d'ambiente | Validazione identificatori |
| `env` | Mostra variabili d'ambiente | Filtraggio automatico |
| `exit` | Esce dalla shell | Codici di uscita numerici |

### 🔄 Redirezioni
```bash
# Input redirection
command < file

# Output redirection  
command > file

# Append redirection
command >> file

# Heredoc
command << delimiter
```

### 🔗 Pipe e Operatori
```bash
# Pipe semplice
command1 | command2

# Pipe multiple
command1 | command2 | command3

# Combinazione con redirezioni
command1 < input.txt | command2 > output.txt
```

### 💾 Gestione Variabili
```bash
# Espansione variabili
echo $HOME
echo $USER

# Exit status
echo $?

# Variabili personalizzate
export MY_VAR="hello"
echo $MY_VAR
```

### 🎭 Gestione Quote
```bash
# Quote singole (letterali)
echo 'Hello $USER'  # Output: Hello $USER

# Quote doppie (con espansione)
echo "Hello $USER"  # Output: Hello username

# Quote miste
echo 'Hello' "$USER"
```

---

## 🚀 Installazione e Utilizzo

### Prerequisiti
```bash
# Ubuntu/Debian
sudo apt-get install libreadline-dev

# macOS (con Homebrew)
brew install readline
```

### Compilazione
```bash
# Clona il repository
git clone [repository-url]
cd minishell

# Compila il progetto
make

# Esegui la shell
./minishell
```

### Esempi d'Uso
```bash
minishell$ echo "Benvenuto in Minishell!"
Benvenuto in Minishell!

minishell$ ls -la | grep minishell
-rwxr-xr-x 1 user user 45678 Dec 15 10:30 minishell

minishell$ export GREETING="Ciao"
minishell$ echo "$GREETING mondo!"
Ciao mondo!

minishell$ cat << EOF > test.txt
> Questo è un test
> di heredoc
> EOF
minishell$ cat test.txt
Questo è un test
di heredoc
```

---

## 🏗️ Architettura

### 📁 Struttura del Progetto
```
minishell/
├── src/
│   ├── main.c              # Entry point e loop principale
│   ├── signals.c           # Gestione segnali
│   ├── execute_child.c     # Esecuzione processi
│   ├── pars/              # Modulo parsing
│   │   ├── parser.c       # Parser principale
│   │   ├── tokenizer.c    # Tokenizzazione
│   │   ├── quotes.c       # Gestione quote
│   │   ├── variables.c    # Espansione variabili
│   │   └── ...
│   ├── blts/              # Built-in commands
│   │   ├── echo.c
│   │   ├── cd.c
│   │   ├── pwd.c
│   │   └── ...
│   └── exec/              # Modulo esecuzione
├── include/
│   └── minishell.h        # Header principale
├── libft/                 # Libreria personalizzata
├── printf/                # Printf personalizzato
└── Makefile
```

### 🔄 Flusso di Esecuzione
1. **Input** → Lettura comando con `readline()`
2. **Tokenizzazione** → Suddivisione in token
3. **Parsing** → Analisi sintattica e costruzione AST
4. **Espansione** → Risoluzione variabili e quote
5. **Esecuzione** → Fork/exec o built-in
6. **Cleanup** → Liberazione memoria

---

## 📚 Funzioni Readline Consentite

### 🔧 Funzioni Principali

#### `readline(const char *prompt)`
```c
char *readline(const char *prompt);
```
- **Scopo**: Legge una riga di input dall'utente con supporto per editing
- **Parametri**: `prompt` - stringa da visualizzare come prompt
- **Ritorno**: Stringa allocata dinamicamente (deve essere liberata con `free()`)
- **Utilizzo**: Funzione principale per l'input interattivo

**Esempio:**
```c
char *line = readline("minishell$ ");
if (line)
{
    // Processa il comando
    free(line);
}
```

#### `add_history(const char *line)`
```c
void add_history(const char *line);
```
- **Scopo**: Aggiunge una riga alla cronologia dei comandi
- **Parametri**: `line` - comando da aggiungere alla cronologia
- **Utilizzo**: Permette navigazione con frecce ↑/↓

**Esempio:**
```c
char *line = readline("minishell$ ");
if (line && *line)
{
    add_history(line);
    // Processa comando...
}
```

### 🧹 Funzioni di Gestione Cronologia

#### `rl_clear_history(void)`
```c
void rl_clear_history(void);
```
- **Scopo**: Cancella completamente la cronologia readline
- **Utilizzo**: Pulizia memoria alla chiusura della shell
- **Differenza**: Libera anche i dati privati di readline (vs `clear_history()`)

#### `rl_on_new_line(void)`
```c
int rl_on_new_line(void);
```
- **Scopo**: Informa readline che il cursore è su una nuova riga
- **Utilizzo**: Necessario dopo output di programmi esterni
- **Ritorno**: Sempre 0

### 🎨 Funzioni di Display

#### `rl_replace_line(const char *text, int clear_undo)`
```c
void rl_replace_line(const char *text, int clear_undo);
```
- **Scopo**: Sostituisce il contenuto del buffer di readline
- **Parametri**: 
  - `text` - nuovo testo da visualizzare
  - `clear_undo` - se non-zero, cancella la cronologia undo
- **Utilizzo**: Manipolazione programmatica del buffer

#### `rl_redisplay(void)`
```c
void rl_redisplay(void);
```
- **Scopo**: Aggiorna il display per riflettere il contenuto corrente del buffer
- **Utilizzo**: Necessario dopo modifiche programmatiche al buffer

### 🔧 Variabili Readline Utilizzate

#### `rl_done`
```c
extern int rl_done;
```
- **Scopo**: Forza readline a terminare e restituire la riga corrente
- **Utilizzo**: Gestione segnali personalizzata

#### `rl_event_hook`
```c
extern rl_hook_func_t *rl_event_hook;
```
- **Scopo**: Funzione chiamata periodicamente durante l'attesa input
- **Utilizzo**: Controllo segnali asincroni

#### `rl_catch_signals`
```c
extern int rl_catch_signals;
```
- **Scopo**: Controlla se readline gestisce automaticamente i segnali
- **Default**: 1 (attivo)
- **Utilizzo**: Disabilitato per gestione segnali personalizzata

### 📝 Esempio di Implementazione

```c
#include <readline/readline.h>
#include <readline/history.h>

void setup_readline(void)
{
    rl_catch_signals = 0;  // Disabilita gestione automatica segnali
    rl_event_hook = check_signals;  // Funzione controllo segnali
}

char *get_user_input(void)
{
    char *line;
    
    line = readline("minishell$ ");
    if (line && *line)
        add_history(line);
    
    return (line);
}

void cleanup_readline(void)
{
    rl_clear_history();
    rl_on_new_line();
}
```

### ⚠️ Considerazioni Importanti

1. **Memory Management**: Tutte le stringhe restituite da `readline()` devono essere liberate
2. **Signal Handling**: Disabilitare `rl_catch_signals` per gestione personalizzata
3. **History Management**: Aggiungere solo comandi non vuoti alla cronologia
4. **Display Updates**: Usare `rl_redisplay()` dopo modifiche programmatiche

### 🔗 Compilazione con Readline

```bash
# Flags di compilazione necessari
gcc -lreadline -L/usr/local/lib -I/usr/local/include

# Su macOS con Homebrew
gcc -lreadline -L$(brew --prefix readline)/lib -I$(brew --prefix readline)/include
```

---

## �� Testing e Qualità

### 📊 Memory Leak Analysis
```bash
valgrind --leak-check=full --show-leak-kinds=all ./minishell
```

**Risultati:**
- ✅ **definitely lost**: 0 bytes
- ✅ **indirectly lost**: 0 bytes  
- ✅ **possibly lost**: 0 bytes
- ⚠️ **still reachable**: 232,796 bytes (solo librerie di sistema)

### 🎯 Compatibilità
- ✅ **Linux** (Ubuntu, Debian, Fedora)
- ✅ **macOS** (con Homebrew)
- ✅ **Comportamento identico a Bash** per le funzionalità implementate

---

## 🤝 Sviluppo

### 👥 Team
- **Parsing & Built-ins**: Gestione input, tokenizzazione, comandi interni
- **Execution & Signals**: Processi, pipe, redirezioni, segnali

### 🛠️ Strumenti Utilizzati
- **Valgrind** - Memory leak detection
- **GDB** - Debugging
- **Norminette** - Code style checking
- **Git** - Version control

---

## 📝 Note Tecniche

### 🔍 Dettagli Implementazione
- **Parser ricorsivo discendente** per l'analisi sintattica
- **Gestione avanzata dei file descriptor** per pipe e redirezioni
- **Sistema di tokenizzazione robusto** con supporto per quote annidate
- **Gestione segnali conforme POSIX** 
- **Environment management personalizzato**

### ⚡ Performance
- Ottimizzato per **velocità di parsing**
- **Memoria efficiente** con cleanup automatico
- **Gestione errori robusta** senza crash

---

## 🎓 Cosa Ho Imparato

- **Programmazione di sistema** in C
- **Gestione processi** (fork, exec, wait)
- **File descriptor** e I/O redirection
- **Parsing** e costruzione di AST
- **Gestione memoria** avanzata
- **Debugging** con Valgrind e GDB
- **Architettura software** modulare

---

<div align="center">

**🎉 Progetto completato con successo! 🎉**

*Realizzato con ❤️ per la 42 School*

</div>
