# Ref: http://andreinc.net/2010/10/05/converting-infix-to-rpn-shunting-yard-algorithm/

LEFT_ASSOC = 0
RIGHT_ASSOC = 1

operators = {
        '+': (0, LEFT_ASSOC),
        '-': (0, LEFT_ASSOC),
        '*' : (5, LEFT_ASSOC),
        '/' : (5, LEFT_ASSOC),
        '%' : (5, LEFT_ASSOC),
        '^' : (10, RIGHT_ASSOC)
        }

def isOperator(c):
    return c in operators.keys()

def isDigit(c):
    return '0' <= c <= '9'


def isAssociative(token, assoc):
    return token in operators and operators[token][1] == assoc

def cmpPrecedence(t1, t2):
    return operators[t1][0] - operators[t2][0]

class LexError(Exception):
    pass

class ParseError(Exception):
    pass

def lex(exp):
    i = 0
    tokens = []
    while i < len(exp):
        if isOperator(exp[i]):
            tokens.append(exp[i])
            i += 1
        elif isDigit(exp[i]):
            j = i+1
            while j < len(exp) and isDigit(exp[j]):
                j += 1
            tokens.append(int(exp[i:j]))
            i = j
        elif exp[i] in ['(', ')']:
            tokens.append(exp[i])
            i += 1
        else:
            raise LexError("lex failed")

    return tokens

# parse infix and return a rpn
# Key Point: when to pop stack
def parseInfix(exp):
    tokens = lex(exp)
    
    op_stack = []
    out = []
    for token in tokens:
        if isOperator(token):
            while op_stack and isOperator(op_stack[-1]):
                if ((isAssociative(token, LEFT_ASSOC) and cmpPrecedence(token, op_stack[-1]) <= 0)
                        or (isAssociative(token, RIGHT_ASSOC) and cmpPrecedence(token, op_stack[-1]) < 0)):
                    out.append(op_stack.pop())
                else:
                    break
            op_stack.append(token)
        elif token == '(':
            op_stack.append(token)
        elif token == ')':
            while op_stack and op_stack[-1] != '(':
                out.append(op_stack.pop())
            if op_stack: op_stack.pop()
            else: raise ParseError("parenthesis mismatch")
        else:
            out.append(token)
    while op_stack:
        out.append(op_stack.pop())
    return out

# evaluate rpn
def evalRPN(exp):
    pass

def evalBinOp(op, v1, v2):
    if op == '-':
        return v1 - v2
    elif op == '+':
        return v1 + v2
    elif op == '*':
        return v1 * v2
    elif op == '/':
        return v1 / v2

def evalOp(op, value_stack):
    v2 = value_stack.pop()
    v1 = value_stack.pop()
    value_stack.append(evalBinOp(op, v1, v2))


# evaluate infix without parsing it into rpn
# Key Point: evaluate when pop stack
def evalInfix(exp):
    tokens = lex(exp)

    op_stack = []
    value_stack = []
    
    for token in tokens:
        if isOperator(token):
            while op_stack and isOperator(op_stack[-1]):
                if ((isAssociative(token, LEFT_ASSOC) and cmpPrecedence(token, op_stack[-1]) <= 0)
                        or (isAssociative(token, RIGHT_ASSOC) and cmpPrecedence(token, op_stack[-1])) < 0):
                    op = op_stack.pop()
                    evalOp(op,value_stack)
                else:
                    break
            op_stack.append(token)
        elif token == '(':
            op_stack.append(token)
        elif token == ')':
            while op_stack and op_stack[-1] != '(':
                op = op_stack.pop()
                evalOp(op, value_stack)
            if op_stack: op_stack.pop()
            else: raise ParseError("parenthesis mismatch")
        else:
            value_stack.append(token)

    while op_stack:
        op = op_stack.pop()
        evalOp(op, value_stack)

    return value_stack[0]

print parseInfix('1*(21+3)-2+4/2')
print evalInfix('1*(21+3)-2+4/2')
