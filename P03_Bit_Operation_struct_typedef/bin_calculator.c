#include <stdlib.h>
#include <stdio.h>

#define OPERAND_BUFFER_SIZE 10

typedef struct {
    unsigned int operand1;
    unsigned int operand2;
    char operation;
} Expression;

int bits_per_int() {
    return sizeof(unsigned int) * 8;
}

unsigned int parse_operand(char operand_str[]) {
    unsigned int operand;
    if (operand_str[0] == '0' && operand_str[1] == 'x') {
        (void) sscanf(&operand_str[2], "%x", &operand);
    } else if (operand_str[0] == '0') {
        (void) sscanf(&operand_str[1], "%o", &operand);
    } else {
        (void) sscanf(operand_str, "%u", &operand);
    }
    return operand;
}

void print_binary(unsigned int value) {
    for (int i = bits_per_int() - 1; i >= 0; i--) {
        (void) printf("%d", (value >> i) & 1);
        if (i % 8 == 0 && i != 0) {
            (void) printf("'");
        }
    }
    (void) printf("\n");
}

void print_bit_operation_bin(Expression expression, unsigned int result) {
    print_binary(expression.operand1);
    (void) printf("%c ", expression.operation);
    print_binary(expression.operand2);
    (void) printf("-----------------------------------\n");
    print_binary(result);
    (void) printf("\n");
}

void print_bit_operation_hex(Expression expression, unsigned int result) {
    (void) printf("0x%x %c 0x%x = 0x%x\n", expression.operand1, expression.operation, expression.operand2, result);
}

void print_bit_operation_dec(Expression expression, unsigned int result) {
    (void) printf("%u %c %u = %u\n", expression.operand1, expression.operation, expression.operand2, result);
}

unsigned int bit_operation(Expression expression) {
    switch (expression.operation) {
        case '&': return expression.operand1 & expression.operand2;
        case '|': return expression.operand1 | expression.operand2;
        case '^': return expression.operand1 ^ expression.operand2;
        case '<': return expression.operand1 << expression.operand2;
        case '>': return expression.operand1 >> expression.operand2;
        default:
            (void) printf("Ungültige Operation!\n");
        exit(EXIT_FAILURE);
    }
}

int main(){
    char operand1_str[10];
    char operand2_str[10];
    char operation;

    unsigned int operand1, operand2;

    do {
        (void) printf("Geben sie die Bit-Operation ein:\n");

        scanf("%s %c %s", operand1_str, &operation, operand2_str);

        operand1 = parse_operand(operand1_str);
        operand2 = parse_operand(operand2_str);

        Expression expression = {operand1, operand2, operation};

        unsigned int result = bit_operation(expression);
        print_bit_operation_bin(expression, result);
        print_bit_operation_hex(expression, result);
        print_bit_operation_dec(expression, result);

        while(getchar() != '\n');
        (void) printf("\nMöchten sie weiter machen oder abbrechen? [(n)ext|(q)uit] ");

    } while(getchar() == 'n');

    (void) printf("Byebye..\n");
    return EXIT_SUCCESS;
}
