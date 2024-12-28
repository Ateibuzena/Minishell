# La Minishell

La Minishell es uno de los proyectos más populares en 42 y tiene como objetivo que los estudiantes desarrollen una réplica simplificada de un shell de Unix, como Bash o Zsh. Es un proyecto desafiante porque te introduce a conceptos importantes relacionados con sistemas operativos, programación en C y procesos. Aquí tienes una visión general de lo que implica:

## Objetivos principales

### Entender el funcionamiento de un shell:
- Cómo procesa comandos y argumentos.
- Cómo interactúa con el sistema operativo para ejecutar programas.

### Trabajar con procesos y señales:
- Crear procesos hijo usando `fork()`.
- Controlar señales como `SIGINT`, `SIGQUIT`, etc.

### Gestión de tuberías y redirecciones:
- Implementar la funcionalidad de `|` (pipes) para conectar la salida de un comando con la entrada de otro.
- Manejar redirecciones como `>`, `>>`, y `<`.

### Crear un entorno interactivo:
- Mostrar un prompt personalizado.
- Esperar comandos del usuario en un bucle.

## Requisitos básicos

La versión inicial de la minishell debe:
- Ejecutar comandos del sistema como `ls`, `echo`, o `grep`.
- Soportar argumentos y rutas relativas/absolutas.
- Implementar las redirecciones (`>`, `<`, `>>`) y las tuberías (`|`).
- Manejar el entorno del sistema (`env`, `export`, `unset`, etc.).
- Tener un buen manejo de errores (sin crashes).
- Procesar comandos simples como `cd`, `pwd`, `exit`, y `env`.

## Herramientas y funciones clave

En este proyecto solo puedes usar funciones permitidas. Algunas de las más importantes son:
- `readline()`: Para capturar la entrada del usuario.
- `fork()`: Para crear procesos hijo.
- `execve()`: Para reemplazar el proceso actual con uno nuevo (ejecutar comandos).
- `pipe()`: Para conectar procesos con tuberías.
- `dup2()`: Para redirigir la entrada y salida estándar.
- `waitpid()`: Para esperar que los procesos hijo terminen.
- `signal()`: Para manejar señales como interrupciones (Ctrl+C).

## Bonus (Opcional)

Si decides hacer el bonus, puedes añadir funcionalidades avanzadas como:
- Soporte para operadores lógicos (`&&`, `||`).
- Subshells usando paréntesis `()` para agrupar comandos.
- Expansión de comodines (`*`, `?`) para rutas de archivos.
- Soporte para variables como `$USER`, `$?`, etc.

## Consejos para abordarlo

1. **Divide el proyecto en partes**:
   - Comienza por leer la entrada del usuario (`readline()`).
   - Implementa un parser para separar comandos y argumentos.
   - Añade las funcionalidades básicas como ejecución de comandos simples.

2. **Prueba constantemente**:
   - Usa pequeños programas para probar conceptos como `fork`, `pipe` o `execve` antes de integrarlos.

3. **Manejo de errores**:
   - Asegúrate de manejar casos como rutas inexistentes o redirecciones inválidas sin que el programa se rompa.

4. **Lee la documentación**:
   - Familiarízate con las funciones del sistema que vayas a usar.

# Guía paso a paso para empezar la Minishell

¡Empezar un proyecto como la Minishell puede parecer abrumador al principio, pero con un enfoque organizado será mucho más manejable! Aquí tienes una guía paso a paso para iniciar:

## 1. Estudia los fundamentos

Antes de escribir código, asegúrate de entender cómo funcionan los componentes básicos que usarás:

- **Procesos**: Aprende cómo funcionan `fork()` y `execve()`.
- **Redirecciones**: Entiende cómo redirigir entrada/salida con `dup2()`.
- **Tuberías**: Investiga cómo usar `pipe()` para conectar procesos.
- **Señales**: Familiarízate con `signal()` o `sigaction()` para manejar interrupciones.

💡 **Consejo**: Crea programas pequeños para probar cada concepto antes de integrarlos.

---

## 2. Estructura el proyecto

Piensa en cómo vas a organizar el código desde el principio. Aquí tienes una posible estructura:

- `main.c`: Contendrá el bucle principal del shell.
- `parser.c`: Procesará la entrada del usuario.
- `executor.c`: Ejecutará los comandos usando `fork()` y `execve()`.
- `builtin.c`: Implementará comandos internos como `cd`, `pwd`, etc.
- `signals.c`: Manejará las señales (Ctrl+C, Ctrl+\).
- `redirections.c`: Implementará redirecciones y tuberías.
- `env.c`: Gestionará variables de entorno.

💡 **Consejo**: Usa un archivo `.h` para declarar funciones y estructuras compartidas.

---

## 3. Define un plan mínimo viable

Empieza por lo básico y agrega funcionalidades progresivamente. Aquí tienes un orden sugerido:

### Fase 1: Lo esencial

#### Bucle principal:
- Imprime un prompt.
- Lee comandos usando `readline()`.
- Muestra el texto que escribió el usuario para probar.

#### Ejecuta comandos simples:
- Usa `fork()` y `execve()` para ejecutar comandos externos (`ls`, `echo`, etc.).

#### Implementa builtins básicos:
- **`cd`**: Cambiar directorio.
- **`pwd`**: Mostrar el directorio actual.
- **`exit`**: Salir del shell.

---

### Fase 2: Funcionalidades avanzadas

#### Parser avanzado:
- Divide el comando en tokens.
- Identifica redirecciones (`>`, `<`, `>>`) y tuberías (`|`).

#### Tuberías:
- Usa `pipe()` para conectar procesos.
- **Ejemplo**: `ls | grep txt`.

#### Redirecciones:
- Implementa `>`, `>>` y `<` con `dup2()`.
- **Ejemplo**: `ls > output.txt`.

#### Manejo de señales:
- Ignora Ctrl+C en el shell principal pero permite interrumpir procesos hijo.

---

### Fase 3: Bonus y optimización

#### Soporte para variables:
- Implementa `$PATH`, `$USER`, `$?`, etc.

#### Expansiones avanzadas:
- Expande variables como `$HOME`.
- Soporte para comodines (`*`, `?`).

#### Errores robustos:
- Maneja errores de forma clara sin que el shell se rompa.
