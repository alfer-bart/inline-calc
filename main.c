#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NUM_LEN 31

static double ANS = 0;

static double calc(const char* expr, const int length, int* trail) {
    double num[length];
    char opr[length];
    char dec[MAX_NUM_LEN + 1];
    int numCount = 0;
    int decCount = 0;
    int skip = 0;
    int lastNum = 0;
    int minus = 0;
    int root = 0;
    int i;
    char c;
    double result;

    for (i = 0; i < length; i++, expr++) {
        c = *expr;
        // Read a sequence of decimal characters
        if ((c >= '0' && c <= '9') || c == '.') {
            if (decCount >= MAX_NUM_LEN) {
                printf("Number length must not exceed %d!\n", MAX_NUM_LEN);
                return 0;
            }
            dec[decCount++] = c;
            continue;
        }
        // Decimal sequence has ended
        if (decCount) {
            dec[decCount] = '\0';
            result = atof(dec);
            if (root) {
                result = sqrt(result);
                root = 0;
            }
            if (minus) {
                result = -result;
                minus = 0;
            }
            num[numCount++] = result;
            lastNum = 1;
            decCount = 0;
        }
        switch (c) {
        case '*':
        case '/':
        case '^':
            if (lastNum != 1) {
                printf("Incorrect order of operations!\n");
                return 0;
            }
            goto assign_operator;
        case '-':
            // XOR negates an even number of minus signs
            minus ^= 1;
        case '+':
            if (lastNum == 2) {
                // Don't let subsequent + or - overwrite * or /
                continue;
            }
        assign_operator:
            opr[numCount] = c;
            lastNum = 2;
            continue;
        case 'r':
            if (lastNum == 1 || root) {
                printf("Root sign must be placed right before a number!\n");
                return 0;
            }
            root = 1;
            continue;
        case 'p':
            result = 3.14159265358979323846;
            goto assign_number;
        case 'e':
            result = 2.71828182845904523536;
            goto assign_number;
        case 'x':
            result = ANS;
        case '(':
        assign_number:
            if (lastNum == 1) {
                printf("Incorrect operation!\n");
                return 0;
            }
            if (c == '(') {
                // Calculate expression in parentheses first
                result = calc(expr + 1, length - i, &skip);
                expr += skip;
                i += skip;
            }
            if (root) {
                result = sqrt(result);
                root = 0;
            }
            if (minus) {
                result = -result;
                minus = 0;
            }
            num[numCount++] = result;
            lastNum = 1;
            continue;
        case ')':
        case '\n':
            break;
        case ' ':
            continue;
        default:
            printf("Unrecognized character!\n");
            return 0;
        }
        break;
    }

    if (!numCount) {
        printf("Nothing to calculate!\n");
        return 0;
    }

    *trail = i + 1;
    result = 0;

    for (i = 1; i < numCount; i++) {
        if (opr[i] == '^') {
            num[i-1] = pow(num[i-1], num[i]);
        }
    }
    for (i = 1; i < numCount; i++) {
        switch (opr[i]) {
        // Addition and subtraction is treated the same: a minus sign turns the right-hand part negative
        case '+':
        case '-':
            // Add the left-hand part to the result
            result += num[i-1];
            break;
        case '*':
            // Store mult/div result in the right-hand part
            num[i] = num[i-1] * num[i];
            break;
        case '/':
            num[i] = num[i-1] / num[i];
            break;
        case '^':
            // Shift power result to the right
            num[i] = num[i-1];
            break;
        default:
            printf("Invalid operator!\n");
            return 0;
        }
    }
    result += num[numCount - 1];
    return result;
}

int main() {
    char expr[2048];
    int skip;

    while (1) {
        fgets(expr, sizeof(expr), stdin);
        if (expr[0] == 'q') {
            break;
        }
        ANS = calc(expr, strlen(expr), &skip);
        printf("%lf\n", ANS);
    }
	return 0;
}

/* TODO
    - factorial
    - lg, ln
    - sin, cos, tan
    - deg/rad toggle
*/
