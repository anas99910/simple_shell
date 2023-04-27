#include "main.h"

void printCharBuffer(char buffer[], int *bufferIndex);

/**
 * my_printf - Custom printf function
 * @format: format string
 * Return: number of printed characters
 */
int my_printf(const char *format, ...)
{
    int i, printed = 0, printedChars = 0;
    int flags, width, precision, size, bufferIndex = 0;
    va_list args;
    char charBuffer[BUFF_SIZE];

    if (format == NULL)
        return (-1);

    va_start(args, format);

    for (i = 0; format && format[i] != '\0'; i++)
    {
        if (format[i] != '%')
        {
            charBuffer[bufferIndex++] = format[i];
            if (bufferIndex == BUFF_SIZE)
                printCharBuffer(charBuffer, &bufferIndex);
            printedChars++;
        }
        else
        {
            printCharBuffer(charBuffer, &bufferIndex);
            flags = getFlags(format, &i);
            width = getWidth(format, &i, args);
            precision = getPrecision(format, &i, args);
            size = getSize(format, &i);
            ++i;
            printed = handlePrint(format, &i, args, charBuffer,
                flags, width, precision, size);
            if (printed == -1)
                return (-1);
            printedChars += printed;
        }
    }

    printCharBuffer(charBuffer, &bufferIndex);

    va_end(args);

    return (printedChars);
}

/**
 * printCharBuffer - Prints the contents of the buffer if it exists
 * @buffer: character array
 * @bufferIndex: pointer to buffer length
 */
void printCharBuffer(char buffer[], int *bufferIndex)
{
    if (*bufferIndex > 0)
        write(1, &buffer[0], *bufferIndex);

    *bufferIndex = 0;
}
