# Cambiándose de Aula

## Descripción del Problema

Tu facultad es una grilla de aulas cuadradas de dimensiones \(n \times m\). Debés moverte desde el aula ubicada en la esquina superior izquierda hasta el aula en la esquina inferior derecha del mapa, recorriendo la menor cantidad posible de aulas.

Cada aula puede ser fría (-1) o caliente (1). Para mantenerte en equilibrio térmico, debés pasar por exactamente la misma cantidad de aulas frías que calientes durante tu recorrido. Tenés que determinar si es posible cumplir con esta condición.

## Ejemplo Visual

A continuación se muestra un ejemplo de una grilla con aulas frías (blancas) y calientes (rojas):

```
 1  -1  -1  -1
-1   1   1  -1
 1   1   1  -1
```

## Formato de Entrada

La primera línea contiene un número entero \(t\), el número de casos de prueba.

Para cada caso de prueba:

- Una línea con dos enteros \(n\) y \(m\), que indican las dimensiones de la grilla.
- Siguen \(n\) líneas con \(m\) enteros cada una, indicando si el aula es fría (-1) o caliente (1).

## Formato de Salida

Para cada caso de prueba, imprimir "YES" si es posible realizar el recorrido solicitado, o "NO" si no lo es.

## Ejemplo de Entrada y Salida

### Entrada:

```
2
3 4
1 -1 -1 -1
-1 1 1 -1
1 1 1 -1
1 2
1 1
```

### Salida:

```
YES
NO
```

*Nota: El primer caso de prueba corresponde al ejemplo visual mostrado previamente.*

