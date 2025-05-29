# 🐚 minishell

Una implementación simplificada de una shell al estilo bash, desarrollada en C como parte del currículo de 42 Málaga. Este proyecto incluye ejecución de comandos, manejo de señales, redirecciones, piping, expansión de variables, builtins personalizados, y más. Todo el código está organizado en módulos reutilizables y estructurados.

## 📁 Estructura del Proyecto

```bash
minishell/
├── builtins/         # Implementación de comandos internos (cd, echo, env...)
├── enviroment/       # Gestión de variables de entorno como lista enlazada
├── history/          # Manejador personalizado del historial (readline + almacenamiento)
├── libft/            # Funciones de utilidad estándar implementadas a mano
├── parser/           # Parser completo con normalización, expansión y validación
├── pipex/            # Ejecuta comandos y pipelines, gestiona duplicaciones y fds
├── prompt/           # Genera el prompt personalizado
├── signals/          # Manejador de señales (SIGINT, SIGQUIT...)
├── tokens/           # Tokenizador inicial
├── minishell.c       # Entrada principal y bucle de ejecución
├── Makefile
└── README.md
```

## 🧠 Conceptos Implementados
- Prompt interactivo usando readline

- Historia de comandos personalizada

- Parsing y tokenización con gestión de comillas, pipes y redirecciones

- Expansión de variables ($VAR, $?, ~)

- Builtins: cd, echo, env, exit, export, pwd, unset

- Redirecciones: <, >, >>, <<

- Pipelines (|) usando dup2 y fork

- Gestión de errores y señales

- Estructuras dinámicas para entornos y comandos

## 🔧 Compilación

```bash
make
./minishell
```

## 📚 Descripción de Módulos

### ✅ builtins/

Contiene la lógica de los comandos internos de la shell, como:

- ft_cd, ft_echo, ft_exit, ft_pwd, ft_env, ft_export, ft_unset

- Funciones auxiliares para expansión de rutas y tratamiento de argumentos

- ft_is_builtins y ft_execute_builtins para distinguir y ejecutar comandos internos

### 🌱 enviroment/

Implementa una lista enlazada (t_Env) para gestionar variables de entorno. Funciones clave:

- ft_copy_env, ft_add_env, ft_delete_key, ft_get_env

- Libre de fugas con ft_free_env

### 📜 history/

Extiende el sistema de historial de readline con una estructura propia t_History.

- Almacena, añade y muestra entradas

- ft_init_history, ft_add_entry, ft_show_history

### 🔄 parser/

Parser robusto que maneja:

- Expansión de variables ($, ~, $?)

- Manejo de comillas (', ")

- Validación de sintaxis (pipes, redirecciones)

- Normalización del input para facilitar el análisis posterior

### 🔧 pipex/

Corazón de la ejecución de comandos:

- Estructuras t_executor y t_command para modelar el pipeline

- Funciones para forkear, redirigir y ejecutar cada comando (builtin o externo)

- Manejo fino de dup2, fds temporales y restauración de stdins/stdouts

### 🚦 signals/

Captura y maneja señales como SIGINT y SIGQUIT para evitar que la shell se rompa con Ctrl+C o Ctrl+\.

### ⌨️ prompt/

Genera el prompt de entrada. Puedes personalizarlo para mostrar el cwd, el usuario o emojis 😄.

## 🧪 Ejemplos de Uso

```bash
minishell> echo "Hola Ana"
Hola Ana

minishell> cd ..
minishell> pwd
/home/ana

minishell> export USER=Ana
minishell> echo $USER
Ana

minishell> ls | grep minishell > resultado.txt
```

## ✅ Cosas que se cumplen del subject (norminette + funciones válidas)

- Sin funciones prohibidas

- Gestión de memoria correcta

- Modularidad y claridad en la estructura

- Adaptación al estilo de bash sin shell scripts

## 💬 Créditos

Desarrollado por Ana Zubieta como parte del proyecto de minishell en 42 Málaga, Fundación Telefónica.
