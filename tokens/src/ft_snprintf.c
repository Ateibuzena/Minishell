#include "../tokensft.h"

void ft_snprintf(char *result, size_t length, const char *str1, const char *str2)
{
	size_t len1;
	size_t len2;
	size_t total_length;

    len1 = ft_strlen(str1);  // Longitud de la primera cadena
    len2 = ft_strlen(str2);  // Longitud de la segunda cadena
    total_length = len1 + len2 + 1;  // Total de caracteres a copiar (+1 para el espacio)

    if (total_length >= length) // Si la longitud total excede el tamaño del buffer, ajustamos la longitud total.
        total_length = length - 1;

    // Copiar la primera cadena en result
    ft_strcpy(result, str1);
    // Añadir un espacio entre las cadenas
    if (total_length > len1)
        ft_strcat(result, " ");

    // Copiar la segunda cadena
    if (total_length > len1 + 1)
        ft_strcat(result, str2);

    // Aseguramos que el string terminado tenga el carácter nulo '\0' al final
    result[total_length] = '\0';
}

/*
### Explicación de `ft_snprintf`

1. **Cálculo de la longitud total**:
   - Se calcula la longitud de las dos cadenas `str1` y `str2`, más un carácter adicional para el espacio que va entre ellas. Esto da como resultado la longitud total que debe tener la cadena resultante.

2. **Comprobación del espacio disponible**:
   - Si la longitud total de la cadena resultante supera la capacidad del buffer (`length`), se ajusta para que no se desborde, dejando espacio para el carácter nulo de terminación `'\0'`.

3. **Copiar las cadenas**:
   - Primero, se copia `str1` en `result`.
   - Luego, se añade un espacio entre las dos cadenas si el espacio lo permite.
   - Después se concatena `str2` al resultado.

4. **Terminación de la cadena**:
   - Finalmente, se asegura que `result` termine con el carácter nulo `'\0'`.

### ¿Por qué usamos `ft_snprintf` en `ft_split_command`?

En la función `ft_split_command`, utilizamos `ft_snprintf` para concatenar dos cadenas (`input[i]` y `input[i + 1]`) con un espacio entre ellas. Esto es útil cuando tenemos que procesar comandos con múltiples argumentos que deben ir juntos como un solo token. Al usar `ft_snprintf`, garantizamos que las cadenas se concatenen correctamente en un buffer controlado y evitamos el desbordamiento de memoria, ya que gestionamos el espacio disponible en el buffer.
*/