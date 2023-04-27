#include "main.h"

/************************* PRINT CHAR *************************/

/**
 * printChar - Prints a char
 * @args: list of arguments
 * @charBuffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int printChar(va_list args, char charBuffer[],
    int flags, int width, int precision, int size)
{
    char c = va_arg(args, int);

    return (handleWriteChar(c, charBuffer, flags, width, precision, size));
}

/************************* PRINT A STRING *************************/
/**
 * printString - Prints a string
 * @args: list of arguments
 * @charBuffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int printString(va_list args, char charBuffer[],
    int flags, int width, int precision, int size)
{
    int length = 0, i;
    char *str = va_arg(args, char *);

    UNUSED(charBuffer);
    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);
    if (str == NULL)
    {
        str = "(null)";
        if (precision >= 6)
            str = "      ";
    }

    while (str[length] != '\0')
        length++;

    if (precision >= 0 && precision < length)
        length = precision;

    if (width > length)
    {
        if (flags & F_MINUS)
        {
            write(1, &str[0], length);
            for (i = width - length; i > 0; i--)
                write(1, " ", 1);
            return (width);
        }
        else
        {
            for (i = width - length; i > 0; i--)
                write(1, " ", 1);
            write(1, &str[0], length);
            return (width);
        }
    }

    return (write(1, str, length));
}

/************************* PRINT PERCENT SIGN *************************/
/**
 * printPercent - Prints a percent sign
 * @args: list of arguments
 * @charBuffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int printPercent(va_list args, char charBuffer[],
    int flags, int width, int precision, int size)
{
    UNUSED(args);
    UNUSED(charBuffer);
    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);
    return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/
/**
 * printInt - Print int
 * @args: list of arguments
 * @charBuffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int printInt(va_list args, char charBuffer[],
    int flags, int width, int precision, int size)
{
    int i = BUFF_SIZE - 2;
    int isNegative = 0;
    long int n = va_arg(args, long int);
    unsigned long int num;

    n = convertSizeNumber(n, size);

    if (n == 0)
        {
    charBuffer[i--] = '0';
}

charBuffer[BUFF_SIZE - 1] = '\0';
num = (unsigned long int)n;

if (n < 0)
{
    num = (unsigned long int)((-1) * n);
    isNegative = 1;
}

while (num > 0)
{
    charBuffer[i--] = (num % 10) + '0';
    num /= 10;
}

i++;

return (writeNumber(isNegative, i, charBuffer, flags, width, precision, size));
}

/************************* PRINT BINARY ***********************/
/

printBinary - Prints an unsigned number

@args: list of arguments

@charBuffer: Buffer array to handle print

@flags: Calculates active flags

@width: Width

@precision: Precision specification

@size: Size specifier

Return: Numbers of char printed.
*/
int printBinary(va_list args, char charBuffer[],
int flags, int width, int precision, int size)
{
unsigned int n, m, i, sum;
unsigned int a[32];
int count;

UNUSED(charBuffer);
UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);

n = va_arg(args, unsigned int);
m = 2147483648; /* (2 ^ 31) */
a[0] = n / m;
for (i = 1; i < 32; i++)
{
m /= 2;
a[i] = (n / m) % 2;
}
for (i = 0, sum = 0, count = 0; i < 32; i++)
{
sum += a[i];
if (sum || i == 31)
{
char z = '0' + a[i];
    write(1, &z, 1);
     count++;
 }
}
return (count);
}
